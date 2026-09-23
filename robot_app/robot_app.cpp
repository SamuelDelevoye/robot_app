



#include <SFML/Graphics.hpp>
#include <vector>

#include "car.hpp"


int main()
{
    //Initialisation of window 
    
    sf::RenderWindow window(
        sf::VideoMode({ 1920, 1080 }),
        "Test SFML"
    );


    Car user_car(25.f);
    user_car.setPosition({ 400.f, 300.f }); 


    std::vector<sf::RectangleShape> obstacles;

    sf::RectangleShape obs1 ({ 100.f,100.f });

    obs1.setPosition({1000.f,500.f});

    sf::RectangleShape obs2({ 200.f,50.f });

    obs2.setPosition({ 1500.f,30.f });
    

    obs1.setFillColor(sf::Color(0, 0, 0));
    obs2.setFillColor(sf::Color(0, 0, 0));

    obstacles.push_back(obs1);
    obstacles.push_back(obs2);


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
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
        for (const auto& obs : obstacles)
        {
            window.draw(obs);
        }
        window.display();
    }

    return 0;
}

