#pragma once
#include "UI.h"

class CosCRUDObj :public QWidget, public Observ, public Observable {

	Cos& cos;
	QWidget* w = new QWidget;
	QLineEdit * numarGen = new QLineEdit;
	QHBoxLayout* but = new QHBoxLayout;
	QPushButton* golCos = new QPushButton("Golire Cos");
	QPushButton* genCos = new QPushButton("Generare Cos");
	QListWidget * listaElementeCos = new QListWidget();

public:
	void Notify() override {
		loadListaCos();
	}
	
	void Show() {
		w->show();
	}

	CosCRUDObj(Cos& c);

	void loadListaCos();

	void create();

	void conn();

	void golesteCosul();
	
	void GenCos();
	
};

