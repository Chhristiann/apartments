/*
    Christian Chacon | 4/19/23

    Begin Exam Practice #2 with this practie program.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //exit(0)
#include <ctype.h>  //toupper()
#include <unistd.h> //sleep()

struct Apartments{
    int number;
    char style[15];
    int beds;
    int baths;
    float squareft;
    char monthAvail[10];
    float rent;
};

void readAllApartments(struct Apartments apt[]);
void getUserData(int *usrBedsP, int *usrBathsP, char *usrMonthP[], float *usrRentP);
int showAvailableApartments(int usrBedsP, int usrBathsP, char usrMonth[], float usrRent, struct Apartments apt[]);
void printContract(struct Apartments apt[], int aptChoice);

int main(){
    struct Apartments apt[10];
    int usrBeds, usrBaths, aptChoice;
    char usrMonth[10];
    float usrRent;
    
    readAllApartments(apt);
    getUserData(&usrBeds, &usrBaths, usrMonth, &usrRent);
    aptChoice = showAvailableApartments(usrBeds, usrBaths, usrMonth, usrRent, apt);
    printContract(apt, aptChoice);

    return 0;
}

void readAllApartments(struct Apartments apt[]){
    char line[100];
    char *sp;

    FILE *fp;
        fp = fopen("apartmentRentals.csv", "r");
        if(fp == NULL){
            printf("\nERROR in reading file, exiting...");
            exit(0);
        }

        //fgets() returns != NULL -- Cannot be used for strings
        //fscanf() returns != EOF

        int x = 0;
        //while fgets takes ALL our data from one line from apartmentRentals.csv and stores that in a big string.
        while(fgets(line, 100, fp) != NULL){
        //atoi takes info and changes to integer
        //atof takes info and changes to float
        sp = strtok(line,",");
            apt[x].number = atoi(sp);
        sp = strtok(NULL,",");
            strcpy(apt[x].style, sp);
        sp = strtok(NULL,",");
            apt[x].beds = atoi(sp);
        sp = strtok(NULL,",");
            apt[x].baths = atoi(sp);
        sp = strtok(NULL,",");
            apt[x].squareft = atof(sp);
        sp = strtok(NULL,",");
            strcpy(apt[x].monthAvail, sp);
        sp = strtok(NULL,",");
            apt[x].rent = atof(sp);
        x++;
        }

    fclose(fp);
}

void getUserData(int *usrBedsP, int *usrBathsP, char *usrMonthP[], float *usrRentP){
    int bedrooms, bathrooms;
    char month[10];
    float rent;

    printf("What is the minimum number of bedrooms (1-3) you would like? ");
    while(1){
        scanf("%d", &bedrooms);
        if(bedrooms >= 1 && bedrooms <= 3){
            break;
        }
        else{
            printf("Please enter the choice of (1-3) bedrooms.");
        }
    }
    printf("What is the minimum number of bathrooms (1-2) you would like? ");
    while(1){
        scanf("%d", &bathrooms);
        if(bathrooms >= 1 && bathrooms <= 2){
        break;
        }
        else{
        printf("Please enter the choice of (1-2) bathrooms.");
        }
    }
    printf("What month of availability are you looking for? (Enter ALL for any month) ");
    scanf("%s", month);
    printf("What is the maximum monthly rent you would like to pay? ");
    while(1){
        scanf("%f", &rent);
        if(rent > 0){
        break;
        }
        else{
        printf("Please enter a valid amount of money.");
        }
    }

    *usrBedsP = bedrooms;
    *usrBathsP = bathrooms;
    strcpy(usrMonthP, month);
    *usrRentP = rent;
}

int showAvailableApartments(int usrBeds, int usrBaths, char usrMonth[], float usrRent, struct Apartments apt[]){
    int aptChoice;

    printf("\n\n Base on your search results, you have the selection of...");
    printf("\n _______________________________________________________________");
    printf("\n|   Apt #        Style     Bed  Bath   Sqr FT   Month    Rent   |");
    printf("\n|  -------------------------------------------------------------|\n");
    for(int x = 0; x < 10; x++){
        if(apt[x].beds >= usrBeds){
            if(apt[x].baths >= usrBaths){
                if(apt[x].rent <= usrRent){
                    if(strcmp("NA", apt[x].monthAvail) != 0){
                        // to check ALL listings
                        for(int x = 0; x < strlen(usrMonth); x++){
                            usrMonth[x] = toupper(usrMonth[x]);
                        }
                        if(strcmp("ALL", usrMonth) == 0){
                            printf("|  %5d | %-15s | %d | %d | %7.2f | %-6s | %7.2f |\n", apt[x].number, apt[x].style, apt[x].beds, apt[x].baths, apt[x].squareft, apt[x].monthAvail, apt[x].rent);
                        }
                        // to check months in the correct formaing
                        for(int x = 1; x < strlen(usrMonth); x++){
                            usrMonth[x] = tolower(usrMonth[x]);
                        }
                        if(strcmp(apt[x].monthAvail, usrMonth) == 0){
                            printf("|  %5d | %-15s | %d | %d | %7.2f | %-6s | %7.2f |\n", apt[x].number, apt[x].style, apt[x].beds, apt[x].baths, apt[x].squareft, apt[x].monthAvail, apt[x].rent);
                        }
                    }
                }
            }
        }
    }
    printf(" ---------------------------------------------------------------\n");

    printf("Enter the apartment of your choice: ");
    scanf("%d", &aptChoice);
    return aptChoice;
}

void printContract(struct Apartments apt[], int aptChoice){
    char extraPark, pets;
    char fileName[20];
    int numPets = 0;
    float addedCharges = 0;

    for(int x = 0; x < 10; x++){
    if(aptChoice == apt[x].number){
        printf("\nYou have choosen the %s, apartment number %d", apt[x].style, apt[x].number);
        printf("\n  with %d bedroom(s) and %d bathroom(s)", apt[x].beds, apt[x].baths);
        printf("\n  and %.0f square feet, avaiable in %s", apt[x].squareft, apt[x].monthAvail);
        printf("\n\nThe monthly rent is $%.2f", apt[x].rent);

        printf("\n------------------Additional Charge(s)------------------");
        printf("\n\nWould you like a covered parking space for an extra $30.00 per month? (Y/N):  ");
        scanf("\n%c", &extraPark);
            extraPark = toupper(extraPark);
            if(extraPark == 'Y'){
                addedCharges += 30.00;
            }

        printf("\nDo you have any pets? (Y/N):  ");
        scanf("\n%c", &pets);
            pets = toupper(pets);
            if(pets == 'Y'){
                printf("How many pets do you have?  ");
                scanf("%d", &numPets);
                  addedCharges += (25 * numPets);
            }
        apt[x].rent += addedCharges;
        printf("\n--------------------------------------------------------");

        printf("\nThank You! Just one more step, what is the file name to print? ");
        scanf("%s", fileName);
            fileName[0] = tolower(fileName[0]);

      // create and write file

      FILE *writeFile;
        writeFile = fopen(fileName, "w");
        if(writeFile == NULL){
            printf("Error in writing file %s, exiting...", fileName);
            exit(0);
        }
        else{
            for(int print = 0; print < 5; print++){
            printf("\nprinting...");
            sleep(1);
            }
            printf("\nSuccess! Your file %s has printed.", fileName);

            fprintf(writeFile, "You have choosen the %s, apartment number %d", apt[x].style, apt[x].number);
            fprintf(writeFile, "\n  with %d bedroom(s) and %d bathroom(s)", apt[x].beds, apt[x].baths);
            fprintf(writeFile, "\n  and %.0f square feet, avaiable in %s", apt[x].squareft, apt[x].monthAvail);
            fprintf(writeFile, "\n\nThe monthly rent is:  $%.2f", apt[x].rent);

            if(extraPark == 'Y'){
            fprintf(writeFile, "\nCovered Parking: $30.00");
            }
            if(pets == 'Y'){
            fprintf(writeFile, "\nPet Charge: $%d.00", (25 * numPets));
            }
        }
        fclose(writeFile);
    }
    }
}