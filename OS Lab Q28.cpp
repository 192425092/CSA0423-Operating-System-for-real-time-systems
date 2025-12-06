#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[500];

    if (argc != 3) return 0;

    fp = fopen(argv[2], "r");
    if (!fp) return 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, argv[1]))
            printf("%s", line);
    }

    fclose(fp);
    return 0;
}

