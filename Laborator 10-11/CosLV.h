#pragma once
#include "UI.h"

class CosLV : public QWidget, public Observ {
private:
	Cos & cos;
	QListView* lista = new QListView;
	ListModel* model = new ListModel(cos.getCurent());

	void init() {
		QVBoxLayout* ly = new QVBoxLayout;
		setLayout(ly);
		cos.Subscribe(this);
		lista->setModel(model);
		ly->addWidget(lista);
	}
	void reload(vector<Activitate>& all) {
		model->setActivitati(cos.getCurent());
	}

public:
	CosLV(Cos& c) :cos{ c } { init(); }

protected:
	void Notify() override {
		reload(cos.getCurent());
	}
};