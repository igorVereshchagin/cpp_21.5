#include <iostream>
#include <vector>
#include <string>

enum room_type_t
{
  room_type_min = 0,
  room_bed = room_type_min,
  room_kitchen,
  room_bath,
  room_play,
  room_living,
  room_type_max = room_living
};

struct room_t
{
  room_type_t type;
  int area;
};

struct floor_t
{
  int height;
  std::vector<room_t> rooms;
};

struct house_t
{
  int area;
  bool stove;
  std::vector<floor_t> floors;
};

struct barn_t
{
};

struct garage_t
{
};

struct vapor_t
{
  bool stove;
};

enum building_type_t
{
  bld_type_min = 0,
  bld_garage = bld_type_min,
  bld_barn,
  bld_vapor,
  bld_type_max = bld_vapor
};

struct building_t
{
  int area;
  building_type_t type;
  union
  {
    garage_t garage;
    barn_t barn;
    vapor_t vapor;
  };
};

struct plot_t
{
  int number;
  int area;
  house_t house;
  std::vector<building_t> buildings;
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

void input_house(house_t &house)
{
  house.area = input_int("Input the area of the house footprint (square meters): ", 0);
  std::cout << "Is there any stove? (yes/no):" << std::endl;
  std::string ans;
  std::cin >> ans;
  house.stove = (ans == "yes") ? true : false;
  int floors_count = input_int("Input the number of floors (1-3):", 1, 3);
  house.floors.resize(floors_count);
  for (int f = 0; f < floors_count; f++)
  {
    house.floors[f].height = input_int("Input the height of the floor #" + std::to_string(f + 1) + " (cm):", 0);
    int rooms_count = input_int("Input the number of rooms on the floor #" + std::to_string(f + 1) + " (2 - 4):", 2, 4);
    house.floors[f].rooms.resize(rooms_count);
    for (int r = 0; r < rooms_count; r++)
    {
      house.floors[f].rooms[r].area = input_int("Input the area of the room #" + std::to_string(r + 1) +
        " of the floor #" + std::to_string(f + 1) + " (square meters): ", 0);
      house.floors[f].rooms[r].type = (room_type_t)input_int("Input the type of the room (0:bed, 1:kitchen, 2:bath, 3:play, 4:living): ", room_type_min, room_type_max);
    }
  }
}

void input_garage(garage_t &garage)
{

}

void input_barn(barn_t &barn)
{

}

void input_vapor(vapor_t &vapor)
{
  std::cout << "Is there any stove? (yes/no):" << std::endl;
  std::string ans;
  std::cin >> ans;
  vapor.stove = (ans == "yes") ? true : false;
}

void input_building(building_t &building)
{
  building.type = (building_type_t)input_int("Input the type of the building (0:garage, 1:barn, 2:vapor): ", bld_type_min, bld_type_max);
  building.area = input_int("Input the area of the building footprint (square meters): ", 0);
  switch(building.type)
  {
    case bld_garage:
      input_garage(building.garage);
      break;
    case bld_barn:
      input_barn(building.barn);
      break;
    case bld_vapor:
      input_vapor(building.vapor);
      break;
  }
}

void input_plot(plot_t &plot)
{
  plot.area = input_int("Input the area of the plot (square meters): ", 0);
  input_house(plot.house);
  std::cout << "Input number of buildings" << std::endl;
  int bld_count;
  std::cin >> bld_count;
  plot.buildings.resize(bld_count);
  for (int i = 0; i < bld_count; i++)
  {
    input_building(plot.buildings[i]);
  }
}

int main()
{
  std::vector<plot_t> village_plots;
  std::cout << "Input number of plots in the village" << std::endl;
  int count;
  std::cin >> count;
  village_plots.resize(count);
  for (int i = 0; i < count; i++)
  {
    village_plots[i].number = i;
    input_plot(village_plots[i]);
  }
  double total_area = 0;
  double buildings_area = 0;
  for (int i = 0; i < village_plots.size(); i++)
  {
    total_area += village_plots[i].area;
    buildings_area += village_plots[i].house.area;
    for (int b = 0; b < village_plots[i].buildings.size(); b++)
      buildings_area += village_plots[i].buildings[b].area;
  }
  std::cout << "Buildings occupy " << buildings_area / total_area * 100 << "% of the area of the village" << std::endl;
  return 0;
}
