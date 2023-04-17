/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
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

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt){
    int count = 0, i;
    const struct Patient *p = patient;
    displayPatientTableHeader();
    for (i = 0; i < max; i++){
        if (p[i].patientNumber != 0){
            displayPatientData(&p[i], fmt);
            count++;
        }
    }
    if (count == 0){
        putchar('\n');
        printf("*** No records found ***\n");
    }
    putchar('\n');
    
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max){
    int selection;
    const struct Patient *p = patient;
    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
            selection = inputIntRange(0, 2);
            putchar('\n');
            switch (selection)
            {
            case 1:
                searchPatientByPatientNumber(p, max);
                clearInputBuffer();
                suspend();
                break;
            case 2:
                searchPatientByPhoneNumber(p, max);
                clearInputBuffer();
                suspend();
                break;
            }
    } while (selection);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max){
    int findFree = 0;
    int indexFree;
    struct Patient *p = patient;
    int i;
    for (i = 0; i< max && findFree == 0; i++){
        if (p[i].patientNumber == 0){
            findFree = 1;
            indexFree = i;
            p[indexFree].patientNumber = nextPatientNumber(p, max);
            inputPatient(&p[indexFree]);
            printf("*** New patient record added ***\n\n");
        }
    }
    if (findFree == 0){
        printf("ERROR: Patient listing is FULL!\n");
        putchar('\n');
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max){
    struct Patient *p = patient;
    int userInput, status = 0;
    printf("Enter the patient number: ");
    scanf("%d", &userInput);
    putchar('\n');
    status = findPatientIndexByPatientNum(userInput, p, max);
    switch (status)
    {
    case -1:
            printf("ERROR: Patient record not found!\n");
            putchar('\n');
            break;
    default:
            menuPatientEdit(&p[status]);
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max){
    struct Patient *p = patient;
     int userRemove, status = 0;
     int selection;
    printf("Enter the patient number: ");
    scanf("%d", &userRemove);
    clearInputBuffer();
    putchar('\n');
    status = findPatientIndexByPatientNum(userRemove, p, max);
    switch (status)
    {
    case -1:
            printf("ERROR: Patient record not found!\n");
            break;
    default:
            displayPatientData(&p[status], FMT_FORM);
            putchar('\n');
            printf("Are you sure you want to remove this patient record? (y/n): ");
            selection = !(inputCharOption("yn") == 'y');
            if (!selection)
            {
                p[status].patientNumber = 0;
                p[status].name[NAME_LEN] = '\0';
                p[status].phone.description[PHONE_DESC_LEN] = '\0';
                p[status].phone.number[PHONE_LEN] = '\0';
                printf("Patient record has been removed!\n");
            }
            else
            {
                printf("Operation aborted.\n");
            }
            break;
    }
    putchar('\n');
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(const struct ClinicData clinic[]){
    void displayScheduleTableHeader();
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(const struct ClinicData clinic[]){
    void displayScheduleTableHeader();
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(const struct Appointment appointment[], int maxApp,
                           const struct Patient patient[], int maxPat){

                           }

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appointment[], int maxApp,
                            const struct Patient patient[], int maxPat){

                              }

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max){
    int userInput;
    const struct Patient *p = patient;
    int status = 0;
    
    printf("Search by patient number: ");
    scanf("%d", &userInput);
    putchar('\n');
    status = findPatientIndexByPatientNum(userInput, p, max);
    switch (status){
        case -1:
            printf("*** No records found ***\n\n");
            break;
        default:
            displayPatientData(&p[status], FMT_FORM);
            putchar('\n');
    }

}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max){
    char userInput[PHONE_LEN+1];
    const struct Patient *p = patient;
    int i, count = 0;
    printf("Search by phone number: ");
    scanf("%s", userInput);
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++){
        if (strcmp(userInput, p[i].phone.number) == 0){
            displayPatientData(&p[i], FMT_TABLE);
            count++;
        }
    }
    putchar('\n');
    if (count == 0){
        printf("*** No records found ***\n\n");
    }
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max){
    const struct Patient *p = patient;
    int largest = p[0].patientNumber;
    int nextPatientNum = 0, i;

    for (i = 0; i < max; i++){
        if (p[i].patientNumber > largest){
            largest = p[i].patientNumber;
        }
    }
    nextPatientNum = largest + 1;

    return nextPatientNum;

}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max){
    const struct Patient *p = patient;
    int i;
    int result, findRecord = 0;
    for (i = 0; p[i].patientNumber != '\0' && findRecord == 0; i++){
        if (patientNumber == p[i].patientNumber){
            result = i;
            findRecord = patientNumber == p[i].patientNumber;
        }
    }
    if (findRecord == 0){
        result = -1;
    }

    return result;
    
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient){
    struct Patient *p = patient;
    
    printf("Patient Data Input\n"
            "------------------\n");
    printf("Number: %05d\n", p->patientNumber);
    printf("Name  : ");
    scanf(" %[^'\n']", p->name);
    clearInputBuffer();
    putchar('\n');
    inputPhoneData(&p->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone){
    int selection;
    printf("Phone Information\n"
            "-----------------\n"
            "How will the patient like to be contacted?\n"
            "1. Cell\n"
            "2. Home\n"
            "3. Work\n"
            "4. TBD\n"
            "Selection: ");
            selection = inputIntRange(1, 4);
            putchar('\n');
            switch (selection)
            {
            case 1:
                strcpy(phone->description, "CELL");
                printf("Contact: %s\n", phone->description);
                printf("Number : ");
                scanf("%s", phone->number);
                clearInputBuffer();
                putchar('\n');
                break;
            case 2:
                strcpy(phone->description, "HOME");
                printf("Contact: %s\n", phone->description);
                printf("Number : ");
                scanf("%s", phone->number);
                clearInputBuffer();
                putchar('\n');
                break;
            case 3:
                strcpy(phone->description, "WORK");
                printf("Contact: %s\n", phone->description);
                printf("Number : ");
                scanf("%s", phone->number);
                clearInputBuffer();
                putchar('\n');
                break;
            case 4:
                strcpy(phone->description, "TBD");
                phone->number[PHONE_LEN] = '\0';
                break;
            default:
                break;
            }

}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(char *filename, const struct Patient patient[], int max){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }
    int i = 0;
    while (i < max && fscanf(file, "%d|%[^|]|%[^|]|%s", &patient[i].patientNumber, patient[i].name, &patient[i].phone.description, &patient[i].phone.number) != EOF) {
        i++;
    }
    fclose(file);
    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:

int importAppointments(char *filename, const struct Appointment appoints[], int max){
    int patientNumber[20];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }
    int i = 0;
    while (i < max && fscanf(file, "%d,%d,%d,%d,%d,%d", patientNumber[i], &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min ) ==6 ){
        i++;
    }
    fclose(file);
    return i;
}
