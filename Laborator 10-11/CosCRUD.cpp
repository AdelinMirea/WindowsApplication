#include "CosCRUD.h"

CosCRUDObj::CosCRUDObj(Cos& c) :cos{ c } {
	cos.Subscribe(this);
	create();
	conn();
}


void CosCRUDObj::create() {
	QVBoxLayout* ly = new QVBoxLayout;
	QListWidget* listaC = new QListWidget;
	w->setLayout(ly);
	loadListaCos();
	ly->addWidget(listaElementeCos);
	numarGen->setPlaceholderText("Numar:");
	but->addWidget(numarGen);
	but->addWidget(genCos);
	but->addWidget(golCos);
	ly->addLayout(but);
}

void CosCRUDObj::golesteCosul() {
	cos.golesteListaActivitati();
	listaElementeCos->clear();
	NotifyAll();
}

void CosCRUDObj::loadListaCos() {
	listaElementeCos->clear();
	for (auto& activitate : cos.getCurent()) {
		listaElementeCos->addItem(QString::fromStdString(activitate.getTitlu()));
	}
}

void CosCRUDObj::conn() {
	QObject::connect(golCos, &QPushButton::clicked, this, &CosCRUDObj::golesteCosul);
	QObject::connect(genCos, &QPushButton::clicked, this, &CosCRUDObj::GenCos);
}

void CosCRUDObj::GenCos() {
	//numarElementeGenerate->setText(numarGen->text());
	try {
		int numar = std::stoi(numarGen->text().toStdString());
		cos.genereazaListaActivitati(numar);
		loadListaCos();
		NotifyAll();
	}
	catch (RepoError& e) {
		QMessageBox* msg = new QMessageBox;
		msg->setText(QString::fromStdString(e.getMessage()));
		msg->exec();
	}
	catch (...) {
		QMessageBox* msg = new QMessageBox;
		msg->setText("Eroare la parsarea datelor");
		msg->exec();
	}
}