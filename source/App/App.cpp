#include "App.hpp"

void App::switchScreen(Screen *NextScreen)
{
    delete CurrentScreen;
    CurrentScreen = NextScreen;
}