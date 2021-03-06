#include "stdafx.h"
#include "Acao.h"
#include "String.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------CONSTRUTORES/DESTRUTOR--------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao::Acao(const String *novasLinhas, const String &novoTipo, const unsigned int *novoPosY, const unsigned int novoTam, const unsigned int novoPosX) : tipo(novoTipo), tamanho(novoTam), posX(novoPosX)
{
	this->aloca(novasLinhas, novoPosY, novoTam);
}

Acao::Acao(const String &novaLinha, const String &novoTipo, const unsigned int novoPosY, const unsigned int novoPosX) : tipo(novoTipo), posX(novoPosX), tamanho(1)
{
	this->palavraMudou = new String(novaLinha);
	this->posY = (unsigned int*)malloc(sizeof(unsigned int));
	this->setPosY(novoPosY, 0);
}

Acao::Acao(const Acao &original) : tipo(original.tipo), tamanho(original.tamanho), posX(original.posX)
{
	this->aloca(original.palavraMudou, original.posY, original.tamanho);
}

Acao::Acao() : posX(0), tamanho(1)
{
	this->palavraMudou = new String("");
	this->tipo = String("");
	this->posY = (unsigned int*)malloc(sizeof(unsigned int));
	this->setPosY(0, 0);
}

Acao::~Acao()
{
//	free(this->palavraMudou);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------CONSTRUTORES DE C�PIA---------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao* Acao::clone()
{
	return new Acao(*this);
}

void Acao::operator= (const Acao& primeira)
{
	int i = this->tamanho;
	this->tamanho = primeira.tamanho;
	this->posY = primeira.posY;
	this->tipo = primeira.tipo;
	this->posX = primeira.posX;

	if (this->tamanho != 1 && i > 0)
	{
		free(this->palavraMudou);
		free(this->posY);
	}
	this->aloca(primeira.palavraMudou, primeira.posY, primeira.tamanho);
}

int Acao::ehMesmoTipo(const Acao& outra) const
{
	if (this->tipo == outra.tipo) return 1;
	return 0;
}

Acao operator+ (const Acao& primeiro, const Acao& segundo)
{
	Acao a = Acao();
	if (segundo.tipo == primeiro.tipo)
	{
		string txt = string();
		for (int i = 0; i < primeiro.getTamanho(); i++)
			txt = txt + primeiro.getString(i).toString();

		for (int i = 0; i < segundo.getTamanho(); i++)
			txt = txt + segundo.getString(i).toString();

		a = Acao(String(txt), segundo.getTipo(), primeiro.getPosY(0), segundo.getPosX());
	}
	return a;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------GETTERS E SETTERS-----------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

String* Acao::getString() const
{
	return this->palavraMudou;
}

String Acao::getString(const unsigned int pos) const
{
	return *(this->palavraMudou + pos);
}

String Acao::getTipo() const
{
	return this->tipo;
}

unsigned int Acao::getPosX() const
{
	return this->posX;
}

unsigned int* Acao::getPosY() const
{
	return this->posY;
}

unsigned int Acao::getPosY(const unsigned int pos) const
{
	return *(this->posY + pos);
}

unsigned int Acao::getTamanho() const
{
	return this->tamanho;
}

void Acao::setString(const String &novaLinha, const unsigned int pos)
{
	*(this->palavraMudou + pos) = novaLinha;
}

void Acao::setString(const char *novaLinha, const unsigned int pos)
{
	*(this->palavraMudou + pos) = String(novaLinha);
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

void Acao::setPosX(const unsigned int novoPosX)
{
	this->posX = novoPosX;
}

void Acao::setPosY(const unsigned int* novoPosY)
{
	free(this->posY);
	this->posY = (unsigned int*)malloc(this->tamanho * sizeof(unsigned int));
	for (int i = 0; i < this->tamanho; i++)
		*(this->posY + i) = *(novoPosY + i);
}

void Acao::setPosY(const unsigned int novoPosY, const unsigned int pos)
{
	*(this->posY + pos) = novoPosY;
}

void Acao::setTamanho(const unsigned int novoTam)
{
	if (novoTam < this->tamanho) throw "Tamanho Inv�lido";
	this->tamanho = novoTam;
	realloc(this->palavraMudou, this->tamanho);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------M�TODOS AUXILIARES-----------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------------------------------------//

void Acao::deletarTudo()
{
	if (palavraMudou->length() < 0 || tipo.length() < 0) return;
	this->palavraMudou->deletarTudo();
	this->tipo.deletarTudo();
	this->posY = 0;
	this->posX = 0;
}

void Acao::aloca(const String *novasString, const unsigned int *novoPosY, unsigned int novoTam, unsigned int ehStr, unsigned int ehLinhas)
{
	if (novoTam == 1)
	{
		this->palavraMudou = new String("");
		*this->palavraMudou = *novasString;
		this->posY = (unsigned int*)malloc(sizeof(unsigned int));
		this->setPosY(*novoPosY, 0);
	}

	else
	{
		if (ehStr > 0)
		{
			this->palavraMudou = new String[novoTam]();
			for (int i = 0; i < novoTam; i++)
				*(this->palavraMudou + i) = String("");
			for (int i = 0; i < novoTam; i++)
				*(this->palavraMudou + i) = *(novasString + i);
		}
		if (ehLinhas > 0)
		{
			this->posY = (unsigned int*)malloc(novoTam * sizeof(unsigned int));
			for (int i = 0; i < novoTam; i++)
				*(this->posY + i) = *(novoPosY + i);
		}
	}
}


String Acao::toString() const
{
	String txt = String(), numbs = String();
	for (int i = 0; i < this->tamanho; i++)
	{
		txt = txt + *(this->palavraMudou + i);
	}
	return String((String)txt + (string)" " + this->tipo + (string)" " + (int)this->tamanho + (string)" " + (int)this->posY);
}