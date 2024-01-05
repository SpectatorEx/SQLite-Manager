#include "win32/console_color.h"

BOOL console_set_color(console_color color) {
    return SetConsoleTextAttribute(HANDLE_STDOUT, color);
}

USHORT console_get_color(void) {
    CONSOLE_SCREEN_BUFFER_INFO buffer;
    BOOL success = GetConsoleScreenBufferInfo(HANDLE_STDOUT, &buffer);

    if (!success) {
        return 0;
    }

    return buffer.wAttributes;
}