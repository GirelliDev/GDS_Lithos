#ifndef OB_INTERNAL_H
#define OB_INTERNAL_H

#include <pthread.h>
#include <stdatomic.h>
#include "../include/nt/status.h"
#include "../include/nt/types.h"

/* Forward declaration of public object header */
typedef struct _OBJECT_HEADER OBJECT_HEADER;

typedef struct _OBJECT_NAME_INFO {
    UNICODE_STRING Name;   /* Owned copy */
    OBJECT_HEADER *Object; /* Back‑reference */
    struct _OBJECT_NAME_INFO *Parent; /* For directory hierarchy */
    struct _OBJECT_NAME_INFO *Child;  /* First child (linked list) */
    struct _OBJECT_NAME_INFO *Sibling;/* Next sibling */
} OBJECT_NAME_INFO;

/* Internal object header – not exposed publicly */
struct _OBJECT_HEADER {
    atomic_uint refcount;          /* Number of active references */
    atomic_uint handlecount;       /* Number of open handles */
    OBJECT_TYPE_ID type_id;        /* Type identifier */
    ACCESS_MASK granted_access;    /* Access mask used when object created */
    pthread_mutex_t lock;          /* Protect internal fields */
    /* Optional name information – NULL if unnamed */
    OBJECT_NAME_INFO *name_info;
    /* Destructor callback – can be NULL for generic objects */
    void (*destructor)(OBJECT_HEADER *obj);
    /* Payload – for generic objects we keep it empty */
    void *payload;
};

/* Handle table entry */
typedef struct _HANDLE_ENTRY {
    OBJECT_HEADER *object;   /* Pointer to object */
    ACCESS_MASK granted;    /* Access rights for this handle */
    uint32_t generation;    /* Generation counter to detect stale handles */
    bool in_use;
} HANDLE_ENTRY;

/* Global handle table – simple fixed‑size table for this prototype */
#define HANDLE_TABLE_SIZE 65536

extern HANDLE_ENTRY g_handle_table[HANDLE_TABLE_SIZE];
extern pthread_mutex_t g_handle_table_lock;

/* Root directory object – created during initialization */
extern OBJECT_HEADER *g_root_directory;

/* Utility functions */
void ob_init_lock(pthread_mutex_t *mtx);
void ob_destroy_lock(pthread_mutex_t *mtx);

/* Name handling helpers */
NTSTATUS ob_parse_path(const UNICODE_STRING *path, OBJECT_NAME_INFO **out_parent, const char **out_leaf);
NTSTATUS ob_find_object_by_path(const UNICODE_STRING *path, OBJECT_HEADER **out_obj);
NTSTATUS ob_insert_named_object(OBJECT_HEADER *obj, const UNICODE_STRING *name);
NTSTATUS ob_remove_named_object(const UNICODE_STRING *name);

#endif /* OB_INTERNAL_H */
