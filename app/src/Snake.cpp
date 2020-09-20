#include "Snake.h"
#include "Food.h"
#include "Screen.h"

Snake::Snake(int x, int y) : score(0), snake_size(4), hungry(1){
  coordinates_x[0] = x;
  coordinates_y[0] = y + 20;
  coordinates_x[1] = x;
  coordinates_y[1] = y;
}

int Snake::getSize() {
    return snake_size;
}

void Snake::setCoordinates(int change_x, int change_y) {
    // body
    for (int i = snake_size - 1; i >= 1; i--) {
      coordinates_x[i] = coordinates_x[i - 1];
      coordinates_y[i] = coordinates_y[i - 1];
    }
  // head
    coordinates_x[0] += change_x;
    coordinates_y[0] += change_y;
    
}

void Snake::growUp(Food &food, Screen screen) {
  int pos = -1;
  for (int i = 0; i < food.type.size(); i++)
    if (coordinates_x[0] == food.food_x[i] && coordinates_y[0] == food.food_y[i])
      pos = i;

  if (pos!= -1) {
    if(food.type[pos] == 5)
      screen.kill_table(*this);
    snake_size++;
    food.delete_food(pos);
    score += 15;
    hungry = 1;
      }
  else 
    hungry++;
  if (hungry % 100 == 0)
    snake_size--;
}

void Snake::check_border(Screen screen) {
  // если вышла за поле, перебросить на противоположное
  if (coordinates_x[0] > screen.N)
    coordinates_x[0] = 0;
  else if (coordinates_x[0] < -1) 
    coordinates_x[0] = screen.N;
  else if(coordinates_y[0] > screen.M) 
    coordinates_y[0] = 0;
  else if(coordinates_y[0] < -1)
    coordinates_y[0] = screen.M;
  else return;
}

bool Snake::game_over(Screen screen) {
  for (int i = 1; i <= snake_size; ++i)
    //съела себя
    if (coordinates_x[0] == coordinates_x[i] &&
        coordinates_y[0] == coordinates_y[i])
      return true;
    //слишком маленькая
    if(snake_size < 2)
      return true;
    if (screen.barier == true) 
      return screen.barier_crush(coordinates_x[0], coordinates_y[0]);
  return false;
}
