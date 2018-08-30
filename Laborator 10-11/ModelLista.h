#pragma once
#include <QAbstractListModel>
#include "Activitate.h"
#include "service.h"
#include "repo.h"
#include "vector"
using std::vector;

class ListModel : public QAbstractListModel {
private:
	vector<Activitate> activitati;
public:
	ListModel(const vector<Activitate>& act) : activitati{ act } {}
	
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return activitati.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			auto act = activitati[index.row()].getTitlu();
			return QString::fromStdString(act);
		}
		return QVariant();
	}
	void setActivitati(const vector<Activitate>& a) {
		activitati = a;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), 1);
		emit dataChanged(topLeft, bottomRight);
	}
};
