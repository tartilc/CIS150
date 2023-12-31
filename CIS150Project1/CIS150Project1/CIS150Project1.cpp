#include "stdafx.h"
/*
*Author: Tartil Chowdhury – CIS150
*Creation Date: 4/19/2017
*Modification Date: 4/19/2017
*Purpose: airline seat reservation system
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void readseatArray(ifstream&, int[], char[][4]);
void displayseatArray(int[], char[][4]);
void reserveSeat(ofstream&, int[], char[][4], int, int);
void cancelseatReservation(ofstream&, int[], char[][4], int, int, char);
void saveseatArray(ofstream&, const string, int[], char[][4]);
void showStats(char[][4]);
void showHelp();

int main() {
	int choice = 0;
	int row;
	char column;

	string outputFile;

	char seatArray[10][4];
	int rows[10];

	ifstream input;
	ofstream output;

	readseatArray(input, rows, seatArray);

	do {
		cout << "------------------------ Menu ---------------------------" << endl << endl;
		cout << "1. Display Seat Chart" << endl;
		cout << "2. Reserve Seat" << endl;
		cout << "3. Cancel Reservation" << endl;
		cout << "4. Save Seat Chart to File" << endl;
		cout << "5. Statistics" << endl;
		cout << "6. Help" << endl;
		cout << "7. Quit" << endl << endl;
		cout << "---------------------------------------------------------" << endl << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			displayseatArray(rows, seatArray);

			system("pause");
			system("cls");
			break;

		case 2:
			displayseatArray(rows, seatArray);

			while (true) {
				cout << "Choose a row (1-10): ";
				cin >> row;

				if (row >= 1 && row <= 10) {
					break;
				}
				else {
					cout << "Invalid input." << endl;
				}
			}

			while (true) {
				cout << "Choose a column (A-D): ";
				cin >> column;
				if (toupper(column) == 'A' || toupper(column) == 'B' || toupper(column) == 'C' || toupper(column) == 'D' || toupper(column) == 'Z')
				{
					break;
				}
				else {
					cout << "Invalid input." << endl;
				}
			}

			switch (toupper(column)) {
			case 'A':
				reserveSeat(output, rows, seatArray, row -= 1, 0);
				break;
			case 'B':
				reserveSeat(output, rows, seatArray, row -= 1, 1);
				break;
			case 'C':
				reserveSeat(output, rows, seatArray, row -= 1, 2);
				break;
			case 'D':
				reserveSeat(output, rows, seatArray, row -= 1, 3);
				break;
			}

			system("pause");
			system("cls");
			break;

		case 3:
			displayseatArray(rows, seatArray);

			while (true) {
				cout << "Enter the row (1-10): ";
				cin >> row;

				if (row >= 1 && row <= 10)
				{
					break;
				}
				else {
					cout << "Invalid input." << endl;
				}
			}

			while (true) {
				cout << "Select a column (A-D): ";
				cin >> column;

				if (toupper(column) == 'A' || toupper(column) == 'B' || toupper(column) == 'C' || toupper(column) == 'D' || toupper(column) == 'Z')
				{
					break;
				}
				else {
					cout << "Invalid input." << endl;
				}
			}

			switch (toupper(column)) {
			case 'A':
				cancelseatReservation(output, rows, seatArray, row -= 1, 0, 'A');
				break;
			case 'B':
				cancelseatReservation(output, rows, seatArray, row -= 1, 1, 'B');
				break;
			case 'C':
				cancelseatReservation(output, rows, seatArray, row -= 1, 2, 'C');
				break;
			case 'D':
				cancelseatReservation(output, rows, seatArray, row -= 1, 3, 'D');
				break;
			}

			system("pause");
			system("cls");
			break;

		case 4:
			cout << endl << endl << "Enter the filename you would like to save your seat chart to: ";
			cin >> outputFile;

			saveseatArray(output, outputFile, rows, seatArray);

			system("pause");
			system("cls");
			break;

		case 5:
			showStats(seatArray);

			system("pause");
			system("cls");
			break;

		case 6:
			cout << endl << endl;
			showHelp();
			cout << endl << endl;
			system("pause");
			system("cls");
			break;

		case 7:
			break;

		default:
			cout << "Invalid input." << endl << endl;
			break;
		}

	} while (choice != 7);

	system("pause");
	return 0;
}

/*
*Author: Tartil Chowdhury – CIS150
*Creation Date: 4/19/2017
*Modification Date: 4/19/2017
*Purpose: reads the seat array
*/

void readseatArray(ifstream& input, int rows[], char seatArray[][4])
{
	input.open("chartIn.txt");

	for (int i = 0; i < 10; i++)
	{
		input >> rows[i];

		for (int x = 0; x < 4; x++)
		{
			input >> seatArray[i][x];
		}
	}

	input.close();
}

/*
*Author: Tartil Chowdhury – CIS150
*Creation Date: 4/19/2017
*Modification Date: 4/19/2017
*Purpose: displays the seat array
*/

void displayseatArray(int rows[], char seatArray[][4])
{
	cout << endl << endl << "Columns A and D are window seats. Columns B and C are aisle seats. Seats marked with an X have been reserved." << endl << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << rows[i] << ' ';

		for (int x = 0; x < 4; x++)
		{
			cout << seatArray[i][x] << ' ';
		}

		cout << endl;
	}

	cout << endl << endl;
}

/*
*Author: Tartil Chowdhury – CIS150
*Creation Date: 4/19/2017
*Modification Date: 4/19/2017
*Purpose: allows user to reserve seat
*/

void reserveSeat(ofstream& output, int rows[], char seatArray[][4], int row, int col)
{
	output.open("chartIn.txt");

	if (seatArray[row][col] != 'X')
	{
		seatArray[row][col] = 'X';
		cout << "Reserved the seat." << endl;
	}
	else {
		cout << "This seat is already reserved." << endl;
		output.close();
		return;
	}


	for (int i = 0; i < 10; i++)
	{
		output << rows[i] << ' ';

		for (int x = 0; x < 4; x++)
		{
			if (x != 3)
			{
				output << seatArray[i][x] << ' ';
			}
			else {
				output << seatArray[i][x];
			}
		}

		if (i != 9) {
			output << endl;
		}

	}

	output.close();
}

/*
*Author: Tartil Chowdhury – CIS150
*Creation Date: 4/19/2017
*Modification Date: 4/19/2017
*Purpose: allows user to cancel a seat reservation
*/

void cancelseatReservation(ofstream& output, int rows[], char seatArray[][4], int row, int column, char replacement) {

	output.open("chartIn.txt");

	if (seatArray[row][column] == 'X')
	{
		seatArray[row][column] = replacement;

		for (int i = 0; i < 10; i++)
		{
			output << rows[i] << ' ';

			for (int x = 0; x < 4; x++)
			{
				if (x != 3)
				{
					output << seatArray[i][x] << ' ';
				}
				else {
					output << seatArray[i][x];
				}
			}

			if (i != 9)
			{
				output << endl;
			}
		}

		cout << "Your seat reservation has been cancelled." << endl;

		output.close();
		return;
	}
	else {
		cout << "This seat is not reserved. " << endl;

		output.close();
		return;
	}
}

/*
*Author: Tartil Chowdhury – CIS150
*Creation Date: 4/19/2017
*Modification Date: 4/19/2017
*Purpose: saves the seat array to file
*/

void saveseatArray(ofstream& output, const string fileName, int rows[], char seatArray[][4])
{
	output.open(fileName);

	for (int i = 0; i < 10; i++) {

		output << rows[i] << ' ';

		for (int x = 0; x < 4; x++)
		{
			if (x != 3)
			{
				output << seatArray[i][x] << ' ';
			}
			else {
				output << seatArray[i][x];
			}
		}

		if (i != 9)
		{
			output << endl;
		}
	}

	cout << endl << endl << "Seat chart has been saved to file. " << endl;

	output.close();
}

/*
*Author: Tartil Chowdhury – CIS150
*Creation Date: 4/19/2017
*Modification Date: 4/19/2017
*Purpose: shows statistics about the seat chart
*/

void showStats(char seatArrange[][4])
{
	int availSeats;
	int totalSeats = 40;
	int reservedSeats = 0;
	int aisleSeats = 0;
	int windowSeats = 0;

	float percReservedSeats;

	for (int i = 0; i < 10; i++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (seatArrange[i][y] == 'X')
			{
				reservedSeats++;
			}

			if (seatArrange[i][y] == 'A' || seatArrange[i][y] == 'D')
			{
				windowSeats++;
			}

			if (seatArrange[i][y] == 'B' || seatArrange[i][y] == 'C')
			{
				aisleSeats++;
			}
		}
	}

	availSeats = totalSeats - reservedSeats;
	percReservedSeats = ((float)reservedSeats / (float)totalSeats) * 100;

	cout << endl << endl;
	cout << "Available Seats:          " << availSeats << endl;
	cout << "% of Reserved Seats:      " << percReservedSeats << '%' << endl;
	cout << "Available Window Seats:   " << windowSeats << endl;
	cout << "Available Aisle Seats:    " << aisleSeats;
	cout << endl << endl;
}

/*
*Author: Tartil Chowdhury – CIS150
*Creation Date: 4/19/2017
*Modification Date: 4/19/2017
*Purpose: tells the user how to use the program
*/

void showHelp()
{
	cout << endl << endl;
	cout << "Option 1 displays the current seat chart." << endl;
	cout << "Option 2 allows the user to reserve a seat." << endl;
	cout << "Option 3 allows the user to cancel a seat reservation." << endl << endl;
	cout << "Option 4 saves the current seat chart to a user chosen file." << endl;
	cout << "Option 5 displays statistics about the seat chart" << endl << endl;
	cout << "Option 7 quits out the program.";
	cout << endl << endl;
}
