// ZBA_Zbalasnsowane_slowa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iterator>
using namespace std;

int const ALPHABET_SIZE = 26;
#define CERR_NEEDED false

bool equalNumberOfLetter(int counts[ALPHABET_SIZE]) {
	int countOfFirstNonZeroOcurance = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (countOfFirstNonZeroOcurance == 0) {
			countOfFirstNonZeroOcurance = counts[i];
		}
		else {
			if (counts[i] != 0 && counts[i] != countOfFirstNonZeroOcurance) {
				return false;
			}
		}
	}
	return true;
}

int main()
{
	string word;
	cin >> word;
#if CERR_NEEDED
	cerr << "word: " << word;
#endif

	int letterCount[ALPHABET_SIZE]{};

	for (string::size_type i = 0; i < word.size(); i++) {
		letterCount[word[i] - 'a']++;
	}

#if CERR_NEEDED
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (letterCount[i] != 0) cerr << endl << (char)('a' + i) << ": " << letterCount[i];
	}
	cerr << endl << "Full word has corect number of letters: " << equalNumberOfLetter(letterCount);
#endif

	int correctCounter = 0;
	int partialLetterCount[ALPHABET_SIZE];
	for (int substringEnd = word.size() - 1; substringEnd >= 0; substringEnd--) {
		copy(begin(letterCount), end(letterCount), begin(partialLetterCount));
		for (int letterToOmit = word.size() - 1; letterToOmit > substringEnd; letterToOmit--) {
			partialLetterCount[word[letterToOmit] - 'a']--;
		}
		for (int substringStart = 0; substringStart <= substringEnd; substringStart++) {
			if (substringStart > 0) {
				partialLetterCount[word[substringStart - 1] - 'a']--;
			}
#if CERR_NEEDED
			cerr << endl << "evaluated substring: " << word.substr(substringStart, substringEnd - substringStart + 1);
#endif
			if (equalNumberOfLetter(partialLetterCount)) {
				correctCounter++;
#if CERR_NEEDED
				cerr << "+";
#endif
			}
		}
	}
#if CERR_NEEDED
	cerr << endl << "correctCounter: ";
#endif

	cout << correctCounter;
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
