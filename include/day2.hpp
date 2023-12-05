#include <string>

enum Color {
    Red,
    Green,
    Blue
};

bool is_possible_set(std::string set, int max_red, int max_blue, int max_green);
bool is_possible_game(std::string game_line, int max_red, int max_blue, int max_green);
int calculate_cube_set_power(std::string game_line);
void update_min_color_count(std::string set, int *min_red, int *min_blue, int *min_green);