#pragma once
#include <vector>
#include "box.hpp"

/*
Grid use many box for mapping the SFML window

we calculate the number of colones and rows by deviding length of window by the length of a box
we use the wavefront algorythme to put the cost of each box by starting with the target box
and than in each box we put the previous box to know the return path
*/

class Grid : public sf::Drawable
{
private:
    std::vector<std::vector<Box>> boxes;

    int nb_of_col;
    int nb_of_row;
    float size_box;
    void draw(sf::RenderTarget& target,
        sf::RenderStates states) const override;

    bool is_in_grid(Box test_box) const;



public:
    static constexpr int INFINITE_COST = 10000000;

    Grid(float size, unsigned int window_width,
        unsigned int window_height);
    

    Box* get_box_of_point(float x, float y);

    bool place_obstacle(float x, float y);


    void wavefront_init(float target_x, float target_y);

    void place_cost(float coord_target_x, float coord_target_y);
    void draw_path(sf::RenderTarget& target, sf::RenderStates states,Box* current_box) const;
};