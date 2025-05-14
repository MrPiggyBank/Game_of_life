#include "Game.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <random>
#include <conio.h>


Game::Game() : Game(20,40)
{

}

Game::Game(int chance) : Game()
{
    this->chance = chance;
}

Game::Game(int height, int width) : Game(height, width, 25)
{

}

Game::Game(int height, int width, int chance)
{
    srand(time(nullptr));
    y = height;
    x = width;
    manual = false;
    this->chance = chance;
}

int Game::get_chance()
{
    return chance;
}

void Game::set_chance(int chance)
{
    this->chance = chance;
}

bool Game::get_state(int x, int y)
{
    return grid[y * this->x + x];
}

void Game::set_state(int x, int y, bool state)
{
    grid[y * this->x + x] = state;
}

bool Game::menu()
{
    int n = 0;

    while (1) {
        system("cls");
        stringstream ss;
        ss << "\n\t\t\tCONWAYS GAME OF LIFE\n\n\n";
        if (n == 0) ss << " >";
        else ss << "  ";
        ss << " height: " << y;

        if (y < 10) ss << "   ";
        else if (y < 100) ss << "  ";
        else ss << " ";

        ss << "  \x1b[48;2;255;255;255m\x1b[38;2;255;255;255m";
        for (size_t i = 0; i < y; i += 2)
        {
            ss << ".";
        }
        ss << "\x1b[48;2;0;0;0m\x1b[38;2;0;0;0m";
        for (size_t i = 0; i < (100 - y) / 2; i++)
        {
            ss << "\x1b[48;2;90;90;90m\x1b[38;2;90;90;90m.";
        }
        ss << "\x1b[48;2;0;0;0m\x1b[38;2;0;0;0m."
            << "\x1b[48;2;0;0;0m\x1b[38;2;255;255;255m\n\n";


        if (n == 1) ss << " >";
        else ss << "  ";
        ss << " width:  " << x;

        if (x < 10) ss << "   ";
        else if (x < 100) ss << "  ";
        else ss << " ";

        ss << "  \x1b[48;2;255;255;255m\x1b[38;2;255;255;255m";
        for (size_t i = 0; i < x; i += 4)
        {
            ss << ".";
        }
        ss << "\x1b[48;2;0;0;0m\x1b[38;2;0;0;0m";
        for (size_t i = 0; i < (200 - x) / 4; i++)
        {
            ss << "\x1b[48;2;90;90;90m\x1b[38;2;90;90;90m.";
        }
        ss << "\x1b[48;2;0;0;0m\x1b[38;2;0;0;0m."
            << "\x1b[48;2;0;0;0m\x1b[38;2;255;255;255m\n\n";


        if (n == 2) ss << " >";
        else ss << "  ";
        ss << " chance: " << chance;

        if (chance < 10) ss << "   ";
        else if (chance < 100) ss << "  ";
        else ss << " ";

        ss << "  \x1b[48;2;255;255;255m\x1b[38;2;255;255;255m";
        for (size_t i = 0; i < chance; i += 2)
        {
            ss << ".";
        }
        ss << "\x1b[48;2;0;0;0m\x1b[38;2;0;0;0m";
        for (size_t i = 0; i < (100 - chance) / 2; i++)
        {
            ss << "\x1b[48;2;90;90;90m\x1b[38;2;90;90;90m.";
        }
        ss << "\x1b[48;2;0;0;0m\x1b[38;2;0;0;0m."
            << "\x1b[48;2;0;0;0m\x1b[38;2;255;255;255m\n\n";


        if (n == 3) ss << " >";
        else ss << "  ";
        ss << " auto:   ";

        if (manual) ss << "      \x1b[48;2;255;50;50m\x1b[38;2;255;50;50m....";
        else ss << "      \x1b[48;2;50;255;50m\x1b[38;2;50;255;50m....";

        ss << "\x1b[48;2;0;0;0m\x1b[38;2;0;0;0m."
            << "\x1b[48;2;0;0;0m\x1b[38;2;255;255;255m\n\n";

        if (n == 4) ss << " >";
        else ss << "  ";
        ss << " START";


        cout << ss.str();

        int a = _getch();

        if (a == 224) {
            a = _getch();
        }
        switch (a) {
        case 'W':
        case 'w':
        case 72:
            if (n == 0) n = 4;
            else n--;
            break;
        case 'A':
        case 'a':
        case 75:
            if (y > 1 && n == 0) y--;

            if (x > 1 && n == 1) x--;
        
            if (chance > 0 && n == 2) chance--;
        case '\r':
            if (manual && n == 3) manual = false;
            else if (n == 3) manual = true;
        
            if (n == 4) return start();
            break;
        case 'S':
        case 's':
        case 80:
            if (n == 4) n = 0;
            else n++;
            break;
        case 'D':
        case 'd':
        case 77:
            if (y < 100 && n == 0) y++;

            if (x < 200 && n == 1) x++;

            if (chance < 100 && n == 2) chance++;

            if (manual && n == 3) manual = false;
            else if (n == 3) manual = true;

            if (n == 4) return start();
            break;
        }
    
    }
}




bool Game::start()
{

    for (size_t i = 0; i < y*x; i++)
    {
        if (rand() % 100 < chance) grid.push_back(true);
        else grid.push_back(false);
    }
    int n = 0;
    if (manual) {
        while (true) {
            if (n == 27) return 1;
            step();
            n = _getch();
            if (n == 224) _getch();  //bez ovoga strelice i slicno radi dva koraka umjesto jednog
        }
    }
    else {
        while (true) {
            step();
            auto begin = chrono::high_resolution_clock::now();
            while (true) {
                auto end = chrono::high_resolution_clock::now();
                if (chrono::duration_cast<chrono::milliseconds>(end - begin).count() > 1980) break; // 1980 milisekundi zbog male greske brojaca
            }
        }
    }
}

bool Game::step()
{
    system("cls");
    stringstream ss;
    ss << "\n\n";
        
    if (manual) ss << "ESC - exit game \n\nany key - step forward\n\n";

    vector<int> v;
    for (size_t i = 0; i < y; i++)
    {
        for (size_t j = 0; j < x; j++)
        {
            int n = 0;
            if (i) {
                if (j) n += get_state(j - 1,i - 1);
                n += get_state(j, i - 1);
                if (j < x - 1) n += get_state(j + 1, i - 1);
            }
            if (j) n += get_state(j - 1, i);
            if (j < x - 1) n += get_state(j + 1, i);

            if (i < y - 1) {
                if (j) n += get_state(j - 1, i + 1);
                n += get_state(j, i + 1);
                if (j < x - 1) n += get_state(j + 1, i + 1);
            }
            v.push_back(n);
        }
    }
    
    ss << "+";
    for (size_t i = 0; i < x; i++)
    {
        ss << "-";
    }
    ss << "+\n|";
    for (size_t i = 0; i < v.size(); i++)
    {

        if ((i % x) == 0 && i != 0) ss << "\x1b[48;2;0;0;0m\x1b[38;2;255;255;255m|\n|";
        if (grid[i]) ss << "\x1b[48;2;255;255;255m\x1b[38;2;255;255;255m.";
        else ss << "\x1b[48;2;0;0;0m\x1b[38;2;0;0;0m.";


        if (v[i] == 3)
        {
            grid[i] = true;
        }

        else if (v[i] != 2)
        {
            grid[i] = false;
        }
    }
    ss << "\x1b[48;2;0;0;0m\x1b[38;2;255;255;255m|\n+";
    for (size_t i = 0; i < x; i++)
    {
        ss << "-";
    }
    ss << "+";
    cout << ss.str();
    return 0;
}
