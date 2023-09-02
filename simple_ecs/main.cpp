#include "SlotMap.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "EntityManager.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"
#include "SFMLOrthogonalLayer.hpp"


int main()
{
   
    tmx::Map map;
    bool v = map.load("C:\\Users\\isaig\\level1.tmx");
    MapLayer layerOne(map, 0);
    
    const auto& mapProperties = map.getProperties();

   

    const auto& layers = map.getLayers();
    std::cout << "Map has " << layers.size() << " layers" << std::endl;
    auto& layer = map.getLayers()[0];
    const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
    
    const auto &dim = map.getTileCount();

    std::cout << dim.x << ", " << dim.y << "\n";
    for (int i = 0; i < tiles.size(); i++)
    {
        if (i % dim.x == 0 && i > 0)
        {
            std::cout << "\n";
        }
        std::cout << tiles[i].ID << ",";
     
       
    }
    EntityManager em(100);
    PhysicsSystem phySys;
    RenderSystem renderSys;
    
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
       
        //renderSys.render(em, window);
        window.display();
        
   
    }  
   

    return 0;
}
