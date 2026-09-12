#include "car.hpp"
#include <cmath>
#include <iostream>

//function that go with the entitie car

const float lin_speed = 0.1;
const float rot_speed = 0.2;

Car::Car(float radius)
    : car_shape(radius), car_speed(lin_speed)
{
    car_shape.setOrigin({ radius, radius });
    car_shape.setFillColor(sf::Color::Blue);
    view_line.setSize({ 150.f,1.f });
    view_line.setOrigin({ 0.f, 0.5f });
    view_line.setPosition({radius,0.f });
    view_line.setFillColor(sf::Color::Red);
}

void Car::update(const std::vector<sf::RectangleShape>& obstacles)
{
    //update the rotation and position of the car with the input of the tester

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        rotate(sf::degrees(-rot_speed));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        rotate(sf::degrees(rot_speed));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        if (can_move(obstacles))
        {
            float radians = getRotation().asRadians();

            float vx = std::cos(radians) * car_speed;
            float vy = std::sin(radians) * car_speed;

            move({ vx, vy });
        }
    }
}

bool Car::can_move(const std::vector<sf::RectangleShape>& obstacles) const
{
    //Create three dot at the limit of the robot (+1f) to check the collisions before mooving

    float radians = getRotation().asRadians();
    float radius = car_shape.getRadius();

    float distance = radius + 1.f;
    std::vector<sf::Vector2f>collision_dot;

    //three detection dot that cover the front of the car:
    //one in front and two on the side at approximative 45°

    float angle_left = radians + 3.14f / 4.f;
    float angle_right = radians - 3.14f / 4.f;

    sf::Vector2f front_dot =
    {
        getPosition().x + std::cos(radians) * distance,
        getPosition().y + std::sin(radians) * distance
    };


    sf::Vector2f left_dot_45 =
    {
        getPosition().x + std::cos(angle_left) * distance,
        getPosition().y + std::sin(angle_left) * distance
    };


    sf::Vector2f right_dot_45 =
    {
        getPosition().x + std::cos(angle_right) * distance,
        getPosition().y + std::sin(angle_right) * distance
    };

    collision_dot.push_back(front_dot);
    collision_dot.push_back(left_dot_45);
    collision_dot.push_back(right_dot_45);


    for (const auto& obs : obstacles){

        for (const auto& dot : collision_dot) {
            
            if (obs.getGlobalBounds().contains(dot)){
                return false;
            }

        }

    }

    return true;
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    
    states.transform *= getTransform();

    target.draw(car_shape, states);    target.draw(view_line, states);
}

