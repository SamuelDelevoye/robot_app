#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "sensor.hpp"
extern std::vector<sf::RectangleShape> obstacles;

class Car : public sf::Drawable, public sf::Transformable {

private:
	std::vector<sf::Vector2f> dot_coords;
	bool can_move(const std::vector<sf::RectangleShape>& obstacles) const;
	sf::CircleShape car_shape;
	sf::RectangleShape view_line;
	float car_speed;
	Sensor front_sensor;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public : 
	Car(float radius = 25.f);
	std::vector<sf::Vector2f> get_coord_obs();
	void update(const std::vector<sf::RectangleShape>& obstacles);
};


