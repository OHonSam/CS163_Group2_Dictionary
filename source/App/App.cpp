#include "App.hpp"

App::App()
{
    dict = new Dict();
    CurrentScreen = new HomeScreen(dict);
}

void App::run()
{
    while (CurrentScreen != nullptr)
    {
        Screen *NextScreen = CurrentScreen->render();
        if (NextScreen != CurrentScreen)
        {
            delete CurrentScreen;
            CurrentScreen = NextScreen;
        }
    }
    dict -> ~Dict();
    return;
}
