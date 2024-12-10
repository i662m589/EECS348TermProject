#include <string>
using namespace std;

double extractNumber(const string& str) {
	double toReturn = 0;
	double multiplier = 0;
	unsigned int length = str.length();
	bool negativeFlag = false;

	try {

		if (str == "" || str == "+" || str == "-") {
			throw 1;
		}

		for (unsigned int i = 0; i < length; i++) {
			char character = str[i];
			switch (character) {
			case '+':
				if (i != 0) {
					throw 1;
				}
				break;
			case '-':
				if (i != 0) {
					throw 1;
				}
				else {
					negativeFlag = true;
				}
				break;
			case '.':
				// If decimal multiplier is not zero (placeholder value), then the number is invalid due to having multiple decimal points.
				if (multiplier != 0.) {
					throw 1;
				}
				else {
					// Shift to decimals
					multiplier = 0.1;
				}
				break;
			default:
				// The default behavior for casting strings to integers is to get the ASCII number, so we use that to get a value from 0-9 as follows:
				double num = (double)character - (double)'0';

				// Check if the character is numeric by checking if it's in the range of 0-9:
				if (num < 0. || num > 9.) {
					throw 1;
				}

				// Differing behavior depending on if pre or post decimal point.
				if (multiplier == 0.) {
					toReturn *= 10.;
					toReturn += num;
				}
				else {
					toReturn += num * multiplier;
					multiplier /= 10.;
				}
				break;
			};
		}
	}
	catch (int err) {
		return -999999.99;
	}

	if (negativeFlag) {
		toReturn *= -1.;
	}

	return toReturn;
}