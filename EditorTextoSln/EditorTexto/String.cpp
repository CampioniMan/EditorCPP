#include "stdafx.h"
#include "String.h"
#include "stdio.h"
#include <string>
using namespace std;

String::String(const String &original) : 
tamanho(original.length()), tamanhoMax(original.getTamanhoMax())
{
	this->minhaString = new char[original.getTamanhoMax()]();
	this->minhaString = original.toString();
}

String::String() : 
tamanhoMax(256), tamanho(0), minhaString(new char[257]())
{

}

String::String(const string &novaString) : 
tamanhoMax((novaString.length()<=256)?256:novaString.length()), tamanho(novaString.length()), minhaString(new char[this->getTamanhoMax()+1]())
{
	int i = 0;
	for (i = 0; i < novaString.length(); i++)
		this->minhaString[i] = (char)novaString.at(i);
	this->minhaString[i] = (char)String::charNull;
}

String::~String()
{
	//delete[] minhaString;
}

// Métodos normais
String::String(const unsigned int &novoTamanhoMax) : 
tamanhoMax(novoTamanhoMax), tamanho(0), minhaString(new char[novoTamanhoMax + 1]())
{

}

void String::deleteCharAt(const unsigned int &posicao)
{
	if (posicao < 0 || posicao > this->tamanhoMax || this->vazia()) // não pode ser menor que 0
		return;

	for (int i = posicao; i < this->length() - 1;i++) // mexendo, de posicao pra frente, 1 para trás
		this->minhaString[i] = (char)this->minhaString[i+1];

	this->minhaString[this->length() - 1] = charNull; // deixando o último nulo
	this->tamanho--;
}

void String::deletar(unsigned int posIni, unsigned int qtos)
{
	if (posIni < 0 || posIni >= this->tamanho || qtos < 0 || qtos > this->length() - 1 || this->vazia())
		return;

	for (int i = posIni; i + qtos < this->length(); i++) // mexendo, de posicao pra frente, 1 para trás
		this->minhaString[i] = (char)this->minhaString[i + qtos];

	for (int i = qtos; i < this->length(); i++) // deixando os últimos nulos
		this->minhaString[i] = this->charNull;
	this->tamanho -= qtos;

}

bool String::cheia() const
{
	return (this->tamanho >= this->tamanhoMax);
}

bool String::vazia() const
{
	return (this->tamanho == 0);
}

void String::inserir(const char &letra, const unsigned int &posicao)
{
	if (cheia() || posicao > this->tamanhoMax && posicao < 0)
		return;

	for (int i = this->tamanho; i >= posicao; i--)
	{
		this->minhaString[i + 1] = this->minhaString[i];
	}
	this->minhaString[posicao] = (char)letra;
	this->tamanho++;
}

// trtretgre tre
void String::inserir(const char &letra)
{
	if (cheia())
		return;

	this->minhaString[this->tamanho] = letra;
	this->minhaString[this->tamanho+1] = String::charNull;
	this->tamanho++;
}

// Apocalipticos
char* String::toString() const
{
	char* pont = new char[this->length()+1]();

	if (this->vazia())
		return pont;

	for (int i = 0; i < this->length(); i++)
		pont[i] = (char)this->minhaString[i];

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
	if (indice < 0 || indice > this->tamanho - 1) // index out of bounds
		return (char(this->charNull));

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

bool String::operator< (const String &outra)
{
	return this->length() < outra.length();
}

bool String::operator> (const String &outra)
{
	return this->length() > outra.length();
}

bool String::operator<= (const String &outra)
{
	return this->length() <= outra.length();
}

bool String::operator>= (const String &outra)
{
	return this->length() >= outra.length();
}

bool String::operator== (const String &outra) // verificar conteúdo também
{
	return this->length() == outra.length();
}

bool String::operator!= (const String &outra) // verificar conteúdo também
{
	return this->length() != outra.length();
}

ostream& operator<< (ostream &OS, const String &aString)
{
	if (aString.vazia())
		return OS;

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