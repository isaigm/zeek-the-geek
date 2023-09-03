#include <SFML/Graphics.hpp>
#include "EntityManager.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"
#include "SlotMap.hpp"
#include "Level.hpp"

int main()
{
    EntityManager em(100);
    PhysicsSystem phySys;
    RenderSystem renderSys;
    Level level("assets/level1.tmx");
    
    
    sf::RenderWindow window(sf::VideoMode(17 * 36, 12 * 36), "");
    

    window.setVerticalSyncEnabled(true);
    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }
        phySys.update(em, dt);
        window.clear(sf::Color::White);
        renderSys.render(em, window);
        window.display();
        
   
    }  
  
    return 0;
}
