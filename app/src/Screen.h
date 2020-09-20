#include <array>
#include <SFML/Graphics.hpp>
using namespace sf;
//class Screen;
class Snake;
class Food;

class Screen final {
 public:
  Screen(bool levl, std::string direct);
  void show_table(Snake snake, Food food, RenderWindow &window);
  void kill_table(Snake snake);
  bool barier_crush(int x, int y);
  std::array<std::array<char, 1000>, 1000> a;
  int N;
  int M;
  bool barier;
  std::string dir;
  RenderWindow *win;
};
