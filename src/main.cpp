#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <thread>
#include <mutex>

std::mutex mtx;

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

void obradiDatoteku(const std:: string& putanja, 
    std::vector<std::string>& ispravneLinije,
    std::vector<std::string>& neispravneLinije){
    std::ifstream datoteka(putanja);

    if(!datoteka.is_open()){
        std::cerr << "❌ Greška pri otvaranju datoteke u threadu: " << putanja << std::endl;
        return;
    }

    std::string linija;
    std::regex uzorak(R"(^\d{2}\.\d{2}\.\d{4}\s+[A-ZŽĆČŠĐ][-a-zA-ZžćčšđŽĆČŠĐ]+(\s+[A-ZŽĆČŠĐ][-a-zA-ZžćčšđŽĆČŠĐ]+)+$)");

    while (std::getline(datoteka, linija)){
        if (std::regex_match(linija, uzorak)) {
            int dan = std::stoi(linija.substr(0,2));
            int mjesec = std::stoi(linija.substr(3,2));
            int godina = std::stoi(linija.substr(6,4));

            if (ispravanDatum(dan, mjesec, godina)){
                std::lock_guard<std::mutex> lock(mtx);
                ispravneLinije.push_back(linija);
            } else {
                std::lock_guard<std::mutex> lock(mtx);
                neispravneLinije.push_back(linija);
            }
        } else {
            std::lock_guard<std::mutex> lock(mtx);
            neispravneLinije.push_back(linija);
        }
    }
    
    datoteka.close();
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

    std::vector<std::string> ispravneLinije;
    std::vector<std::string> neispravneLinije;

    std::thread t(obradiDatoteku, putanja,
                std::ref(ispravneLinije),
                std::ref(neispravneLinije));

    t.join();

    std::cout << "\n✅ Ispis ispravnih unosa:\n";
    int broj = 1;
    for (const auto& linija : ispravneLinije){
        std::cout << " [" << broj << "] " << linija << std::endl;
        broj++;
    }

    std::cout << "\n❌ Ispis neispravnih unosa:\n";
    int broj2 = 1;
    for (const auto& linija: neispravneLinije){
        std::cout<< " [" << broj2 << "] " << linija << std::endl;
        broj2++;
    }

    return 0;
}