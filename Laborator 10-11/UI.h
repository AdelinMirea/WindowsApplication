#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Laborator1011.h"
#include <qpushbutton.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include "service.h"
#include "repo.h"
#include <vector>//--------
#include <qdialog.h>
#include <qslider.h>
#include <qpainter>
#include <qrect.h>	
#include "ModelLista.h"

class UI : public QMainWindow
{
	Q_OBJECT

public:
	UI() = default;
	UI(Service& service, QWidget *parent = Q_NULLPTR);
	/*UI(Service service, QWidget *parent = Q_NULLPTR) :serv{ service } {
		CreareUI();
		ConnectSignals();
		ui.setupUi(this);
	}*/


	Service& serv;
private:
	Ui::Laborator1011Class ui;

	QHBoxLayout* HorizontalLayout = new QHBoxLayout();
	QWidget* mainWindow = new QWidget();
	QWidget* LeftWindow = new QWidget();
	QVBoxLayout* VerticalLayout1 = new QVBoxLayout();
	QListWidget* lista = new QListWidget();
	QHBoxLayout* buttons1 = new QHBoxLayout();
	QWidget* buttonsLeft = new QWidget();
	QPushButton* remove = new QPushButton("Stergere");
	QPushButton* Sort = new QPushButton("Sortare");
	QWidget* RightWindow = new QWidget();
	QVBoxLayout* VerticalLayout2 = new QVBoxLayout();
	QFormLayout* fields = new QFormLayout();
	QWidget* textinput = new QWidget();
	QLabel* lblTitlu = new QLabel("Titlu: ");
	QLabel* lblDescriere = new QLabel("Descriere: ");
	QLabel* lblTip = new QLabel("Tip: ");
	QLabel* lblDurata = new QLabel("Durata: ");
	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtDescriere = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtDurata = new QLineEdit;
	QHBoxLayout* buttons2 = new QHBoxLayout();
	QWidget* row1 = new QWidget();
	QPushButton* add = new QPushButton("Adaugare");
	QPushButton* update = new QPushButton("Modificare durata");
	QPushButton* filter = new QPushButton("Filtrare");
	QPushButton* close = new QPushButton("Close");
	QLabel* ContinutLista = new QLabel("Continutul listei curente:");
	QWidget* WidgetListaCos = new QWidget;
	QVBoxLayout* ListaCosLayout = new QVBoxLayout();
	QLabel* ContinutCos = new QLabel("Continutul cosului:");
	QFormLayout* adaugareElementInCos = new QFormLayout;
	QLineEdit* txtCosTitlu = new QLineEdit;
	QPushButton* adaugaInCos = new QPushButton("Adauga in cos");
	QHBoxLayout* butoane2Cos = new QHBoxLayout();
	QWidget* row2 = new QWidget();
	QPushButton* golesteCos = new QPushButton("Goleste lista");
	QPushButton* genereazaCos = new QPushButton("Genereaza");
	QLineEdit* numarElementeGenerate = new QLineEdit;
	QWidget* window2 = new QWidget;
	QVBoxLayout* layoutNew = new QVBoxLayout();
	QHBoxLayout* layoutExportCos = new QHBoxLayout;
	QWidget* ExportCosWidget = new QWidget;
	QPushButton* undo = new QPushButton("Undo");
	QPushButton* exportCosHTML = new QPushButton("Export cos HTML");
	QPushButton* exportCosCSV = new QPushButton("Export cos CSV");
	QListWidget* flist = new QListWidget;
	QListView* flist2 = new QListView;
	ListModel* modelFilter = new ListModel(serv.getAll());
	QLineEdit* descriere = new QLineEdit;
	QLineEdit*tip = new QLineEdit;
	QWidget* historigramaw = new QWidget;
	QVBoxLayout* histL = new QVBoxLayout;
	QPushButton* WindowFields = new QPushButton("Campuri");
	QPushButton* cosCRUD = new QPushButton("Cos CRUD");
	QPushButton* COSRO = new QPushButton("Cos RO");
	QPushButton* histogramaB = new QPushButton("Histograma");
	QListWidget * listaElementeCos = new QListWidget();

	QListView* listaa = new QListView;
	ListModel* modelListaa = new ListModel(serv.getAll());

	QPushButton* cosList = new QPushButton("CosLV");

	void CreareUI();
	void ConnectSignals();
	void adaugare();
	void modificare();
	void getDetails(QModelIndex item);
	void removeF();
	void sort();
	void colour();
	void printList();
	void SortTitlu();
	void SortDescriere();
	void SortDurata();
	void Filter();	
	void filterDescriere();
	void filterTip();
	void doUndo();
	void golesteCosul();
	void adaugaCos();
	void genereazaCosul();
	void exportCSV();
	void exportHTML();
	void updateCos();
	void hist();
	void CosCRUD();
	void CosRO();
	void loadListaCos();
	void cosLV();
};

