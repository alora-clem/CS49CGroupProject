//
//  main.c
//  CS49CgrpPrj
//
//  Created by Alora Clem and Gurdev Sihra on 11/19/18.
//  Copyright 2018 Alora Clem and Gurdev Sihra. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void generatePassword(FILE*);
void savePassword(FILE*, char []);
void export(FILE*);
void printMenu(void);
int verification(void);


int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    //password file creation
    FILE* passwordFile;
    passwordFile = fopen("/Users/aclem/Desktop/cs49c/CS49CgrpPrj/CS49CgrpPrj/en.lproj/passwords.txt", "w");
    fclose(passwordFile);
    
    //verify username and password
    int verify = verification();
    if(verify == 0){
        // end program, incorrect password too many times
        return 0;
    }
    
    //menu statements
    printMenu();
    int input = 0;
    scanf("%d", &input);
    //check that input is valid
    while (input < 1 || input > 4) {
        printf("Error incorect input, please pick a number from 1 to 4");
        scanf("%d", &input);
    }
    
    while(input !=4){
        //case 1: generating a new password on its own
    if (input == 1) {
        generatePassword(passwordFile);
    }
    //case 2: saving a new website and password combination
    else if (input == 2) {
        char emptyPass[50] = {0};
        savePassword(passwordFile, emptyPass);
    }
    //case 3: exporting your combinations to a file
    else if(input==3){
        export(passwordFile);
    }
        printMenu();
    scanf("%d", &input);
    }
    //case 4 quitting
    puts("Have a nice day!");
    return 0;
}

void generatePassword(FILE *passwordFile) {
    printf("How many characters total would you like your password to be? You can generate up to a max of 50 length\n");
    int length = 0;
    scanf("%d", &length);
    while (length < 1) {
        printf("Error incorect input, please pick a number greater than 0\n");
        scanf("%d", &length);
    }
    while (length > 50) {
        printf("Error incorect input, please pick a number less than 50\n");
        scanf("%d", &length);
    }
    
    //the count to track how many total characters are already used
    int characterCount = 0;
    
    printf("How many should be letters? ");
    int letters = 0;
    scanf("%d", &letters);
    if ((letters + characterCount) > length) {
        printf("Error incorect input, please pick a number less than the length desired");
        scanf("%d", &letters);
    }
    characterCount += letters;
    
    int upper = 0;
    if(letters > 0){
    printf("How many should be uppercase? ");
    
    scanf("%d", &upper);
    if (upper > letters) {
        printf("Error incorect input, please pick a number less than the number of letters desired");
        scanf("%d", &upper);
    }
    }
    printf("How many should be numbers? ");
    int numbers = 0;
    scanf("%d", &numbers);
    if ((numbers + characterCount) > length) {
        printf("Error incorect input, please pick a number less than the length desired");
        scanf("%d", &numbers);
    }
    characterCount += numbers;
    
    printf("Special characters will fill the rest of the password: ");
    int special = length - characterCount;
    printf("%d\n", special);
    characterCount += special;
    
    int index = 0;
    char pass[50];
    while (index < length) {
        pass[index] = 0;
        index++;
    }
    index = 0;
    int tempUpper = upper;
    while (tempUpper > 0) {
        //upper case ascii is from 65-90
        int character = rand() % (90 + 1 - 65) + 65;
        char c = character;
        pass[index] = c;
        tempUpper--;
        index++;
    }
    tempUpper = upper;
    while ((letters - tempUpper) > 0) {
        //lower case ascii is from 97-122
        int character = rand() % (122 + 1 - 97) + 97;
        char c = character;
        pass[index] = c;
        tempUpper++;
        index++;
    }
    while (numbers > 0) {
        //number ascii is from 48-57
        int character = rand() % (57 + 1 - 48) + 48;
        char c = character;
        pass[index] = c;
        numbers--;
        index++;
    }
    while (special > 0) {
        //special ascii is from 33-47, 58-64, 91-96, 123-126
        //4 ranges are possible
        //randomly get one of the ranges
        int set = rand() % 4 + 1;
        int character = 0;
        //depending on which range, generate a character
        switch (set) {
            case 1:
                character = rand() % (47 + 1 - 33) + 33;
                break;
            case 2:
                character = rand() % (64 + 1 - 58) + 58;
                break;
            case 3:
                character = rand() % (96 + 1 - 91) + 91;
                break;
            case 4:
                character = rand() % (126 + 1 - 123) + 123;
                break;
        }
        char c = character;
        pass[index] = c;
        special--;
        index++;
    }
    //shuffle array so password is randomized
    for (int i = 0; i < length; i++)
    {
        int randIndex = (rand() % length);
        char temp = pass[i];
        pass[i] = pass[randIndex];
        pass[randIndex] = temp;
    }
    puts("GENERATED PASSWORD:");
    for (int i = 0; i < length; i++)
    {
        printf("%c", pass[i]);
    }
    puts("\n-------------------------");
    
    // Option to automatically create a struct object to save generated password for a specified site
    puts("Press 1 to save this password for a website");
    puts("Press 0 to return to the menu");
    int save = 0;
    scanf("%d", &save);
    if (save == 1) {
        savePassword(passwordFile, pass);
    }
}

void savePassword(FILE* passwordFile, char pass[50]) {
    char website[50] = {0};
    printf("What is the website's URL?:\n");
    scanf("%s", website);
    //check contents of password to see if it is prefilled or empty
    for(int i = 0; i <50; i ++){
        if(pass[i]!=0){
            //it isn't empty, don't need to ask for password
            break;
        }
        else if( i == 49){
            //iterated and had all 0's therefore empty password
            printf("What is the website's password?:");
            scanf("%s", pass);
        }
    }
    passwordFile = fopen("/Users/aclem/Desktop/cs49c/CS49CgrpPrj/CS49CgrpPrj/en.lproj/passwords.txt", "a");
    fprintf(passwordFile, "Website: %s\n", website);
    fprintf(passwordFile, "Password: %s\n", pass);
    fprintf(passwordFile, "-------------------------\n");
    fclose(passwordFile);
    puts("Combination saved");
    puts("-------------------------");
}

void export(FILE* passwordFile) {
    puts("Your file is titled passwords.txt and contains all combinations");
    puts("It's file path is: /Users/aclem/Desktop/cs49c/CS49CgrpPrj/CS49CgrpPrj/en.lproj/passwords.txt");
    puts("Warning: if you would like to keep the file, copy it to another location before running Password Generator again");
}
void printMenu(){
    printf("Press 1 for generating a new password on its own\n");
    printf("Press 2 for saving a new website and password combination\n");
    printf("Press 3 for exporting your combinations to a file\n");
    printf("Press 4 to exit\n");
}

int verification(){
    //file with username and password
    FILE *userInfo;
    userInfo = fopen("/Users/aclem/Desktop/cs49c/CS49CgrpPrj/CS49CgrpPrj/en.lproj/userInfo.txt", "r");
    //username and password strings from file
    char fileUserName[20] = {0};
    char filePassword[20] = {0};
    
    char ch;
    int index = 0;
    //flag to switch from writing into fileUserName to filePassword
    int switchToPassword = 0;
    
    while ((ch = fgetc(userInfo)) != EOF) {
        if(ch == '\n'){
            //the file has an enter, that means the password now needs to be read
            switchToPassword = 1;
            index = 0;
            //skip the /n character
            ch = fgetc(userInfo);
        }
        if(switchToPassword == 0){
            //write into username
            fileUserName[index] = ch;
        }
        else{
            //write into password
            filePassword[index] = ch;
        }
        index++;
    }
    fclose(userInfo);
    
    //strings for user inputted username and password
    char inputtedUsername[10] = {0};
    char inputtedPassword[10] = {0};
    //number of tries to enter password
    int tries = 3;
    printf("Hello, welcome to Password Generator!\n");
    //flag to determine if the user has been verified
    int verified = 1;
    //loop to check equality of user input and user information file
    while(verified != -1){
        verified = 1;
        printf("Enter your username:\n");
        scanf("%s", inputtedUsername);
        for(int i = 0; i < 10; i ++){
            char f = fileUserName[i];
            char in = inputtedUsername[i];
            if(f != in){
                puts("Incorrect Username, try again");
                //reset inputterUsername
                for(int j = 0; j <= i; j ++){
                    inputtedUsername[j] = 0;
                }
                verified = 0;
                break;
            }
        }
        if(verified == 1){
            //passed the username section now onto password verification
            printf("Enter your password:\n");
            scanf("%s", inputtedPassword);
            for(int i = 0; i < 10; i ++){
                char f = filePassword[i];
                char in = inputtedPassword[i];
                if(f != in){
                    tries--;
                    //reset inputtedPassword
                    for(int j = 0; j <= i; j ++){
                        inputtedPassword[j] = 0;
                    }
                    if(tries>0){
                        printf("Incorrect Password, %d tries left\n", tries);
                    }
                    else{
                        puts("Incorrect Password, you have run out of tries, come back later\n");
                        //whole program needs to be ended, the user is locked out
                        return 0;
                    }
                    verified = 0;
                    break;
                }
            }
        }
        if(verified == 1){
            puts("Correct, logged in");
            puts("-------------------------");
            //to break out of loop
            verified = -1;
        }
    }
    return 1;
    //verified
}
