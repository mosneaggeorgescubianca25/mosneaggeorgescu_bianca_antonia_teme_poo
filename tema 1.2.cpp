#include <iostream>
#include <string>

using namespace std;

class Restaurant {
private:
    const int id;
    string denumire;
    int nrMese;
    float* incasari;

public:
    static int nrRestaurante;

    Restaurant() : id(++nrRestaurante) {
        denumire = "Necunoscut";
        nrMese = 0;
        incasari = nullptr;
    }

    Restaurant(int id, string denumire, int nrMese,
        const float* incasari)
        : id(id) {

        this->denumire = denumire;
        this->nrMese = nrMese;

        if (nrMese > 0 && incasari != nullptr) {
            this->incasari = new float[nrMese];

            for (int i = 0; i < nrMese; i++) {
                this->incasari[i] = incasari[i];
            }
        }
        else {
            this->incasari = nullptr;
        }

        nrRestaurante++;
    }

    void afisareRestaurant() const {
        cout << "\nID: " << id;
        cout << "\nDenumire: " << denumire;
        cout << "\nNumar mese: " << nrMese;

        if (nrMese > 0 && incasari != nullptr) {
            cout << "\nIncasari per masa: ";

            for (int i = 0; i < nrMese; i++) {
                cout << incasari[i];

                if (i < nrMese - 1) {
                    cout << ", ";
                }
                else {
                    cout << ".";
                }
            }
        }
        cout << '\n';
    }

    Restaurant(const Restaurant& r)
        : id(r.id),
        denumire(r.denumire),
        nrMese(r.nrMese) {

        if (nrMese > 0 && r.incasari != nullptr) {
            incasari = new float[nrMese];

            for (int i = 0; i < nrMese; i++) {
                incasari[i] = r.incasari[i];
            }
        }
        else {
            incasari = nullptr;
        }

        nrRestaurante++;
    }

    Restaurant& operator=(const Restaurant&) = delete;

    ~Restaurant() {
        delete[] incasari;
    }
};

int Restaurant::nrRestaurante = 0;

int main() {
    Restaurant r1;
    r1.afisareRestaurant();

    float* valori = new float[4] {120.5f, 95.0f, 180.75f, 140.0f};

    Restaurant* r2 = new Restaurant(15, "La Aroma", 4, valori);
    r2->afisareRestaurant();

    Restaurant r3(*r2);
    r3.afisareRestaurant();

    delete[] valori;
    valori = nullptr;

    delete r2;
    r2 = nullptr;

    cout << "\nNumar restaurante construite: "
        << Restaurant::nrRestaurante << '\n';

    return 0;
}
