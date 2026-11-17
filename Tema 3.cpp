#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

enum TipLibrarie {
    INDEPENDENTA = 1,
    RETEA = 2
};

class Librarie {
private:
    const int id;
    string denumire;
    TipLibrarie tip;
    int nrRafturi;
    int* vectorCarti;

public:
    static int nrLibrarii;

    Librarie() : id(++nrLibrarii) {
        denumire = "Librarie implicita";
        tip = INDEPENDENTA;
        nrRafturi = 0;
        vectorCarti = nullptr;
    }

    Librarie(string denumire, TipLibrarie tip,
        int nrRafturi, const int* vectorCarti)
        : id(++nrLibrarii) {

        if (nrRafturi < 0 ||
            (nrRafturi > 0 && vectorCarti == nullptr)) {
            --nrLibrarii;
            throw invalid_argument("Date invalide!");
        }

        this->denumire = denumire;
        this->tip = tip;
        this->nrRafturi = nrRafturi;
        this->vectorCarti = nullptr;

        if (nrRafturi > 0) {
            this->vectorCarti = new int[nrRafturi];

            for (int i = 0; i < nrRafturi; i++) {
                this->vectorCarti[i] = vectorCarti[i];
            }
        }
    }

    Librarie(const Librarie& l) : id(++nrLibrarii) {
        denumire = l.denumire;
        tip = l.tip;
        nrRafturi = l.nrRafturi;
        vectorCarti = nullptr;

        if (nrRafturi > 0 && l.vectorCarti != nullptr) {
            vectorCarti = new int[nrRafturi];

            for (int i = 0; i < nrRafturi; i++) {
                vectorCarti[i] = l.vectorCarti[i];
            }
        }
    }

    Librarie& operator=(const Librarie& l) {
        if (this != &l) {
            int* copie = nullptr;

            if (l.nrRafturi > 0 && l.vectorCarti != nullptr) {
                copie = new int[l.nrRafturi];

                for (int i = 0; i < l.nrRafturi; i++) {
                    copie[i] = l.vectorCarti[i];
                }
            }

            delete[] vectorCarti;

            denumire = l.denumire;
            tip = l.tip;
            nrRafturi = l.nrRafturi;
            vectorCarti = copie;
        }

        return *this;
    }

    void afisareLibrarie() const {
        cout << "\n\nID: " << id;
        cout << "\nDenumire: " << denumire;
        cout << "\nNumar rafturi: " << nrRafturi;
        cout << "\nTip: ";

        if (tip == INDEPENDENTA) {
            cout << "INDEPENDENTA";
        }
        else {
            cout << "RETEA";
        }

        if (nrRafturi > 0) {
            cout << "\nCarti pe rafturi: ";

            for (int i = 0; i < nrRafturi; i++) {
                cout << vectorCarti[i];

                if (i < nrRafturi - 1) {
                    cout << ", ";
                }
            }

            cout << ".";
        }
    }

    int getNrRafturi() const {
        return nrRafturi;
    }

    void setNrRafturi(int nrNou) {
        if (nrNou < 0) {
            throw invalid_argument(
                "Numarul de rafturi nu poate fi negativ!"
            );
        }

        int* copie = nullptr;

        if (nrNou > 0) {
            copie = new int[nrNou];

            int limita = (nrNou < nrRafturi)
                ? nrNou : nrRafturi;

            for (int i = 0; i < limita; i++) {
                copie[i] = vectorCarti[i];
            }

            for (int i = limita; i < nrNou; i++) {
                copie[i] = 0;
            }
        }

        delete[] vectorCarti;
        vectorCarti = copie;
        nrRafturi = nrNou;
    }

    int* getVectorCarti() const {
        if (nrRafturi == 0) {
            return nullptr;
        }

        int* copie = new int[nrRafturi];

        for (int i = 0; i < nrRafturi; i++) {
            copie[i] = vectorCarti[i];
        }

        return copie;
    }

    void setVectorCarti(const int* vector, int nr) {
        if (nr < 0 || (nr > 0 && vector == nullptr)) {
            throw invalid_argument("Vector invalid!");
        }

        int* copie = nullptr;

        if (nr > 0) {
            copie = new int[nr];

            for (int i = 0; i < nr; i++) {
                copie[i] = vector[i];
            }
        }

        delete[] vectorCarti;
        vectorCarti = copie;
        nrRafturi = nr;
    }

    bool operator<(const Librarie& l) const {
        return nrRafturi < l.nrRafturi;
    }

    ~Librarie() {
        delete[] vectorCarti;
    }
};

int Librarie::nrLibrarii = 0;

int main() {
 
    Librarie lOrizont;
    lOrizont.afisareLibrarie();

    int carti1[] = { 120, 85, 140, 95 };

    Librarie lLibris(
        "Libris",
        RETEA,
        4,
        carti1
    );

    lLibris.afisareLibrarie();

    Librarie lCarturesti(lLibris);
    lCarturesti.afisareLibrarie();

    lOrizont = lLibris;
    lOrizont.afisareLibrarie();

    cout << "\n\nNumarul de rafturi la Libris: "
        << lLibris.getNrRafturi();

    int cartiNoi[] = { 75, 110, 90 };

    lCarturesti.setVectorCarti(cartiNoi, 3);
    lCarturesti.afisareLibrarie();

    cout << "\n\nComparatie intre librarii:";

    if (lCarturesti < lLibris) {
        cout << "\nCarturesti are mai putine rafturi decat Libris.";
    }
    else if (lLibris < lCarturesti) {
        cout << "\nLibris are mai putine rafturi decat Carturesti.";
    }
    else {
        cout << "\nCele doua librarii au acelasi numar de rafturi.";
    }

    lOrizont.setNrRafturi(2);
    lOrizont.afisareLibrarie();

    cout << "\n\nAu fost construite "
        << Librarie::nrLibrarii
        << " obiecte de tip Librarie.\n";

    int* copieCarti = lLibris.getVectorCarti();
    delete[] copieCarti;

    return 0;
}
