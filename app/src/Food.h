class Screen;
#include <vector>
//class Snake;
//class Food;

class Food final {
 public:
  Food(Screen screen);
  void place_food(Screen screen);
  void delete_food(int pos);
  bool food_check();
  std::vector<int> food_x;
  std::vector<int> food_y;
  std::vector<int> type;
  int last_occur;
};
