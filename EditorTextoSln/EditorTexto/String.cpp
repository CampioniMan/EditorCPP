#include "stdafx.h"
#include "String.h"
#include "stdio.h"
#include <string>
using namespace std;

String::String(const String &original) : minhaString(original.minhaString), tamanho(original.length()), tamanhoMax(original.getTamanhoMax())
{

}

String::String() : tamanhoMax(256), tamanho(0), minhaString(new char[257]())
{

}

String::String(const std::string &novaString) : tamanhoMax(novaString.length()), tamanho(novaString.length()), minhaString(new char[novaString.length() + 1]())
{
	for (int i = 0; i < novaString.length(); i++)
		minhaString[i] = novaString[i];
}

String::~String()
{
	//delete[] minhaString;
}

// Métodos normais
String::String(const unsigned int &novoTamanhoMax) : tamanhoMax(novoTamanhoMax), tamanho(0), minhaString(new char[novoTamanhoMax + 1]())
{

}

void String::deleteCharAt(const unsigned int &posicao)
{
	if (posicao < 0 || posicao > this->tamanhoMax || this->vazia()) // não pode ser menor que 0
		return;

	for (int i = posicao; i < this->length() - 1;) // mexendo, de posicao pra frente, 1 para trás
		this->minhaString[i] = this->minhaString[++i];

	this->minhaString[this->length() - 1] = charNull; // deixando o último nulo
	this->tamanho--;
}

void String::deletar(unsigned int posIni, unsigned int posFim)
{
	if (posIni < 0 || posIni >= this->tamanho || posFim < 0 || posFim > this->length() - 1 || this->vazia())
		return;

	if (posIni > posFim) // pode estar ao contrário
	{
		unsigned int aux = posIni;
		posIni = posFim;
		posFim = aux;
	}
	unsigned int diff = posFim - posIni;
	/*
	while (diff != 0)
	{
	deleteCharAt(posIni+diff);
	}
	*/
	for (int i = posIni; i + diff <= this->length(); i++) // mexendo, de posicao pra frente, 1 para trás
		this->minhaString[i] = this->minhaString[i + diff];

	for (int i = posFim; i <= this->length(); i++) // deixando os últimos nulos
		this->minhaString[posFim] = this->charNull;
	this->tamanho -= diff;

}

bool String::cheia() const
{
	return (this->tamanho >= this->tamanhoMax);
}

bool String::vazia() const
{
	return (this->tamanho == 0);
}

void String::inserir(const unsigned int &posicao, const char &letra)
{
	if (!cheia() && posicao > this->tamanhoMax && posicao < 0)
		return;

	if (this[posicao] == charNull)
	{
		for (int i = this->tamanho; i <= posicao; i++)
		{
			this[i + 1] = this[i];
		}
		this[posicao] = letra;
	}
	this->tamanho++;
}

void String::inserir(const char &letra)
{
	if (!cheia())
		return;

	this->minhaString[this->tamanho] = letra;
	this->tamanho++;
}

// Apocalipticos
char* String::toString() const
{
	char *pont = new char[this->length()]();
	for (int i = 0; i < this->length(); i++)
		pont[i] += (char)this->minhaString[i];
	return pont;
}

// getters e setters
int String::length() const
{
	return this->tamanho;
}

int String::getTamanhoMax() const
{
	return this->tamanhoMax;
}

char String::operator[] (const int &indice) const
{
	char* oi = new char(this->charNull);
	if (indice < 0 || indice > this->tamanho - 1)
		return (*oi);
	return this->minhaString[indice];
}

// operators
void String::operator= (const String &primeira)
{
	this->deletar(0, this->length() - 1);
	for (int i = 0; i <= primeira.length(); i++)
	{
		this->inserir(primeira[i]);
	}
}

void String::operator+ (const String &outra)
{
	for (int i = 0; i <= outra.length(); i++)
	{
		this->inserir(this->tamanho, outra[i]);
	}
}

bool operator< (const String &primeira, const String &segunda)
{
	return primeira.length() < segunda.length();
}

bool operator> (const String &primeira, const String &segunda)
{
	return primeira.length() > segunda.length();
}

bool operator<= (const String &primeira, const String &segunda)
{
	return primeira.length() <= segunda.length();
}

bool operator>= (const String &primeira, const String &segunda)
{
	return primeira.length() >= segunda.length();
}

bool operator== (const String &primeira, const String &segunda) // verificar conteúdo também
{
	return primeira.length() == segunda.length();
}

bool operator!= (const String &primeira, const String &segunda) // verificar conteúdo também
{
	return primeira.length() != segunda.length();
}

ostream& operator<< (ostream &OS, const String &aString)
{
	char *pont = new char[aString.length()]();
	for (int i = 0; i < aString.length(); i++)
		pont[i] += (char)aString.minhaString[i];

	for (int i = 0; i < aString.length() - 1; i++) 
		OS << pont[i];
	return (OS << pont[aString.length() - 1]);
}

istream& operator>> (istream &IS, String &aString)
{
	char* lida = new char[aString.tamanhoMax];

	IS >> lida;

	String *aux = new String(lida);
	aString = *aux;

	return IS;
}