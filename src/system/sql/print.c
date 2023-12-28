#include <stdio.h>
#include <stdlib.h>

#include "sqlite3.h"
#include "cengine32.h"

#include "system/types.h"

static void get_column_length(sqlite3 *db, const char *sql, int *cols_length);
static void print_column_names(sqlite3_stmt *stmt, int *cols_length);

static int authorizer_callback(void *data, int code, const char *str1, 
    const char *str2, const char *db_name, const char *trigger);

int print_table(sqlite3 *db, const char *sql) {
    sqlite3_stmt *stmt = NULL;
    sqlite3_set_authorizer(db, &authorizer_callback, NULL);
    
    int status = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (status != SQLITE_OK) {
        sqlite3_set_authorizer(db, NULL, NULL);
        return status;
    }

    system("cls");

    int cols_count = sqlite3_column_count(stmt);
    int cols_length[cols_count];
    int length;

    memset(cols_length, 0, sizeof(cols_length));
    get_column_length(db, sql, cols_length);

    if (cols_length[0] == 0) {
        puts("Table can't be printed because it is empty!");
        return status;
    }

    print_column_names(stmt, cols_length);

    for (int i = 0; sqlite3_step(stmt) == SQLITE_ROW; i++) {
        console_cursor_pos(0, i + 2);
        length = 0;

        for (int j = 0; j < cols_count; j++) {
            length += cols_length[j];
            printf("%s", sqlite3_column_text(stmt, j));

            console_cursor_pos(length, i + 2);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_set_authorizer(db, NULL, NULL);

    return status;
}

static void print_column_names(sqlite3_stmt *stmt, int *cols_length) {
    int cols_count = sqlite3_column_count(stmt);
    int length = 0;

    for (int i = 0; i < cols_count; i++) {
        const char *name = sqlite3_column_name(stmt, i);
        length += cols_length[i];

        puts(name);
        console_cursor_pos(length, 0);
    }
}

static void get_column_length(sqlite3 *db, const char *sql, int *cols_length) {
    sqlite3_stmt *stmt = NULL;
    int status = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (status != SQLITE_OK) {
        return;
    }

    int cols_count = sqlite3_column_count(stmt);
    int length = 0, name_length = 0;

    for (int i = 0; sqlite3_step(stmt) == SQLITE_ROW; i++) {
        for (int j = 0; j < cols_count; j++) {
            const uint8 *text = sqlite3_column_text(stmt, j);
            const char *name = sqlite3_column_name(stmt, j);

            name_length = strlen(name);
            length = text != NULL ? strlen((const char*)text) + 1 : 7;

            if (cols_length[j] < length) { 
                cols_length[j] = length; 
            } 

            if (cols_length[j] <= name_length) {
                cols_length[j] = name_length + 1;
            }
        }
    }

    sqlite3_finalize(stmt);
}

static int authorizer_callback(void *data, int code, const char *str1, 
    const char *str2, const char *db_name, const char *trigger) {
    
    if (code != SQLITE_SELECT && code != SQLITE_READ) {
        return SQLITE_DENY;
    }

    return SQLITE_OK;
}