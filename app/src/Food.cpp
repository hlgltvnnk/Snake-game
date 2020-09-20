#include "Snake.h"
#include "Food.h"
#include "Screen.h"

Food::Food(Screen screen) : last_occur(0){
  place_food(screen);
  place_food(screen);
}

void Food::delete_food(int pos) {
    food_x.erase(food_x.begin() + pos);
    food_y.erase(food_y.begin()+ pos);
    type.erase(type.begin()+ pos);
}

// gets current time
int get_time() {
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);
    return localTime->tm_sec;
}

// adding and deleating check
bool Food::food_check() {
  int time = get_time() - last_occur;
  if (time % 5 == 0 && time != 0)
    delete_food(0);
  if ((type.size() < 5 && time >= 4) || (type.size() == 0)) 
    return true;
  return false;
}

// randomize type
int get_type() {
  int random = std::rand() % 100;
  if (random >= 0 && random < 30)
    return 1;
  else if (random >= 30 && random < 60)
    return 2;
  else if (random >= 60 && random < 90)
   return 3;
  else if (random >= 90 && random < 95)
    return 4;
  return 5;
}

bool unique(int x, int y, Food f) {
  for (int i = 0; i < f.food_x.size(); i++) {
    if (f.food_x[i] == x && f.food_y[i] == y) 
      return false; 
  }
  return true;
}

void Food::place_food(Screen screen) {
  last_occur = get_time();
  int x;
  int y;

  std::srand(std::time(NULL));
  while (1) {
    x = std::rand() % screen.N;
    y = std::rand()% screen.M;
    if (y%20 == 0 && x%20 == 0 && unique(x, y, *this)) {
      if (screen.barier == true && screen.barier_crush(x, y) == false)
          break;
      else if (screen.barier == false)
        break;
    }
    
  }
  food_x.push_back(x);
  food_y.push_back(y);
  type.push_back(get_type());
  //std::cout<<type<<std::endl;
}
