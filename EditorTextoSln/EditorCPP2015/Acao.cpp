#include "stdafx.h"
#include "Acao.h"
#include "String.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------CONSTRUTORES/DESTRUTOR--------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

Acao::Acao(const String *novasLinhas, const String &novoTipo, const unsigned int *novaLinhaOcorren, const unsigned int novoTam) : tipo(novoTipo), tamanho(novoTam)
{
	this->aloca(novasLinhas, novaLinhaOcorren, novoTam);
}

Acao::Acao(const String &novaLinha, const String &novoTipo, const unsigned int novaLinhaOcorren) : tipo(novoTipo)
{
	this->palavraMudou = (String*)malloc(sizeof(String));
	this->linhaOcorrencia = (unsigned int*)malloc(sizeof(unsigned int));

	this->setString(novaLinha, 0);
	this->setLinhaOcorrencia(novaLinhaOcorren, 0);
}

Acao::Acao(const Acao &original) : tipo(original.tipo), tamanho(original.tamanho)
{
	this->aloca(original.palavraMudou, original.linhaOcorrencia, original.tamanho);
}

Acao::Acao() : tipo(""), tamanho(1)
{
	this->palavraMudou = (String*)malloc(sizeof(String));
	this->linhaOcorrencia = (unsigned int*)malloc(sizeof(unsigned int));

	this->setString(String(""), 0);
	this->setLinhaOcorrencia(0, 0);
}

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
	int i = this->tamanho;
	this->tamanho = primeira.tamanho;
	this->linhaOcorrencia = primeira.linhaOcorrencia;
	this->tipo = primeira.tipo;

	if (this->tamanho != 1 && i > 0)
	{
		free(this->palavraMudou);
		free(this->linhaOcorrencia);
	}
	this->aloca(primeira.palavraMudou, primeira.linhaOcorrencia, primeira.tamanho);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------GETTERS E SETTERS-----------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------//

String* Acao::getString() const
{
	return this->palavraMudou;
}

String Acao::getTipo() const
{
	return this->tipo;
}

unsigned int* Acao::getLinhasOcorrencias() const
{
	return this->linhaOcorrencia;
}

unsigned int Acao::getLinhaOcorrencia(const unsigned int pos) const
{
	return *(this->linhaOcorrencia + pos);
}

unsigned int Acao::getTamanho() const
{
	return this->tamanho;
}

void Acao::setString(const String &novaLinha, const unsigned int pos)
{
	*(this->palavraMudou + pos) = novaLinha;
}

void Acao::setString(const string &novaLinha, const unsigned int pos)
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

void Acao::setLinhasOcorrencias(const unsigned int* novasLinhas)
{
	free(this->linhaOcorrencia);
	this->linhaOcorrencia = (unsigned int*)malloc(this->tamanho * sizeof(unsigned int));
	for (int i = 0; i < this->tamanho; i++)
		*(this->linhaOcorrencia + i) = *(novasLinhas + i);
}

void Acao::setLinhaOcorrencia(const unsigned int novoLinha, const unsigned int pos)
{
	*(this->linhaOcorrencia + pos) = novoLinha;
}

void Acao::setTamanho(const unsigned int novoTam)
{
	if (novoTam < this->tamanho) throw "Tamanho Inválido";
	this->tamanho = novoTam;
	realloc(this->palavraMudou, this->tamanho);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------MÉTODOS AUXILIARES-----------------------------------------------------------------------//
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
	this->linhaOcorrencia = 0;
}

void Acao::aloca(const String *novasLinhas, const unsigned int *novaLinhaOcorren, unsigned int novoTam, unsigned int ehStr, unsigned int ehLinhas)
{
	if (ehStr > 0)
	{
		this->palavraMudou = (String*)malloc(novoTam * sizeof(String));
		for (int i = 0; i < novoTam; i++)
			*(this->palavraMudou + i) = *(novasLinhas + i);
	}
	if (ehLinhas > 0)
	{
		this->linhaOcorrencia = (unsigned int*)malloc(novoTam * sizeof(unsigned int));
		for (int i = 0; i < novoTam; i++)
			*(this->linhaOcorrencia + i) = *(novaLinhaOcorren + i);
	}
}


String Acao::toString() const
{
	String txt = String(), numbs = String();
	for (int i = 0; i < this->tamanho; i++)
	{
		txt = txt + *(this->palavraMudou + i);
	}
	return String((String)txt + (string)" " + this->tipo + (string)" " + (int)this->tamanho + (string)" " + (int)this->linhaOcorrencia);
}