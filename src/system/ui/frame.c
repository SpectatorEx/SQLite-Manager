#include <stdio.h>
#include <stdarg.h>

#include "cengine32.h"
#include "ui/frame.h"

extern int string_split(char *dest, const char *src, char *delim, int rows, int cols);
extern char* string_input(char *buffer, int length);

void ui_frame_draw(ui_frame *frame) {
    for (short y = 0; y < frame->size.height; y++) {
        console_cursor_pos(frame->size.x, frame->size.y + y);

        for (short x = 0; x < frame->size.width; x++) {
            if ((y == 0 || y == frame->size.height - 1)
                || (x == 0 || x == frame->size.width - 1)) {

                putchar('#');
                continue;
            } 

            putchar(' ');
        }
    }

    if (frame->name != NULL) {
        uint16 center_x = frame->size.width / 2 - strlen(frame->name) / 2;

        console_cursor_pos(frame->size.x + center_x - 1, frame->size.y);
        printf("[%s]", frame->name);
    }
}

void ui_frame_clear(ui_frame *frame) {
    for (short i = 0; i < frame->size.height - 2; i++) {
        for (short j = 0; j < frame->size.width - 2; j++) {
            console_cursor_pos(frame->size.x + j + 1, frame->size.y + i + 1);
            putchar(' ');
        }
    }
}

void ui_frame_print(ui_frame *frame, const char *text) {
    if (text == NULL) { return; }

    char buffer[32][16];

    int length = 0, pos_y = 0; 
    int amount = string_split(buffer[0], text, "\n ", 32, 16);

    ui_frame_clear(frame);
    console_cursor_pos(frame->size.x + 2, frame->size.y + 2);

    for (int i = 0; i < amount - 1; i++) {
        if (pos_y >= frame->size.height - 4) {
            return;
        }

        length += strlen(buffer[i]) + 1;
        printf("%s ", buffer[i]);

        if (length + strlen(buffer[i + 1]) > frame->size.width - 4) {
            length = 0, pos_y++;
            console_cursor_pos(frame->size.x + 2, frame->size.y + pos_y + 2);
        }
    }

    puts(buffer[amount - 1]);
}

void ui_frame_printf(ui_frame *frame, const char *format, ...) {
    va_list args, temp_args;

    va_start(args, format);
    va_copy(temp_args, args);

    int length = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);

    if (length < 0) {
        ui_frame_print(frame, "Format string error.");
        return;
    }

    char buffer[length];

    vsnprintf(buffer, sizeof(buffer), format, temp_args);
    va_end(temp_args);

    ui_frame_print(frame, buffer);
}

void ui_frame_input(ui_frame *frame, const char *message, char *buffer, int length) {
    ui_frame_print(frame, message);

    console_cursor_info(TRUE, 1);
    console_cursor_pos(frame->size.x + strlen(message) + 3, 
        frame->size.y + 2);

    char *str = string_input(buffer, length);

    if (str == NULL) {
        ui_frame_print(frame, "Input error!");
    }

    console_cursor_info(FALSE, 1);
}