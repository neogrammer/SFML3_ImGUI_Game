#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include <Resources/Cfg.h>

#include <Tilemap/Tilemap.h>

#include <iostream>
#include <GameObjects/Player/PlayerObj.h>


int main(int argc, char* argv[])
{
    Cfg::Initialize();
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }),"SFML3 Game", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
    // change the position of the window (relatively to the desktop
    window.setPosition({ 400, 200 });
    // change the title of the window
    window.setTitle("SFML window");
    
    Tilemap tmap1;
    tmap1.Initialize(LevelName::Intro);

    PlayerObj player;


    // ImGui default Font load
    bool soWhat = ImGui::SFML::Init(window, false);
    soWhat = false;
    auto& IO = ImGui::GetIO();
   IO.Fonts->Clear(); // clear fonts if you loaded some before (even if only default one was loaded)
    // IO.Fonts->AddFontDefault(); // this will load default font as well
    IO.Fonts->AddFontFromFileTTF("Assets\\Fonts\\Crusty.ttf", 18.f);


    // run the program as long as the window is open
    sf::Clock deltaClock;
    // initilialize all buttons to be false
    bool upPressed{ false };
    bool downPressed{ false };
    bool leftPressed{ false };
    bool rightPressed{ false };
    // main view
    sf::View vw = window.getDefaultView();
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Time dt = deltaClock.restart();
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
                if (keyPressed->scancode == sf::Keyboard::Scancode::W)
                    upPressed = false;
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
                    downPressed = false;
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
                    leftPressed = false;
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
                    rightPressed = false;
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::W)
                    upPressed = true;
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
                    downPressed = true;
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
                    leftPressed = true;
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
                    rightPressed = true;
            }
        }
        // Move mapview accordingly
        if (rightPressed)
        {
            // store players pixel position mapped from coords, and use that to map to coords when moving the player  after the map , or if moving just the player, dont worry about this
            if (vw.getCenter().x < tmap1.Cols() * tmap1.TW() - (vw.getSize().x / 2.f))
                vw.setCenter({ vw.getCenter().x + (300.f * dt.asSeconds()), vw.getCenter().y}); // and put player at same pixel in the window as was before the move;         
        }
        if (leftPressed)
        {
            if (vw.getCenter().x - (300.f * dt.asSeconds()) > vw.getSize().x / 2)
                vw.setCenter({ vw.getCenter().x + (-300.f * dt.asSeconds()), vw.getCenter().y });   
        }
        if (upPressed)
        {
            if (vw.getCenter().y - (300.f * dt.asSeconds()) > vw.getSize().y / 2)
                vw.setCenter({ vw.getCenter().x,  vw.getCenter().y + (-300.f * dt.asSeconds()) });
        }
        if (downPressed)
        {
            if (vw.getCenter().y < tmap1.Rows() * tmap1.TH() - (vw.getSize().y / 2))
                vw.setCenter({ vw.getCenter().x,  vw.getCenter().y + (300.f * dt.asSeconds()) });
        }

        player.update(dt.asSeconds());
     

        // ImGui rendering
        soWhat = ImGui::SFML::UpdateFontTexture(); // important call: updates font texture
        ImGui::SFML::Update(window, dt);
        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        // set main game view and clear the window
        window.setView(vw);
        window.clear(sf::Color(47, 147, 247, 255));
        // render tilemap, then gameobjects, then foreground then GUI, then pause screen if paused
        tmap1.Render(window, dt.asSeconds());

        player.render(window);
        // and last but not lease ImGui
        ImGui::SFML::Render(window);
        // swap chain buffer pointer swap
        window.display();
    }

    // cleanup sfml
    ImGui::SFML::Shutdown();
	return 0;
}

