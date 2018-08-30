#include "repo.h"
#include <algorithm>
#include <fstream>

std::vector<Activitate> Repository::getall() const
{
	return this->listaActivitati;
}

void Repository::adaugareActivitate(Activitate other)
{
	/*
	for (auto activitate : listaActivitati) {
		if (activitate == other) {
			throw RepoError("Activitatea exista deja!");
		}
	}*/
	auto it = find_if(listaActivitati.begin(), listaActivitati.end(), [=](Activitate a) {return (a.getTitlu() == other.getTitlu()); });
	if (it != listaActivitati.end()) {
		throw RepoError("Activitatea exista deja!");
	}else	this->listaActivitati.push_back(other); 
}

void Repository::stergereActivitate(Activitate other)
{
	std::vector<Activitate>::iterator it = std::find(listaActivitati.begin(), listaActivitati.end(), other);
	if (it != listaActivitati.end()) {
		listaActivitati.erase(it);
	}
	else {
		throw RepoError("Elementul nu exista");
	}
}

void Repository::modificareDurataActivitate(Activitate other)
{
	bool exista = false;
	for (auto &activitate : listaActivitati) {
		if (activitate.getTitlu() == other.getTitlu() && activitate.getDescriere() == other.getDescriere() && activitate.getTip() == other.getTip()) {
			activitate.setDurata(other.getDurata());
			exista = true;
			break;
		}
	}
	if (exista == false) {
		throw RepoError("Activitatea nu exista");
	}
}

Activitate Repository::getSpecific(Activitate other)
{
	Activitate ret;
	for (auto &activitate : listaActivitati) {
		if (activitate.getTitlu() == other.getTitlu() && activitate.getDescriere() == other.getDescriere() && activitate.getTip() == other.getTip()) {
			ret = activitate;
		}
	}
	return ret;
}

//
//std::vector<Activitate> Repository::getCurent()
//{
//	return curentListaActivitati;
//}

void FileRepo::writeToFile() {
	std::ofstream out(fName);/*
	if (!out.is_open()) {
		throw RepoError("Fisierul nu poate fi deschis!");
	}
	else {*/
	for (auto& other : getall()) {
		out << other.getTitlu() << std::endl;
		out << other.getDescriere() << std::endl;
		out << other.getTip() << std::endl;
		out << other.getDurata() << std::endl;
	}
	out.close();
	//}
}

void FileRepo::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) { 
		std::ofstream creare(fName);
		creare.close();
		return;
	}
	while (!in.eof()) {
		std::string titlu;
		in >> titlu;// std::getline(in, titlu, '\n');

		std::string descriere;
		in >> descriere; // std::getline(in, descriere, '\n');

		std::string tip;
		in >> tip; // std::getline(in, tip, '\n');

		int durata;
		in >> durata;
		if (in.eof()) {	//nu am reusit sa citesc numarul
			break;
		}
		Activitate a{ titlu, descriere, tip, durata };
		Repository::adaugareActivitate(a);
 	}
	in.close();
}

void FileRepo::adaugareActivitate(Activitate other)
{
	Repository::adaugareActivitate(other);
	writeToFile();
}

void FileRepo::stergereActivitate(Activitate other)
{
	Repository::stergereActivitate(other);
	writeToFile();
}

void FileRepo::modificareDurataActivitate(Activitate other)
{
	Repository::modificareDurataActivitate(other);
	writeToFile();
}
