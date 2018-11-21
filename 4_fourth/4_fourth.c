#include <malloc.h>

void
normalize_path(char *buf)
{
    char *current_char = buf;
    char *current_buf = buf - 1;
    char last_char = 0;

    while (*(current_char) != 0) {
        if (*current_char == '/' && last_char != '/') {
            *current_buf = last_char;
            last_char = '/';
            current_buf++;
        } else if (*current_char != '/') {
            *current_buf = last_char;
            last_char = *current_char;
            current_buf++;
        }

        current_char++;
    }
    
    if (last_char != '/') {
        *current_buf = last_char;
        current_buf++;
    }
    
    if (*--current_char == '/') {
        *current_buf = '/';
        current_buf++;
    }
    
    *current_buf = 0;
} 

int
main(void)
{
    char* buf = calloc(20, sizeof(char));

    scanf("%s", buf);
    normalize_path(buf);
    printf("%s\n", buf);

    return 0;
}

