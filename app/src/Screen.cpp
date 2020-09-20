#include "Snake.h"
#include "Food.h"
#include "Screen.h"

Screen::Screen(bool levl, std::string direct) : barier(levl) , dir(direct){
  // N - высота.
  // M - ширина таблицы.
  N = 1000;
  M = 700;
}

bool check_touch(int x, int y) {
  //1
  if ((y > 83 && y < 111) && (x > 153 && x < 271))
    return true;
  if ((x > 240 && x < 272) && (y > 111 && y < 204))
    return true;
  if ((y > 174 && y < 204) && (x > 240 && x < 467))
    return true;
  if ((x > 333 && x < 363) && (y > 202 && y < 316))
    return true;
  if ((x > 437 && x < 467) && (y > 202 && y < 245))
    return true;

  //2
  if ((x > 394 && x < 421) && (y > 384 && y < 550))
    return true;
  if ((y > 384 && y < 410) && (x > 421 && x < 566))
    return true;
  if ((x > 536 && x < 566) && (y > 283 && y < 383))
    return true;
  if ((y > 279 && y < 306) && (x > 564 && x < 703))
    return true;
  if ((x > 605 && x < 635) && (y > 224 && y < 281))
    return true;
  if ((x > 673 && x < 703) && (y > 307 && y < 403))
    return true;
  
  //3
  if ((x > 50 && x < 77) && (y > 556 && y < 656))
    return true;
  if ((y > 557 && y < 586) && (x > 75 && x < 222))
    return true;
  if ((x > 193 && x < 222) && (y > 367 && y < 558))
    return true;
  if ((y > 447 && y < 477) && (x > 220 && x < 349))
    return true;

  //4
  if ((y > 453 && y < 483) && (x > 679 && x < 799))
    return true;
  if ((x > 769 && x < 799) && (y > 415 && y < 458))
    return true;
  if ((y > 415 && y < 443) && (x > 497 && x < 889))
    return true;
  if ((x > 859 && x < 889) && (y > 279 && y < 417))
    return true;

  //5
  if ((x > 800 && x < 830) && (y > 45 && y < 119))
    return true;
  if ((y > 117 && y < 147) && (x > 800 && x < 900))
    return true;
  
  //6
  if ((y > 50 && y < 80) && (x > 559 && x < 593))
    return true;

  //7
  if ((y > 248 && y < 276) && (x > 89 && x < 123))
    return true;

  //8
  if ((y > 621 && y < 649) && (x > 453 && x < 487))
    return true;
    
  //9
  if ((y > 607 && y < 635) && (x > 859 && x < 893))
    return true;

  return false;
}

bool Screen::barier_crush(int x, int y) {
  if (check_touch(x, y) || check_touch(x + 20, y) ||
    check_touch(x, y + 20) || check_touch(x + 20, y + 20))
      return true;
  return false;
}

int rotation(Snake snake) {
  // int pos_x = snake.coordinates_x[1] - snake.coordinates_x[2];
  // int pos_y = snake.coordinates_y[1] - snake.coordinates_y[2];
  // int res_x;
  // int res_y;

  // if(pos_x > 0)
  //   res_x = -1;
  // else res_x = -3;
  // if(pos_y > 0)
  //   res_y = -2;
  // else res_y = 0;

  // if (snake.coordinates_x[0] < snake.coordinates_x[1] && res_y != 0)
  //     return res_y + 3;
  // else if (snake.coordinates_x[0] > snake.coordinates_x[1] && res_y != -2)
  //     return res_y + 1;
  // else if (snake.coordinates_y[0] > snake.coordinates_y[1] &&  res_x != -1)
  //     return res_x + 2;
  // else if(snake.coordinates_y[0] < snake.coordinates_y[1] &&  res_x != -3)
  //     return res_x + 4;
    return 0;
}

void draw_snake(RenderWindow &window, Snake snake, int i, std::string dir) {
  Texture texture;
  if (i == 0)
    texture.loadFromFile(dir + "head.png");
  else
    texture.loadFromFile(dir + "snake.png");
  Sprite sprite(texture);
  if (i == 0)
  sprite.setRotation(rotation(snake) * 90.f);
  sprite.setPosition(Vector2f(snake.coordinates_x[i],snake.coordinates_y[i]));
  window.draw(sprite);
}

void draw_food(RenderWindow &window, Food food, int i, std::string dir) {
  Texture texture;

  if (food.type[i] == 1)
    texture.loadFromFile(dir + "grapes.png");
  else if (food.type[i] == 2)
    texture.loadFromFile(dir + "apple.png");
  else if (food.type[i] == 3)
    texture.loadFromFile(dir + "strawb.png");
  else if (food.type[i] == 4)
    texture.loadFromFile(dir + "pie.png");
  else if (food.type[i] == 5)
    texture.loadFromFile(dir + "bomb.png");
  Sprite sprite(texture);
  sprite.setPosition(Vector2f(food.food_x[i], food.food_y[i]));
  window.draw(sprite);
}

void draw_barier(RenderWindow &window, std::string dir) {
  int coord[9][2] = {{154, 84}, {395, 224}, {48, 367}, {680, 272}, {798, 43}, 
    {560, 49}, {90, 244}, {454, 619}, {860, 605}};

  for (int i = 0; i < 9; i++) {
    Texture texture;
    i < 6? texture.loadFromFile(dir + std::to_string(i + 1) + ".png") : 
      texture.loadFromFile(dir + "6.png");
    Sprite sprite(texture);
    sprite.setPosition(Vector2f(coord[i][0], coord[i][1]));
    window.draw(sprite);
  }
}

void draw_bg(RenderWindow &window, std::string dir) {
  Texture bgtxt;
  bgtxt.loadFromFile(dir + "bg.png");
  Sprite bgSprite(bgtxt);
  bgSprite.setPosition(0, 0);
  window.draw(bgSprite);
}

void Screen::show_table(Snake snake, Food food, RenderWindow &window) {
  draw_bg(window, dir);
  Texture texture;
  for (int i = 0; i < snake.snake_size; i++)
    draw_snake(window, snake, i, dir);
  for (int i = 0; i < food.type.size(); i++)
    draw_food(window, food, i, dir);
  if(barier == true)
    draw_barier(window, dir);
  window.display();
}

void Screen::kill_table(Snake snake) {
  usleep(100000);
  win->close();
puts("++++");
  RenderWindow window(VideoMode(1000, 700), "Game over");
  draw_bg(window, dir);
  Texture bgtxt;
  bgtxt.loadFromFile(dir + "boom.png");
  Sprite bgSprite(bgtxt);
  bgSprite.setPosition(0, 50);
  window.draw(bgSprite);
  window.display();
  sleep(1);
  window.clear(Color::Green);

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case Event::Closed:
          window.close();
        case Event::KeyPressed:
          window.close();
          break;
        default:
            break;
      }
    }
    draw_bg(window, dir);
    sf::Text text;
    Font font;
    font.loadFromFile(dir + "arial.ttf");
    text.setFont(font); 
    text.setString("Snake score: " + std::to_string(snake.score));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(351, 350);
    window.draw(text);
    window.display();
  }
}