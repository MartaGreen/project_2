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

int n() {
  FILE* dataloger = fopen("dataloger_V2.txt", "r");
  if (dataloger == NULL) {
    printf("Zaznamy neboli nacitane!\n");
    return 1;
  }

  char file_str[17];
  int records_count = 0, counter = 0;
  DATALOGER_DATA* first_data_link = NULL, * last_data_link = NULL;

  while (fscanf(dataloger, "%s", file_str) == 1) {
    if (!strcmp(file_str, SEPARATOR)) {
      records_count++;
      counter = 0;
    }

    create_record(&dataloger, &first_data_link, &last_data_link, records_count);
    printf("record %d was crwated\n", records_count);
  }

  fclose(dataloger);
  printf("records_count: %d\n", records_count);
  printf("first record data: %c%d%c %g\n", first_data_link->id.start, first_data_link->id.num_part, first_data_link->id.end, first_data_link->value);
  printf("next elem: %g %g\n", first_data_link->next->pozition.latitude, first_data_link->next->pozition.longitude);

  return 0;
}

int main() {
  char command;

  while (command != 'k') {
    scanf("%c", &command);

    if (command == 'n') n();
  }
  return 0;
}
