#include "Header.h"

// генерация локации
void generation_location(int HEIGHT, int WIDTH, int** location) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // сколько видов объектов заданной значении
            location[y][x] = rand() % 6; // 0 1 2 3 4 5

            // стены по краям
            if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1)
                location[y][x] = WALL; // стена
            int prob = rand() % 2; 

            // вход и выход
            if (x == 0 && y == 2 || x == WIDTH - 1 && y == HEIGHT - 3)
                location[y][x] = HALL; // пустое место

            if (x == 2 && y == 2)
                location[y][x] = HALL;

            // вероятность объектов сколько их будет
            if (location[y][x] == ENEMY) { // враги
                int prob = rand() % 5;
                if (prob != 0)
                    location[y][x] = HALL;
            }

            if (location[y][x] == COIN) { // монеты
                int prob = rand() % 5;
                if (prob != 0)
                    location[y][x] = HALL;
            }

            if (location[y][x] == BONUS_ENERGY) { // бонус энергии
                int prob = rand() % 5;
                if (prob != 0)
                    location[y][x] = HALL;
            }

            if (location[y][x] == BONUS_HP) { // бонус хп
                int prob = rand() % 10;
                if (prob != 0)
                    location[y][x] = HALL;
            }
        }
    }
}

// показ локации
void show_location(int HEIGHT, int WIDTH, int** location, HANDLE h) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            switch (location[y][x]) {
            case HALL: // пустое место
                cout << " ";
                break;

            case WALL: // стена
                SetConsoleTextAttribute(h, DARKGREEN);
                cout << (char)177;
                break;

            case COIN: // монета
                SetConsoleTextAttribute(h, YELLOW);
                cout << (char)15;
                break;

            case ENEMY: // враги
                SetConsoleTextAttribute(h, RED);
                cout << (char)2;
                break;

            case BONUS_ENERGY: // бонус энергии
                SetConsoleTextAttribute(h, BLUE);
                cout << (char)4;
                break;

            case BONUS_HP: // бонус хп
                SetConsoleTextAttribute(h, PINK);
                cout << (char)3;
                break;

            default:
                cout << location[y][x];
                break;
            }
        }
        cout << "\n";
    }
}

// показ героя
void show_hero(HANDLE h, const Hero& hero) {
    SetConsoleCursorPosition(h, hero.position);
    SetConsoleTextAttribute(h, BLUE);
    cout << (char)1;
}

// очищение позиции
void clear_position(HANDLE h, const Hero& hero) {
    SetConsoleCursorPosition(h, hero.position);
    cout << " ";
}

// монеты
int object_COINS(int** location, Hero& hero) {
    if (location[hero.position.Y][hero.position.X] == COIN) {
        hero.coins++;
        location[hero.position.Y][hero.position.X] = HALL;
        message_coin(1, 16, YELLOW, hero.coins);
    }
    return hero.coins;
}

// сообщение собирании монет
void message_coin(int x, int y, int color, int message) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position_text;
    position_text.X = x;
    position_text.Y = y;
    SetConsoleCursorPosition(h, position_text);
    SetConsoleTextAttribute(h, color);
    cout << "Coins: " << message;
}

// враг наносит урон героя
int enemy_DAMAGE(int** location, Hero& hero) {
    if (location[hero.position.Y][hero.position.X] == ENEMY) {
        location[hero.position.Y][hero.position.X] = HALL;
        int damage = 20;
        hero.HP -= damage;
    }
    return hero.HP;
}

// добавление персонажа хп
int object_BONUS_HP(int** location, Hero& hero) {
    if (location[hero.position.Y][hero.position.X] == BONUS_HP) {
        location[hero.position.Y][hero.position.X] = HALL;
        if (hero.HP < 100) {
            int add_HP = 20;
            hero.HP += add_HP;
        }
        if (hero.HP < 100) {
            int HP = 100;
        }
    }
    return hero.HP;
}

// сообщение показа текущего хп
void message_HP(int x, int y, int color, int HP) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position_text;
    position_text.X = x;
    position_text.Y = y;
    SetConsoleCursorPosition(h, position_text);
    SetConsoleTextAttribute(h, RED);
    cout << "HP: " << HP << " ";
}

// добавление персонажа энергию
int object_BONUS_ENERGY(int** location, Hero& hero) {
    if (location[hero.position.Y][hero.position.X] == BONUS_ENERGY) {
        location[hero.position.Y][hero.position.X] = HALL;
        int add_energy = 60;
        hero.energy += add_energy;
    }
    return hero.energy;
}

// сообщение показа текущего энергии
void message_energy(int x, int y, int color, int energy) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position_text;
    position_text.X = x;
    position_text.Y = y;
    SetConsoleCursorPosition(h, position_text);
    SetConsoleTextAttribute(h, BLUE);
    cout << "Energy: " << energy << " ";
}

// движок игры
void engine(int HEIGHT, int WIDTH, int** location, Hero& hero) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    while (true) {
        int code = _getch();
        if (code == 224)
            code = _getch();
        clear_position(h, hero);

        switch (code) {
        case ENTER:
            break;
        case SPACEBAR:
            break;
        case ESCAPE:
            system("cls"); // очищение консоли
            exit(0); // завершение программы   
            return;
        case RIGHT:
            if (hero.position.X > 0 && location[hero.position.Y][hero.position.X + 1] != WALL) {
                hero.position.X++; // движение право героя 
                hero.energy -= 10;
            }
            break;
        case LEFT:
            if (hero.position.X > 0 && location[hero.position.Y][hero.position.X - 1] != WALL) {
                hero.position.X--; // движение лево героя 
                hero.energy -= 10;
            }
            break;
        case UP:
            if (location[hero.position.Y - 1][hero.position.X] != WALL) {
                hero.position.Y--; // движение вверх героя
                hero.energy -= 10;
            }
            break;
        case DOWN:
            if (location[hero.position.Y + 1][hero.position.X] != WALL) {
                hero.position.Y++; // движение вниз героя
                hero.energy -= 10;
            }
            break;
        default:
            cout << code << "\n";
            break;
        }

        // нашли выход - победа!
        if (hero.position.X == WIDTH - 1 && hero.position.Y == HEIGHT - 3) {
            // сообщение о результате
            string result_message = "Победа! Ваши результаты:\n";
            result_message += "Монеты: " + to_string(hero.coins) + "\n";
            result_message += "Здоровье: " + to_string(hero.HP) + "\n";
            result_message += "Энергия: " + to_string(hero.energy) + "\n";

            // запись результата в файл
            FILE* f = nullptr;
            fopen_s(&f, "C:/Maze_Result/result.txt", "w");
            if (f != nullptr) {
                fputs(result_message.c_str(), f);
                fclose(f);
            }

            // победа
            MessageBoxA(NULL, result_message.c_str(), "Победа!", MB_OK | MB_ICONINFORMATION);
            system("cls"); // очищение консоли
            exit(0); // завершение программы
        }

        show_hero(h, hero);
        enemy_DAMAGE(location, hero);
        object_COINS(location, hero);
        object_BONUS_ENERGY(location, hero);
        object_BONUS_HP(location, hero);
        message_HP(43, 16, RED, hero.HP);
        message_energy(20, 16, BLUE, hero.energy);

        // нет хп - поражение
        if (hero.HP <= 0) {
            MessageBoxA(NULL, "Вы погибли!", "Игра окончена", MB_OK | MB_ICONERROR);
            system("cls"); // очищение консоли
            exit(0); // завершение программы
            return;
        }

        // нет энергии - поражение
        if (hero.energy <= 0) {
            MessageBoxA(NULL, "У вас закончилась энергия!", "Игра окончена", MB_OK | MB_ICONERROR);
            system("cls"); // очищение консоли
            exit(0); // завершение программы
            return;
        }
    }
}

int main() {
    int coins = 0;
    int HP = 100;
    int energy = 900;
    system("title Maze");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(h, &info);

    // размеры карты
    const int WIDTH = 50;
    const int HEIGHT = 15;
    
    // выделение в памяти
    int** location = new int* [HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        location[i] = new int[WIDTH];
    }

    // система нашего героя
    Hero hero;
    hero.position;
    hero.position.X = 1;
    hero.position.Y = 2;
    hero.coins = 0;           
    hero.HP = 100;            
    hero.energy = 900;       

    COORD position;
    position.X = 1;
    position.Y = 2;

    generation_location(HEIGHT, WIDTH, location);
    show_location(HEIGHT, WIDTH, location, h);
    show_hero(h, hero);

    message_coin(1, 16, YELLOW, coins);
    message_HP(43, 16, RED, HP);
    message_energy(20, 16, BLUE, energy);

    engine(HEIGHT, WIDTH, location, hero);

    // освобождение памяти для массивов
    for (int i = 0; i < HEIGHT; i++) {
        delete[] location[i];
    }
    delete[] location;
}