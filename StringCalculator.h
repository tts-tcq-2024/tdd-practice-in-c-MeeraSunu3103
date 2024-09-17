#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "ctype.h"

/* Function Prototypes */
int calculateStringSum(const char *inputString);
int isEmptyString(const char *inputString);
void replaceNewLineDelimiterWithCommaDelimiter(char *tempInputString);
void addNumbersFromInputString(char *inputString, int* sumString);
void removeNonDigitCharactersFromToken(char *token);
void deleteCharFromStringByIndex(char *inputString, int charIndex);
void removeNumbersGreaterThanThousand(char *token);
void checkAndReplaceCustomDelimiterWithCommaDelimiter(char *inputString);
void replaceCustomDelimiterWithCommaDelimiter(char *inputString, char* customDelimiter);
void checkForNegativeNumbersInInputString(char *inputString);
void throwExceptionForNegativeNumber(char *listOfNegativeNumbers);

int calculateStringSum(const char *inputString) {
  int stringSum = 0;
  char* customDelimiter;
  char tempInputString[strlen(inputString)];
  strcpy(tempInputString, inputString);

  if(!isEmptyString(inputString)) {
    checkAndReplaceCustomDelimiterWithCommaDelimiter(tempInputString);
    replaceNewLineDelimiterWithCommaDelimiter(tempInputString);
    checkForNegativeNumbersInInputString(tempInputString);
    addNumbersFromInputString(tempInputString, &stringSum);
  }

  return stringSum;
}

int isEmptyString(const char *inputString) {
  return (strlen(inputString) == 0);
}

void throwExceptionForNegativeNumber(char *listOfNegativeNumbers) {
  if(listOfNegativeNumbers) {
    char errorMessage[strlen(listOfNegativeNumbers) + 35];
    strcpy(errorMessage,"negative numbers not allowed: ");
    strcat(errorMessage, listOfNegativeNumbers);
    errorMessage[strlen(errorMessage)-1] = '\0';
    printf("\n%s\n",errorMessage);
    exit(EXIT_FAILURE);
  }
}

void checkForNegativeNumbersInInputString(char *inputString) {
  char listOfNegativeNumbers[strlen(inputString)];
  strcpy(listOfNegativeNumbers,"");
  char* token = strtok(inputString,",");
  while (token != NULL) {
    if(atoi(token) < 0) {
      strcat(listOfNegativeNumbers,token);
      strcat(listOfNegativeNumbers,",");
    }
    token = strtok(NULL,",");
  }
  throwExceptionForNegativeNumber(listOfNegativeNumbers);
}

void addNumbersFromInputString(char *inputString, int* sumString) {
  char* token = strtok(inputString,",");
  printf("\n\nsumString(before loop) = %d",*sumString);
  while (token != NULL) {
    removeNonDigitCharactersFromToken(token);
    removeNumbersGreaterThanThousand(token);
    (*sumString) += atoi(token);
    printf("\nsumString(in loop) = %d",*sumString);
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

void checkAndReplaceCustomDelimiterWithCommaDelimiter(char *inputString) {
  if((inputString[0] == '/') && (inputString[1] == '/')) {
    char tempInputString[strlen(inputString)];
    strcpy(tempInputString,inputString);
    
    char* customDelimiter = strtok(tempInputString+2,"\n");
    
    char* contentOfInputString = inputString + 2 + strlen(customDelimiter) + 1;
    
    replaceCustomDelimiterWithCommaDelimiter(contentOfInputString, customDelimiter);
    
    strcpy(inputString,contentOfInputString);
  }
}

void replaceCustomDelimiterWithCommaDelimiter(char *inputString, char* customDelimiter) {
  int lenInputString = strlen(inputString);
  char tempString[lenInputString];
  char tempString2[lenInputString];
  int lenCustomDelimiter = strlen(customDelimiter);
  
//   printf("\n\ncustom delimiter: %s",customDelimiter);
  
  strcpy(tempString2,"");
  strcpy(tempString,inputString);
  char* token = strstr(tempString,customDelimiter);
  
//   printf("\ntempString: %s\ttempString2: %s\ttoken: %s\n",tempString,tempString2,token);
    
  while(token != NULL) {
    strncpy(tempString2,tempString,(token-tempString));
    // printf("\ntempString: %s\ttempString2: %s\ttoken: %s",tempString,tempString2,token);
    
    tempString2[(token-tempString)] = '\0';
    // printf("\ntempString: %s\ttempString2: %s\ttoken: %s",tempString,tempString2,token);
    
    strcat(tempString2,",");
    // printf("\ntempString: %s\ttempString2: %s\ttoken: %s",tempString,tempString2,token);
    
    strcat(tempString2, (token+lenCustomDelimiter));
    // printf("\ntempString: %s\ttempString2: %s\ttoken: %s",tempString,tempString2,token);
    
    strcpy(tempString,tempString2);
    // printf("\ntempString: %s\ttempString2: %s\ttoken: %s",tempString,tempString2,token);
    
    token = strstr(tempString,customDelimiter);
    // printf("\ntempString: %s\ttempString2: %s\ttoken: %s",tempString,tempString2,token);
    
    strcpy(tempString2,"");
    // printf("\ntempString: %s\ttempString2: %s\ttoken: %s\n",tempString,tempString2,token);
  }
  strcpy(inputString,tempString);
}

void replaceNewLineDelimiterWithCommaDelimiter(char *inputString) {
  for(int i = 0; inputString[i] != '\0'; ++i) {
    if(inputString[i] == '\n') {
      inputString[i] = ',';
    }
  }
}
