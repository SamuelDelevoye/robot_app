#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
/*
Sensor imitates a lidar sensor to detect a wall
I use a dot that travel from the car to the end of the sensor and check if it's in collision with a wall

*/

class Sensor  : public sf::Drawable, public sf::Transformable {
private:

	sf::RectangleShape s_line;
	sf::CircleShape end_dot;

	float s_length;
	float angle;
	bool is_trigger; 
	float dist_dot;

	bool found_new_wall;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public: 
	
	void reset_found_new_wall();
	bool get_found_new_wall();
	Sensor(float length = 150.f, float angleInDegrees=0);
	void update_sensor(const std::vector<sf::RectangleShape>& obstacle, const sf::Transform& parentTransform, std::vector<sf::Vector2f>& dot_coords);
};