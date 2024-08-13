//Brianna Knight
//PROJECT ITERATION_03

//The goal of this is to create a ride share program with administrator login privleges to set up
// information for the ridesharing, the program will then continue to run until the admin shuts the program down. Survey data, fare details and total calculations will then be displayed followed by the program summary for the business.

//The first iteration demonstrates the use of functions, random, and to showcase the AGILE development cycle.  The second iteration will demonstrate the use of functions, pointers 2D arrays and validating input data.



//Preprocessor director headers to allow the use of booleans, inputs/outputs,time and general utilities
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <ctype.h>



//Used to generate random number of minutes based on number of miles
#define MIN_RAND_MINUTES_FACTOR 1.2
#define MAX_RAND_MINUTES_FACTOR 1.5

//Sentinel value to end rider mode
#define SENTINAL_VALUE -1

//Allocated space for character arrays
#define STRING_LENGTH 80

//Correct password and correct ID
#define CORRECT_ID "a"
#define CORRECT_PASS "b"

//Maximum attempts for admin login
#define MAX_ATTEMPTS 2

//Number of categories for the survey
#define NUMBER_CATEGORIES 3

//Row numbers for the survey
#define SURVERY_RIDER_ROWS 5

//Range for rating for the rider survey
#define MIN_RATING 1
#define MAX_RATING 5

//Range for the maximum and minimum miles
#define MIN_MILES 1
#define MAX_MILES 100

//Range for the minimum and maximum admin values
#define MIN_ADMIN_VALUES .1
#define MAX_ADMIN_VALUES 50

//Structure to carry variables for a single rideshare
typedef struct rideshare{
    
    //Represents the basefare,cost per minute, cost per mile and flat rate set by the admin
    double baseFare;
    double costPerMinute;
    double costPerMile;
    double flatRate;
    //Represents the total outcomes from a rideshare program
    double totalMiles;
    double totalMinutes;
    double totalFare;
    double totalRiders;
    unsigned int surveyCount;
    unsigned int count;
    //Represents the company name
    char companyName[STRING_LENGTH];
    //Represents the next pointer in a linked list
    struct rideshare *nextPtr;
    //Represents to surveys submitted by users
    int survey[][NUMBER_CATEGORIES];
    
    
}RideShare;



//Function Prototypes
double getValidDoubleSentinel(int min, int max, int sentinel);
double getValidDouble(int min,int max);
int calculateRandomNumber(int min,int max);
double calculateFare(double base, double minuteCost, double mileCost, double minRate, double miles, int minutes);
void printFare(int count, double miles, double minutes, double fare);
void fgetsRemoveNewLine(char *strptr);
char getYorN();
bool logInAdmin(const char *correctID, const char *correctPass,unsigned int maxAttempts);
void setUpRideShare(RideShare *rideSharePtr,int min,int max);
bool scanDouble(const char *buffer,double *output);
void displayRideShareRatings(unsigned int surveyCount,const int survey[][NUMBER_CATEGORIES], const char *surveyCategories[NUMBER_CATEGORIES]);
void getRideShareRatings(unsigned int survey[][NUMBER_CATEGORIES],unsigned int *surveyCount,unsigned int min,unsigned int max);
void riderShareMode(RideShare *headPtr);
void calculateAndPrintRideShare(RideShare *rideSharePtr, const char *surveyCategories[NUMBER_CATEGORIES]);
void insertNode(RideShare **headPtr);
RideShare *riderSelectMode(RideShare *headPtr);
void writeInfoToFile(RideShare *headPtr);
void deallocateMemory(RideShare *headPtr);

//Survey Categories that riders give a rating for.
const char *surveyCategories[NUMBER_CATEGORIES] = {"Safety", "Cleanliness", "Comfort"};


int main(void) {

//Administrator will login
    
    bool adminStarted = logInAdmin(CORRECT_ID,CORRECT_PASS,MAX_ATTEMPTS);
    
    //RS *headPtr=null;
    RideShare *headPtr=NULL;
    //If login successful, setup a rideshare program
    if(adminStarted){
        insertNode(&headPtr);
        riderShareMode(headPtr);
        writeInfoToFile(headPtr);
    }
    
    deallocateMemory(headPtr);
    
}//Main


//Returns a double, checks if input from user is a double, within min and max range or a sentinel
double getValidDoubleSentinel(int min, int max, int sentinel) {
    
    //Variables for a flag, an output double, input from user, and a pointer
    bool isValid =false;
    double validDouble=0;
    char input [STRING_LENGTH];
    
    //While user input isnt within parameters
    while(isValid ==false){
        
        //Gets input from the user
        fgets(input,STRING_LENGTH,stdin);
        
        //Removes new line operator
        fgetsRemoveNewLine(input);
        
        bool isDouble = scanDouble(input,&validDouble);
        
        //Check if what was entered was converted to a double
        if(isDouble){
        
            //Ensure hours are within the range from 0-max, sentinel value -1
            if((validDouble >= min && validDouble <=max || (validDouble==sentinel))){
                
                //If valid set to true
                isValid = true;
                
            }
        
               //Print error if not within range but is a number
               else {
                printf("Error: Not within %d and %d. Please enter value again. ", min,max);
                }
            }
        
               //print error for not a number
            else {
                puts("Error: Not an integer number. Please enter the value again.");
            }
        
    }//End of while
    
    return validDouble;

}//getValidDoubleSentinel



//Validating user input without checking the sentinel value
double getValidDouble(int min,int max){
    
    bool isValid =false;
    double validDouble=0;
    char input [STRING_LENGTH];
    
    //while input isnt a number
    while(!isValid){
        
        //Gets input from user, removes new line character
        fgets(input,STRING_LENGTH,stdin);
        fgetsRemoveNewLine(input);
        
        bool isDouble = scanDouble(input,&validDouble);
        
        //double
        
        //Check if what is entered is a number
        if(isDouble){
            
            //Ensure hours are within the range from 0-max
            if((validDouble >= min && validDouble <=max )){
    
                isValid = true;
                
            }
            
            //Print error if not within range but is a number
            else {
                printf("Error: Not within %d and %d. Please enter value again. ", min,max);
            }
        }
        //print error for not a number
        else {
            puts("Error: Not an integer number. Please enter the value again.");
        }
        
    }//End of while
    
    return validDouble;
    
}//validDouble


//Calculates riderfare using given equations
double calculateFare(double base, double minuteCost, double mileCost, double minRate, double miles, int minutes) {

    //setting rideFare to calculated values
     double rideFare = base + (minuteCost * minutes) + (mileCost * miles);
    
    //if ridefare is below the minimum rate, charge the flat rate
    if (rideFare <= minRate) {
        rideFare = minRate;
    }

    return rideFare;

}//calculateFare


//Get a random number for simulate minutes of a rideshare ride
int calculateRandomNumber(int min, int max){
                
    int randomNum = rand() % (max-min+1)+min;
    return randomNum;
                
}//calculateRandomNumber


//Prints riders,miles, minutes and fare
void printFare(int count, double miles, double minutes, double fare) {

    puts("");
    
    //if no riders, print no riders message, or else you print the fare.
    if (count == 0){
        puts("There are no riders");
    }

    else{
        puts("Rider\t\tNumber of Miles\t\t\tNumber of Minutes\t\t\tRide Fare Amount");
        
        printf("%d    \t\t%.1lf    \t\t\t\t\t%.1lf             \t\t\t$%.2lf",count,miles,minutes,fare);
    }

}//printFare


//Removes the newline character from a character array to ensure no issues when comparing strings
void fgetsRemoveNewLine(char *strptr){
    
    //take the length of the inputted string
    size_t length = strlen(strptr);
    
    //if the second to last character is the newline character and the string is bigger than 1
    if(strptr[length-1]=='\n'&&length>0){
        
        //set the second to last character to the null, ommitting the newline
        strptr[length-1]='\0';
    }
    //if the string isnt longer than 1, set it all to null to ensure no issues
    else{
        strptr[0]='\0';
    }
}//fgetsRemoveNewLine
 

//Ensure the user either enters a y,Y,n,N
char getYorN(void){
   
    bool isValid =false;
    char yesOrNo=0;
    char input [STRING_LENGTH];
    
    while(isValid == false){
        
        //Store value for valid data inputted from fgets
        fgets(input,STRING_LENGTH,stdin);
        
        //remove the new line to ensure you can compare the input
        fgetsRemoveNewLine(input);
        
        //if input is within parameters, set flag to true, set the output to the first char entered
        if(input[0]=='y'||input[0]=='n'||input[0]=='Y'||input[0]=='N'){
            
            isValid=true;
            yesOrNo=input[0];
            
        }
        
        //keep asking the user for correct input
        else{
            puts("You did not enter yes or no, please enter y or n");
        }
        
    }//while
    
    return yesOrNo;
    
}//getYorN


//Returns true if the user inputs the correct ID and password within the attempts, returns false otherwise.
bool logInAdmin(const char* correctID, const char* correctPass,unsigned int maxAttempts){
    
    //Initializing variables for the return value, attempts,inputs for ID and password
    bool isLoginValid=false;
    unsigned int attempts=1;
    char inputID [STRING_LENGTH];
    char inputPass [STRING_LENGTH];
    
    //while the login is unsuccessful and the user hasnt reached the maximum attempts
    while(attempts<=maxAttempts && !isLoginValid){
        
        //obtains ID and passwords from the user
        puts("Admin Login");
        puts("Enter your Admin id");
        fgets(inputID,STRING_LENGTH,stdin);
        fgetsRemoveNewLine(inputID);
        
        puts("Enter your Admin passcode");
        fgets(inputPass,STRING_LENGTH,stdin);
        fgetsRemoveNewLine(inputPass);
        
        //If correctID and password are inputted, return value is true
        if(strcmp(inputID, correctID) == 0 && strcmp(inputPass, correctPass) == 0){
            isLoginValid=true;
        }
        
        //else, add to the total attempts
        else{
            attempts++;
        }
        
        //if max attempts met, exit the rideShare
        if(attempts > maxAttempts){
            puts("Exiting RideShare");
        }
    }//while

    return isLoginValid;
    
}//loginAdmin


//Allows the admin to set up the baseFare, cost per minute and mile, and a flat rate, initializes the totals to zero.
void setUpRideShare(RideShare *rideSharePtr,int min,int max){
    
    puts("Set up rideshare information");
    puts("");
    
    puts("Enter the base fare:");
    rideSharePtr->baseFare=getValidDouble(min,max);
    
    puts("Enter the cost per minute:");
    rideSharePtr->costPerMinute=getValidDouble(min,max);
    
    puts("Enter the cost per mile:");
    rideSharePtr->costPerMile=getValidDouble(min,max);
    
    puts("Enter the minimum flat rate:");
    rideSharePtr->flatRate=getValidDouble(min,max);
    
    rideSharePtr->totalMiles=0;
    rideSharePtr->totalMinutes=0;
    rideSharePtr->totalRiders=0;
    rideSharePtr->totalFare=0;
    rideSharePtr->surveyCount=0;
    
    puts("Enter the Company Name:");
    
    fgets(rideSharePtr->companyName,STRING_LENGTH,stdin);
    
    fgetsRemoveNewLine(rideSharePtr->companyName);
    
    //Printing the inputted values from admin
    puts("");
    printf("%s\n",rideSharePtr->companyName);
    printf("baseFare = %.1f\n",rideSharePtr->baseFare);
    printf("costPerMinute = %.1f\n",rideSharePtr->costPerMinute);
    printf("costPerMile = %.1f\n",rideSharePtr->costPerMile);
    printf("minFlatRate = %.1f\n",rideSharePtr->flatRate);
    puts("");
    
    
    
}//setUpRideShare


//Returns true if the input given is successfully translated to a double.
bool scanDouble(const char *buffer,double *output){
    
    char *attempt;
    double testNum =0;
    bool isValid=false;
    
    //takes the input from the user and changes it from a char array to a decimel.
    testNum=strtod(buffer,&attempt);
    
    //if attempt and input from user aren't equal, the strod was successful
    
    
    if(attempt!=buffer){
        isValid=true;
        *output=testNum;
    }
    return isValid;
    
}//scanDouble


//Displays the 2D survey taken from users.
void displayRideShareRatings(unsigned int surveyCount,const int survey[][NUMBER_CATEGORIES], const char *surveyCategories[NUMBER_CATEGORIES]){
    
    if(surveyCount<=0){
        puts("No surveys");
    }
    else{
        puts("");
        puts("Survey Results");
        puts("Rating Categories");
        
        for(size_t i =0;i<NUMBER_CATEGORIES;i++){
            printf("\t\t\t\t%zu. %s",i+1,surveyCategories[i]);
        }
        
        puts("");
        for(size_t row = 0; row<surveyCount;row++){
            
            printf("Rider %zu\t\t\t\t",row+1);
            
            for(size_t col =0; col<NUMBER_CATEGORIES;col++){
                
                printf("\t%d\t\t\t\t\t",(survey[row][col]));
                
            }
            printf("\n");
        }
    }//else
    
}//displayRideShareRatings


//Obtains survey ratings for each categories, stores it in the 2D array for surveyratings
void getRideShareRatings(unsigned int survey[][NUMBER_CATEGORIES],unsigned int *surveyCount, unsigned int min,unsigned int max){
    
    puts("\nWe want to know how your experience was on your ride today.  Using the rating system 1 to 5 enter your rating for each category:");
    
    for(size_t i =0;i<NUMBER_CATEGORIES;i++){
        printf("\t\t\t%zu. %s\t     ",i+1,surveyCategories[i]);
    }
    
    puts("");
    double input = 0;
    
    for(size_t category=0;category<NUMBER_CATEGORIES;category++){
        
        printf("Enter your rating for %s: \n", surveyCategories[category]);
        input = getValidDouble(min,max);
        survey[*surveyCount][category]= input;
        
    }
    
    *surveyCount+=1;
    
}//getRatings


//Allows for riders to input miles and vote in survey, admins to exit the program and view business summary.
void riderShareMode(RideShare *headPtr){
    
    bool loginStatus = false;
    
    do{
        
        
        RideShare *rideSharePtr = riderSelectMode(headPtr);
        
        
        printf("Welcome to the %s. \nWe can only provide services for rides from %d to %d miles.",rideSharePtr->companyName,MIN_MILES,MAX_MILES);
        puts("");
        
        //Display the 2D array
        displayRideShareRatings(rideSharePtr->surveyCount,rideSharePtr->survey,surveyCategories);
        
        puts("");
      
        //REPLACE WITH GET SELECTED RIDESHARE
            puts("Please enter the number of miles");
            
            double inputMiles=getValidDoubleSentinel(MIN_MILES, MAX_MILES, SENTINAL_VALUE);
            
            //If sentinel value is entered, ask for the admin login again
            if(inputMiles==SENTINAL_VALUE){
                
            bool adminSuccess = logInAdmin(CORRECT_ID, CORRECT_PASS, MAX_ATTEMPTS);
                
                if(adminSuccess){
                    
                    RideShare *current= headPtr;
                    
                    while(current!=NULL){
                        
                        calculateAndPrintRideShare(current, surveyCategories);
                        current=current->nextPtr;
                        
                    }
                    
                    loginStatus=true;
                }
                else{
                    loginStatus=false;
                }
            }//If sentinel entered
            
            //If sentinel not entered, calculate the ride share
            else{
                
                rideSharePtr->count++;
                int minutes = calculateRandomNumber(MIN_RAND_MINUTES_FACTOR, MAX_RAND_MINUTES_FACTOR);
                double baseFare= rideSharePtr->baseFare;
                double costPerMin= rideSharePtr->costPerMinute;
                double costPerMile= rideSharePtr->costPerMile;
                double flatRate = rideSharePtr->flatRate;
                double fare = calculateFare(baseFare, costPerMin, costPerMile, flatRate ,inputMiles,minutes);
                
                int riderNumber =rideSharePtr->count;
                //Add to the totals
                rideSharePtr->totalFare+=fare;
                rideSharePtr->totalMiles+=inputMiles;
                rideSharePtr->totalRiders++;
                rideSharePtr->totalMinutes+=minutes;
                
                printFare(rideSharePtr->totalRiders,inputMiles,minutes,fare);
                
                //Add in totalMiles,totalMinutes, totalFare;
                
                puts("\nDo you want to rate your rideshare experience?");
                
                char rateAnswer = getYorN();
                
                if(rateAnswer=='y'||rateAnswer=='Y'){
                    
                    getRideShareRatings(rideSharePtr->survey, &(rideSharePtr->surveyCount), MIN_RATING, MAX_RATING);
                }
                else{
                    puts("Thanks for riding with us.");
                }
                
            }//Sentinel not entered, go through with logins
            
    }
    while(loginStatus==false);
        
}//riderShareMode


//Calculates the averages for each survey category, prints the business summary.
void calculateAndPrintRideShare(RideShare *rideSharePtr, const char *surveyCategories[NUMBER_CATEGORIES]){
    
    int surveyCount=rideSharePtr->surveyCount;
    double totalMinutes= rideSharePtr->totalMinutes;
    double totalFare=rideSharePtr->totalFare;
    double averageArray[NUMBER_CATEGORIES];
    
    if(surveyCount==0){
        puts("There are no surveys");
    }
    
    else{
        
        for(size_t columns=0;columns<NUMBER_CATEGORIES;columns++){
            
            double totalCategory =0;
            double average=0;
            
            for(size_t rows=0;rows<surveyCount;rows++){
                
                totalCategory+=rideSharePtr->survey[rows][columns];
                
            }
            
            average=(double) totalCategory/surveyCount;
            averageArray[columns]=average;
        }
    }//else
    
    printf("%s Summary Report\n\n",rideSharePtr->companyName);
    
    puts("Rider \t\t Number of Miles\tNumber of Minutes\tRide Fare Amount");
    
    printf("%.1f \t\t  %.1lf \t\t\t\t\t %.1lf \t\t\t $%.2lf\n",rideSharePtr->totalRiders,rideSharePtr->totalMiles,rideSharePtr->totalMinutes,rideSharePtr->totalFare);
    
    puts("");
    puts("Category Rating Averages");
    
    if(rideSharePtr->surveyCount>0){
        for(size_t i =0;i<NUMBER_CATEGORIES;i++){
            printf("%d. %s: \t%.2lf\n",i+1,surveyCategories[i],averageArray[i]);
        }
    }
    else{
        puts("No surveys.");
    }
    
    
    
}//calculateAndPrintRideShare

//Inserts a new node into the linked list according to the company name
void insertNode(RideShare **headPtr){
    
    char userAnswer='q';
    do{
        //Create a temporary rideshare object
        RideShare rideShareProgram;
        
        //Set up new rideshare details with predefined min and max values
        setUpRideShare(&rideShareProgram, MIN_ADMIN_VALUES, MAX_ADMIN_VALUES);
        
        //Allocate memory for the new node
        RideShare *newNode = (RideShare*)malloc(sizeof(RideShare));
        
        //If memory allocation fails, print an error message
        if(newNode == NULL){
            puts("Memory not allocated");
        }
        
        //If memory allocation is successful
        else {
            //Initialize the new node with the rideShareProgram details
            *newNode = rideShareProgram;
            //Set the next pointer of the new node to NULL
            newNode ->nextPtr=NULL;
            
            //Check if list empty or new node should be inserted in beginning
            if(*headPtr==NULL||(strcmp(newNode->companyName,(*headPtr)->companyName))<0){
                //Point the new node next pointer to the head, putting it in front
                newNode->nextPtr=*headPtr;
                //Put the head at the beginning of the list
                *headPtr = newNode;
            }
            
            //IF LIST NOT EMPTY TRAVERSE LIST AND FIND WHERE IT FITS
            else{
                
                //Set a new current pointer to the beginning of the list
                RideShare *current = *headPtr;
                
                //Create a pointer for a previous node, incase the node must go in the middle
                RideShare *previous = NULL;
                
                //WHILE POINTER NOT AT END AND LOOK FOR ALPHABETICAL FIT
                while(current != NULL && strcmp(newNode->companyName,current->companyName)>0){
                    
                    //set the previous node to the current pointer.
                    previous = current;
                    //set the current pointer to the next node over.
                    current = current->nextPtr;
                }
                
                //If the new node should be inserted somewhere after the first node in the list
                if(previous!=NULL){
                    
                    //Links the new node after the current (which comes AFTER the new node alphabetically).
                    newNode->nextPtr=current;
                    
                    //The previous node next pointer points to the new node, linking it to the list.
                    previous->nextPtr = newNode;
                }
              
            }//else list not empty
            puts("Do you want to add another rideshare, y or n?");
            userAnswer = getYorN();
        }//else memory was allocated
    }while(userAnswer =='y'||userAnswer=='Y');
}//InsertNode


//Asks the user to enter a company name, checks if the company matches any in the linked list. Returns the pointer of the selected RideShare
RideShare *riderSelectMode(RideShare *headPtr){
    
    //Setting the boolean flag to false.
    bool foundRideShare= false;
    
    //Initializing the return rideshare pointer
    RideShare *selectedRideShare=NULL;
    
    //While the user has not entered the correct rideshare
    while(!foundRideShare){
        
        //Set a current pointer to the beginning of the linked list.
        RideShare *current= headPtr;
        
        //Printing out each option for the ride shares.
        while(current!=NULL){
            
            printf("Company name: %s\n",current->companyName);
            displayRideShareRatings(current->surveyCount, current->survey, surveyCategories);
            current=current->nextPtr;
        }
        
        puts("");
        puts("Enter the name of the RideShare you want to use:");
        
        //Obtaining the userInput from the user
        char userInput[STRING_LENGTH];
        fgets(userInput,STRING_LENGTH,stdin);
        
        //Removing the newline character to ensure comparison works
        fgetsRemoveNewLine(userInput);
        
        //Resetting the current pointer to the beginning.
        current=headPtr;
        
        //While the pointer is not at the end of the list.
        while(current!=NULL){
            
            //If the user input is equal to the RideShare nodes company name.
            if(strcmp(userInput, current->companyName)==0){
                
                //The return value is set as whatever the current is, flag set to true to break out of loop.
                selectedRideShare=current;
                foundRideShare=true;
            }
            
            //Change the current to the next node, compare the values again.
            current=current->nextPtr;
            
        }//while temp not at end
        puts("");
        puts("Error, the RideShare you entered doesn't match, please select from the following:");
    }//whileRideShareNotFound
    
    return selectedRideShare;
}

//Writes the Business Summaries to a file according to a name.
void writeInfoToFile(RideShare *headPtr){
    
    //Setting a pointer to the beginning of a list.
    RideShare *current = headPtr;
    
    while(current != NULL){
        
        //Initializing a string to the file data path
        char fileName[STRING_LENGTH]="/Users/briannaknight/Dev/rideshare/";
        char underscoreCompanyName[STRING_LENGTH];
        
        //Replacing the whitespace with the _ in a company name
        strcpy(underscoreCompanyName, current->companyName);
        
        for(int i = 0; underscoreCompanyName[i]!='\0';i++){
            if(underscoreCompanyName[i]==' '){
                underscoreCompanyName[i]= '_';
            }
        }
        
       
        //Add two strings together using string concatanate, adding the file name
        strcat(fileName,underscoreCompanyName);
        //The adding the .txt extension
        strcat(fileName,".txt");
        
        //Opening/Creating a text file for writing
        FILE* file = fopen(fileName,"w");
        
        //If creating the file was unsuccessful, print error message
        if(file==NULL){
            puts("File could not be opened");
        }
        
        //If file creation was successful, write the business summary to the file.
        else{
            fprintf(file,"%s Summary Report\n",current->companyName);
            fputs("Rider  Number of Miles  Number of Minutes  RideFare Amount",file);
            fprintf(file,"%.1f \t\t  %.1lf \t\t\t\t\t %.1lf \t\t\t $%.2lf\n\n",current->totalRiders,current->totalMiles,current->totalMinutes,current->totalFare);
            fputs("Category Rating Averages",file);
            
            
        }
        //Close the file
        fclose(file);
        //Move to the next node in the linked list
        current=current->nextPtr;
        
    }
    
}

//Deallocating memory made on the stack
void deallocateMemory(RideShare *headPtr){
    
    while(headPtr!=NULL){
        RideShare *temp = headPtr->nextPtr;
        free(headPtr);
        headPtr=temp;
    }
    headPtr=NULL;
}

