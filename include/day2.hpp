#include <string>

enum Color {
    Red,
    Green,
    Blue
};

bool is_possible_set(std::string set, int max_red, int max_blue, int max_green);
bool is_possible_game(std::string game_line, int max_red, int max_blue, int max_green);