// A-5_BUT_Butelki.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

//equals and hashcode from https://thispointer.com/how-to-use-unordered_set-with-user-defined-classes-tutorial-example/
class State {
public:
    int bottle[3];

    const bool operator==(const State& otherPoint) const
    {
        if (this->bottle[0] == otherPoint.bottle[0] 
            && this->bottle[1] == otherPoint.bottle[1]
            && this->bottle[2] == otherPoint.bottle[2])
            return true;
        else return false;
    }
};

namespace std
{
    template<> struct hash<State>
    {
        size_t operator()(const State& obj) const
        {
            size_t hashZero = std::hash<int>()(obj.bottle[0]);
            size_t hashOne = std::hash<int>()(obj.bottle[1]) << 1;
            size_t hashTwo = std::hash<int>()(obj.bottle[2]) << 2; //TODO: i wonder, if this is bit shift and if it doesnt lose data here
            return hashZero ^ hashOne ^ hashTwo;
        }
    };
}

int main()
{
    State cappacity;
    cin >> cappacity.bottle[0] >> cappacity.bottle[1] >> cappacity.bottle[2];

    State start;
    cin >> start.bottle[0] >> start.bottle[1] >> start.bottle[2]; 

    int n = cappacity.bottle[2]+1;
    long long* minNumberOfMoves = new long long[n];
    fill_n(minNumberOfMoves, n, -1);
    int stillToBeFound = n;

    unordered_set<State> reachedStates;
    vector<State>* statesToBeEvaluated = new vector<State>;
    vector<State>* visibleStates = new vector<State>;
    visibleStates->push_back(start);
    long long moveNo = 0;

    reachedStates.insert(start);
    minNumberOfMoves[start.bottle[0]] = moveNo;
    minNumberOfMoves[start.bottle[1]] = moveNo;
    minNumberOfMoves[start.bottle[2]] = moveNo;
    stillToBeFound -= 3;

    while (!visibleStates->empty()) {
        vector<State>* swapTemp;
        swapTemp = statesToBeEvaluated;
        statesToBeEvaluated = visibleStates;
        visibleStates = swapTemp;
        visibleStates->clear();

        moveNo++;

        while (!statesToBeEvaluated->empty()) {
            State current = statesToBeEvaluated->back();
            statesToBeEvaluated->pop_back();

            //Move whatever is possible from j to i
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i != j) {
                        int liquidInIandJ = current.bottle[i] + current.bottle[j];
                        int indexOfNotUsedBottle = 0 + 1 + 2 - i - j;
                        State possiblyNewState;

                        possiblyNewState.bottle[i]=min(cappacity.bottle[i], liquidInIandJ);
                        possiblyNewState.bottle[j] = liquidInIandJ - possiblyNewState.bottle[i];
                        possiblyNewState.bottle[indexOfNotUsedBottle]= current.bottle[indexOfNotUsedBottle];
                        
                        if (reachedStates.find(possiblyNewState)==reachedStates.end()) {
                            //not seen before
                            reachedStates.insert(possiblyNewState);

                            if (minNumberOfMoves[possiblyNewState.bottle[i]] == -1) {
                                minNumberOfMoves[possiblyNewState.bottle[i]] = moveNo;
                                stillToBeFound--;
                            }

                            if (minNumberOfMoves[possiblyNewState.bottle[j]] == -1) {
                                minNumberOfMoves[possiblyNewState.bottle[j]] = moveNo;
                                stillToBeFound--;
                            }

                            visibleStates->push_back(possiblyNewState);                                  
                        }
                    }
                }
            }
        }//end of "while (!statesToBeEvaluated->empty())"
        if (stillToBeFound == 0) break;
    }

    for (int i = 0; i < n; ++i) cout << minNumberOfMoves[i] << " ";
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
