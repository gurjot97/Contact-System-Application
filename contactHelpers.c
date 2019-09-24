/* -------------------------------------------
Name: Gurjot Saini
Student number: 035 053 156
Email: gssaini15@myseneca.ca
Section: R
Date: 11/22/18
----------------------------------------------
Assignment: 2
Milestone:  4
---------------------------------------------- */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// This source file needs to "know about" the SYSTEM string library functions.
// HINT: The library name is string.h.
//       #include the string.h header file on the next line:
#include <string.h>

// ----------------------------------------------------------
// Include your contactHelpers header file on the next line:
#include "contactHelpers.h"


// ----------------------------------------------------------
// define MAXCONTACTS for sizing contacts array (5):
#define MAXCONTACTS 5


//------------------------------------------------------
// Function Definitions
//------------------------------------------------------

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        function definitions below...            |
// +-------------------------------------------------+

// clearKeyboard:
void clearKeyboard(void)
{
	while (getchar() != '\n'); 
}

// pause:
void pause(void)
{
	printf("%s", "(Press Enter to Continue)");
	clearKeyboard();
}

// getInt:
int getInt(void)
{
	char NL = 'x';
	int inputValue = 0;
	int rc;

	while (NL != '\n') {
		rc = scanf("%d%c", &inputValue, &NL);

		if ((NL != '\n') || (rc != 2)) {
			clearKeyboard();
			printf("%s", "*** INVALID INTEGER *** <Please enter an integer>: ");
		}
	}

	return inputValue;
}

// getIntInRange:
int getIntInRange(int lowerBound, int upperBound)
{
	int isValid = 0;
	int inputValue;

	do {

		inputValue = getInt();

		if (inputValue < lowerBound || inputValue > upperBound) {
			printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", lowerBound, upperBound);
		}
		else {
			isValid = 1;
		}
	} while (isValid != 1);

	return inputValue;
}

// yes:
int yes(void)
{
	char NL = 'x';
	char inputValue;
	int isValid = 0;
	int returnValue;

	char errorMessage[] = "*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ";

	while (isValid != 1) {
		scanf("%c%c", &inputValue, &NL);

		if (NL != '\n') {
			clearKeyboard();
			printf("%s", errorMessage);
		}
		else if ((inputValue == 'y') || (inputValue == 'Y')) {
			returnValue = 1;
			isValid = 1;
		}
		else if ((inputValue == 'n') || (inputValue == 'N')) {
			returnValue = 0;
			isValid = 1;
		}
		else {
			printf("%s", errorMessage);
		}
	}

	return returnValue;
}

// menu:
int menu(void)
{
	printf("%s\n"
		"%s\n"
		"%s\n"
		"%s\n"
		"%s\n"
		"%s\n"
		"%s\n"
		"%s\n"
		"%s\n"
		"\n"
		"%s",
		"Contact Management System",
		"-------------------------",
		"1. Display contacts",
		"2. Add a contact",
		"3. Update a contact",
		"4. Delete a contact",
		"5. Search contacts by cell phone number",
		"6. Sort contacts by cell phone number",
		"0. Exit",
		"Select an option:> ");

	return getIntInRange(0, 6);
}

// contactManagerSystem:
void contactManagerSystem(void)
{
	
	struct Contact contacts[MAXCONTACTS] = { 
		
		{ { "Rick", {'\0'}, "Grimes" },						
		{ 11, "Trailer Park", 0, "A7A 2J2", "King City" },		//Contact #1
		{ "4161112222", "4162223333", "4163334444" } },

		{ { "Maggie", "R.", "Greene" },
		{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },		//Contact #2
		{ "9051112222", "9052223333", "9053334444" } },

		{ { "Morgan", "A.", "Jones" },
		{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },	//Contact #3
		{ "7051112222", "7052223333", "7053334444" } },

		{ { "Sasha", {'\0'}, "Williams" },
		{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },		//Contact #4
		{ "9052223333", "9052223333", "9054445555" } },
																//Contact #5 (not initialized)
	};

	int isEnd = 0;
	int userSelection;

	do {

		userSelection = menu();
		printf("\n");

		switch (userSelection) {

		case 0:
			printf("%s", "Exit the program? (Y)es/(N)o: ");
			isEnd = yes();
			printf("\n");

			if (isEnd == 1) {
				printf("%s\n", "Contact Management System: terminated");
			}
			break;

		case 1:
			displayContacts(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;

		case 2:
			addContact(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;

		case 3:
			updateContact(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;

		case 4:
			deleteContact(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;

		case 5:
			searchContacts(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;

		case 6:
			sortContacts(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		}

	} while (isEnd != 1);
}


// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        empty function definitions below...      |
// +-------------------------------------------------+

// getTenDigitPhone:
void getTenDigitPhone(char telNum[])
{
	int needInput = 1;

	while (needInput == 1) {
		scanf("%10s", telNum);
		clearKeyboard();

		// (String Length Function: validate entry of 10 characters AND checkNum() function checks if the char array contains numbers or not)
		if (strlen(telNum) == 10 && checkNum(telNum, MAXCONTACTS))
			needInput = 0;
		else
			printf("Enter a 10-digit phone number: ");
	}
}

int checkNum(const char array[], int size) {

	int isNum = 1;
	int i;
	
	for (i = 0; i < size && isNum; ++i) {

		if (array[i] < 48 || array[i] > 57) {
			isNum = 0;
		}
	}

	return isNum;
}

// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[]) //can double returns work? yes...
{
	int i;
	int isMatch = 0;

	for (i = 0; i < size && isMatch != 1; ++i) {

		if (strcmp(contacts[i].numbers.cell, cellNum) == 0) {
			isMatch = 1;
			return i;
		}
	}

	return -1;
}

// displayContactHeader
void displayContactHeader(void)
{
	printf("%s\n"
		   "%s\n"
		   "%s\n",
		   "+-----------------------------------------------------------------------------+",
		   "|                              Contacts Listing                               |",
		   "+-----------------------------------------------------------------------------+");
}

// displayContactFooter
void displayContactFooter(int totalContacts)
{
	printf("%s\n"
		   "%s%d\n\n",
		   "+-----------------------------------------------------------------------------+",
		   "Total contacts: ", totalContacts);
}

// displayContact:
void displayContact(const struct Contact* contact)
{
	printf(" %s%s%s%s%s\n", contact->name.firstName, 
							" ", 
							strlen(contact->name.middleInitial) > 0 ? contact->name.middleInitial : "",
							strlen(contact->name.middleInitial) > 0 ? " " : "",
							contact->name.lastName);

	printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell,
												   contact->numbers.home,
												   contact->numbers.business);

	printf("       %d %s, ", contact->address.streetNumber, contact->address.street);

	if (contact->address.apartmentNumber > 0) {
		printf("Apt# %d, ", contact->address.apartmentNumber);
	}

	printf("%s, %s\n", contact->address.city, contact->address.postalCode);
}

// displayContacts:
void displayContacts(const struct Contact contacts[], int size)
{
	int i;
	int validNumOfContacts = 0;

	displayContactHeader();

	for (i = 0; i < size; ++i) {

		if (strlen(contacts[i].numbers.cell) > 0) {
			displayContact(&contacts[i]);
			++validNumOfContacts;
		}
	}

	displayContactFooter(validNumOfContacts);
}

// searchContacts:
void searchContacts(const struct Contact contacts[], int size)
{
	char cellPhoneNum[11];
	int matchedIndex;

	printf("%s", 
		   "Enter the cell number for the contact: ");

	getTenDigitPhone(cellPhoneNum);
	matchedIndex = findContactIndex(contacts, size, cellPhoneNum);

	if (matchedIndex != -1) {
		printf("\n");
		displayContact(&contacts[matchedIndex]);
		printf("\n");
	} 
	else {
		printf("%s\n\n", "*** Contact NOT FOUND ***");
	}
}

// addContact:
void addContact(struct Contact contacts[], int size)
{
	int i;
	int isContactSlotEmpty = 0;

	for (i = 0; i < size && isContactSlotEmpty != 1; ++i) {

		if (strlen(contacts[i].numbers.cell) == 0) {

			getContact(&contacts[i]);
			printf("%s\n\n", 
				   "--- New contact added! ---");
			isContactSlotEmpty = 1;
		}
	}

	if (isContactSlotEmpty == 0) {
		printf("%s\n\n", 
			   "*** ERROR: The contact list is full! ***");
	}
	
}

// updateContact:
void updateContact(struct Contact contacts[], int size)
{
	char cellPhoneNum[11];
	int matchedIndex;

	printf("%s",
		"Enter the cell number for the contact: ");

	getTenDigitPhone(cellPhoneNum);
	matchedIndex = findContactIndex(contacts, size, cellPhoneNum);

	if (matchedIndex != -1) {
		printf("\n%s\n", "Contact found:");
		displayContact(&contacts[matchedIndex]);
		printf("\n");

		printf("%s",
			   "Do you want to update the name? (y or n): ");
		if (yes()) {
			getName(&contacts[matchedIndex].name);
		}

		printf("%s",
			   "Do you want to update the address? (y or n): ");
		if (yes()) {
			getAddress(&contacts[matchedIndex].address);
		}

		printf("%s",
			   "Do you want to update the numbers? (y or n): ");
		if (yes()) {
			getNumbers(&contacts[matchedIndex].numbers);
		}

		printf("%s\n\n", "--- Contact Updated! ---");
	}
	else {
		printf("%s\n\n", "*** Contact NOT FOUND ***");
	}
}

// deleteContact:
void deleteContact(struct Contact contacts[], int size)
{
	char cellPhoneNum[11];
	int matchedIndex;

	printf("%s",
		   "Enter the cell number for the contact: ");

	getTenDigitPhone(cellPhoneNum);
	matchedIndex = findContactIndex(contacts, size, cellPhoneNum);

	if (matchedIndex != -1) {
		printf("\n%s\n", "Contact found:");
		displayContact(&contacts[matchedIndex]);
		printf("\n");

		printf("%s",
			"CONFIRM: Delete this contact? (y or n): ");
		if (yes()) {

			contacts[matchedIndex].name.firstName[0] = '\0';
			contacts[matchedIndex].name.middleInitial[0] = '\0';
			contacts[matchedIndex].name.lastName[0] = '\0';

			contacts[matchedIndex].address.streetNumber = 0;
			contacts[matchedIndex].address.street[0] = '\0';
			contacts[matchedIndex].address.apartmentNumber = 0;
			contacts[matchedIndex].address.postalCode[0] = '\0';
			contacts[matchedIndex].address.city[0] = '\0';

			contacts[matchedIndex].numbers.cell[0] = '\0';
			contacts[matchedIndex].numbers.home[0] = '\0';
			contacts[matchedIndex].numbers.business[0] = '\0';

			//Question: Why doesn't this clear out the data?...
			//contacts[matchedIndex] = { 
			//	{ "\0", "\0", "\0" },
			//	{ 0, "\0", 0, "\0", "\0" },
			//	{ "\0", "\0", "\0" } 
			//};

			printf("%s\n", "--- Contact deleted! ---");
		}

		printf("\n");
	}
	else {
		printf("%s\n\n", "*** Contact NOT FOUND ***");
	}
}

// sortContacts:
void sortContacts(struct Contact contacts[], int size)
{
	int i, j, m;
	struct Contact tempContact;

	for (i = 0; i < size; i++) {
		
		m = i;

		for (j = i + 1; j < size; j++) {

			// ((int) contacts[j].numbers.cell) < ((int) contacts[m].numbers.cell)

			if (strcmp(contacts[j].numbers.cell, contacts[m].numbers.cell) < 0 ? 1 : 0) {
				m = j;
			}
		}

		if (m != i) {

			//storing the members of the contact with a lower cell phone number in a temporary contact
			strcpy(tempContact.name.firstName, contacts[i].name.firstName);
			strcpy(tempContact.name.middleInitial, contacts[i].name.middleInitial);
			strcpy(tempContact.name.lastName, contacts[i].name.lastName);

			tempContact.address.streetNumber = contacts[i].address.streetNumber;
			strcpy(tempContact.address.street, contacts[i].address.street);
			tempContact.address.apartmentNumber = contacts[i].address.apartmentNumber;
			strcpy(tempContact.address.postalCode, contacts[i].address.postalCode);
			strcpy(tempContact.address.city, contacts[i].address.city);

			strcpy(tempContact.numbers.cell, contacts[i].numbers.cell);
			strcpy(tempContact.numbers.home, contacts[i].numbers.home);
			strcpy(tempContact.numbers.business, contacts[i].numbers.business);


			//storing the members of the contact with a higher cell phone number in the lower contact
			strcpy(contacts[i].name.firstName, contacts[m].name.firstName);
			strcpy(contacts[i].name.middleInitial, contacts[m].name.middleInitial);
			strcpy(contacts[i].name.lastName, contacts[m].name.lastName);

			contacts[i].address.streetNumber = contacts[m].address.streetNumber;
			strcpy(contacts[i].address.street, contacts[m].address.street);
			contacts[i].address.apartmentNumber = contacts[m].address.apartmentNumber;
			strcpy(contacts[i].address.postalCode, contacts[m].address.postalCode);
			strcpy(contacts[i].address.city, contacts[m].address.city);

			strcpy(contacts[i].numbers.cell, contacts[m].numbers.cell);
			strcpy(contacts[i].numbers.home, contacts[m].numbers.home);
			strcpy(contacts[i].numbers.business, contacts[m].numbers.business);


			//storing the members of the contact with a temporary cell phone number in the higher contact
			strcpy(contacts[m].name.firstName, tempContact.name.firstName);
			strcpy(contacts[m].name.middleInitial, tempContact.name.middleInitial);
			strcpy(contacts[m].name.lastName, tempContact.name.lastName);

			contacts[m].address.streetNumber = tempContact.address.streetNumber;
			strcpy(contacts[m].address.street, tempContact.address.street);
			contacts[m].address.apartmentNumber = tempContact.address.apartmentNumber;
			strcpy(contacts[m].address.postalCode, tempContact.address.postalCode);
			strcpy(contacts[m].address.city, tempContact.address.city);

			strcpy(contacts[m].numbers.cell, tempContact.numbers.cell);
			strcpy(contacts[m].numbers.home, tempContact.numbers.home);
			strcpy(contacts[m].numbers.business, tempContact.numbers.business);
		}
	}

	printf("%s\n\n", "--- Contacts sorted! ---");
}

