#include "sqlite3.h"
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

enum Operation { NEW_GAME, CONTINUE_GAME, QUIT_GAME };

void drawTitle();        // Draw title on startup
void drawInstructions(); // Draw instructions on startup
void initDB(sqlite3 *db); // Initialize database

#endif
