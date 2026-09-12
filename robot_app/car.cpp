#include "car.hpp"
#include <cmath>


const float lin_speed = 0.2;
const float rot_speed = 0.2;

Car::Car(float radius)
    : car_shape(radius), car_speed(lin_speed)
{
    car_shape.setOrigin({ radius, radius });
    car_shape.setFillColor(sf::Color::Red);
}

void Car::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        rotate(sf::degrees(-rot_speed));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        rotate(sf::degrees(rot_speed));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) )
    {
        float radians = getRotation().asRadians();

        float vx = std::cos(radians) * car_speed;
        float vy = std::sin(radians) * car_speed;

        move({ vx, vy });
    }
}

// Implémentation du rendu
void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // On applique la transformation de la Car (sa position/rotation) aux états de rendu
    states.transform *= getTransform();

    // On dessine le shape interne en lui appliquant les états
    target.draw(car_shape, states);
}