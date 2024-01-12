#ifndef P_H
#define P_H

#include <stdio.h>
#include <stdlib.h>
#include "../types.h"
#include "helper.h"

// B151a +48.1255+19.4514 RD 145.25 1015 20231010
int p(DATALOGER_DATA** first_record, int records_count) {
  int p;

  scanf("%d", &p);

  if (p < 0) return records_count;
  records_count++;
  if (p > records_count) {
    p = records_count;
  }

  char id[6], pozition[17], type[3], time[5], date[9];
  double value;
  scanf("%s %s %s %lf %s %s", id, pozition, type, &value, time, date);

  DATALOGER_DATA* new_record = create_record(records_count, id, pozition, type, value, time, date);
  if (*first_record == NULL) {
    *first_record = new_record;
    return 1;
  }

  if (p == 1) {
    new_record->next = (*first_record);
    (*first_record) = new_record;
    return records_count;
  }

  DATALOGER_DATA* prev_record = *first_record, * next_record;
  for (int i = 1; i < p - 1; i++) {
    prev_record = prev_record->next;
  }
  next_record = prev_record->next;

  new_record->next = next_record;
  prev_record->next = new_record;

  return records_count;
}

#endif
