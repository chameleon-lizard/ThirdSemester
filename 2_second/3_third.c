#include <stdio.h>
#include <malloc.h>
#include <string.h>

enum 
{ 
    NUMBER_AMOUNT = 10,
    AMOUNT_READ = 1024
};

// NUMBER_AMOUNT:
// It is the amount of numbers that are between 0 and 9. Used in the counter array.
// AMOUNT_READ:
// It is the amount of numbers that are read from the file at one time.

int
main(void)
{
    unsigned long long number_counts[NUMBER_AMOUNT] = { 0 };

    char filename[FILENAME_MAX + 3];

    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        size_t filename_length = strlen(filename);
    
        if (filename_length != 0) {
            for (int i = 0; filename[i] != 0; i++) {
                if (filename[i] == '\n' || filename[i] == '\r') {
                    filename[i] = 0;
                    break;
                }
            }
        
            FILE *file = fopen(filename, "r");
        
            if (file != NULL) {
                char current_chars[AMOUNT_READ];
                while (fgets(current_chars, sizeof(current_chars), file)) {
                    for (int i = 0; i < AMOUNT_READ && current_chars[i] != 0; i++) {
                        if (current_chars[i] >= '0' && current_chars[i] <= '9') {
                            number_counts[current_chars[i] - '0']++;
                        }
                    }
                }
            
                fclose(file);
            }
        }
    }


    for (int i = 0; i < NUMBER_AMOUNT; i++) {
        printf("%d %llu\n", i, number_counts[i]);
    }

    return 0;
}
