#include <iostream>
#include <fstream>

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

    std:: string linija;
    int broj_linije = 1;

    while (std::getline(datoteka, linija)){
        std::cout<< " [" << broj_linije << "] " << linija << std::endl;
        broj_linije++;
    }
    

    datoteka.close();

    return 0;

}