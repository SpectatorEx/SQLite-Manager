#include <stdio.h>
#include <conio.h>

#include "cengine32.h"
#include "ui/menu.h"

void ui_menu_draw(ui_menu *menu) {
    int key_down = 0;

    while (key_down != KEY_ENTER) {
        for (uint16 i = 0; i < menu->length; i++) {
            if (menu->index == i) {
                console_set_color(BCOLOR_WHITE);
            } else {
                console_set_color(FCOLOR_GRAY);
            }
            
            ui_option *option = &menu->options[i];

            console_cursor_pos(option->pos.x, option->pos.y);
            printf("[%d] - %s", i, option->name);
        }

        key_down = getch();

        if (key_down == 0 || key_down == 0xE0) {
            key_down = getch();
        }

        if (key_down == KEY_UP && menu->index > 0) {
            menu->index--;
        } else if (key_down == KEY_DOWN && menu->index < menu->length - 1) {
            menu->index++;
        }
    }

    console_set_color(FCOLOR_GRAY);
}
