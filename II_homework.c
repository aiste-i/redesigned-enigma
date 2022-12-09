#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_FOR_ARRAY_SIZE 6
#define MAX_FOR_ELEMENT_LENGHT 10
#define ARRAY_CAPACITY 99999
#define NUMBER_OF_FORMULAS 3

int numberOfArrayElements();
int checkForRightDigitInput(char *element, int lenghtMax);
int getArrayElement( unsigned long *dataForElement);
int getMinMaxElements( int numberOfElementsInArray,  unsigned long *arrayElements, unsigned long *minElementAddress, unsigned long *maxElementAdress);
int intervalElements( int minValue, int maxValue, int numberOfElementsToBeChecked, unsigned long *arrayElements);

int main(){
    int arraySize = 0;
    unsigned long minElement, maxElement;
    unsigned long userInputArray[ARRAY_CAPACITY] = {0};
    char *formulas[NUMBER_OF_FORMULAS] = {"[MIN, MIN + (MAX - MIN)/3]", "[MIN + (MAX - MIN)/3, MIN + (MAX - MIN)*2/3]", "[MIN + (MAX - MIN)*2/3, MAX]"};
    //sending to function, to get the array size
    arraySize = numberOfArrayElements();
    // checking if an error did not occur
    for( int i = 0; i < arraySize; i++){
        printf("\nIveskite %d masyvo nari, kuris yra sveikas naturalusis skaicius: ", i + 1);
        if(getArrayElement(&userInputArray[i]) == 0)
            printf("Atlikta sekmingai. Teskite.\n");
    }
    // sending to function to get MIN and MAX elements, checking if an error did not occur
    if (getMinMaxElements(arraySize, userInputArray, &minElement, &maxElement) != 0)
        printf("Problem with evaluating MIN and MAX elements.\n");
    // sending to function, to get the I interval elements
    for(int i = 0; i < NUMBER_OF_FORMULAS; i++){
        printf("\nMasyvo reiksmes, kurios atitinka %d intervalo %s salyga:\n\n", i + 1, formulas[i]);
        if(intervalElements(minElement + (maxElement - minElement)*i/3 , minElement + (maxElement - minElement)*(i + 1)/3, arraySize, userInputArray) != 0)
            printf("Problem with evaluating %d interval elements.\n", i + 1);
    }
    return 0;
}

int numberOfArrayElements(){
    int sizeOfArray = 0;
    char arraySizeHolder[MAX_FOR_ARRAY_SIZE] = "";
    printf("Iveskite viena sveika naturaluji skaiciu: ");
    if(fgets(arraySizeHolder, SHRT_MAX, stdin) != NULL){
        if(checkForRightDigitInput(arraySizeHolder, MAX_FOR_ARRAY_SIZE) > 1){
            printf("\nNeteisinga ivestis. Negalimi simboliai, neigiami skaiciai, skaiciai su kableliu. Ivestis gali buti iki %d skaitmenu.\n", MAX_FOR_ARRAY_SIZE - 1);
            return 0 + numberOfArrayElements();
        }else{
            sizeOfArray = atoi(arraySizeHolder);
            return sizeOfArray;
        } 
    }
}

int checkForRightDigitInput(char *element, int lenghtMax){
    int dataLenght = 0;
    int dataErrCount = 0;
    dataLenght = strlen(element);
    // cheking how many symbols aren't numbers
    for(int i = 0; i < dataLenght; i++){
        if(isdigit(element[i]) == '\0')
            ++dataErrCount;
    }
    // checking if it's not too long
    if(dataLenght > lenghtMax || dataLenght == dataErrCount){
        // jei ne pridedamas 1 prie error count
        ++dataErrCount;
    }
    return dataErrCount;
}

int getArrayElement( unsigned long *dataForElement){
    int counterForWhileCycle = 0;
    char dataHolder[MAX_FOR_ELEMENT_LENGHT];
    do{
        free(dataForElement);
        if(counterForWhileCycle > 0)
            printf("\nNeteisinga ivestis. Negalimi simboliai, neigiami skaiciai, skaiciai su kableliu. Ivestis gali buti iki %d skaitmenu.\n", MAX_FOR_ELEMENT_LENGHT - 1);
        ++counterForWhileCycle;
        fgets(dataHolder, SHRT_MAX, stdin);
    }while(checkForRightDigitInput(dataHolder, MAX_FOR_ELEMENT_LENGHT) > 1);
    *dataForElement = atoi(dataHolder);
    return 0;
}

int getMinMaxElements( int numberOfElementsInArray,  unsigned long *arrayElements, unsigned long *minElementAddress, unsigned long *maxElementAdress){
    //first array elements assigned to MIN and MAX
    *minElementAddress = arrayElements[0];
    *maxElementAdress = arrayElements[0];
    for(int i = 0; numberOfElementsInArray > i; i++){
        // MIN or MAX elements changed if are true
        if(*minElementAddress > arrayElements[i])
            *minElementAddress = arrayElements[i];
        if(*maxElementAdress < arrayElements[i])
            *maxElementAdress = arrayElements[i];
    }
    return 0;
}

int intervalElements( int minValue, int maxValue, int numberOfElementsToBeChecked, unsigned long *arrayElements){
    int printingCount = 0;
    for(int i = 0; i < numberOfElementsToBeChecked; i++){
        if(arrayElements[i] >= minValue && arrayElements[i] <= maxValue ){
            printf("%-10lu", arrayElements[i]);
            //checking how many times it worked
            ++printingCount;
        }
    }
    // if non elements were printed
    if(printingCount == 0)
            printf("Siam intervalui atitinkanciu skaitmenu nera.\n");
    return 0;
}
