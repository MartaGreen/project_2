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

void create_record(FILE** dataloger, DATALOGER_DATA** first_record_link, DATALOGER_DATA** last_record_link, int records_count) {
  DATALOGER_DATA* new_record = (DATALOGER_DATA*)malloc(sizeof(DATALOGER_DATA));
  char file_str[17];

  fscanf(*dataloger, "%s", file_str);
  char id_start, id_end;
  int id_num;
  sscanf(file_str, "%c%3d%c", &id_start, &id_num, &id_end);
  new_record->id.start = id_start;
  new_record->id.num_part = id_num;
  new_record->id.end = id_end;

  fscanf(*dataloger, "%s", file_str);
  double latitude, longitude;
  sscanf(file_str, "%8lf%8lf", &latitude, &longitude);
  new_record->pozition.latitude = latitude;
  new_record->pozition.longitude = longitude;

  fscanf(*dataloger, "%s", file_str);
  strcpy(new_record->type, file_str);

  fscanf(*dataloger, "%s", file_str);
  new_record->value = atof(file_str);

  fscanf(*dataloger, "%s", file_str);
  strcpy(new_record->time, file_str);

  fscanf(*dataloger, "%s", file_str);
  strcpy(new_record->date, file_str);

  new_record->next = NULL;

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
    create_record(&dataloger, &*first_record, &last_data_link, records_count);
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

int main() {
  char command;
  DATALOGER_DATA* first_record = NULL;
  int records_count = 0;

  while (command != 'k') {
    scanf("%c", &command);

    if (command == 'n') records_count = n(&first_record, records_count);
    if (command == 'v') v(&first_record, 1, records_count);
  }
  return 0;
}
