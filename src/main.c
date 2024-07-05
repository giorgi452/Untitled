#include "sqlite3.h"
#include "utils/utils.h"

int main(int argc, char **argv) {
  sqlite3 *db; // Database connection pointer
  initDB(db);
  drawTitle();
  drawInstructions();
  return 0;
}
