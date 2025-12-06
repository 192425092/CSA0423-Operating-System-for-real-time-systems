#include <stdio.h>
#include <windows.h>

int readCount = 0;
int sharedData = 0;

HANDLE mutexR;
HANDLE writeSem;

DWORD WINAPI reader(LPVOID p) {
    int id = *(int*)p;
    while (1) {
        WaitForSingleObject(mutexR, INFINITE);
        readCount++;
        if (readCount == 1)
            WaitForSingleObject(writeSem, INFINITE);
        ReleaseSemaphore(mutexR, 1, NULL);

        printf("Reader %d reads data = %d\n", id, sharedData);
        Sleep(300);

        WaitForSingleObject(mutexR, INFINITE);
        readCount--;
        if (readCount == 0)
            ReleaseSemaphore(writeSem, 1, NULL);
        ReleaseSemaphore(mutexR, 1, NULL);

        Sleep(500);
    }
    return 0;
}

DWORD WINAPI writer(LPVOID p) {
    int id = *(int*)p;
    while (1) {
        WaitForSingleObject(writeSem, INFINITE);

        sharedData++;
        printf("Writer %d updates data to %d\n", id, sharedData);

        ReleaseSemaphore(writeSem, 1, NULL);
        Sleep(600);
    }
    return 0;
}

int main() {
    HANDLE r1, r2, w1;
    int id1 = 1, id2 = 2, id3 = 1;

    mutexR = CreateSemaphore(NULL, 1, 1, NULL);
    writeSem = CreateSemaphore(NULL, 1, 1, NULL);

    r1 = CreateThread(NULL, 0, reader, &id1, 0, NULL);
    r2 = CreateThread(NULL, 0, reader, &id2, 0, NULL);
    w1 = CreateThread(NULL, 0, writer, &id3, 0, NULL);

    WaitForSingleObject(r1, INFINITE);
    WaitForSingleObject(r2, INFINITE);
    WaitForSingleObject(w1, INFINITE);

    CloseHandle(r1);
    CloseHandle(r2);
    CloseHandle(w1);
    CloseHandle(mutexR);
    CloseHandle(writeSem);

    return 0;
}

