#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <Dibujo.hpp>
#include <GestorDibujos.hpp> 

using namespace ftxui;

const std::vector<std::u32string> pacman_open = {
    U"          .';:ccc:;'.. ",
    U"      .;lxOKKKKKKKKK00Odc,. ",
    U"    .ckKKKKKKKKKKKKKKKKK0x:.  ",
    U"   ;kKKKKKKKKKKKKKKKKKKKKKKx' ",
    U"  c0KKKKKKKKKKKKKKKKKKKKKKOx:  ",
    U" ;0KKKKKKKKKKKKKKKKKKK0xl;.  ",
    U".dKKKKKKKKKKKKKKK0xlc;.     ",
    U".xXKKKKKKKKKKKKOo'.       ",
    U".dXKKKKKKKKKKKKKOdl,'.      ",
    U" cKKKKKKKKKKKKKKKKKK0Odl,.    ",
    U" .dKKKKKKKKKKKKKKKKKKKKKKOdl,   ",
    U"  .o0KKKKKKKKKKKKKKKKKKKKKKO:  ",
    U"    ;x0KKKKKKKKKKKKKKKKKK0o'   ",
    U"     .,ok0KKKKKKKKKKKK0xc'  ",
    U"        .':coddddolc:;.  "
};
const std::vector<std::u32string> pacman_closed = 
{
    U"          .';:ccc:;'..  ",
    U"      .;xOKKKKKKKKkK00Odc,.  ",
    U"    .kKKKKKKKKKKKKKKKK0x:.  ",
    U"   ;KKKKKKKKKKKKKkKKKKKKKKx'  ",
    U"  cKKKKKKKKKKKKKKkKkkKKKKKKOx:  ",
    U" ;KKKKKKKKKKKKKKKKKkkKK0kkkkk.   ",
    U".KKKKKKKKKKKKKkkkkkkkkkkkkkkk     ",
    U".xXKKKKKKKKKKKOokkkkkkkkkkkk'k.   ",
    U".dKKKKKKKKKKKKOdlkkkkkkkkkkkk      ",
    U" cKKKKKKKKKKKKKKKK0Odlkkkkk",
    U" .KKKKKKKKKKKKKKKKKKKKKKOdl, ",
    U"  .0KKKKKKKKKKKKKKKKKKKKKO:  ",
    U"    ;0KKKKKKKKKKKKKKKKK0o' ",
    U"     .,kKKKKKKKKKKKK0xc' ",
    U"        .':odddolc:;.  "
};

// Fantasma (Todos los colores usan este sprite)
const std::vector<std::u32string> ghost_sprite = {
    U"              ';;;;;;;;;;              ",
    U"         ....'oOkkOOOOOOO'....         ",
    U"        'oxxxxkkkkkkkkkkkxxxxc.        ",
    U"      'ldxkkkkkkkkkkkkkkkkkkkxoc'      ",
    U"   .:kkkkO0KKK0kkkkkkkkkk00KK0o:,.   ",
    U"   .OkkO0KNNNNX0OOkkkkkO0XNNNNK0x.   ",
    U"   .OkOXNNNNNNXXX0kkkkkXNNNNXNXXO'   ",
    U"   .Ok0XNNNXd:::cokkkkkXNNN0l:cc;.   ",
    U" ';ckk0XNNNKc...'cxkkkkXNNNk,...';;' ",
    U".cOkkOKKXNXxllc:okkkkkKKXN0olc:cxOc.",
    U".ckkkkkkk0XXXXKOkkkkkkkkOKXXXX0kkkkc.",
    U".ckkkk:xOkkkkko,'''',okkkkOo,'lkkkkc.",
    U".cOx:. .;cokkkkl.    .lkkxl:'  .:cdOl.",
    U" ,l;.      .cccl;      ;cc:.      .;l, ",
    U"                                        "
};

const double INITIAL_GAP = 40.0; 

const double GHOST_START_X[4] = { -50.0, -90.0, -130.0, -170.0 }; 
const double PACMAN_START_X = -10.0;                              

int main()
{
    auto screen = Screen::Create(
        Dimension::Fixed(150),
        Dimension::Fixed(20)); 

    GestorDibujos gestor;

    const int START_Y = 2;

    ftxui::Color ghost_colors[] = {
        ftxui::Color::Red,      // Blinky
        ftxui::Color::Magenta,  // Pinky
        ftxui::Color::Cyan,     // Inky
        ftxui::Color::Yellow    // Clyde 
    };

    double pacman_x   = PACMAN_START_X;
    double ghost_x[4] = { GHOST_START_X[0], GHOST_START_X[1], GHOST_START_X[2], GHOST_START_X[3] };

    gestor.Agregar(Dibujo((int)pacman_x, START_Y, pacman_open, ftxui::Color::Yellow));
    
    for (int i = 0; i < 4; i++) {
        gestor.Agregar(Dibujo((int)ghost_x[i], START_Y, ghost_sprite, ghost_colors[i]));
    }

    double pacman_speed = 1; 
    double ghost_speed  = 1.0;  

    int frames = 500;

    for (int frame = 0; frame < frames; frame++)
    {
        screen.Clear();

        pacman_x += pacman_speed;

        for (int i = 0; i < 4; i++)
            ghost_x[i] += ghost_speed;

        if (ghost_x[0] > screen.dimx() + 10) 
        {
            pacman_x = PACMAN_START_X;
            ghost_x[0] = GHOST_START_X[0];
            ghost_x[1] = GHOST_START_X[1];
            ghost_x[2] = GHOST_START_X[2];
            ghost_x[3] = GHOST_START_X[3];
        }

        Dibujo& pacman = gestor.dibujos[0];
        pacman.figura = (frame % 4 < 2) ?
            pacman_open :
            pacman_closed;

        pacman.x = (int)pacman_x;

        for (int i = 0; i < 4; i++)
            gestor.dibujos[1 + i].x = (int)ghost_x[i];

        gestor.DibujarTodos(screen);

        std::cout << screen.ToString();
        std::cout << screen.ResetPosition() << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
    return 0;
}