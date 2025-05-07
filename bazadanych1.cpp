#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


struct Point {
    double x, y;
};

void wczytajBaze(std::vector<Point>& baza, const std::string& nazwaPliku) {
    std::ifstream plik(nazwaPliku);

    if (!plik.is_open()) {
        std::cerr << "Nie można otworzyć pliku do odczytu." << std::endl;
        return;
    }

    baza.clear();

    std::string linia;
    while (std::getline(plik, linia)) {
        Point punkt;
        std::istringstream ss(linia);

        ss >> punkt.x;
        ss.ignore(); 
        ss >> punkt.y;

        baza.push_back(punkt);
    }

    plik.close();
}

void zapiszBaze(const std::vector<Point>& baza, const std::string& nazwaPliku) {
    std::ofstream plik(nazwaPliku);

    if (!plik.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
        return;
    }

    for (const Point& punkt : baza) {
        plik << punkt.x << ',' << punkt.y << std::endl;
    }

    plik.close();
}

void dodajElement(std::vector<Point>& baza) {
    Point nowyPunkt;

    std::cout << "Podaj wspolrzedna x: ";
    std::cin >> nowyPunkt.x;

    std::cout << "Podaj wspolrzedna y: ";
    std::cin >> nowyPunkt.y;

    baza.push_back(nowyPunkt);
}

void wyswietlBaze(const std::vector<Point>& baza) {
    for (const Point& punkt : baza) {
        std::cout << "X: " << punkt.x << ", Y: " << punkt.y << std::endl;
    }
}

int main() {
    std::vector<Point> baza;
    std::string nazwaPliku = "baza_point.txt";

    int wybor;

    do {
        std::cout << "\nMenu:\n1. Wczytaj baze z pliku\n2. Zapisz baze do pliku\n3. Dodaj nowy element\n4. Wyswietl baze\n0. Zakoncz\nWybierz opcje: ";
        std::cin >> wybor;

        switch (wybor) {
        case 1:
            wczytajBaze(baza, nazwaPliku);
            break;
        case 2:
            zapiszBaze(baza, nazwaPliku);
            break;
        case 3:
            dodajElement(baza);
            break;
        case 4:
            wyswietlBaze(baza);
            break;
        case 0:
            break;
        default:
            std::cout << "Nieprawidlowy wybor. Sprobuj ponownie." << std::endl;
        }

    } while (wybor != 0);

    return 0;
}

