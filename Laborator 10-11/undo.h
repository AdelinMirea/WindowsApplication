#pragma once
#include "repo.h"
//#include "Activitate.h"
class ActiuneUndo{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo()= default;
};

class UndoAdauga :public ActiuneUndo {
private:
	Activitate adaugat;
	ReposotoryInterface& repo;
public:
	UndoAdauga(ReposotoryInterface& repo, const Activitate& a) :repo{ repo }, adaugat{ a } {}
	void doUndo() override {
		repo.stergereActivitate(adaugat);
	}
};

class UndoSterge : public ActiuneUndo {
private:
	ReposotoryInterface & repo;
	Activitate sters;
public:
	UndoSterge(ReposotoryInterface& repo, const Activitate& a) :repo{ repo }, sters{ a } {}
	void doUndo() override {
		repo.adaugareActivitate(sters);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	ReposotoryInterface & repo;
	Activitate before;
	Activitate after;
public:
	UndoModifica(ReposotoryInterface& repo, const Activitate& before, const Activitate& after) : before{ before }, after{ after }, repo{ repo } {}
	void doUndo() override {
		repo.stergereActivitate(after);
		repo.adaugareActivitate(before);
	}
};
