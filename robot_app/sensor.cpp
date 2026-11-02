#include "sensor.hpp"
#include "grid.hpp"
#include <cmath>
#include <iostream>



bool update_coords(sf::Vector2f new_coord, std::vector<sf::Vector2f>&dot_coords){
    /*
        Keep the coords of wall and filter the dots to take of the ones to closes
    */
    for (const auto& coord : dot_coords){
            
        sf::Vector2f dist = coord - new_coord;
        float distance = std::hypot(dist.x, dist.y);

        if (distance < 10.f)
            return false;
        }

    dot_coords.push_back(new_coord);
    return true;
    }

Sensor::Sensor(float length, float angleInDegrees)
/*
init sensor Class
*/
: s_length(length), angle(angleInDegrees),dist_dot(length)

{
    is_trigger = false;
    s_line.setSize({ length, 2.f }); //line of 2 px width
    s_line.setFillColor(sf::Color::Yellow);
    s_line.setOrigin({ 0.f, 1.f });


    float dotRadius = 4.f;
    end_dot.setRadius(dotRadius);
    end_dot.setFillColor(sf::Color::Green);
    end_dot.setOrigin({ dotRadius, dotRadius });
    end_dot.setPosition({ dist_dot, 0.f });

    found_new_wall = false;
    setRotation(sf::degrees(angleInDegrees));
}

void Sensor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(end_dot, states);
}
void Sensor::reset_found_new_wall() {
    found_new_wall = false;
}
bool Sensor::get_found_new_wall() {
    return found_new_wall;
}


void Sensor::update_sensor(const std::vector<sf::RectangleShape>& obstacles, const sf::Transform& parentTransform, std::vector<sf::Vector2f>& dot_coords) {
    //Update the sensor to detect walls
    //Go from the car to the end of the sensor and detect when it's in a wall by stp of 1 pixel

    float step = 1;
    sf::Transform globalTransform = parentTransform * getTransform();

    sf::Vector2f globalDotPosition = globalTransform.transformPoint({ dist_dot, 0.f });

    bool isColliding = false;
    dist_dot = 0;

    for (; dist_dot <= s_length; dist_dot += step) {
        for ( const auto& obs : obstacles) {
        
            globalDotPosition = globalTransform.transformPoint({ dist_dot, 0.f });
            if (obs.getGlobalBounds().contains(globalDotPosition)) {


                isColliding = true;
                update_coords(globalDotPosition, dot_coords);
                found_new_wall = true;
                break;
            }

        }
        if (isColliding) {
            break;
       }
    }
    end_dot.setPosition({ dist_dot, 0.f });
 
}

