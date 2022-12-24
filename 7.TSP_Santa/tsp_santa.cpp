#include <bits/stdc++.h>
using namespace std;
#define N 4

void efficientItinerary(int address[][N], int ownCost)
{
    vector<int> places;
    for (int i = 0; i < N; i++)
        if (i != ownCost)
            places.push_back(i);

    int minCost = INT_MAX;
    vector<int> minCosts;
    vector<int> minItinerary;
    do
    {

        int currentCost = 0;
        vector<int> currentCosts;
        vector<int> currentItinerary;

        int k = ownCost;
        for (int i = 0; i < places.size(); i++)
        {
            currentCost += address[k][places[i]];
            currentCosts.push_back(address[k][places[i]]);
            currentItinerary.push_back(k);
            k = places[i];
        }
        currentCost += address[k][ownCost];
        currentCosts.push_back(address[k][ownCost]);
        currentItinerary.push_back(k);
        currentItinerary.push_back(ownCost);

        if (currentCost < minCost)
        {
            minCost = currentCost;
            minCosts.clear();
            minItinerary.clear();
            while (!currentCosts.empty())
            {
                minCosts.push_back(currentCosts.back());
                currentCosts.pop_back();
            }

            while (!currentItinerary.empty())
            {
                minItinerary.push_back(currentItinerary.back());
                currentItinerary.pop_back();
            }
        }

    } while (
        next_permutation(places.begin(), places.end()));

    cout << "The most effective itinerary: ";
    while (!minItinerary.empty())
    {
        cout << minItinerary.back() + 1;
        minItinerary.pop_back();
        if (minItinerary.size() > 0)
            cout << " -> ";
    }
    cout << endl
         << "with costs: ";
    while (!minCosts.empty())
    {
        cout << minCosts.back();
        minCosts.pop_back();
        if (minCosts.size() > 0)
            cout << " + ";
    }
    cout << " = " << minCost << endl;
}

int main()
{
    int address[][N] = {{0, 10, 15, 20},
                        {10, 0, 35, 25},
                        {15, 35, 0, 30},
                        {20, 25, 30, 0}};
    int ownCost = 0;
    efficientItinerary(address, ownCost);
    return 0;
}
