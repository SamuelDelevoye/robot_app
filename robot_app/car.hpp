#pragma once
#include <SFML/Graphics.hpp>

class Car : public sf::Drawable, public sf::Transformable {
private :
private:
	sf::CircleShape car_shape;
	float car_speed;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public : 
	Car(float radius = 25.f);

	void update();
};


