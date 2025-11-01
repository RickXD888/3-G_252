#pragma once
#include <vector>
#include "Dibujo.hpp"

using namespace std;
using namespace ftxui;

class Corral {
public:
    int x, y, ancho, alto;
    Dibujo dibujo_corral;
    vector<Dibujo> animales;

    Corral(int x, int y, int ancho, int alto, Color color = Color::White)
        : x(x), y(y), ancho(ancho), alto(alto),
          dibujo_corral(x, y, GenerarFiguraCorral(ancho, alto), color) {}

    static vector<u32string> GenerarFiguraCorral(int ancho, int alto) {
        vector<u32string> figura;
        u32string top = U"+" + u32string(ancho-2, U'-') + U"+";
        u32string mid = U"|" + u32string(ancho-2, U' ') + U"|";
        figura.push_back(top);
        for (int i = 0; i < alto-2; ++i) figura.push_back(mid);
        figura.push_back(top);
        return figura;
    }

    void AgregarAnimal(const Dibujo& animal) {
        // Asegura que el animal esté dentro del corral
        int ax = animal.x;
        int ay = animal.y;
        if (ax < x+1) ax = x+1;
        if (ax > x+ancho-3) ax = x+ancho-3;
        if (ay < y+1) ay = y+1;
        if (ay > y+alto-3) ay = y+alto-3;
        Dibujo animal_dentro(ax, ay, animal.figura, animal.color);
        animales.push_back(animal_dentro);
    }

    void Dibujar(Screen& screen) const {
        dibujo_corral.Dibujar(screen);
        for (const auto& animal : animales) {
            animal.Dibujar(screen);
        }
    }
};