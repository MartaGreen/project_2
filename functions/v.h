#ifndef V_H
#define V_H

#include <stdio.h>
#include <stdlib.h>
#include "../types.h"

void v(DATALOGER_DATA** first_record, int counter, int records_count) {
  if (!records_count) return;

  DATALOGER_DATA* current_record = *first_record;
  printf("%d:\n", counter);
  printf("ID: %c%d%c\t%s\t%g\n", current_record->id.start, current_record->id.num_part, current_record->id.end, current_record->type, current_record->value);
  printf("Poz: %+g\t%+g\n", current_record->pozition.latitude, current_record->pozition.longitude);
  printf("DaC: %s\t%s\n", current_record->date, current_record->time);

  if ((*first_record)->next == NULL) return;
  counter++;
  v(&current_record->next, counter, records_count);
}

#endif
