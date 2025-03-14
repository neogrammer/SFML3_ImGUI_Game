#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include <Resources/Cfg.h>

#include <Tilemap/Tilemap.h>

#include <iostream>
#include <GameObjects/Player/PlayerObj.h>
#include <Physics/Physics.h>
#include <GameObjects/StandardEnemy/StandardEnemy.h>
#include <sstream>
#include <GameObjects/Projectiles/BusterBullet.h>

int main(int argc, char* argv[])
{
    Cfg::Initialize();
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }),"SFML3 Game", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
    window.setVerticalSyncEnabled(true);
    // change the position of the window (relatively to the desktop
    window.setPosition({ 400, 200 });
    // change the title of the window
    window.setTitle("SFML window");
    
    Tilemap tmap1;
    tmap1.Initialize(LevelName::Intro);

    PlayerObj player;
    StandardEnemy enemy;


    // ImGui default Font load
    bool soWhat = ImGui::SFML::Init(window, false);
    soWhat = false;
    auto& IO = ImGui::GetIO();
   IO.Fonts->Clear(); // clear fonts if you loaded some before (even if only default one was loaded)
    // IO.Fonts->AddFontDefault(); // this will load default font as well
    IO.Fonts->AddFontFromFileTTF("Assets\\Fonts\\Crusty.ttf", 18.f);
    sf::Font font2{ "Assets\\Fonts\\frisky_puppy.ttf" };


    // run the program as long as the window is open
    sf::Clock deltaClock;
    // initilialize all buttons to be false
    bool upPressed{ false };
    bool downPressed{ false };
    bool leftPressed{ false };
    bool rightPressed{ false };
    sf::Text mytext{ font2 };
    sf::Vector2i nowPos = {};
    sf::Vector2i nowOff = {};
    sf::Vector2i nowSize = {};
    sf::Vector2i nowVel = {};
    sf::Vector2i nowTRSize = {};
    mytext.setString("");
    mytext.setFillColor(sf::Color::Red);
    mytext.setCharacterSize(24u);
    mytext.setPosition({ 10.f,10.f });
    // main view
    sf::View vw = window.getDefaultView();
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Time dt = deltaClock.restart();
        if (dt.asSeconds() > 0.016f)
        {
            dt = sf::seconds(0.016f);
        }


        static bool presses[4] = { false, };

        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();

            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
                if (keyPressed->scancode == sf::Keyboard::Scancode::W)
                {
                    upPressed = false;
                    presses[0] = upPressed;
                    player.UpdateDPad(presses);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
                {
                    downPressed = false;
                    presses[1] = downPressed;
                    player.UpdateDPad(presses);
                }

                else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
                {
                    leftPressed = false;
                    presses[2] = leftPressed;
                    player.UpdateDPad(presses);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
                {
                    rightPressed = false;
                    presses[3] = rightPressed;
                    player.UpdateDPad(presses);
                }
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::W)
                {
                    upPressed = true;
                    presses[0] = upPressed;
                    player.UpdateDPad(presses);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
                {
                    downPressed = true;
                    presses[1] = downPressed;
                    player.UpdateDPad(presses);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
                {
                    leftPressed = true;
                    presses[2] = leftPressed;
                    player.UpdateDPad(presses);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
                {
                    rightPressed =true;
                    presses[3] = rightPressed;
                    player.UpdateDPad(presses);
                }
            }

        }

        
        // Move mapview accordingly
        if (rightPressed)
        {
            // store players pixel position mapped from coords, and use that to map to coords when moving the player  after the map , or if moving just the player, dont worry about this
            if (vw.getCenter().x < tmap1.Cols() * tmap1.TW() - (vw.getSize().x / 2.f)  && window.mapCoordsToPixel(player.GetPosition()).x >= window.getSize().x * 0.65f)
            {
                vw.setCenter({ vw.getCenter().x + (350.f * dt.asSeconds()), vw.getCenter().y }); // and put player at same pixel in the window as was before the move;         
                if (vw.getCenter().x > tmap1.TW() * tmap1.Cols() - (vw.getSize().x / 2.f))
                {
                    vw.setCenter({ tmap1.TW() * tmap1.Cols() - (vw.getSize().x / 2.f), vw.getCenter().y});
                }
            }
        }
        if (leftPressed)
        {
            if (vw.getCenter().x - (350.f * dt.asSeconds()) > (vw.getSize().x / 2.f) && window.mapCoordsToPixel(player.GetPosition()).x <= window.getSize().x * 0.35f)
                vw.setCenter({ vw.getCenter().x + (-350.f * dt.asSeconds()), vw.getCenter().y });   
        }
        if (upPressed)
        {
            if (vw.getCenter().y - (350.f * dt.asSeconds()) > vw.getSize().y / 2)
                vw.setCenter({ vw.getCenter().x,  vw.getCenter().y + (-350.f * dt.asSeconds()) });
        }
        if (downPressed)
        {
            if (vw.getCenter().y < tmap1.Rows() * tmap1.TH() - (vw.getSize().y / 2))
                vw.setCenter({ vw.getCenter().x,  vw.getCenter().y + (350.f * dt.asSeconds()) });
        }

        for (auto& b : player.getBullets())
        {
            b->update(dt.asSeconds());
        }

        player.update(dt.asSeconds());
        enemy.update(dt.asSeconds());
      


        
        // update other game objects now


        // now ticked, check collisions and adjust accordingly
        for (auto& tile : tmap1.getTiles())
        {
            if (Physics::rectVrect(player.GetPosition(), player.GetSize(), tile->GetPosition(), tile->GetSize()))
            {
                
                Physics::resolveCollision(&player, dynamic_cast<GObj*>(tile));
            }
        }

        // check bullets on enemies
        for (auto& bullet : player.getBullets())
        {
            if (Physics::rectVrect(bullet->GetPosition(), bullet->GetSize(), enemy.GetPosition(), enemy.GetSize()))
            {
                if (enemy.GetHit(dynamic_cast<BusterBullet*>(bullet.get())->GetPower()))
                    bullet->setAlive(false);
                else
                {
                    enemy.sounds.at(Cfg::Sounds::HelmetHit)->play();
                    bullet->SetVelocity({ bullet->GetVelocity().x * -1.f, -40.f });
                   
                }
            }
        }

        // finalize animations

      //  static std::string strng = {""};


    //    const char* str = strng.c_str();


        // render frame

        // ImGui rendering
        soWhat = ImGui::SFML::UpdateFontTexture(); // important call: updates font texture
        ImGui::SFML::Update(window, dt);
        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
 //       ImGui::Text(str);
        ImGui::End();

        // set main game view and clear the window
        window.setView(vw);
        window.clear(sf::Color(47, 147, 247, 255));
        // render tilemap, then gameobjects, then foreground then GUI, then pause screen if paused
        tmap1.Render(window, dt.asSeconds());
      
        enemy.render(window);
        player.render(window);
        for (auto& b : player.getBullets())
        {
            b->render(window);
        }

        //if (player.getFsm().getStateName() == "Shooting")
        //{
        //    nowOff = (sf::Vector2i)player.getFrameOffset();
        //    nowPos = (sf::Vector2i)player.GetPosition();
        //    nowVel = (sf::Vector2i)player.GetVelocity();
        //    nowSize = (sf::Vector2i)player.GetSize();
        //    nowTRSize = player.getTexRectSize();

        //    std::string oss = "Player OutPut at #1 frame index:  ";
        //    oss.append("\n");
        //    oss.append("World: x = " + std::to_string(nowPos.x) + ", y= " + std::to_string(nowPos.y));
        //    oss.append("\n");
        //    oss.append("TexOffsets: x = " + std::to_string(nowOff.x) + ", y = " + std::to_string(nowOff.y));
        //    oss.append("\n");
        //    oss.append("(Size(World) : x = " + std::to_string(nowSize.x) + ", y= " + std::to_string(nowSize.y));
        //    oss.append("\n");
        //    oss.append("Velocity*dt: x= " + std::to_string(nowVel.x) + ", y= " + std::to_string(nowVel.y));
        //    oss.append("\n");
        //    oss.append("Size(TexRect): x= " + std::to_string(nowTRSize.x) + ", y= " + std::to_string(nowTRSize.y));



        //   // strng = oss.str();
        //    
        //    mytext.setString(oss);
        //}
        //window.draw(mytext);


        // and last but not lease ImGui
        ImGui::SFML::Render(window);
        // swap chain buffer pointer swap
                window.display();
                

            


                    

    }

    // cleanup sfml
    ImGui::SFML::Shutdown();
	return 0;
}

