#include <iostream>
#include <random>
#include <stdlib.h>
using namespace std;
int numberTubes = 5;    // default value
int numberColors = 5;   // default value
const int capacity = 5; // default value
struct testTube
{
    int testTube[capacity] = {0};
    int top = 0;
};

random_device rd; // seeding the random number generator
mt19937 gen(rd());
void welcomeMessage()
{
    cout << "Welcome to this wonderful game created by yours turly" << "\n";
    cout << "The goal is to turn an unordered set of test tubes to an ordered one" << "\n";
    cout << "Please enter the game settings you want to play with: " << "\n";
    cout << "Enter the number of test tubes(the less number there are more the difficulty)" << "\n";
    cin >> numberTubes;
    cout << "Enter the number of colors(the more number there are more the difficulty)" << "\n";
    cin >> numberColors;
    cout << "Please note that 0 indicates an absence of liquid \n two of the same numbers indicate the same liqud ";
    cout << "Let the games begin" << endl;
}
int random(int i)
{
    uniform_int_distribution<> dist(1, numberColors); // number generator for colors
    return dist(gen);
}
int random()
{
    uniform_int_distribution<> dist(1, capacity); // number generator for how much to fill in each TT
    return dist(gen);
}
int pop(testTube *var)
{
    int temp = 0;
    if (var->top > 0)
    {
        temp = var->testTube[var->top - 1];
        var->testTube[var->top - 1] = 0;
        var->top--;
    }
    return temp;
}
void push(testTube *var, int val)
{
    var->testTube[var->top] = val;
    var->top++;
}
void print(testTube var[])
{
    system("cls");
    for (int i = (capacity - 1); i >= 0; i--)
    {
        for (int j = 0; j < numberTubes; j++)
        {
            cout << var[j].testTube[i] << "\t";
        }
        cout << "\n";
    }
}
bool pour(testTube var[], int source, int destination)
{
    int temp = var[source].testTube[var[source].top - 1];
    int temp2 = var[destination].testTube[var[destination].top - 1];
    //  attempting to pour from source to destination
    while (var[source].testTube[var[source].top - 1] == temp)
    {
        if (temp == temp2 && var[destination].testTube[var[destination].top + 1] <= capacity)
            push(&var[destination], pop(&var[source]));
        else
            return false;
    }
    return true;
}

bool checkForWin(testTube var[])
{
    for (int i = 0; i < numberTubes; i++)
    {
        int num = 0;
        bool isFirstNonZero = true;

        for (int j = 0; j < capacity; j++)
        {
            if (var[i].testTube[j] != 0)
            {
                if (isFirstNonZero)
                {
                    num = var[i].testTube[j];
                    isFirstNonZero = false;
                }
                else if (var[i].testTube[j] != num)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
int main()
{
    welcomeMessage();
    int dest = 0;
    int source = 0;
    testTube tubes[numberTubes];
    for (int i = 0; i < numberTubes; i++)
    {
        for (int j = 0; j < random(); j++)
        {
            push(&tubes[i], random(0));
        }
    }
    while (1)
    {
        print(tubes);
        cout << "Enter source first then destination for pouring liquid(tubes are ordered from 1 )" << "\n";
        cin >> source;
        cin >> dest;
        source--;
        dest--;
        if ((dest > numberTubes) || (source > numberTubes))
        {
            cout << "enter number within ranges :(" << "\n";
            continue;
        }
        if (!pour(tubes, source, dest))
        {
            cout << "Illegal move :(" << "\n";
        }
        if (checkForWin(tubes))
        {
            print(tubes);
            cout << "YAY YOU WONNNN!" << "\n";
            break;
        }
    }
    return 0;
}