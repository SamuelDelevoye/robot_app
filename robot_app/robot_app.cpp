



#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include "car.hpp"


int main()
{
    //Initialisation of window 
    
    sf::RenderWindow window(
        sf::VideoMode({ 1920, 1080 }),
        "Test SFML"
    );

    window.setFramerateLimit(150);

    int frame_count = 0;
    auto last_time = std::chrono::steady_clock::now();

    Car user_car(25.f);
    user_car.setPosition({ 400.f, 300.f }); 


    std::vector<sf::RectangleShape> obstacles;
    
    sf::RectangleShape obs1 ({ 500.f,500.f });

    obs1.setPosition({1000.f,500.f});

    sf::RectangleShape obs2({ 200.f,50.f });

    obs2.setPosition({ 1500.f,30.f });
    

    obs1.setFillColor(sf::Color(0, 0, 0));
    obs2.setFillColor(sf::Color(0, 0, 0));

    obstacles.push_back(obs1);
    obstacles.push_back(obs2); 
    
    /*
    for (int i = 0; i < 10000; i++)
    {
        sf::RectangleShape obstacle({ 50.f, 50.f });

        obstacle.setPosition({
            static_cast<float>((i % 20) * 80),
            static_cast<float>((i / 20) * 80)
            });

        obstacles.push_back(obstacle);
    }*/
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
       
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

        
        user_car.update(obstacles);
        window.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
        {
            for (const auto coords : user_car.get_coord_obs()) {
                sf::CircleShape dot(3.f);

                dot.setOrigin({ 3.f, 3.f });

                dot.setPosition(coords);

                dot.setFillColor(sf::Color::Red);

                window.draw(dot);
            }
        }
        window.draw(user_car); 
        /*for (const auto& obs : obstacles)
        {
            window.draw(obs);
        }*/
        window.display();
    }

    return 0;
}

