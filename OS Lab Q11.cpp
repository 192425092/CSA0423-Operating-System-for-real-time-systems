#include <stdio.h>
#include <windows.h>

DWORD WINAPI threadFunction1(LPVOID p) {
    int i;
    for(i = 1; i <= 5; i++) {
        printf("Thread 1 count: %d\n", i);
        Sleep(500);
    }
    return 0;
}

DWORD WINAPI threadFunction2(LPVOID p) {
    int i;
    for(i = 1; i <= 5; i++) {
        printf("Thread 2 count: %d\n", i);
        Sleep(500);
    }
    return 0;
}

int main() {
    HANDLE t1, t2;

    t1 = CreateThread(NULL, 0, threadFunction1, NULL, 0, NULL);
    t2 = CreateThread(NULL, 0, threadFunction2, NULL, 0, NULL);

    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    CloseHandle(t1);
    CloseHandle(t2);

    return 0;
}

