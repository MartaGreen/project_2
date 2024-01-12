#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "functions/functions.h"

int main() {
  char command;
  DATALOGER_DATA* first_record = NULL;
  int records_count = 0;

  while (command != 'k') {
    scanf("%c", &command);

    if (command == 'n') records_count = n(&first_record, records_count);
    if (command == 'v') v(&first_record, 1, records_count);
    if (command == 'p') records_count = p(&first_record, records_count);
    if (command == 'z') records_count = z(&first_record, records_count);
    if (command == 'u') u(&first_record, records_count);
    if (command == 'r') r(&first_record, records_count);
  }

  if (first_record != NULL) free_linked_list(&first_record);
  return 0;
}
