#include "ob_internal.h"
#include <stdlib.h>
#include <string.h>

/* Helper to allocate and copy a UNICODE_STRING (UTF‑8) */
static NTSTATUS copy_unicode_string(const UNICODE_STRING *src, UNICODE_STRING *dst) {
    if (!src || !dst) return STATUS_INVALID_PARAMETER;
    size_t len = src->Length;
    size_t max = src->MaximumLength;
    if (max == 0) max = len + 1; /* ensure space for NUL */
    char *buf = malloc(max);
    if (!buf) return STATUS_INSUFFICIENT_RESOURCES;
    memcpy(buf, src->Buffer, len);
    buf[len] = '\0';
    dst->Length = (USHORT)len;
    dst->MaximumLength = (USHORT)max;
    dst->Buffer = buf;
    return STATUS_SUCCESS;
}

/* Split a path like "\\BaseNamedObjects\\MyObj" into parent directory and leaf name.
   Returns OBJECT_NAME_INFO for the parent (or root) and the leaf component string. */
NTSTATUS ob_parse_path(const UNICODE_STRING *path, OBJECT_NAME_INFO **out_parent, const char **out_leaf) {
    if (!path || !out_parent || !out_leaf) return STATUS_INVALID_PARAMETER;
    /* Ensure path starts with backslash */
    if (path->Length == 0 || path->Buffer[0] != '\\') {
        return STATUS_OBJECT_NAME_INVALID;
    }
    /* Duplicate path for tokenisation */
    char *dup = strndup(path->Buffer, path->Length);
    if (!dup) return STATUS_INSUFFICIENT_RESOURCES;
    char *saveptr = NULL;
    char *token = strtok_r(dup, "\\", &saveptr);
    OBJECT_NAME_INFO *parent = NULL;
    OBJECT_NAME_INFO *current = NULL;
    /* Start from root */
    if (g_root_directory) {
        /* Create a synthetic OBJECT_NAME_INFO for root (no name) */
        parent = calloc(1, sizeof(OBJECT_NAME_INFO));
        if (!parent) { free(dup); return STATUS_INSUFFICIENT_RESOURCES; }
        parent->Object = g_root_directory;
    }
    while (token) {
        const char *next = strtok_r(NULL, "\\", &saveptr);
        if (next == NULL) {
            /* Leaf component */
            *out_parent = parent;
            *out_leaf = token;
            free(dup);
            return STATUS_SUCCESS;
        }
        /* Find child with matching name */
        OBJECT_NAME_INFO *child = NULL;
        for (child = parent ? parent->Child : NULL; child; child = child->Sibling) {
            if (strcmp(child->Name.Buffer, token) == 0) {
                break;
            }
        }
        if (!child) {
            free(dup);
            return STATUS_OBJECT_NAME_NOT_FOUND;
        }
        parent = child;
        token = next;
    }
    free(dup);
    return STATUS_OBJECT_NAME_NOT_FOUND;
}

NTSTATUS ob_find_object_by_path(const UNICODE_STRING *path, OBJECT_HEADER **out_obj) {
    if (!path || !out_obj) return STATUS_INVALID_PARAMETER;
    OBJECT_NAME_INFO *parent = NULL;
    const char *leaf = NULL;
    NTSTATUS st = ob_parse_path(path, &parent, &leaf);
    if (!NT_SUCCESS(st)) return st;
    /* Search leaf under parent */
    OBJECT_NAME_INFO *child = NULL;
    for (child = parent ? parent->Child : NULL; child; child = child->Sibling) {
        if (strcmp(child->Name.Buffer, leaf) == 0) {
            *out_obj = child->Object;
            return STATUS_SUCCESS;
        }
    }
    return STATUS_OBJECT_NAME_NOT_FOUND;
}

NTSTATUS ob_insert_named_object(OBJECT_HEADER *obj, const UNICODE_STRING *name) {
    if (!obj || !name) return STATUS_INVALID_PARAMETER;
    /* Parse path – need parent directory */
    OBJECT_NAME_INFO *parent = NULL;
    const char *leaf = NULL;
    NTSTATUS st = ob_parse_path(name, &parent, &leaf);
    if (!NT_SUCCESS(st) && st != STATUS_OBJECT_NAME_NOT_FOUND) {
        return st;
    }
    if (!parent) {
        /* Insert directly under root */
        parent = calloc(1, sizeof(OBJECT_NAME_INFO));
        if (!parent) return STATUS_INSUFFICIENT_RESOURCES;
        parent->Object = g_root_directory;
    }
    /* Ensure leaf not already present */
    for (OBJECT_NAME_INFO *c = parent->Child; c; c = c->Sibling) {
        if (strcmp(c->Name.Buffer, leaf) == 0) {
            return STATUS_OBJECT_NAME_COLLISION;
        }
    }
    /* Allocate name info */
    OBJECT_NAME_INFO *info = calloc(1, sizeof(OBJECT_NAME_INFO));
    if (!info) return STATUS_INSUFFICIENT_RESOURCES;
    UNICODE_STRING copy = {0};
    st = copy_unicode_string(name, &copy);
    if (!NT_SUCCESS(st)) { free(info); return st; }
    info->Name = copy;
    info->Object = obj;
    /* Link into parent's child list */
    info->Parent = parent;
    info->Sibling = parent->Child;
    parent->Child = info;
    obj->name_info = info;
    return STATUS_SUCCESS;
}

NTSTATUS ob_remove_named_object(const UNICODE_STRING *name) {
    if (!name) return STATUS_INVALID_PARAMETER;
    OBJECT_NAME_INFO *parent = NULL;
    const char *leaf = NULL;
    NTSTATUS st = ob_parse_path(name, &parent, &leaf);
    if (!NT_SUCCESS(st)) return st;
    OBJECT_NAME_INFO *prev = NULL;
    for (OBJECT_NAME_INFO *c = parent ? parent->Child : NULL; c; c = c->Sibling) {
        if (strcmp(c->Name.Buffer, leaf) == 0) {
            /* Unlink */
            if (prev) prev->Sibling = c->Sibling; else parent->Child = c->Sibling;
            /* Free name buffer */
            free(c->Name.Buffer);
            free(c);
            return STATUS_SUCCESS;
        }
        prev = c;
    }
    return STATUS_OBJECT_NAME_NOT_FOUND;
}

