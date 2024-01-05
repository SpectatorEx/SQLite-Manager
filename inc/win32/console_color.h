#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H

#include "console_win32.h"

/**
 *  \brief
 *       Basic colors used in the console.
 */
typedef enum {

    COLOR_BLACK        = 0,

    FCOLOR_DARKBLUE    = 0x01,
    FCOLOR_DARKGREEN   = 0x02,
    FCOLOR_DARKCYAN    = 0x03,
    FCOLOR_DARKRED     = 0x04,
    FCOLOR_DARKMAGENTA = 0x05,
    FCOLOR_DARKYELLOW  = 0x06,
    FCOLOR_GRAY        = 0x07,
    FCOLOR_DARKGRAY    = 0x08,
    FCOLOR_BLUE        = 0x09,
    FCOLOR_GREEN       = 0x0A,
    FCOLOR_CYAN        = 0x0B,
    FCOLOR_RED         = 0x0C,
    FCOLOR_MAGENTA     = 0x0D,
    FCOLOR_YELLOW      = 0x0E,
    FCOLOR_WHITE       = 0x0F,

    BCOLOR_DARKBLUE    = 0x10,
    BCOLOR_DARKGREEN   = 0x20,
    BCOLOR_DARKCYAN    = 0x30,
    BCOLOR_DARKRED     = 0x40,
    BCOLOR_DARKMAGENTA = 0x50,
    BCOLOR_DARKYELLOW  = 0x60,
    BCOLOR_GRAY        = 0x70,
    BCOLOR_DARKGRAY    = 0x80,
    BCOLOR_BLUE        = 0x90,
    BCOLOR_GREEN       = 0xA0,
    BCOLOR_CYAN        = 0xB0,
    BCOLOR_RED         = 0xC0,
    BCOLOR_MAGENTA     = 0xD0,
    BCOLOR_YELLOW      = 0xE0,
    BCOLOR_WHITE       = 0xF0

} console_color;

/** 
 *  \brief
 *       Sets the color of text attributes.
 *       You can combine foreground and background colors.
 *       Example: FCOLOR_CYAN | BCOLOR_WHITE.
 *  \param color
 *       Color index. (Example: FCOLOR_CYAN).
 *  \return
 *       If the function succeeds, the return value is true.
 *       Otherwise false.
 */
BOOL console_set_color(console_color color);

/** 
 *  \brief 
 *      Returns the color index of text attributes.
 *  \return
 *      Returns zero if there are any errors.
 */
USHORT console_get_color(void);

#endif