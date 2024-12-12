#include <string>
using namespace std;

string Format(const string& input) {
	// Wherever a plus or minus sign is found, add a space on both sides
	string copy = input;
	for (int i = 0; i < (int)copy.size(); i++) {
		char c = copy[i];
		if (c == '+' || c == '-') {
			copy.insert(i + 1, " ");
			copy.insert(i, " ");
			i += 2;
		}
	}

	// For each plus or minus sign, check that there is a number preceding it; if not, add a zero.
	bool lookingForNum = false;
	int opIndex;
	for (int i = copy.size() - 1; i >= 0; i--) {
		char c = copy[i];
		if (c >= '0' && c <= '9') {
			lookingForNum = false;
		} else if (c == '(' && lookingForNum) {
			copy.insert(i + 1, "0");
			lookingForNum = false;
		} else if (c == '+' || c == '-') {
			lookingForNum = true;
			opIndex = i;
		}
	}
	if (lookingForNum) {
		copy = "0 " + copy;
	}

	return copy;
}