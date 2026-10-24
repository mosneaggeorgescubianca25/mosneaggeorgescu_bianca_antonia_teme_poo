#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Librarie {
private:
    const int id;
    string denumire;
    int nrCarti;
    float* vectorPreturi;

public:
    static int nrLibrarii;

    Librarie() : id(++nrLibrarii) {
        this->denumire = "Necunoscuta";
        this->nrCarti = 0;
        this->vectorPreturi = nullptr;
    }

    Librarie(int id, string denumire, int nrCarti,
        const float* vectorPreturi)
        : id(id) {

        if (nrCarti < 0) {
            throw invalid_argument("Numarul de carti nu poate fi negativ!");
        }

        if (nrCarti > 0 && vectorPreturi == nullptr) {
            throw invalid_argument("Vectorul de preturi nu este valid!");
        }

        this->denumire = denumire;
        this->nrCarti = nrCarti;
        this->vectorPreturi = nullptr;

        if (nrCarti > 0) {
            this->vectorPreturi = new float[nrCarti];

            for (int i = 0; i < nrCarti; i++) {
                this->vectorPreturi[i] = vectorPreturi[i];
            }
        }

        nrLibrarii++;
    }

    Librarie(const Librarie& sursa)
        : id(++nrLibrarii) {

        this->denumire = sursa.denumire;
        this->nrCarti = sursa.nrCarti;
        this->vectorPreturi = nullptr;

        if (nrCarti > 0) {
            this->vectorPreturi = new float[nrCarti];

            for (int i = 0; i < nrCarti; i++) {
                this->vectorPreturi[i] = sursa.vectorPreturi[i];
            }
        }
    }

    void afisareLibrarie() const {
        cout << "\nID: " << this->id;
        cout << "\nDenumire: " << this->denumire;
        cout << "\nNumar carti: " << this->nrCarti;

        if (this->nrCarti > 0) {
            cout << "\nPreturi carti: ";

            for (int i = 0; i < this->nrCarti; i++) {
                cout << this->vectorPreturi[i] << " lei";

                if (i < this->nrCarti - 1) {
                    cout << ", ";
                }
            }
        }

        cout << endl;
    }

    int getNrCarti() const {
        return this->nrCarti;
    }

    void setNrCarti(int nrNou) {
        if (nrNou < 0) {
            throw invalid_argument(
                "Numarul de carti nu poate fi negativ!"
            );
        }

        if (nrNou == this->nrCarti) {
            return;
        }

        float* vectorNou = nullptr;

        if (nrNou > 0) {
            vectorNou = new float[nrNou];

            int limita = (nrNou < this->nrCarti)
                ? nrNou : this->nrCarti;

            for (int i = 0; i < limita; i++) {
                vectorNou[i] = this->vectorPreturi[i];
            }

            for (int i = limita; i < nrNou; i++) {
                vectorNou[i] = 0;
            }
        }

        delete[] this->vectorPreturi;

        this->vectorPreturi = vectorNou;
        this->nrCarti = nrNou;
    }

    float* getVectorPreturi() const {
        float* copie = nullptr;

        if (this->nrCarti > 0) {
            copie = new float[this->nrCarti];

            for (int i = 0; i < this->nrCarti; i++) {
                copie[i] = this->vectorPreturi[i];
            }
        }

        return copie;
    }

    void setVectorPreturi(const float* vector, int nr) {
        if (nr < 0) {
            throw invalid_argument(
                "Numarul de preturi nu poate fi negativ!"
            );
        }

        if (nr > 0 && vector == nullptr) {
            throw invalid_argument(
                "Vectorul de preturi nu este valid!"
            );
        }

        float* copie = nullptr;

        if (nr > 0) {
            copie = new float[nr];

            for (int i = 0; i < nr; i++) {
                copie[i] = vector[i];
            }
        }

        delete[] this->vectorPreturi;

        this->vectorPreturi = copie;
        this->nrCarti = nr;
    }

    ~Librarie() {
        delete[] this->vectorPreturi;
    }

    Librarie& operator=(const Librarie&) = delete;
};

int Librarie::nrLibrarii = 0;

int main() {
    Librarie librarie1;

    cout << "Prima librarie:";
    librarie1.afisareLibrarie();

    try {
        librarie1.setNrCarti(3);
    }
    catch (const exception& e) {
        cout << "\nEroare: " << e.what();
    }

    cout << "\nNumarul nou de carti este: "
        << librarie1.getNrCarti() << endl;

    float preturiNoi[] = { 45.5f, 32.0f, 67.9f };

    librarie1.setVectorPreturi(preturiNoi, 3);

    float* copiePreturi = librarie1.getVectorPreturi();

    cout << "\nNoile preturi sunt: ";

    for (int i = 0; i < librarie1.getNrCarti(); i++) {
        cout << copiePreturi[i] << " lei";

        if (i < librarie1.getNrCarti() - 1) {
            cout << ", ";
        }
    }

    cout << endl;

    delete[] copiePreturi;

    librarie1.afisareLibrarie();

    float preturiInitiale[] = { 25.0f, 39.5f, 52.0f, 18.9f };

    Librarie librarie2(
        10,
        "Carturesti",
        4,
        preturiInitiale
    );

    cout << "\nA doua librarie:";
    librarie2.afisareLibrarie();

    Librarie librarie3(librarie1);

    cout << "\nA treia librarie (copie):";
    librarie3.afisareLibrarie();

    cout << "\nNumarul de librarii construite este: "
        << Librarie::nrLibrarii << endl;

    return 0;
}
