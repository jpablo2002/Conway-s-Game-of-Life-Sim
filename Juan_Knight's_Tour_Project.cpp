/*
 * Juan Pablo Acosta
 * Mar. 2, 2021
 * Assignment 3: Knight's Tour
*/
#include <iostream>
#include <array>
#include <string>

using namespace std;

void printchessboard(array < array<int, 8>, 8> boardsquares, array < array<int, 8>, 8>comparesquares);
void possiblemoves(array < array<int, 8>, 8>& boardpositions, array<int, 2> knightcurrently, array<int, 8>& usercheck);

int main()
{
    array < array <int, 8>, 8> boardplaces;
    array <int, 2> knightposition;
    array < int, 8> usermovecheck;
    array <array <int, 8>, 8> comparisonboard;
    string tryagain;

    do
    {
        int beentocounter {1};

        for (auto& row: boardplaces) //Loop accesses every row of 2D array boardplaces (chessboard).
            row.fill(10); //Calls fill to initialize all elements of array to 10.

        for (auto& comparisonrow: comparisonboard) //Loop accesses every row of 2D array comparisonboard.
            comparisonrow.fill(0); //Calls fill to initialize all elements of array to 0.

        printchessboard(boardplaces, comparisonboard);

        float userrow, usercolumn;

        cout << '\n' << "This program allows you, the user, to choose a location for the knight to start on a chess board, and to move it until you move to a square you've already been to!" << endl;

        do
        {
            cout << '\n' << "Please enter the x-coordinate (row number) for the knight to begin at: ";
            cin >> userrow;

            if (userrow != (int)(userrow) || userrow < 0 || userrow > 7) //Condition prints warning for inappropriate input.
                cout << "That is not an appropriate input! Please enter a non-decimal number between 0 and 7 (inclusive)" << endl;

        } while (userrow != (int)(userrow) || userrow < 0 || userrow > 7); //Loop ensures that user enters an appropriate input.

        do
        {
            cout << "Please enter the y-coordinate (column number) for the knight to begin at: ";
            cin >> usercolumn;

            if (usercolumn != (int)(usercolumn) || usercolumn < 0 || usercolumn > 7) //Condition prints warning for inappropriate input.
                cout << "That is not an appropriate input! Please enter a non-decimal number between 0 and 7 (inclusive)" << '\n' << endl;

        } while (usercolumn != (int)(usercolumn) || usercolumn < 0 || usercolumn > 7); //Loop ensures that user enters an appropriate input.

        boardplaces.at(userrow).at(usercolumn) = 11; //Assigns value of 11 (prints out K) to an element in boardplaces 2D array.

        knightposition.at(0) = userrow; //Assigns elements of array knightposition the row and column numbers of knight's position.
        knightposition.at(1) = usercolumn;

        int memoryrow, memorycolumn;
        int knightcolumn, knightrow{0};

        do
        {
            usermovecheck.fill(10); //Initializes all elements of usermovecheck to 10.

            possiblemoves (boardplaces, knightposition, usermovecheck);

            printchessboard(boardplaces, comparisonboard);

            float knightmove;
            char moveallowed;

            moveallowed = 'n';

            do
            {
                cout << '\n' << "Please enter the number (position) you would like to move to: ";
                cin >> knightmove;

                for (int check: usermovecheck) //Loop accesses every row of the array usermovecheck.
                {
                    if (check == knightmove && check != 10) //Condition ensures that moveallowed is 'y' if the position entered by the user is one of the possible positions stored in usermovecheck.
                        moveallowed = 'y';
                }

                if (knightmove != (int)(knightmove) || moveallowed != 'y') //Condition prints warning for inappropriate input.
                    cout << "That is not an appropriate input! Please enter a non-decimal number seen as a possible position on the grid." << endl;

            } while (knightmove != (int)(knightmove) || moveallowed != 'y'); //Loop ensures that an appropriate input is entered.

            memoryrow = 0;

            for (auto const rows: boardplaces) //Loop accesses every row of the 2D array boardplaces.
            {
                memorycolumn = 0;

                for (auto const previousposition: rows) //Loop accesses every element of a row of 2D array boardplaces.
                {
                    if (previousposition == 11) //If element of row is 11 (where the knight is), breaks loop so column value is saved.
                        break;

                    if (memorycolumn < 7) //Condition ensures that memorycolumn value is less than 8 (8 or greater is not possible column).
                        memorycolumn ++;
                }

                if (boardplaces.at(memoryrow).at(memorycolumn) == 11) //Condition ensures that if appropriate square has been found where knight is, breaks loop so row value is saved.
                    break;

                if (memoryrow < 7) //Condition ensures that memoryrow value is less than 8 (8 or greater is not possible row).
                    memoryrow ++;
            }

            comparisonboard.at(memoryrow).at(memorycolumn) = beentocounter; //Updates value of comparison board to where knight currently is, setting it as square that knight has already visited.

            for (auto& reset: boardplaces) //Loop accesses every row of the 2D array boardplaces.
            {
                for (auto& redo: reset) //Loop accesses every element of a row of 2D array boardplaces.
                {
                    if (redo != knightmove) //Condition ensures that every element of 2D array is reset to 10 except for where the knight is supposed to move (user entered).
                        redo = 10;
                }
            }

            for (auto& rowsmove: boardplaces) //Loop accesses every row of the 2D array boardplaces.
            {
                for (auto& move: rowsmove) //Loop accesses every element of a row of 2D array boardplaces.
                {
                    if (move == knightmove) //Condition ensures that if the element of the array is knightmove (where knight is supposed to move), it becomes 11 (equivalent to K, where knight is).
                        move = 11;
                }
            }

            knightrow = 0;

            for (auto& knightrows: boardplaces) //Loop accesses every row of the 2D array boardplaces.
            {
                knightcolumn = 0;

                for (auto& knight: knightrows) //Loop accesses every element of a row of 2D array boardplaces.
                {
                    if (knight == 11) //Condition ensures that if location of knight is found, loop breaks (saves knightcolumn value).
                        break;

                    if (knightcolumn < 7) //Condition ensures that knightcolumn is less than 8 (8 or greater is not a possible column).
                        knightcolumn ++;
                }

                if (boardplaces.at(knightrow).at(knightcolumn) == 11) //Condition ensures that once location of knight is found, breaks loop to save knightrow value.
                    break;

                if (knightrow < 7) //Condition ensures that knightrow is less than 8 (8 or greater is not a possible row).
                    knightrow ++;
            }

            knightposition.at(0) = knightrow; //Sets values of knightposition array to row and column number of knight's position.
            knightposition.at(1) = knightcolumn;

            beentocounter ++; //Makes values on comparison board consecutive and increasing (tracks order in which squares have been visited).

        } while (comparisonboard.at(knightrow).at(knightcolumn) == 0); //Loop ensures that user is able to move knight until knight is moved to a position it has already been to.

        cin.ignore();

        do
        {
            cout << '\n' << "You tried to move to a spot you've already been to, and so the program has stopped. Would you like to try again ('y' or 'n')? ";
            getline (cin, tryagain);

            tryagain[0] = tolower(tryagain[0]); //Calls tolower to make first letter of string entered lowercase.

            if (tryagain != "y" && tryagain != "n") //Condition prints warning for inappropriate input.
                cout << "That is not an appropriate input! Please enter 'y' or 'n'." << endl;

        } while (tryagain != "y" && tryagain != "n"); //Loop ensures that user enters an appropriate input.

    } while (tryagain == "y"); //Loop ensures that user can continue to play until wants to stop.

    cout << '\n' << "Thanks for playing! Have a great day!" << endl;

    return 0;
}

//Purpose: Prints grid of chessboard with appropriate visuals for user, and below, prints coordinates of squares visited.
void printchessboard(array < array<int, 8>, 8> boardsquares, array < array<int, 8>, 8> comparesquares)
{
    cout << "    ";
    for (int topnumbers {0}; topnumbers < 8; topnumbers++) //Loop prints out top numbers (column numbers) of grid.
        cout << topnumbers << "   ";

    cout << '\n' << "  ";

    for (int top {0}; top < 33; top ++) //Loop prints out top edge of chess board.
        cout << "_";

    cout << '\n';

    int sidenumbers {0};
    int rownum{0}, columnnum;

    for (auto const rows: boardsquares) //Loop accesses every row of the 2D array (chessboard).
    {
        cout << sidenumbers <<  " |";

        for (auto element: rows) //Loop runs through every element of each row of the 2D array (chessboard).
        {
            if (element == 10) //Condition ensures that for certain values, certain visuals are generated on the board. (ex. 10 in 2D array prints out empty space).
                cout << "   |";

            else if (element == 11)
                cout << " K |";

            else
                cout << " " << element <<  " |";
        }

        cout << '\n' << "  |";

        for (int grid {0}; grid < 31; grid ++) //Loop prints out bottom edge of the chess board.
            cout << "_";

        cout << "|" << '\n';

        sidenumbers ++; //Increases side numbers by one to print out appropriate row numbers of board.
    }

    int counter{1};

    cout << '\n' << "            Squares Visited" << endl;

    do
    {
        rownum = 0;

        for (auto const comparerow: comparesquares) //Loop accesses every row of the comparison 2D array (comparesquares).
        {
            columnnum = 0;

            for (auto const compareelement: comparerow) //Loop accesses every element of a row of the comparison 2D array to see if a value appears indicating that the square has already been visited.
            {
                if (compareelement == counter) //Condition ensures that if square that has been visited is found, breaks out of loop.
                    break;

                if (columnnum < 7) //Condition ensures that the columnnum value doesn't go past 7 (8 or larger isn't possible column).
                    columnnum ++;
            }

            if (comparesquares.at(rownum).at(columnnum) == counter) //Condition ensures that once visited square is found, breaks out of this loop too.
                break;

            if (rownum < 7) //Condition ensures that rownum value doesn't go past 7 (8 or larger isn't possible row).
                rownum ++;
        }

        if (comparesquares.at(rownum).at(columnnum) == counter) //Condition ensures that if square that has been visited is found, prints coordinates of square.
        {
            cout << "(" << rownum << ", " << columnnum << ") ";

            if (counter % 5 == 0) //Condition ensures that after every fifth coordinate, a new row of coordinates is made.
                cout << endl;
        }

        counter ++; //Counter increases to look for the next square that user has already visited.

    } while (counter <= 64); //Loop ensures that all squares are checked for values that indicate that the square has already been visited.

    cout << endl;
}

//Purpose: Generates possible positions for knight to move based on current position.
void possiblemoves (array<array<int, 8>, 8>& boardpositions, array <int, 2> knightcurrently, array<int, 8>& usercheck)
{   //Position 0
    if (knightcurrently.at(0) - 1 >= 0 && knightcurrently.at(1) + 2 < 8) //Condition finds the row and column numbers of the possible position, and ensures that they're possible on the board.
    {
        boardpositions.at(knightcurrently.at(0) - 1).at(knightcurrently.at(1) + 2) = 0; //Updates value of element of array that matches possible position on board.
        usercheck[0] = 0; //Updates usercheck value and passes by reference back to main function (values in this array are possible positions).
    }

    //Position 1
    if (knightcurrently.at(0) - 2 >= 0 && knightcurrently.at(1) + 1 < 8) //Condition finds the row and column numbers of the possible position, and ensures that they're possible on the board.
    {
        boardpositions.at(knightcurrently.at(0) - 2).at(knightcurrently.at(1) + 1) = 1; //Updates value of element of array that matches possible position on board.
        usercheck[1] = 1; //Updates usercheck value and passes by reference back to main function (values in this array are possible positions).
    }

    //Position 2
    if (knightcurrently.at(0) - 2 >= 0 && knightcurrently.at(1) - 1 >= 0) //Condition finds the row and column numbers of the possible position, and ensures that they're possible on the board.
    {
        boardpositions.at(knightcurrently.at(0) - 2).at(knightcurrently.at(1) - 1) = 2; //Updates value of element of array that matches possible position on board.
        usercheck[2] = 2; //Updates usercheck value and passes by reference back to main function (values in this array are possible positions).
    }

    //Position 3
    if (knightcurrently.at(0) - 1 >= 0 && knightcurrently.at(1) - 2 >= 0) //Condition finds the row and column numbers of the possible position, and ensures that they're possible on the board.
    {
        boardpositions.at(knightcurrently.at(0) - 1).at(knightcurrently.at(1) - 2) = 3; //Updates value of element of array that matches possible position on board.
        usercheck[3] = 3; //Updates usercheck value and passes by reference back to main function (values in this array are possible positions).
    }

    //Position 4
    if (knightcurrently.at(0) + 1 < 8 && knightcurrently.at(1) - 2 >= 0) //Condition finds the row and column numbers of the possible position, and ensures that they're possible on the board.
    {
        boardpositions.at(knightcurrently.at(0) + 1).at(knightcurrently.at(1) - 2) = 4; //Updates value of element of array that matches possible position on board.
        usercheck[4] = 4; //Updates usercheck value and passes by reference back to main function (values in this array are possible positions).
    }

    //Position 5
    if (knightcurrently.at(0) + 2 < 8 && knightcurrently.at(1) - 1 >= 0) //Condition finds the row and column numbers of the possible position, and ensures that they're possible on the board.
    {
        boardpositions.at(knightcurrently.at(0) + 2).at(knightcurrently.at(1) - 1) = 5; //Updates value of element of array that matches possible position on board.
        usercheck[5] = 5; //Updates usercheck value and passes by reference back to main function (values in this array are possible positions).
    }

    //Position 6
    if (knightcurrently.at(0) + 2 < 8 && knightcurrently.at(1) + 1 < 8) //Condition finds the row and column numbers of the possible position, and ensures that they're possible on the board.
    {
        boardpositions.at(knightcurrently.at(0) + 2).at(knightcurrently.at(1) + 1) = 6; //Updates value of element of array that matches possible position on board.
        usercheck[6] = 6; //Updates usercheck value and passes by reference back to main function (values in this array are possible positions).
    }

    //Position 7
    if (knightcurrently.at(0) + 1 < 8 && knightcurrently.at(1) + 2 < 8) //Condition finds the row and column numbers of the possible position, and ensures that they're possible on the board.
    {
        boardpositions.at(knightcurrently.at(0) + 1).at(knightcurrently.at(1) + 2) = 7; //Updates value of element of array that matches possible position on board.
        usercheck[7] = 7; //Updates usercheck value and passes by reference back to main function (values in this array are possible positions).
    }
}

