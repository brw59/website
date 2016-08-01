#include <iostream>
using namespace std;


// simple program to help make multiplication turing machines
int main()
{
	int base = 3;
	cout << "Choose a base to display in: ";
	cin >> base;
	cout << "Choose a carry value to display for (-1 for all): ";
	int targetcarry;
	cin >> targetcarry;
	for(int a = 1; a < base; a++) { //multiplier starts on 1 as 0 does nothing
		for(int b = 0; b < base; b++) { //multiplicand 0 is useful here
			for(int c = 0; c < base; c++) { // product...
				for(int d = 0; d < base; d++) { // the prior carry
					int pro = a * b; // product
					int sum = pro + c + d; // sum (product + sum + carry)
					int car = 0; // the carry created
					while (sum > base - 1) { //base - 1 equals largest number in language
						sum -= base; // chop of the extra
						car++; // and store extra as a carry
					} 
					if (car == targetcarry || targetcarry == -1) { // this if is if you only want to see the result to a specific carry. Useful when putting into JFLAP. 
						if (c == 0) {// this case is for the blank possiblity when the sum is empty (ie the first loop through multiplication step)
							cout << a << ' ' << b << ' ' << "_" << " " << d  << "  " << sum << "  " << car << endl;
						}
						cout << a << ' ' << b << ' ' << c << " "  << d  << "  " << sum << "  " << car << endl;
					}
				}
			}
		}
	}
	
	
}

