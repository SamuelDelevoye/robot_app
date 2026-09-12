#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
extern std::vector<sf::RectangleShape> obstacles;

class Car : public sf::Drawable, public sf::Transformable {

private:
	bool can_move(const std::vector<sf::RectangleShape>& obstacles) const;
	sf::CircleShape car_shape;
	sf::RectangleShape view_line;
	float car_speed;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public : 
	Car(float radius = 25.f);
	sf::FloatRect getGlobalBounds() const;

	void update(const std::vector<sf::RectangleShape>& obstacles);
};


