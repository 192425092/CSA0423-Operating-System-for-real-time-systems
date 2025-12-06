#include <stdio.h>
#include <windows.h>

#define BUFFER 5

int buf[BUFFER];
int in = 0, out = 0;

HANDLE empty, full, mutex;

DWORD WINAPI producer(LPVOID p) {
    int item = 1;
    while (1) {
        WaitForSingleObject(empty, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        buf[in] = item;
        printf("Producer produced %d at %d\n", item, in);
        in = (in + 1) % BUFFER;
        item++;

        ReleaseSemaphore(mutex, 1, NULL);
        ReleaseSemaphore(full, 1, NULL);
        Sleep(400);
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID p) {
    int item;
    while (1) {
        WaitForSingleObject(full, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        item = buf[out];
        printf("Consumer consumed %d from %d\n", item, out);
        out = (out + 1) % BUFFER;

        ReleaseSemaphore(mutex, 1, NULL);
        ReleaseSemaphore(empty, 1, NULL);
        Sleep(600);
    }
    return 0;
}

int main() {
    HANDLE prod, cons;

    empty = CreateSemaphore(NULL, BUFFER, BUFFER, NULL);
    full  = CreateSemaphore(NULL, 0, BUFFER, NULL);
    mutex = CreateSemaphore(NULL, 1, 1, NULL);

    prod = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    cons = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(prod, INFINITE);
    WaitForSingleObject(cons, INFINITE);

    CloseHandle(prod);
    CloseHandle(cons);
    CloseHandle(empty);
    CloseHandle(full);
    CloseHandle(mutex);

    return 0;
}

