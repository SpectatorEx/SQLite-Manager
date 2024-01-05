#include "win32/console_win32.h"

BOOL console_title(LPCTSTR title) {
    return SetConsoleTitle(title);
}

ULONG console_get_title(LPSTR title, ULONG size) {
    return GetConsoleTitle(title, size);
}

BOOL console_window_size(SHORT width, SHORT height) {
    SMALL_RECT window = { 0, 0 };

    window.Right = width - 1;
    window.Bottom = height - 1;

    return SetConsoleWindowInfo(HANDLE_STDOUT, 1, &window);
}

BOOL console_get_window_size(SHORT *width, SHORT *height) {
    CONSOLE_SCREEN_BUFFER_INFO buffer;
    BOOL success = GetConsoleScreenBufferInfo(HANDLE_STDOUT, &buffer);

    if (success) {
        *width = buffer.srWindow.Right - buffer.srWindow.Left + 1;
        *height = buffer.srWindow.Bottom - buffer.srWindow.Top + 1;
    }
    
    return success;
}

void console_get_window_max_size(SHORT *width, SHORT *height) {
    COORD size = GetLargestConsoleWindowSize(HANDLE_STDOUT);

    *width = size.X;
    *height = size.Y; 
}

BOOL console_buffer_size(SHORT width, SHORT height) {
    COORD size;

    size.X = width;
    size.Y = height;

    return SetConsoleScreenBufferSize(HANDLE_STDOUT, size);
}

BOOL console_get_buffer_size(SHORT *width, SHORT *height) {
    CONSOLE_SCREEN_BUFFER_INFO buffer;
    BOOL success = GetConsoleScreenBufferInfo(HANDLE_STDOUT, &buffer);

    if (success) {
        *width = buffer.dwSize.X;
        *height = buffer.dwSize.Y;
    }

    return success;
}

BOOL console_cursor_pos(SHORT x, SHORT y) {
    COORD pos;

    pos.X = x;
    pos.Y = y;

    return SetConsoleCursorPosition(HANDLE_STDOUT, pos);
}

BOOL console_get_cursor_pos(SHORT *x, SHORT *y) {
    CONSOLE_SCREEN_BUFFER_INFO buffer;
    BOOL success = GetConsoleScreenBufferInfo(HANDLE_STDOUT, &buffer);

    if (success) {
        *x = buffer.dwCursorPosition.X;
        *y = buffer.dwCursorPosition.Y;
    }

    return success;
}

BOOL console_cursor_info(BOOL visible, ULONG size) {
    CONSOLE_CURSOR_INFO cursor;

    cursor.bVisible = visible;
    cursor.dwSize = size;

    return SetConsoleCursorInfo(HANDLE_STDOUT, &cursor);
}

CONSOLE_CURSOR_INFO console_get_cursor_info(void) {
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(HANDLE_STDOUT, &cursor);

    return cursor;
}

BOOL console_set_font(LPCWSTR name, SHORT width, SHORT height, UINT weight) {
    CONSOLE_FONT_INFOEX font;

    font.cbSize = sizeof(font);
    font.nFont = 0;
    font.dwFontSize.X = width;
    font.dwFontSize.Y = height;
    font.FontFamily = FW_DONTCARE;
    font.FontWeight = weight;

    lstrcpyW(font.FaceName, name);

    return SetCurrentConsoleFontEx(HANDLE_STDOUT, FALSE, &font);
}

BOOL console_print_error(ULONG error_code) {
    ULONG size;
    TCHAR buffer[256];

    size = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, error_code, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                        buffer, 256, NULL);

    WriteConsole(HANDLE_STDOUT, buffer, lstrlen(buffer), NULL, NULL);

    return size > 0;
}