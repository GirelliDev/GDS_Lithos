#ifndef NT_TYPES_H
#define NT_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* Basic NT integer types */
typedef uint8_t  UCHAR;
typedef uint16_t USHORT;
typedef uint32_t ULONG;
typedef uint64_t ULONGLONG;
typedef int8_t   CHAR;
typedef int16_t  SHORT;
typedef int32_t  LONG;
typedef int64_t  LONGLONG;

typedef ULONG    ACCESS_MASK;

typedef void*    PVOID;

typedef const void* PCVOID;

/* Opaque handle type */
typedef uint32_t HANDLE;

/* Boolean */
typedef uint8_t BOOLEAN;

/* UNICODE_STRING – simplified for UTF-8 strings in this userspace implementation */
typedef struct _UNICODE_STRING {
    USHORT Length;        /* Length in bytes */
    USHORT MaximumLength; /* Allocated size in bytes */
    char*  Buffer;        /* UTF-8 null‑terminated buffer */
} UNICODE_STRING, *PUNICODE_STRING;

/* OBJECT_ATTRIBUTES – minimal subset */
typedef struct _OBJECT_ATTRIBUTES {
    ULONG           Length;
    HANDLE          RootDirectory;   /* optional, not used in this simplified version */
    PUNICODE_STRING ObjectName;      /* optional name */
    ULONG           Attributes;      /* flags – unused */
    PVOID           SecurityDescriptor; /* unused */
    PVOID           SecurityQualityOfService; /* unused */
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

/* Object type identifier – simple enum */
typedef enum _OBJECT_TYPE_ID {
    ObjectTypeDirectory,
    ObjectTypeSymbolicLink,
    ObjectTypeProcess,
    ObjectTypeThread,
    ObjectTypeFile,
    ObjectTypeSection,
    ObjectTypeEvent,
    ObjectTypeMutant,
    ObjectTypeSemaphore,
    ObjectTypeKey,
    ObjectTypeGeneric   /* fallback for user‑defined types */
} OBJECT_TYPE_ID;

#endif /* NT_TYPES_H */
