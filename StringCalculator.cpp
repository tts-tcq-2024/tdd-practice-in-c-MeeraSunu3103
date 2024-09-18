#include <stdlib.h>
#include <string.h>
#include <cctype>
#include "StringCalculator.h"

/* Function Prototypes */
void replaceNewLineDelimiterWithCommaDelimiter(char *tempInputString);
int addNumbersFromInputString(char *inputString);
void removeNonDigitCharactersFromToken(char *token);
void deleteCharFromStringByIndex(char *inputString, int charIndex);
void removeNumbersGreaterThanThousand(char *token);
void checkAndReplaceCustomDelimiterWithCommaDelimiter(char *inputString);
void replaceCustomDelimiterWithCommaDelimiter(char *inputString, char* customDelimiter);
void checkForNegativeNumbersInInputString(char *inputString);
void throwExceptionForNegativeNumber(char *listOfNegativeNumbers);
int isCustomDelimiterFormatStarterPresent(char *inputString);
int isCustomDelimiterFormatEnderPresent(char *inputString);

/* Function Description: sets the exception message and throws the exception once a negative number has been detected*/
/* Parameters:
      listOfNegativeNumbers - string in which the negative numbers have been listed so that they can be included in the exception message
*/
void throwExceptionForNegativeNumber(char *listOfNegativeNumbers) {
  if(strlen(listOfNegativeNumbers) != 0) {
    char errorMessage[strlen(listOfNegativeNumbers) + 35];
    strcpy(errorMessage,"negative numbers not allowed: ");
    strcat(errorMessage, listOfNegativeNumbers);
    errorMessage[strlen(errorMessage)-1] = '\0';
    throw std::runtime_error(errorMessage);
  }
}

/* Function Description:  */
/* Parameters:
      p - 
*/
void checkForNegativeNumbersInInputString(char *inputString) {
  /* create a copy of input string to be used with strtok() */
  char tempInputString[strlen(inputString)];
  strcpy(tempInputString,inputString);
  
  /* create a string to store the negative numbers */
  char listOfNegativeNumbers[strlen(inputString)];
  strcpy(listOfNegativeNumbers,"");

  /* get the sub-string before the delimiter and loop through all such sub-strings */
  char* token = strtok(tempInputString,",");
  while (token != NULL) {
    if(atoi(token) < 0) {
      strcat(listOfNegativeNumbers,token);
      strcat(listOfNegativeNumbers,",");
    }
    token = strtok(NULL,",");
  }
  throwExceptionForNegativeNumber(listOfNegativeNumbers);
}

int calculateStringSum(const char *inputString) {
  int stringSum = 0;
  char* customDelimiter;
  char tempInputString[strlen(inputString)];
  strcpy(tempInputString, inputString);

  if(strlen(inputString) != 0) {
    checkAndReplaceCustomDelimiterWithCommaDelimiter(tempInputString);
    replaceNewLineDelimiterWithCommaDelimiter(tempInputString);
    checkForNegativeNumbersInInputString(tempInputString);
    stringSum = addNumbersFromInputString(tempInputString);
  }

  return stringSum;
}

int addNumbersFromInputString(char *inputString) {
  int stringSum = 0;
  
  /* get the sub-string before the delimiter and loop through all such sub-strings */
  char* token = strtok(inputString,",");  
  while (token != NULL) {
    removeNonDigitCharactersFromToken(token);
    removeNumbersGreaterThanThousand(token);
    stringSum += atoi(token);
    token = strtok(NULL,",");
  }

  return stringSum;
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
    /* if the number is greater than 1000, it is replaced with zero so that 0 is added to the string sum */
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

int isCustomDelimiterFormatStarterPresent(char *inputString) {
    return (((inputString[0] - '/') + (inputString[1] - '/')) == 0);
}

int isCustomDelimiterFormatEnderPresent(char *inputString) {
    return (strstr(inputString+2,"\n") != NULL);
}

void checkAndReplaceCustomDelimiterWithCommaDelimiter(char *inputString) {
  if((isCustomDelimiterFormatStarterPresent(inputString) + isCustomDelimiterFormatEnderPresent(inputString)) == 2) {
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
  
  /* set initial values for the temporary strings */
  strcpy(tempString2,"");
  strcpy(tempString,inputString);
  char* token = strstr(tempString,customDelimiter);
    
  while(token != NULL) {
    /* copy the characters that occur before the custom delimiter */
    strncpy(tempString2,tempString,(token-tempString));    
    tempString2[(token-tempString)] = '\0';

    /* add the comma delimiter */
    strcat(tempString2,",");
    
    /* add the rest of the string after the custom delimiter */
    strcat(tempString2, (token+lenCustomDelimiter));
    
    /* prepare for next iteration of the while loop */
    strcpy(tempString,tempString2);    
    token = strstr(tempString,customDelimiter);    
    strcpy(tempString2,"");
  }

  /* finally copy the modified string into the input string */
  strcpy(inputString,tempString);
}

void replaceNewLineDelimiterWithCommaDelimiter(char *inputString) {
  for(int i = 0; inputString[i] != '\0'; ++i) {
    if(inputString[i] == '\n') {
      inputString[i] = ',';
    }
  }
}
