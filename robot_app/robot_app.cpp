



#include <SFML/Graphics.hpp>
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



    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        user_car.update();
        window.clear();
        window.draw(user_car); 
        window.display();
    }

    return 0;
}