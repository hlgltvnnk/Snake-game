#include "src/Snake.h"
#include "src/Food.h"
#include "src/Screen.h"
#include <iostream>
#include <fstream>
using namespace sf;
std::string dir;

void draw_bg(RenderWindow &window) {
  Texture bgtxt;
  bgtxt.loadFromFile(dir + "bg.png");
  Sprite bgSprite(bgtxt);
  bgSprite.setPosition(0, 0);
  window.draw(bgSprite);
}

void change_direction(int &change_x, int &change_y, Event event) {
  switch (event.key.code) {
    case Keyboard::Up: 
        if ((change_x != 0 || change_y != 20) && (change_x != 0 || change_y != -20)) {
                change_x = 0; change_y = -20;
              }
              break;
    case Keyboard::Left: 
        if ((change_x != 20 || change_y != 0) && (change_x != -20 || change_y != 0)) {
                change_x = -20; change_y = 0;
              }
              break;
    case Keyboard::Down:
        if ((change_x != 0 || change_y != -20) && (change_x != 0 || change_y != 20)) {
                change_x = 0; change_y = 20;
              }
              break;
    case Keyboard::Right: 
        if ((change_x != -20 || change_y != 0) && (change_x != 20 || change_y != 0)) {
                change_x = 20; change_y = 0;
              }
              break;
    default: break;
  }
}

bool next_step(Snake &snake, Food &food, Screen screen, int change_x, int change_y, RenderWindow &window) {
    if (food.food_check())
        food.place_food(screen);
    snake.setCoordinates(change_x, change_y);
    snake.growUp(food, screen);
    screen.show_table(snake, food, window);
  if (snake.game_over(screen)) {
    screen.kill_table(snake);
    return false;
  }
  snake.check_border(screen);
  return true;
}

void print_score(RenderWindow &window, std::string str, int heigh, int width) {
  sf::Text text;
  Font font;
  font.loadFromFile(dir + "arial.ttf");
  text.setFont(font); 
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  text.setPosition(width, heigh);
  text.setString(str + "  ");
  window.draw(text);
  window.display();
}

void scoreBoard (char *argc[] , std::map<std::string, int> map) {
  RenderWindow window(VideoMode(1000, 700), "ScoreBoard");
  int heigh = 50;
  draw_bg(window);

  for (auto i : map) {
    for(int k = 100; k > 0; k++) {
      print_score(window, i.first, heigh, 50);
      print_score(window, std::to_string(i.second), heigh, i.first.size()*10 + 100);
      heigh += 50;
    }
    }
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case Event::Closed:
          window.close();
          break;
        default:
            break;
      }
    }
  }
}

void sleeping(Snake snake) {
  int sleeper = 100;
  if (snake.snake_size > 6)
    sleeper = 100 - 5 * snake.snake_size;
  usleep(sleeper * 1000);
}

std::string get_name(RenderWindow &window) {
  sf::Text playerText;
  std::string res;
  draw_bg(window);

  sf::Text text;
  Font font;
  font.loadFromFile(dir + "arial.ttf");
  text.setFont(font); 
  text.setString("Player name");
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  text.setPosition(400, 250);
  window.draw(text);
  window.draw(playerText);
  window.display();

  playerText.setFont(font);
  playerText.setCharacterSize(24);
  playerText.setFillColor(sf::Color::White);
  playerText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  playerText.setPosition(400, 350);

  Event event;
  while(res.empty() || (event.type != sf::Event::KeyPressed && event.key.code != sf::Keyboard::Enter)) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::TextEntered) {
          res += static_cast<char>(event.text.unicode);
          playerText.setString(res);
          window.draw(text);
          window.draw(playerText);
          window.display();
        // if (res[0] == '/n')
        //   res.clear();
      }
    }
  }
return res;
}

void Gameplay (char *argc[], bool level, std::map<std::string, int> &map) {
    RenderWindow window(VideoMode(1000, 700), "Snake");
    Snake snake(0, 0);
    Screen screen(level, dir);
    screen.win = &window;
    Food food(screen);
    int change_x = 0;
    int change_y = 20;
    int flag = true;
    std::string name;
    
    while (window.isOpen() && flag) {
      if(name.empty())
        name = get_name(window);
      window.clear(Color::Green);
                Event event;
                while (window.pollEvent(event)) {
                    switch (event.type) {
                        case Event::Closed:
                            window.close();
                            break;
                        case Event::KeyPressed:
                            change_direction(change_x, change_y, event);
                            flag = next_step(snake, food, screen, change_x, change_y, window);
                        default:
                        break;
                    }
                }
        flag? flag = next_step(snake, food, screen, change_x, change_y, window) : 0;
        sleeping(snake);
    }
    if (map[name] < snake.score)
      map[name] = snake.score;
}

void draw_sprites(RenderWindow &window) {
  draw_bg(window);
  Texture firstButton;
  firstButton.loadFromFile(dir + "easy.png");
  Sprite firstSprite(firstButton);
  firstSprite.setPosition(351, 240);
  Texture secondButton;
  secondButton.loadFromFile(dir + "hard.png");
  Sprite secondSprite(secondButton);
  secondSprite.setPosition(351, 321);
  Texture thirdButton;
  thirdButton.loadFromFile(dir + "score.png");
  Sprite thirdSprite(thirdButton);
  thirdSprite.setPosition(351, 407);
  window.draw(firstSprite);
  window.draw(secondSprite);
  window.draw(thirdSprite);
}

void newGame (char *argc[], std::map<std::string, int> &map) {
  RenderWindow window(VideoMode(1000, 700), "newGame");
  draw_sprites(window);
  window.display();

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case Event::Closed:
          window.close();
          break;
        case Event::MouseButtonPressed:
          if (IntRect(351, 240, 300 , 54).contains(Mouse::getPosition(window)))
            Gameplay(argc, false, map);
          if (IntRect(351, 312,  300 , 54).contains(Mouse::getPosition(window)))
            Gameplay(argc, true, map);
          if (IntRect(351, 407,  300 , 54).contains(Mouse::getPosition(window)))
            scoreBoard(argc, map);
          default:
            break;
      }
    }
  }
}

std::string get_dir(char *str) {
    std::string tmp = std::string(str);
    auto end = tmp.find("build");

    if (end != -1)
      return tmp.substr(0, end) + "app/resource/";
    if (tmp.find("app") != tmp.size())
      return "../app/resource/";
    return "../../app/resource/";
}

int main(int argv, char *argc[]) {
    std::map<std::string, int>  scores;
    dir = get_dir(argc[0]);
    newGame(argc, scores);
    return 0;
}
