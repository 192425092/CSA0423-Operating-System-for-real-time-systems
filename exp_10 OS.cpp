#include <windows.h>
#include <stdio.h>
#include <string.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"
#define BUF_SIZE 256

DWORD WINAPI ClientThread(LPVOID lpParam) {
    HANDLE hClient;
    char buffer[BUF_SIZE];
    DWORD bytesRead = 0, bytesWritten = 0;

    // Wait until the pipe is available, then connect as client
    if (!WaitNamedPipeA(PIPE_NAME, 5000)) {
        printf("[Client] WaitNamedPipe failed. Error: %lu\n", GetLastError());
        return 1;
    }

    hClient = CreateFileA(
        PIPE_NAME,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hClient == INVALID_HANDLE_VALUE) {
        printf("[Client] CreateFile failed. Error: %lu\n", GetLastError());
        return 1;
    }

    // Read message from server
    if (!ReadFile(hClient, buffer, BUF_SIZE - 1, &bytesRead, NULL)) {
        printf("[Client] ReadFile failed. Error: %lu\n", GetLastError());
        CloseHandle(hClient);
        return 1;
    }
    buffer[bytesRead] = '\0';
    printf("[Client] Received: %s\n", buffer);

    // Send reply to server
    const char* reply = "Hello from Client!";
    if (!WriteFile(hClient, reply, (DWORD)(strlen(reply) + 1), &bytesWritten, NULL)) {
        printf("[Client] WriteFile failed. Error: %lu\n", GetLastError());
        CloseHandle(hClient);
        return 1;
    }
    printf("[Client] Sent: %s\n", reply);

    CloseHandle(hClient);
    return 0;
}

int main() {
    HANDLE hPipe = INVALID_HANDLE_VALUE;
    HANDLE hThread = NULL;
    DWORD threadId = 0;
    char buffer[BUF_SIZE];
    DWORD bytesWritten = 0, bytesRead = 0;

    // Create the named pipe (server side)
    hPipe = CreateNamedPipeA(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,                       // read/write
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,                                        // max instances
        BUF_SIZE,                                 // out buffer
        BUF_SIZE,                                 // in buffer
        0,                                        // default timeout
        NULL                                      // default security
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("[Server] CreateNamedPipe failed. Error: %lu\n", GetLastError());
        return 1;
    }

    // Start client thread that will connect to this pipe
    hThread = CreateThread(NULL, 0, ClientThread, NULL, 0, &threadId);
    if (hThread == NULL) {
        printf("[Server] CreateThread failed. Error: %lu\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("[Server] Waiting for client to connect...\n");
    if (!ConnectNamedPipe(hPipe, NULL)) {
        DWORD err = GetLastError();
        if (err != ERROR_PIPE_CONNECTED) {
            printf("[Server] ConnectNamedPipe failed. Error: %lu\n", err);
            CloseHandle(hPipe);
            CloseHandle(hThread);
            return 1;
        }
    }
    printf("[Server] Client connected.\n");

    // Send a message to the client
    const char* msg = "Hello from Server!";
    if (!WriteFile(hPipe, msg, (DWORD)(strlen(msg) + 1), &bytesWritten, NULL)) {
        printf("[Server] WriteFile failed. Error: %lu\n", GetLastError());
        CloseHandle(hPipe);
        CloseHandle(hThread);
        return 1;
    }
    printf("[Server] Sent: %s\n", msg);

    // Read the client's reply
    if (!ReadFile(hPipe, buffer, BUF_SIZE - 1, &bytesRead, NULL)) {
        printf("[Server] ReadFile failed. Error: %lu\n", GetLastError());
        CloseHandle(hPipe);
        CloseHandle(hThread);
        return 1;
    }
    buffer[bytesRead] = '\0';
    printf("[Server] Received: %s\n", buffer);

    // Cleanup
    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);

    // Wait for client thread to end
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    printf("IPC demo completed successfully.\n");
    return 0;
}
