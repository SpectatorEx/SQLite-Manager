#ifndef CONSOLE_KEY_H
#define CONSOLE_KEY_H

#include "console_win32.h"

/** \brief
 *      Default keys used in the CEngine32. 
 */
typedef enum 
{
    /* Standard keys */

    KEY_BACK = 0x08,
    KEY_ENTER = 0x0D,
    KEY_ESC = 0x1B,
    KEY_SPACE = 0x20,
    KEY_UP = 0x48,
    KEY_LEFT = 0x4B,
    KEY_RIGHT = 0x4D,
    KEY_DOWN = 0x50,

    KEY_N0 = 0x30,
    KEY_N1 = 0x31,
    KEY_N2 = 0x32,
    KEY_N3 = 0x33,
    KEY_N4 = 0x34,
    KEY_N5 = 0x35,
    KEY_N6 = 0x36,
    KEY_N7 = 0x37,
    KEY_N8 = 0x38,
    KEY_N9 = 0x39,

    KEY_A = 0x41,
    KEY_B = 0x42,
    KEY_C = 0x43,
    KEY_D = 0x44,
    KEY_E = 0x45,
    KEY_F = 0x46,
    KEY_G = 0x47,
    KEY_H = 0x48,
    KEY_I = 0x49,
    KEY_J = 0x4A,
    KEY_K = 0x4B,
    KEY_L = 0x4C,
    KEY_M = 0x4D,
    KEY_N = 0x4E,
    KEY_O = 0x4F,
    KEY_P = 0x50,
    KEY_Q = 0x51,
    KEY_R = 0x52,
    KEY_S = 0x53,
    KEY_T = 0x54,
    KEY_U = 0x55,
    KEY_V = 0x56,
    KEY_W = 0x57,
    KEY_X = 0x58,
    KEY_Y = 0x59,
    KEY_Z = 0x5A,

    /* Extended keys */

    KEY_F1 = 0x70,
    KEY_F2 = 0x71,
    KEY_F3 = 0x72,
    KEY_F4 = 0x73,
    KEY_F5 = 0x74,
    KEY_F6 = 0x75,
    KEY_F7 = 0x76,
    KEY_F8 = 0x77,
    KEY_F9 = 0x78,
    KEY_F10 = 0x79,
    KEY_F11 = 0x7A,
    KEY_F12 = 0x7B

} console_key;

#endif