#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;

void mainMenu();
void newGame();
void selectPlayer(string players[10], int playerScore[10]);
void startNewGameGrid(int** gameGrid1, int D);
void update(int** gameGrid1, int D);
void updateTheScreen(int** gameGrid1, int D);
void getInput(int** gameGrid1, int D);
void check(int** gameGrid1, int D);

bool isGame;
int isTurn = 1;
int I;
int J;
int openSlotCounter = 0;
int XsScore = 2;
int OsScore = 2;
string players[10] = {"BLUEMUSTARD", "BLUEMUSTARD", "BLUEMUSTARD", "BLUEMUSTARD", "BLUEMUSTARD", "BLUEMUSTARD", "BLUEMUSTARD", "BLUEMUSTARD", "BLUEMUSTARD", "BLUEMUSTARD"};
int playerScore[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int P1;
int P2;


int main()
{
    mainMenu();
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

void mainMenu()
{
    system("cls");
    cout << "1.NEW GAME" << endl << "2.LOAD GAME" << endl << "3.RANKING" << endl << "4.EXIT" << endl;
    char input;
    input = _getch();
    switch (input)
    {
        case '1':
            system("cls");
            newGame();
           break;
        case '2':
            system("cls");
            cout << "In progress";
            break;
        case '3':
            system("cls");
            for (int i = 0; i < 10; i++)
            {
                if (i == 9)
                {
                    cout << i+1 << " . " << players[i] << endl << endl << "        " << playerScore[i] << endl << endl;
                }
                else
                {
                    cout << i+1 << "  . " << players[i] << endl << endl << "        " << playerScore[i] << endl << endl;
                }
            }
            break;
        case '4':
            system("cls");
            cout << "come on!! you didn't even play.";
            break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------

void newGame()
{
    selectPlayer(players, playerScore);
    isGame = true;

    int D;
    cout << "Please enter the dimension of the GAMEGRID (even and bigger than 6) and then press Enter:" << endl;
    cin >> D;

    int** gameGrid1 = new int*[D];
        for(int l = 0; l < D; ++l)
        {
            gameGrid1[l] = new int[D];
        }

    startNewGameGrid(gameGrid1, D);
    update(gameGrid1, D);
}

void selectPlayer(string players[10], int playerScore[10])
{
    system("cls");
    for (int i = 0; i < 10; i++)
    {
        if (i == 9)
        {
            cout << i+1 << " . " << players[i] << endl << endl << "        " << playerScore[i] << endl << endl;
        }
        else
        {
            cout << i+1 << "  . " << players[i] << endl << endl << "        " << playerScore[i] << endl << endl;
        }
    }

    string P1name;
    cout << endl << "Player O, please select a player slot and enter your name : ";
    cin >> P1;
    cout << endl << "name: ";
    cin >> P1name;
    players[P1] = P1name;

    string P2name;
    cout << endl << "Player X, please select a player slot and enter your name : ";
    cin >> P2;
    cout << endl << "name: ";
    cin >> P2name;
    players[P2] = P2name;

    system("cls");
}


void startNewGameGrid(int** gameGrid1, int D)
{

    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < D; j++)
            {

                if ((i + 1 == D/2 && j == i) || (i == D/2 && j == i))
                {
                    gameGrid1[i][j] = 1;
                }
                else if ((i + 1 == D/2 && j == i +1) || (i == D/2 && j == i -1))
                {
                    gameGrid1[i][j] = 2;
                }
                else
                {
                    gameGrid1[i][j] = 0;
                }
            }
    }
}


void update(int** gameGrid1, int D)
{
    check(gameGrid1, D);
    while (isGame)
    {
        updateTheScreen(gameGrid1, D);
        getInput(gameGrid1, D);
        check(gameGrid1, D);
    }
    updateTheScreen(gameGrid1, D);
    char input;
    cout << endl << "Press -m- to go back to the main menu" << endl << "press anything else to exit";
    input = _getch();
    if (input == 'm')
    {
        mainMenu();
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------

void updateTheScreen(int** gameGrid1, int D)
{

    system("cls");
    cout << endl << "  X's score: " << XsScore << " -";
    for(int i = 0; i < (D*4 - 26); i++)
    {
        cout << "-";
    }
    cout << " O's Score: " << OsScore << endl << endl;

    cout << "    ";
    for (int l = 0; l < D; l++)
    {
       if (l < 9)
       {
           cout << (l+1) << "   ";
       }
       else
       {
           cout << (l+1) << "  ";
       }
    }
    cout << endl << "  ";

    for (int j = 0; j < D; j++)
        {
            cout << "----";
        }
        cout << "-" << endl;

    for (int i = 0; i < D; i++)
    {
        if (i < 9)
        {
            cout << (i+1) << " ";
        }
        else
        {
            cout << (i+1);
        }
        for (int j = 0; j < D; j++)
            {
                if (gameGrid1[i][j] == 0)
                {
                    cout << "|   ";
                }
                else if (gameGrid1[i][j] == 1)
                {
                    cout << "| O ";
                }
                else if (gameGrid1[i][j] ==  2)
                {
                    cout << "| X ";
                }
                else if (gameGrid1[i][j] ==  5)
                {
                    if (isTurn == 1)
                    {
                        cout << "| * ";
                    }
                    else
                    {
                        cout << "|   ";
                    }
                }
                else
                {
                    if (isTurn == 2)
                    {
                        cout << "| * ";
                    }
                    else
                    {
                        cout << "|   ";
                    }
                }
            }
        cout << "|" << endl << "  ";
        for (int j = 0; j < D; j++)
        {
            cout << "----";
        }
        cout << "-" << endl;
    }
    cout << endl;

    switch (isTurn)
    {
    case 1:
        cout << players[P1] << "'s turn:";
        break;
    case 2:
        cout << players[P2] <<"'s turn:";
        break;
    }

    if (isGame == false)
    {
        if (XsScore > OsScore)
        {
            cout << "The winner is "<< players[P2] << (XsScore - OsScore) << endl << "now they can hang this victory on the wall next to the mayonnaise drinking cup";
        }
        else  if (OsScore > XsScore)
        {
            cout << players[P1] << "won by " << (XsScore - OsScore) << " much" << endl << "I'm really sure they can get into oxford with this grand victory";
        }
        else
        {
            cout << "Bliemy you two twats couldn't even do this one right" << endl << "getting a tie in othello is so boring its amuzing I must give you that I feel";
        }
    }
}


void getInput(int** gameGrid1, int D)
{
    cout << endl;
    int i, j;
    cout << "Enter the Row:";
    cin >> i;
    cout << "Enter the Col:";
    cin >> j;
    i = i - 1;
    j = j - 1;
    I = i;
    J = j;
    if (gameGrid1[i][j] == 5 && isTurn == 1)
    {
        gameGrid1[i][j] = 1;
        isTurn = 2;
    }
    else if (gameGrid1[i][j] == 6 && isTurn == 2)
    {
        gameGrid1[i][j] = 2;
        isTurn = 1;
    }
}


void check(int** gameGrid1, int D)
{
    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < D; j++)
        {
            if (gameGrid1[i][j] == 5 || gameGrid1[i][j] == 6)
            {
                gameGrid1[i][j] = 0;
            }
        }
    }

    int M;
    int N;
    int Z;
    int V;

    for (int l = I - 1; l < I + 2; l++)
    {
        for (int f = J - 1; f < J + 2; f++)
        {
            if ((l != I && f != J) || (l != I && f == J) || (l == I && f != J))
            {
                if (l >= 0 && l < D && J >= 0 && J < D)
                {

                    if(gameGrid1[I][J] == 2 && gameGrid1[l][f] == 1)
                    {
                        int counter = 0;

                        M = l + (l-I);
                        N = f + (f-J);
                        Z = (l-I);
                        V = (f-J);
                        while (M >= 0 && M < 8 && N >= 0 && N < 8 )
                        {
                            if (gameGrid1[M][N] == 2)
                            {
                                int Q = I + Z;
                                int W = J + V;
                                for(int i = 0; i < counter+1; i++)
                                {
                                    gameGrid1[Q][W] = 2;
                                    Q = Q + Z;
                                    W = W + V;
                                }
                            }
                            M = M + Z;
                            N = N + V;
                            counter = counter + 1;
                        }
                    }

                    else if(gameGrid1[I][J] == 1 && gameGrid1[l][f] == 2)
                    {
                        int counter = 0;

                        M = l + (l-I);
                        N = f + (f-J);
                        Z = (l-I);
                        V = (f-J);
                        while (M >= 0 && M < 8 && N >= 0 && N < 8 )
                        {
                            if (gameGrid1[M][N] == 1)
                            {
                                int Q = I + Z;
                                int W = J + V;
                                for(int i = 0; i < counter+1; i++)
                                {
                                    gameGrid1[Q][W] = 1;
                                    Q = Q + Z;
                                    W = W + V;
                                }
                            }
                            M = M + Z;
                            N = N + V;
                            counter = counter + 1;
                        }
                    }
                }
            }
        }
    }


    int L;
    int F;
    int X;
    int Y;

    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < D; j++)
        {
            for (int l = i - 1; l < i + 2; l++)
            {
                for (int f = j - 1; f < j + 2; f++)
                {
                    if ((l != i && f != j) || (l == i && f != j) || (l != i && f == j))
                    {
                        if (l >= 0 && l < D  &&  f >= 0 && f < D)
                        {
                            if (gameGrid1[i][j] == 0 && gameGrid1[l][f] == 1)
                            {
                                L = l + (l-i);
                                F = f + (f-j);
                                X = (l-i);
                                Y = (f-j);

                                while (L >= 0 && L < D && F >= 0 && F < D && gameGrid1[L-X][F-Y] == 1)
                                {
                                    if (gameGrid1[L][F] == 2)
                                    {
                                        gameGrid1[i][j] = 6;
                                    }
                                    L = L + X;
                                    F = F + Y;
                                }
                            }

                            else if (gameGrid1[i][j] == 0 && gameGrid1[l][f] == 2)
                            {
                                L = l + (l-i);
                                F = f + (f-j);
                                X = (l-i);
                                Y = (f-j);

                                while (L >= 0 && L < D && F >= 0 && F < D && gameGrid1[L-X][F-Y] == 2)
                                {
                                    if (gameGrid1[L][F] == 1)
                                    {
                                        gameGrid1[i][j] = 5;
                                    }
                                    L = L + X;
                                    F = F + Y;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    OsScore = 0;
    XsScore = 0;

    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < D; j++)
        {
            if (gameGrid1[i][j] == 1)
            {
                OsScore = OsScore + 1;
                playerScore[P1] = OsScore;
            }
            else if (gameGrid1[i][j] == 2)
            {
                XsScore = XsScore + 1;
                playerScore[P2] = XsScore;
            }
        }
    }

    openSlotCounter = 0;

    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < D; j++)
        {
            if (gameGrid1[i][j] == 5 || gameGrid1[i][j] == 6)
            {
                openSlotCounter++;
            }
        }
    }

    if (openSlotCounter == 0)
    {
        isGame = false;
    }
}


