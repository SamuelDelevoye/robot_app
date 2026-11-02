#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "sensor.hpp"
#include "grid.hpp"
/*
The car is the "robot" that move
Two usage available:
	auto_move = true so that the car move alone to the target
	auto_move = false to be able to move the car with the arrows

dot_coords is to keep in mind all the collision of the sensors with a wall
sensors is a vector with all the sensors in it

for auto_move=true:
	current_box and next_box to know where the car is and where he should go
	algo_grid is the grid for the algorythme with all the box
	and we keep the target position in target_x and target_y


*/
extern std::vector<sf::RectangleShape> obstacles;

class Car : public sf::Drawable, public sf::Transformable {

private:

	std::vector<sf::Vector2f> dot_coords;

	bool can_move(const std::vector<sf::RectangleShape>& obstacles) const;
	sf::CircleShape car_shape;

	sf::RectangleShape view_line;

	float car_speed;

	std::vector<Sensor> sensors;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Box* current_box;
	Box* next_box;

	bool auto_move;
	Grid algo_grid;
	float target_x;
	float target_y;



public : 

	Car(float radius, int wind_width, int wind_height,float init_target_x, float init_target_y);
	void update_target(float new_target_x, float new_target_y);
	std::vector<sf::Vector2f> get_coord_obs();
	void update(const std::vector<sf::RectangleShape>& obstacles);
	void set_auto_move(bool new_auto_move);
	void turn_toward(float target_angle);
	void move_toward(float coord_x, float coord_y,const std::vector<sf::RectangleShape>& obstacles);
};


