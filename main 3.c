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

typedef struct PassWeb PassWeb;
typedef struct display Display;

int generatePassword(void);
int savePassword(FILE*);
int export(FILE*);
void addPassWeb(PassWeb *obj);
PassWeb *checkWebsite(char *website);

Display *passList;

// Structure that saves the website associated with a randomize password
struct PassWeb {
	char password[50];
	char *website;
	char *date;
	PassWeb *next;
};

// Structure that acts like a linked list to save all the passwords generated for each website given by the user
struct display {
	int size;
	PassWeb *head;
};

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
	while (input < 1 || input > 3) {
		printf("Error incorect input, please pick a number from 1 to 3");
		scanf("%d", &input);
	}

	//Initializing the list of passwords and websited that will be used to display for users
	passList->size = 0;
	passList->head = NULL;

	//case 1: generating a new password on its own
	if (input == 1) {
		generatePassword();
	}
	//case 2: saving a new website and password combination
	else if (input == 2) {
		savePassword(passwordFile);
	}
	//case 3: exporting your combinations to a file
	else {
		export(passwordFile);
	}

	return 0;
}

int generatePassword() {
	printf("How many characters total would you like your password to be? You can generate up to a max of 50 length");
	int length = 0;
	scanf("%d", &length);
	while (length < 1) {
		printf("Error incorect input, please pick a number greater than 0");
		scanf("%d", &length);
	}
	while (length > 50) {
		printf("Error incorect input, please pick a number less than 50");
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

	printf("How many should be uppercase? ");
	int upper = 0;
	scanf("%d", &upper);
	if (upper > letters) {
		printf("Error incorect input, please pick a number less than the number of letters desired");
		scanf("%d", &upper);
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
		//special ascii is from 33 - 47
		int character = rand() % (47 + 1 - 33) + 33;
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
	puts("Press 1 to save this password for a website.");
	int save = 0;
	scanf("%d", &save);
	if (save == 1) {
		PassWeb *obj;	// = (PassWeb *)malloc(sizeOf(PassWeb));

		// Saving the (Current) date the password was saved
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		char *cdate = (tm.tm_mon+1) + '/' + (tm.tm_mday) + '/' + (tm.tm_year + 1900);
		
		obj->next = NULL;
		obj->date = cdate;
		strcpy(obj->password, pass);
		char *website;
		put("Pase the website url below.\n");
		scanf("%s", website);
	
		// Adding new PassWeb object to saved list of passwords/websites
		addPassWeb(obj);
	}

	return 0;
}

int savePassword(FILE* passwordFile) {
	char *website;
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

int export(FILE* passwordFile) {
	puts("Your file is titled passwords.txt and contains all combinations");
	return 0;
}

/**
	Method that adds a PassWeb object to a "display" list of all user saved passwords for websites
**/
void addPassWeb(PassWeb *obj) {
	if (passList->head == NULL) {
		passList->size = 1;
		passList->head = obj;
	}
	else {

		// PassWeb object that is either null if the website has never been used, and an actual object that was previously initialized with the given website
		PassWeb *object = checkWebsite(obj->website);

		// If the website was never in the passList, add given object
		if (object == NULL) {
			PassWeb *current = passList->head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = obj;
			passList->size++;
		}

		// If the website in the passList, update the password if the user wants
		else {
			put("The website entered has previously been used for another password, enter 1 to update it.");
			int update;
			scanf("%d", &update);
			if (update == 1) {
			
				// Updating the PassWeb object attached to the given website with the current date and password
				strcpy(object->password, obj->password);

				time_t t = time(NULL);
				struct tm tm = *localtime(&t);
				object->date = (tm.tm_mon + 1) + '/' + (tm.tm_mday) + '/' + (tm.tm_year + 1900);
			}
		}
	}
}

/**
	Method that checks the list of PassWeb objects to return if the given website is already linked with a password
	Returns NULL if website is NOT in the list, PassWeb object if the website IS in the list
**/
PassWeb *checkWebsite(char *website) {
	PassWeb *current = passList->head;
	while (current->next != NULL) {

		// If a website in passList matches the one given, the PassWeb object associated will be returned
		if (current->website == website) {
			return current;
			break;
		}
		current = current->next;
	}
	return NULL;
}