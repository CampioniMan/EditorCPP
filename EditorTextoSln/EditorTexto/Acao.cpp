#include "stdafx.h"
#include "Acao.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------CONSTRUTORES/DESTRUTOR--------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao::Acao(const String *novaPalavra, const unsigned int novoTam, const String &novoTipo, const unsigned int novoX, const unsigned int novoY) : tipo(novoTipo), X(novoX), Y(novoY), tamanho(novoTam)
{
	this->palavraMudou = (String*)malloc(novoTam * sizeof(String));
	for (int i = 0; i < novoTam; i++)
		*(this->palavraMudou + i) = *(novaPalavra + i);
}

Acao::Acao(const Acao &original) : tamanho(original.tamanho), tipo(original.tipo), X(original.X), Y(original.Y)
{
	//free(this->palavraMudou);
	this->palavraMudou = (String*)malloc(original.tamanho * sizeof(String));
	for (int i = 0; i < original.tamanho; i++)
		*(this->palavraMudou + i) = *(original.palavraMudou + i);
}

Acao::Acao() : palavraMudou(NULL), tamanho(0), tipo(""), X(0), Y(0){}

Acao::~Acao()
{
	free(this->palavraMudou);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------CONSTRUTORES DE CÓPIA---------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao* Acao::clone() const
{
	return new Acao(*this);
}

void Acao::operator= (const Acao& primeira)
{
	*this = Acao(primeira);
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

String Acao::toString() const
{
	String txt = String();
	for (int i = 0; i < this->tamanho; i++)
	{
		txt = txt + this->palavraMudou[i];
	}
	return String(txt + " " + this->tipo + " " + (int)this->tamanho + " " + (int)this->X + " " + (int)this->Y);
}
