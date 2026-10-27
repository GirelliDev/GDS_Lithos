#include "ob_internal.h"
#include <stdlib.h>
#include <string.h>

/* Forward declarations */
static void default_destructor(OBJECT_HEADER *obj);

NTSTATUS ObInitialize(void) {
    /* Initialize global lock */
    ob_init_lock(&g_handle_table_lock);
    for (size_t i = 0; i < HANDLE_TABLE_SIZE; ++i) {
        g_handle_table[i].in_use = false;
        g_handle_table[i].object = NULL;
        g_handle_table[i].granted = 0;
        g_handle_table[i].generation = 0;
    }
    /* Create root directory */
    OBJECT_HEADER *root = NULL;
    NTSTATUS status = ObCreateObject(ObjectTypeDirectory, NULL, 0, &root);
    if (!NT_SUCCESS(status)) {
        return status;
    }
    g_root_directory = root;
    return STATUS_SUCCESS;
}

static void default_destructor(OBJECT_HEADER *obj) {
    if (!obj) return;
    /* Free name info if present */
    if (obj->name_info) {
        if (obj->name_info->Name.Buffer) {
            free(obj->name_info->Name.Buffer);
        }
        free(obj->name_info);
    }
    free(obj);
}

NTSTATUS ObCreateObject(
    OBJECT_TYPE_ID TypeId,
    PUNICODE_STRING Name,
    ACCESS_MASK DesiredAccess,
    POBJECT_HEADER *ObjectOut) {

    if (!ObjectOut) return STATUS_INVALID_PARAMETER;
    OBJECT_HEADER *obj = calloc(1, sizeof(OBJECT_HEADER));
    if (!obj) return STATUS_INSUFFICIENT_RESOURCES;

    atomic_init(&obj->refcount, 1); /* initial reference */
    atomic_init(&obj->handlecount, 0);
    obj->type_id = TypeId;
    obj->granted_access = DesiredAccess;
    obj->destructor = default_destructor;
    obj->payload = NULL;
    pthread_mutex_init(&obj->lock, NULL);
    obj->name_info = NULL;

    if (Name) {
        NTSTATUS ns = ob_insert_named_object(obj, Name);
        if (!NT_SUCCESS(ns)) {
            /* Cleanup */
            pthread_mutex_destroy(&obj->lock);
            free(obj);
            return ns;
        }
    }

    *ObjectOut = obj;
    return STATUS_SUCCESS;
}

NTSTATUS ObOpenObjectByName(
    PUNICODE_STRING Name,
    ACCESS_MASK DesiredAccess,
    HANDLE *HandleOut) {
    if (!Name || !HandleOut) return STATUS_INVALID_PARAMETER;
    OBJECT_HEADER *obj = NULL;
    NTSTATUS status = ob_find_object_by_path(Name, &obj);
    if (!NT_SUCCESS(status)) return status;
    /* Create handle */
    pthread_mutex_lock(&g_handle_table_lock);
    for (uint32_t i = 0; i < HANDLE_TABLE_SIZE; ++i) {
        if (!g_handle_table[i].in_use) {
            g_handle_table[i].in_use = true;
            g_handle_table[i].object = obj;
            g_handle_table[i].granted = DesiredAccess;
            g_handle_table[i].generation++;
            uint32_t handle = (g_handle_table[i].generation << 16) | i;
            /* Increment counts */
            atomic_fetch_add_explicit(&obj->handlecount, 1, memory_order_relaxed);
            atomic_fetch_add_explicit(&obj->refcount, 1, memory_order_relaxed);
            *HandleOut = handle;
            pthread_mutex_unlock(&g_handle_table_lock);
            return STATUS_SUCCESS;
        }
    }
    pthread_mutex_unlock(&g_handle_table_lock);
    return STATUS_INSUFFICIENT_RESOURCES; /* no free handle slots */
}

NTSTATUS ObCloseHandle(HANDLE Handle) {
    uint16_t index = Handle & 0xFFFF;
    uint16_t gen = (Handle >> 16) & 0xFFFF;
    if (index >= HANDLE_TABLE_SIZE) return STATUS_INVALID_HANDLE;
    pthread_mutex_lock(&g_handle_table_lock);
    HANDLE_ENTRY *entry = &g_handle_table[index];
    if (!entry->in_use || entry->generation != gen) {
        pthread_mutex_unlock(&g_handle_table_lock);
        return STATUS_INVALID_HANDLE;
    }
    OBJECT_HEADER *obj = entry->object;
    entry->in_use = false;
    entry->object = NULL;
    entry->granted = 0;
    /* Decrement counts */
    atomic_fetch_sub_explicit(&obj->handlecount, 1, memory_order_relaxed);
    pthread_mutex_unlock(&g_handle_table_lock);
    /* Dereference the object (handle reference) */
    ObDereferenceObject(obj);
    return STATUS_SUCCESS;
}

NTSTATUS ObReferenceObjectByHandle(
    HANDLE Handle,
    ACCESS_MASK DesiredAccess,
    POBJECT_HEADER *ObjectOut) {
    if (!ObjectOut) return STATUS_INVALID_PARAMETER;
    uint16_t index = Handle & 0xFFFF;
    uint16_t gen = (Handle >> 16) & 0xFFFF;
    if (index >= HANDLE_TABLE_SIZE) return STATUS_INVALID_HANDLE;
    pthread_mutex_lock(&g_handle_table_lock);
    HANDLE_ENTRY *entry = &g_handle_table[index];
    if (!entry->in_use || entry->generation != gen) {
        pthread_mutex_unlock(&g_handle_table_lock);
        return STATUS_INVALID_HANDLE;
    }
    OBJECT_HEADER *obj = entry->object;
    /* Verify access */
    if ((entry->granted & DesiredAccess) != DesiredAccess) {
        pthread_mutex_unlock(&g_handle_table_lock);
        return STATUS_ACCESS_DENIED;
    }
    atomic_fetch_add_explicit(&obj->refcount, 1, memory_order_relaxed);
    pthread_mutex_unlock(&g_handle_table_lock);
    *ObjectOut = obj;
    return STATUS_SUCCESS;
}

void ObDereferenceObject(OBJECT_HEADER *Object) {
    if (!Object) return;
    if (atomic_fetch_sub_explicit(&Object->refcount, 1, memory_order_acq_rel) == 1) {
        /* Last reference – check handle count */
        if (atomic_load_explicit(&Object->handlecount, memory_order_acquire) == 0) {
            /* Safe to destroy */
            if (Object->destructor) {
                Object->destructor(Object);
            } else {
                default_destructor(Object);
            }
        }
    }
}

NTSTATUS ObQueryObjectName(
    OBJECT_HEADER *Object,
    PUNICODE_STRING NameOut) {
    if (!Object || !NameOut) return STATUS_INVALID_PARAMETER;
    if (!Object->name_info) return STATUS_OBJECT_NAME_NOT_FOUND;
    UNICODE_STRING src = Object->name_info->Name;
    char *buf = malloc(src.MaximumLength);
    if (!buf) return STATUS_INSUFFICIENT_RESOURCES;
    memcpy(buf, src.Buffer, src.Length);
    buf[src.Length] = '\0';
    NameOut->Length = src.Length;
    NameOut->MaximumLength = src.MaximumLength;
    NameOut->Buffer = buf;
    return STATUS_SUCCESS;
}

