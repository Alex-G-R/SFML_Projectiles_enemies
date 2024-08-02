#include <iostream>
#include <vector>

#include <Graphics.hpp>
#include <System.hpp>
#include <Window.hpp>
#include <Audio.hpp>
#include <Network.hpp>

#include<cstdlib> // srand
#include <algorithm> // For std::max and std::min

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Works!", sf::Style::Default);
    window.setFramerateLimit(120);

    // Balls
    sf::CircleShape projectile;
    projectile.setRadius(5.f);
    projectile.setFillColor(sf::Color::Blue);

    sf::RectangleShape enemy;
    enemy.setFillColor(sf::Color::Red);
    enemy.setSize(sf::Vector2f(50.f, 50.f));
    int enemy_spawn_timer = 0;

    sf::CircleShape player;
    player.setFillColor(sf::Color::Green);
    player.setRadius(30.f);
    player.setPosition(window.getSize().x/2 - player.getRadius(), window.getSize().y - player.getRadius()*2 - 10.f);
    sf::Vector2f player_center;
    int shoot_timer = 0;

    std::vector<sf::CircleShape> projectiles;
    projectiles.push_back(sf::CircleShape(projectile));

    std::vector<sf::RectangleShape> enemies;
    enemies.push_back(sf::RectangleShape(enemy));

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            //if(event.KeyPressed && event.key.code == sf::Keyboard::Escape)
            //    window.close();
        }

        // Update

        /* Player */
        player_center = sf::Vector2f(player.getPosition().x+player.getRadius(), player.getPosition().y+player.getRadius());

        if(shoot_timer < 3)
            shoot_timer++;


        // Get mouse position relative to the window
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Clamp the x position to the window bounds
        mousePosition.x = std::max(0, std::min(mousePosition.x, static_cast<int>(window.getSize().x - player.getRadius()*2)));

        // Set player's x position while keeping y position unchanged
        player.setPosition(static_cast<float>(mousePosition.x), player.getPosition().y);

        /* Projectiles */
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && shoot_timer >= 3)
        {
            projectile.setPosition(player_center);
            projectiles.push_back(sf::CircleShape(projectile));

            shoot_timer = 0;
        }

        for (size_t i = 0; i < projectiles.size(); i++)
        {
            projectiles[i].move(0.f, -10.f);

            if(projectiles[i].getPosition().y < 0)
                projectiles.erase(projectiles.begin() + i);

        }

        /* Enemies */
        if(enemy_spawn_timer < 8)
            enemy_spawn_timer++;

        if(enemy_spawn_timer >= 8)
        {
            enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0.f);
            enemies.push_back(sf::RectangleShape(enemy));

            enemy_spawn_timer = 0;
        }

        for (size_t i = 0; i < enemies.size(); i++)
        {
            enemies[i].move(0.f, 3.f);

            // Erase enemies out of screen
            if(enemies[i].getPosition().y > 1080)
                enemies.erase(enemies.begin() + i);

        }


        /* Collision */
        for(size_t i = 0; i < projectiles.size(); i++)
        {
            for(size_t j = 0; j < enemies.size(); j++)
            {
                if(projectiles[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
                {
                    projectiles.erase(projectiles.begin() + i);
                    enemies.erase(enemies.begin() + j);
                    break;
                }
            }
        }


        // Draw
        window.clear();
        // Draw stuff

        window.draw(player);
        for (size_t i = 0; i < enemies.size(); i++)
        {
            window.draw(enemies[i]);
        }

        for (size_t i = 0; i < projectiles.size(); i++)
        {
            window.draw(projectiles[i]);
        }


        window.display();
    }

    return 0;
}

