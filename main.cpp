#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <ctime>
using namespace std;

enum directions
{
    Right,
    Left,
    Stop
};
directions dir;
int width, height, score, x, y;
bool gameover;

vector<pair<int, int>> mine;
vector<pair<int, int>> food;
vector<pair<int, int>> bombs;

int xmine, ymine, xfood, yfood;

void setup()
{
    width = 20;
    height = 16;
    dir = Stop;
    gameover = false;
    score = 0;
    x = width / 2;
    y = height - 1;

    xmine = rand() % (width - 2) + 1;
    ymine = rand() % (height - 2) + 1;
    xfood = rand() % (width - 3) + 1;
    yfood = rand() % (height - 3) + 1;

    mine.push_back({xmine, ymine});
    food.push_back({xfood, yfood});

    for (int i = 0; i < 5; i++)
    {
        int xb = rand() % (width - 2) + 1;
        int yb = rand() % 3;
        bombs.push_back({xb, yb});
    }

    cout << "===== Welcome to Fly Game =====\n";
    cout << "Press [A] to move Left\n";
    cout << "Press [D] to move Right\n";
    cout << "Press [X] to quit\n";
    system("pause");
}

void draw()
{
    system("cls");

    for (int y_pos = 0; y_pos < height + 2; y_pos++)
    {
        for (int x_pos = 0; x_pos < width; x_pos++)
        {
            if (x == x_pos && y == y_pos)
                cout << "R";
            else if (x_pos == width - 1 || x_pos == 0)
                cout << "|";
            else
            {
                bool printed = true;

                if (xmine == x_pos && ymine == y_pos)
                {
                    cout << "B";
                    printed = false;
                }

                for (auto &f : food)
                    if (f.first == x_pos && f.second == y_pos)
                    {
                        cout << "S";
                        printed = false;
                    }

                for (auto &b : bombs)
                    if (b.first == x_pos && b.second == y_pos)
                    {
                        cout << "*";
                        printed = false;
                    }

                if (printed)
                    cout << " ";
            }
        }
        cout << endl;
    }

    cout << "==============\n";
    cout << "Score: " << score << "\n";
    cout << "==============\n";
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = Left;
            break;
        case 'd':
            dir = Right;
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}

void logic()
{
    if (x == width - 1 || x == 0)
        gameover = true;

    switch (dir)
    {
    case Right:
        x++;
        break;
    case Left:
        x--;
        break;
    }

  
    ymine++;
    yfood++;
    for (auto &b : bombs)
        b.second++;

    if (xmine == x && ymine == y)
        gameover = true;

    for (auto &b : bombs)
    {
        if (b.first == x && b.second == y)
            {
                score-=30;
            }
    }
    if(score<0)
    {
        gameover=true;
        score = 0;
    }
        
    if (xfood == x && yfood == y)
    {
        score += 30;
        xfood = rand() % (width - 3) + 1;
        yfood = rand() % (height - 3) + 1;
    }

    if (ymine > height + 2)
    {
        score += 5;
        xmine = rand() % (width - 2) + 1;
        ymine = 1;
    }

    if (yfood > height + 2)
    {
        xfood = rand() % (width - 3) + 1;
        yfood = 1;
    }

 
    for (int i = 0; i < bombs.size(); i++)
    {
        if (bombs[i].second > height + 2)
        {
            bombs[i].first = rand() % (width - 2) + 1;
            bombs[i].second = 0;
            score += 2; 
        }
    }
}

int main()
{
    srand(time(0));
    setup();

    while (!gameover)
    {
        draw();
        input();
        logic();
        Sleep(150);
    }

    cout << "Game Over!" << endl;
    cout << "Final Score: " << score << endl;
    return 0;
}
