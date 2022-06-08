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
        std::cout << "Continue the last level you've played\n";

        std::ifstream fin("assets/level/lastlevel.txt");

        if (!fin.is_open())
            std::cout << "Cannot open the file\n";

        int level;
        fin >> level;
        fin.close();

        Game game;
        game.run(level);
    }
    else
        std::cout << "Quit the game!\n";

    return 0;
}