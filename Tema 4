#include<iostream>
#include<string>

using namespace std;

enum TipRestaurant { FAST_FOOD = 1, TRADITIONAL = 2 };

class Restaurant {
private:
    const int id;
    string denumire;
    TipRestaurant tip;
    int nrMese;
    float* vectorIncasari;

public:
    static int nrRestaurante;

    Restaurant() : id(++nrRestaurante) {
        this->denumire = "Necunoscut";
        this->nrMese = 0;
        this->tip = FAST_FOOD;
        this->vectorIncasari = nullptr;
    }

    Restaurant(int id, string denumire, TipRestaurant tip,
        int nrMese, float* vectorIncasari) : id(id) {

        this->denumire = denumire;
        this->tip = tip;
        this->nrMese = nrMese;

        this->vectorIncasari = new float[nrMese];

        for (int i = 0; i < this->nrMese; i++) {
            this->vectorIncasari[i] = vectorIncasari[i];
        }

        nrRestaurante++;
    }

    Restaurant(const Restaurant& r) : id(++nrRestaurante) {
        this->denumire = r.denumire;
        this->nrMese = r.nrMese;
        this->tip = r.tip;

        if (r.vectorIncasari != nullptr) {
            this->vectorIncasari = new float[r.nrMese];

            for (int i = 0; i < r.nrMese; i++) {
                this->vectorIncasari[i] = r.vectorIncasari[i];
            }
        }
        else {
            this->vectorIncasari = nullptr;
        }
    }

    Restaurant& operator=(const Restaurant& r) {
        if (this != &r) {
            this->denumire = r.denumire;
            this->nrMese = r.nrMese;
            this->tip = r.tip;

            if (this->vectorIncasari != nullptr) {
                delete[] this->vectorIncasari;
                this->vectorIncasari = nullptr;
            }

            if (r.vectorIncasari != nullptr) {
                this->vectorIncasari = new float[r.nrMese];

                for (int i = 0; i < r.nrMese; i++) {
                    this->vectorIncasari[i] = r.vectorIncasari[i];
                }
            }
        }

        return *this;
    }

    void afisareRestaurant() {
        cout << endl << "Id: " << this->id;
        cout << endl << "Denumire: " << this->denumire;
        cout << endl << "Nr mese: " << this->nrMese;

        cout << endl << "Tip restaurant: ";

        if (this->tip == FAST_FOOD) {
            cout << "FAST FOOD";
        }
        else {
            cout << "TRADITIONAL";
        }

        if (this->nrMese > 0) {
            cout << endl << "Incasari per masa: ";

            for (int i = 0; i < this->nrMese - 1; i++) {
                cout << this->vectorIncasari[i] << ", ";
            }

            cout << this->vectorIncasari[this->nrMese - 1] << ".";
        }
    }

    int getNrMese() {
        return this->nrMese;
    }

    void setNrMese(int nrMeseNou) {
        if (nrMeseNou >= 0) {
            this->nrMese = nrMeseNou;
        }
        else {
            throw "Valoare negativa";
        }
    }

    float* getVectorIncasari() {
        if (this->vectorIncasari == nullptr) {
            return nullptr;
        }

        float* vectorNou = new float[this->nrMese];

        for (int i = 0; i < this->nrMese; i++) {
            vectorNou[i] = this->vectorIncasari[i];
        }

        return vectorNou;
    }

    void setVectorIncasari(float* vector, int nr) {
        if (nr < 0) {
            throw "Numar invalid";
        }

        if (nr > 0 && vector == nullptr) {
            throw "Vector invalid";
        }

        float* vectorNou = nullptr;

        if (nr > 0) {
            vectorNou = new float[nr];

            for (int i = 0; i < nr; i++) {
                vectorNou[i] = vector[i];
            }
        }

        delete[] this->vectorIncasari;

        this->vectorIncasari = vectorNou;
        this->nrMese = nr;
    }

    ~Restaurant() {
        if (this->vectorIncasari != nullptr) {
            delete[] this->vectorIncasari;
        }
    }

    bool operator<(const Restaurant& r) {
        return this->nrMese < r.nrMese;
    }
};

int Restaurant::nrRestaurante = 0;

int main() {

    Restaurant rMcDonalds;
    rMcDonalds.afisareRestaurant();

    float* vectorIncasari = new float[4] {120, 85, 150, 95};

    Restaurant* pRestaurant = new Restaurant(
        10, "La Bunica", TRADITIONAL, 4, vectorIncasari
    );

    delete[] vectorIncasari;

    pRestaurant->afisareRestaurant();

    Restaurant rKFC = *pRestaurant;
    rKFC.afisareRestaurant();

    rMcDonalds = *pRestaurant;
    rMcDonalds.afisareRestaurant();

    cout << endl << endl << "Am construit "
        << Restaurant::nrRestaurante << " restaurante!";

    if (rMcDonalds < rKFC) {
        cout << endl << "Restaurantul McDonalds are mai putine mese!";
    }
    else {
        cout << endl << "Restaurantul KFC are mai putine mese!";
    }

    delete pRestaurant;

    return 0;
}
