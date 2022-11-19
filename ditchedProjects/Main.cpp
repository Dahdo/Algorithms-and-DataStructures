#include <iostream>



bool inRangePlus(int index, int size){
        return index < size;
}

bool inRangeMinus(int index, int size){
        return index >= 0;
}

bool diagonal(int x, int y){
    return x == y;
}

bool lastIndex(int x, int y, int n){
        return (x == n - 1 && y == n - 1);
}

bool indexed(int x, int y, int* indexedXs, int* indexedYs, int indexedCount){
        for(int i = 0; i < indexedCount; i++)
            if(indexedXs[i] == x && indexedYs[i] == y)
                return true;
        return false;
}

bool goodMove(int x, int y, int k, int n, int* indexedXs, int* indexedYs, int indexedCount){
    if(k > 0 && inRangePlus(x + k, n) && !diagonal(x + k, y)) {
        if(!indexed(x + k, y, indexedXs, indexedYs, indexedCount))
            return true;
    }
    else if(k > 0 && inRangeMinus(x - k, n) && !diagonal(x - k, y)) {
        if(!indexed(x - k, y, indexedXs, indexedYs, indexedCount))
            return true;
    }
    else if(k > 0 && inRangePlus(y + k, n) && !diagonal(x, y + k)) {
        if(!indexed(x, y + k, indexedXs, indexedYs, indexedCount))
            return true;
    }
    else if(k > 0 && inRangeMinus(y - k, n) && !diagonal(x, y - k)) {
        if(!indexed(x, y - k, indexedXs, indexedYs, indexedCount))
            return true;
    } 
    else
        return false;
    
    return false;
}


int main(){
  int n = 10;
    
int map[n][n] = {{7,1,3,5,3,6,1,1,7,5},
                {2,3,6,1,1,6,6,6,1,2},
                {6,1,7,2,1,4,7,1,6,2},
                {6,4,7,1,3,3,5,1,3,4},
                {5,5,6,1,5,4,6,4,7,4},
                {3,5,5,2,7,5,3,3,3,6},
                {4,1,4,3,6,4,5,5,2,6},
                {4,4,1,7,4,3,3,3,4,2},
                {4,4,5,1,5,2,3,3,3,5},
                {3,6,3,5,2,2,6,0,2,1}};
    int x = 0, y = 0;
    int k = map[x][y];
    bool gotStuck = true;

    int indexedXs[n * n];
    int indexedYs[n * n];
    int indexedCount = 0;

    while(!lastIndex(x, y, n)){
        int higherXIndex = -1;
        int higherYIndex = -1;
        if(k > 0 && inRangePlus(x + k, n) && !diagonal(x + k, y) && !indexed(x + k, y, indexedXs, indexedYs, indexedCount)
         && goodMove(x + k, y, map[x + k][y], n, indexedXs, indexedYs, indexedCount)){
            gotStuck = false;
            if(x + k > higherXIndex)
                higherXIndex = x + k;
            //x = x + k;
            //k = map[x][y];

            // indexedXs[indexedCount] = x;
            // indexedYs[indexedCount] = y;
            // indexedCount++;

            std::cout << "\nx: " << x << " y: " << y << " value: " << map[x][y] << std::endl;

            // if(lastIndex(x, y, n))
            //     break;
        }
        if(k > 0 && inRangeMinus(x - k, n) && !diagonal(x - k, y) && !indexed(x - k, y, indexedXs, indexedYs, indexedCount)
        && goodMove(x - k, y, map[x - k][y], n, indexedXs, indexedYs, indexedCount)){
            gotStuck = false;
            if(x - k > higherXIndex)
                higherXIndex = x - k;
            // x = x - k;
            // k = map[x][y];

            // indexedXs[indexedCount] = x;
            // indexedYs[indexedCount] = y;
            // indexedCount++;

            std::cout << "x: " << x << " y: " << y << " value: " << map[x][y] << std::endl;

            // if(lastIndex(x, y, n))
            //     break;
        }
        if(k > 0 && inRangePlus(y + k, n) && !diagonal(x, y + k) && !indexed(x, y + k, indexedXs, indexedYs, indexedCount) 
        && goodMove(x, y + k, map[x][y + k], n, indexedXs, indexedYs, indexedCount)){
            gotStuck = false;
            if(y + k > higherYIndex)
                higherYIndex = y + k;
            // y = y + k;
            // k = map[x][y];

            // indexedXs[indexedCount] = x;
            // indexedYs[indexedCount] = y;
            // indexedCount++;

            std::cout << "x: " << x << " y: " << y << " value: " << map[x][y] << std::endl;

            // if(lastIndex(x, y, n))
            //     break;
        }
        if(k > 0 && inRangeMinus(y - k, n) && !diagonal(x, y - k) && !indexed(x, y - k, indexedXs, indexedYs, indexedCount) 
        && goodMove(x, y - k, map[x][y - k], n, indexedXs, indexedYs, indexedCount)){
            gotStuck = false;
            if(y - k > higherYIndex)
                higherYIndex = y - k;
            // y = y - k;
            // k = map[x][y];

            // indexedXs[indexedCount] = x;
            // indexedYs[indexedCount] = y;
            // indexedCount++;

            std::cout << "x: " << x << " y: " << y << " value: " << map[x][y] << std::endl;

            // if(lastIndex(x, y, n))
            //     break;
        }
        if(gotStuck){
            std::cout << "Harry in Trouble... I'm out!" << std::endl;
            std::cout << "x: " << x << " y: " << y << " value: " << map[x][y] << std::endl;
            break;
        }


        if(higherYIndex >= higherXIndex && higherYIndex > y){
            y = higherYIndex;
            k = map[x][y];

            indexedXs[indexedCount] = x;
            indexedYs[indexedCount] = y;
            indexedCount++;

            std::cout << "---YChoice x: " << x << " y: " << y << " value: " << map[x][y] << std::endl;
            if(lastIndex(x, y, n))
                break;
        }
        else if(higherXIndex > x){
            x = higherXIndex;
            k = map[x][y];

            indexedXs[indexedCount] = x;
            indexedYs[indexedCount] = y;
            indexedCount++;

            std::cout << "---XChoice x: " << x << " y: " << y << " value: " << map[x][y] << std::endl;
            if(lastIndex(x, y, n))
                break;
        }
        else if(higherYIndex >= higherXIndex && higherYIndex > -1){ // give a second chance to the first if statement. && cond. removed 
            y = higherYIndex;
            k = map[x][y];

            indexedXs[indexedCount] = x;
            indexedYs[indexedCount] = y;
            indexedCount++;

            std::cout << "---YChoice x: " << x << " y: " << y << " value: " << map[x][y] << std::endl;
            if(lastIndex(x, y, n))
                break;
        }
        else if(higherXIndex > -1){ // a second chance to this too with comparison against initial value
            x = higherXIndex;
            k = map[x][y];

            indexedXs[indexedCount] = x;
            indexedYs[indexedCount] = y;
            indexedCount++;

            std::cout << "---XChoice x: " << x << " y: " << y << " value: " << map[x][y] << std::endl;
            if(lastIndex(x, y, n))
                break;
        }
        else {
            std::cout << "---cond2: Harry in Trouble... I'm out!" << std::endl;
            std::cout << "x: " << x << " y: " << y << " value: " << map[x][y] << std::endl;
            break;
        }

        gotStuck = true; // reset after each iteration
    }

    std::cout << "x: " << x << " y: " << y << " value: " << map[x][y] << std::endl;
    exit(0);
}