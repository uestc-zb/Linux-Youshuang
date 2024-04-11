#include <unistd.h>
#include <stdio.h>

int main()
{
    uid_t uid = getuid(); //真实用户ID
    uid_t euid = geteuid();
    printf("userid is %d, effective userid is: %d\n", uid, euid);
    return 0;
}