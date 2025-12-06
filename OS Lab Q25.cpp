#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hFile;
    DWORD written, readBytes;
    char buffer[100];
    WIN32_FIND_DATA findData;
    HANDLE hFind;

    hFile = CreateFile("demo.txt", GENERIC_WRITE | GENERIC_READ,
                       0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    WriteFile(hFile, "WINDOWS IO CALLS\n", 17, &written, NULL);

    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

    ReadFile(hFile, buffer, 17, &readBytes, NULL);
    buffer[readBytes] = '\0';
    printf("Read: %s\n", buffer);

    CloseHandle(hFile);

    printf("\nFiles in current directory:\n");

    hFind = FindFirstFile("*.*", &findData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            printf("%s\n", findData.cFileName);
        } while (FindNextFile(hFind, &findData));
        FindClose(hFind);
    }

    return 0;
}

