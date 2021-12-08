// B-2_PAN_Pandemia.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <deque>
using namespace std;

bool sortByFirstDesc(const pair<int, int>& a, const pair<int, int>& b)
{
    return (a.first > b.first);
}

int solveTest() {
    int n;
    cin >> n;

    //k: v - size of healthy city group: number of such groups 
    unordered_map<int, int> map_cities1; //bordered by 1 sick city //possibly some 0 size groups of sick city
    unordered_map<int, int> map_cities2; //bordered by 2 sick cities //possibly some 0 size groups of sick city

    bool spreadingFromLeft = false;
    char currentCity;
    int sizeOfGroup = 0;
    int SPECIAL_CASE_SIZE_OF_LEFT_BORDER_GROUP = -1;
    int SPECIAL_CASE_SIZE_OF_RIGHT_BORDER_GROUP;
    for (int i = 0; i < n; i++) {
        cin >> currentCity;
        if (currentCity == '0') {
            sizeOfGroup++;
        }
        else {
            //met sick city
            if (spreadingFromLeft) {
                map_cities2[sizeOfGroup]++;
            }
            else {
                map_cities1[sizeOfGroup]++;
                SPECIAL_CASE_SIZE_OF_LEFT_BORDER_GROUP = sizeOfGroup;
            }
            spreadingFromLeft = true;
            sizeOfGroup = 0;
        }
    }

    //below works for not infected country and unended group 
    map_cities1[sizeOfGroup]++;
    SPECIAL_CASE_SIZE_OF_RIGHT_BORDER_GROUP = sizeOfGroup;
    

    //0 size groups - sick cities - erase them
    map_cities1.erase(0);
    map_cities2.erase(0);

    //transforming to vec for sorting
    vector<pair<int, int>> vec_cities1 = vector<pair<int, int>>(map_cities1.begin(),map_cities1.end());
    vector<pair<int, int>> vec_cities2 = vector<pair<int, int>>(map_cities2.begin(), map_cities2.end());

    //left for possible future use: //sort(vec_cities1.begin(), vec_cities1.end(), sortByFirstDesc);

    sort(vec_cities1.begin(), vec_cities1.end());
    sort(vec_cities2.begin(), vec_cities2.end());

    deque<pair<int, int>> deq_cities1 = deque<pair<int, int>>(vec_cities1.begin(), vec_cities1.end());
    deque<pair<int, int>> deq_cities2 = deque<pair<int, int>>(vec_cities2.begin(), vec_cities2.end());
    deque<pair<int, int>> werePartialyQuarantined;

    int savedCities = 0;
    int daysPassed=0;
    int SPECIAL_CASE = 0;
    while (!deq_cities1.empty() || !deq_cities2.empty()||!werePartialyQuarantined.empty()) {
        
        //possible candidates for vacination for
        pair<int, int> fullQuarantine;
        pair<int, int> partialQuarantine;
        pair<int, int> ongoingQuarantine;
        
        if (!deq_cities1.empty()) {
            fullQuarantine = deq_cities1.back();
        }
               
        if (!deq_cities2.empty()) {
            partialQuarantine = deq_cities2.back();
        }

        if (!werePartialyQuarantined.empty()) {
            ongoingQuarantine = werePartialyQuarantined.back();
        }

        if (fullQuarantine.first - daysPassed  >= partialQuarantine.first - 2*daysPassed) {
            if (fullQuarantine.first - daysPassed >= ongoingQuarantine.first - daysPassed) {
                savedCities += fullQuarantine.first - daysPassed;
                fullQuarantine.second--;
                if (SPECIAL_CASE_SIZE_OF_LEFT_BORDER_GROUP == SPECIAL_CASE_SIZE_OF_RIGHT_BORDER_GROUP) {
                    SPECIAL_CASE++;
                }
                deq_cities1.pop_back();
                if (fullQuarantine.second > 0) {
                    deq_cities1.push_back(make_pair(fullQuarantine.first, fullQuarantine.second));
                }
            }
            else {
                savedCities += ongoingQuarantine.first - daysPassed;
                werePartialyQuarantined.pop_back();
            }
            
        }
        else {
            if (partialQuarantine.first - daysPassed >= ongoingQuarantine.first - daysPassed)
            {
                //quarantine this city group from 1 side, making it cities1
                partialQuarantine.second--;
                deq_cities2.pop_back();
                if (partialQuarantine.second > 0) {
                    deq_cities2.push_back(make_pair(partialQuarantine.first, partialQuarantine.second));
                }
                //magic equation: partialQuarantine.first - daysPassed
                //it should be -2*daysPassed, but then we would have to remember when quarantine occured
                //this way when we check which city we should vacinate
                //we can subract from ongoingquarantine daysPassed and it is coherent
                werePartialyQuarantined.push_back(make_pair(partialQuarantine.first - daysPassed, 1));
            }
            else {
                savedCities += ongoingQuarantine.first - daysPassed;
                werePartialyQuarantined.pop_back();
            }
            
        }

        //move to next day
        daysPassed++;
        while (!deq_cities1.empty() && deq_cities1.front().first <= daysPassed)
        {
            savedCities += deq_cities1.front().second;
            if (deq_cities1.front().first == SPECIAL_CASE_SIZE_OF_LEFT_BORDER_GROUP) savedCities--;
            if (deq_cities1.front().first == SPECIAL_CASE_SIZE_OF_RIGHT_BORDER_GROUP) savedCities--;
            if (SPECIAL_CASE_SIZE_OF_LEFT_BORDER_GROUP == SPECIAL_CASE_SIZE_OF_RIGHT_BORDER_GROUP) {
                savedCities += SPECIAL_CASE;
            }
            deq_cities1.pop_front();
            
        }
        while (!deq_cities2.empty() && deq_cities2.front().first <= 2*daysPassed)
            deq_cities2.pop_front();
        while (!werePartialyQuarantined.empty() && werePartialyQuarantined.front().first <= daysPassed)
        {
            savedCities+= werePartialyQuarantined.front().second;
            werePartialyQuarantined.pop_front();
        }
    }   

    return n-savedCities;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cout << solveTest() << endl;
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
