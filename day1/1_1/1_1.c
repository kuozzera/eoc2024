#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int *tab1 = NULL;
  int *tab2 = NULL;
  int count = 0;
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int dist = 0;

  fp = fopen("1_1.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1) {
    char *token = strtok(line, " ");
    // loop through the string to extract all other tokens
    while (token != NULL) {
      if (count % 2 == 0) {
        tab1 = (int *)realloc(tab1, (count / 2 + 1) * sizeof(int));
        if (tab1 == NULL) {
          perror("Realloc failed");
          exit(EXIT_FAILURE);
        }
        tab1[count / 2] = atoi(token);
      } else {
        tab2 = (int *)realloc(tab2, (count / 2 + 1) * sizeof(int));
        if (tab2 == NULL) {
          perror("Realloc failed");
          exit(EXIT_FAILURE);
        }
        tab2[count / 2] = atoi(token);
      }
      count++;
      token = strtok(NULL, " ");
    }
  }

  fclose(fp);
  if (line)
    free(line);

  int originalCount = count / 2;
  int pos1, pos2;
  long int min1 = 0;
  long int min2 = 0;
  for (int i = 1; i <= originalCount; i++) {
    min1 = tab1[0];
    pos1 = 0;
    min2 = tab2[0];
    pos2 = 0;

    for (int y = 0; y <= originalCount - i; y++) {
      if (tab1[y] < min1) {
        // printf("min1:%d",min1);
        min1 = tab1[y];
        pos1 = y;
      }
      if (tab2[y] < min2) {
        min2 = tab2[y];
        pos2 = y;
      }
    }
    dist += abs(min1 - min2);
    for (int h = pos1; h < originalCount - 1; h++)
      tab1[h] = tab1[h + 1];
    for (int h = pos2; h < originalCount - 1; h++)
      tab2[h] = tab2[h + 1];

    tab1 = (int *)realloc(tab1, (originalCount - 1) * sizeof(int));
    if (tab1 == NULL && originalCount - i - 1 > 0) {
      perror("Realloc failed");
      exit(EXIT_FAILURE);
    }
    tab2 = (int *)realloc(tab2, (originalCount - 1) * sizeof(int));
    if (tab2 == NULL && originalCount - i - 1 > 0) {
      perror("Realloc failed");
      exit(EXIT_FAILURE);
    }
    count -= 2;
  }

  printf("dist is : %d", dist);
  free(tab1);
  free(tab2);
  exit(EXIT_SUCCESS);
}
