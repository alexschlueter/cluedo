#include <vector>

// A game of CLUEDO
class CluedoSpiel
{
    enum class Charakter
    {
        Gloria, Gatow, Porz, Grün, Weiß, Bloom
    };

    std::vector<Charakter> _spieler;

public:
    CluedoSpiel(std::vector<Charakter> spieler);

    void zug(int feldX, int feldY);
};
