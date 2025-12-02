#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    // Create a named shared memory object
    hMapFile = CreateFileMapping(
                 INVALID_HANDLE_VALUE,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write access
                 0,                       // maximum object size (high-order DWORD)
                 256,                     // maximum object size (low-order DWORD)
                 "MySharedMemory");       // name of mapping object

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    // Map a view of the file into the process's address space
    pBuf = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                  FILE_MAP_ALL_ACCESS, // read/write permission
                                  0,
                                  0,
                                  256);

    if (pBuf == NULL) {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write data into shared memory
    sprintf((char*)pBuf, "Hello from Process 1!");

    printf("Data written to shared memory: %s\n", pBuf);

    // Simulate another process reading the data
    printf("Data read from shared memory: %s\n", pBuf);

    // Unmap and close
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
