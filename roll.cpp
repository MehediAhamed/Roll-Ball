#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void delay(int num);
int playRollBall();
void gotoxy(int x, int y);                // input coordinate
void setcursor(bool visible, DWORD size); // set bool visible = 0(invisible), bool visible = 1(visible)
int serialRB(int x, FILE *fpRB);
int deserialRB(int x, FILE *fpRB);
void instructionsRollBall();
void updatescoreRollBall(int *scoreRB);
void gameoverRollBall(int *scoreRB);

int main()
{
    setcursor(0, 0);
    do
    {
        system("cls");
        system("color 1E");
        gotoxy(43, 9);
        cout << " -------------------------- ";
        gotoxy(43, 10);
        cout << " |   >> ROLL THE BALL <<  | ";
        gotoxy(43, 11);
        cout << " --------------------------";
         gotoxy(45, 13);
        cout << "1. START GAME";
        gotoxy(45, 15);
        cout << "2. INSTRUCTIONS";
        gotoxy(45, 17);
        cout << "3. QUIT";
        gotoxy(45, 19);
        cout << "Select an Option- ";
        char op = getch();

        if (op == '1')
        {
            Beep(1459,105);
            playRollBall();
        }

        else if (op == '2')
        {
            Beep(1459,105);
            instructionsRollBall();
        }

        else if (op == '3')
        {
            system("cls");
            system("color 1");

            Beep(1459,105);
            exit(0);
        }
    } while (1);
    return 0;
}

int playRollBall()
{
    system("cls");
    //system("color 1");
    srand(time(0));
    char mv;
    char repeat = 'y';
    int highscore = 0;
    while (repeat == 'y')
    {

         system("cls");
        system("color 9");
        gotoxy(45, 13);
        cout << "Press Any Key To Start...";
        getch();
        system("cls");
        setcursor(0,0);
        system("color 6");
        int change=0;
        int scoreRB, pointRB = 0;
        bool isBool = true;
        int x = 2, y = 20;
        int scrnCol[3];
        int scrnRow[3];
        scrnRow[0] = 8;                     // three initial positions for the bars
        scrnRow[1] = 15;
        scrnRow[2] = 23;
        for (int i = 0; i < 3; i++)
        {
            scrnCol[i] = (rand() % 27) + 2; // used for determing the gap in bars
        }
        string grid[25][40];
        for (int i = 0; i < 25; i++)        // creates the outer border
        {
            for (int j = 0; j < 40; j++)
            {
                if (i == 0 || i == 24 || j == 39 || j == 0)
                    grid[i][j] = 219;
                else
                    grid[i][j] = " ";
            }
        }
        while (isBool == true)
        {
            change++;
            if (change%2 == 0)
                system("color E");
            else
                system("color 6");

            for (int i = 0; i < 3; i++)     // removes the bars
            {
                for (int j = 1; j < 39; j++)
                {
                    grid[scrnRow[i]][j] = " ";
                }
            }
            for (int i = 0; i < 3; i++)     // changes the position of the bars closer
            {
                scrnRow[i]--;
            }

            for (int i = 0; i < 3; i++)     // generates the bars
            {
                grid[scrnRow[i]][scrnCol[i]] = "_";
                grid[scrnRow[i]][scrnCol[i] + 1] = "_";
                grid[scrnRow[i]][scrnCol[i] + 2] = "_";
                grid[scrnRow[i]][scrnCol[i] + 3] = "_";
                grid[scrnRow[i]][scrnCol[i] + 4] = "_";
                grid[scrnRow[i]][scrnCol[i] + 5] = "_";
                grid[scrnRow[i]][scrnCol[i] + 6] = "_";
                grid[scrnRow[i]][scrnCol[i] + 7] = "_";
                grid[scrnRow[i]][scrnCol[i] + 8] = "_";
                grid[scrnRow[i]][scrnCol[i] + 9] = "_";
            }
            for (int i = 0; i < 3; i++)     // pushes back a bar at the end when its nearest
            {
                if (scrnRow[i] == 1)
                {
                    scrnRow[i] = 23;
                    scrnCol[i] = (rand() % 27) + 2;
                }
            }
            if (grid[x][y] != "_")
            {
                grid[x][y] = " ";           // clear the ball
            }

            if (kbhit())                    // makes jump
            {
                mv = getch();
                if (mv == 75)
                    y = y - 2;
                else if (mv == 77)
                    y = y + 2;
            }
            if (grid[x][y] == "_" || grid[x - 1][y] == "_")
                x--;
            else
                x++;

            pointRB++;

            scoreRB = pointRB/5;

            if (x < 2 || x > 23 || y < 2 || y > 38) // die conditions
                isBool = false;

            grid[x][y] = "O";            // jetpack player
            for (int i = 1; i < 39; i++) // removes the bar at nearest
            {

                grid[1][i] = " ";
            }






            for (int i = 0; i < 25; i++) // prints the entire screen again
            {

                for (int j = 0; j < 40; j++)
                {


                    cout << grid[i][j];
                }


                cout << endl;
            }


            cout << "\n\t\tSCORE : " << scoreRB << endl;

            Sleep(200);
            system("cls");
        }
        updatescoreRollBall(&scoreRB);
        gameoverRollBall(&scoreRB);
    }
    system("color 7");
    system("cls");
    return 0;
}



void instructionsRollBall()
{

    system("cls");
    gotoxy(43, 9);
    system("color 27");
    cout << "Instructions";
    gotoxy(41, 10);
    cout << "________________\n\n";
    gotoxy(41, 12);
    cout << ">> Avoid touching the border. Use the bars to stay in the screen. ";
    gotoxy(41, 13);
    cout << ">> Press '<-' to move left";
    gotoxy(41, 14);
    cout << ">> Press '->' to move right";
    gotoxy(41, 15);
    cout << ">> Press 'escape' to exit\n\n";
    gotoxy(41, 17);
    cout << "Press any key to go back to menu";
    getch();
}

void gotoxy(int x, int y) // input coordinate
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) // set bool visible = 0(invisible), bool visible = 1(visible)
{
    if (size == 0)
        size = 20; // size is 0 to 20
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void gameoverRollBall(int *scoreRB)
{
    Beep(6059, 80);
    system("cls");
    system("color 4F");
    char ch;
    cout << endl;
    gotoxy(44, 10);
    cout << "---->>>> Game Over <<<<----" << endl;
    gotoxy(44, 11);
    cout << "___________________________" ;

    FILE *fpRB = fopen("roll.txt", "r");
    int hs = deserialRB(*scoreRB, fpRB);

    gotoxy(45, 14);
    cout << "Your Score :" << *scoreRB << endl;
    gotoxy(45, 15);
    cout << "High Score :" << hs << endl;
    gotoxy(45, 18);
    cout << "RETRY? (y/n) = "; // if wannna play again
    cin >> ch;
    ch = tolower(ch);
    if (ch == 'y')
    {
        playRollBall();
    }
    else
    {
       // system("color 7");
        system("cls");
        exit(0);
    }
    getch();
}

void updatescoreRollBall(int *scoreRB) // print score
{
    //Beep(700, 80);
    FILE *fpRB = fopen("roll.txt", "a+");
    serialRB(*scoreRB, fpRB);

}

int serialRB(int x, FILE *fpRB)
{
    fpRB = fopen("roll.txt", "a+");
    fprintf(fpRB, "%d ", x);
    fclose(fpRB);
}

int deserialRB(int x, FILE *fpRB)
{
    int i = 0;
    int num[10000];
    char ch;

    fpRB = fopen("roll.txt", "r");

    while (!feof(fpRB))
    {
        fscanf(fpRB, "%d ", &num[i]);
        i++;
    }
    remove("roll.txt");
    fclose(fpRB);

    for (int k = 0; k < i - 1; k++)
    {
        for (int j = 0; j < i - k - 1; j++)
        {
            if (num[j + 1] > num[j])
            {
                int temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }

    FILE *fpRB1 = fopen("roll.txt", "w");
    for (int k = 0; k < i; k++)
    {
        fprintf(fpRB1, "%d ", num[k]);
    }

    fclose(fpRB1);
    return num[0];
}
