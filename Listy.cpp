#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// ----------- TABLICA DYNAMICZNA -----------

class ProstaTablica {
    int* dane;
    int ileJest;
    int rozmiar;

    void powiekszTablice() {
        rozmiar *= 2;
        int* nowa = new int[rozmiar];
        for (int i = 0; i < ileJest; i++) {
            nowa[i] = dane[i];
        }
        delete[] dane;
        dane = nowa;
    }

public:
    ProstaTablica(int poczatkowy = 4) {
        rozmiar = poczatkowy;
        ileJest = 0;
        dane = new int[rozmiar];
    }

    ~ProstaTablica() {
        delete[] dane;
    }

    void dodajNaKoniec(int liczba) {
        if (ileJest == rozmiar) powiekszTablice();
        dane[ileJest++] = liczba;
    }

    void dodajNaPoczatek(int liczba) {
        if (ileJest == rozmiar) powiekszTablice();
        for (int i = ileJest; i > 0; i--) {
            dane[i] = dane[i - 1];
        }
        dane[0] = liczba;
        ileJest++;
    }

    void dodajNaMiejsce(int liczba, int miejsce) {
        if (miejsce < 0 || miejsce > ileJest) return;
        if (ileJest == rozmiar) powiekszTablice();
        for (int i = ileJest; i > miejsce; i--) {
            dane[i] = dane[i - 1];
        }
        dane[miejsce] = liczba;
        ileJest++;
    }

    void usunZPoczatku() {
        for (int i = 0; i < ileJest - 1; i++) {
            dane[i] = dane[i + 1];
        }
        ileJest--;
    }

    void usunZKonca() {
        if (ileJest > 0) ileJest--;
    }

    void usunZ(int miejsce) {
        if (miejsce < 0 || miejsce >= ileJest) return;
        for (int i = miejsce; i < ileJest - 1; i++) {
            dane[i] = dane[i + 1];
        }
        ileJest--;
    }

    int znajdz(int liczba) {
        for (int i = 0; i < ileJest; i++) {
            if (dane[i] == liczba) return i;
        }
        return -1;
    }
};

// ----------- LISTA WIĄZANA -----------

struct ElementListy {
    int liczba;
    ElementListy* nastepny;
};

class ProstaLista {
    ElementListy* poczatek;

public:
    ProstaLista() {
        poczatek = nullptr;
    }

    ~ProstaLista() {
        while (poczatek) {
            ElementListy* tmp = poczatek;
            poczatek = poczatek->nastepny;
            delete tmp;
        }
    }

    void dodajNaKoniec(int liczba) {
        ElementListy* nowy = new ElementListy{ liczba, nullptr };
        if (!poczatek) {
            poczatek = nowy;
            return;
        }
        ElementListy* aktualny = poczatek;
        while (aktualny->nastepny) {
            aktualny = aktualny->nastepny;
        }
        aktualny->nastepny = nowy;
    }

    void dodajNaPoczatek(int liczba) {
        ElementListy* nowy = new ElementListy{ liczba, poczatek };
        poczatek = nowy;
    }

    void dodajNaMiejsce(int liczba, int miejsce) {
        if (miejsce == 0) {
            dodajNaPoczatek(liczba);
            return;
        }
        ElementListy* aktualny = poczatek;
        for (int i = 0; i < miejsce - 1 && aktualny; i++) {
            aktualny = aktualny->nastepny;
        }
        if (!aktualny) return;
        ElementListy* nowy = new ElementListy{ liczba, aktualny->nastepny };
        aktualny->nastepny = nowy;
    }

    void usunZPoczatku() {
        if (!poczatek) return;
        ElementListy* tmp = poczatek;
        poczatek = poczatek->nastepny;
        delete tmp;
    }

    void usunZKonca() {
        if (!poczatek) return;
        if (!poczatek->nastepny) {
            delete poczatek;
            poczatek = nullptr;
            return;
        }
        ElementListy* aktualny = poczatek;
        while (aktualny->nastepny->nastepny) {
            aktualny = aktualny->nastepny;
        }
        delete aktualny->nastepny;
        aktualny->nastepny = nullptr;
    }

    void usunZ(int miejsce) {
        if (miejsce == 0) {
            usunZPoczatku();
            return;
        }
        ElementListy* aktualny = poczatek;
        for (int i = 0; i < miejsce - 1 && aktualny; i++) {
            aktualny = aktualny->nastepny;
        }
        if (!aktualny || !aktualny->nastepny) return;
        ElementListy* doUsuniecia = aktualny->nastepny;
        aktualny->nastepny = doUsuniecia->nastepny;
        delete doUsuniecia;
    }

    int znajdz(int liczba) {
        ElementListy* aktualny = poczatek;
        int index = 0;
        while (aktualny) {
            if (aktualny->liczba == liczba) return index;
            aktualny = aktualny->nastepny;
            index++;
        }
        return -1;
    }
};

// ----------- PORÓWNANIE CZASU -----------

int main() {
    const int ILE = 10000;
    ProstaTablica tablica;
    ProstaLista lista;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < ILE; i++) tablica.dodajNaKoniec(i);
    auto stop = high_resolution_clock::now();
    cout << "Tablica - dodawanie na koniec: "
        << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int i = 0; i < ILE; i++) lista.dodajNaKoniec(i);
    stop = high_resolution_clock::now();
    cout << "Lista   - dodawanie na koniec: "
        << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    start = high_resolution_clock::now();
    tablica.znajdz(ILE / 2);
    stop = high_resolution_clock::now();
    cout << "Tablica - wyszukiwanie: "
        << duration_cast<microseconds>(stop - start).count() << " µs\n";

    start = high_resolution_clock::now();
    lista.znajdz(ILE / 2);
    stop = high_resolution_clock::now();
    cout << "Lista   - wyszukiwanie: "
        << duration_cast<microseconds>(stop - start).count() << " µs\n";

    return 0;
}
