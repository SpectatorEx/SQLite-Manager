#include "win32/console_win32.h"

BOOL console_window_title(LPCTSTR title) {
    return SetConsoleTitle(title);
}

BOOL console_window_size(SHORT width, SHORT height) {
    SMALL_RECT window_size = { 0, 0 };

    window_size.Right = width - 1;
    window_size.Bottom = height - 1;

    return SetConsoleWindowInfo(HANDLE_STDOUT, 1, &window_size);
}

COORD console_get_window_size(void) {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    BOOL error_check = GetConsoleScreenBufferInfo(HANDLE_STDOUT, &buffer_info);

    COORD window_size = { 0, 0 };

    if (error_check) {
        window_size.X = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
        window_size.Y = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;
    }

    return window_size; 
}

COORD console_get_window_max_size(void) {
    COORD window_size = GetLargestConsoleWindowSize(HANDLE_STDOUT);
    return window_size;
}

BOOL console_buffer_size(SHORT width, SHORT height) {
    COORD buffer_size;

    buffer_size.X = width;
    buffer_size.Y = height;

    return SetConsoleScreenBufferSize(HANDLE_STDOUT, buffer_size);
}

BOOL console_cursor_pos(SHORT x, SHORT y) {
    COORD pos;

    pos.X = x;
    pos.Y = y;

    return SetConsoleCursorPosition(HANDLE_STDOUT, pos);
}

BOOL console_cursor_info(BOOL visible, ULONG size) {
    CONSOLE_CURSOR_INFO cursor_info;

    cursor_info.bVisible = visible;
    cursor_info.dwSize = size;

    return SetConsoleCursorInfo(HANDLE_STDOUT, &cursor_info);
}

BOOL console_set_font(LPCWSTR font, SHORT width, SHORT height, UINT weight) {
    CONSOLE_FONT_INFOEX text_font;

    text_font.cbSize = sizeof(text_font);
    text_font.nFont = 0;
    text_font.dwFontSize.X = width;
    text_font.dwFontSize.Y = height;
    text_font.FontFamily = FW_DONTCARE;
    text_font.FontWeight = weight;

    lstrcpyW(text_font.FaceName, font);

    return SetCurrentConsoleFontEx(HANDLE_STDOUT, FALSE, &text_font);
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