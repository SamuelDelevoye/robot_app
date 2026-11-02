#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


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

