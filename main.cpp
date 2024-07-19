#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;

bool gameOver;
// Arena
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
// Movement & custom variables of type eDirection
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
// Tail of the snake
int tailX[100], tailY[100];
int tailLength;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tailLength = 0;
}

void Draw() {
    system("cls");
    // Upper wall
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";
            if (i == y && j == x) cout << "O";
            else if (i == fruitY && j == fruitX) cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }

    // Lower wall
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    cout << "The Score is: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    // Walls don't kill
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailLength++;
    }
}

int main() {
    srand(time(NULL));
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        _sleep(100); // Slow down the game loop for better playability
    }
    return 0;
}
