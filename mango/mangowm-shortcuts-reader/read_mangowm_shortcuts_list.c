#include <stdio.h>
#include <stdlib.h>

int main() {
  const char *pathConf = "/home/gallahard/.config/mango/mangowm-shortcuts-reader/keybind-docs.txt";
  FILE *file = fopen(pathConf, "r");
  char bufferLine[50];

  if (file == NULL) {
    printf("Failed to open file");
    exit(EXIT_FAILURE);
  }

  while (fgets(bufferLine, 50, file)) {
    printf("%s", bufferLine);
  }

  fclose(file);

  return 0;
}