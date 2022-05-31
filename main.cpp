#include "game.cpp"
#include "menu.cpp"

int main()
{
    Menu menu;
    int opt = menu.run();

    if (opt == 0)
    {
        std::cout << "Playing game...\n";
        Game game;
        game.run();
    }
    else if (opt == 1)
    {
        std::cout << "Instruction of the game or smthing\n";
    }
    else
        std::cout << "Quit the game!\n";

    return 0;
}