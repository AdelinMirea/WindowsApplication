#include "UI.h"
#include <QtWidgets/QApplication>

#include "UI.h"
#include <qpushbutton.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "service.h"
#include "repo.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Repository repo;
	Service serv(repo);
	UI w(serv);
	
	//w.show();
	return a.exec();
}
