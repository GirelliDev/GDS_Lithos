#ifndef NT_OBJECT_H
#define NT_OBJECT_H

#include "nt/status.h"
#include "nt/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declaration of internal object */
typedef struct _OBJECT_HEADER OBJECT_HEADER;

/* Public opaque object pointer */
typedef OBJECT_HEADER* POBJECT_HEADER;

/* Create a generic object of a given type. Returns a pointer to the internal header. */
NTSTATUS ObCreateObject(
    OBJECT_TYPE_ID TypeId,
    PUNICODE_STRING Name,          /* optional, may be NULL */
    ACCESS_MASK DesiredAccess,
    POBJECT_HEADER *ObjectOut);

/* Open an existing named object and obtain a handle. */
NTSTATUS ObOpenObjectByName(
    PUNICODE_STRING Name,
    ACCESS_MASK DesiredAccess,
    HANDLE *HandleOut);

/* Close a handle, releasing the reference. */
NTSTATUS ObCloseHandle(HANDLE Handle);

/* Reference an object via a handle. Returns a new reference (object pointer). */
NTSTATUS ObReferenceObjectByHandle(
    HANDLE Handle,
    ACCESS_MASK DesiredAccess,
    POBJECT_HEADER *ObjectOut);

/* Dereference an object obtained via ObReferenceObjectByHandle or ObCreateObject. */
void ObDereferenceObject(POBJECT_HEADER Object);

/* Query the name of an object (if named). Caller must free the returned buffer. */
NTSTATUS ObQueryObjectName(
    POBJECT_HEADER Object,
    PUNICODE_STRING NameOut);

/* Initialize the Object Manager (create root directory, etc.). */
NTSTATUS ObInitialize(void);

#ifdef __cplusplus
}
#endif

#endif /* NT_OBJECT_H */
