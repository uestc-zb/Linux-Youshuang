#include <stdlib.h>
#include <string.h>
int main() {
    const char *path = "/home/user/example.txt";
    char *base = basename((char *)path);

    return 0;
}