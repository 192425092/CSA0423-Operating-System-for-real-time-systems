#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char writeData[] = "Hello UNIX System Calls\n";
    char readData[100];
    int bytes;

    fd = open("sample.txt", O_CREAT | O_RDWR, 0644);

    write(fd, writeData, sizeof(writeData));

    lseek(fd, 0, SEEK_SET);

    bytes = read(fd, readData, sizeof(readData));
    readData[bytes] = '\0';

    printf("Data read from file: %s", readData);

    close(fd);

    return 0;
}

