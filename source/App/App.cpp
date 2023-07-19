#include "App.hpp"

App::App()
{
    CurrentScreen = new Home(&dict);
}

void App::run()
{
    while (CurrentScreen != nullptr)
    {
        Screen* NextScreen=CurrentScreen->render();
        delete CurrentScreen;
        CurrentScreen = NextScreen;
    }
}
