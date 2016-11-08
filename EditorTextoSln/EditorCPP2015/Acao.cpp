#include "stdafx.h"
#include "String.h"
#include "Acao.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------CONSTRUTORES/DESTRUTOR--------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao::Acao(const String *novaPalavra, unsigned int novoTam, const String &novoTipo, unsigned int novoX, unsigned int novoY) : tipo(novoTipo), X(novoX), Y(novoY), tamanho(novoTam)
{
	this->alocaPalavra(novaPalavra, novoTam);
}

Acao::Acao(const Acao &original) : tamanho(original.tamanho), tipo(original.tipo), X(original.X), Y(original.Y)
{
	this->alocaPalavra(original.palavraMudou, original.tamanho);
}

Acao::Acao() : tamanho(1), tipo(""), X(0), Y(0)
{
	this->alocaPalavra(new String(), 1);
}

Acao::~Acao()
{
	free(this->palavraMudou);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------CONSTRUTORES DE C�PIA---------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao* Acao::clone() const
{
	return new Acao(*this);
}

void Acao::operator= (const Acao& primeira)
{
	int i = this->tamanho;
	this->tamanho = primeira.tamanho;
	this->X = primeira.X;
	this->Y = primeira.Y;
	this->tipo = primeira.tipo;

	if (this->tamanho != 1 && i > 0)
		free(this->palavraMudou);
	this->alocaPalavra(primeira.palavraMudou, primeira.tamanho);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------GETTERS E SETTERS-----------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

String* Acao::getPalavra() const
{
	return this->palavraMudou;
}

String Acao::getTipo() const
{
	return this->tipo;
}

unsigned int Acao::getX() const
{
	return this->X;
}

unsigned int Acao::getY() const
{
	return this->Y;
}

unsigned int Acao::getTamanho() const
{
	return this->tamanho;
}

void Acao::setPalavra(const String &novaPalavra, const unsigned int pos)
{
	*(this->palavraMudou + pos) = novaPalavra;
}

void Acao::setPalavra(const string &novaPalavra, const unsigned int pos)
{
	*(this->palavraMudou + pos) = novaPalavra;
}

void Acao::setPalavra(const char *novaPalavra, const unsigned int pos)
{
	*(this->palavraMudou + pos) = String(novaPalavra);
}

void Acao::setFrase(const String &novoTipo)
{
	free(this->palavraMudou);
	this->palavraMudou = (String*)malloc(this->tamanho * sizeof(String));
	for (int i = 0; i < this->tamanho; i++)
		*(this->palavraMudou + i) = (novoTipo + i);
}

void Acao::setTipo(const String &novoTipo)
{
	this->tipo = novoTipo;
}

void Acao::setX(const unsigned int novoX)
{
	this->X = novoX;
}

void Acao::setY(const unsigned int novoY)
{
	this->Y = novoY;
}

void Acao::setTamanho(const unsigned int novoTam) 
{
	this->tamanho = novoTam;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------M�TODOS AUXILIARES-----------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao Acao::acaoNull()
{
	Acao *acao = NULL;
	return *acao;
}

void Acao::deletarTudo()
{
	if (palavraMudou->length() < 0 || tipo.length() < 0) return;
	this->palavraMudou->deletarTudo();
	this->tipo.deletarTudo();
	this->X = 0;
	this->Y = 0;
}

void Acao::alocaPalavra(const String *novaPalavra, const unsigned int tam)
{
	this->palavraMudou = (String*)malloc(tam * sizeof(String));
	for (int i = 0; i < tam; i++)
		*(this->palavraMudou + i) = *(novaPalavra + i);
}

String Acao::toString() const
{
	String txt = String();
	for (int i = 0; i < this->tamanho; i++)
		txt = txt + *(this->palavraMudou + i);
	return String((String)txt + (string)" " + this->tipo + (string)" " + (int)this->tamanho + (string)" " + (int)this->X + (string)" " + (int)this->Y);
}