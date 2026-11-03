
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include "car.hpp"
#include "box.hpp"
#include "grid.hpp"
const float radius = 25.f;
const int wind_width = 1920;
const int wind_height = 1080;

/*
auto_type = true if we want the automatic car with algo
auto_type = false if we want to control the car
*/
const bool auto_type = true; 

int main()
{
    //Initialisation of window 
    
    sf::RenderWindow window(
        sf::VideoMode({ wind_width, wind_height }),
        "Test SFML"
    );

    sf::RenderWindow window2(
        sf::VideoMode({ wind_width, wind_height }),

        "Fenetre Secondaire");

    //function to set frame max

    window.setFramerateLimit(150);
    window2.setFramerateLimit(150);


    int frame_count = 0;
    auto last_time = std::chrono::steady_clock::now();
    
    

    std::vector<sf::RectangleShape> obstacles;

    // Create the obstacles
    auto createObstacle = [](sf::Vector2f size, sf::Vector2f position)
        {
            sf::RectangleShape obstacle(size);
            obstacle.setPosition(position);
            obstacle.setFillColor(sf::Color(100, 0, 0));

            return obstacle;
        };

    //Creation of the map:
    
    // walls exte
    obstacles.push_back(createObstacle({ 1800.f, 40.f }, { 50.f, 50.f }));     
    obstacles.push_back(createObstacle({ 1800.f, 40.f }, { 50.f, 990.f }));    
    obstacles.push_back(createObstacle({ 40.f, 980.f }, { 50.f, 50.f }));      
    obstacles.push_back(createObstacle({ 40.f, 980.f }, { 1810.f, 50.f }));    


   
    obstacles.push_back(createObstacle({ 300.f, 150.f }, { 800.f, 450.f }));


    obstacles.push_back(createObstacle({ 50.f, 300.f }, { 500.f, 200.f }));


    obstacles.push_back(createObstacle({ 50.f, 300.f }, { 1400.f, 300.f }));


    obstacles.push_back(createObstacle({ 250.f, 50.f }, { 300.f, 700.f }));


    obstacles.push_back(createObstacle({ 250.f, 50.f }, { 1200.f, 750.f }));


    obstacles.push_back(createObstacle({ 100.f, 100.f }, { 700.f, 150.f }));
    obstacles.push_back(createObstacle({ 100.f, 100.f }, { 1200.f, 150.f }));
    
    //target for car
    float target_x = 1500;
    float target_y = 500;
    sf::CircleShape target(12.f);

    target.setOrigin({ 12.f, 12.f });
    target.setPosition({target_x, target_y });
    target.setFillColor(sf::Color::Red);
    sf::Vector2f target_pos = target.getPosition();

    //init for the algorythme 

    Grid grid(radius*2, wind_width, wind_height);
    grid.place_cost(target_pos.x, target_pos.y);


    //init of the car
    Car user_car(radius, wind_width, wind_height, target_x, target_y);
    user_car.setPosition({ 300.f, 300.f });

    user_car.set_auto_move(auto_type);

    //start of windows
    while (window.isOpen() || window2.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        while (const std::optional event = window2.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window2.close();
        }

       
        //Frame Count : 

        frame_count++;

        auto current_time = std::chrono::steady_clock::now();

        float elapsed = std::chrono::duration<float>(
            current_time - last_time
        ).count();

        if (elapsed >= 1.0f)
        {
            std::cout << "FPS: " << frame_count << std::endl;

            frame_count = 0;
            last_time = current_time;
        }

        //Update the car

        user_car.update(obstacles);

        for (const auto& point : user_car.get_coord_obs())
        {
            sf::CircleShape dot(3.f);
            dot.setPosition(point);
            //window_points.draw(dot);
        }

        //target
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
        {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            sf::Vector2f world_pos = window.mapPixelToCoords(mouse_pos);

            target.setPosition(world_pos);

            target_x = world_pos.x;
            target_y = world_pos.y;
            user_car.update_target(target_x, target_y);
            
        }
        //Draw component :

        window.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
        {
            user_car.turn_toward(90);
            for (const auto coords : user_car.get_coord_obs()) {
                sf::CircleShape dot(3.f);

                dot.setOrigin({ 3.f, 3.f });

                dot.setPosition(coords);

                dot.setFillColor(sf::Color::Red);

                window.draw(dot);
            }
        }
        window.draw(user_car); 
        

        for (const auto& obs : obstacles)
        {
            window.draw(obs);
        }
      
        window.draw(target);
        window.display();

        
        window2.clear();

        for (const auto& point : user_car.get_coord_obs())
        {
            sf::CircleShape dot(3.f);

            dot.setOrigin({ 3.f, 3.f });
            dot.setPosition(point);
            dot.setFillColor(sf::Color::Red);

            window2.draw(dot);

        }
        //window2.draw(grid);
        window2.draw(user_car);
        window2.draw(target);
        window2.display();
        


    }

    return 0;
}

