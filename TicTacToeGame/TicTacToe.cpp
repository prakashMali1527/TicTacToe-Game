#include <iostream>
#include <sstream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;
void Menu();
void continueGame();
void makeGrid();
void playMove();
class player
{
public:
    string name;
    char symbol;
} firstPlayer, secondPlayer;
vector<vector<char>> gridBox(3, vector<char>(3));
int turn = 1;
template <typename T>
void alert(T item)
{
    ostringstream os;
    os << item;
    MessageBoxA(NULL, os.str().c_str(), "Message", MB_OK | MB_ICONINFORMATION);
}
void gotoxy(short int xCoordinate, short int yCoordinate)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {xCoordinate, yCoordinate};
    SetConsoleCursorPosition(h, position);
}
void makeGrid()
{
    for (int j = 6; j < 14; j++)
    {
        gotoxy(45, j);
        cout << "|      |";
    }
    gotoxy(38, 8);
    cout << "-----------------------";
    gotoxy(38, 11);
    cout << "-----------------------";
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (gridBox[row][col] == 'X' || gridBox[row][col] == 'O')
            {
                gotoxy(41 + row * 7, 7 + col * 3);
                cout << gridBox[row][col];
            }
        }
    }
}
int getX(int position)
{
    return (position - 1) % 3;
}
int getY(int position)
{
    return (position - 1) / 3;
}
bool isCorrectPosition(int position)
{
    if (position >= 1 && position <= 9 && gridBox[getX(position)][getY(position)] == '\0')
        return true;
    else
        return false;
}
string Winner()
{
    int cntX = 0, cntO = 0;
    char winnerSymbol = '\0';
    // check horizontal
    for (int row = 0; row < 3; row++)
    {
        cntX = 0;
        cntO = 0;
        for (int col = 0; col < 3; col++)
        {
            if (gridBox[row][col] == 'X')
                cntX++;
            else if (gridBox[row][col] == 'O')
                cntO++;
        }
        if (cntX == 3)
            winnerSymbol = 'X';
        else if (cntO == 3)
            winnerSymbol = 'O';
    }
    // check vertical
    for (int col = 0; col < 3; col++)
    {
        cntX = 0;
        cntO = 0;
        for (int row = 0; row < 3; row++)
        {
            if (gridBox[row][col] == 'X')
                cntX++;
            else if (gridBox[row][col] == 'O')
                cntO++;
        }
        if (cntX == 3)
            winnerSymbol = 'X';
        else if (cntO == 3)
            winnerSymbol = 'O';
    }
    // check diagonal
    if (gridBox[0][0] == gridBox[1][1] && gridBox[1][1] == gridBox[2][2])
    {
        winnerSymbol = gridBox[1][1];
    }
    else if (gridBox[0][2] == gridBox[1][1] && gridBox[1][1] == gridBox[2][0])
    {
        winnerSymbol = gridBox[1][1];
    }

    if (winnerSymbol == firstPlayer.symbol)
        return firstPlayer.name;
    else if (winnerSymbol == secondPlayer.symbol)
        return secondPlayer.name;
    return "";
}
void playMove(player &p)
{
    char input;
    gotoxy(43, 15);
    cout << p.name << " turn :> ";
    input = getch();
    int position = (int)(input - '0');
    cout << input;
    if (!isCorrectPosition(position))
    {
        alert("Wrong Position!!");
        playMove(p);
    }
    turn++;
    gridBox[getX(position)][getY(position)] = p.symbol;
    // check for winner
    string winnerName = Winner();
    if (winnerName != "")
    {
        system("color 37");
        makeGrid();
        gotoxy(43, 17);
        cout << winnerName << " Wins!!!" << endl;
        exit(1);
    }
    continueGame();
}
void continueGame()
{
    system("cls");
    gotoxy(30, 0);
    cout << "<------------Game Started------------->" << endl;
    cout << firstPlayer.name << " -> " << firstPlayer.symbol << endl;
    cout << secondPlayer.name << " -> " << secondPlayer.symbol << endl;
    makeGrid();
    while (turn <= 9)
    {
        if (turn % 2)
            playMove(firstPlayer);
        else
            playMove(secondPlayer);
    }
    gotoxy(44, 17);
    cout << "Game Draw!!" << endl;
}
void Menu()
{
    gotoxy(35, 0);
    cout << "<-----------MENU----------->" << endl;
    cout << "Enter player1 name : ";
    cin >> firstPlayer.name;
    cout << "Enter player1 symbol : ";
label1:
    firstPlayer.symbol = getch();
    firstPlayer.symbol = toupper(firstPlayer.symbol);
    cout << firstPlayer.symbol;
    switch (firstPlayer.symbol)
    {
    case 'X':
        break;
    case 'O':
        break;
    default:
        alert("Choose only from X/O");
        cout << "\b";
        goto label1;
    }
    cout << "\nEnter player2 name : ";
    cin >> secondPlayer.name;
    cout << "Enter player2 symbol : ";
label2:
    secondPlayer.symbol = getch();
    secondPlayer.symbol = toupper(secondPlayer.symbol);
    cout << secondPlayer.symbol;
    if (secondPlayer.symbol == firstPlayer.symbol || (secondPlayer.symbol != 'X' && secondPlayer.symbol != 'O'))
    {
        alert("Wrong Choice!!");
        cout << "\b";
        goto label2;
    }
}
int main()
{
    system("cls");
    system("color 07");
    Menu();
    continueGame();
}
