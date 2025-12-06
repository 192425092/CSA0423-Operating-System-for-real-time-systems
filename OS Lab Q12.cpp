#include <stdio.h>
#include <windows.h>

#define N 5

HANDLE chopstick[N];

DWORD WINAPI philosopher(LPVOID p) {
    int id = *(int*)p;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        Sleep(300);

        WaitForSingleObject(chopstick[left], INFINITE);
        WaitForSingleObject(chopstick[right], INFINITE);

        printf("Philosopher %d is eating\n", id);
        Sleep(300);

        ReleaseSemaphore(chopstick[left], 1, NULL);
        ReleaseSemaphore(chopstick[right], 1, NULL);
    }
    return 0;
}

int main() {
    int i;
    HANDLE th[N];
    int ids[N];

    for (i = 0; i < N; i++) {
        chopstick[i] = CreateSemaphore(NULL, 1, 1, NULL);
        if (chopstick[i] == NULL) {
            printf("CreateSemaphore failed\n");
            return 1;
        }
    }

    for (i = 0; i < N; i++) {
        ids[i] = i;
        th[i] = CreateThread(NULL, 0, philosopher, &ids[i], 0, NULL);
        if (th[i] == NULL) {
            printf("CreateThread failed for philosopher %d\n", i);
            return 1;
        }
    }

    WaitForMultipleObjects(N, th, TRUE, INFINITE);

    for (i = 0; i < N; i++) {
        CloseHandle(th[i]);
        CloseHandle(chopstick[i]);
    }

    return 0;
}


