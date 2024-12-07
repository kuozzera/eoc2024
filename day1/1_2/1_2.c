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

  fp = fopen("1_2.txt", "r");
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


  for(int i = 0;i<count/2;i++){
    for(int y = 0;y<count/2;y++){
      if(tab1[i] == tab2[y]) dist+=tab1[i];
    }
  }  





  printf("dist is : %d", dist);
  free(tab1);
  free(tab2);
  exit(EXIT_SUCCESS);
}