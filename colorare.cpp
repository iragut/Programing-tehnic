#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

/* Custome function to calculate the power of a number with O(log n) 
complexity and by spefici range (module)*/
long module_power(long base, int exponent, long module) {
    long result = 1;

	while (exponent > 0) {
		if (exponent % 2 == 1) {
			result *= base;
			result %= module;
		}
		base *= base;
		base %= module;
		exponent >>= 1;
	}
    return result;
}

int main() {
	ifstream fin("colorare.in");
	ofstream fout("colorare.out");

	int i;
	long n, number, result = 1;
	long module = pow(10, 9) + 7;
	char character, last_character = 0;
	fin >> n;

	// We iterate through the file take the number and the character
	// and calculate the result based on if have horizontal or vertical
	// triangles
	for (i = 0; i < n; i++) {
		fin >> number;
		fin >> character;
		if (character == 'H') {
			if (last_character == 0) {
				result *= 2 * module_power(3, number, module);
			} else if (last_character == 'H') {
				result *= module_power(3, number, module);
			} else {
				result *= 2 * module_power(3, number - 1, module);
			}
		} else if (character == 'V') {
			if (last_character == 0) {
				result *= 3 * module_power(2, number - 1, module);
			} else if (last_character == 'H') {
				result *= module_power(2, number - 1, module);
			} else {
				result *= module_power(2, number, module);
			}
		}
		last_character = character;
		result %= module;
	}

	fout << result << "\n";

	fin.close();
	fout.close();
	return 0;
}
