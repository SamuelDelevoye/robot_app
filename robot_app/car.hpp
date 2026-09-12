#pragma once
#include <SFML/Graphics.hpp>

class Car : public sf::Drawable, public sf::Transformable {
private :
private:
	sf::CircleShape car_shape;
	float car_speed;

	// Méthode obligatoire imposée par sf::Drawable (note le 'override')
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public : 
	Car(float radius = 25.f);

	// Méthode pour mettre à jour la logique du robot à chaque frame
	void update();
};


