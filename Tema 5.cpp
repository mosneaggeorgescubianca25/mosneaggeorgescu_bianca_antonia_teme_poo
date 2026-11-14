#include<iostream>
#include<string>

using namespace std;

enum Tip { MAGAZIN = 1, CHIOSC = 2 };

class Florarie {
private:
	const int id;
	float taxaLunara;
	string nume;
	Tip tip;
	int nrBuchete;
	float* vectorPreturi;
public:
	static int nrFlorarii;

	Florarie() :id(++nrFlorarii) {
		this->nume = "Anonim";
		this->taxaLunara = 0;
		this->tip = CHIOSC;
		this->nrBuchete = 0;
		this->vectorPreturi = nullptr;
	}

	Florarie(int id, float taxaLunara, string nume, Tip tip, int nrBuchete, float* vectorPreturi)
		:id(id) {
		this->nume = nume;
		this->taxaLunara = taxaLunara;
		this->tip = tip;
		this->nrBuchete = nrBuchete;
		this->vectorPreturi = new float[nrBuchete];
		for (int i = 0; i < this->nrBuchete; i++) {
			this->vectorPreturi[i] = vectorPreturi[i];
		}
		nrFlorarii++;
	}

	Florarie(const Florarie& f) :id(++nrFlorarii) {
		this->nume = f.nume;
		this->taxaLunara = f.taxaLunara;
		this->tip = f.tip;
		this->nrBuchete = f.nrBuchete;

		if (f.vectorPreturi != nullptr) {
			this->vectorPreturi = new float[f.nrBuchete];
			for (int i = 0; i < f.nrBuchete; i++) {
				this->vectorPreturi[i] = f.vectorPreturi[i];
			}
		}
		else {
			this->vectorPreturi = nullptr;
		}
	}

	Florarie& operator=(const Florarie& f) {
		if (this == &f) {
			return *this;
		}
		this->nume = f.nume;
		this->taxaLunara = f.taxaLunara;
		this->tip = f.tip;
		this->nrBuchete = f.nrBuchete;

		if (this->vectorPreturi != nullptr) {
			delete[] this->vectorPreturi;
			this->vectorPreturi = nullptr;
		}

		if (f.vectorPreturi != nullptr) {
			this->vectorPreturi = new float[f.nrBuchete];
			for (int i = 0; i < f.nrBuchete; i++) {
				this->vectorPreturi[i] = f.vectorPreturi[i];
			}
		}
		return *this;
	}

	void afisareFlorarie() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Nume: " << this->nume;
		cout << endl << "Taxa lunara: " << this->taxaLunara << " lei";
		cout << endl << "Nr buchete: " << this->nrBuchete;
		cout << endl << "Tip: ";
		if (this->tip == MAGAZIN) {
			cout << "MAGAZIN";
		}
		else {
			cout << "CHIOSC";
		}

		if (this->nrBuchete > 0 && this->vectorPreturi != nullptr) {
			cout << endl << "Preturi buchete: ";
			for (int i = 0; i < this->nrBuchete - 1; i++) {
				cout << this->vectorPreturi[i] << ", ";
			}
			cout << this->vectorPreturi[this->nrBuchete - 1] << ".";
		}
	}

	int getNrBuchete() {
		return this->nrBuchete;
	}

	void setNrBuchete(int nrBucheteNou) {
		if (nrBucheteNou >= 0) {
			this->nrBuchete = nrBucheteNou;
		}
		else {
			throw "Valoare negativa";
		}
	}

	float* getVectorPreturi() {
		if (this->vectorPreturi == nullptr) {
			return nullptr;
		}
		float* vectorNou = new float[this->nrBuchete];
		for (int i = 0; i < this->nrBuchete; i++) {
			vectorNou[i] = this->vectorPreturi[i];
		}
		return vectorNou;
	}

	void setVectorPreturi(float* vector, int nrB) {
		setNrBuchete(nrB);

		if (this->vectorPreturi != nullptr) {
			delete[] this->vectorPreturi;
		}

		this->vectorPreturi = new float[this->nrBuchete];
		for (int i = 0; i < this->nrBuchete; i++) {
			this->vectorPreturi[i] = vector[i];
		}
	}

	~Florarie() {
		if (this->vectorPreturi != nullptr) {
			delete[] this->vectorPreturi;
		}
	}

	bool operator<(const Florarie& f) {
		return this->nrBuchete < f.nrBuchete;
	}

	void operator+=(float taxaDeAdunat) {
		this->taxaLunara += taxaDeAdunat;
	}

	bool operator!() {
		return this->taxaLunara > 0;
	}

	float operator()(float valoareDeAdaugat) {
		return this->taxaLunara + valoareDeAdaugat;
	}

	float& operator[](int index) {
		if (index >= 0 && index < this->nrBuchete) {
			return this->vectorPreturi[index];
		}
		else {
			throw exception();
		}
	}

	friend ostream& operator<<(ostream& out, const Florarie& f) {
		out << endl << "Operator de afisare: ";
		out << endl << "Id: " << f.id;
		out << endl << "Nume: " << f.nume;
		out << endl << "Taxa lunara: " << f.taxaLunara;
		out << endl << "Tip: ";
		if (f.tip == MAGAZIN) out << "MAGAZIN";
		if (f.tip == CHIOSC) out << "CHIOSC";
		out << endl << "Nr buchete: " << f.nrBuchete;
		if (f.vectorPreturi != nullptr && f.nrBuchete > 0) {
			out << endl << "Vector preturi: ";
			for (int i = 0; i < f.nrBuchete - 1; i++) {
				out << f.vectorPreturi[i] << " lei, ";
			}
			out << f.vectorPreturi[f.nrBuchete - 1] << " lei.";
		}
		return out;
	}

	friend istream& operator>>(istream& in, Florarie& f);

	Florarie operator++(int) {
		Florarie copie = *this;
		this->taxaLunara++;
		return copie;
	}

	Florarie& operator++() {
		this->taxaLunara++;
		return *this;
	}

	explicit operator int() {
		return this->nrBuchete;
	}
};

int Florarie::nrFlorarii = 0;

istream& operator>>(istream& in, Florarie& f) {
	cout << endl << "Taxa lunara: ";
	in >> f.taxaLunara;

	cout << endl << "Nume: ";
	in >> f.nume;

	cout << endl << "Tip (1 - MAGAZIN, 2 - CHIOSC): ";
	int tip;
	in >> tip;
	if (tip == 1) f.tip = MAGAZIN;
	if (tip == 2) f.tip = CHIOSC;

	cout << endl << "Nr buchete: ";
	in >> f.nrBuchete;

	if (f.vectorPreturi != nullptr) {
		delete[] f.vectorPreturi;
		f.vectorPreturi = nullptr;
	}

	f.vectorPreturi = new float[f.nrBuchete];
	for (int i = 0; i < f.nrBuchete; i++) {
		cout << endl << "vectorPreturi[" << i << "]: ";
		in >> f.vectorPreturi[i];
	}
	return in;
}

int main() {
	Florarie fLaTrandafir;

	fLaTrandafir += 250;

	if (!fLaTrandafir) {
		cout << endl << "Taxa nenula!";
	}
	else {
		cout << endl << "Taxa nula!";
	}

	cout << endl << "Apel operator functie: " << fLaTrandafir(15);

	cout << fLaTrandafir;

	Florarie f1 = fLaTrandafir++;

	cout << f1;
	cout << fLaTrandafir;

	Florarie f2 = ++fLaTrandafir;

	cout << f2;
	cout << fLaTrandafir;

	float* vectorPreturi = new float[4] {45, 60, 80, 120};
	Florarie* pPrimavara = new Florarie(9, 500, "Primavara", MAGAZIN, 4, vectorPreturi);
	delete[] vectorPreturi;
	pPrimavara->afisareFlorarie();

	if (fLaTrandafir < *pPrimavara) {
		cout << endl << "Floraria La Trandafir are mai putine buchete!";
	}
	else {
		cout << endl << "Floraria Primavara are mai putine buchete!";
	}

	(*pPrimavara)[0] = 50;
	cout << endl << "Apel operator index: " << (*pPrimavara)[0];

	cout << endl << "Am construit " << Florarie::nrFlorarii << " florarii!";

	cout << endl << "Cast explicit la int: " << (int)(*pPrimavara);

	delete pPrimavara;

	return 0;
}
