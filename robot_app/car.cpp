#include "car.hpp"
#include <cmath>
#include <algorithm>
#include <numbers>
#include <iostream>

//function that go with the entitie car

const float lin_speed = 2;
const float rot_speed = 2;
const float sensor_size = 400.f;

Car::Car(float radius, int wind_width, int wind_height,float init_target_x,float init_target_y)
    : car_shape(radius), car_speed(lin_speed),
    sensors{        //Creation for the 5 sensors of the car
          Sensor(sensor_size, 0.f),
          Sensor(sensor_size, 22.5f),
          Sensor(sensor_size, 45.f),
          Sensor(sensor_size, -22.5f),
          Sensor(sensor_size, -45.f)
    },
    algo_grid(radius * 2, wind_width, wind_height)
{
    car_shape.setOrigin({ radius, radius });
    car_shape.setFillColor(sf::Color::Blue);

    current_box = nullptr;
    next_box = nullptr;

    auto_move = false;


    view_line.setSize({ 150.f,1.f });
    view_line.setOrigin({ 0.f, 0.5f });
    view_line.setPosition({radius,0.f });
    view_line.setFillColor(sf::Color::Red);

    //init the target coords and initiate the cost for each box
    target_x = init_target_x;
    target_y = init_target_y;
    algo_grid.wavefront_init(target_x, target_y);
    
}

void Car::update(const std::vector<sf::RectangleShape>& obstacles)
/*
function for update :
    if not auto we can move it with the arrows
    if auto it goes to the target
*/
{

    if (!auto_move) {
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
    else {

        if (auto_move)
        {
            //found the box of the car

            if (current_box == nullptr)
                
                current_box = algo_grid.get_box_of_point(
                    getPosition().x, getPosition().y
                );

            //if we know we can move to the next box

            if (current_box != nullptr) //check if the path exist
            {
                next_box = current_box->get_previous();

                if (next_box != nullptr)
                {
                    sf::Vector2f target = next_box->get_middle_coords();

                    float dx = target.x - getPosition().x;
                    float dy = target.y - getPosition().y;
                    float distance = std::hypot(dx, dy);

                    if (distance < 2.f)
                    {
                        current_box = next_box;
                    }
                    else
                    {
                        move_toward(target.x, target.y,obstacles);
                    }
                }
            }
        }
    }

    //Look if we detect new walls a

    bool grid_changed = false;

    for (auto& sensor : sensors)
    {
        sensor.update_sensor(obstacles, getTransform(), dot_coords);

        if (sensor.get_found_new_wall())
        {
            sf::Vector2f p = dot_coords.back();

            if (algo_grid.place_obstacle(p.x, p.y))
                grid_changed = true;
        }
    }

    //If it changed we need to redo the wavefront grid

    if (grid_changed)
    {
        algo_grid.wavefront_init(target_x, target_y);

        current_box = algo_grid.get_box_of_point(
            getPosition().x, getPosition().y
        );

        next_box = nullptr;
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

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    algo_grid.draw_path(target, states, current_box);

    states.transform *= getTransform();

    target.draw(car_shape, states);    
    //target.draw(view_line, states);
    for (auto& sensor : sensors)
    {
        target.draw(sensor, states);
    }

    
}

std::vector<sf::Vector2f> Car::get_coord_obs() {
    return dot_coords;
    
}
void Car::set_auto_move(bool new_auto_move) {
    auto_move = new_auto_move;
}

void Car::turn_toward(float target_angle){

    float current_angle = getRotation().asRadians();

    float diff = target_angle - current_angle;

    // Normalize the angle difference to [-pi, pi]
    while (diff > std::numbers::pi_v<float>)
        diff -= 2.f * std::numbers::pi_v<float>;

    while (diff < -std::numbers::pi_v<float>)
        diff += 2.f * std::numbers::pi_v<float>;

    // Stop when the target angle is reached
    if (std::abs(diff) < 0.01f)
        return;

    float max_step = sf::degrees(rot_speed).asRadians();
    float step = std::clamp(diff, -max_step, max_step);

    rotate(sf::radians(step));
}

void Car::move_toward(float coord_x, float coord_y, const std::vector<sf::RectangleShape>& obstacles){
    //look if the car can drive forward without going into a wall
    
    float direction_x = coord_x - getPosition().x;
    float direction_y = coord_y - getPosition().y;


    float distance = std::sqrt(
        direction_x * direction_x +
        direction_y * direction_y );

    if (distance < 2.f)
        return;

    float target_angle = std::atan2(direction_y, direction_x);

    float current_angle = getRotation().asRadians();

    float diff = target_angle - current_angle;

    while (diff > std::numbers::pi_v<float>)
        diff -= 2.f * std::numbers::pi_v<float>;

    while (diff < -std::numbers::pi_v<float>)
        diff += 2.f * std::numbers::pi_v<float>;

    if (std::abs(diff) > 0.01f) //check if it's close anougth to avoid oscilation
    {
        turn_toward(target_angle);
    }
    else
    {
        if (can_move(obstacles)) {


            move({
                std::cos(current_angle) * car_speed,
                std::sin(current_angle) * car_speed
                });
        }
    }
}

void Car::update_target(float x, float y)
{
    //used to update the coords of the target

    target_x = x;
    target_y = y;

    algo_grid.wavefront_init(target_x, target_y);

    current_box = algo_grid.get_box_of_point(
        getPosition().x, getPosition().y
    );

    next_box = nullptr;
}