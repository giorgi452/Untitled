#include "sqlite3.h"
#include "utils/utils.h"

int main(int argc, char **argv) {
  // --------------------
  // sqlite3 *db; // Database connection pointer

  /*
   * --------------------
   * Initialize Database
   * --------------------
   */
  // initDB(db);

  /*
   * --------------------
   * Draw Title
   * --------------------
   */
  drawTitle();

  /*
   * --------------------
   * Draw Instructions
   * --------------------
   */
  drawInstructions();

  // sqlite3_close(db); // Close Database

  /*
   * --------------------
   * End Process with status 0
   * --------------------
   */
  return 0;
}
