#include <stdio.h>
#include <stdlib.h>

char* file_read(const char *filename) {
    FILE *file = fopen(filename, "r");

    size_t count = sizeof(char);
    int chr = 0;

    char *buffer = (char*)malloc(count);

    if (file == NULL || buffer == NULL) {
        free(buffer);
        return NULL;
    }

    while ((chr = getc(file)) != EOF) {
        if (chr != '\t') {
            buffer[count - 1] = chr;
            buffer = (char*)realloc(buffer, ++count);
        }
    }

    buffer[count - 1] = '\0';
    fclose(file);

    return buffer;
}
