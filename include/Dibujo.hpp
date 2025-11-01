#pragma once

// Clase para dibujar figuras ASCII en la pantalla usando FTXUI
#include <vector>
#include <string>
#include <ftxui/screen/screen.hpp>

using namespace std;      // Para no escribir std::
using namespace ftxui;    // Para no escribir ftxui::

class Dibujo {
public:
    int x, y;
    vector<u32string> figura;
    Color color;

    Dibujo(int x, int y, const vector<u32string>& figura, Color color = Color::White)
        : x(x), y(y), figura(figura), color(color) {}

    void Dibujar(Screen& screen) const {
        for (size_t row = 0; row < figura.size(); ++row) {
            for (size_t col = 0; col < figura[row].size(); ++col) {
                int px = x + col;
                int py = y + row;
                if (px < screen.dimx() && py < screen.dimy() && figura[row][col] != U' ') {
                    auto& pixel = screen.PixelAt(px, py);
                    pixel.character = figura[row][col];
                    pixel.bold = true;
                    pixel.foreground_color = color;
                }
            }
        }
    }
};
