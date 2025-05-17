#include <iostream>
#include <fstream>
#include <regex>

bool ispravanDatum(int dan, int mjesec, int godina)
{
    if (mjesec < 1 || mjesec > 12) return false;
    if (dan < 1) return false;

    int daniUMjesecu[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mjesec == 2 && ((godina % 4 == 0 && godina % 100 !=0) || godina % 400 == 0 )) {
        daniUMjesecu[1] = 29;
    }

    return dan <= daniUMjesecu[mjesec - 1];

}

int main(int argc, char *argv[])
{
    // Ovdje provjeravam ukoliko je korisnik unio točno jedan argument
    if (argc != 2)
    {
        std::cerr << " Upotreba: " << argv[0] << " <putanja_do_datoteke>" << std::endl;
        return 1;
    }
    // Dohvacanje putanje iz komandne linije
    std::string putanja = argv[1];

    // Otvaranje datoteke
    std::ifstream datoteka(putanja);

    // Uvjet koji provjerava da li je datoteka uspješno otvorena
    if (!datoteka.is_open())
    {
        std::cerr << "Greska ne mogu otvoriti datoteku!" << putanja << std::endl;
        return 1;
    }

    std::cout << "Datoteka uspješno otvorena!" << putanja << std::endl;

    std::string linija;
    int broj_linije = 1;
    std::regex uzorak(R"(^\d{2}\.\d{2}\.\d{4}\s+[A-ZŽĆČŠĐ][a-zA-ZžćčšđŽĆČŠĐ-]+(\s+[A-ZŽĆČŠĐ][a-zA-ZžćčšđŽĆČŠĐ-]+)+$)");

    while (std::getline(datoteka, linija)) {
        if (std::regex_match(linija, uzorak)) {

            int dan = std::stoi(linija.substr(0,2));
            int mjesec = std::stoi(linija.substr(3,2));
            int godina = std::stoi(linija.substr(6,4));

            if(ispravanDatum(dan, mjesec, godina)){
                std::cout << " [" << broj_linije << "] ✅ Ispravno: " << linija << std::endl; 
            } else {
                std::cout << "[" << broj_linije << "] ❌ Neispravan datum: " << linija << std::endl;
            }
        } else {
            std::cout << "[" << broj_linije << "] ❌ Neispravno: " << linija << std::endl;
        }
        broj_linije++;
    }
    
    datoteka.close();

    return 0;
}