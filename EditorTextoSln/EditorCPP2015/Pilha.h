#pragma once
using namespace std;
#include "NoLista.h"

template <class Tipo>
class Pilha
{
public:
	// ------------------------------------------------------------------------------------------------------------------------------------------------------ -//
	//-------------------------------------------------------------CONSTRUTORES/DESTRUTOR--------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//

	Pilha(const unsigned int novoTamanhoMax) : tamanhoMax(novoTamanhoMax), tamanhoAtual(0)
	{
		NoLista<Tipo> *pont = (NoLista<Tipo>*)malloc(novoTamanhoMax * sizeof(NoLista<Tipo>));
		for (int i = 0; i < novoTamanhoMax; i++)
			*(pont + i) = NoLista<Tipo>();
		this->alocaNo(pont, novoTamanhoMax);
	}

	Pilha(const Pilha<Tipo> &original) : tamanhoMax(original.tamanhoMax), tamanhoAtual(original.tamanhoAtual)
	{
		this->alocaNo(original.nos, original.tamanhoMax);
	}

	Pilha() : tamanhoMax(1), tamanhoAtual(0)
	{
		this->alocaNo(new NoLista<Tipo>(), 1);
	}

	~Pilha()
	{
		free(this->nos);
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//--------------------------------------------------------------CONSTRUTORES DE C�PIA--------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//

	Pilha<Tipo>* clone() const
	{
		return new Pilha<Tipo>(*this);
	}

	void operator= (Pilha<Tipo> *primeira) const
	{
		primeira = this->clone();
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------------------------------M�TODOS PRINCIPAIS---------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//

	NoLista<Tipo> empilhar(const Tipo& feita)
	{
		if (&feita == NULL) throw "A��o Inv�lida";

		NoLista<Tipo> no = NoLista<Tipo>(feita);
		if (this->ehCheia())
		{
			NoLista<Tipo> acc = *(this->nos + 0);
			for (int i = 0; i < this->tamanhoAtual; i++)
				*(this->nos + i) = *(this->nos + (i + 1));
			this->tamanhoAtual--;
			this->empilhar(feita);
			return acc;
		}

		*(this->nos + this->tamanhoAtual++) = no;
		return NoLista<Tipo>();
	}

	NoLista<Tipo> desempilhar()
	{
		if (this->ehVazia()) throw "Pilha Vazia";
		return *(this->nos + --this->tamanhoAtual);
	}

	bool ehCheia() const
	{
		return this->tamanhoAtual >= this->tamanhoMax;
	}

	bool ehVazia() const
	{
		return this->tamanhoAtual <= 0;
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//---------------------------------------------------------------GETTERS E SETTERS-----------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//

	NoLista<Tipo> getTopo() const
	{
		return *(this->nos + this->tamanhoAtual - 1);
	}

	int length() const
	{
		return this->tamanhoAtual;
	}

	String toString() const
	{
		String txt = String();
		for (int i = 0; i < this->tamanhoAtual; i++)
			txt = txt + (this->nos + i)->getDado()->toString();
		return String(txt + " " + (int)this->tamanhoAtual + " " + (int)this->tamanhoMax + "\n");
	}
protected:
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------------------------------M�TODOS AUXILIARES---------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	NoLista<Tipo> valorDe(const int &indice) const
	{
		return *(this->acoes + indice);
	}

	void alocaNo(const NoLista<Tipo> *novoNo, const unsigned int tam)
	{
		this->nos = (NoLista<Tipo>*)malloc(tam * sizeof(NoLista<Tipo>));
		for (int i = 0; i < tam; i++)
			*(this->nos + i) = *(novoNo + i);
	}
private:
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//-------------------------------------------------------------------ATRIBUTOS---------------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	NoLista<Tipo> *nos;
	unsigned int tamanhoMax, tamanhoAtual;
};
