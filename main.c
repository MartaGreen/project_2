#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct id_mer_module {
  char start;
  int num_part;
  char end;
} ID_MER_MODULE;

typedef struct pozition_mer_module {
  double latitude;
  double longitude;
} POSITION_MER_MODULE;

typedef struct dataloger_data {
  ID_MER_MODULE id;
  POSITION_MER_MODULE pozition;
  char type[3];
  double value;
  char time[5];
  char date[9];
  struct dataloger_data* next;
} DATALOGER_DATA;

char SEPARATOR[4] = "$$$\0";

void free_linked_list(DATALOGER_DATA** first_record) {
  // printf("deleted record id: %c%d%c\n", (*first_record)->id.start, (*first_record)->id.num_part, (*first_record)->id.end);
  DATALOGER_DATA* next_link = (*first_record)->next;
  if (next_link == NULL) return;

  free(*first_record);
  free_linked_list(&next_link);
}

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

int n(DATALOGER_DATA** first_record, int records_count) {
  FILE* dataloger = fopen("dataloger_V2.txt", "r");
  if (dataloger == NULL) {
    printf("Zaznamy neboli nacitane!\n");
    return 0;
  }

  if (records_count) {
    free_linked_list(&*first_record);
    records_count = 0;
  }

  char file_str[17];
  DATALOGER_DATA* last_data_link = NULL;

  while (fscanf(dataloger, "%s", file_str) == 1) {
    if (!strcmp(file_str, SEPARATOR)) records_count++;
    add_record(&dataloger, &*first_record, &last_data_link, records_count);
  }

  fclose(dataloger);
  if (records_count) printf("Nacitalo sa %d zaznamov\n", records_count);
  return records_count;
}

void v(DATALOGER_DATA** first_record, int counter, int records_count) {
  if (!records_count) return;

  DATALOGER_DATA* current_record = *first_record;
  printf("%d:\n", counter);
  printf("ID: %c%d%c\t%s\t%g\n", current_record->id.start, current_record->id.num_part, current_record->id.end, current_record->type, current_record->value);
  printf("Poz: %g\t%g\n", current_record->pozition.latitude, current_record->pozition.longitude);
  printf("DaC: %s\t%s\n", current_record->date, current_record->time);

  if ((*first_record)->next == NULL) return;
  counter++;
  v(&current_record->next, counter, records_count);
}

//B151a +481255+194514 RD 145.25 1015 20231010
int p(DATALOGER_DATA** first_record, int records_count) {
  int p;

  scanf("%d", &p);

  if (p - records_count > 1) return records_count;

  char id[6], pozition[17], type[3], time[5], date[9];
  double value;
  scanf("%s %s %s %lf %s %s", id, pozition, type, &value, time, date);

  DATALOGER_DATA* new_record = create_record(records_count, id, pozition, type, value, time, date);
  records_count++;

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

void z(DATALOGER_DATA** first_record) {
  char removed_id[6];
  scanf("%s", removed_id);

  DATALOGER_DATA* current_record = *first_record, * prev_record = NULL;
  while (current_record->next != NULL) {
    char id[6];
    sprintf(id, "%c%d%c", current_record->id.start, current_record->id.num_part, current_record->id.end);

    if (prev_record == NULL && !strcmp(id, removed_id)) {
      current_record = current_record->next;
      (*first_record) = current_record;
      continue;
    }

    if (!strcmp(id, removed_id)) {
      prev_record->next = current_record->next;
      free(current_record);
      current_record = prev_record->next;
      continue;
    }

    prev_record = current_record;
    current_record = current_record->next;
  }
}

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
  else if (month1 > month2) return 1;
  else if (day1 > day2) return 1;
  else if (hour1 > hour2) return 1;
  else if (minutes1 > minutes2) return 1;

  return 0;
}

void replace_records(DATALOGER_DATA** first_record, int pos1, int pos2) {
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

  DATALOGER_DATA* record_1 = record_1_prev == NULL ? *first_record : record_1_prev->next,
    * record_2 = record_2_prev->next,
    * record_2_next = record_2->next;
  printf("%g\n", record_1->value);

  if (record_1_prev != NULL) {
    record_1_prev->next = record_2;
  }
  else {
    *first_record = record_2;
  }
  record_2->next = record_1->next;
  record_2_prev->next = record_1;
  record_1->next = record_2_next;

  DATALOGER_DATA* record_i = *first_record;
  while (record_i->next != NULL) {
    printf("%c%d%c %g\n", record_i->id.start, record_i->id.num_part, record_i->id.end, record_i->value);
    record_i = record_i->next;
  }
}

void r(DATALOGER_DATA** first_record, int records_count) {
  int pos1, pos2;
  scanf("%d %d", &pos1, &pos2);

  if (pos1 > records_count || pos2 > records_count) return;

  replace_records(&*first_record, pos1, pos2);
}

void u(DATALOGER_DATA** first_record) {
  DATALOGER_DATA* current_record_i = *first_record, * current_record_j = NULL,
    * prev_record_i = NULL, * prev_record_j = NULL, * save_next = NULL;

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
        save_next = current_record_j->next;
        if (prev_record_i != NULL) {
          prev_record_i->next = current_record_j;
        }
        current_record_j->next = current_record_i->next;
        current_record_i->next->next = prev_record_j;
        prev_record_j->next = current_record_i;
        current_record_i->next = save_next;

        DATALOGER_DATA* changer = current_record_i;
        current_record_i = current_record_j;
        current_record_j = changer;
      }
    }

    prev_record_i = current_record_i;
    current_record_i = current_record_i->next;
  }
}

int main() {
  char command;
  DATALOGER_DATA* first_record = NULL;
  int records_count = 0;

  while (command != 'k') {
    scanf("%c", &command);

    if (command == 'n') records_count = n(&first_record, records_count);
    if (command == 'v') v(&first_record, 1, records_count);
    if (command == 'p') p(&first_record, records_count);
    if (command == 'z') z(&first_record);
    if (command == 'u') u(&first_record);
    if (command == 'r') r(&first_record, records_count);
  }
  return 0;
}
