# Validacija unosa iz tekstualne datoteke (C++ zadatak)

## Opis

Konzolna aplikacija napisana u C++ jeziku koja provjerava ispravnost unosa iz tekstualne datoteke prema zadanim pravilima. Kao build alat koristi se CMake. Čitanje i validacija se odvijaju u zasebnom threadu, dok glavni thread ispisuje ispravne i neispravne unose.

## Tehnički detalji

- Jezik: C++
- Build alat: CMake
- Struktura projekta:
  - `src/main.cpp` – glavni izvorni kod
  - `CMakeLists.txt` – build konfiguracija
  - `primjer.txt` – datoteka s unosima
  - `README.md` 

## Pravila validacije

- Svaki red u tekstualnoj datoteci mora sadržavati:
  - Datum u formatu `DD.MM.YYYY`
  - Ime i prezime
- Dozvoljeni su formati:
  - `Ime Ime Prezime Prezime`
  - `Ime-Ime Prezime-Prezime`
- Imena i prezimena moraju počinjati velikim slovom
- Nedozvoljeni su brojevi u imenima, kao i specijalni znakovi poput `%`, `#`, `@`, `&`, itd.
- Datum mora biti kalendarski ispravan (npr. 31.02. je nevažeći)

## Upute za korištenje

1. **Buildanje projekta**

Otvorite terminal u root direktoriju projekta i izvršite:

```bash
mkdir build
cd build
cmake ..
make
Nakon buildanja - ./ZenitelZadatak ../primjer.txt
