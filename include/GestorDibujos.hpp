#pragma once
#include <vector>
#include "Dibujo.hpp"
#include <ftxui/screen/screen.hpp>

using namespace std;
using namespace ftxui;

class GestorDibujos {
public:
    vector<Dibujo> dibujos;

    void Agregar(const Dibujo &dibujo) {
        dibujos.push_back(dibujo);
    }

    void Mover(size_t idx, int dx, int dy) {
        if (idx < dibujos.size()) {
            dibujos[idx].x += dx;
            dibujos[idx].y += dy;
        }
    }

    void DibujarTodos(Screen &screen) const {
        for (const auto &dibujo : dibujos) {
            dibujo.Dibujar(screen);
        }
    }
};
