#include <cassert>
#include <iostream>
#include "grid.hpp"
/*
int main()
{
    Grid grid(50.f, 350, 350);

    Box* obstacle = grid.get_box_of_point(125.f, 175.f);
    
    obstacle->set_cost(Grid::INFINITE_COST);

    grid.wavefront_init(175.f, 175.f);

    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            Box* box = grid.get_box_of_point(
                col * 50.f + 25.f,
                row * 50.f + 25.f
            );

            if (box->get_cost() == Grid::INFINITE_COST)
                std::cout << " X ";
            else
                std::cout << box->get_cost() << "  ";
        }

        std::cout << '\n';
    }


    Box* current = grid.get_box_of_point(25.f, 175.f);

    while (current != nullptr)
    {
        sf::Vector2f pos = current->get_middle_coords();

        std::cout << "(" << pos.x << ", " << pos.y << ")\n";

        current = current->get_previous();
    }

    return 0;
}*/