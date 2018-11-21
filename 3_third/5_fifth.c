#include <stdio.h>
#include <string.h>

long
readNumber(char *numbers)
{
    return 0;
}

int
main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        int string_length = strlen(argv[i]);
        for(int j = 0; j < string_length; j++)
            getc(argv[i][j]);
        }
    }

    return 0;
}
