/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  :
Student ID#:
Email      :
Section    :

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS



//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

#include <stdio.h>
#include <stdlib.h>

#include "core.h"


// Clear the standard input buffer 
void clearInputBuffer(void) 
{
    // Discard all remaining char's from the standard input buffer: 
    while (getchar() != '\n') 
    { 
        ; // do nothing! } 
    }
}

// Wait for user to input the "enter" key to continue 
void suspend(void) 
{ 
    printf("<ENTER> to continue..."); 
    clearInputBuffer(); 
    putchar('\n'); 
}

int inputInt(void)
{
    int value = 0;
    char newLine = 'x';
    do {
        scanf("%d%c", &value, &newLine);

        if (newLine != '\n'){
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newLine != '\n');
        return value;
}

  int inputIntPositive(void)
  {
      int value;
      char newLine = 'x';
      int keepVal = 1;
    do {
        scanf("%d%c", &value, &newLine);
     
             if (newLine != '\n'){
                 clearInputBuffer();
                 printf("Error! Input a whole number: ");
             }
             else if (newLine == '\n'){
                 if (value <= 0){
                     printf("ERROR! Value must be > 0: ");
                 }
                 else if (value > 0) {
                     keepVal = 0;
                 }
             }
     } while (keepVal == 1);
   
        return value;
  }

 int inputIntRange(int minInRange, int maxInRange)
 {

     int value;
     char newLine = 'x';
     int keepVal = 1;
   do {
       scanf("%d%c", &value, &newLine);

            if (newLine != '\n'){
                clearInputBuffer();
                printf("Error! Input a whole number: ");
            }
            else if (newLine == '\n'){
                if (value < minInRange || value > maxInRange){
                    printf("ERROR! Value must be between %d and %d inclusive: ",minInRange,maxInRange);
                }
                else if (value >= minInRange && value <= maxInRange){
                    keepVal = 0;
                }
            }
    } while (keepVal == 1);

       return value;
 }

 char inputCharOption(const char inputString[])
 {
     int i;
     char tempChar;
     int stopChecking = 0;

    do{
    scanf(" %c", &tempChar);

        for (i = 0; inputString[i] != '\0';i++){
            if (tempChar == inputString[i]){
                stopChecking = tempChar == inputString[i]; //to exit foor loop
                }
        }
        if (stopChecking == 0){
            clearInputBuffer();
            printf("ERROR: Character must be one of [qwErty]: ");
        }

    } while (stopChecking == 0);

     return tempChar;
}

  void inputCString(char *inputCString, int minInRange,int maxInRange)
  {
      int i;
      int countChar;
      int keepValid = 1;
  //does not return a value, but does return a C string via the 1st argument parameter pointer.
        do
        {
            scanf(" %[^'\n']", inputCString);
            for (i = 0, countChar = 0; inputCString[i] != '\0'; i++){
                 countChar ++;
            }

            if (minInRange == maxInRange) {
                if (countChar != minInRange) {
                    clearInputBuffer();
                    printf("ERROR: String length must be exactly %d chars: ", maxInRange);
                }
                else {
                    keepValid = 0;
                }
            }
            else if (maxInRange > minInRange) {
                if (countChar > maxInRange) {
                    clearInputBuffer();
                    printf("ERROR: String length must be no more than %d chars: ", maxInRange);
                }
                else if (countChar < minInRange) {
                    clearInputBuffer();
                    printf("ERROR: String length must be between %d and %d chars: ", minInRange, maxInRange);
                }
                else {
                    keepValid = 0;
                }
            }
        } while(keepValid == 1);
  }

void displayFormattedPhone(const char *inputCString)
{
    int i, countChar;
    
    
        if (inputCString == NULL) {
            printf("(___)___-____");
        } //if
        else {
            int findInt = 1;
            for (i = 0, countChar = 0; inputCString[i] != '\0'; i++){
                countChar++;
            }
            for (i = 0; inputCString[i] != '\0' && findInt; i++){
                findInt = inputCString[i] - '0' < 10;
            }
            if (countChar != 10 || !findInt){
                printf("(___)___-____");
            }
            else if (countChar == 10 && findInt == 1){
                printf("(%c%c%c)%c%c%c-%c%c%c%c", inputCString[0], inputCString[1], inputCString[2], inputCString[3], inputCString[4], inputCString[5], inputCString[6], inputCString[7], inputCString[8], inputCString[9]);
                
            }
                
            
         }//else
        
        
        
}