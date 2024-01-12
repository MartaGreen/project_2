#ifndef R_H
#define R_H

#include <stdio.h>
#include <stdlib.h>
#include "../types.h"
#include "helper.h"

void r(DATALOGER_DATA** first_record, int records_count) {
  if (*first_record == NULL) {
    printf("Zaznamy neboli nacitane!\n");
    return;
  }

  int pos1, pos2;
  scanf("%d %d", &pos1, &pos2);

  if (pos1 > records_count || pos2 > records_count) return;

  if (pos1 == pos2) return;

  DATALOGER_DATA* record_1_prev = NULL, * record_2_prev = NULL,
    * current_record = *first_record;
  int counter1 = 1, counter2 = 1;
  int found_first_record = 0, found_second_record = 0;

  if (pos1 > pos2) {
    int pos_changer = pos1;
    pos1 = pos2;
    pos2 = pos_changer;
  }

  while (current_record->next != NULL && (!found_first_record || !found_second_record)) {
    if (!found_first_record && pos1 == 1) found_first_record = 1;
    if (!found_first_record && (counter1 == pos1 - 1)) {
      record_1_prev = current_record;
      found_first_record = 1;
    }
    if (!found_second_record && pos2 == 1) found_second_record = 1;
    if (!found_second_record && (counter2 == pos2 - 1)) {
      record_2_prev = current_record;
      found_second_record = 1;
    }

    counter1 += !found_first_record ? 1 : 0;
    counter2 += !found_second_record ? 1 : 0;
    current_record = current_record->next;
  }

  replace_records(&*first_record, &record_1_prev, &record_2_prev);
}

#endif
