#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int main()
{
    char buf[BUFSIZ];

    memset(buf, 0, BUFSIZ);

    if (fgets(buf, BUFSIZ, stdin) < 0)
    {
        perror("fgets");
        exit(1);
    }
    buf[strlen(buf) - 1] = '\0';

    printf("%s\n", buf);
}
