#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include <Resources/Cfg.h>

#include <GameObjects/GameObject.h>


int main(int argc, char* argv[])
{
    Cfg::Initialize();

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }),"SFML3 Game", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
    bool soWhat = ImGui::SFML::Init(window, false);
    soWhat = false;

    auto& IO = ImGui::GetIO();
   IO.Fonts->Clear(); // clear fonts if you loaded some before (even if only default one was loaded)
    // IO.Fonts->AddFontDefault(); // this will load default font as well
    IO.Fonts->AddFontFromFileTTF("Assets\\Fonts\\Crusty.ttf", 18.f);

 

    // change the position of the window (relatively to the desktop)
    window.setPosition({ 400, 200 });

    // change the title of the window
    window.setTitle("SFML window");

    sf::Sprite playerSpr(Cfg::textures.get((int)Cfg::Textures::PlayerAtlas));
    playerSpr.setTextureRect({ {0*130,1*160},{130,160} });
    playerSpr.setPosition({300.f, 390.f});

    std::vector<sf::Sprite> tiles;
    for (int i = 0; i < SCREENTILESY - 1; i++)
    {
        tiles.emplace_back(sf::Sprite{ Cfg::textures.get((int)Cfg::Textures::Tileset1) });
        tiles[tiles.size() - (size_t)1].setTextureRect({ {0 * 50,0 * 50},{50,50} });
        tiles[tiles.size() - (size_t)1].setPosition({ 0.f, i * 50.f });
    }
    for (int i = 0; i < SCREENTILESX; i++)
    {
        tiles.emplace_back(sf::Sprite{ Cfg::textures.get((int)Cfg::Textures::Tileset1) });
        tiles[tiles.size() - (size_t)1].setTextureRect({ {0 * 50,0 * 50},{50,50} });
        tiles[tiles.size() - (size_t)1].setPosition({ i * 50.f, 550.f});
    }


    GameObject gameObject{ {500.f, 400.f}, {50.f,50.f} };

    // run the program as long as the window is open
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::W)
                {
                    gameObject.move({0.f , -200 * 0.013f});
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
                {
                    gameObject.move({ 0.f , 200 * 0.013f });
                }

                if (keyPressed->scancode == sf::Keyboard::Scancode::A)
                {
                    gameObject.move({ -200 * 0.013f, 0.f });
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
                {
                    gameObject.move({ 200 * 0.013f, 0.f });
                }
            }

        }
        gameObject.Update(0.00013f);

        soWhat = ImGui::SFML::UpdateFontTexture(); // important call: updates font texture
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear(sf::Color(47, 147, 247, 255));

        for (auto& spr : tiles)
        {
            window.draw(spr);

        }
        window.draw(playerSpr);

        gameObject.Render(window);

        ImGui::SFML::Render(window);
        window.display();

    }

    ImGui::SFML::Shutdown();
	return 0;

}