	#pragma once
#include <vector>
#include "Activitate.h"
#include "repo.h"
#include <fstream>
#include <random>
#include <chrono>

class Observ {
public:
	virtual void Notify() = 0;
};
//Observable - cea la care se uita
//Observer - primeste notificari
class Observable {
	std::vector<Observ*> observati;
protected:
	void NotifyAll() {
		for (auto c : observati) {
			c->Notify();
		}
	}
public:
	void Subscribe(Observ* c) {
		observati.push_back(c);
	}
};


class Cos : public Observable {
private:
	std::vector<Activitate> curentListaActivitati;
	ReposotoryInterface& repo;
public:

	Cos(ReposotoryInterface& rep) :repo{ rep } {}

	//va elimina elementele din lista de activitati curenta
	//elementele vor fi distruse
	//size-ul va fi setat pe 0
	void golesteListaActivitati() {
		curentListaActivitati.clear();
		NotifyAll();
	}


	//va genera o lista de n activitati alese aleator
	//input: numar
	int genereazaListaActivitati(size_t numar)
	{
		/*
		std::ifstream f("in.txt");
		f >> numar;*/
		if (numar > repo.getall().size()) {
			throw RepoError("Numaul introdus este prea mare");
		}
		
		golesteListaActivitati();
		while (curentListaActivitati.size() != numar) {
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<> dist(0, repo.getall().size() - 1);
			int rndNr = dist(mt);
			Activitate a = repo.getall()[rndNr];
			auto it = std::find_if(curentListaActivitati.begin(), curentListaActivitati.end(), [&](const Activitate& b) {return a == b; });//repo.getall()[rndNr]);
			if (it == curentListaActivitati.end()) {
				curentListaActivitati.push_back(repo.getall()[rndNr]);
			}
		}
		NotifyAll();
		return curentListaActivitati.size();
	}



	std::vector<Activitate> getCurent()
	{
		return curentListaActivitati;
	}
	
	//returneaza numarul de elemente din lista de activitati curente
	int getallcurent() {
		return curentListaActivitati.size();
	}

	//va cauta in listaActivitati un element cu titlul identic
	//va insera elementul in lista de activitati curente
	//daca nu va fi gasit, se va arunca o exceptie
	//input: titlu
	void adaugaListaActivitati(std::string titlu, ReposotoryInterface& repo)
	{
		bool gasit = false;
		//auto it = find(listaActivitati.begin(), listaActivitati.end(), [=](Activitate a) {return a.getTitlu() == titlu; });
		for (auto activitate : repo.getall()) {
			if (activitate.getTitlu() == titlu) {
				curentListaActivitati.push_back(activitate);
				gasit = true;
				break;
			}
		}
		NotifyAll();
		if (gasit == false) {
			throw RepoError("Nu exista element cu acest titlu");
		}
	}

	void stergeElementCos(std::string titlu) {
		for (int i = 0; i < curentListaActivitati.size(); i++) {
			if (curentListaActivitati[i].getTitlu() == titlu) {
				curentListaActivitati.erase(curentListaActivitati.begin() + i);
				i--;
			}
		}
	}
};