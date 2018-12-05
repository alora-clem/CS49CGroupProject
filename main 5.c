//
//  CS 49C Term Project
//	Section 1
//
//  Created by Alora Clem and Gurdev Sihra on 11/19/18.
//  Copyright 2018 Alora Clem and Gurdev Sihra. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void generatePassword(FILE*);
void savePassword(FILE*, char[50]);
void export(FILE*);
void printMenu(void);
int verification(void);
void display(FILE* passwordFile);
void setFiles();

char filePath[1000];
char passwordFile[1000];
char userFile[1000];

/**
	Default File Paths

		Unspecified File Path: /Users/sihra/Desktop/cs49c/CS49CgrpPrj/CS49CgrpPrj/en.lproj
		User Info File Path: /Users/sihra/Desktop/cs49c/CS49CgrpPrj/CS49CgrpPrj/en.lproj/userInfo.txt
		Passwords File Path: /Users/sihra/Desktop/cs49c/CS49CgrpPrj/CS49CgrpPrj/en.lproj/passwords.txt
**/

int main(int argc, const char * argv[]) {

	srand((unsigned int)time(NULL));

	// Introduction to the Password Generator program
	printf("---------- Password Generator ----------\n\n\n");
	printf("Welcome to the Password Generator!\n\n");

	printf("This program will generate randomized passwords to secure your accounts, save your website/password combinations, and export these to a file in your specified path.\n\n");

	// Requirements for using Password Generator
	printf("Before we get started, make sure that:\n");
	printf("1. There is a folder in your preferred file path to specify where your exported file for website/password combinations should go.\n");
	printf("2. There is a file, \" userInfo.txt \", that contains your username and password on two seperate files in the specified folder from 1.\n\n");

	printf("* The default file path will be used if not specified. *\n");

	// 1. Asking user to specify their file path
	printf("Do you want to specify your own file path to the folder containing \"userInfo.txt\"? [Y/N]\n");
	char check;
	scanf("%s", &check);
	char yes = 'Y';
	char no = 'N';

	// Checks if user input either Y for yes or N for no
	while (check != yes && check != no) {
		printf("Error incorect input, please enter Y for yes or N for no.\n");
		scanf("%s", &check);
	}
	// If the user inputs Y, then file path will be updated
	if (check == yes) {
		printf("\nSpecify your file path:  ");
		printf("Enter file path: \n");
		scanf("%s", filePath);

		//Run method to output userInfo.txt filePath
		setFiles();

		// **********DELETE: Alora these are tests to make sure it's working for you
		printf("\nHere's the path you included: %s \n", filePath);
		printf("Here's your user file, the one used to check if the path exists: %s \n", userFile);

		// We check if the file path contains userInfo.txt because it is required from the program and passwords.txt will be generated if it doesn't exist
		FILE* checkFilePath = fopen(userFile, "r");

		// Checks if the user specified file path is accessible and continuously asks if there's an error
		while (checkFilePath == NULL) {
			printf("\n\nError: Specified file path does not exist, enter the correct path:  ");
			scanf("%s", filePath);
			setFiles();
			FILE* checkFilePath = fopen(userFile, "r");
		}
		printf("\n");

	}
	else {
		// Default file path - Used when connected to "main source", also listed above
		char *defaultPath = "/Users/sihra/Desktop/cs49c/CS49CgrpPrj/CS49CgrpPrj/en.lproj";
		strncpy(filePath, defaultPath, sizeof(filePath));
		setFiles();
	}

	// 2. Ask user if they have used this program in the past
	printf("Have you used this program before? [Y/N] \n");
	scanf("%s", &check);

	// Checks if input is not Y or N
	while (check != yes && check != no) {
		printf("Error incorect input, please enter Y for yes or N for no.\n");
		scanf("%s", &check);
	}

	// FILE* used to check if file path is correct
	FILE* passwordsTXT;

	// If the user has used this program before, their passwords.txt file will either be appended or overwritten
	if (check == yes) {
		printf("The last application of this program output a \"passwords.txt\" file, would you like to overwrite it? [Y/N]\n");
		scanf("%s", &check);

		// Checks if input is not Y or N
		while (check != yes && check != no) {
			printf("Error incorect input, please enter Y for yes or N for no.\n");
			scanf("%s", &check);
		}

		// If the user wants to overwrite their passwords.txt file
		if (check == yes) {
			passwordsTXT = fopen(passwordFile, "w");
			fclose(passwordsTXT);
		}

		// IF the user wants to append/add to their passwords.txt file
		else {
			passwordsTXT = fopen(passwordFile, "a");
			fclose(passwordsTXT);
		}
	}

	// If the user has NEVER used this program before, a new passwords.txt file will be created
	else {
		printf("\nA new file \"passwords.txt\" will be created in your file path.\n");
		passwordsTXT = fopen(passwordFile, "w");
		fclose(passwordsTXT);
	}


	// Verify username and password
	int verify = verification();
	if (verify == 0) {

		// End program, incorrect password too many times
		return 0;
	}

	// Menu statements
	printMenu();
	int input = 0;
	scanf("%d", &input);

	// Check that input is valid
	while (input < 1 || input > 6) {
		printf("Error incorect input, please pick a number from 1 to 4");
		scanf("%d", &input);
	}

	while (input != 5) {
		//case 1: generating a new password on its own
		if (input == 1) {
			generatePassword(passwordsTXT);
		}
		//case 2: saving a new website and password combination
		else if (input == 2) {
			char emptyPass[50] = { 0 };
			savePassword(passwordsTXT, emptyPass);
		}
		//case 3: exporting your combinations to a file
		else if (input == 3) {
			export(passwordsTXT);
		}
		//case 4: displaying password - website combinations
		else if (input == 4) {
			display(passwordsTXT);
		}
		printMenu();
		scanf("%d", &input);
	}
	//case 5: quitting
	puts("Have a nice day!");
	return 0;
}

/**
	Method that generates the randomized password suited to user specifications of a length under 50 and the amount of letters, uppercase letters, and numbers
**/
void generatePassword(FILE *passwordFile) {
	printf("How many characters total would you like your password to be? You can generate up to a max of 50 length\n");

	// User specified length of the password
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

	// Count to track how many total characters are already used
	int characterCount = 0;
	printf("How many should be letters? ");

	// Count to track how many letters wanted
	int letters = 0;
	scanf("%d", &letters);
	if ((letters + characterCount) > length) {
		printf("Error incorect input, please pick a number of %d or less\n", length);
		scanf("%d", &letters);
	}
	characterCount += letters;

	// Count to track how many uppercase letters wanted
	int upper = 0;

	// If the user wanted more than 0 letters, the dialog for uppercase letters will show
	if (characterCount != 0) {
		if (letters > 0) {
			printf("How many should be uppercase? ");
			scanf("%d", &upper);
			if (upper > letters) {
				printf("Error incorect input, please pick a number of %d or less\n", letters);
				scanf("%d", &upper);
			}
		}
	}

	// Count to track how many numbers wanted
	int numbers = 0;

	// If the user did not account for the password to be all letters, then the dialog for numbers will show
	if (characterCount < length) {
		printf("How many should be numbers? ");
		scanf("%d", &numbers);
		if ((numbers + characterCount) > length) {
			printf("Error incorect input, please pick a number of %d or less\n", (length - characterCount));
			scanf("%d", &numbers);
		}
		characterCount += numbers;
	}

	// Count to track how many special characters needed
	int special = 0;

	// If the user's password still has "space" for more characters, this dialog will run
	if (characterCount != length) {
		printf("Special characters will fill the rest of the password: ");
		special = length - characterCount;
		printf("%d\n", special);
		characterCount += special;
	}

	int index = 0;
	char pass[50];
	while (index < length) {
		pass[index] = 0;
		index++;
	}
	index = 0;
	int tempUpper = upper;
	while (tempUpper > 0) {
		// upper case ascii is from 65-90
		int character = rand() % (90 + 1 - 65) + 65;
		char c = character;
		pass[index] = c;
		tempUpper--;
		index++;
	}
	tempUpper = upper;
	while ((letters - tempUpper) > 0) {
		// lower case ascii is from 97-122
		int character = rand() % (122 + 1 - 97) + 97;
		char c = character;
		pass[index] = c;
		tempUpper++;
		index++;
	}
	while (numbers > 0) {
		// number ascii is from 48-57
		int character = rand() % (57 + 1 - 48) + 48;
		char c = character;
		pass[index] = c;
		numbers--;
		index++;
	}
	while (special > 0) {

		// Special ascii is from 33-47, 58-64, 91-96, 123-126
		// 4 ranges are possible
		// Randomly get one of the ranges
		int set = rand() % 4 + 1;
		int character = 0;

		// Depending on which range, generates a character
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
	// Shuffle array so password is randomized
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

	// Option to save the generated password for a website
	puts("Press 1 to save this password for a website");
	puts("Press 0 to return to the menu");
	int save = 0;
	scanf("%d", &save);
	if (save == 1) {
		savePassword(passwordFile, pass);
	}
}

/**
	Method that saves a password to the "password.txt" file to the user's specified file path
**/
void savePassword(FILE* passwordTXT, char pass[50]) {
	char website[50] = { 0 };
	printf("What is the website's URL?:\n");
	scanf("%s", website);

	// Check contents of password to see if it is prefilled or empty
	for (int i = 0; i < 50; i++) {
		if (pass[i] != 0) {
			// it isn't empty, don't need to ask for password
			break;
		}
		else if (i == 49) {
			// iterated and had all 0's therefore empty password
			printf("What is the website's password?:");
			scanf("%s", pass);
		}
	}

	// Writes the generated password to the file path
	passwordTXT = fopen(passwordFile, "a");
	fprintf(passwordTXT, "Website: %s\n", website);
	fprintf(passwordTXT, "Password: %s\n", pass);
	fprintf(passwordTXT, "-------------------------\n");
	fclose(passwordTXT);
	puts("Combination saved");
	puts("-------------------------");
}

/**
	Method that exports the file to the specified file path
**/
void export(FILE* passwordFile) {
	puts("Your file is titled passwords.txt and contains all combinations");
	printf("It's file path is: %s\n", passwordFile);
}

void printMenu() {
	printf("\nPress 1 for generating a new password on its own\n");
	printf("Press 2 for saving a new website and password combination\n");
	printf("Press 3 for exporting your combinations to a file\n");
	printf("Press 4 to display your password and website combinations\n");
	printf("Press 5 to exit\n");
}

/**
	Method that sets the instance char arrays to the specified file path's required files so it's easily accessible
**/
void setFiles() {
	// Placing the file path for userInfo.txt into char array: userFile
	char userInfoTxt[13] = "/userInfo.txt";
	strncpy(userFile, filePath, sizeof(filePath));
	int fileLength = strlen(userFile);
	for (int i = 0; i < 13; i++) {
		userFile[fileLength + i] = userInfoTxt[i];
	}

	// Placing the path for passwords.txt into charr array: passwordFile
	char passwordTxt[14] = "/passwords.txt";
	strncpy(passwordFile, filePath, sizeof(filePath));
	fileLength = strlen(passwordFile);
	for (int i = 0; i < 14; i++) {
		passwordFile[fileLength + i] = passwordTxt[i];
	}
}

/**
	Method that displays the password combinations from the "password.txt" file in the specified file path
**/
void display(FILE* passwordTXT) {

	printf("\n\nCurrrent Account Password Combinations\n");
	char ch;
	passwordTXT = fopen(passwordFile, "r");
	while ((ch = fgetc(passwordTXT)) != EOF) {
		printf("%c", ch);
	}
	fclose(passwordTXT);
	printf("");
}

/**
	Method that verified the username and password of the user to ensure security
**/
int verification() {

	//file with username and password
	FILE* userInfo;
	userInfo = fopen(userFile, "r");

	//username and password strings from file
	char fileUserName[20] = { 0 };
	char filePassword[20] = { 0 };

	char ch;
	int index = 0;

	//flag to switch from writing into fileUserName to filePassword
	int switchToPassword = 0;

	while ((ch = fgetc(userInfo)) != EOF) {
		if (ch == '\n') {
			//the file has an enter, that means the password now needs to be read
			switchToPassword = 1;
			index = 0;
			//skip the /n character
			ch = fgetc(userInfo);
		}
		if (switchToPassword == 0) {
			//write into username
			fileUserName[index] = ch;
		}
		else {
			//write into password
			filePassword[index] = ch;
		}
		index++;
	}
	fclose(userInfo);

	//strings for user inputted username and password
	char inputtedUsername[10] = { 0 };
	char inputtedPassword[10] = { 0 };
	//number of tries to enter password
	int tries = 3;
	printf("\n---------- Login ----------\n");
	//flags to determine if the user has been verified
	int bothVerified = 0;
	int usernameVerified = 0;
	int passwordVerified = 0;

	//loop to check equality of user input and user information file
	while (bothVerified == 0) {
		while (usernameVerified == 0) {
			printf("\nEnter your username:\n");
			scanf("%s", inputtedUsername);
			for (int i = 0; i < 10; i++) {
				char f = fileUserName[i];
				char in = inputtedUsername[i];
				if (f != in) {
					puts("Incorrect Username, try again\n");

					//reset inputterUsername
					for (int j = 0; j <= i; j++) {
						inputtedUsername[j] = 0;
					}
					break;
				}
				else if (i == 9) {
					usernameVerified = 1;
				}
			}
		}
		if (usernameVerified == 1) {
			while (passwordVerified == 0) {

				//passed the username section now onto password verification
				printf("\nEnter your password:\n");
				scanf("%s", inputtedPassword);
				for (int i = 0; i < 10; i++) {
					char f = filePassword[i];
					char in = inputtedPassword[i];
					if (f != in) {
						tries--;

						//reset inputtedPassword
						for (int j = 0; j <= i; j++) {
							inputtedPassword[j] = 0;
						}
						if (tries > 0) {
							printf("Incorrect Password, %d tries left\n", tries);
						}
						else {
							puts("Incorrect Password, you have run out of tries, come back later\n");
							//whole program needs to be ended, the user is locked out
							return 0;
						}
						break;
					}
					else if (i == 9) {
						passwordVerified = 1;
					}
				}
			}
		}
		if (usernameVerified == 1 && passwordVerified == 1) {
			//to break out of loop
			bothVerified = 1;
			puts("\nCorrect, logged in\n");
			puts("-------------------------");
		}
	}
	return 1;
	// Verified
}
