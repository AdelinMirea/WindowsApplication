#include "Activitate.h"
#include "repo.h"
#include "service.h"
#include <assert.h>
#include <string>
#include "export.h"
//#include "Validare.h"

void testActivitate() {
	Activitate activitate;
	std::string titlu, descriere, tip;
	titlu = "Titlu";
	descriere = "Descriere";
	tip = "Tip";
	activitate.setTitlu(titlu);
	activitate.setDescriere(descriere);
	activitate.setTip(tip);
	activitate.setDurata(1);
	assert(activitate.getTitlu() == titlu);
	assert(activitate.getDescriere() == descriere);
	assert(activitate.getTip() == tip);
	assert(activitate.getDurata() == 1);
	Activitate a{ titlu, descriere, tip, 1 };
	assert(a == activitate);
	a = activitate;
	assert(a == activitate);
	a.setDurata(2);
	assert(!(a == activitate));
}

void testAdaugare() {
	std::string titlu, descriere, tip;
	titlu = "Titlu";
	descriere = "Descriere";
	tip = "Tip";
	int durata = 1;
	Activitate activitate{ titlu, descriere, tip, durata };
	Repository repo;
	Service serv(repo);
	serv.AdaugareActivitate(titlu, descriere, tip, durata);
	assert(serv.getAll().size() == 1);
	serv.AdaugareActivitate(titlu, descriere, tip, durata+1);
	serv.AdaugareActivitate(titlu, descriere, tip, durata+2);
	assert(serv.adaugaListaCurenta(titlu) == 1);
	//assert(serv.genereazaListaActivitati(2) == 2);
	//assert(serv.getCurent().size() == 2);
}

void testStergere() {
	std::string titlu, descriere, tip;
	titlu = "Titlu";
	descriere = "Descriere";
	tip = "Tip";
	int durata = 1;
	Activitate activitate{ titlu, descriere, tip, durata };
	Repository repo;
	Service serv(repo);
	serv.AdaugareActivitate(titlu, descriere, tip, durata);
	assert(serv.getAll().size() == 1);
	serv.StergereActivitate(titlu, descriere, tip, durata);
	assert(serv.getAll().size() == 0);
}

void testModificare() {
	std::string titlu, descriere, tip;
	titlu = "Titlu";
	descriere = "Descriere";
	tip = "Tip";
	int durata = 1;
	Activitate activitate{ titlu, descriere, tip, durata };
	Repository repo;
	Service serv(repo);
	serv.AdaugareActivitate(titlu, descriere, tip, durata);
	assert(serv.getAll()[0].getDurata() == 1);
	serv.ModificareDurataActivitate(titlu, descriere, tip, durata + 2);
	assert(serv.getAll()[0].getDurata() == durata + 2);
}

void testCautare() {
	std::string titlu, descriere, tip;
	titlu = "Titlu";
	descriere = "Descriere";
	tip = "Tip";
	int durata = 1;
	Activitate activitate{ titlu, descriere, tip, durata };
	Repository repo;
	Service serv(repo);
	serv.AdaugareActivitate(titlu, descriere, tip, durata);
	assert(serv.CautareActivitate(titlu)[0] == activitate);
}

void testFiltrare() {
	std::string titlu, descriere, tip;
	titlu = "Titlu";
	descriere = "Descriere";
	tip = "Tip";
	int durata = 1;
	Activitate activitate{ titlu, descriere, tip, durata };
	Repository repo;
	Service serv(repo);
	serv.AdaugareActivitate(titlu, descriere, tip, durata);
	serv.AdaugareActivitate(titlu, descriere, "altTip", durata);
	serv.AdaugareActivitate(titlu, "AltaDescriere", "altTip", durata);
	serv.AdaugareActivitate(titlu, "AltaDescriere", tip, durata);
	assert(serv.FiltrareDescriere(descriere).size() == 2);
	assert(serv.FiltrareTip(tip).size() == 2);
}

void testSort() {
	std::string titlu, descriere, tip;
	titlu = "z";
	descriere = "z";
	tip = "z";
	Repository repo;
	Service serv(repo);
	serv.AdaugareActivitate(titlu, descriere, tip, 3);

	titlu = "c";
	descriere = "c";
	tip = "c";
	serv.AdaugareActivitate(titlu, descriere, tip, 2);

	titlu = "a";
	descriere = "a";
	tip = "a";
	serv.AdaugareActivitate(titlu, descriere, tip, 1);
	serv.Sortare(SortareDurata);
	serv.Sortare(SortareTitlu);
	serv.Sortare(SortareDescriere);
}

void testeExcep() {
	Repository r;
	Service s{ r };
	std::string titlu, descriere, tip;
	titlu = "Titlu";
	descriere = "Descriere";
	tip = "Tip";
	const int durata = 1;
	s.AdaugareActivitate(titlu, descriere, tip, durata);
	assert(s.golesteListaCurenta()==0);
	try {
		s.AdaugareActivitate(titlu, descriere, tip, durata);	}
	catch (RepoError& e) {
		assert(e.getMessage() == "Activitatea exista deja!");
	}
	try {
		s.StergereActivitate("q", "q", "q", 1);	}
	catch (RepoError& e) {
		assert(e.getMessage() == "Elementul nu exista");
	}try {
		s.ModificareDurataActivitate("q", "q", "q", 1);	}
	catch (RepoError& e) {
		assert(e.getMessage() == "Activitatea nu exista");
	}try {
		int i=s.adaugaListaCurenta("ll");
	}catch (RepoError& e) {
		assert(e.getMessage() == "Nu exista element cu acest titlu");
	}
}

void testCos() {
	FileRepo repo("test");
	Service serv{ repo };
	Activitate a{ "a", "a", "a", 1 };
	serv.AdaugareActivitate("a", "a", "a", 1);
	serv.AdaugareActivitate("b", "b", "b", 2);
	serv.AdaugareActivitate("c", "c", "c", 3);
	assert(serv.genereazaListaActivitati(2) == 2);
	assert(serv.getCurent().size() == 2);
	serv.exportaCosCVS("test");
	serv.exportaCosHTML("test");
	assert(serv.golesteListaCurenta() == 0);
	serv.exportaCosCVS("test");
	try {
		serv.genereazaListaActivitati(10);
	}catch(RepoError& e) {
		assert("Numaul introdus este prea mare" == e.getMessage());
	}
}

void testUndo() {
	FileRepo repo("test");
	Service serv{ repo };
	serv.AdaugareActivitate("a", "a", "a", 1);
	serv.AdaugareActivitate("b", "b", "b", 2);
	serv.AdaugareActivitate("c", "c", "c", 3);
	assert(serv.getAll().size() == 3);
	serv.undo();
	assert(serv.getAll().size() == 2);
	serv.ModificareDurataActivitate("a", "a", "a", 4);
	assert(serv.getAll().size() == 2);
	serv.StergereActivitate("a", "a", "a", 4);
	assert(serv.getAll().size() == 1);
	serv.undo();
	assert(serv.getAll().size() == 2);
	serv.undo();
	assert(serv.getAll().size() == 2);
	/*try {
		exportCVS("test1", repo.getall());
	}
	catch (RepoError& e) {
		assert("Unable to open file:test" == e.getMessage());
	}try {
		exportHTML("test1", repo.getall());
	}catch (RepoError& e) {
		assert("Unable to open file:test" == e.getMessage());
	}*/
	try {
		serv.undo();
		serv.undo();
		serv.undo();
	}catch (RepoError& e) {
		assert("Nu mai exista operatii" == e.getMessage());
	}
	//std::ofstream o("test");
	//o.close();
	
	FileRepo f("testFile");
}


void TestAll() {
	testActivitate();
	testAdaugare();
	testStergere();
	testModificare();
	testCautare();
	testFiltrare();
	testSort();
	testeExcep();
	testCos();
	testUndo();
}