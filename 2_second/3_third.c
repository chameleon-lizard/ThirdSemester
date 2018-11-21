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
            if (filename[filename_length - 1] == '\n') {
                filename[filename_length - 1] = 0;
    
                filename_length = strlen(filename);
        
                if (filename[filename_length - 1] == '\r') {
                    filename[filename_length - 1] = 0;
                }
            }
        
            FILE *file = fopen(filename, "r");
        
            if (file != NULL) {
                char current_chars[AMOUNT_READ];
                size_t count_read = 0;
            
                while (fgets(current_chars, sizeof(current_chars), file)) {
                    count_read = strlen(current_chars);
                    for (int j = 0; j < count_read; j++) {
                        if (current_chars[j] >= '0' && current_chars[j] <= '9') {
                            number_counts[current_chars[j] - '0']++;
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
