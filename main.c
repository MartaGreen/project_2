#include <stdio.h>
#include <stdlib.h>

int n() {
  FILE* dataloger = fopen("dataloger_V2.txt", "r");
  if (dataloger == NULL) {
    printf("Zaznamy neboli nacitane!\n");
    return 1;
  }

  return 0;
}

int main() {
  char command;

  while (command != 'k') {
    command = getchar();

    if (command == 'n') n();
  }
  return 0;
}
