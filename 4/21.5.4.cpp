#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

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


enum direction_t
{
  dir_left = 0,
  dir_right,
  dir_top,
  dir_bottom
};

int input_int(const std::string &msg, int min = INT_MIN, int max = INT_MAX);
void input_personage(personage_t &pers);
void generate_personage(personage_t &pers, const std::string &name);
void place_personage(personage_t &pers);
void show(personage_t players[6]);
bool is_collision(personage_t &pers, int dx, int dy, personage_t players[6], personage_t **victim);
void move(personage_t &pers, const direction_t &dir, personage_t players[6]);



int main()
{
  personage_t players[6];
  std::srand(time(nullptr));
  input_personage(players[0]);
  for (int i = 1; i < 6; i++)
    generate_personage(players[i], "Enemy #" + std::to_string(i));
  for (int i = 0; i < 6; i++)
    place_personage(players[i]);
  while ((players[0].health > 0) &&
    ((players[1].health > 0) || (players[2].health > 0) || (players[3].health > 0) ||
     (players[4].health > 0) || (players[5].health > 0)))
  {
    std::string cmd;
    show(players);
    std::cout << players[0].name << "'s turn" << std::endl;
    std::cin >> cmd;
    direction_t dir;
    if (cmd == "l")
      dir = dir_left;
    else if (cmd == "r")
      dir = dir_right;
    else if (cmd == "t")
      dir = dir_top;
    else if (cmd == "b")
      dir = dir_bottom;
    else if (cmd == "save")
    {
      std::string fname;
      std::cout << "Input save name: " << std::endl;
      std::cin >> fname;
      std::ofstream savefile(fname, std::ios::binary);
      if (!savefile.is_open())
      {
        std::cout << "Invalid name" << std::endl;
        continue;
      }
      int magick_head = 0x00210504;
      savefile.write((char*)&magick_head, sizeof(magick_head));
      for (int i = 0; i < 6; i++)
      {
        int namelen = players[i].name.length();
        savefile.write((char*)&namelen, sizeof(namelen));
        savefile.write(players[i].name.c_str(), namelen);
        savefile.write((char*)&players[i].health, sizeof(players[i].health));
        savefile.write((char*)&players[i].armor, sizeof(players[i].armor));
        savefile.write((char*)&players[i].strength, sizeof(players[i].strength));
        savefile.write((char*)&players[i].enemy, sizeof(players[i].enemy));
        savefile.write((char*)&players[i].pos_x, sizeof(players[i].pos_x));
        savefile.write((char*)&players[i].pos_y, sizeof(players[i].pos_y));
      }
      savefile.close();
      continue;
    }
    else if (cmd == "load")
    {
      std::string fname;
      std::cout << "Input saved name: " << std::endl;
      std::cin >> fname;
      std::ifstream loadfile(fname, std::ios::binary);
      if (!loadfile.is_open())
      {
        std::cout << "Invalid name" << std::endl;
        continue;
      }
      int magick_head;
      loadfile.read((char*)&magick_head, sizeof(magick_head));
      if (magick_head != 0x00210504)
      {
        std::cout << "Invalid file format" << std::endl;
        loadfile.close();
        continue;
      }
      for (int i = 0; i < 6; i++)
      {
        int namelen = players[i].name.length();
        loadfile.read((char*)&namelen, sizeof(namelen));
        players[i].name.resize(namelen);
        loadfile.read((char*)players[i].name.c_str(), namelen);
        loadfile.read((char*)&players[i].health, sizeof(players[i].health));
        loadfile.read((char*)&players[i].armor, sizeof(players[i].armor));
        loadfile.read((char*)&players[i].strength, sizeof(players[i].strength));
        loadfile.read((char*)&players[i].enemy, sizeof(players[i].enemy));
        loadfile.read((char*)&players[i].pos_x, sizeof(players[i].pos_x));
        loadfile.read((char*)&players[i].pos_y, sizeof(players[i].pos_y));
      }
      loadfile.close();
      continue;
    }
    else
      continue;
    move(players[0], dir, players);
    for (int i = 1; i < 6; i++)
    {
      dir = (direction_t)(std::rand() % 4);
      move(players[i], dir, players);
    }
  }
  if (players[0].health > 0)
    std::cout << players[0].name << " WON!" << std::endl;
  else
    std::cout << players[0].name << " LOST!" << std::endl;
  return 0;
}

int input_int(const std::string &msg, int min, int max)
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
  if (players[0].health > 0)
    field_buf[players[0].pos_y][players[0].pos_x] = 'P';
  for (int i = 1; i < 6; i++)
  {
    if (players[i].health > 0)
      field_buf[players[i].pos_y][players[i].pos_x] = 'E';
  }
  for (int i = 0; i < 40; i++)
    std::cout << field_buf[i] << std::endl;
  for (int i = 0; i < 6; i++)
    std::cout << players[i].name << ": H:" << players[i].health << "  A:" << players[i].armor << "  S: " << players[i].strength << std::endl;
}

bool is_collision(personage_t &pers, int dx, int dy, personage_t players[6], personage_t **victim)
{
  bool collision = false;
  for (int i = 0; !collision && i < 6; i++)
  {
    if (&pers == &players[i])
      continue;
    if ((players[i].health > 0) && (((pers.pos_x + dx) == players[i].pos_x) && ((pers.pos_y + dy) == players[i].pos_y)))
    {
      collision = true;
      *victim = &players[i];
    }
  }
  return collision;
}

void move(personage_t &pers, const direction_t &dir, personage_t players[6])
{
  int dx = 0;
  int dy = 0;
  if (dir == dir_left)
    dx = -1;
  else if (dir == dir_right)
    dx = 1;
  else if (dir == dir_top)
    dy = -1;
  else if (dir == dir_bottom)
    dy = 1;

  if ((pers.pos_x + dx >= 0) && (pers.pos_x + dx < 40) && (pers.pos_y + dy >= 0) && (pers.pos_y + dy < 40))
  {
    personage_t *victim = nullptr;
    if (is_collision(pers, dx, dy, players, &victim))
    {
      if (pers.enemy != victim->enemy)
      {
        std::cout << victim->name << " took damage: -" << pers.strength << std::endl;
        victim->armor -= pers.strength;
        if (victim->armor < 0)
        {
          victim->health += victim->armor;
          victim->armor = 0;
          if (victim->health < 0)
          {
            victim->pos_x = -1;
            victim->pos_y = -1;
          }
        }
      }
    }
    else
    {
      pers.pos_x += dx;
      pers.pos_y += dy;
    }
  }

}
