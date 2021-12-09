// C-3_SUM_Sumy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
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

    bool canEatAtLeastOneFish = false;

    vector<Catfish*> fishesWithSameWeight;
    int weightOfSingleFishFromPreviousGroup = 0;
    int weightOfPreviousFish = 0;
    long long weightOfFishesEatableByPreviousGroup = 0;
    for (int i = 0; i < n; ++i) {
        if (weightOfPreviousFish == catfishes[i].weight) {
            fishesWithSameWeight.push_back(&catfishes[i]);
        }
        else {
            long long eatableByThisGroup = weightOfFishesEatableByPreviousGroup + weightOfSingleFishFromPreviousGroup;
            if (canEatAtLeastOneFish) {
                eatableByThisGroup += (fishesWithSameWeight.size()-1)*(long long)fishesWithSameWeight[0]->weight;
            }
            
            for (unsigned int j = 0; j < fishesWithSameWeight.size(); j++) {
                fishesWithSameWeight[j]->weightOfEatableFishes= eatableByThisGroup;
            }

            if (weightOfPreviousFish != 0) {
                weightOfSingleFishFromPreviousGroup = fishesWithSameWeight[0]->weight;
                weightOfFishesEatableByPreviousGroup = fishesWithSameWeight[0]->weightOfEatableFishes;
                canEatAtLeastOneFish = true;
                
            }
            fishesWithSameWeight.clear();
            fishesWithSameWeight.push_back(&catfishes[i]);
        }
        weightOfPreviousFish = catfishes[i].weight;
    }

    //consider last group - could be done in previous loop, if some kind of guard was added
    long long eatableByThisGroup = weightOfFishesEatableByPreviousGroup + weightOfSingleFishFromPreviousGroup;
    if (canEatAtLeastOneFish) {
        eatableByThisGroup += (fishesWithSameWeight.size() - 1) * (long long)fishesWithSameWeight[0]->weight;
    }

    for (unsigned int j = 0; j < fishesWithSameWeight.size(); j++) {
        fishesWithSameWeight[j]->weightOfEatableFishes = eatableByThisGroup;
    }
    weightOfSingleFishFromPreviousGroup = catfishes[0].weight;
    weightOfFishesEatableByPreviousGroup = catfishes[0].weightOfEatableFishes;
    canEatAtLeastOneFish = true;
    //end of consideration of last group

    int weightOfBiggestFish = catfishes.back().weight;

    sort(catfishes.begin(), catfishes.end(), [](Catfish a, Catfish b) {return a.inputIndex < b.inputIndex; });

    //TODO: how to declare "Catfish current;" here?
    for (int i = 0; i < n; i++) {
        Catfish current = catfishes[i];
        if (current.weightOfEatableFishes + current.weight > weightOfBiggestFish) {
            cout << 'T';
        }
        else{
            cout << 'N';
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
