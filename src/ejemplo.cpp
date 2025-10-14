#include <iostream>
using namespace std;
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
using namespace ftxui;

int main()
{
    auto pantalla = Screen::Create(
        Dimension::Full(),
        Dimension::Fixed(10));
    int x = 0;
    int y = 0;

    auto &pixel = pantalla.PixelAt(5, 5);
    pixel.blink = true;
    pixel.background_color = Color::Blue;
    pixel.background_color = Color::Red;
    pixel.character = 'A';
    pantalla.Print();
    // cout << endl;
    return 0;
}