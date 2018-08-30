#pragma once
#include <string>
#include <vector>
#include "Activitate.h"
/*
Scrie in fisierul fName lista de animale
in format Comma Separated Values
*/
void exportCVS(const std::string& fName, const std::vector<Activitate>& activitati);
/*
Scrie in fisierul fName lista de animale
in format HTML
*/
void exportHTML(const std::string& fName, const std::vector<Activitate>& activitati);