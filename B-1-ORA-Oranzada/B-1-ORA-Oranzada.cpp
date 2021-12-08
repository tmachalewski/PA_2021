// B-1-ORA-Oranzada.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <queue>
#include <unordered_map>
using namespace std;

unsigned long const MAX_WINES = 5 * 100000 + 1;

int main()
{
    unsigned int n, k;
    cin >> n >> k;

    int* wines = new int[n] {};
    unordered_set<int> uniques;
    queue<pair<int, int>> uniquesFirstOccurrence;

    for (unsigned int i = 0; i < n; ++i) {
        cin >> wines[i];
        if (uniques.find(wines[i]) == uniques.end()){
            uniques.insert(wines[i]);
            uniquesFirstOccurrence.push(pair<int,int>(wines[i], i));
        }
    }

    if (uniquesFirstOccurrence.size() < k) {
        cout << -1;
        return 0;
    }
    
    unordered_set<int> metUniques;
    long long neededSwaps = 0;
    for (unsigned int i = 0; i < k; i++) {
        if (metUniques.find(wines[i]) == metUniques.end()) //is this the first occurance?
        {      
            metUniques.insert(wines[i]);
            uniquesFirstOccurrence.pop();
        }
        else {
            pair<int, int> neededUnique = uniquesFirstOccurrence.front();
            uniquesFirstOccurrence.pop();
            metUniques.insert(neededUnique.first);
            neededSwaps += (neededUnique.second - i);
        }
    }
    cout << neededSwaps;
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
