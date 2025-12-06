#include <stdio.h>
#include <windows.h>

int counter = 0;
HANDLE mutex;

typedef struct {
    int id;
} ThreadData;

DWORD WINAPI worker(LPVOID p) {
    ThreadData *td = (ThreadData*)p;
    int id = td->id;

    for (int i = 0; i < 5; i++) {
        WaitForSingleObject(mutex, INFINITE);
        counter++;
        printf("Thread %d incremented counter to %d\n", id, counter);
        ReleaseMutex(mutex);
        Sleep(300);
    }
    return 0;
}

int main() {
    HANDLE t1, t2;
    ThreadData d1, d2;

    d1.id = 1;
    d2.id = 2;

    mutex = CreateMutex(NULL, FALSE, NULL);

    t1 = CreateThread(NULL, 0, worker, &d1, 0, NULL);
    t2 = CreateThread(NULL, 0, worker, &d2, 0, NULL);

    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    CloseHandle(t1);
    CloseHandle(t2);
    CloseHandle(mutex);

    return 0;
}

