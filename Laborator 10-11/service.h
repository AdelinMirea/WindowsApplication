#pragma once
#include "repo.h"
#include "undo.h"
#include "Cos.h"
#include <memory>
using std::unique_ptr;



class Service
{
public:
	Service() = default;
	Service(ReposotoryInterface& rep) : repo{ rep } {}

	//functia adauga o activitate la lista de  activitati existente
	//input: titlu, descriere, tip, durata
	void AdaugareActivitate(std::string titlu, std::string descriere, std::string tip, int durata);

	//functia sterge o activitate, daca aceasta deja exista
	//input: titlu, descriere, tip, durata
	void StergereActivitate(std::string titlu, std::string descriere, std::string tip, int durata);

	//functia modifica durata unei activitati daca aceasta exista deja
	//input: titlu, descriere, tip, noua durata
	void ModificareDurataActivitate(std::string titlu, std::string descriere, std::string tip, int durata);


	//functia get all
	//output: o lista cu toate activitatile existente pana la acel moment
	std::vector<Activitate> getAll();

	//functia cauta o activitate dupa titlu si returneaza prima activitate gasita
	//input: titlu
	std::vector<Activitate> CautareActivitate(std::string titlu);

	//functia filtreaza activitatile dupa o anumita descriere data
	//input: descriere
	//output: lista filtrata
	std::vector<Activitate> FiltrareDescriere(std::string descriere);

	//functia filtreaza activitatile dupa un anumit tip dat
	//input: tip
	//output: lista filtrata
	std::vector<Activitate> FiltrareTip(std::string tip);

	std::vector<Activitate> Sortare(bool(*f)(Activitate, Activitate));

	//goleste lista de activitati curente
	//output: numarul curent de elemente din lista de activitati
	int golesteListaCurenta();

	//input: titlu
	//output: numarul de elemente curente din lista de activitati
	//adauga un element cu acelasi titlu din lista in lista de activitati curente 
	int adaugaListaCurenta(std::string titlu);
	
	int genereazaListaActivitati(int numar);

	Cos &getCos() {
		return cos;
	}

	std::vector<Activitate> getCurent();

	void stergeElementCos(std::string titlu) {
		cos.stergeElementCos(titlu);
	}

	void undo();

	void exportaCosCVS(std::string fileName);

	void exportaCosHTML(std::string fileName);
private:
	ReposotoryInterface & repo;
	std::vector<std::shared_ptr<ActiuneUndo>> undoActions;
	Cos cos{ repo };
};

bool SortareTitlu(Activitate a1, Activitate a2);

bool SortareDescriere(Activitate a1, Activitate a2);
bool SortareDurata(Activitate a1, Activitate a2);