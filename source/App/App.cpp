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
        if(NextScreen!=CurrentScreen)//if the screen is changed
        {
            delete CurrentScreen;
            CurrentScreen = NextScreen;
        }
    }
}
