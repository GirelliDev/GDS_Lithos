#include <stdio.h>
#include "../include/nt/object.h"
#include "../include/nt/status.h"
#include "../include/nt/types.h"

int main(void) {
    NTSTATUS st;
    POBJECT_HEADER obj = NULL;
    HANDLE h = 0;
    UNICODE_STRING name = {0};
    const char *path = "\\TestObj";
    name.Length = (USHORT)strlen(path);
    name.MaximumLength = name.Length + 1;
    name.Buffer = (char*)path; /* using static string for simplicity */

    /* Initialize manager */
    st = ObInitialize();
    if (!NT_SUCCESS(st)) {
        fprintf(stderr, "ObInitialize failed: 0x%08x\n", st);
        return 1;
    }

    /* Create object */
    st = ObCreateObject(ObjectTypeGeneric, &name, 0, &obj);
    if (!NT_SUCCESS(st)) {
        fprintf(stderr, "ObCreateObject failed: 0x%08x\n", st);
        return 1;
    }
    printf("Object created.\n");

    /* Open by name */
    st = ObOpenObjectByName(&name, 0, &h);
    if (!NT_SUCCESS(st)) {
        fprintf(stderr, "ObOpenObjectByName failed: 0x%08x\n", st);
        return 1;
    }
    printf("Handle opened: %u\n", h);

    /* Reference via handle */
    POBJECT_HEADER obj2 = NULL;
    st = ObReferenceObjectByHandle(h, 0, &obj2);
    if (!NT_SUCCESS(st)) {
        fprintf(stderr, "ObReferenceObjectByHandle failed: 0x%08x\n", st);
        return 1;
    }
    printf("Object referenced via handle.\n");

    /* Close handle */
    st = ObCloseHandle(h);
    if (!NT_SUCCESS(st)) {
        fprintf(stderr, "ObCloseHandle failed: 0x%08x\n", st);
        return 1;
    }
    printf("Handle closed.\n");

    /* Dereference original object */
    ObDereferenceObject(obj);
    ObDereferenceObject(obj2);
    printf("Objects dereferenced.\n");
    return 0;
}
