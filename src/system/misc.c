#include <stdio.h>
#include <string.h>

char* string_input(char *buffer, int length) {
    char *str = fgets(buffer, length, stdin);

    if (str == NULL) {
        return str;
    }

    int index = strlen(str) - 1;
    int chr = 0;

    if (str[index] != '\n') {
        while (chr != '\n' && chr != EOF) {
            chr = getchar();
        }
    } else {
        str[index] = '\0';
    }

    return str;
}

int string_split(char *dest, const char *src, char *delim, int rows, int cols) {
    int length = strlen(src) + 1;
    int words_amount = 0;

    char buffer[length];
    memcpy(buffer, src, length);

    char *temp = strtok(buffer, delim);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dest[i * cols + j] = *temp;

            if (*temp == '\0') {
                break;
            }

            temp++;
        }

        temp = strtok(NULL, delim);
        words_amount++;

        if (temp == NULL) {
            break;
        }
    }

    return words_amount;
}