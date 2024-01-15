#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Network.hpp>

#include <ClientWebSocketThread.h>

#include <thread>

bool manualManagment = true;

int hightValue = 0;
int moveSpeed = 0;

int valLF = 500;
int valRF = 500;
int valLB = 500;
int valRB = 500;

void display(ImVec2 size = {})
{
    ImGui::Begin("Drones Motor", nullptr, ImGuiWindowFlags_NoMove + ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoTitleBar);
    ImGui::SetWindowPos({0, 0});
    ImGui::SetWindowSize(size);

    ImGui::Checkbox("Manual managment", &manualManagment);
    if(manualManagment)
    {
        ImGui::Columns(2);
        ImGui::SliderInt("LF", &valLF, 0, 1000);
        ImGui::SliderInt("RF", &valRF, 0, 1000);
        ImGui::NextColumn();
        ImGui::SliderInt("LB", &valLB, 0, 1000);
        ImGui::SliderInt("RB", &valRB, 0, 1000);
        ImGui::Columns(1);

        SendMessage(R"({"t":0, "LF":)" + std::to_string(valLF) + R"(, "RF":)" + std::to_string(valRF) + R"(, "LB":)" + std::to_string(valLB) + R"(, "RB":)" + std::to_string(valRB) + "}");

    }
    else
    {
        ImGui::SliderInt("Move speed", &moveSpeed, 0, 100);
        ImGui::SliderInt("Height", &hightValue, 0, 1000);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            SendMessage(R"({"t":1, "key" : "left", "value" : )" + std::to_string(moveSpeed) + R"(, "height" : )" + std::to_string(hightValue) + "}");
            ImGui::Text("LEFT");

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,0));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,0));
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            SendMessage(R"({"t":1, "key" : "back", "value" : )" + std::to_string(moveSpeed) + R"(, "height" : )" + std::to_string(hightValue) + "}");
            ImGui::Text("BACK");

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,0));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,0));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,100));
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            SendMessage(R"({"t":1, "key" : "forward", "value" : )" + std::to_string(moveSpeed) + R"(, "height" : )" + std::to_string(hightValue) + "}");
            ImGui::Text("FORWARD");

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,0));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,0));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            SendMessage(R"({"t":1, "key" : "right", "value" : )" + std::to_string(moveSpeed) + R"(, "height" : )" + std::to_string(hightValue) + "}");
            ImGui::Text("RIGHT");

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,0));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,0));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,100));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
           SendMessage(R"({"t":1, "key" : "yawR", "value" : )" + std::to_string(moveSpeed) + R"(, "height" : )" + std::to_string(hightValue) + "}");
            ImGui::Text("Yaw right");

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,0));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,0));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,100));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            SendMessage(R"({"t":1, "key" : "yawL", "value" : )" + std::to_string(moveSpeed) + R"(, "height" : )" + std::to_string(hightValue) + "}");
            ImGui::Text("Yaw left");

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,0));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,0));
        }
        else
        {
            ImGui::Text("STOP");

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddLine({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, {ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, ImColor(100,100,100), 10);

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 100}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,100));

            ImGui::GetWindowDrawList()->AddCircleFilled({ImGui::GetWindowPos().x + 200, ImGui::GetWindowPos().y + 200}, 20, ImColor(100,100,100));
        }   
    }
    ImGui::End();
}


int main()
{
    // Нужно для запуска потока с сервером
    memset(&info, 0, sizeof info);
    info.port = 41235;
    info.protocols = protocols;
    context = lws_create_context(&info);
    std::thread t1(run);
    t1.detach();

    sf::RenderWindow window(sf::VideoMode(800, 480), "Arduino UDP");
    window.setFramerateLimit(60);

    if(ImGui::SFML::Init(window))
    {
        sf::Clock deltaClock;
        while (window.isOpen())
        {
            sf::Event event{};
            while (window.pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(window, event);
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            ImGui::SFML::Update(window, deltaClock.restart());

            // Вызов вашей функции здесь
            display({(float)window.getSize().x, (float)window.getSize().y});

            window.clear();
            ImGui::SFML::Render(window);
            window.display();
        }
        ImGui::SFML::Shutdown();
    }

    running_ = false;
    lws_context_destroy(context);
    return 0;
}
