#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

template <typename NT = int>
struct LevelNode
{
    NT val;
    int lvl;
    LevelNode(NT val, int lvl) : val(val), lvl(lvl) {}
    bool operator==(const LevelNode &a) const
    {
        return a.val == this->val && a.lvl == this->lvl;
    }
    bool operator!=(const LevelNode &a) const
    {
        return !(*this == a);
    }
};

template <typename T = int, typename D = vector<T>>
class Testing
{
  public:
    Testing(string name = "", bool toFirstError = true)
    {
        this->name = name;
        this->toFirstErrorMode = toFirstError;
        if (toFirstErrorMode)
        {
            cout << "(!) Tests are run to the first error. If you want to run all tests, set in constructor toFirstError=false" << endl;
        }
    }
    void ValuesTest(string testName, D inputData, T (*expectedScenario)(D), T (*actualScenario)(D))
    {
        if (toFirstErrorMode && testCount != testsPassed)
            return;

        testCount++;
        cout.width(testNumWidth);
        cout << right << testCount << ". ";
        cout.width(testNameWidth);
        cout << left << testName;

        T expected = expectedScenario(inputData);
        T actual;
        try
        {
            actual = actualScenario(inputData);
        }
        catch (int e)
        {
            cout << errorSpace << "\n\tUNEXPECTED EXCEPTION " << e << endl;
            throw e;
        }
        if (expected == actual)
        {
            cout << "PASSED" << endl;
            testsPassed++;
            return;
        }
        cout << "FAILED" << endl;
        if (printingEnabled)
        {
            cout << errorSpace << "Expected: " << expected << endl;
            cout << errorSpace << "Actual:   " << actual << endl;
        }
    }

    void TreeTest(string testName, D inputData, vector<LevelNode<T>> (*expectedScenario)(D), vector<LevelNode<T>> (*actualScenario)(D))
    {
        if (toFirstErrorMode && testCount != testsPassed)
            return;

        testCount++;
        cout.width(testNumWidth);
        cout << right << testCount << ". ";
        cout.width(testNameWidth);
        cout << left << testName << flush;

        vector<LevelNode<T>> expected = expectedScenario(inputData);
        vector<LevelNode<T>> actual;
        try
        {
            actual = actualScenario(inputData);
        }
        catch (int e)
        {
            cout << errorSpace << "\n\tUNEXPECTED EXCEPTION " << e << endl;
            throw e;
        }

        if (assertEqualTree(expected, actual))
        {
            cout << "PASSED" << endl;
            testsPassed++;
            return;
        }
        cout << "FAILED" << endl;
        if (printingEnabled)
            printTree(expected, actual);
    }

    void ExceptionTest(string testName, D inputData, vector<LevelNode<T>> (*actualScenario)(D))
    {
        if (toFirstErrorMode && testCount != testsPassed)
            return;

        testCount++;
        cout.width(testNumWidth);
        cout << right << testCount << ". ";
        cout.width(testNameWidth);
        cout << left << testName;
        vector<LevelNode<T>> actual;
        try
        {
            actual = actualScenario(inputData);
        }
        catch (int e)
        {
            cout << "PASSED" << endl;
            testsPassed++;
            return;
        }
        cout << "FAILED" << endl;
        if (printingEnabled)
        {
            cout << errorSpace << "Expected exception" << endl;
        }
    }

    void ExceptionTest(string testName, D inputData, T (*actualScenario)(D))
    {
        if (toFirstErrorMode && testCount != testsPassed)
            return;

        testCount++;
        cout.width(testNumWidth);
        cout << right << testCount << ". ";
        cout.width(testNameWidth);
        cout << left << testName;
        try
        {
            actualScenario(inputData);
        }
        catch (int e)
        {
            cout << "PASSED" << endl;
            testsPassed++;
            return;
        }
        cout << "FAILED" << endl;
        if (printingEnabled)
        {
            cout << errorSpace << "Expected exception" << endl;
        }
    }

    void SequenceTest(string testName, D inputData, vector<T> (*expectedScenario)(D), vector<T> (*actualScenario)(D))
    {
        if (toFirstErrorMode && testCount != testsPassed)
            return;

        testCount++;
        cout.width(testNumWidth);
        cout << right << testCount << ". ";
        cout.width(testNameWidth);
        cout << left << testName;

        vector<T> expected = expectedScenario(inputData);
        vector<T> actual;
        try
        {
            actual = actualScenario(inputData);
        }
        catch (int e)
        {
            cout << errorSpace << "\n\tUNEXPECTED EXCEPTION " << e << endl;
            throw e;
        }

        if (assertEqualSeq(expected, actual))
        {
            cout << "PASSED" << endl;
            testsPassed++;
            return;
        }
        cout << "FAILED" << endl;
        if (printingEnabled)
            printSeq(expected, actual);
    }

    void EnablePrinting(bool enable)
    {
        printingEnabled = enable;
    }

    void PrintStats()
    {
        cout << endl;
        cout << "===============================" << endl;
        cout << name << ":" << endl;
        cout << "Passed: " << testsPassed << " / " << testCount << endl;
        cout << "===============================" << endl;
    }

    void enableToFirstErrorMode(bool enable)
    {
        toFirstErrorMode = enable;
    }

  private:
    int testCount = 0;
    int testsPassed = 0;
    string errorSpace = "\t";
    bool printingEnabled = true;
    int testNumWidth = 3;
    int testNameWidth = 30;
    bool toFirstErrorMode = true;
    string name;

    void printSeq(vector<T> expected, vector<T> actual)
    {
        cout << errorSpace << "Answer"
             << "\t\t"
             << "Expected" << endl;
        for (int i = 0; i < (int)max(expected.size(), actual.size()); i++)
        {
            cout << errorSpace;
            if (i < (int)actual.size())
                cout << actual[i] << "\t\t";
            else
                cout << "(null)\t\t";
            if (i < (int)expected.size())
                cout << expected[i];
            else
                cout << "(null)\t\t";
            if (i >= (int)actual.size() || i >= (int)expected.size() || (actual[i] != expected[i]))
            {
                cout << " <---";
            }
            cout << endl;
        }
    }

    void printTree(vector<LevelNode<T>> expected, vector<LevelNode<T>> actual)
    {
        cout << errorSpace << "Actual:" << endl;
        cout << errorSpace;
        if (actual.size() == 0)
            cout << "(null)";
        else
            for (int i = 0; i < (int)actual.size(); i++)
                cout << actual[i].val << " ";
        cout << endl;

        cout << errorSpace << "Expected:" << endl;
        cout << errorSpace;
        if (expected.size() == 0)
            cout << "(null)";
        else
            for (int i = 0; i < (int)expected.size(); i++)
                cout << expected[i].val << " ";
        cout << endl;
        cout << errorSpace << "(Elements are printed in order of correct adding to BST)" << endl;
    }

    bool assertEqualTree(vector<LevelNode<T>> expected, vector<LevelNode<T>> actual)
    {
        if (expected.size() != actual.size())
            return false;
        for (int i = 0; i < (int)expected.size(); i++)
            if (expected[i] != actual[i])
                return false;
        return true;
    }

    bool assertEqualSeq(vector<T> expected, vector<T> actual)
    {
        if (expected.size() != actual.size())
            return false;
        for (int i = 0; i < (int)expected.size(); i++)
            if (expected[i] != actual[i])
                return false;
        return true;
    }
};
