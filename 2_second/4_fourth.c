#include <stdio.h>
#include <malloc.h>
#include <string.h>

enum 
{ 
    READ = 10 
};

// READ:
// The amount of chars that we initially read.

char *
getline2(FILE *f)
{
    char str[READ] = { 0 };
    char *result = calloc(READ, sizeof(result[0]));

    if (result == 0) {
        return result;
    }

    size_t mallocked = READ;
    int string_length = 0;
    int flag = 0;

    while (fgets(str, READ, f) != NULL) {
        string_length = strlen(result);
        int input_length = strlen(str);

        if (string_length + READ >= mallocked) {
            mallocked *= 2;
            result = realloc(result, mallocked);
        }

        for (int i = 0; i < input_length; i++) {
            if (str[i] == '\n') {
                result[string_length + i + 1] = 0;
                flag = 1;
                break;
            }
        }

        memcpy(&result[string_length], str, input_length + 1);

        if (flag == 1) {
            return result;
        }
    }
    
    if (result[0] == 0) {
        free(result);
        return NULL;
    }

    return result;
} 

int main(void)
{
    char* a = getline2(stdin);

    printf("%s\n", a);

    return 0;
}
