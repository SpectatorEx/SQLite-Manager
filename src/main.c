#include <stdio.h>

#include "sqlite3.h"
#include "cengine32.h"

#include "ui/frame.h"
#include "ui/menu.h"

#include "system/types.h"

sqlite3 *database;
ui_frame frame_menu, frame_info, frame_input, frame_about;

extern const char *logo[];

static void database_menu(void);
static void database_open(void);
static void database_delete(void);
static void database_close(void);
static void query_execute(void);

static void display_query(const char *sql);
static void ui_draw(void);

extern void display_logo(ui_frame *frame, const char **logo);
extern int print_table(sqlite3 *database, const char *sql);
extern char* file_read(const char *filename);

int main(void) {
    console_window_title("SQLite Manager");
    console_cursor_info(FALSE, 1);

    system("chcp 65001");

    ui_option options[] = {
        { { 2, 2 }, "Database.", "Database management." },
        { { 2, 3 }, "Queries.", "Execute SQL query for the current database." },
        { { 2, 4 }, "Exit.", NULL }
    };

    ui_menu menu = { 0, 3, options };

    frame_menu = (ui_frame) { "Menu", { 0, 0, 40, 15 } };
    frame_info = (ui_frame) { "Info", { 0, 15, 40, 15 } };
    frame_input = (ui_frame) { "Input", { 40, 25, 80, 5 } };
    frame_about = (ui_frame) { "About", { 40, 0, 80, 25 } };

    ui_draw();

    ui_frame_print(&frame_info, "Welcome to \"SQLite Manager\"! "
        "Use the Enter key and the arrows to select the options.");

    while (TRUE) {
        ui_menu_draw(&menu);

        int index = menu.index;
        ui_frame_print(&frame_info, menu.options[index].desc);

        switch (index) {
            case 0:
                database_menu();
                break;
            case 1:
                if (database == NULL) {
                    ui_frame_print(&frame_info, "Database isn't open!");
                    break;
                }

                query_execute();
                break;
            case 2:
                sqlite3_close(database);
                exit(EXIT_SUCCESS);

                break;
        }
    }

    return 0;
}

static void database_menu(void) {
    bool update = TRUE;

    ui_option options[] = {
        { { 2, 2 }, "Open database.", "Open or create a database." },
        { { 2, 3 }, "Delete database.", NULL },
        { { 2, 4 }, "Close database.",  NULL },
        { { 2, 5 }, "Back.", NULL }
    };

    ui_menu menu = { 0, 4, options };
    ui_frame_clear(&frame_menu);

    while (update) {
        ui_menu_draw(&menu);

        int index = menu.index;
        ui_frame_print(&frame_info, menu.options[index].desc);

        switch (index) {
            case 0:
                if (database != NULL) {
                    ui_frame_print(&frame_info, "Database is already open!");
                    break;
                }

                database_open();
                break;
            case 1:
                database_delete();
                break;
            case 2:
                if (database == NULL) {
                    ui_frame_print(&frame_info, "Database isn't open!");
                    break;
                }

                database_close();
                break;
            case 3:
                update = FALSE;
                break;
        }
    }

    ui_frame_clear(&frame_menu);
}

static void database_open(void) {
    char filename[50] = "database/";
    char buffer[35];

    ui_frame_input(&frame_input, "Enter a name:", buffer, 35);
    ui_frame_clear(&frame_input);

    strcat(filename, buffer);

    int status = sqlite3_open(filename, &database);

    if (status != SQLITE_OK) {
        ui_frame_print(&frame_info, sqlite3_errmsg(database));
        sqlite3_close(database);

        database = NULL;

        return;
    }

    ui_frame_print(&frame_info, "Database has opened!");
}

static void database_delete(void) {
    char filename[50] = "database\\";
    char buffer[35];

    ui_frame_input(&frame_input, "Enter a name:", buffer, 35);
    ui_frame_clear(&frame_input);

    strcat(filename, buffer);

    int error = DeleteFile(filename);

    if (error == 0) {
        ui_frame_print(&frame_info, "Database is in use or doesn't exist.");
        return;
    }

    ui_frame_print(&frame_info, "Database has been deleted!");
}

static void database_close(void) {
    ui_frame_print(&frame_info, "Database is closed!");
    sqlite3_close(database);

    database = NULL;
}

static void query_execute(void) {
    char filename[50] = "queries/";
    char buffer[35];

    ui_frame_input(&frame_input, "SQL query:", buffer, 35);
    ui_frame_clear(&frame_input);

    strcat(filename, buffer);

    char *sql = file_read(filename);

    if (sql == NULL) {
        ui_frame_print(&frame_info, "File is empty or doesn't exist!");
        return;
    }

    char *error_msg = NULL;
    bool exec_status = sqlite3_exec(database, sql, NULL, NULL, &error_msg);

    if (exec_status != SQLITE_OK) {
        ui_frame_print(&frame_info, error_msg);
    } else {
        display_query(sql);
        ui_frame_print(&frame_info, "SQL query has been executed!");
    }

    sqlite3_free(error_msg);
    free(sql);
}

static void display_query(const char *sql) {
    int status = print_table(database, sql);

    if (status == SQLITE_OK) {
        system("echo: && echo: && pause");
        ui_draw();
    }
}

static void ui_draw(void) { 
    ui_frame_draw(&frame_menu);
    ui_frame_draw(&frame_info);
    ui_frame_draw(&frame_input);
    ui_frame_draw(&frame_about);

    display_logo(&frame_about, logo);
}
