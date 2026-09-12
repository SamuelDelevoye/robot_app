



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
    obstacles.push_back(obs1);

    sf::RectangleShape obs2({ 200.f,50.f });

    obs2.setPosition({ 1500.f,30.f });
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
        window.draw(user_car); 
        for (const auto& obs : obstacles)
        {
            window.draw(obs);
        }
        window.display();
    }

    return 0;
}