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
tamanhoMax(1024), tamanho(0)
{
	this->minhaString = new char[1025]();
}

String::String(const char* original)
{
	String aux;
	for (int i = 0; original[i] != '\0'; i++)
		aux.inserir(original[i]);
	*this = aux; // utilizando o operator
}

String::String(const string &novaString) : 
tamanhoMax((novaString.size() <= 512) ? 1024 : novaString.size()*2), tamanho(novaString.size())
{
	this->minhaString = new char[this->getTamanhoMax() + 1]();
	int i = 0;
	for (i = 0; i < novaString.length(); i++)
		this->minhaString[i] = (char)novaString.at(i);
	this->minhaString[i] = (char)String::charNull;
}


String::String(const int &n,char novaString[]) :
tamanhoMax((n <= 1024) ? 1024 : n), tamanho(n)
{
	this->minhaString = new char[this->getTamanhoMax() + 1]();
	int i = 0;
	for (i = 0; i < n; i++)
		this->minhaString[i] = (char)novaString[i];
	this->minhaString[i] = (char)String::charNull;
}

String::~String()
{
	//this->minhaString[this->length() - 1] = '\0';
	//delete minhaString;
}

// Métodos normais
String::String(const unsigned int &novoTamanhoMax) : 
tamanhoMax(novoTamanhoMax), tamanho(0)
{
	this->minhaString = new char[novoTamanhoMax + 1]();
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

} // "rrr"   --  ""

void String::deletarTudo()
{
	this->minhaString = NULL;
	this->minhaString = new char[this->tamanhoMax+1]();
	this->tamanho = 0;
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

char& String::operator[] (const int &indice) const
{
	static char nulao = char('\0');
	if (indice < 0 || indice > this->tamanho - 1) // index out of bounds
		return nulao;

	return this->minhaString[indice];
}

// operators
void String::operator= (const String &primeira)
{
	this->tamanhoMax = primeira.getTamanhoMax();
	this->deletarTudo();
	for (int i = 0; i <= primeira.length(); i++)
		this->inserir(primeira[i]);
}

String operator+ (const String &th, const String &outra)
{
	char *arrai = new char[th.tamanho + outra.length() + 2]();
	int i = 0;

	for (i = 0; i < th.length(); i++)
		arrai[i] = (char)th.minhaString[i];

	int u = 0;
	for (i = th.length(); i < th.length() + outra.length(); i++, u++)
		arrai[i] = (char)outra[u];

	arrai[i] = String::charNull;

	String ret = String(i, arrai);
	delete[] arrai;

	return ret;
}

String operator+ (const String &th, const string &outra)
{
	char *arrai = new char[th.tamanho + outra.length() + 1]();

	int i = 0;

	for (i = 0; i < th.tamanho + 1; i++)
		arrai[i] = (char)th.minhaString[i];

	int u = 0;
	for (i = th.tamanho; i < th.tamanho + outra.length(); i++, u++)
		arrai[i] = (char)outra.at(u);

	arrai[i] = String::charNull;
	String ret = String(i, arrai);
	delete[] arrai;

	return ret;
}

String operator+ (const String &th, const char &outra)
{
	char *arrai = new char[th.tamanho + 2]();
	int i;
	for (i = 0; i < th.tamanho; i++)
		arrai[i] = (char)th.minhaString[i];
	arrai[i] = outra;
	arrai[i+1] = String::charNull;
	String ret = String(i+1, arrai);
	delete[] arrai;
	return ret;
}

String operator+ (const String &th, const int &outra)
{
	string intEmStr = to_string(outra);

	char *arrai = new char[th.tamanho + intEmStr.length() + 1]();

	int i = 0;
	for (i = 0; i < th.tamanho; i++)
		arrai[i] = (char)th.minhaString[i];

	int u = 0;
	for (i = th.tamanho; i < th.tamanho + intEmStr.length(); i++, u++)
		arrai[i] = (char)intEmStr.at(u);

	arrai[i] = String::charNull;
	String ret = String(i, arrai);
	delete[] arrai;
	return ret;
}

String operator+ (const String &th, const char* &outra)
{
	string charEmStr = outra;
	String ret = th + charEmStr;
	return ret;
}

String operator+ (const std::string &outra, const String &th)
{
	char *arrai = new char[th.tamanho + outra.length() + 1]();

	int i = 0;

	for (i = 0; i < outra.size(); i++)
		arrai[i] = (char)outra.at(i);

	int u = 0;
	for (i = outra.size(); i < th.tamanho + outra.size(); i++, u++)
		arrai[i] = (char)th.minhaString[u];

	arrai[i] = String::charNull;
	String ret = String(i, arrai);
	delete[] arrai;

	return ret;
}

String operator+ (const char &outra, const String &th)
{
	char *arrai = new char[th.tamanho + 2]();
	int i;
	arrai[0] = outra;
	for (i = 1; i < th.tamanho+1; i++)
		arrai[i] = (char)th.minhaString[i-1];
	arrai[i] = String::charNull;
	String ret = String(i, arrai);
	delete[] arrai;
	return ret;
}

String operator+ (const char* &outra, const String &th)
{
	string charEmStr = outra;
	String ret = charEmStr + th;
	return ret;
}

String operator+ (const int &outra, const String &th)
{
	string intEmStr = to_string(outra);

	char *arrai = new char[th.tamanho + intEmStr.length() + 1]();

	int i = 0;
	for (i = 0; i < th.tamanho; i++)
		arrai[i] = (char)intEmStr.at(i);

	int u = 0;
	for (i = th.tamanho; i < th.tamanho + intEmStr.length(); i++, u++)
		arrai[i] = (char)th.minhaString[i];

	arrai[i] = String::charNull;
	String ret = String(i, arrai);
	delete[] arrai;
	return ret;
}

String operator+ (const String &th, const char* outra)
{
	string charEmStr = outra;
	String ret = th + charEmStr;
	return ret;
}

String operator+ (const char* outra, const String &th)
{
	string charEmStr = outra;
	String ret = charEmStr + th;
	return ret;
}


String::operator char*() const
{
	static char *ret = new char[this->tamanho+1]();
	for (int i = 0; i < this->tamanho; i++)
		ret[i] = (char)this->minhaString[i];
	ret[this->tamanho] = String::charNull;
	return ret;
}

String::operator const char*() const
{
	static char *ret = new char[this->tamanho + 1]();
	for (int i = 0; i < this->tamanho; i++)
		ret[i] = (char)this->minhaString[i];
	ret[this->tamanho] = String::charNull;
	return ret;
}

String::operator string() const
{
	string ret = string();
	for (int i = 0; i < this->tamanho; i++)
		ret.push_back((char)this->minhaString[i]);
	return ret;
}

ostream& operator<< (ostream &OS, const String &aString)
{
	if (aString.vazia())
		return OS;

	char *pont = new char[aString.length()]();
	for (int i = 0; i < aString.length(); i++)
	{
		pont[i] += (char)aString.minhaString[i];
	}

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

bool operator< (const String &pri, const String &seg)
{
	return pri.length() < seg.length();
}

bool operator> (const String &pri, const String &seg)
{
	return pri.length() > seg.length();
}

bool operator<= (const String &pri, const String &seg)
{
	return pri.length() <= seg.length();
}

bool operator>= (const String &pri, const String &seg)
{
	return pri.length() >= seg.length();
}

bool operator== (const String &pri, const String &seg) // verificar conteúdo também
{
	if (pri.length() != seg.length())
		return false;

	for (int i = 0; i < pri.tamanho; i++)
	{
		if (pri[i] != seg[i])
			return false;
	}
	return true;
}

bool operator!= (const String &pri, const String &seg) // verificar conteúdo também
{
	if (pri.length() != seg.length())
		return true;

	for (int i = 0; i < pri.tamanho; i++)
	{
		if (pri[i] != seg[i])
			return true;
	}
	return false;
}

bool operator< (const String &pri, const char* seg)
{
	int i = 0;
	for (i = 0; seg[i] != String::charNull; i++)
	{}
	return pri.length() < i;
}

bool operator> (const String &pri, const char* seg)
{
	int i = 0;
	for (i = 0; seg[i] != String::charNull; i++)
	{
	}
	return pri.length() > i;
}

bool operator<= (const String &pri, const char* seg)
{
	int i = 0;
	for (i = 0; seg[i] != String::charNull; i++)
	{
	}
	return pri.length() <= i;
}

bool operator>= (const String &pri, const char* seg)
{
	int i = 0;
	for (i = 0; seg[i] != String::charNull; i++)
	{
	}
	return pri.length() >= i;
}

bool operator== (const String &pri, const char* seg) // verificar conteúdo também
{
	int i = 0;
	for (i = 0; seg[i] != String::charNull; i++)
	{
	}
	if (pri.length() != i)
		return false;

	for (int i = 0; i < pri.tamanho; i++)
	{
		if (pri[i] != seg[i])
			return false;
	}
	return true;
}

bool operator!= (const String &pri, const char* seg) // verificar conteúdo também
{
	int i = 0;
	for (i = 0; seg[i] != String::charNull; i++)
	{
	}
	if (pri.length() != i)
		return true;

	for (int i = 0; i < pri.tamanho; i++)
	{
		if (pri[i] != seg[i])
			return true;
	}
	return false;
}