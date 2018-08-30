#include "UI.h"
#include "Validare.h"
#include <string>
#include <qdebug.h>
#include "qlistview.h"
using std::string;

UI::UI(Service& service, QWidget *parent) : QMainWindow(parent), serv{ service } {
	CreareUI();
	ConnectSignals();
	ui.setupUi(this);
}

string FormToInput(string &text) {
	for (int i = 0; i < text.length(); i++) {
		if (text[i] == ' ') {
			text[i] = '_';
		}
	}
	return text;
}

string InputToForm(string& text) {
	for (int i = 0; i < text.length(); i++) {
		if (text[i] == '_') {
			text[i] = ' ';
		}
	}
	return text;
}

void UI::colour() {

	std::vector<Activitate> vect = serv.getAll();
	std::vector<int> durate;
	for (int i = 0; i < vect.size(); i++) {
		durate.push_back(vect[i].getDurata());
	}
	std::sort(durate.begin(), durate.end());
	for (int i = 0; i < lista->count(); ++i) {
		QListWidgetItem* item = lista->item(i);
		for (auto& a : vect) {
			if (a.getTitlu() == item->text().toStdString()) {
				if (a.getDurata() < durate[durate.size() / 3]) {
					item->setBackground(Qt::green);
				}
				else if (a.getDurata() >= durate[durate.size() / 3] && a.getDurata() < durate[(durate.size() / 3) * 2]) {
					item->setBackground(Qt::blue);
				}
				else {
					item->setBackground(Qt::red);
				}
			}
		}
		//item->setBackground(Qt::green);
	}

}

void UI::adaugare() {
	try {
		string titlu = txtTitlu->text().toStdString();
		string descriere = txtDescriere->text().toStdString();
		string tip = txtTip->text().toStdString();
		string durata = txtDurata->text().toStdString();
		Validare v;
		v.ValidareTitlu(titlu);
		v.ValidareDescriere(descriere);
		v.ValidareTip(tip);
		v.ValidareDurata(std::stoi(durata));
		titlu = FormToInput(titlu);
		descriere = FormToInput(descriere);
		tip = FormToInput(tip);
		//txtTitlu->setText(QString::fromStdString(InputToForm(titlu))); //de ce nu inlocuieste spatiu cu _ fata asta?
		serv.AdaugareActivitate(titlu, descriere, tip, std::stoi(durata));
		lista->addItem(txtTitlu->text());
		//Sort->setEnabled(true);
		//filter->setEnabled(true);
		modelListaa->setActivitati(serv.getAll());
		//colour();
	}
	catch (ValidareErr &e) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString(e.getMessage()));
		msg.exec();
	}
	catch (RepoError &e) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString(e.getMessage()));
		msg.exec();
	}
	catch (...) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString("S-a produs o eroare / durata introdusa nu este valida"));
		msg.exec();
	}
}

void UI::modificare()
{
	try {
		string titlu = txtTitlu->text().toStdString();
		string descriere = txtDescriere->text().toStdString();
		string tip = txtTip->text().toStdString();
		string durata = txtDurata->text().toStdString();
		Validare v;
		v.ValidareTitlu(titlu);
		v.ValidareDescriere(descriere);
		v.ValidareTip(tip);
		v.ValidareDurata(std::stoi(durata));
		titlu = FormToInput(titlu);
		descriere = FormToInput(descriere);
		tip = FormToInput(tip);
		serv.ModificareDurataActivitate(titlu, descriere, tip, std::stoi(durata));
		modelListaa->setActivitati(serv.getAll());

	}
	catch (ValidareErr &e) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString(e.getMessage()));
		msg.exec();
	}
	catch (RepoError &e) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString(e.getMessage()));
		msg.exec();
	}
	catch (...) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString("S-a produs o eroare / durata introdusa nu este valida"));
		msg.exec();
	}
}

void UI::getDetails(QModelIndex item)
{
	auto all = serv.getAll();
	Activitate a = all[item.row()];
	remove->setEnabled(true);
	//for (auto& a : serv.getAll()) {
		//if (a.getTitlu() == FormToInput(item->text().toStdString())) {
			txtTitlu->setText(QString::fromStdString(a.getTitlu())); 
			//txtTitlu->setText(QString::fromStdString(InputToForm(a.getTitlu())));
			txtDescriere->setText(QString::fromStdString(a.getDescriere())); 
			//txtDescriere->setText(QString::fromStdString(InputToForm(a.getDescriere())));
			txtTip->setText(QString::fromStdString(a.getTip())); 
			//txtTip->setText(QString::fromStdString(InputToForm(a.getTip())));
			txtDurata->setText(QString::fromStdString(std::to_string(a.getDurata())));
			//break;
		//}
	//}
	//txtTitlu->setText();
}

void UI::removeF()
{
	try {
		string titlu = txtTitlu->text().toStdString();
		string descriere = txtDescriere->text().toStdString();
		string tip = txtTip->text().toStdString();
		string durata = txtDurata->text().toStdString();
		Validare v;
		v.ValidareTitlu(titlu);
		v.ValidareDescriere(descriere);
		v.ValidareTip(tip);
		v.ValidareDurata(std::stoi(durata));
		titlu = FormToInput(titlu);
		descriere = FormToInput(descriere);
		tip = FormToInput(tip);
		bool existaInCos = false;
		for (int i = 0; i < listaElementeCos->count(); i++) {
			if (txtTitlu->text() == listaElementeCos->item(i)->text()) {
				existaInCos = true;
				break;
			}
		}
		if (existaInCos == true) {
			QMessageBox* msg = new QMessageBox;
			msg->setText("Elementul pe care doriti sa il stergeti exista in cos. Doriti sa continuati?");
			msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
			int ret = msg->exec();
			if (ret == QMessageBox::Yes) {
				serv.StergereActivitate(titlu, descriere, tip, std::stoi(durata));
				serv.stergeElementCos(titlu);
				qDeleteAll(lista->selectedItems());
				std::vector<Activitate> list = serv.getAll();
				lista->clear();
				for (auto& activitate : list) {
					lista->addItem(QString::fromStdString(activitate.getTitlu()));
				}
				updateCos(); //-----------
				modelListaa->setActivitati(serv.getAll());

			}
		}
		else {
			serv.StergereActivitate(titlu, descriere, tip, std::stoi(durata));
			qDeleteAll(lista->selectedItems());
			std::vector<Activitate> list = serv.getAll();
			lista->clear();
			for (auto& activitate : list) {
				lista->addItem(QString::fromStdString(activitate.getTitlu()));
			}
			modelListaa->setActivitati(serv.getAll());

		}
		if (serv.getAll().size() == 0) {
			remove->setEnabled(false);
			Sort->setEnabled(false);
			filter->setEnabled(false);
		}
	}
	catch (ValidareErr &e) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString(e.getMessage()));
		msg.exec();
	}
	catch (RepoError &e) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString(e.getMessage()));
		msg.exec();
	}
	catch (...) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString("S-a produs o eroare / durata introdusa nu este valida"));
		msg.exec();
	}
}

void UI::printList() {
	/*lista->clear();
	for (auto& activitate : serv.getAll()) {
		lista->addItem(QString::fromStdString(activitate.getTitlu()));
	}*/
	modelListaa->setActivitati(serv.getAll());
}

void UI::SortTitlu() {
	std::vector<Activitate> sorted = serv.Sortare(SortareTitlu);
	/*lista->clear();
	for (auto& activitate : sorted) {
		lista->addItem(QString::fromStdString(activitate.getTitlu()));
	}*/
	modelListaa->setActivitati(sorted);

}

void UI::SortDescriere() {
	std::vector<Activitate> sorted = serv.Sortare(SortareDescriere);
	/*lista->clear();
	for (auto& activitate : sorted) {
		lista->addItem(QString::fromStdString(activitate.getTitlu()));
	}*/
	modelListaa->setActivitati(sorted);

}

void UI::SortDurata() {
	std::vector<Activitate> sorted = serv.Sortare(SortareDurata);
	/*lista->clear();
	for (auto& activitate : sorted) {
		lista->addItem(QString::fromStdString(activitate.getTitlu()));
	}*/
	modelListaa->setActivitati(sorted);

}

void UI::sort()
{
	//titlu, descriere, durata
	QWidget* SortOptions = new QWidget;
	QHBoxLayout* sortedLayout = new QHBoxLayout;
	SortOptions->setLayout(sortedLayout);
	QPushButton* SortTitlu = new QPushButton("Sortare titlu");
	QPushButton* SortDescriere = new QPushButton("Sortare descriere");
	QPushButton* Sortdurata = new QPushButton("Sortare durata");

	sortedLayout->addWidget(SortTitlu);
	sortedLayout->addWidget(SortDescriere);
	sortedLayout->addWidget(Sortdurata);

	SortOptions->show();

	QObject::connect(SortTitlu, &QPushButton::clicked, this, &UI::SortTitlu);
	QObject::connect(SortDescriere, &QPushButton::clicked, this, &UI::SortDescriere);
	QObject::connect(Sortdurata, &QPushButton::clicked, this, &UI::SortDurata);

}
/*
void creareUI() {


	
	//main window
	QHBoxLayout* HorizontalLayout = new QHBoxLayout();
	QWidget* window = new QWidget();
	window->setLayout(HorizontalLayout);


	//left window: list and buttons
	QWidget* LeftWindow = new QWidget();
	QVBoxLayout* VerticalLayout1 = new QVBoxLayout();
	LeftWindow->setLayout(VerticalLayout1);
	//add left window to the whole window
	HorizontalLayout->addWidget(LeftWindow);

	//create and add list
	QListWidget* lista = new QListWidget();
	VerticalLayout1->addWidget(lista);

	//vreate buttons layout and widget
	QHBoxLayout* buttons1 = new QHBoxLayout();
	QWidget* buttonsLeft = new QWidget();

	//add buttons layout to left window layout
	VerticalLayout1->addLayout(buttons1);

	buttonsLeft->setLayout(buttons1);
	//add remove button
	QPushButton* remove = new QPushButton("Stergere");
	buttons1->addWidget(remove);
	//add remobe button
	QPushButton* Sort = new QPushButton("Sortare");
	buttons1->addWidget(Sort);

	//right window UI
	QWidget* RightWindow = new QWidget();
	QVBoxLayout* VerticalLayout2 = new QVBoxLayout();

	//add right window to the window
	RightWindow->setLayout(VerticalLayout2);
	//	VerticalLayout2->addWidget(RightWindow);
	HorizontalLayout->addWidget(RightWindow);

	//add form to the right layout
	QFormLayout* fields = new QFormLayout();
	QWidget* textinput = new QWidget();
	fields->addWidget(textinput);

	QLabel* lblTitlu = new QLabel("Titlu: ");
	QLabel* lblDescriere = new QLabel("Descriere: ");
	QLabel* lblTip = new QLabel("Tip: ");
	QLabel* lblDurata = new QLabel("Durata: ");

	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtDescriere = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtDurata = new QLineEdit;

	fields->addRow(lblTitlu, txtTitlu);
	fields->addRow(lblDescriere, txtDescriere);
	fields->addRow(lblTip, txtTip);
	fields->addRow(lblDurata, txtDurata);

	VerticalLayout2->addLayout(fields);

	QHBoxLayout* buttons2 = new QHBoxLayout();
	QWidget* row1 = new QWidget();
	VerticalLayout2->addLayout(buttons2);

	row1->setLayout(buttons2);
	QPushButton* add = new QPushButton("Adaugare");
	buttons2->addWidget(add);

	QPushButton* update = new QPushButton("Modificare durata");
	buttons2->addWidget(update);

	QHBoxLayout* buttons3 = new QHBoxLayout();
	QWidget* row2 = new QWidget();
	VerticalLayout2->addLayout(buttons3);
	row2->setLayout(buttons3);

	QPushButton* filterDescription = new QPushButton("FiltrareDescriere");
	QPushButton* filterType = new QPushButton("FiltrareTip");
	buttons3->addWidget(filterDescription);
	buttons3->addWidget(filterType);

	QPushButton* close = new QPushButton("Close");
	buttons3->addWidget(close);

	window->show();


	QObject::connect(close, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
	QObject::connect(add, &QPushButton::clicked(), adaugare(txtTitlu, txtDescriere, txtTip, txtDurata));
	
}
*/

void UI::filterDescriere() {
	std::vector<Activitate> filtrat = serv.FiltrareDescriere(descriere->text().toStdString());
	/*flist->clear();
	for (auto& activitate : filtrat) {
		flist->addItem(QString::fromStdString(activitate.getTitlu()));
	}
	*/
	modelFilter->setActivitati(filtrat);
}

void UI::filterTip() {
	std::vector<Activitate> filtrat = serv.FiltrareTip(tip->text().toStdString());
	/*flist->clear();
	for (auto& activitate : filtrat) {
		flist->addItem(QString::fromStdString(activitate.getTitlu()));
	}*/
	modelFilter->setActivitati(filtrat);

}

void UI::Filter() {
	QWidget* filterWindow = new QWidget;
	QVBoxLayout* filterLayout = new QVBoxLayout;
	filterWindow->setLayout(filterLayout);
	flist2->setModel(modelFilter);
	filterLayout->addWidget(flist2);
	QPushButton* fdescriere = new QPushButton("Filtrare descriere");
	QPushButton* ftip = new QPushButton("Filtrare tip");

	descriere->setPlaceholderText("Descriere");

	tip->setPlaceholderText("Tip");

	QFormLayout* filterform = new QFormLayout;
	filterform->addRow(descriere, fdescriere);
	filterform->addRow(tip, ftip);

	filterLayout->addLayout(filterform);

	QObject::connect(fdescriere, &QPushButton::clicked, this, &UI::filterDescriere);
	QObject::connect(ftip, &QPushButton::clicked, this, &UI::filterTip);

	filterWindow->show();
}

void UI::doUndo() {
	try {
		serv.undo();
		printList();
		if (serv.getAll().size() == 0) {
			filter->setEnabled(false);
			Sort->setEnabled(false);
		}
		else {
			filter->setEnabled(true);
			Sort->setEnabled(true);
		}
	}catch(...){
		QMessageBox* msg = new QMessageBox;
		msg->setText("Eroare undo");
		msg->exec();
	}

}

void UI::golesteCosul() {
	serv.golesteListaCurenta();
	listaElementeCos->clear();
}

void UI::adaugaCos() {
	try {
		serv.adaugaListaCurenta(txtCosTitlu->text().toStdString());		
	}
	catch (RepoError& e) {
		QMessageBox* msg = new QMessageBox;
		msg->setText(QString::fromStdString(e.getMessage()));
		msg->exec();
	}
}

void UI::genereazaCosul()
{
	try {
		int numar = std::stoi(numarElementeGenerate->text().toStdString());
		serv.genereazaListaActivitati(numar);
		listaElementeCos->clear();
		for (auto& activitate : serv.getCurent()) {
			listaElementeCos->addItem(QString::fromStdString(activitate.getTitlu()));
		}
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

void UI::exportCSV()
{
	try {
		serv.exportaCosCVS("ListaActivitati.cvs");
	}
	catch (...) {
		QMessageBox* msg = new QMessageBox;
		msg->setText("Eroare la exportarea in fisier");
		msg->exec();
	}
}

void UI::exportHTML()
{
	try {
		serv.exportaCosCVS("ListaActivitati.html");
	}
	catch (...) {
		QMessageBox* msg = new QMessageBox;
		msg->setText("Eroare la exportarea in fisier");
		msg->exec();
	}
}

bool ExistaInLista(const QString titlu, const std::vector<Activitate>& all) {

	for (auto& p : all) {
		if (p.getTitlu() == titlu.toStdString()) {
			return true;
		}
	}
	return false;
}

void UI::updateCos()
{
	//pune in cos doar elementele care sunt si in lista
	//golesteCosul();
	listaElementeCos->clear();
	for (auto&p : serv.getCurent()) {
		//if (ExistaInLista(QString::fromStdString(p.getTitlu()), serv.getAll())) {
			listaElementeCos->addItem(QString::fromStdString(p.getTitlu()));
		//}
	}
}

void UI::CreareUI()
{
	mainWindow->setLayout(HorizontalLayout);

	LeftWindow->setLayout(VerticalLayout1);

	HorizontalLayout->addWidget(LeftWindow);
	VerticalLayout1->addWidget(ContinutLista);

	listaa->setModel(modelListaa);
	VerticalLayout1->addWidget(listaa);
	
	VerticalLayout1->addLayout(buttons1);

	buttonsLeft->setLayout(buttons1);
	//pentru histograma
	buttons1->addWidget(histogramaB);
	buttons1->addWidget(remove);
	if (serv.getAll().size() == 0) {
		remove->setEnabled(false);
		Sort->setEnabled(false);
		filter->setEnabled(false);
	}
	buttons1->addWidget(Sort);

	buttons1->addWidget(filter);
	QHBoxLayout* UndoClose = new QHBoxLayout;
	VerticalLayout1->addLayout(UndoClose);
	UndoClose->addWidget(undo);
	UndoClose->addWidget(close);

	fields->addWidget(textinput);
	
	fields->addRow(lblTitlu, txtTitlu);
	fields->addRow(lblDescriere, txtDescriere);
	fields->addRow(lblTip, txtTip);
	fields->addRow(lblDurata, txtDurata);


	window2->setLayout(layoutNew);
	layoutNew->addLayout(fields);

	layoutNew->addLayout(buttons2);

	row1->setLayout(buttons2);
	buttons2->addWidget(add);

	buttons2->addWidget(update);



		
	//lista pentru cos

	VerticalLayout1->addLayout(ListaCosLayout);
	ListaCosLayout->addLayout(adaugareElementInCos);

	txtCosTitlu->setPlaceholderText("Titlul: ");
	adaugareElementInCos->addRow(txtCosTitlu, adaugaInCos);

	ListaCosLayout->addLayout(butoane2Cos);

	row2->setLayout(butoane2Cos);

	numarElementeGenerate->setPlaceholderText("Numar");
	butoane2Cos->addWidget(numarElementeGenerate);
	butoane2Cos->addWidget(genereazaCos);
	butoane2Cos->addWidget(golesteCos);


	ListaCosLayout->addWidget(ExportCosWidget);
	ExportCosWidget->setLayout(layoutExportCos);
	layoutExportCos->addWidget(exportCosHTML);
	layoutExportCos->addWidget(exportCosCSV);

	//histograma	
	historigramaw->setLayout(histL);

	printList();

	mainWindow->show();
	QHBoxLayout* COS = new QHBoxLayout;
	VerticalLayout1->addLayout(COS);
	COS->addWidget(WindowFields);
	COS->addWidget(cosCRUD);
	COS->addWidget(COSRO);
	COS->addWidget(cosList);
	//window2->show();
}

class Painter : public QWidget {
	std::vector<Activitate> v;
	int x = 20, y = 25, h = 1, w = 20;
public:
	void setw(std::vector<Activitate> v) {
		this->v = v;
	}
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		//p.setFont(QFont("Arial", 11));
		for (const auto&act : v) {
			//p.drawText(x, y-5, QString::fromStdString(act.getTitlu()));
			p.drawRect(x, y, w, act.getDurata() * 20);
			x += w + w / 2;
		}
		x = 20;
	}
};

void UI::hist() {	
	Painter* paint = new Painter;
	paint->setw(serv.getAll());
	paint->show();
}

#include "CosCRUD.h"
void UI::CosCRUD() {
	CosCRUDObj *c = new CosCRUDObj(serv.getCos());
	c->Show();
}

class draw : public QWidget, public Observ{
private:
	std::vector<Activitate> v;
	//UI& ui;*/
	Cos& cos;
public:
	draw(Cos& c) :cos{ c } {
		cos.Subscribe(this);
		v = cos.getCurent();
	}

	void Notify() override {
		// update v
		v = cos.getCurent();
		repaint();
	}

	void paintEvent(QPaintEvent* ev)override{
		QPainter p{this};
		int x=0, y=20, h=30, w=30;
		for (const auto& a : v) {
			int val = rand() % 5;
			switch (val) {
			case 0:
				p.drawRect(x, y, w, h);
				break;
			case 1:
				p.drawEllipse(x, y, w, h);
				break;
			case 2:
				p.drawPie(x, y, w, h, 30 * 16, 120 * 16);
				break;
			case 3:
				p.drawArc(x, y, w, h, 30 * 16, 120 * 16);
				break;
			case 4:
				p.drawEllipse(x, y, w + 5, h);
				break;
			}
			x += 40;
			if (x>sqrt(v.size())*40) {
				y += 50;
				x = 0;
			}
		}
	}
};
//fereastra care trebuie desenata sa se deseneze in functie de matrice patratica in care fiecare element este o figura geometrica random
//minim 5 variante
void UI::CosRO() {
	draw*p = new draw(serv.getCos());
	p->show();
}

#include "CosLV.h"
void UI::cosLV() {
	CosLV* cos = new CosLV(serv.getCos());
	cos->show();
}

void UI::ConnectSignals()
{
	try {

		QObject::connect(WindowFields, &QPushButton::clicked, this, [&]() {	window2->show(); });
		QObject::connect(close, &QPushButton::clicked, this, QApplication::quit);
		QObject::connect(add, &QPushButton::clicked, this, &UI::adaugare);
		QObject::connect(update, &QPushButton::clicked, this, &UI::modificare);
		QObject::connect(listaa, &QListView::clicked, this, &UI::getDetails);
		QObject::connect(remove, &QPushButton::clicked, this, &UI::removeF);
		QObject::connect(Sort, &QPushButton::clicked, this, &UI::sort);
		QObject::connect(filter, &QPushButton::clicked, this, &UI::Filter);
		QObject::connect(undo, &QPushButton::clicked, this, &UI::doUndo);
		QObject::connect(golesteCos, &QPushButton::clicked, this, &UI::golesteCosul);
		QObject::connect(adaugaInCos, &QPushButton::clicked, this, &UI::adaugaCos);
		QObject::connect(genereazaCos, &QPushButton::clicked, this, &UI::genereazaCosul);
		QObject::connect(histogramaB, &QPushButton::clicked, this, &UI::hist);
		QObject::connect(cosCRUD, &QPushButton::clicked, this, &UI::CosCRUD);
		QObject::connect(COSRO, &QPushButton::clicked, this, &UI::CosRO);
		QObject::connect(cosList, &QPushButton::clicked, this, &UI::cosLV);
		//QObject::connect(golCos, &QPushButton::clicked, this, &UI::golesteCosul);
		//QObject::connect(genCos, &QPushButton::clicked, this, &UI::GenCos);

	}
	catch (ValidareErr &e) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString(e.getMessage()));
		msg.exec();
	}
	catch (RepoError &e) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString(e.getMessage()));
		msg.exec();
	}
	catch (...) {
		QMessageBox msg;
		msg.setWindowTitle("Alerta");
		msg.setText(QString::fromStdString("S-a produs o eroare / durata introdusa nu este valida"));
		msg.exec();
	}
}
