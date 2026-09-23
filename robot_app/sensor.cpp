#include "sensor.hpp"
#include <cmath>
#include <iostream>



void update_coords(sf::Vector2f new_coord, std::vector<sf::Vector2f>& dot_coords) {

    bool can_add = true;
    for (const auto& coord : dot_coords) {
        sf::Vector2f dist = coord - new_coord;
        float distance = std::hypot(dist.x, dist.y);
        if (distance < 10.0f) {
            can_add = false;
            break;
        }
    }

    if (can_add) {
        dot_coords.push_back(new_coord);
    }


}

Sensor::Sensor(float length, float angleInDegrees)
    : s_length(length), angle(angleInDegrees),dist_dot(length)
{
    is_trigger = false;
    s_line.setSize({ length, 2.f });
    s_line.setFillColor(sf::Color::Yellow);
    s_line.setOrigin({ 0.f, 1.f });


    float dotRadius = 4.f;
    end_dot.setRadius(dotRadius);
    end_dot.setFillColor(sf::Color::Green);
    end_dot.setOrigin({ dotRadius, dotRadius });
    end_dot.setPosition({ dist_dot, 0.f });


    setRotation(sf::degrees(angleInDegrees));
}

void Sensor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(end_dot, states);
}


void Sensor::update_sensor(const std::vector<sf::RectangleShape>& obstacles, const sf::Transform& parentTransform, std::vector<sf::Vector2f>& dot_coords) {

    sf::Transform globalTransform = parentTransform * getTransform();

    sf::Vector2f globalDotPosition = globalTransform.transformPoint({ dist_dot, 0.f });

    bool isColliding = false;

  

    for (const auto& obs : obstacles) {

        if (obs.getGlobalBounds().contains(globalDotPosition)) {
          

            isColliding = true;
            update_coords(globalDotPosition, dot_coords);
            break;
        }
    }

    if (isColliding) {
        dist_dot -= 1.0f;
        if (dist_dot < 0.f) dist_dot = 0.f;
    }
    else if (dist_dot < s_length) {
        dist_dot += 1.0f; 
    }

    end_dot.setPosition({ dist_dot, 0.f });
    s_line.setSize({ dist_dot, 2.f });
}

