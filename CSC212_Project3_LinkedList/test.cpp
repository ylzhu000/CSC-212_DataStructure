// FILE: newlink.cxx
// An interactive test program for the four new functions of the
// expanded linked list toolkit.
#include <cctype>     // Provides toupper
#include <iostream>   // Provides cout and cin
#include <cstdlib>    // Provides EXIT_SUCCESS and size_t
#include "newnode.h"   // With node::valuetype defined as double
using namespace std;
using namespace main_savitch_5;

// PROTOTYPES for functions used by this test program:
void print_menu();
// Postcondition: A menu of choices for this program has been written to cout.

char get_user_command();
// Postcondition: The user has been prompted to enter a one character command.
// The next character has been read (skipping blanks and newline characters), 
// and this character has been returned.

void show_list(node* display);
// Postcondition: The items on display have been printed to cout (one per line).

double get_number(const char* message);
// Postcondition: The user has been prompted to enter a real number. The
// number has been read, and returned by the function.

size_t get_position(const char* message);
// Postcondition: The user has been prompted to enter a position in the list. The
// number has been read, and returned by the function.


int main()
{
	node* test;      // A list that we'll perform tests on
	char choice;     // A command character entered by the user
	double value;    // A value that is stored on the linked list
	size_t n;        // Argument to list_copy_front
	node* segment;   // Result of call to list_copy_segment

	test = NULL;
	cout << "I have initialized an empty linked list of real numbers." << endl;

	do
	{
		print_menu();
		choice = toupper(get_user_command());
		switch (choice)
		{
		case 'C':
			value = get_number("Type the number to count occurrences of: ");
			cout << "There are " << list_occurrences(test, value);
			cout << " occurrences of " << value << "." << endl;
			break;
		case 'A':
			value = get_number("Type the number to insert: ");
			list_tail_attach(test, value);
			cout << value << " has been inserted." << endl;
			break;
		case 'R':
			list_tail_remove(test);
			cout << " The tail has been removed. " << endl;
			break;
		case 'S':
			n = get_position("Type the amount to copy: ");
			cout << "Here is the result of the copy of that segment: " << endl;
			segment = list_copy_front(test, n);
			show_list(segment);
			list_clear(segment);
			break;
		case 'P':
			cout << "The list has these items: " << endl;
			show_list(test);
			break;
		case 'Q': cout << "Ridicule is the best test of truth." << endl;
			break;
		default:  cout << choice << " is invalid. Sorry." << endl;
		}
	} while (cin && (choice != 'Q'));

	if (!cin)
		cerr << "Bad input character." << endl;

	return EXIT_SUCCESS;
}

void print_menu()
// Library facilities used: iostream.h
{
	cout << endl; // Print blank line before the menu
	cout << "The following choices are available: " << endl;
	cout << " C   Count the number of occurrences of some number" << endl;
	cout << " A   Attach a new number at the tail" << endl;
	cout << " R   Remove a number from the tail" << endl;
	cout << " S   Copy the front of the list, and print this segment" << endl;
	cout << endl;
	cout << " P   Print the current list" << endl;
	cout << " Q   Quit this test program" << endl;
}

char get_user_command()
// Library facilities used: iostream.h
{
	char command;

	cout << "Enter choice: ";
	cin >> command; // Input of characters skips blanks and newline character

	return command;
}

void show_list(node* display)
// Library facilities used: iostream.h
{
	while (display != NULL)
	{
		cout << display->data() << endl;
		display = display->link();
	}
}

double get_number(const char* message)
// Library facilities used: iostream.h
{
	double result;

	cout << message;
	cin >> result;
	return result;
}

size_t get_position(const char* message)
// Library facilities used: iostream.h, stdlib.h
{
	size_t result;

	cout << message;
	cin >> result;
	return result;
}