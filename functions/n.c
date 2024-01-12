#include <stdio.h>
#include <stdlib.h>
#include "../functions.h"
// #include "../types.h"

// int n(DATALOGER_DATA** first_record, int records_count) {
//   FILE* dataloger = fopen("dataloger_V2.txt", "r");
//   if (dataloger == NULL) {
//     printf("Zaznamy neboli nacitane!\n");
//     return 0;
//   }

//   if (records_count) {
//     free_linked_list(&*first_record);
//     records_count = 0;
//   }

//   char file_str[17];
//   DATALOGER_DATA* last_data_link = NULL;

//   while (fscanf(dataloger, "%s", file_str) == 1) {
//     if (!strcmp(file_str, SEPARATOR)) records_count++;
//     add_record(&dataloger, &*first_record, &last_data_link, records_count);
//   }

//   fclose(dataloger);
//   if (records_count) printf("Nacitalo sa %d zaznamov\n", records_count);
//   return records_count;
// }

int n() {
  return 0;
}
