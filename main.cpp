#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <tuple>
#include <sstream>
#include <stdio.h>
#include <algorithm>

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

std::vector<std::string> charPZuStrVec(const char** ar, int len)
{
    std::vector<std::string> res(len);
    for (int i = 0; i < len; ++i)
    {
        res[i] = ar[i];
    }
    return res;
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

class Raum
{
public:
    enum class RaumT
    {
        Schlaf, Bade, Arbeits, Küche, Speise, Wohn, Hof, Garage, Spiele, Mitte
    } typ;
    static const int anzahl = 10;
    static const char* strings[];
    static const char* artikel[];
    static const char* instr[];
    static const char* akkus[];

    static RaumT vonZahl(int z) { return static_cast<RaumT>(z); }

    Raum() : typ(RaumT::Mitte) {};
    Raum(RaumT r) : typ(r) {};
    Raum(int z) : typ(vonZahl(z)) {};
    Raum(char c)
    {
        switch (c)
        {
        case 'a':
            typ = RaumT::Schlaf; break;
        case 'b':
            typ = RaumT::Bade; break;
        case 'c':
            typ = RaumT::Arbeits; break;
        case 'd':
            typ = RaumT::Küche; break;
        case 'e':
            typ = RaumT::Spiele; break;
        case 'f':
            typ = RaumT::Speise; break;
        case 'g':
            typ = RaumT::Mitte; break;
        case 'h':
            typ = RaumT::Garage; break;
        case 'i':
            typ = RaumT::Wohn; break;
        case 'j':
            typ = RaumT::Hof; break;
        }
    }
    int zuZahl() const { return static_cast<int>(typ); }
    std::string zuStr() const { return strings[zuZahl()]; }
    std::string vollStr() const { return std::string(artikel[zuZahl()]) + " " + zuStr(); }
    std::string inStr() const { return std::string(instr[zuZahl()]) + " " + zuStr(); }
    std::string akkusStr() const { return std::string(akkus[zuZahl()]) + " " + zuStr(); }

    bool operator==(const Raum& a) const { return typ == a.typ; }
};

const char* Raum::strings[] = {"Schlafzimmer", "Badezimmer", "Arbeitszimmer",
                               "Küche", "Speisezimmer", "Wohnzimmer", "Hof",
                               "Garage", "Spieleraum", "Mitte"};
const char* Raum::artikel[] = {"das", "das", "das", "die", "das", "das", "der",
                               "die", "der", "die"};
const char* Raum::instr[] = {"im", "im", "im", "in der", "im", "im", "im",
                             "in der", "im", "in der"};
const char* Raum::akkus[] = {"das", "das", "das", "die", "das", "das", "den",
                             "die", "den", "die"};

class Charakter
{
public:
    enum class CharT
    {
        Gloria, Gatow, Porz, Grün, Weiß, Bloom
    } typ;
    static const int anzahl = 6;
    static const char* strings[];

    static CharT vonZahl(int z) { return static_cast<CharT>(z); }

    Charakter() : typ(CharT::Gloria) {};
    Charakter(CharT c) : typ(c) {};
    Charakter(int z) : typ(vonZahl(z)) {};
    int zuZahl() const { return static_cast<int>(typ); }
    std::string zuStr() const { return strings[zuZahl()]; }

    bool operator==(const Charakter& a) const { return typ == a.typ; }
};

const char* Charakter::strings[] = {"Gloria", "Gatow", "Porz", "Grün", "Weiß", "Bloom"};

class Waffe
{
public:
    enum class WafT
    {
        Rohrzange, Dolch, Heizungsrohr, Leuchter, Pistole, Seil
    } typ;
    static const int anzahl = 6;
    static const char* strings[];
    static const char* artikel[];
    static const char* dativ[];

    static WafT vonZahl(int z) { return static_cast<WafT>(z); }

    Waffe() : typ(WafT::Rohrzange) {};
    Waffe(WafT w) : typ(w) {};
    Waffe(int z) : typ(vonZahl(z)) {};
    int zuZahl() const { return static_cast<int>(typ); }
    std::string zuStr() const { return strings[zuZahl()]; }
    std::string mitStr() const { return std::string(dativ[zuZahl()]) + " " + zuStr(); }

    bool operator==(const Waffe& a) const { return typ == a.typ; }
};

const char* Waffe::strings[] = {"Rohrzange", "Dolch", "Heizungsrohr", "Leuchter",
                                "Pistole", "Seil"};
const char* Waffe::artikel[] = {"die", "der", "das", "der", "die", "das"};
const char* Waffe::dativ[] = {"der", "dem", "dem", "dem", "der", "dem"};

struct Karte
{
    enum class KartenTyp
    {
        CharK, RaumK, WaffeK
    } typ;

    union
    {
        Charakter charakter;
        Raum raum;
        Waffe waffe;
    };

    Karte() : typ(KartenTyp::CharK), charakter() {};
    Karte(Raum r) : typ(KartenTyp::RaumK), raum(r) {};
    Karte(Charakter c) : typ(KartenTyp::CharK), charakter(c) {};
    Karte(Waffe w) : typ(KartenTyp::WaffeK), waffe(w) {};
    Karte(const Karte& andere)
    {
        typ = andere.typ;
        if (typ == KartenTyp::CharK)
        {
            charakter = andere.charakter;
        }
        else if (typ == KartenTyp::RaumK)
        {
            raum = andere.raum;
        }
        else
        {
            waffe = andere.waffe;
        }
    }

    bool operator==(const Karte& a) const
    {
        if (typ != a.typ) return false;
        return (typ == KartenTyp::CharK && charakter == a.charakter)
            || (typ == KartenTyp::RaumK && raum == a.raum)
            || (typ == KartenTyp::WaffeK && waffe == a.waffe);
    }
};

std::ostream& operator<<(std::ostream& os, const Karte &karte)
{
    switch (karte.typ)
    {
    case Karte::KartenTyp::CharK:
        os << karte.charakter.zuStr();
        break;
    case Karte::KartenTyp::RaumK:
        os << karte.raum.zuStr();
        break;
    case Karte::KartenTyp::WaffeK:
        os << karte.waffe.zuStr();
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
    } typ;


    union
    {
        Koord feld;
        Raum raum;
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


    Position() : typ(PosTyp::Raum), raum() {};
    Position(Raum r) : typ(PosTyp::Raum), raum(r) {};
    Position(Koord f) : typ(PosTyp::Feld), feld(f) {};
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

bool willNichtBleiben(Raum r)
{
    char c;
    do
    {
        cout << "Du wurdest von einem anderen Spieler in " << r.akkusStr() << " teleportiert! Möchtest du in diesem Raum fragen? [j/n]";
        c = getchar();
    }
    while (c != 'j' && c != 'n');

    return c == 'n'; // will nicht bleiben
}

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
        if (input == "Gloria") spieler.push_back(Charakter::CharT::Gloria);
        else if (input == "Gatow") spieler.push_back(Charakter::CharT::Gatow);
        else if (input == "Porz") spieler.push_back(Charakter::CharT::Porz);
        else if (input == "Grün") spieler.push_back(Charakter::CharT::Grün);
        else if (input == "Weiß") spieler.push_back(Charakter::CharT::Weiß);
        else if (input == "Bloom") spieler.push_back(Charakter::CharT::Bloom);
        else if (input.empty()) break;
        else cout << "Falsche Eingabe!";
    }
    cout << endl;

    int spielerAnzahl = spieler.size();
    std::vector<Position> positionen(Charakter::anzahl);
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
    std::vector<Karte>  akte(3);
    int pos = std::uniform_int_distribution<>(0, 8)(mt);
    akte[0] = karten[pos];
    karten.erase(karten.begin() + pos);
    pos = std::uniform_int_distribution<>(8, 13)(mt);
    akte[1] = karten[pos];
    karten.erase(karten.begin() + pos);
    pos = std::uniform_int_distribution<>(13, 18)(mt);
    akte[2] = karten[pos];
    karten.erase(karten.begin() + pos);

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
    if (! karten.empty())
    {
        cout << "Übrige Karten werden offengelegt:" << endl;
        zeigeKarten(karten);
        cout << endl;
    }

    // Wer darf anfangen?
    std::uniform_int_distribution<> spieler_dist(1, spielerAnzahl);
    geradeDran = spieler_dist(mt);
    cout << "Spieler " << geradeDran << " darf anfangen." << endl;

    for (;; geradeDran = (geradeDran) % spielerAnzahl + 1)
    {
        if (hatVerloren[geradeDran - 1]) continue; // Spieler darf nicht mehr ziehen oder fragen
        cout << "Spieler " << geradeDran << " (" << spieler[geradeDran - 1].zuStr() << ") ist dran." << endl;
        cout << "Deine Karten: ";
        zeigeKarten(spKarten[geradeDran - 1]);
        cout << endl;

        cout << "Bereit zum Würfeln?";
        getchar();
        // Würfelzufall
        std::uniform_int_distribution<> würfel_dist(2, 12);
        int wurf = würfel_dist(mt);
        cout << "Du hast eine " << wurf << " gewürfelt." << endl;

        int spIndex = spieler[geradeDran - 1].zuZahl();
        auto startPos = positionen[spIndex];
        auto pos = startPos;
        if (! wurdeTeleportiert[spIndex] || willNichtBleiben(pos.raum))
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
                    auto neuePos = pos;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    neuePos.geheNach(frageOptionen(opts)); // FIXME: numerierung durcheinander
                    posCh = brett[7 - std::get<1>(neuePos.feld)][std::get<0>(neuePos.feld) + 3];
                    if (islower(posCh))
                    {
                        if (startPos == Position(Raum(posCh)))
                        {
                            cout << "Du kannst nicht in denselben Raum wieder zurückgehen!" << endl;
                            ++wurf; // diesen Zug nochmal versuchen
                        }
                        else
                        {
                            pos = Position(Raum(posCh));
                        }
                    }
                    else
                    {
                        pos = neuePos;
                    }
                }
                else
                {
                    cout << pos.raum.inStr() << "." << endl;
                    switch (pos.raum.typ)
                    {
                    case Raum::RaumT::Schlaf:
                        cout << "Optionen:" << endl;
                        switch (frageOptionen({
                                    "Geiheimgang zum Wohnzimmer",
                                    "Durchgang zum Badezimmer",
                                    "Ausgang zu Feld (-2,5)"}))
                        {
                        case 1:
                            pos = Position(Raum::RaumT::Wohn);
                            break;
                        case 2:
                            pos = Position(Raum::RaumT::Bade);
                            break;
                        case 3:
                            pos = Position(std::make_tuple(-2, 5));
                            break;
                        }
                        break;
                    case Raum::RaumT::Bade:
                        cout << "Optionen:" << endl;
                        switch (frageOptionen({
                                        "Durchgang zum Schlafzimmer",
                                        "Ausgang zu Feld (0,6)"}))
                        {
                        case 1:
                            pos = Position(Raum::RaumT::Schlaf);
                            break;
                        case 2:
                            pos = Position(std::make_tuple(0, 6));
                            break;
                        }
                        break;
                    case Raum::RaumT::Arbeits:
                        cout << "Du kannst nur durch den Ausgang auf Feld (1,6) gehen." << endl;
                        pos = Position(std::make_tuple(1, 6));
                        break;
                    case Raum::RaumT::Küche:
                        cout << "Optionen:" << endl;
                        switch (frageOptionen({
                                    "Durchgang zum Speisezimmer",
                                    "Ausgang zu Feld (5,4)"}))
                        {
                        case 1:
                            pos = Position(Raum::RaumT::Speise);
                            break;
                        case 2:
                            pos = Position(std::make_tuple(5, 4));
                            break;
                        }
                        break;
                    case Raum::RaumT::Speise:
                        cout << "im Speisezimmer. Optionen:" << endl;
                        switch (frageOptionen({
                                    "Durchgang zur Küche",
                                    "Ausgang zu Feld (4,0)"}))
                        {
                        case 1:
                            pos = Position(Raum::RaumT::Küche);
                            break;
                        case 2:
                            pos = Position(std::make_tuple(4, 0));
                        }
                        break;
                    case Raum::RaumT::Wohn:
                        cout << "Optionen:" << endl;
                        switch (frageOptionen({
                                    "Geheimgang zum Schlafzimmer",
                                    "Ausgang zu Feld (5,-4)"}))
                        {
                        case 1:
                            pos = Position(Raum::RaumT::Schlaf);
                            break;
                        case 2:
                            pos = Position(std::make_tuple(5, -4));
                            break;
                        }
                        break;
                    case Raum::RaumT::Hof:
                        cout << "Optionen:" << endl;
                        switch (frageOptionen({
                                    "Ausgang zu Feld (1,-6)",
                                    "Ausgang zu Feld (2,-6)"}))
                        {
                        case 1:
                            pos = Position(std::make_tuple(1, -6));
                            break;
                        case 2:
                            pos = Position(std::make_tuple(2, -6));
                            break;
                        }
                        break;
                    case Raum::RaumT::Garage:
                        cout << "Optionen:";
                        switch (frageOptionen({
                                    "Geheimgang zur Küche",
                                    "Ausgang zu Feld (-2,-5)"}))
                        {
                        case 1:
                            pos = Position(Raum::RaumT::Küche);
                            break;
                        case 2:
                            pos = Position(std::make_tuple(-2, -5));
                            break;
                        }
                        break;
                    case Raum::RaumT::Spiele:
                        cout << "Du kannst nur durch den Ausgang auf Feld (-2,-1) gehen." << endl;
                        pos = Position(std::make_tuple(-2, -1));
                        break;
                    case Raum::RaumT::Mitte:
                        cout << "Optionen:" << endl;
                        switch (frageOptionen({
                                    "Ausgang zu Feld (-1,-1)",
                                    "Ausgang zu Feld (2,1)",
                                    "Ausgang zu Feld (4,-1)",
                                    "Ausgang zu Feld (2,-3)"}))
                        {
                        case 1:
                            pos = Position(std::make_tuple(-1, -1));
                            break;
                        case 2:
                            pos = Position(std::make_tuple(2, 1));
                            break;
                        case 3:
                            pos = Position(std::make_tuple(4, -1));
                            break;
                        case 4:
                            pos = Position(std::make_tuple(2, -3));
                            break;
                        }
                        break;
                    }
                }
            }
            while (pos.typ != Position::PosTyp::Raum && --wurf != 0);
            positionen[spIndex] = pos;

            if (pos.typ == Position::PosTyp::Raum)
            {
                cout << "Du hast " << pos.raum.akkusStr() << " erreicht!" << endl;
            }
        }

        if (pos.typ != Position::PosTyp::Raum) continue; // hat keinen Raum erreicht
        if (pos.raum.typ == Raum::RaumT::Mitte)
        {
            cout << "Gegen wen möchtest du Anklage ergeheben?" << endl;
            int ch = frageOptionen(charPZuStrVec(Charakter::strings, Charakter::anzahl)) - 1;
            cout << "Was war die Tatwaffe?" << endl;
            int waf = frageOptionen(charPZuStrVec(Waffe::strings, Waffe::anzahl)) - 1;
            cout << "Wo geschah die Tat?" << endl;
            int ort = frageOptionen(charPZuStrVec(Raum::strings, Raum::anzahl - 1)) - 1;
            if (akte[0] == Karte(Raum(ort)) && akte[1] == Karte(Charakter(ch))
                && akte[1] == Karte(Waffe(waf)))
            {
                cout << "Glückwunsch! Du hast gewonnen! :-)" << endl;
                break;
            }
            else
            {
                cout << "Das war leider falsch :-( Die Akte ist" << endl;
                zeigeKarten(akte);
                cout << endl;
                hatVerloren[geradeDran - 1] = true;
                if (std::all_of(std::begin(hatVerloren), std::end(hatVerloren), [](bool i) { return i; }))
                {
                    cout << "Alle haben verloren..." << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Nach welchem Charakter möchtest du fragen?" << endl;
            int ch = frageOptionen(charPZuStrVec(Charakter::strings, Charakter::anzahl)) - 1;
            cout << "Nach welcher Waffe möchtest du fragen?" << endl;
            int waf = frageOptionen(charPZuStrVec(Waffe::strings, Waffe::anzahl)) - 1;
            cout << "Spieler " << geradeDran << " fragt: War es " << Charakter::strings[ch]
                << " mit " << Waffe(waf).mitStr() << " " << pos.raum.inStr() << "?" << endl;

            positionen[ch] = pos;
            wurdeTeleportiert[ch] = true;

            for (int i = geradeDran % spielerAnzahl;; i = (i + 1) % spielerAnzahl)
            {
                std::vector<std::string> kandidaten;
                cout << "Spieler " << i + 1 << " (" << spieler[i].zuStr() << ") ist gefragt." << endl;
                if (std::find(spKarten[i].begin(), spKarten[i].end(), Karte(Waffe(waf))) != spKarten[i].end())
                {
                    kandidaten.push_back(Waffe(waf).zuStr());
                }
                if (std::find(spKarten[i].begin(), spKarten[i].end(), Karte(Charakter(ch))) != spKarten[i].end())
                {
                    kandidaten.push_back(Charakter(ch).zuStr());
                }
                if (std::find(spKarten[i].begin(), spKarten[i].end(), Karte(pos.raum)) != spKarten[i].end())
                {
                    kandidaten.push_back(pos.raum.zuStr());
                }

                if (kandidaten.empty())
                {
                    cout << "Spieler " << i + 1 << " weiß nichts." << endl;
                    if (i == (geradeDran - 1) % spielerAnzahl)
                    {
                        cout << "Keiner wusste was!" << endl;
                        break;
                    }
                }
                else
                {
                    cout << "Spieler " << i + 1 << " weiß was. Welche Karte möchte er zeigen?" << endl;
                    int wahl = frageOptionen(kandidaten);
                    cout << "Spieler " << i + 1 << " zeigt Spieler " << geradeDran << " die Karte \"" << kandidaten[wahl - 1] << "\"." << endl;
                    break;
                }
            }
        }
        cout << endl;
        wurdeTeleportiert[spIndex] = false;
    }
}
