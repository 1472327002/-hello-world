#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#define PADDLE_SIZE 4

int ballX, ballY, ballDX, ballDY;
int leftPaddle, rightPaddle;

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw() {
    system("cls");
    // 顶部边界
    for(int i=0; i<WIDTH; i++) printf("-");
    printf("\n");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH-1) printf("|"); // 侧边界
            else if (x == 2 && y >= leftPaddle && y < leftPaddle+PADDLE_SIZE) printf("|"); // 左挡板
            else if (x == WIDTH-3 && y >= rightPaddle && y < rightPaddle+PADDLE_SIZE) printf("|"); // 右挡板
            else if (x == ballX && y == ballY) printf("O"); // 球
            else printf(" ");
        }
        printf("\n");
    }
    // 底部边界
    for(int i=0; i<WIDTH; i++) printf("-");
    printf("\n");
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 'w' && leftPaddle > 0) leftPaddle--;
        if (ch == 's' && leftPaddle+PADDLE_SIZE < HEIGHT) leftPaddle++;
        if (ch == 72 && rightPaddle > 0) rightPaddle--;         // 上箭头
        if (ch == 80 && rightPaddle+PADDLE_SIZE < HEIGHT) rightPaddle++; // 下箭头
    }
}

void logic() {
    // 移动球
    ballX += ballDX;
    ballY += ballDY;

    // 碰到上下墙壁反弹
    if (ballY == 0 || ballY == HEIGHT - 1) ballDY = -ballDY;

    // 碰到左挡板
    if (ballX == 3 && ballY >= leftPaddle && ballY < leftPaddle+PADDLE_SIZE) ballDX = -ballDX;
    // 碰到右挡板
    if (ballX == WIDTH-4 && ballY >= rightPaddle && ballY < rightPaddle+PADDLE_SIZE) ballDX = -ballDX;

    // 出界
    if (ballX == 0 || ballX == WIDTH-1) {
        // 重新开始
        ballX = WIDTH/2;
        ballY = HEIGHT/2;
        ballDX = (ballDX > 0) ? -1 : 1;  // 改变方向
        ballDY = (ballDY > 0) ? -1 : 1;
    }
}

int main() {
    // 初始化球和挡板位置
    leftPaddle = rightPaddle = HEIGHT/2 - PADDLE_SIZE/2;
    ballX = WIDTH/2; ballY = HEIGHT/2;
    ballDX = -1; ballDY = 1;

    while (1) {
        draw();
        input();
        logic();
        Sleep(50);
    }
    return 0;
}
