#include "win32/console_color.h"

BOOL console_set_color(console_color color) {
    return SetConsoleTextAttribute(HANDLE_STDOUT, color);
}

USHORT console_get_color(void) {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    BOOL error_check = GetConsoleScreenBufferInfo(HANDLE_STDOUT, &buffer_info);

    if (!error_check) {
        return 0;
    }

    return buffer_info.wAttributes;
}