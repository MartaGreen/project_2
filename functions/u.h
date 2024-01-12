#ifndef U_H
#define U_H

#include <stdio.h>
#include <stdlib.h>
#include "../types.h"
#include "helper.h"

void u(DATALOGER_DATA** first_record, int records_count) {
  if (*first_record == NULL) {
    printf("Zaznamy neboli nacitane!\n");
    return;
  }

  DATALOGER_DATA* current_record_i = *first_record, * current_record_j = NULL,
    * prev_record_i = NULL, * prev_record_j = NULL;

  while (current_record_i->next != NULL) {
    current_record_j = current_record_i->next;

    while (current_record_j->next != NULL) {
      prev_record_j = current_record_j;
      current_record_j = current_record_j->next;

      char date1[9], time1[5], date2[9], time2[5];
      strcpy(date1, current_record_i->date);
      strcpy(time1, current_record_i->time);
      strcpy(date2, current_record_j->date);
      strcpy(time2, current_record_j->time);

      if (compare_dates(date1, time1, date2, time2)) {
        replace_records(&*first_record, &prev_record_i, &prev_record_j);

        if (prev_record_i == NULL) current_record_i = *first_record;
        else current_record_i = prev_record_i->next;
        current_record_j = prev_record_j->next;
      }
    }

    prev_record_i = current_record_i;
    current_record_i = current_record_i->next;
  }

  DATALOGER_DATA* records_iterator = *first_record;
  int counter = 0;
  while (records_iterator->next != NULL) {
    counter++;
    records_iterator = records_iterator->next;
  }
  counter++;

  if (counter == records_count) printf("Spajany zoznam bol usporiadany.\n");
  else printf("Chyba usporiadania\n");
}

#endif
