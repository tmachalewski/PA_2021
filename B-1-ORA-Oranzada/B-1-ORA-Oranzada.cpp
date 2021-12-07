// B-1-ORA-Oranzada.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <queue>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    int* wines = new int[n]{};
    unordered_set<int> uniques;
    for (int i = 0; i < n; ++i) {
        cin >> wines[i];
        uniques.insert(wines[i]);
    }

    if (uniques.size() < k) {
        cout << -1;
        return 0;
    }
    
    unordered_set<int> metUniques;
    queue<int> toMove;
    int neededSwaps = 0;
    for (int i = 0; i < n; i++) {
        if (metUniques.find(wines[i]) == metUniques.end()) //is this the first occurance?
        {      
            metUniques.insert(wines[i]);
            if (i > k - 1) // do i need to move this unique to the left part of shelf?
            {
                neededSwaps += (i - toMove.front());
                toMove.pop();
            }
            else if(uniques.size() - metUniques.size() >= k - i) //do i need to push this unique backward to make place for more uniques?
            {
                neededSwaps += (i - toMove.front());
                toMove.pop();
            }
        }
        else {
            if (uniques.size() - metUniques.size() >= i) //will i need to make place for uniques
            {
                toMove.push(i);
            }
            
        }
    }
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
