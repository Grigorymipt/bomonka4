// ConsoleApplication11(ьыег4).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Header.h"

int main()
{
	Polynom p;

	cout << "Making polynom:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		Term<Polynom> t;
		cout << "Enter term: ";
		cin >> t;
		p += t;
		cout << "Polynom 1: " << p << endl << endl;
	}

	cout << "Reversed output:" << endl;
	p.set_order(-1);
	cout << "Polynom 1: " << p << endl << endl;
	p.set_order(1);

	cout << "operator +=:" << endl;
	Polynom p2 = p;
	p2 += Term<Polynom>(3, 2);
	cout << "Polynom 2: " << p2 << endl << endl;
	p2 += p;
	cout << "Polynom 2: " << p2 << endl << endl;

	cout << "operator *:" << endl;
	Polynom p3 = p * p2;
	cout << "Polynom 1 * Polynom 2: " << p3 << endl << endl;

	cout << "operator *=:" << endl;
	p *= p;
	cout << "Polynom 1 *= Polynom 1: " << p << endl << endl;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
