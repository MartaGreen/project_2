#ifndef TYPES_H
#define TYPES_H

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

char SEPARATOR[] = "$$$";

#endif // TYPES_H
