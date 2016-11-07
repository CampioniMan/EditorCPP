#include "stdafx.h"
#include "Pilha.h"
#include "Acao.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------CONSTRUTORES/DESTRUTOR--------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Pilha::Pilha(const unsigned int novoTamanhoMax) :tamanhoMax(novoTamanhoMax), tamanhoAtual(0)
{
	Acao* pont = (Acao*)malloc((novoTamanhoMax) * sizeof(Acao));
	for (int i = 0; i < novoTamanhoMax; i++)
		*(pont + i) = Acao();
	this->alocaPalavra(pont, novoTamanhoMax);
}

Pilha::Pilha(const Pilha &original) : tamanhoMax(original.tamanhoMax), tamanhoAtual(original.tamanhoAtual)
{
	this->alocaPalavra(original.acoes, original.tamanhoMax);
}

Pilha::Pilha() : tamanhoMax(1), tamanhoAtual(0)
{
	this->alocaPalavra(new Acao(), 1);
}

Pilha::~Pilha()
{
	free(this->acoes);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------CONSTRUTORES DE CÓPIA--------------------------------------------------------------------//
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
//----------------------------------------------------------------MÉTODOS PRINCIPAIS---------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao Pilha::empilhar(const Acao& feita)
{
	if (&feita == NULL) throw "Ação Inválida";
	if (this->ehCheia())
	{
		Acao acc = *(this->acoes + 0);
		for (int i = 0; i < this->tamanhoAtual; i++)
			*(this->acoes + i) = *(this->acoes + (i + 1));
		this->empilhar(feita);
		return acc;
	}

	*(this->acoes + this->tamanhoAtual++) = feita;
	return Acao();
}

Acao Pilha::desempilhar()
{
	if (this->ehVazia()) throw "Pilha Vazia";
	return *(this->acoes + --this->tamanhoAtual);
}

bool Pilha::ehCheia() const
{
	return this->tamanhoAtual >= this->tamanhoMax;
}

bool Pilha::ehVazia() const
{
	return this->tamanhoAtual <= 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------MÉTODOS AUXILIARES---------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao Pilha::valorDe(const int &indice) const
{
	return *(this->acoes + indice);
}

Acao Pilha::getTopo() const
{
	return *(this->acoes + this->tamanhoAtual-1);
}

int Pilha::length() const
{
	return this->tamanhoAtual;
}

void Pilha::alocaPalavra(const Acao *novaAcao, const unsigned int tam)
{
	this->acoes = (Acao*)malloc(tam * sizeof(Acao));
	for (int i = 0; i < tam; i++)
		*(this->acoes + i) = *(novaAcao + i);
}

String Pilha::toString() const
{
	String txt = String();
	for (int i = 0; i < this->tamanhoAtual; i++)
		txt = txt + (this->acoes + i)->toString();
	return String(txt + " " + (int)this->tamanhoAtual + " " + (int)this->tamanhoMax + "\n");
}