#include "export.h"
#include "Activitate.h"
#include <fstream>
#include <string>
#include <vector>
#include "repo.h"
/*
Scrie in fisierul fName lista de animale
in format Comma Separated Values
*/
void exportCVS(const std::string& fName, const std::vector<Activitate>& activitati) {
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {		throw RepoError("Unable to open file:" + fName);
	}
	for (const auto& p : activitati) {
		out << p.getTitlu() << ",";
		out << p.getDescriere() << ",";
		out << p.getTip() << ",";
		out << p.getDurata() << std::endl;
	}
	out.close();
}
/*
Scrie in fisierul fName lista de animale
in format HTML
*/
void exportHTML(const std::string& fName, const std::vector<Activitate>& activitati) {
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {		throw RepoError("Unable to open file:" + fName);
	}
	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const auto& p : activitati) {
		out << "<tr>" << std::endl;
		out << "<td>" << p.getTitlu() << "</td>" << std::endl;
		out << "<td>" << p.getDescriere() << "</td>" << std::endl;
		out << "<td>" << p.getTip() << "</td>" << std::endl;
		out << "<td>" << p.getDurata() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();
}