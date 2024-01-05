#ifndef UI_FRAME_H
#define UI_FRAME_H

#include "system/types.h"

typedef struct {
    const char *name;
    rect size;
} ui_frame;

void ui_frame_draw(ui_frame *frame);
void ui_frame_clear(ui_frame *frame);
void ui_frame_print(ui_frame *frame, const char *text);
void ui_frame_printf(ui_frame *frame, const char *format, ...);
void ui_frame_input(ui_frame *frame, const char *message, char *buffer, int length);

#endif