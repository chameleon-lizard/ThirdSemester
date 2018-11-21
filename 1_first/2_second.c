#include "stdio.h"

int main(void) 
{
    enum 
    { 
        MASK_THIRD_BIT = 8, 
        MASK_SECOND_BIT = 251,
        MAX_NUMBER = 10,
        MAX_LOWERCASE = 36,
        MAX_UPPERCASE = 62
    };

    int current_char = 0;

    while ((current_char = getchar()) != EOF) {

        if (current_char >= '0' && current_char <= '9') {
            current_char = current_char - '0' + 1;
        } else if (current_char >= 'a' && current_char <= 'z') {
            current_char = current_char - 'a' + MAX_NUMBER + 1;
        } else if (current_char >= 'A' && current_char <= 'Z') {
            current_char = current_char - 'A' + MAX_LOWERCASE + 1;
        } else {
            current_char = -1;
        }
        
        current_char = current_char & MASK_SECOND_BIT;
        current_char = current_char ^ MASK_THIRD_BIT;
        
        if (current_char >= 1 && current_char <= MAX_NUMBER) {
            current_char = current_char + '0' - 1;
            putchar(current_char);
        } else if (current_char >= MAX_NUMBER + 1 && current_char <= MAX_LOWERCASE) {
            current_char = current_char + 'a' - MAX_NUMBER - 1;
            putchar(current_char);
        } else if (current_char >= MAX_LOWERCASE + 1 && current_char <= MAX_UPPERCASE) {
            current_char = current_char + 'A' - MAX_LOWERCASE - 1;
            putchar(current_char);
        } else if (current_char == MAX_UPPERCASE + 1) {
            putchar('#');
        } else if (current_char == 0) {
            putchar('@');
        }
    }

    return 0;
}
