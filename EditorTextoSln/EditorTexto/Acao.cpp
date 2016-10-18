#include "stdafx.h"
#include "Acao.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------CONSTRUTORES/DESTRUTOR--------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao::Acao(String &novaPalavra, String &novoTipo, unsigned int novoX, unsigned int novoY) : palavraMudou(novaPalavra), tipo(novoTipo), X(novoX), Y(novoY)
{
	this->palavraMudou = novaPalavra;
	this->tipo = novoTipo;
	this->X = novoX;
	this->Y = novoY;
}

Acao::Acao(const Acao &original) : palavraMudou(original.palavraMudou), tipo(original.tipo), X(original.X), Y(original.Y)
{
	this->palavraMudou = original.palavraMudou;
	this->tipo = original.tipo;
	this->X = original.X;
	this->Y = original.Y;
}

Acao::Acao() : palavraMudou(), tipo(), X(0), Y(0)
{

}

Acao::~Acao()
{
	delete this;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------CONSTRUTORES DE CÓPIA---------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao* Acao::clone() const
{
	return new Acao(*this);
}

void Acao::operator= (Acao *primeira) const
{
	primeira = this->clone();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------GETTERS E SETTERS-----------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

String Acao::getPalavra() const
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

void Acao::setPalavra(String &novaPalavra)
{
	this->palavraMudou = novaPalavra;
}

void Acao::setTipo(String &novoTipo)
{
	this->tipo = novoTipo;
}

void Acao::setX(unsigned int novoX)
{
	this->X = novoX;
}

void Acao::setY(unsigned int novoY)
{
	this->Y = novoY;
}

Acao Acao::acaoNull()
{
	Acao *acao = NULL;
	return *acao;
}

