#ifndef MENU_H
#define MENU_H

#include "system/types.h"

typedef struct {
    point pos;
    char *name;
    const char *desc;
} ui_option;

typedef struct {
    uint16 index, length; 
    ui_option *options;
} ui_menu;

void ui_menu_draw(ui_menu *menu);

#endif