#include "App.hpp"

void App::switchScreen(Screen *NextScreen)
{
    delete CurrentScreen;
    CurrentScreen = NextScreen;
}

void App::run()
{
    while (!CurrentScreen->getIsEnd())
        CurrentScreen->render();
    delete CurrentScreen;
}
