#pragma once
#include <vector>
#include "Activitate.h"
#include "POSError.h"
#include <map>

class RepoError : public POSError {
public:
	RepoError(std::string message) :
		POSError(message) {
	}
};

class ReposotoryInterface {


public:
	ReposotoryInterface() = default;
	virtual std::vector<Activitate> getall() const =0;

	virtual void adaugareActivitate(Activitate other) = 0;

	virtual void stergereActivitate(Activitate other) = 0;

	virtual void modificareDurataActivitate(Activitate other)= 0 ;

	virtual Activitate getSpecific(Activitate other)=0;

	virtual ~ReposotoryInterface() {};
};


class Repository:public ReposotoryInterface {
public:

	//constructor default 
	Repository() {// = default;
		add();
	}
	Repository(const Repository& ot) = delete;
	//functia get all
	//output: o lista cu toate activitatile existente pana la acel moment
	std::vector<Activitate> getall() const;

	//functia adauga o activitate noua la lista de activitati existente
	//input: other - Activitate
	virtual void adaugareActivitate(Activitate other);


	void add() {
		adaugareActivitate(Activitate{ "a1", "a", "a", 1 });
		adaugareActivitate(Activitate{ "a2", "a", "a", 2 });
		adaugareActivitate(Activitate{ "a3", "a", "a", 7 });
		adaugareActivitate(Activitate{ "a4", "a", "a", 2 });
		adaugareActivitate(Activitate{ "a5", "a", "a", 4 });

	}
	//functia cauta daca activitatea exista si in caz afirmativ o sterge
	//input: other - Activitate
	virtual void stergereActivitate(Activitate other);

	//functia modifica durata unei activitati in cazul in care aceasta este gasita
	//input: other - Activitate
	virtual void modificareDurataActivitate(Activitate other);

	virtual Activitate getSpecific(Activitate other);

	//std::vector<Activitate> getCurent();

	virtual ~Repository() {};

private:
	std::vector<Activitate> listaActivitati;
};


class RepoMap : public ReposotoryInterface {
private:
	std::map<std::string, Activitate> mapActivitati;

public:
	void adaugareActivitate(Activitate other) override {
		auto it = mapActivitati.find(other.getTitlu());
		if (it != mapActivitati.end()) {
			throw RepoError("Activitatea exista deja!");
		}
		else	this->mapActivitati.insert(std::make_pair(other.getTitlu(), other));
	}

	void stergereActivitate(Activitate other)override {
		auto it = mapActivitati.find(other.getTitlu());
		if (it != mapActivitati.end()) {
			mapActivitati.erase(it);
		}
		else {
			throw RepoError("Elementul nu exista");
		}
	}

	void modificareDurataActivitate(Activitate other)override {
		for (auto &activitate : mapActivitati) {
			if (activitate.second.getTitlu() == other.getTitlu() && activitate.second.getDescriere() == other.getDescriere() && activitate.second.getTip() == other.getTip()) {
				activitate.second.setDurata(other.getDurata());
				return;
			}
		}
		throw RepoError("Activitatea nu exista");
	}

	Activitate getSpecific(Activitate other)override {
		Activitate ret;
		for (auto &activitate : mapActivitati) {
			if (activitate.second.getTitlu() == other.getTitlu() && activitate.second.getDescriere() == other.getDescriere() && activitate.second.getTip() == other.getTip()) {
				return activitate.second;
			}
		}
		return ret;
	}
	std::vector<Activitate> getall() const {
		std::vector<Activitate> ret;
		for (auto& act : mapActivitati) {
			ret.push_back(act.second);
		}
		return ret;
	}
};

class FileRepo :public Repository {
private:
	void writeToFile();
	void loadFromFile();
	std::string fName;

public:
	FileRepo(std::string fName) :fName{ fName }, Repository(){
		loadFromFile();
	}
	void adaugareActivitate(Activitate other) override;

	void stergereActivitate(Activitate other) override;

	void modificareDurataActivitate(Activitate other) override;
};