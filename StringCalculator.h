#include "string.h"

/* Function Prototypes */
int calculateStringSum(const char *inputString);
int isEmptyString(const char *inputString);

int calculateStringSum(const char *inputString) {
  int stringSum = 0;

  if(!isEmptyString(inputString)) {
    //tbd
  }

  return stringSum;
}

int isEmptyString(const char *inputString) {
  return (strlen(inputString) == 0);
}
