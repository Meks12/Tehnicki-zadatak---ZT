Specifikacija:
Zadatak je potrebno riješiti koristeći C++ sa željenim dodatnim open source bibliotekama, ili koristeći Qt framework.
Kao build alat je potrebno koristiti CMake.
Rješenje je potrebno uploadati na git server po vlastitom odabiru (github, gitlab, nešto treće...) kao dobro strukturirani projekt.
Konzolna aplikacija koje će verificirati unose iz tekstualne datoteke prema zadanim pravilima i ispisivati sve unose koji zadovolje zadani format.
Putanja do datoteke mora biti ulazni parametar za aplikaciju.
Tekstualna datoteka će u svakom redu imati unos koji se sastoji od datuma, imena i prezimena.
Ispravni format za unos je „DD.MM.YYYY Ime Prezime“
Dupla imena i prezimena se smatraju valjanim unosom, te su za njih podržana ova dva formata:
DD.MM.YYYY Ime Ime Prezime Prezime
DD.MM.YYYY Ime-Ime Prezime-Prezime
Potrebno je pripremiti tekstualnu datoteku sa barem 10 unosa.
Datoteka mora imati i nekoliko unosa koji ne zadovoljavaju zadani format, npr. datum u krivom obliku, ime koje sadrži specijalne znakove (%,#,& itd.).
Provjeru unosa je potrebno implementirati koristeći regularne ekspresije (regex).
Čitanje iz datoteke i provjera unosa se mora obaviti na zasebnom threadu. Nakon što je cijela datoteka procesirana glavni thread mora ispisati ispravne unose.
Bonus bodovi za unit testove.
