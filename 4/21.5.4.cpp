#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

struct personage_t
{
  std::string name;
  int health;
  int armor;
  int strength;
  bool enemy;
  int pos_x;
  int pos_y;
};

int input_int(const std::string &msg, int min = INT_MIN, int max = INT_MAX)
{
  int input;
  do
  {
    std::cout << msg << std::endl;
    std::cin >> input;
    if (input < min || input > max)
    {
      std::cout << "Invalid input" << std::endl;
    }
  }while (!(input >= min && input <= max));
  return input;
}

void input_personage(personage_t &pers)
{
  std::cout << "Input name: " << std::endl;
  std::cin >> std::ws;
  std::getline(std::cin, pers.name);
  pers.health = input_int("Input health (50 - 150):", 50, 150);
  pers.armor = input_int("Input armor (0 - 50):", 0, 50);
  pers.strength = input_int("Input strength (15 - 30):", 15, 30);
  pers.enemy = false;
}

void generate_personage(personage_t &pers, const std::string &name)
{
  pers.name = name;
  pers.health = (std::rand() % 101) + 50;
  pers.armor = std::rand() % 51;
  pers.strength = (std::rand() % 16) + 15;
  pers.enemy = true;
}

void place_personage(personage_t &pers)
{
  pers.pos_x = std::rand() % 40;
  pers.pos_y = std::rand() % 40;
}

void show(personage_t players[6])
{
  char field_buf[40][41];
  for (int i = 0; i < 40; i++)
  {
    for (int j = 0; j < 40; j++)
      field_buf[i][j] = '.';
    field_buf[i][40] = 0;
  }
  field_buf[players[0].pos_y][players[0].pos_x] = 'P';
  for (int i = 1; i < 6; i++)
    field_buf[players[i].pos_y][players[i].pos_x] = 'E';
  for (int i = 0; i < 40; i++)
    std::cout << field_buf[i] << std::endl;
  for (int i = 0; i < 6; i++)
    std::cout << players[i].name << ": H:" << players[i].health << "  A:" << players[i].armor << std::endl;
}

enum direction_t
{
  dir_left = 0,
  dir_right,
  dir_top,
  dir_bottom
};

void move(personage_t &pers, const direction_t &dir)
{

}

int main()
{
  personage_t players[6];
  input_personage(players[0]);
  for (int i = 1; i < 6; i++)
    generate_personage(players[i], "Enemy #" + std::to_string(i));
  for (int i = 0; i < 6; i++)
    place_personage(players[i]);
  show(players);
  return 0;
}
