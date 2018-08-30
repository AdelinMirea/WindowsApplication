#include "Activitate.h"

void Activitate::setTitlu(const std::string & titlu)
{
	this->titlu = titlu;
}

void Activitate::setDescriere(const std::string & descriere)
{
	this->descriere = descriere;
}

void Activitate::setTip(const std::string & tip)
{
	this->tip = tip;
}

void Activitate::setDurata(int durata)
{
	this->durata = durata;
}

std::string Activitate::getTitlu() const
{
	return this->titlu;
}

std::string Activitate::getDescriere() const
{
	return this->descriere;
}

std::string Activitate::getTip() const
{
	return this->tip;
}

int Activitate::getDurata() const
{
	return this->durata;
}

