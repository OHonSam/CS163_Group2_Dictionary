#include "App.hpp"

App::App()
{
    CurrentScreen = new HomeScreen(&dict);
}

void App::run()
{
    // while (CurrentScreen != nullptr)
    // {
    // Screen *NextScreen = CurrentScreen->render();
    //     if (NextScreen != CurrentScreen)
    //     {
    // delete CurrentScreen;
    //         CurrentScreen = NextScreen;
    //     }
    // }

    CurrentScreen->render();

}
