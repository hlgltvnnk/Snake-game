#pragma once
#define SNAKE_H
#include <map>
#include <vector>
#include <regex>
#include <array>
#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
//#include <conio.h>
#include <chrono>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
//#include <Text.hpp>
class Screen;
class Snake;
class Food;

template <typename Container> 
void outputContainer(const Container& container){
    std::ostream_iterator<typename Container::value_type> cont (std::cout,"\n");
    std::copy(container.begin(), container.end(), cont);
}

template <class Collection, class T>
int IndexOf(const Collection& c, const T& value) {
    auto el = std::find(c.begin(), c.end(), value);
    if(el == c.end())
        return -1;
    int res = distance(c.begin(), el);
    return res;
};

class Snake final {
    public:
        Snake(int x, int y);
        int  getSize();
        void setCoordinates(int change_x, int change_y);
        void growUp(Food &food, Screen screen);
        bool game_over(Screen screen);
        void check_border(Screen screen);
        int snake_size;
        std::array<int, 1000> coordinates_x = {-1};
        std::array<int, 1000> coordinates_y = {-1};
        int score;
        int hungry;
};

