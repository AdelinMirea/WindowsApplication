#pragma once
#include "POSError.h"
class ValidareErr : public POSError {
public:
	ValidareErr(std::string message) : POSError(message) {}
};

class Validare
{
public:
	Validare() noexcept;
	void ValidareTitlu(std::string titlu);
	void ValidareDescriere(std::string descriere);
	void ValidareTip(std::string tip);
	void ValidareDurata(int durata);

private:

};

void Validare::ValidareTitlu(std::string titlu) {
	if (titlu == "") {
		throw ValidareErr("Titlul nu poate fi inexistent");
	}
}

void Validare::ValidareDescriere(std::string descriere) {
	if (descriere == "") {
		throw ValidareErr("Descrierea nu poate fi inexistenta");
	}}

void Validare::ValidareTip(std::string tip) {
	if (tip == "") {
		throw ValidareErr("Tipul nu poate fi inexistent");
	}
}

void Validare::ValidareDurata(int durata) {
	try {
		if (durata < 1) {
			throw ValidareErr("Durata nu poate fi negativa sau nula");
		}
	}
	catch(...){
		throw ValidareErr("Durata invalida");
	}
}

Validare::Validare() noexcept
{
}
