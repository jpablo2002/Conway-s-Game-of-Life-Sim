/*
 * Juan Pablo Acosta
 * Apr. 6,  2021
 * Project: Conways Game of Life
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

void printgrid (const vector<vector<int> >& generationgrid, const float gridsize);
int numliveneighbours (const vector<vector<int> > pastgrid, const float gridsize, const int currentcolumn, const int currentrow);
void gamerulesaction (vector<vector<int> >& gamegrid, const vector<vector<int> >& pastgrid, const int currentcolumn, const int currentrow, const int numlivecells);

int main()
{
    float fixedsize, initiallive, initcellcounter, initcellrow, initcellcolumn, usergenerations;
    int numgeneration{1}, livecells;

    cout << '\n' << "Welcome to Conway's Game of Life! In this program, you will simulate Conway's Game of Life for as many generations as you indicate and with your starting conditions, inside a fixed square grid." << endl;

    do
    {
        cout << '\n' << "Please enter the fixed size of the grid (input will be treated as ___ x ___): ";
        cin >> fixedsize;

        if (fixedsize != (int)(fixedsize) || fixedsize <= 0) //Condition prints warning for inappropriate input.
            cout << "That is not an appropriate input! Please enter a natural number." << endl;
    } while (fixedsize != (int)(fixedsize) || fixedsize <= 0); //Loop ensures that user enters an appropriate input.

    vector<vector<int> > simulationgrid(fixedsize); //Vectors are created with indicated number of rows from user.
    vector<vector<int> > pastgrid(fixedsize);

    for(auto& simrow: simulationgrid){ //Range-based for loop accesses every row of the 2D vector
        for (int initializecounter{0}; initializecounter < fixedsize; initializecounter ++) //For loop creates number of columns indicated by user, with all elements initialized to 0 (dead cells).
            simrow.push_back(0);
    }

    for(auto& pastrow: pastgrid) //Range-based for loop accesses every row of the 2D vector
    {
        for (int initializecounter{0}; initializecounter < fixedsize; initializecounter ++) //For loop creates number of columns indicated by user, with all elements initialized to 0 (dead cells).
            pastrow.push_back(0);
    }

    do
    {
        cout << '\n' << "How many live cells would you like to begin with? ";
        cin >> initiallive;

        if (initiallive != (int)(initiallive) || initiallive < 0 || (initiallive > pow(fixedsize, 2))) //Condition prints warning for inappropriate inputs
            cout << "That is not an appropriate input! Please enter a whole number that is less than or equal to the area of the square of the size you entered." << endl;
    } while (initiallive != (int)(initiallive) || initiallive < 0 || (initiallive > pow(fixedsize, 2))); //Loop ensures user enters an appropriate input (last condition ensures user doesn't enter more cells than there are squares).

    initcellcounter = 0;
    printgrid(simulationgrid, fixedsize);

    while (initcellcounter < initiallive) //Loop ensures that user is asked for coordinates of live cell only as many times as user indicated.
    {
        do
        {
            cout << '\n' << "Please enter the row number of the live cell (row numbers begin at 0): ";
            cin >> initcellrow;

            if (initcellrow < 0 || initcellrow >= fixedsize || (int)(initcellrow) != initcellrow) //Condition prints warning for inappropriate input
                cout << "That is not an appropriate input! Please enter a whole number less than " << fixedsize << endl;
        } while (initcellrow < 0 || initcellrow >= fixedsize || (int)(initcellrow) != initcellrow); //Loop ensures user enters an appropriate input

        do
        {
            cout << "Please enter the column  number of the live cell (column numbers begin at 0): ";
            cin >> initcellcolumn;

            if (initcellcolumn < 0 || initcellcolumn >= fixedsize || (int)(initcellcolumn) != initcellcolumn) //Condition prints warning for inappropriate input
                cout << "That is not an appropriate input! Please enter a whole number less than " << fixedsize << endl;
        } while (initcellcolumn < 0 || initcellcolumn >= fixedsize || (int)(initcellcolumn) != initcellcolumn); // Loop ensures user enters an appropriate input

        if (simulationgrid.at(initcellrow).at(initcellcolumn) == 1) //Condition ensures that user doesn't enter same coordinates for a live cell twice
        {
            cout << "You can't enter the same set of coordinates twice!" << endl;
            continue;
        }

        simulationgrid.at(initcellrow).at(initcellcolumn) = 1; //Coordinates of user make a live cell on the 2D vector.

        initcellcounter ++; //Counter of live cells marked increases to keep track of how many live cells have been made.
    }

    do
    {
        cout << '\n' << "For how many generations would you like to run the simulation? ";
        cin >> usergenerations;

        if(usergenerations <= 0 || usergenerations != (int)(usergenerations)) //Condition prints warning for inappropriate input
            cout << "That is not an appropriate input! Please enter a natural number." << endl;
    } while (usergenerations <= 0 || usergenerations != (int)(usergenerations)); //Loop ensures user enters an appropriate input


    cout << '\n' << "Generation 0" << endl;
    printgrid(simulationgrid, fixedsize);

    pastgrid = simulationgrid; //Pastgrid is updated to be the same as simulation grid (pastgrid is used to see conditions and make changes on simulationgrid, so changes made on simulationgrid don't affect future changes)

    while (numgeneration < usergenerations) //Condition ensures that new conditions of a generation are created only as many times as user indicated.
    {
        for (int currentrow{0}; currentrow < fixedsize; currentrow ++) //For loop runs through every row of the 2D vector.
        {
            for (int currentcolumn{0}; currentcolumn < fixedsize; currentcolumn ++) //For loop runs through every column of the 2D vector.
            {
                livecells = numliveneighbours (pastgrid, fixedsize, currentcolumn, currentrow); //Number of live cells (neighbours) of current element is stated.
                gamerulesaction(simulationgrid, pastgrid, currentcolumn, currentrow, livecells);
            }
        }

        cout << '\n' << "Generation " << numgeneration << endl;
        printgrid(simulationgrid, fixedsize);

        pastgrid = simulationgrid; //Pastgrid is updated to simulation grid now that changes have been made to make appropriate changes in next generation.

        numgeneration ++; //Numgeneration is increased to keep track of current generation generated.
    }

    cout << '\n' << "Thanks for playing! Have a great day!" << endl;

    return 0;
}

//Purpose: To print a grid with borders in which the elements of the vector printed show the progression of generations according to rules of Conway's Game of Life.
void printgrid (const vector<vector<int> >& generationgrid, const float gridsize)
{
    cout << setw(2) << " ";
    cout << "_";

    for (int topborder{0}; topborder < gridsize; topborder ++) //Loop prints top border of grid (3 '_' per box and extra 1 for column line)
        cout << "____";

    cout << '\n';

    for (auto const& gridrow: generationgrid) //Loop runs through every row of the 2D vector generationgrid.
    {
        cout << "  |";

        for (auto const& gridelement: gridrow) //Loop runs through every element of current row of 2D vector.
            cout << " " << gridelement << " |";

             cout << '\n' << "  |";

             for (int bottomborder{0}; bottomborder < gridsize; bottomborder ++) //Loop prints out bottom border of grid (3 '_' per box and extra 1 for column line).
                cout << "___|";

             cout << '\n';
    }

}

//Purpose: To carry out appropriate action for current cell on the 2D vector based on number of live neighbours, state of current cell, and appropriate rule of Conway's Game of Life. Changes in 2D vector passed by reference.
void gamerulesaction (vector<vector<int> >& gamegrid, const vector<vector<int> >& pastgrid, const int currentcolumn, const int currentrow, const int numlivecells)
{
    //Overpopulation scenario of Conway's Game of Life
    if (pastgrid.at(currentrow).at(currentcolumn) == 1 && numlivecells > 3) //Condition ensures that appropriate action is taken for Overpopulation scenario (according to Conway's Game of Life)
        gamegrid.at(currentrow).at(currentcolumn) = 0;

    //Just Right scenario of Conway's Game of Life
    if (pastgrid.at(currentrow).at(currentcolumn) == 1 && (numlivecells == 3 || numlivecells == 2)) //Condition ensures that appropriate action is taken for Just Right scenario (according to Conway's Game of Life)
        gamegrid.at(currentrow).at(currentcolumn) = 1;

    //Underpopulation scenario of Conway's Game of Life
    if (pastgrid.at(currentrow).at(currentcolumn) == 1 && numlivecells < 2) //Condition ensures that appropriate action is taken for Underpopulation scenario (according to Conway's Game of Life)
        gamegrid.at(currentrow).at(currentcolumn) = 0;

    //Breeding scenario of Conway's Game of Life
    if (pastgrid.at(currentrow).at(currentcolumn) == 0 && numlivecells == 3) //Condition ensures that appropriate action is taken for Breeding scenario (according to Conway's Game of Life)
        gamegrid.at(currentrow).at(currentcolumn) = 1;
}

//Purpose: To calculate and return the number of live neighbours of the current cell on the 2D vector.
int numliveneighbours (const vector<vector<int> > pastgrid, const float gridsize, const int currentcolumn, const int currentrow)
{
    int livecellcounter{0};

    for (int rowcheckcounter{-1}; rowcheckcounter < 2; rowcheckcounter ++) //Loop ensures that every row (3 rows) that could have neighbours of current cell are checked.
    {
        if (currentrow + rowcheckcounter < 0 || currentrow + rowcheckcounter >= gridsize) //Condition ensures that if there is no row to check since the current cell is at the top or bottom edge of the grid, neighbours aren't looked for.
            continue;

        else //Condition ensures that if there are rows to check since the current cell isn't at the top or bottom edge of the grid, neighbours are searched for.
        {
            for (int columncheckcounter{-1}; columncheckcounter < 2; columncheckcounter ++) //Loop ensures that every column (3 columns) that could have neighbours of current cell are checked.
            {
                if (currentcolumn + columncheckcounter < 0 || currentcolumn + columncheckcounter >= gridsize) //Condition ensures that if there is no column to check since the current cell is at the left or right edge of the grid, neighbours aren't looked for.
                    continue;

                else //Condition ensures that if there are columns to check since the current cell isn't at the left or right edge of the grid, neighbours are searched for.
                {
                    if (pastgrid.at(currentrow + rowcheckcounter).at(currentcolumn + columncheckcounter) == 1 && !(rowcheckcounter == 0 && columncheckcounter == 0)) //Condition ensures that if current neighbour being checked is living, live cell counter is increased (neighbour can't be itself).
                        livecellcounter ++;

                    if (pastgrid.at(currentrow + rowcheckcounter).at(currentcolumn + columncheckcounter) == 0) //Condition ensures that if current neighbour being checked is dead, no change to livecellcounter.
                        continue;
                }
            }
        }
    }

    return livecellcounter;
}
