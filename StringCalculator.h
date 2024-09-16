#include "stdlib.h"
#include "string.h"
#include "ctype.h"

/* Function Prototypes */
int calculateStringSum(const char *inputString);
int isEmptyString(const char *inputString);
void replaceNewLineDelimiterWithCommaDelimiter(char *tempInputString);
void addNumbersFromInputString(char *inputString, int* sumString);
void removeNonDigitCharactersFromToken(char *token);
void deleteCharFromStringByIndex(char *inputString, int charIndex);
void removeNumbersGreaterThanThousand(char *token);

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
    removeNonDigitCharactersFromToken(token);
    removeNumbersGreaterThanThousand(token);
    (*sumString) += atoi(token);
    token = strtok(NULL,",");
  }
}

/* Function Description: delete the character at the given index from the given string */
/* Parameters:
      inputString - string from which a character is to be deleted
      charIndex - index of the character which is to be deleted
*/
void deleteCharFromStringByIndex(char *inputString, int charIndex) {        
    int len = strlen(inputString); /* len - length of the input string */
    int i;
    for(i = charIndex; i < len-1; ++i) {
        inputString[i] = inputString[i+1];
    }
    inputString[i] = '\0';
}

void removeNumbersGreaterThanThousand(char *token) {
  if(atoi(token) > 1000) {
    strcpy(token,"0");
  }
}

void removeNonDigitCharactersFromToken(char *token) {
  int i = 0;
  while(token[i] != '\0') {
    if(!isdigit(token[i])) {
      deleteCharFromStringByIndex(token,i);
    } else {
        ++i;
    }
  }
}

void replaceNewLineDelimiterWithCommaDelimiter(char *tempInputString) {
  for(int i = 0; tempInputString[i] != '\0'; ++i) {
    if(tempInputString[i] == '\n') {
      tempInputString[i] = ',';
    }
  }
}
