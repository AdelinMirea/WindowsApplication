#include "service.h"
#include <string.h>
#include <algorithm>
#include "export.h"

void Service::AdaugareActivitate(std::string titlu, std::string descriere, std::string tip, int durata)
{
	Activitate activitate = Activitate(titlu, descriere, tip, durata);
	repo.adaugareActivitate(activitate);

	undoActions.push_back(std::make_unique<UndoAdauga>(repo, activitate));
}

void Service::StergereActivitate(std::string titlu, std::string descriere, std::string tip, int durata)
{
	Activitate activitate = Activitate(titlu, descriere, tip, durata);
	repo.stergereActivitate(activitate);

	undoActions.push_back(std::make_unique<UndoSterge>(repo, activitate));
}

void Service::ModificareDurataActivitate(std::string titlu, std::string descriere, std::string tip, int durata)
{
	Activitate activitate = Activitate(titlu, descriere, tip, durata);
	Activitate before = repo.getSpecific(activitate);
	repo.modificareDurataActivitate(activitate);

	undoActions.push_back(std::make_unique<UndoModifica>(repo, before, activitate));
}

std::vector<Activitate> Service::getAll()
{
	return repo.getall();
}

std::vector<Activitate> Service::CautareActivitate(std::string string)
{
	std::vector<Activitate>act;
	std::vector<Activitate> activitati = repo.getall();
	for (auto activitate : activitati) {
		if (activitate.getTitlu()==string || activitate.getDescriere() == string || activitate.getTip() == string) {
			act.push_back(activitate);
		}
	}
	return act;
	
}

std::vector<Activitate> Service::FiltrareDescriere(std::string descriere)
{
	std::vector<Activitate> Activitati = repo.getall();
	std::vector<Activitate> Filtrat;

	for (auto activitate : Activitati) {
		if (activitate.getDescriere() == descriere) {
			Filtrat.push_back(activitate);
		}
	}
	return Filtrat;
}

std::vector<Activitate> Service::FiltrareTip(std::string tip)
{
	std::vector<Activitate> Activitati = repo.getall();
	std::vector<Activitate> Filtrat;
/*
	for (auto activitate : Activitati) {
		if (activitate.getTip() == tip) {
			Filtrat.push_back(activitate);
		}
	}*/
	auto it = std::copy_if(Activitati.begin(), Activitati.end(), std::back_inserter(Filtrat), [&](const Activitate& a) {return (a.getTip() == tip);});
	return Filtrat;
}


std::vector<Activitate> Service::Sortare(bool (*f)(Activitate, Activitate)) {
	
	std::vector<Activitate> Elemente = repo.getall();
	/*for(int i=0; i<(int)Elemente.size()-1; i++)
		for (int j = i + 1; j < (int)Elemente.size(); j++) {
			if (f(Elemente[i], Elemente[j])) {
				Activitate aux= Elemente[i];
				Elemente[i] = Elemente[j];
				Elemente[j] = aux;
			}
			return Elemente;
			}*/
	
	std::sort(Elemente.begin(), Elemente.end(), f);
	return Elemente;
}

int Service::golesteListaCurenta()
{
	cos.golesteListaActivitati();
	return cos.getallcurent();
}



int Service::adaugaListaCurenta(std::string titlu)
{
	cos.adaugaListaActivitati(titlu, repo);
	return cos.getallcurent();
}

int Service::genereazaListaActivitati(int numar)
{
	return cos.genereazaListaActivitati(numar);
}

std::vector<Activitate> Service::getCurent()
{
	return cos.getCurent();
}

void Service::undo()
{
	if (undoActions.empty()) {
		throw RepoError("Nu mai exista operatii");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void Service::exportaCosCVS(std::string fileName)
{
	exportCVS(fileName, cos.getCurent());
}

void Service::exportaCosHTML(std::string fileName)
{
	exportHTML(fileName, cos.getCurent());
}


bool SortareTitlu(Activitate a1, Activitate a2) {
	return a1.getTitlu()<a2.getTitlu();
}

bool SortareDescriere(Activitate a1, Activitate a2) {
	return a1.getDescriere()<a2.getDescriere();
}

bool SortareDurata(Activitate a1, Activitate a2) {
	return a1.getDurata() < a2.getDurata();
}



