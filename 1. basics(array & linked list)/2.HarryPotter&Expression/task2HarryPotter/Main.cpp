#include <iostream>
#include "queue.h"

bool inRangePlus(int index, int size)
{
    return index < size;
}

bool inRangeMinus(int index, int size)
{
    return index >= 0;
}

bool diagonal(int x, int y, int n)
{
    return ((x == 0 && y == 0) || (x == n - 1 && y == n - 1)) ? false : x == y;
}

bool lastIndex(int x, int y, int n)
{
    return (x == n - 1 && y == n - 1);
}

bool indexed(int x, int y, int *indexedXs, int *indexedYs, int indexedCount)
{
    for (int i = 0; i < indexedCount; i++)
        if (indexedXs[i] == x && indexedYs[i] == y)
            return true;
    return false;
}

int main()
{
    int n = 10;

    int map[n][n] = {{7, 1, 3, 5, 3, 6, 1, 1, 7, 5},
                     {2, 3, 6, 1, 1, 6, 6, 6, 1, 2},
                     {6, 1, 7, 2, 1, 4, 7, 1, 6, 2},
                     {6, 4, 7, 1, 3, 3, 5, 1, 3, 4},
                     {5, 5, 6, 1, 5, 4, 6, 4, 7, 4},
                     {3, 5, 5, 2, 7, 5, 3, 3, 3, 6},
                     {4, 1, 4, 3, 6, 4, 5, 5, 2, 6},
                     {4, 4, 1, 7, 4, 3, 3, 3, 4, 2},
                     {4, 4, 5, 1, 5, 2, 3, 3, 3, 5},
                     {3, 6, 3, 5, 2, 2, 6, 0, 2, 1}};

    int indexedXs[n * n];
    int indexedYs[n * n];
    int indexedCount = 0;

    Queue queuedXs;
    Queue queuedYs;

    queuedXs.put(0);
    queuedYs.put(0);

    while (!queuedXs.empty() && !queuedYs.empty())
    {
        int x = queuedXs.get();
        int y = queuedYs.get();
        int k = map[x][y];

        if (inRangePlus(x + k, n) && !diagonal(x + k, y, n) && !indexed(x + k, y, indexedXs, indexedYs, indexedCount))
        {
            queuedXs.put(x + k);
            queuedYs.put(y);

            indexedXs[indexedCount] = x + k;
            indexedYs[indexedCount] = y;
            indexedCount++;

            //std::cout << "\nx: " << x << " y: " << y << " value: " << map[x + k][y] << std::endl;
        }
        if (inRangeMinus(x - k, n) && !diagonal(x - k, y, n) && !indexed(x - k, y, indexedXs, indexedYs, indexedCount))
        {
            queuedXs.put(x - k);
            queuedYs.put(y);

            indexedXs[indexedCount] = x - k;
            indexedYs[indexedCount] = y;
            indexedCount++;

            //std::cout << "x: " << x << " y: " << y << " value: " << map[x - k][y] << std::endl;
        }
        if (inRangePlus(y + k, n) && !diagonal(x, y + k, n) && !indexed(x, y + k, indexedXs, indexedYs, indexedCount))
        {
            queuedXs.put(x);
            queuedYs.put(y + k);

            indexedXs[indexedCount] = x;
            indexedYs[indexedCount] = y + k;
            indexedCount++;

            //std::cout << "x: " << x << " y: " << y << " value: " << map[x][y + k] << std::endl;
        }
        if (inRangeMinus(y - k, n) && !diagonal(x, y - k, n) && !indexed(x, y - k, indexedXs, indexedYs, indexedCount))
        {
            queuedXs.put(x);
            queuedYs.put(y - k);

            indexedXs[indexedCount] = x + k;
            indexedYs[indexedCount] = y;
            indexedCount++;
            //std::cout << "x: " << x << " y: " << y << " value: " << map[x][y - k] << std::endl;
        }

        if(lastIndex(x, y, n))
        {
            std::cout << "Harry, Don't worry we've got you covered. Exit address: (" << x <<", " << y << ") with value: " << map[x][y] << std::endl;
            break;
        }
    }
}