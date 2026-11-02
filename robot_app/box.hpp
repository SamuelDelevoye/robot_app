#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
/*
Class Box:
	Used for the SLAM algorythm, have to be at least the size of the car,
	For the coords i used the middle of the box so that the car know where it is
	The cost is how much box the car need to go to found the target +1
	for the cost : 
		INFINITE_COST is for the walls
		0 when it's not init
		1 for the target
	previous_box is used to know the next box to go to the target
*/

class Box: public sf::Drawable {
private:
	sf::Vector2f middle_coords;

	float size;
	sf::RectangleShape box_vue;
	void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;
	int cost;

	int row_box;
	int col_box;

	Box* previous_box;

public:
	Box(float x_coord, float y_coord, float size, int row, int col);
	int get_cost();
	sf::Vector2f get_middle_coords();
	void set_cost(int cost);
	void set_previous(Box* previous);
	Box* get_previous();
	int get_row();
	int get_col();

};

