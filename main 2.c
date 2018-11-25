//
//  main.c
//  CS49CgrpPrj
//
//  Created by Alora Clem on 11/19/18.
//  Copyright © 2018 Alora Clem. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int generatePassword(void);
int savePassword(FILE*);
int export(FILE*);
int main(int argc, const char * argv[]) {
    //password file creation
    FILE* passwordFile;
    passwordFile = fopen("passwords.txt", "w+");
    fprintf(passwordFile, "Website:             Password:\n");
    fclose(passwordFile);
    
    
    srand((unsigned int)time(NULL));
    //menu statements
    printf("Hello, welcome to Password Generator!\n");
    printf("Press 1 for generating a new password on its own\n");
    printf("Press 2 for saving a new website and password combination\n");
    printf("Press 3 for exporting your combinations to a file\n");
    int input = 0;
    scanf("%d", &input);
    //check that input is valid
    while(input < 1 || input > 3){
        printf("Error incorect input, please pick a number from 1 to 3");
        scanf("%d", &input);
    }
    
    //case 1: generating a new password on its own
    if(input == 1){
    generatePassword();
    }
    //case 2: saving a new website and password combination
    else if(input == 2){
    savePassword(passwordFile);
    }
    //case 3: exporting your combinations to a file
    else{
        export(passwordFile);
    }
    
    return 0;
}
int generatePassword(){
    printf("How many characters total would you like your password to be? You can generate up to a max of 50 length");
    int length = 0;
    scanf("%d", &length);
    while(length <1){
        printf("Error incorect input, please pick a number greater than 0");
        scanf("%d", &length);
    }
    while(length >50){
        printf("Error incorect input, please pick a number less than 50");
        scanf("%d", &length);
    }
    
    //the count to track how many total characters are already used
    int characterCount= 0;
    
    printf("How many should be letters? ");
    int letters = 0;
    scanf("%d", &letters);
    if((letters + characterCount) > length){
        printf("Error incorect input, please pick a number less than the length desired");
        scanf("%d", &letters);
    }
    characterCount+= letters;
    
    printf("How many should be uppercase? ");
    int upper = 0;
    scanf("%d", &upper);
    if( upper > letters){
        printf("Error incorect input, please pick a number less than the number of letters desired");
        scanf("%d", &upper);
    }
    
    printf("How many should be numbers? ");
    int numbers = 0;
    scanf("%d", &numbers);
    if((numbers + characterCount) > length){
        printf("Error incorect input, please pick a number less than the length desired");
        scanf("%d", &numbers);
    }
    characterCount+= numbers;
    
    printf("Special characters will fill the rest of the password: ");
    int special = length-characterCount;
    printf("%d\n", special);
    characterCount+= special;
    
    int index = 0;
    char pass[50];
    while (index < length){
        pass[index] = 0;
        index++;
    }
    index=0;
    int tempUpper = upper;
    while(tempUpper > 0){
        //upper case ascii is from 65-90
        int character = rand()%(90+1-65) +65;
        char c = character;
        pass[index] = c;
        tempUpper--;
        index ++;
    }
    tempUpper= upper;
    while((letters-tempUpper) > 0){
        //lower case ascii is from 97-122
        int character = rand()%(122+1-97)+97;
        char c = character;
        pass[index]= c;
        tempUpper++;
        index ++;
    }
    while(numbers > 0){
        //number ascii is from 48-57
        int character = rand()%(57+1-48)+48;
        char c = character;
        pass[index]= c;
        numbers--;
        index ++;
    }
    while(special > 0){
        //special ascii is from 33 - 47
        int character = rand()%(47+1-33)+33;
        char c = character;
        pass[index]= c;
        special--;
        index ++;
    }
    //shuffle array so password is randomized
    for(int i = 0; i < length; i++)
    {
        int randIndex = (rand()%length);
        char temp = pass[i];
        pass[i] = pass[randIndex];
        pass[randIndex] = temp;
    }
    puts("GENERATED PASSWORD:");
    for(int i = 0; i < length; i++)
    {
        printf("%c", pass[i]);
    }
    puts("\n-------------------------");
    return 0;
}

int savePassword(FILE* passwordFile){
    char website[50];
    char password[50];
    printf("What is the website's URL?:");
    scanf("%s", website);
    printf("What is the website's password?:");
    scanf("%s", password);
    passwordFile = fopen("passwords.txt", "a");
    fprintf(passwordFile, "%s             %s\n", website, password);
    fclose(passwordFile);
    return 0;
}
int export(FILE* passwordFile){
    puts("Your file is titled passwords.txt and contains all combinations");
    return 0;
}
