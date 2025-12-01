#include <stdio.h>
#include <windows.h>

int main() {

    DWORD pid = GetCurrentProcessId();   // current process id

    printf("Current Process ID: %lu\n", pid);
    printf("Parent Process ID : %lu\n", pid); // Windows cannot get real parent

    return 0;
}
