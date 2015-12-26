#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <tuple>
#include <sstream>
#include <stdio.h>

using std::cout;
using std::cin;
using std::endl;

template<std::size_t> struct int_{};

template <class Tuple, size_t Pos>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<Pos> ) {
    out << std::get< std::tuple_size<Tuple>::value-Pos >(t) << ',';
    return print_tuple(out, t, int_<Pos-1>());
}

template <class Tuple>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<1> ) {
    return out << std::get<std::tuple_size<Tuple>::value-1>(t);
}

template <class... Args>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t) {
    out << '('; 
    print_tuple(out, t, int_<sizeof...(Args)>()); 
    return out << ')';
}

typedef std::tuple<int, int> Koord;

bool willNichtBleiben()
{
    char c;
    do
    {
        cout << "Du wurdest von einem anderen Spieler teleportiert! Möchtest du in diesem Raum fragen? [j/n]";
        c = getchar();
    }
    while (c != 'j' && c != 'n');

    return c == 'n'; // will nicht bleiben
}

int frageZahl(int max)
{
    std::string eingabe;
    int zahl;
    for (;;)
    {
        getline(cin, eingabe);
        std::stringstream ss(eingabe);
        if (ss >> zahl && zahl >= 1 && zahl <= max) break;
        cout << "Ungültige Eingabe (Zahl zwischen 1 und " << max << ")" << endl;
    }
    return  zahl;
}

int frageOptionen(std::vector<std::string> optionen)
{
    for (size_t i = 0; i < optionen.size(); ++i)
    {
        cout << i + 1 << ". " << optionen[i] << endl;
    }
    return frageZahl(optionen.size());
}

enum class Raum
{
    Schlaf, Bade, Arbeits, Küche, Speise, Wohn, Hof, Garage, Spiele, Mitte
};

enum class Charakter
{
    Gloria, Gatow, Porz, Grün, Weiß, Bloom
};

enum class Waffe
{
    Rohrzange, Dolch, Heizungsrohr, Leuchter, Pistole, Seil
};

enum class Richtung
{
    Oben, Unten, Rechts, Links
};

struct Karte
{
    enum class KartenTyp
    {
        CharT, RaumT, WaffeT
    } typ;

    union
    {
        Charakter charakter;
        Raum raum;
        Waffe waffe;
    };

    Karte() : typ(KartenTyp::CharT), charakter(Charakter::Gloria) {};
    Karte(Raum r) : typ(KartenTyp::RaumT), raum(r) {};
    Karte(Charakter c) : typ(KartenTyp::CharT), charakter(c) {};
    Karte(Waffe w) : typ(KartenTyp::WaffeT), waffe(w) {};
    Karte(const Karte& andere)
    {
        typ = andere.typ;
        if (typ == KartenTyp::CharT)
        {
            charakter = andere.charakter;
        }
        else if (typ == KartenTyp::RaumT)
        {
            raum = andere.raum;
        }
        else
        {
            waffe = andere.waffe;
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Karte &karte)
{
    switch (karte.typ)
    {
    case Karte::KartenTyp::CharT:
        switch (karte.charakter)
        {
        case Charakter::Gloria:
            os << "Gloria"; break;
        case Charakter::Gatow:
            os << "Gatow"; break;
        case Charakter::Porz:
            os << "Porz"; break;
        case Charakter::Grün:
            os << "Grün"; break;
        case Charakter::Weiß:
            os << "Weiß"; break;
        case Charakter::Bloom:
            os << "Bloom"; break;
        }
        break;
    case Karte::KartenTyp::RaumT:
        switch(karte.raum)
        {
        case Raum::Schlaf:
            cout << "Schlafzimmer"; break;
        case Raum::Bade:
            cout << "Badezimmer"; break;
        case Raum::Arbeits:
            cout << "Arbeitszimmer"; break;
        case Raum::Küche:
            cout << "Küche"; break;
        case Raum::Speise:
            cout << "Speisezimmer"; break;
        case Raum::Wohn:
            cout << "Wohnzimmer"; break;
        case Raum::Hof:
            cout << "Hof"; break;
        case Raum::Garage:
            cout << "Garage"; break;
        case Raum::Spiele:
            cout << "Spieleraum"; break;
        case Raum::Mitte:
            cout << "Mitte"; break;
        }
        break;
    case Karte::KartenTyp::WaffeT:
        switch (karte.waffe)
        {
        case Waffe::Rohrzange:
            os << "Rohrzange"; break;
        case Waffe::Dolch:
            os << "Dolch"; break;
        case Waffe::Heizungsrohr:
            os << "Heizungsrohr"; break;
        case Waffe::Leuchter:
            os << "Leuchter"; break;
        case Waffe::Pistole:
            os << "Pistole"; break;
        case Waffe::Seil:
            os << "Seil"; break;
        }
    }
    return os;
}

void zeigeKarten(std::vector<Karte> karten)
{
    cout << "[";
    for (int i = 0; i < karten.size() - 1; ++i)
    {
        cout << karten[i] << ", ";
    }
    cout << karten[karten.size() - 1] << "]";
}

struct Position
{
    enum class PosTyp
    {
        Feld, Raum
    } typ{PosTyp::Raum};


    union
    {
        Koord feld;
        Raum raum{Raum::Mitte};
    };

    void geheNach(int richtung)
    {
        switch (richtung)
        {
        case 1:
            ++std::get<1>(feld); break;
        case 2:
            --std::get<1>(feld); break;
        case 3:
            ++std::get<0>(feld); break;
        case 4:
            --std::get<0>(feld); break;
        }
    }

    static Raum charZuRaum(char c)
    {
        switch (c)
        {
        case 'a':
            return Raum::Schlaf;
        case 'b':
            return Raum::Bade;
        case 'c':
            return Raum::Arbeits;
        case 'd':
            return Raum::Küche;
        case 'e':
            return Raum::Spiele;
        case 'f':
            return Raum::Speise;
        case 'g':
            return Raum::Mitte;
        case 'h':
            return Raum::Garage;
        case 'i':
            return Raum::Wohn;
        case 'j':
            return Raum::Hof;
        }
    }

    Position() {};
    Position(const Position& andere)
    {
        typ = andere.typ;
        if (typ == PosTyp::Feld)
        {
            feld = andere.feld;
        }
        else
        {
            raum = andere.raum;
        }
    }

    Position& operator=(const Position& andere)
    {
        typ = andere.typ;
        if (typ == PosTyp::Feld)
        {
            feld = andere.feld;
        }
        else
        {
            raum = andere.raum;
        }
        return *this;
    }

    bool operator==(const Position& andere) const
    {
        if (typ != andere.typ) return false;
        return (typ == PosTyp::Feld && feld == andere.feld)
            || (typ == PosTyp::Raum && raum == andere.raum);
    }
};

int main()
{
    std::random_device rd;
    std::mt19937 mt(rd());

    // Lade Brett
    std::ifstream brettDatei("brett.clb");
    std::vector<std::string> brett;
    while (! brettDatei.eof())
    {
        std::string zeile;
        getline(brettDatei, zeile);
        brett.push_back(zeile);
    }

    // Welcher Spieler spielen?
    std::vector<Charakter> spieler;
    cout << "Welche Charaktere spielen in welcher Reihenfolge mit?" << endl;
    std::string input;
    for (int i = 1; i <= 6; ++i)
    {
        cout << i << ".\t";
        getline(cin, input);
        if (input == "Gloria") spieler.push_back(Charakter::Gloria);
        else if (input == "Gatow") spieler.push_back(Charakter::Gatow);
        else if (input == "Porz") spieler.push_back(Charakter::Porz);
        else if (input == "Grün") spieler.push_back(Charakter::Grün);
        else if (input == "Weiß") spieler.push_back(Charakter::Weiß);
        else if (input == "Bloom") spieler.push_back(Charakter::Bloom);
        else if (input.empty()) break;
        else cout << "Falsche Eingabe!";
    }
    cout << endl;

    int spielerAnzahl = spieler.size();
    std::vector<Position> positionen(spielerAnzahl);
    int geradeDran;
    std::vector<bool> wurdeTeleportiert(spielerAnzahl);
    std::vector<bool> hatVerloren(spielerAnzahl);
    std::vector<Karte> karten;
    std::vector<std::vector<Karte>> spKarten(spielerAnzahl);
    for (int i = 0; i < 9; ++i)
    {
        karten.push_back(static_cast<Raum>(i));
    }
    for (int i = 0; i < 6; ++i)
    {
        karten.push_back(static_cast<Charakter>(i));
    }
    for (int i = 0; i < 6; ++i)
    {
        karten.push_back(static_cast<Waffe>(i));
    }
    std::array<Karte, 3>  akte;
    for (int i = 0; i < 3; ++i)
    {
        std::uniform_int_distribution<> dist(0, karten.size() - 1);
        int pos = dist(mt);
        akte[i] = karten[pos];
        karten.erase(karten.begin() + pos);
    }

    while (karten.size() >= spielerAnzahl)
    {
        for (auto &sp : spKarten)
        {
            std::uniform_int_distribution<> dist(0, karten.size() - 1);
            int pos = dist(mt);
            sp.push_back(karten[pos]);
            karten.erase(karten.begin() + pos);
        }
    }
    // Wer darf anfangen?
    std::uniform_int_distribution<> spieler_dist(1, spielerAnzahl);
    geradeDran = spieler_dist(mt);
    cout << "Spieler " << geradeDran << " darf anfangen." << endl;

    for (;; geradeDran = (geradeDran) % spielerAnzahl + 1)
    {
        if (hatVerloren[geradeDran]) break; // Spieler darf nicht mehr ziehen oder fragen
        cout << "Deine Karten: ";
        zeigeKarten(spKarten[geradeDran - 1]);
        cout << endl;

        cout << "Bereit zum Würfeln?";
        getchar();
        // Würfelzufall
        std::uniform_int_distribution<> würfel_dist(2, 12);
        int wurf = würfel_dist(mt);
        cout << "Du hast eine " << wurf << " gewürfelt." << endl;

        auto startPos = positionen[geradeDran - 1];
        Position pos = startPos;
        if (! wurdeTeleportiert[geradeDran - 1] || willNichtBleiben())
        {
            do
            {
                cout << "Du stehst gerade ";
                if (pos.typ == Position::PosTyp::Feld)
                {
                    cout << "auf Feld " << pos.feld << ". Optionen:" << endl;
                    char posCh = brett[7 - std::get<1>(pos.feld)][std::get<0>(pos.feld) + 3];
                    if (posCh >= 'A') posCh += 10 - 'A';
                    else posCh -= '0';
                    std::vector<std::string> opts;
                    if (posCh & 1)
                    {
                        opts.push_back("Oben");
                    }
                    if (posCh & 2)
                    {
                        opts.push_back("Unten");
                    }
                    if (posCh & 4)
                    {
                        opts.push_back("Rechts");
                    }
                    if (posCh & 8)
                    {
                        opts.push_back("Links");
                    }
                    pos.geheNach(frageOptionen(opts));
                    posCh = brett[7 - std::get<1>(pos.feld)][std::get<0>(pos.feld) + 3];
                    if (islower(posCh))
                    {
                        pos.typ = Position::PosTyp::Raum;
                        pos.raum = Position::charZuRaum(posCh);
                    }
                }
                else
                {
                    switch (pos.raum)
                    {
                    case Raum::Schlaf:
                        cout << "im Schlafzimmer. Optionen:" << endl;
                        switch (frageOptionen({
                                    "Geiheimgang zum Wohnzimmer",
                                    "Durchgang zum Badezimmer",
                                    "Ausgang zu Feld (-2,5)"}))
                        {
                        case 1:
                            pos.raum = Raum::Wohn;
                            break;
                        case 2:
                            pos.raum = Raum::Bade;
                            break;
                        case 3:
                            pos.typ = Position::PosTyp::Feld;
                            pos.feld = std::make_tuple(-2, 5);
                            break;
                        }
                        break;
                    case Raum::Bade:
                        cout << "im Badezimmer. Optionen:" << endl;
                        switch (frageOptionen({
                                        "Durchgang zum Schlafzimmer",
                                        "Ausgang zu Feld (0,6)"}))
                        {
                        case 1:
                            pos.raum = Raum::Schlaf;
                            break;
                        case 2:
                            pos.typ = Position::PosTyp::Feld;
                            pos.feld = std::make_tuple(0, 6);
                            break;
                        }
                        break;
                    case Raum::Arbeits:
                        cout << "im Arbeitszimmer. Du kannst nur durch den Ausgang auf Feld (1,6) gehen.";
                        pos.typ = Position::PosTyp::Feld;
                        pos.feld = std::make_tuple(1, 6);
                        break;
                    case Raum::Küche:
                        cout << "in der Küche. Optionen:" << endl;
                        switch (frageOptionen({
                                    "Durchgang zum Speisezimmer",
                                    "Ausgang zu Feld (5,4)"}))
                        {
                        case 1:
                            pos.raum = Raum::Speise;
                            break;
                        case 2:
                            pos.typ = Position::PosTyp::Feld;
                            pos.feld = std::make_tuple(5, 4);
                            break;
                        }
                        break;
                    case Raum::Speise:
                        cout << "im Speisezimmer. Optionen:" << endl;
                        switch (frageOptionen({
                                    "Durchgang zur Küche",
                                    "Ausgang zu Feld (4,0)"}))
                        {
                        case 1:
                            pos.raum = Raum::Küche;
                            break;
                        case 2:
                            pos.typ = Position::PosTyp::Feld;
                            pos.feld = std::make_tuple(4, 0);
                        }
                        break;
                    case Raum::Wohn:
                        cout << "im Wohnzimmer. Optionen:" << endl;
                        switch (frageOptionen({
                                    "Geheimgang zum Schlafzimmer",
                                    "Ausgang zu Feld (5,-4)"}))
                        {
                        case 1:
                            pos.raum = Raum::Schlaf; break;
                        case 2:
                            pos.typ = Position::PosTyp::Feld;
                            pos.feld = std::make_tuple(5, -4);
                            break;
                        }
                        break;
                    case Raum::Hof:
                        cout << "im Hof. Optionen:" << endl;
                        pos.typ = Position::PosTyp::Feld;
                        switch (frageOptionen({
                                    "Ausgang zu Feld (1,-6)",
                                    "Ausgang zu Feld (2,-6)"}))
                        {
                        case 1:
                            pos.feld = std::make_tuple(1, -6);
                            break;
                        case 2:
                            pos.feld = std::make_tuple(2, -6);
                            break;
                        }
                        break;
                    case Raum::Garage:
                        cout << "in der Garage. Optionen:";
                        switch (frageOptionen({
                                    "Geheimgang zur Küche",
                                    "Ausgang zu Feld (-2,-5)"}))
                        {
                        case 1:
                            pos.raum = Raum::Küche;
                            break;
                        case 2:
                            pos.typ = Position::PosTyp::Feld;
                            pos.feld = std::make_tuple(-2, -5);
                            break;
                        }
                        break;
                    case Raum::Spiele:
                        cout << "im Spieleraum. Du kannst nur durch den Ausgang auf Feld (-2,-1) gehen.";
                        pos.typ = Position::PosTyp::Feld;
                        pos.feld = std::make_tuple(-2, -1);
                        break;
                    case Raum::Mitte:
                        cout << "in der Mitte. Optionen:" << endl;
                        pos.typ = Position::PosTyp::Feld;
                        switch (frageOptionen({
                                    "Ausgang zu Feld (-1,-1)",
                                    "Ausgang zu Feld (2,1)",
                                    "Ausgang zu Feld (4,-1)",
                                    "Ausgang zu Feld (2,-3)"}))
                        {
                        case 1:
                            pos.feld = std::make_tuple(-1, -1);
                            break;
                        case 2:
                            pos.feld = std::make_tuple(2, 1);
                            break;
                        case 3:
                            pos.feld = std::make_tuple(4, -1);
                            break;
                        case 4:
                            pos.feld = std::make_tuple(2, -3);
                            break;
                        }
                        break;
                    }
                }
            } while (pos.typ != Position::PosTyp::Raum && --wurf != 0);
            positionen[geradeDran] = pos;

            if (pos.typ == Position::PosTyp::Raum)
            {
                cout << "Du hast ";
                switch (pos.raum)
                {
                case Raum::Schlaf:
                    cout << "das Schlafzimmer"; break;
                case Raum::Bade:
                    cout << "das Badezimmer"; break;
                case Raum::Arbeits:
                    cout << "das Arbeitszimmer"; break;
                case Raum::Küche:
                    cout << "die Küche"; break;
                case Raum::Speise:
                    cout << "das Speisezimmer"; break;
                case Raum::Wohn:
                    cout << "das Wohnzimmer"; break;
                case Raum::Hof:
                    cout << "den Hof"; break;
                case Raum::Garage:
                    cout << "die Garage"; break;
                case Raum::Spiele:
                    cout << "den Spieleraum"; break;
                case Raum::Mitte:
                    cout << "die Mitte"; break;
                }
                cout << " erreicht!" << endl;
            }
        }

        if (pos.typ != Position::PosTyp::Raum) continue; // hat keinen Raum erreicht


    }
    wurdeTeleportiert[geradeDran - 1] = false;
}
