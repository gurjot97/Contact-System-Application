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

// +-------------------------------------------------+
// | NOTE:  Include additional header files...       |
// +-------------------------------------------------+
#include "contacts.h"
#include "contactHelpers.h"


// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        source code below...                     |
// +-------------------------------------------------+

// getName:
void getName(struct Name *name) {

	printf("%s", "Please enter the contact's first name: ");
	scanf("%30[^\n]", name->firstName);
	clearKeyboard();

	printf("%s", "Do you want to enter a middle initial(s)? (y or n): ");

	if (yes()) {
		printf("%s", "Please enter the contact's middle initial(s): ");
		scanf("%6[^\n]", name->middleInitial);
		clearKeyboard();
	}
	else {
		name->middleInitial[0] = '\0';
	}

	printf("%s", "Please enter the contact's last name: ");
	scanf("%35[^\n]", name->lastName);
	clearKeyboard();
}


// getAddress:
void getAddress(struct Address *address) {

	int tempVal = 0;

	printf("%s", "Please enter the contact's street number: ");

	while (tempVal <= 0) {
		tempVal = getInt();

		if (tempVal <= 0) {
			printf("%s", "Please enter the contact's street number: ");
		//	printf("%s", "*** INVALID STREET NUMBER *** <must be a positive number>: ");
		}
	}
	address->streetNumber = tempVal;

	printf("%s", "Please enter the contact's street name: ");
	scanf("%40[^\n]", address->street);
	clearKeyboard();

	printf("%s", "Do you want to enter an apartment number? (y or n): ");

	if (yes()) {
		tempVal = 0;

		printf("%s", "Please enter the contact's apartment number: ");

		while (tempVal <= 0) {
			tempVal = getInt();

			if (tempVal <= 0) {
				printf("%s", "Please enter the contact's apartment number: ");
			//	printf("%s", "*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");
			}
		}
		address->apartmentNumber = tempVal;
	}
	else {
		address->apartmentNumber = 0;
	}

	printf("%s", "Please enter the contact's postal code: ");
	scanf("%7[^\n]", address->postalCode);
	clearKeyboard();

	printf("%s", "Please enter the contact's city: ");
	scanf("%40[^\n]", address->city);
	clearKeyboard();
}


// getNumbers:s
void getNumbers(struct Numbers *numbers) {

	printf("%s", "Please enter the contact's cell phone number: ");
	getTenDigitPhone(numbers->cell);

	printf("%s", "Do you want to enter a home phone number? (y or n): ");

	if (yes()) {
		printf("%s", "Please enter the contact's home phone number: ");
		getTenDigitPhone(numbers->home);
	}
	else {
		numbers->home[0] = '\0';
	}

	printf("%s", "Do you want to enter a business phone number? (y or n): ");

	if (yes()) {
		printf("%s", "Please enter the contact's business phone number: ");
		getTenDigitPhone(numbers->business);
	}
	else {
		numbers->business[0] = '\0';
	}
}

// getContact
void getContact(struct Contact* contact)
{
	getName(&contact->name);
	getAddress(&contact->address);
	getNumbers(&contact->numbers);
}