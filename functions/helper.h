#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"

// LINKEDLIST HELPER
void free_linked_list(DATALOGER_DATA** first_record) {
  DATALOGER_DATA* next_link = (*first_record)->next;
  if (next_link == NULL) {
    *first_record = NULL;
    return;
  }

  free(*first_record);
  free_linked_list(&next_link);
}

// RECORDS HELPER
DATALOGER_DATA* create_record(int records_count, char id[6], char pozition[17], char type[3], double value, char time[5], char date[9]) {
  DATALOGER_DATA* new_record = (DATALOGER_DATA*)malloc(sizeof(DATALOGER_DATA));

  char id_start, id_end;
  int id_num;
  sscanf(id, "%c%3d%c", &id_start, &id_num, &id_end);
  new_record->id.start = id_start;
  new_record->id.num_part = id_num;
  new_record->id.end = id_end;

  double latitude, longitude;
  sscanf(pozition, "%8lf%8lf", &latitude, &longitude);
  new_record->pozition.latitude = latitude;
  new_record->pozition.longitude = longitude;

  strcpy(new_record->type, type);
  new_record->value = value;
  strcpy(new_record->time, time);
  strcpy(new_record->date, date);
  new_record->next = NULL;

  return new_record;
}

void add_record(FILE** dataloger, DATALOGER_DATA** first_record_link, DATALOGER_DATA** last_record_link, int records_count) {
  char id[6], pozition[17], type[3], time[5], date[9];
  double value;
  fscanf(*dataloger, "%s", id);
  fscanf(*dataloger, "%s", pozition);
  fscanf(*dataloger, "%s", type);
  fscanf(*dataloger, "%lf", &value);
  fscanf(*dataloger, "%s", time);
  fscanf(*dataloger, "%s", date);

  DATALOGER_DATA* new_record = create_record(records_count, id, pozition, type, value, time, date);

  if (records_count == 1) {
    *first_record_link = new_record;
    *last_record_link = new_record;
    return;
  }

  (*last_record_link)->next = new_record;
  *last_record_link = new_record;
}

void replace_records(DATALOGER_DATA** first_record, DATALOGER_DATA** record_1_prev, DATALOGER_DATA** record_2_prev) {
  DATALOGER_DATA* record_1 = *record_1_prev == NULL ? *first_record : (*record_1_prev)->next,
    * record_2 = (*record_2_prev)->next,
    * record_2_next = record_2->next;

  if (*record_1_prev != NULL) {
    (*record_1_prev)->next = record_2;
  }
  else {
    *first_record = record_2;
  }
  if (record_1->next != record_2) {
    record_2->next = record_1->next;
    (*record_2_prev)->next = record_1;
  }
  else {
    record_2->next = record_1;
  }
  record_1->next = record_2_next;
}

// DATES HELPER
//return 1 if date1 > date2
//return 0 if date1 <= date2
int compare_dates(char date1[9], char time[5], char date2[9], char time2[5]) {
  int year1, month1, day1;
  int hour1, minutes1;

  sscanf(date1, "%4d%2d%2d", &year1, &month1, &day1);
  sscanf(time, "%2d%2d", &hour1, &minutes1);

  int year2, month2, day2;
  int hour2, minutes2;

  sscanf(date2, "%4d%2d%2d", &year2, &month2, &day2);
  sscanf(time2, "%2d%2d", &hour2, &minutes2);

  if (year1 > year2) return 1;
  if (year1 < year2) return 0;
  if (month1 > month2) return 1;
  if (month1 < month2) return 0;
  if (day1 > day2) return 1;
  if (day1 < day2) return 0;
  if (hour1 > hour2) return 1;
  if (hour1 < hour2) return 0;
  if (minutes1 > minutes2) return 1;

  return 0;
}

#endif
