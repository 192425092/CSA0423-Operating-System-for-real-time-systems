#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *d;
    struct dirent *de;

    d = opendir(".");
    if (!d) return 0;

    while ((de = readdir(d)) != NULL)
        printf("%s\n", de->d_name);

    closedir(d);
    return 0;
}

