#include "utils.h"
#include "sqlite3.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/*
 * --------------------
 * Draw Title
 * --------------------
 */
void drawTitle() {
  system("clear");
  printf("\n\n");
  printf(
      "\t ██    ██ ███    ██ ████████ ██ ████████ ██      ███████ ██████ \n");
  printf(
      "\t ██    ██ ████   ██    ██    ██    ██    ██      ██      ██   ██ \n");
  printf(
      "\t ██    ██ ██ ██  ██    ██    ██    ██    ██      █████   ██   ██ \n");
  printf(
      "\t ██    ██ ██  ██ ██    ██    ██    ██    ██      ██      ██   ██ \n");
  printf(
      "\t  ██████  ██   ████    ██    ██    ██    ███████ ███████ ██████ \n");
  printf("\t\t\n\n");
}

/*
 * --------------------
 * Set Noncanonical Mode
 * --------------------
 */
void set_noncanonical_mode() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

/*
 * --------------------
 * Draw Instructions
 * --------------------
 */
void drawInstructions() {
  printf("\n\n");
  printf("\t\t\t\t n - New Game \n");
  printf("\t\t\t\t c - Continue Game \n");
  printf("\t\t\t\t q - Quit Game \n");
  printf("\n\n");

  set_noncanonical_mode();
  char ch;
  read(STDIN_FILENO, &ch, 1); // Read a single character

  if (ch == 'n') {
    system("clear");
    printf("Game Started");
  } else if (ch == 'c') {
    printf("Select saved games");
  } else if (ch == 'q') {
    system("clear");
    printf("Good Bye see you later");
    exit(1);
  }
}

/*
 * --------------------
 * Log In
 * --------------------
 */
int login(sqlite3 *db, int *rc) {
  char username[100];

  system("clear");
  printf("\n\n");
  printf("\t .____                   .___       \n");
  printf("\t|    |    ____   ____   |   | ____  \n");
  printf("\t|    |   /  _ \\ / ___\\  |   |/    \\ \n");
  printf("\t|    |__(  <_> ) /_/  > |   |   |  \\ \n");
  printf("\t|_______ \\____/\\___  /  |___|___|  / \n");
  printf("\t        \\/    /_____/            \\/ \n");
  printf("\n\n");
  printf("\n\t Enter your username:  ");
  fgets(username, sizeof(username), stdin);
  printf("%s", username);

  // Prepare SQL statement to insert user
  sqlite3_stmt *stmt;
  const char *sql = "INSERT INTO users (name) VALUES (?)";
  *rc = sqlite3_prepare(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  // Bind user data to placeholders
  sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

  // Execute the insertion
  *rc = sqlite3_step(stmt);
  if (*rc != SQLITE_DONE) {
    fprintf(stderr, "Error inserting user: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt); // Clean up prepared statement even on error
    sqlite3_close(db);
    return 1;
  }

  // Finalize prepared statement (important for memory cleanup)
  sqlite3_finalize(stmt);
  return 0;
}

/*
 * --------------------
 * Initialize Database
 * --------------------
 */
void initDB(sqlite3 *db) {

  int rc = sqlite3_open("database.db", &db);
  if (rc != SQLITE_OK) {
    printf("Cannot open database");
    exit(1);
  }

  char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY "
              "AUTOINCREMENT, name TEXT)";
  rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
  if (rc != SQLITE_OK) {
    printf("Operation not completed");
    exit(1);
  }

  int logged = login(db, &rc);
}
