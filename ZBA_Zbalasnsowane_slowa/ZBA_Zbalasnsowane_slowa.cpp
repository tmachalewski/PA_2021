#include <iostream>
#include <string>
#include <iterator>
using namespace std;

int const ALPHABET_SIZE = 26;

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

	int letterCount[ALPHABET_SIZE]{};

	for (string::size_type i = 0; i < word.size(); i++) {
		letterCount[word[i] - 'a']++;
	}


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

			if (equalNumberOfLetter(partialLetterCount)) {
				correctCounter++;
			}
		}
	}

	cout << correctCounter;
}