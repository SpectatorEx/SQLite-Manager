#ifndef CONSOLE_WIN32_H
#define CONSOLE_WIN32_H

#include <windows.h>

#include "console_color.h"
#include "console_key.h"

#define HANDLE_STDIN GetStdHandle(STD_INPUT_HANDLE)
#define HANDLE_STDOUT GetStdHandle(STD_OUTPUT_HANDLE)

/**
 *  \brief
 *      Sets title of console.
 *  \param title
 *      Pointer to string.
 *  \return
 *      If the function succeeds, the return value is true.
 *      Otherwise false.     
 */
BOOL console_window_title(LPCTSTR title);

/**
 *  \brief 
 *      Sets the size of the console window.
 *  \param width
 *      The width is measured in the number of columns.
 *  \param height
 *      The height is measured in the number of rows.
 *  \warning
 *      Before increasing the window size, you need to set a buffer 
 *      for it equal to the size of your window or larger.
 *  \return
 *      If the function succeeds, the return value is true.
 *      Otherwise false.
 */
BOOL console_window_size(SHORT width, SHORT height);

/**
 *  \brief 
 *      Returns the current number of rows and columns 
 *      in the console window.
 */
COORD console_get_window_size(void);

/**
 *  \brief
 *      Returns the number of rows and columns 
 *      based on the current font and screen resolution.
 */
COORD console_get_window_max_size(void);

/**
 *  \brief 
 *      Sets the size of the console buffer. 
 *  \param width
 *      The width is measured in the number of columns.
 *  \param height
 *      The height is measured in the number of rows.
 *  \return
 *      If the function succeeds, the return value is true.
 *      Otherwise false.
 */ 
BOOL console_buffer_size(SHORT width, SHORT height);

/**  
 *  \brief 
 *      Sets the cursor position.
 *  \return
 *      If the function succeeds, the return value is true.
 *      Otherwise false.
 */
BOOL console_cursor_pos(SHORT x, SHORT y);

/** \brief 
 *      Sets the cursor size and visibility. 
 *  \param visible
 *      If is true, the cursor is visible. Otherwise invisible.
 *  \param size
 *      Must be in the range [1..100]. 
 *  \return
 *      If the function succeeds, the return value is true.
 *      Otherwise false.
 */
BOOL console_cursor_info(BOOL visible, ULONG size);

/** \brief
 *      Sets the font of the text.
 *  \param font
 *      The name of the font defined in the OS. Example: L"Consolas".
 *  \param weight
 *      The weight can range from 100 to 1000, in multiples of 100.
 *  \return
 *      If the function succeeds, the return value is true.
 *      Otherwise false.
*/
BOOL console_set_font(LPCWSTR font, SHORT width, SHORT height, UINT weight);

/**
 *  \brief
 *      Formats the error code into a message and prints it.
 *  \param error_code
 *      Can be obtained using GetLastError().
 *  \return
 *      If the function succeeds, the return value is true.
 *      Otherwise false.       
 */
BOOL console_print_error(ULONG error_code); 

#endif