#include "stdlib.h"
#include "string.h"

/* Function Prototypes */
int calculateStringSum(const char *inputString);
int isEmptyString(const char *inputString);
void replaceNewLineDelimiterWithCommaDelimiter(char *tempInputString);
void addNumbersFromInputString(char *inputString, int* sumString);

int calculateStringSum(const char *inputString) {
  int stringSum = 0;
  char tempInputString[strlen(inputString)];
  strcpy(tempInputString, inputString);

  if(!isEmptyString(inputString)) {
    replaceNewLineDelimiterWithCommaDelimiter(tempInputString);
    addNumbersFromInputString(tempInputString, &stringSum);
  }

  return stringSum;
}

int isEmptyString(const char *inputString) {
  return (strlen(inputString) == 0);
}

void addNumbersFromInputString(char *inputString, int* sumString) {
  char* token = strtok(inputString,",");
  while (token != NULL) {
    (*sumString) += atoi(token);
    token = strtok(NULL,",");
  }
}

void replaceNewLineDelimiterWithCommaDelimiter(char *tempInputString) {
  for(int i = 0; tempInputString[i] != '\0'; ++i) {
    if(tempInputString[i] == '\n') {
      tempInputString[i] = ',';
    }
  }
}
