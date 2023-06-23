#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct my_date_t {
    uint8_t date;
    uint8_t month;
    uint16_t year;
} my_date_t;

typedef enum status_t {
    SUCCESS,
    NULL_PTR,
    INCORRECT
} status_t;

status_t convertStringToDate(const char* dateStr, my_date_t* dateStruct) {
    if (dateStr == NULL || dateStruct == NULL) {
        return NULL_PTR;
    }

    // Check if the date string has the correct format "DD/MM/YYYY"
    if (sscanf(dateStr, "%hhu/%hhu/%hu", &dateStruct->date, &dateStruct->month, &dateStruct->year) != 3) {
        return INCORRECT;
    }

    // Additional checks for valid values
    if (dateStruct->date < 1 || dateStruct->date > 31 || dateStruct->month < 1 || dateStruct->month > 12 || dateStruct->year < 1) {
        return INCORRECT;
    }

    return SUCCESS;
}

int main() {
    const char* dateStr = "07/06/2023";
    my_date_t dateStruct;
    status_t status = convertStringToDate(dateStr, &dateStruct);

    if (status == SUCCESS) {
        printf("Conversion successful: %02d/%02d/%04d\n", dateStruct.date, dateStruct.month, dateStruct.year);
    } else if (status == NULL_PTR) {
        printf("Error: NULL pointers.\n");
    } else if (status == INCORRECT) {
        printf("Error: Incorrect values for date, month, or year.\n");
    }

    return 0;
}
