#ifndef Z_H
#define Z_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"

int z(DATALOGER_DATA** first_record, int records_count) {
  if (*first_record == NULL) {
    printf("Zaznamy neboli nacitane!\n");
    return records_count;
  }

  char removed_id[6];
  scanf("%s", removed_id);

  int removed_counter = 0;

  DATALOGER_DATA* current_record = *first_record, * prev_record = NULL;
  char id[6];
  while (current_record->next != NULL) {
    sprintf(id, "%c%d%c", current_record->id.start, current_record->id.num_part, current_record->id.end);

    if (prev_record == NULL && !strcmp(id, removed_id)) {
      (*first_record) = current_record->next;
      free(current_record);
      current_record = *first_record;
      printf("Zaznam pre ID: %s bol vymazany.\n", removed_id);
      removed_counter++;
      continue;
    }

    if (!strcmp(id, removed_id)) {
      prev_record->next = current_record->next;
      free(current_record);
      current_record = prev_record->next;
      printf("Zaznam pre ID: %s bol vymazany.\n", removed_id);
      removed_counter++;
      continue;
    }

    prev_record = current_record;
    current_record = current_record->next;
  }

  sprintf(id, "%c%d%c", current_record->id.start, current_record->id.num_part, current_record->id.end);
  if (!strcmp(id, removed_id)) {
    prev_record->next = NULL;
    free(current_record);
    printf("Zaznam pre ID: %s bol vymazany.\n", removed_id);
    removed_counter++;
  }

  return records_count - removed_counter;
}

#endif
