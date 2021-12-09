// C-3_SUM_Sumy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
class Catfish {
public:
    int inputIndex;
    int weight;
    long long weightOfEatableFishes;
    Catfish(int inputIndex, int weight) {
        this->inputIndex = inputIndex;
        this->weight = weight;
        this->weightOfEatableFishes = 0;
    }
};
int main()
{
    //TODO: there should be better way of handling first fish and last group
    int n;
    cin >> n;
    vector<Catfish> catfishes;
    int weight;
    for (int i = 0; i < n; i++) {
        cin >> weight;
        catfishes.push_back(Catfish(i, weight));
    }

    sort(catfishes.begin(), catfishes.end(), [](Catfish a, Catfish b) {return a.weight < b.weight; });

    vector<pair<long long, int>> groupCounts;
    int groupCount = 1;
    for (int i = 1; i < n; i++) {
        if (catfishes[i - 1].weight == catfishes[i].weight) {
            groupCount++;
        }
        else {
            groupCounts.push_back(make_pair(catfishes[i - 1].weight, groupCount));
            groupCount = 1;
        }
    }
    groupCounts.push_back(make_pair(catfishes[n - 1].weight, groupCount));
    
    vector<long long> prefixMasses;
    prefixMasses.push_back((long long)groupCounts[0].first * groupCounts[0].second);
    unsigned int j =  0; //nice mistake while trying -1
    for(unsigned int i = 1; i < groupCounts.size(); i++) {
        long long biggestCeratinMass =
            prefixMasses[i - 1];
            
        for (; j < groupCounts.size();) {
            if (j == 0) {
                j = i;
            }
            if (i == j) {
                biggestCeratinMass += groupCounts[j].first * groupCounts[j].second;
                j++;
            }
            else if (biggestCeratinMass > groupCounts[j].first) {
                biggestCeratinMass += groupCounts[j].first* groupCounts[j].second;
                j++;
            }
            else {
                break;
            }
        }
        prefixMasses.push_back(biggestCeratinMass);
    }
    prefixMasses[0] = groupCounts[0].first;
    unordered_map<long long, long long> initialSizeToPotentialSize;
    for (unsigned int i = 0; i < groupCounts.size(); i++) {
        initialSizeToPotentialSize[groupCounts[i].first]= prefixMasses[i];
    }

    //bool canEatAtLeastOneFish = false;
    //bool hasPreviousGroupEatenItself = false;

    //vector<Catfish*> fishesWithSameWeight;
    //int weightOfSingleFishFromPreviousGroup = 0;
    //int weightOfPreviousFish = 0;
    //int sizeOfPreviousGroup = 0;
    //long long weightOfFishesEatableByPreviousGroup = 0;
    //for (int i = 0; i < n; ++i) {
    //    if (weightOfPreviousFish == catfishes[i].weight) {
    //        fishesWithSameWeight.push_back(&catfishes[i]);
    //    }
    //    else {
    //        long long eatableByThisGroup = weightOfFishesEatableByPreviousGroup;
    //        if (hasPreviousGroupEatenItself) {
    //            eatableByThisGroup += weightOfSingleFishFromPreviousGroup;
    //        }
    //        else {
    //            eatableByThisGroup += (long long)weightOfSingleFishFromPreviousGroup * sizeOfPreviousGroup;
    //        }

    //        if (canEatAtLeastOneFish) {
    //            eatableByThisGroup += (fishesWithSameWeight.size() - 1) * (long long)fishesWithSameWeight[0]->weight;
    //            hasPreviousGroupEatenItself = true;
    //        }
    //        
    //        for (unsigned int j = 0; j < fishesWithSameWeight.size(); j++) {
    //            fishesWithSameWeight[j]->weightOfEatableFishes= eatableByThisGroup;
    //        }

    //        if (!fishesWithSameWeight.empty()) {
    //            weightOfSingleFishFromPreviousGroup = fishesWithSameWeight[0]->weight;
    //            weightOfFishesEatableByPreviousGroup = fishesWithSameWeight[0]->weightOfEatableFishes;
    //            sizeOfPreviousGroup = fishesWithSameWeight.size();
    //            canEatAtLeastOneFish = true;
    //        }
    //        fishesWithSameWeight.clear();
    //        fishesWithSameWeight.push_back(&catfishes[i]);
    //    }
    //    weightOfPreviousFish = catfishes[i].weight;
    //}

    ////consider last group - could be done in previous loop, if some kind of guard was added
    //long long eatableByThisGroup = weightOfFishesEatableByPreviousGroup;
    //if (hasPreviousGroupEatenItself) {
    //    eatableByThisGroup += weightOfSingleFishFromPreviousGroup;
    //}
    //else {
    //    eatableByThisGroup += (long long)weightOfSingleFishFromPreviousGroup * sizeOfPreviousGroup;
    //}
    //eatableByThisGroup = weightOfFishesEatableByPreviousGroup + weightOfSingleFishFromPreviousGroup;
    //if (canEatAtLeastOneFish) {
    //    eatableByThisGroup += (fishesWithSameWeight.size() - 1) * (long long)fishesWithSameWeight[0]->weight;
    //    hasPreviousGroupEatenItself = true;
    //}

    //for (unsigned int j = 0; j < fishesWithSameWeight.size(); j++) {
    //    fishesWithSameWeight[j]->weightOfEatableFishes = eatableByThisGroup;
    //}
    //weightOfSingleFishFromPreviousGroup = fishesWithSameWeight[0]->weight;
    //weightOfFishesEatableByPreviousGroup = fishesWithSameWeight[0]->weightOfEatableFishes;
    //sizeOfPreviousGroup = fishesWithSameWeight.size();
    //canEatAtLeastOneFish = true;    
    ////end of consideration of the last group

    int weightOfBiggestFish = catfishes.back().weight;

    sort(catfishes.begin(), catfishes.end(), [](Catfish a, Catfish b) {return a.inputIndex < b.inputIndex; });

    //TODO: how to declare "Catfish current;" here?
    for (int i = 0; i < n; i++) {
        Catfish current = catfishes[i];
        if (initialSizeToPotentialSize[current.weight] > weightOfBiggestFish) {
            cout << "T";
        }
        else{
            cout << "N";
        }
    }
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
