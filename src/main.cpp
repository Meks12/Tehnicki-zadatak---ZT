#include <iostream>
#include <fstream>
#include <regex>

int main(int argc, char* argv[]) {
    // Ovdje provjeravam ukoliko je korisnik unio točno jedan argument
    if (argc !=2)    {
        std::cerr <<" Upotreba: " << argv[0] << " <putanja_do_datoteke>" << std::endl;
        return 1;
    }
    // Dohvacanje putanje iz komandne linije 
    std::string putanja = argv[1];

    // Otvaranje datoteke
    std::ifstream datoteka(putanja);

    // Uvjet koji provjerava da li je datoteka uspješno otvorena
    if (!datoteka.is_open()){
        std::cerr << "Greska ne mogu otvoriti datoteku!" << putanja << std::endl;
        return 1;
    }

    std::cout << "Datoteka uspješno otvorena!" << putanja << std::endl;

    std::string linija;
    int broj_linije = 1;
    std::regex uzorak(R"(^\d{2}\.\d{2}\.\d{4}\s+[A-ZŽĆČŠĐ][a-zA-ZžćčšđŽĆČŠĐ-]+(\s+[A-ZŽĆČŠĐ][a-zA-ZžćčšđŽĆČŠĐ-]+)+$)");

    while (std::getline(datoteka, linija)) {
        if (std::regex_match(linija, uzorak)) {
            std::cout << "[" << broj_linije << "] ✅ Ispravno: " << linija << std::endl;
    } else {
        std::cout << "[" << broj_linije << "] ❌ Neispravno: " << linija << std::endl;
    }
    broj_linije++;
    }


    datoteka.close();

    return 0;

}