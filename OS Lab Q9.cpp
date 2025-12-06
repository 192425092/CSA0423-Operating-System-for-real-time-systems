#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hMapFile;
    char *data;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        1024,
        "MySharedMemory"
    );

    if (hMapFile == NULL) {
        printf("Could not create shared memory\n");
        return 1;
    }

    data = (char*) MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        1024
    );

    if (data == NULL) {
        printf("Could not map view\n");
        CloseHandle(hMapFile);
        return 1;
    }

    printf("Enter message to write: ");
    gets(data);

    printf("Data written to shared memory.\n");

    UnmapViewOfFile(data);
    CloseHandle(hMapFile);

    return 0;
}

