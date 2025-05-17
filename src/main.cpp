#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <thread>
#include <mutex>

// Omogucuje se siguran pristup dijeljenim podacima izmedu glavne dretve i dretve koja obraduje datoteku
std::mutex mtx;

//Funkcija provjerava ako je datum kalendarski ispravan
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

// Funkcija koja obraduje datoteku i puni vektore ispravnih i neispravnih linija
void obradiDatoteku(const std:: string& putanja, 
    std::vector<std::pair<int, std::string>>& ispravneLinije,
    std::vector<std::pair<int, std::string>>& neispravneLinije){
    // Otvaramo datoteku za čitanje
    std::ifstream datoteka(putanja);
    
    // Ako nije moguce otvoriti, ispisi gresku i prekini funkciju
    if(!datoteka.is_open()){
        std::cerr << "❌ Greška pri otvaranju datoteke u threadu: " << putanja << std::endl;
        return;
    }

    std::string linija;
    int brojLinije = 1; // Brojac koji pamti redni broj linije u datoteci
    // Regex se koristi za validaciju unosa tj. da podrzava zadani unos
    std::regex uzorak(R"(^\d{2}\.\d{2}\.\d{4}\s+[A-ZŽĆČŠĐ][-a-zA-ZžćčšđŽĆČŠĐ]+(\s+[A-ZŽĆČŠĐ][-a-zA-ZžćčšđŽĆČŠĐ]+)+$)");

    // While čita datoteku liniju po liniju i povećava redni broj linije
    while (std::getline(datoteka, linija)){
        if (std::regex_match(linija, uzorak)) {
            int dan = std::stoi(linija.substr(0,2));
            int mjesec = std::stoi(linija.substr(3,2));
            int godina = std::stoi(linija.substr(6,4));

            if (ispravanDatum(dan, mjesec, godina)){
                std::lock_guard<std::mutex> lock(mtx);
                ispravneLinije.push_back({brojLinije, linija});
            } else {
                std::lock_guard<std::mutex> lock(mtx);
                neispravneLinije.push_back({brojLinije, linija});
            }
        } else {
            std::lock_guard<std::mutex> lock(mtx);
            neispravneLinije.push_back({brojLinije, linija});
        }
        brojLinije++;
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
    
    // Vektori za spremanje validiranih linija s njihovim rednim brojevima
    std::vector<std::pair<int, std::string>> ispravneLinije;
    std::vector<std::pair<int, std::string>> neispravneLinije;

    // Pokretanje zasebne dretve koja obrađuje datoteku
    std::thread t(obradiDatoteku, putanja,
                std::ref(ispravneLinije),
                std::ref(neispravneLinije));
    
    // ceka da dretva završi prije nego nastavimo
    t.join();

    // Ispis ispravnih linija s rednim brojem iz datoteke
    std::cout << "\n✅ Ispis ispravnih unosa:\n";
    for (const auto& linija : ispravneLinije){
        std::cout << " [" << linija.first << "] " << linija.second << std::endl;
    }

     // Ispis neispravnih linija s rednim brojem iz datoteke
    std::cout << "\n❌ Ispis neispravnih unosa:\n";
    for (const auto& linija: neispravneLinije){
        std::cout<< " [" << linija.first << "] " << linija.second << std::endl;
    }

    return 0; // Zavrsetak programa
}