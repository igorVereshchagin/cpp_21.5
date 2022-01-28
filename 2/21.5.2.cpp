#include <iostream>
#include <vector>

enum room_type_t
{
    room_bed = 0,
    room_kitchen,
    room_bath,
    room_play,
    room_living
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
    bool stove;
//    std::vector<floor_t> floors;
};

struct barn_t
{
    int dummy;
};

struct garage_t
{
    int dummy;
};

struct vapor_t
{
    bool stove;
};

enum building_type_t
{
    bld_house = 0,
    bld_garage,
    bld_barn,
    bld_vapor
};

struct building_t
{
    int area;
    building_type_t type;
    union
    {
        int arr;
        house_t house;
//        garage_t garage;
//        barn_t barn;
//        vapor_t vapor;
    };
};

struct plot_t
{
    int number;
    std::vector<building_t> buildings;
};

void fill_plot(plot_t &plot)
{
    std::cout << "Input number of buildings" << std::endl;
    int bld_count;
    std::cin >> bld_count;
    plot.buildings.resize(bld_count);
    plot.buildings[0].area = 0;
}

int main()
{
    std::vector<plot_t> village_plots;
    std::cout << "Input number of plots in the village" << std::endl;
    int count;
    std::cin >> count;
    village_plots.resize(count);
    for (int i = 0; i < count; i++)
        fill_plot(village_plots[i]);
    return 0;
}
