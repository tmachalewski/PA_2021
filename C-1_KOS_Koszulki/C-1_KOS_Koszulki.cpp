// C-1_KOS_Koszulki.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

#define CERR_NEEDED false

int const MAX_POINTS = 120;
int const MAX_POINTS_BUFFER = MAX_POINTS + 1;

int main()
{
    int n, k;
    cin >> n >> k;

    int countOfPlayersWithGivenPoints[MAX_POINTS_BUFFER]{};
    int processedPlayer = 0;
    for (int i = 0; i < n; i++) {
        cin >> processedPlayer;
        countOfPlayersWithGivenPoints[processedPlayer]++;
    }

    int freeShirts = k;
    for(int i = MAX_POINTS; i > 0; --i) {
        if (freeShirts <= 0) break;
        freeShirts -= countOfPlayersWithGivenPoints[i];
    }

    //this is wrong -> "no abs(freeShirst) because you dont have to use all shirst for all players"
    //task states, that k<=n
    int neededShirts = k - freeShirts; 
    cout << neededShirts;
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
