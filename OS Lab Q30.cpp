#include <stdio.h>
#include <windows.h>

DWORD WINAPI work(LPVOID p) {
    int id = *(int*)p;
    printf("Thread %d running\n", id);
    ExitThread(id);
    return 0;
}

int main() {
    HANDLE t1, t2;
    DWORD id1 = 1, id2 = 2;
    DWORD ret1, ret2;

    t1 = CreateThread(NULL, 0, work, &id1, 0, NULL);
    t2 = CreateThread(NULL, 0, work, &id2, 0, NULL);

    if (t1 == t2)
        printf("Threads are equal\n");
    else
        printf("Threads are not equal\n");

    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    GetExitCodeThread(t1, &ret1);
    GetExitCodeThread(t2, &ret2);

    printf("Thread 1 exited with %lu\n", ret1);
    printf("Thread 2 exited with %lu\n", ret2);

    CloseHandle(t1);
    CloseHandle(t2);

    return 0;
}

