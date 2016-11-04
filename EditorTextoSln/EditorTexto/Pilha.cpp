#include "stdafx.h"
#include "Pilha.h"
#include "Acao.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------CONSTRUTORES/DESTRUTOR--------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Pilha::Pilha(const unsigned int novoTamanhoMax) :tamanhoMax(novoTamanhoMax), tamanhoAtual(0)
{
	//Acao* a = (Acao*)malloc((novoTamanhoMax + 1) * sizeof(Acao));
	this->acoes = (Acao*)malloc((novoTamanhoMax + 1) * sizeof(Acao));
}

Pilha::Pilha(const Pilha &original) : tamanhoMax(original.tamanhoMax), tamanhoAtual(original.tamanhoAtual), acoes(original.acoes)
{
	this->tamanhoMax = original.tamanhoMax;
	for (int i = 0; i < original.tamanhoAtual; i++)
		this->empilhar(original.valorDe(i));
}

Pilha::~Pilha()
{
	free(this->acoes);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------CONSTRUTORES DE C�PIA--------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Pilha* Pilha::clone() const
{
	return new Pilha(*this);
}

void Pilha::operator= (Pilha *primeira) const
{
	primeira = this->clone();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------M�TODOS PRINCIPAIS---------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao Pilha::empilhar(const Acao& feita)
{
	if (&feita == NULL) throw "A��o Inv�lida";
	if (this->ehCheia())
	{
		Acao acc = *(this->acoes + 0);
		for (int i = 0; i < this->tamanhoAtual; i++)
			*(this->acoes + i) = *(this->acoes + (i + 1));
		this->empilhar(feita);
		return acc;
	}

	this->inserir(feita);
	static Acao a = Acao();
	return a;
}

void Pilha::inserir(const Acao& feita)
{
	(this->acoes + this->tamanhoAtual)->setPalavra(*feita.getPalavra());
	(this->acoes + this->tamanhoAtual)->setTipo(feita.getTipo());
	(this->acoes + this->tamanhoAtual)->setX(feita.getX());
	(this->acoes + this->tamanhoAtual++)->setY(feita.getY());
}

Acao Pilha::desempilhar()
{
	if (this->ehVazia()) throw "Pilha Vazia";
	return *(this->acoes + this->tamanhoAtual--);
}

bool Pilha::ehCheia() const
{
	return this->tamanhoAtual >= this->tamanhoMax;
}

bool Pilha::ehVazia() const
{
	return this->tamanhoAtual <= this->tamanhoMax;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------M�TODOS AUXILIARES---------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao Pilha::valorDe(const int &indice) const
{
	return *(this->acoes + indice);
}

Acao Pilha::getTopo() const
{
	return *(this->acoes + this->tamanhoAtual);
}

int Pilha::length() const
{
	return this->tamanhoAtual;
}

