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
void p(DATALOGER_DATA** first_record, int records_count) {
  int p;

  scanf("%d", &p);

  DATALOGER_DATA* prev_record = *first_record, * next_record;
  for (int i = 0; i < p - 2; i++) {
    prev_record = prev_record->next;
  }
  next_record = prev_record->next;

  char id[6], pozition[17], type[3], time[5], date[9];
  double value;
  scanf("%s %s %s %lf %s %s", id, pozition, type, &value, time, date);
  printf("%s %s %s %lf %s %s\n", id, pozition, type, value, time, date);

  DATALOGER_DATA* new_record = create_record(records_count, id, pozition, type, value, time, date);

  new_record->next = next_record;
  prev_record->next = new_record;
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
  }
  return 0;
}
