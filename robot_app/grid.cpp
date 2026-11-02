
#include <queue>
#include <climits>
#include "grid.hpp"



Grid::Grid(float size, unsigned int window_width,
    unsigned int window_height)
{
    size_box = size;
    nb_of_col = static_cast<int>(window_width / size_box);
    nb_of_row = static_cast<int>(window_height / size_box);

    boxes.resize(nb_of_row);

    for (int y = 0; y < nb_of_row; y++)
    {
        boxes[y].reserve(nb_of_col);

        for (int x = 0; x < nb_of_col; x++)
        {
            boxes[y].emplace_back(
                x * size_box + size_box / 2.f,
                y * size_box + size_box / 2.f,
                size_box, 
                y,
                x
            );
        }
    }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& row : boxes)
    {
        for (const auto& box : row)
        {
            target.draw(box, states);
        }
    }
}

bool Grid::place_obstacle(float x, float y)
{
    Box* box = get_box_of_point(x, y);

    if (box == nullptr)
        return false;

    if (box->get_cost() == INFINITE_COST)
        return false;

    box->set_cost(INFINITE_COST);
    return true;
}

Box* Grid::get_box_of_point(float x, float y)
{
    int col = static_cast<int>(x / size_box);
    int row = static_cast<int>(y / size_box);

    if (col < 0 || col >= nb_of_col ||
        row < 0 || row >= nb_of_row)
    {
        return nullptr;
    }

    return &boxes[row][col];
}

bool Grid::is_in_grid(Box test_box) const
{
    float x = test_box.get_middle_coords().x;
    float y = test_box.get_middle_coords().y;
    return x >= 0 && y >= 0 &&
        x < nb_of_col * size_box &&
        y < nb_of_row * size_box;
}


    
void Grid::place_cost(float coord_target_x, float coord_target_y) {
    Box* target_box = get_box_of_point(coord_target_x, coord_target_y);
    target_box->set_cost(1);
    
    int col_targ_box = target_box->get_col();
    int row_targ_box = target_box->get_row();

    for (int i = 0; i < nb_of_row; i++) {
        for (int j = 0; j < nb_of_col; j++) {
            
            int col_ij = boxes[i][j].get_col();
            int row_ij = boxes[i][j].get_row();
            
            /*
            Calculate the cost with the Manhattan alg and adding + 1
            because the cost of the target is equal to 1 and not 0, 0 being not init 
            */
            int cost_box = abs(col_targ_box - col_ij) + abs(row_targ_box - row_ij) + 1;
            boxes[i][j].set_cost(cost_box);
        }
    }

    
}




void Grid::wavefront_init(float target_x, float target_y)
{
    std::queue<Box*> queue;

    Box* target = get_box_of_point(target_x, target_y);

    if (target == nullptr)
        return;

    for (auto& row : boxes)
    {
        for (auto& box : row)
        {
            if (box.get_cost() != INFINITE_COST)
                box.set_cost(0);

            box.set_previous(nullptr);
        }
    }

    if (target->get_cost() == INFINITE_COST)
        return;

    target->set_cost(1);
    queue.push(target);

    const int directions[4][2] = {
        {-1,  0},
        { 1,  0},
        { 0, -1},
        { 0,  1}
    };

    while (!queue.empty())
    {
        Box* current = queue.front();
        queue.pop();

        int row = current->get_row();
        int col = current->get_col();

        for (const auto& direction : directions)
        {
            int new_row = row + direction[0];
            int new_col = col + direction[1];

            if (new_row < 0 || new_row >= nb_of_row ||
                new_col < 0 || new_col >= nb_of_col)
                continue;

            Box* neighbor = &boxes[new_row][new_col];

            if (neighbor->get_cost() == INFINITE_COST)
                continue;

            if (neighbor->get_cost() != 0)
                continue;

            neighbor->set_cost(current->get_cost() + 1);
            neighbor->set_previous(current);

            queue.push(neighbor);
        }
    }
}

void Grid::draw_path(sf::RenderTarget& target, sf::RenderStates states, Box* current_box) const
{
    Box* box = current_box;

    while (box != nullptr)
    {
        target.draw(*box, states);
        box = box->get_previous();
    }
}