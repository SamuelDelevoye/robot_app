#include "box.hpp"
#include <cmath>
#include <algorithm>
#include <numbers>
#include <iostream>




Box::Box(float x_coord,float y_coord, float size_box,int row, int col) {
	middle_coords.x = x_coord;
	middle_coords.y = y_coord;
	size = size_box;
	cost = 0;

	col_box = col;
	row_box = row;

	previous_box = nullptr;

	//init for the algorythme box

	box_vue.setSize({ size, size });
	box_vue.setOrigin({ size / 2.f, size / 2.f });
	box_vue.setPosition(middle_coords);

	box_vue.setFillColor(sf::Color::Transparent);
	box_vue.setOutlineColor(sf::Color::White);
	box_vue.setOutlineThickness(1.f);

}

int Box :: get_cost() {
	return cost;
}
sf::Vector2f Box::get_middle_coords() {
	return middle_coords;
}

int Box::get_col() {
	return col_box;
}

int Box::get_row() {
	return row_box;
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box_vue, states);
}


void Box::set_cost(int new_cost) {
	cost = new_cost;

}

void Box::set_previous(Box* previous)
{
	previous_box = previous;
}

Box* Box::get_previous()
{
	return previous_box;
}

