#ifndef header_game
#define header_game

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

enum KeyCodes { ENTER = 13, ESCAPE = 27, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, SPACEBAR = 32 };
enum Colors { DARKGREEN = 2, RED = 12, YELLOW = 14, BLUE = 9, PINK = 4, WHITE = 5, MAGENTA = 13 };
enum Objects { HALL, WALL, COIN, ENEMY, BONUS_ENERGY, BONUS_HP };

struct Hero {
    COORD position;
    int coins;
    int HP;
    int energy;
};

void generation_location(int HEIGHT, int WIDTH, int** location);
void show_location(int HEIGHT, int WIDTH, int** location, HANDLE h);
void show_hero(HANDLE h, const Hero& hero);
void clear_position(HANDLE h, const Hero& hero);
int object_COINS(int** location, Hero& hero);
void message_coin(int x, int y, int color, int message);
int enemy_DAMAGE(int** location, Hero& hero);
int object_BONUS_HP(int** location, Hero& hero);
void message_HP(int x, int y, int color, int HP);
int object_BONUS_ENERGY(int** location, Hero& hero);
void message_energy(int x, int y, int color, int energy);
void engine(int HEIGHT, int WIDTH, int** location, Hero& hero);

#endif