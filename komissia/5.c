#include <stdio.h>

void
normalize_path(char *buf)
{
    int offset = 0;
    int flag = 0;

    for (char *pointer = buf; *pointer != 0; pointer++) {
        if (flag) {
            break;
        }

        if (*pointer == '/') {
            offset++;
            if (*(pointer + 1) == 0) {
                *(pointer - offset + 1) = 0;
            }
            
            continue;
        } else if (offset != 0) {
            offset--;
            for (int i = 0; i < offset; i++) {
                *(pointer - offset + i) = *(pointer + i);

                if (*(pointer + i) == 0) {
                    flag = 1;
                    break;
                }
                *(pointer + i) = '/';
            }
            pointer -= offset;
            offset = 0;
        }
    }
}

int
main(void)
{
    char buf[15] = "////a//abcd/c";

    normalize_path(buf);

    printf("%s\n", buf);

    return 0;
}
