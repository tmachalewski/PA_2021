// C-2_ZAK_Zaklocenia.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>

using namespace std;

void printCharNTimes(char c, long long n) {
    for (long long i = 0; i < n; i++) cout << c;
}

void printSolution(long long a, long long c, long long g, long long o) {
    cout << string(a, 'a');
    cout << string(c, 'c');
    cout << string(g, 'g');
    cout << string(o, 'o');
}

int main()
{
    long long n; //note, n>0
    cin >> n;
    string str;
    cin >> str;
    long long zeroes = 0, ones = 0;
    for(long long i = 0; i < 8*n; ++i) {
        if (str[i] == '0') zeroes++;
        else ones++;
    }

    
    //all usable ASCIIs start with 011 - we must use them anyway 
    zeroes -= n;
    ones -= 2 * n;
        
    // there are not avaialable ascii letters that dont have at least one '0' or '1'
    // divisibility by 5 is required by 
    // Wolfram's solution
    // it should be possible to limit to non-negative integers
    // https://www.wolframalpha.com/input/?i=4a%2B3c%2B2f%2Bo%3D%3DX%2C+1a%2B2c%2B3f%2B4o%3D%3DY+solve+for+a%2Cc%2Cf%2Co
    if (zeroes <= 0 || ones <= 0 
        || ((4 * zeroes - ones)%5!=0 && (-3 * zeroes + 2 * ones) %5!=0)) {
        cout << "NIE";
        return 0;
    }
    
    //below letters are representative of different groups, each having different numbers of '1's and 'o's in their representation
    long long a, c, g, o;
    long long maxNumberOfG = (4 * zeroes - ones) / 5;
    long long minNumberOfO = (-3 * zeroes + 2 * ones) / 5;
    for (a = 0; a <= n; ++a) {
        if (maxNumberOfG < 0) continue;
        if (minNumberOfO + 2*n < 0) continue;
        c = max(0LL, -minNumberOfO - 2 * a);
        for (; c + a <= n; ++c) {
            g = maxNumberOfG - 3 * a - 2 * c;
            o = minNumberOfO + 2 * a + c; // => 0 - minNumberOfO -  2 * a = c;
            if (o < 0) continue; //we could use this to start from bigger c or a
            if (g < 0 || o + a + c>n) break;
            if (a + c + g + o == n) {
                printSolution(a, c, g, o);
                return 0;
            }
        }
    }
    cout << "NIE";
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
