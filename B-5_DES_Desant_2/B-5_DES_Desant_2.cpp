// B-5_DES_Desant_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, k, q; //n - number of soldaten, k - size of groups, q - test cases
    cin >> n >> k >> q;

    vector<long long> soldiers(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> soldiers[i];
    }

    int numberOfGroups = n - k + 1;
    vector<long long> groupUtility;

    //count first group by hand
    long long firstGroup = 0;
    for (int i = 0; i < k; ++i) firstGroup += soldiers[i];
    groupUtility.push_back(firstGroup);

    for (int i = 1; i < numberOfGroups; ++i) {
        groupUtility.push_back(groupUtility[i - 1] - soldiers[i - 1] + soldiers[i + k - 1]);
    }

    for (int testNo = 0; testNo < q; ++testNo) {
        int L, R;
        cin >> L >> R; //1<=L<=R<=n
        L -= 1;
        R -= 1;

        vector<pair<long long,bool>> biggestTotalUtility; //till and including index, second of pair - was this group used
        if (L < numberOfGroups) {
            if (groupUtility[L] > 0) biggestTotalUtility.push_back(make_pair(groupUtility[L], true));
            else biggestTotalUtility.push_back(make_pair(0, false));
        }
        
        for (int i = L+1 ; i < L + k && i <= R-k+1 ; ++i) {
            if (groupUtility[i] > 0 && biggestTotalUtility[i - L - 1].first < groupUtility[i]) {
                biggestTotalUtility.push_back(make_pair(groupUtility[i], true));
            }
            else {
                biggestTotalUtility.push_back(make_pair(biggestTotalUtility[i - L - 1].first, false));
            }
            /*if (groupUtility[i] > 0) {
                biggestTotalUtility.push_back(make_pair(groupUtility[i], true));
            }
            else {
                biggestTotalUtility.push_back(make_pair(0, false));
            }*/
        }
        
        for (int i = L + k; i <= R-k+1; ++i) {
        //    long long biggestSoFar = 0;
        //    //THIS group - i
        //    bool isThisGroupUsed = false;     

        //    for (int j = 1; j < k ; ++j) {
        //        //THAT group - j
        //        if (biggestTotalUtility[i - j - L].second && groupUtility[i] > 0) {
        //            //that group was used
        //            if (biggestSoFar < biggestTotalUtility[i - j - L].first) {
        //                biggestSoFar = biggestTotalUtility[i - j - L].first;
        //                isThisGroupUsed = false;
        //            }
        //        }
        //        else {
        //            //that group was not used - we can use this group
        //            if (biggestSoFar < biggestTotalUtility[i - j - L].first + groupUtility[i]) {
        //                biggestSoFar = biggestTotalUtility[i - j - L].first + groupUtility[i];
        //                isThisGroupUsed = true;
        //            }
        //        }
        //    }

        //    if (groupUtility[i] > 0) {
        //        if (biggestSoFar < biggestTotalUtility[i - k - L].first + groupUtility[i])
        //        {
        //            biggestSoFar = biggestTotalUtility[i - k - L].first + groupUtility[i];
        //            isThisGroupUsed = true;
        //        }
        //    }
        //    biggestTotalUtility.push_back(make_pair(biggestSoFar, isThisGroupUsed));
            biggestTotalUtility.push_back(make_pair(
                max(biggestTotalUtility[i - k - L].first + groupUtility[i],
                    biggestTotalUtility[i - 1 - L ].first),
                false));
        }// end of for (int i = L + k; i <= R; ++i) {

        if (R - L - k +1 >= 0)
            cout << (end(biggestTotalUtility)-1)->first << endl;
        else
            cout << 0 << endl;
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
