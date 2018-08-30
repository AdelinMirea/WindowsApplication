#pragma once
#include <String>

class Activitate {
public:
	Activitate() = default;

	/*
	constructor clasa
	input: titlu, desctiere, tip, durata

	*/
	Activitate(std::string titlu, std::string descriere, std::string tip, int durata) {
		this->titlu = titlu;
		this->descriere = descriere;
		this->durata = durata;
		this->tip = tip;
	}

	/*
	set titlu 
	input: titlu
	*/
	void setTitlu(const std::string& titlu);

	/*
	set descriere
	input: descriere
	*/
	void setDescriere(const std::string& descriere);

	/*
	set tip
	input: tip
	*/
	void setTip(const std::string& tip);

	/*
	set durata
	input durata
	*/
	void setDurata(int durata);

	/*
	get titlu
	output: string titlu
	*/
	std::string getTitlu() const;
	
	/*
	get descriere
	output: string descriere
	*/
	std::string getDescriere() const;

	/*
	get tip
	output: string tip
	*/
	std::string getTip() const;
	
	/*
	get durata
	output: int durata
	*/
	int getDurata() const;

	bool operator==(Activitate other) {
		if (this->descriere == other.getDescriere() && this->durata == other.getDurata() && this->titlu == other.getTitlu() && this->tip == other.getTip()) {
			return true;
		}
		return false;
	}

	void operator=(Activitate other) {
		this->setDescriere(other.getDescriere());
		this->setDurata(other.getDurata());
		this->setTip(other.getTip());
		this->setTitlu(other.getTitlu());
	}

private:
	std::string titlu;
	std::string descriere;
	std::string tip;
	int durata;
};
