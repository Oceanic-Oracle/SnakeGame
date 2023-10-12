#include <iostream>
#include <vector>
#include <Windows.h>

class Snake {
private:
    char map[451] =
        "*---------------------------*\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "|                           |\n"
        "*---------------------------*\n";

    const int HEIGHT = 15;
    const int WIDTH = 29;

    const int RIGHT = 0;
    const int UP = 1;
    const int LEFT = 2;
    const int DOWN = 3;

    char snake = 'S';
    const int max_len = (HEIGHT - 2) * (WIDTH - 2); 
    int len = 1;
    int move = RIGHT;

    int food_x = 1 + (rand() % (WIDTH - 3));
    int food_y = 1 + (rand() % (HEIGHT - 2));
    char food = 'f';
public:
    void gotoxy(int x, int y) {
        COORD pos = { x, y };
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(output, pos);
    }

    void print_map() {
        std::cout << map << std::endl;
    }

    int ret_HEIGHT() {
        return HEIGHT;
    }

    int ret_WIDTH() {
        return WIDTH;
    }

    int now_len() {
        return len;
    }

    void change_map_snake(int i) {
        map[snake_coordinates_Y[i] * (WIDTH + 1) + snake_coordinates_X[i]] = snake;
    }

    void change_map_food() {
        map[food_y * (WIDTH + 1) + food_x] = food;
    }

    void change_map_space(int i) {
        map[snake_coordinates_Y[i] * (WIDTH + 1) + snake_coordinates_X[i]] = ' ';
    }

    void movement(){
        if (move == RIGHT) {
            ++snake_coordinates_X[0];
        }
        if (move == UP) {
            --snake_coordinates_Y[0];
        }
        if (move == LEFT) {
            --snake_coordinates_X[0];
        }
        if (move == DOWN) {
            ++snake_coordinates_Y[0];
        }
    }

    void wall() {
        if (
            snake_coordinates_Y[0] <= 0 ||
            snake_coordinates_X[0] <= 0 ||
            snake_coordinates_X[0] >= WIDTH - 2 ||
            snake_coordinates_Y[0] >= HEIGHT - 1
           )
        {
            exit(0);
        }
    }

    void food_check() {
        if (snake_coordinates_X[0] == food_x && snake_coordinates_Y[0] == food_y) {
            ++len;
            food_x = 1 + (rand() % (WIDTH - 3));
            food_y = 1 + (rand() % (HEIGHT - 2));
            change_map_food();
        }
    }


    void direction() {
        if (GetKeyState('D') & 0x800 && move != LEFT) {
            move = RIGHT;
        }
        if (GetKeyState('W') & 0x800 && move != DOWN) {
            move = UP;
        }
        if (GetKeyState('A') & 0x800 && move != RIGHT) {
            move = LEFT;
        }
        if (GetKeyState('S') & 0x800 && move != UP) {
            move = DOWN;
        }
    }

    void spiral() {
        for (int i = 1; i <= len; ++i) {
            if (snake_coordinates_X[0] == snake_coordinates_X[i] && snake_coordinates_Y[0] == snake_coordinates_Y[i]) {
                exit(0);
            }
        }
    }

    int snake_coordinates_X[169] = {0};
    int snake_coordinates_Y[169] = {0};
};


int main() {
    double gametime = clock();

	Snake Game;

    Game.snake_coordinates_X[0] = Game.ret_WIDTH() / 2;
    Game.snake_coordinates_Y[0] = Game.ret_HEIGHT() / 2;

    Game.change_map_food();

    while (true) {
        if ((clock() - gametime) / CLOCKS_PER_SEC >= 0.5) {

            Game.food_check();

            Game.direction();

            for (int i = Game.now_len() - 2; i >= 0; --i) {
                Game.snake_coordinates_X[i + 1] = Game.snake_coordinates_X[i];
                Game.snake_coordinates_Y[i + 1] = Game.snake_coordinates_Y[i];
            }

            Game.movement();

            Game.wall();

            Game.spiral();

            Game.gotoxy(0, 0);

            std::cout << "LENGHT: " << Game.now_len() << std::endl;

            for (int i = 0; i != Game.now_len(); ++i) {
                Game.change_map_snake(i);
            }

            Game.print_map();

            for (int i = 0; i != Game.now_len(); ++i) {
                Game.change_map_space(i);
            }

            gametime = clock();
        }
    }
}