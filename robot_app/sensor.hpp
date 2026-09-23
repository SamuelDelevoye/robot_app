#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


class Sensor  : public sf::Drawable, public sf::Transformable {
private:
	sf::RectangleShape s_line;
	sf::CircleShape end_dot;

	float s_length;
	float angle;
	bool is_trigger; 
	float dist_dot;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public: 
	Sensor(float length = 150.f, float angleInDegrees=0);
	void update_sensor(const std::vector<sf::RectangleShape>& obstacle, const sf::Transform& parentTransform, std::vector<sf::Vector2f>& dot_coords);
};