#include "stdafx.h"
#include "String.h"
#include "stdio.h"
#include <string>
using namespace std;

String::String(const String &original) : 
tamanho(original.length()), tamanhoMax(original.getTamanhoMax())
{
	this->minhaString = (char*)malloc((original.getTamanhoMax()+1) * sizeof(char));
	this->minhaString = original.toString();
	*(this->minhaString + this->tamanho) = String::charNull;
}

String::String() : 
tamanhoMax(78), tamanho(0)
{
	this->minhaString = (char*)malloc(79 * sizeof(char));
}

String::String(const int &novoTamanho) :
tamanhoMax(novoTamanho), tamanho(0)
{
	this->minhaString = (char*)malloc((novoTamanho+1) * sizeof(char));
}

String::String(const char* original) : tamanho(tamanhoDe(original)+1), tamanhoMax((tamanho <= 1024) ? 1024 : tamanho * 2)
{
	this->minhaString = (char*)malloc((this->tamanhoMax+1) * sizeof(char));
	int i;
	for (i = 0; i < tamanho; i++)
		*(this->minhaString + i) = *(original + i);
	*(this->minhaString + i) = String::charNull;
}

String::String(const char &caracter) : tamanho(1), tamanhoMax(512)
{
	this->minhaString = new char[513]();
    *(this->minhaString+0) = caracter;
	*(this->minhaString+1) = String::charNull;
}

String::String(const string &novaString) : 
tamanhoMax((novaString.size() <= 512) ? 1024 : novaString.size()*2), tamanho(novaString.size())
{
	this->minhaString = (char*)malloc((this->getTamanhoMax() + 1) * sizeof(char));
	int i = 0;
	for (i = 0; i < novaString.length(); i++)
		*(this->minhaString+i) = (char)novaString.at(i);
	*(this->minhaString+i) = (char)String::charNull;
}


String::String(const int &n,char novaString[]) :
tamanhoMax((n < 1024) ? 1024 : n * 2), tamanho(n)
{
	this->minhaString = (char*)malloc((this->getTamanhoMax() + 1) * sizeof(char));
	int i = 0;
	for (i = 0; i < n; i++)
		*(this->minhaString+i) = (char)*(novaString+i);
	*(this->minhaString+i) = (char)String::charNull;
}

String::~String()
{
	//free(minhaString);
}

// Métodos normais
String::String(const unsigned int &novoTamanhoMax) : 
tamanhoMax(novoTamanhoMax), tamanho(0)
{
	this->minhaString = (char*)malloc((novoTamanhoMax + 1) * sizeof(char));
}

char String::deleteCharAt(const unsigned int &posicao)
{
	if (posicao < 0 || posicao >= this->tamanho || this->vazia()) // não pode ser menor que 0 ou maior igual ao tamanho
		return String::charNull;

	char ret = *(this->minhaString + posicao);

	for (int i = posicao; i < this->length() - 1;i++) // mexendo, de posicao pra frente, 1 para trás
		*(this->minhaString+i) = (char)*(this->minhaString + i+1);

	*(this->minhaString + this->length() - 1) = String::charNull; // deixando o último nulo
	this->tamanho--;
	return ret;
}

String String::deletar(unsigned int posIni, unsigned int qtos)
{
	if (posIni < 0 || posIni >= this->tamanho || qtos <= 0 || qtos > this->length() - 1 || this->vazia())
		return String::charNull;

	String ret = this->substr(posIni, qtos);
	for (int u = 0; u < qtos; u++)
	{
		for (int i = posIni; i < this->tamanho; i++) // mexendo, de posicao inicial pra frente, 1 para trás
			*(this->minhaString + i) = (char)*(this->minhaString + i + 1);
	}
	this->tamanho -= qtos;

	return ret;
}

String String::deletarTudo()
{
	String ret = this->clone();
	this->minhaString = NULL;
	this->minhaString = (char*)malloc((this->tamanhoMax+1) * sizeof(char));
	this->tamanho = 0;
	return ret;
}

bool String::cheia() const
{
	return (this->tamanho >= this->tamanhoMax);
}

bool String::vazia() const
{
	return (this->tamanho == 0);
}

int String::tamanhoDe(const char* ch)
{
	int i;
	for (i = 0; *(ch + i) != String::charNull; i++) {}
	return i-1;
}

void String::inserir(const char &letra, const unsigned int &posicao)
{
	if (cheia() || posicao > this->tamanhoMax && posicao < 0)
		return;
	char* aux = this->minhaString;
	this->minhaString = (char*)malloc((this->tamanho+2) * sizeof(char));

	for (int i = 0; i < posicao; i++)
	{
		*(this->minhaString + i) = *(aux+i);
	}

	*(this->minhaString + posicao) = letra;

	for (int i = posicao + 1; i <= this->tamanho; i++)
	{
		*(this->minhaString+i) = *(aux+i-1);
	}
	this->tamanho++;
	*(this->minhaString + this->tamanho) = String::charNull;
}

void String::inserir(const char &letra)
{
	if (cheia())
		return;

	*(this->minhaString + this->tamanho) = letra;
	*(this->minhaString + this->tamanho+1) = String::charNull;
	this->tamanho++;
}

void String::inserirNoComeco(const char & letra)
{
	if (cheia())
		return;

	*this = letra + this->substr(0);
}

void String::inserir(const String &letra, const unsigned int &posicao) // não precisa verificar o tamanhoMax
{
	if (cheia())
		return;

	*this = this->substr(0, posicao) + letra + this->substr(posicao, this->tamanho-1);
}

void String::inserir(const String &letra)
{
	if (cheia())
		return;

	*this = this->minhaString + letra;
}

String String::substr(int posIni, int qtos) const
{
	String ret;
	for (int i = posIni; i < posIni+qtos; i++)
		ret.inserir(this->operator[](i));
	return ret;
}

String String::substr(int posIni) const
{
	return substr(posIni, this->tamanho - posIni);
}

// Apocalipticos
char* String::toString() const
{
	char* pont = (char*)malloc((this->length()+1) *sizeof(char));

	if (this->vazia())
		return pont;

	for (int i = 0; i < this->length(); i++)
		*(pont + i) = (char)*(this->minhaString + i);

	return pont;
}

String String::clone() const
{
	String ret(*this);
	return ret;
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
	static char nulao = char(String::charNull);
	if (indice < 0 || indice > this->tamanho - 1) // index out of bounds
		return nulao;

	return *(this->minhaString + indice);
}

// operators
void String::operator= (const String &primeira)
{
	this->tamanhoMax = primeira.getTamanhoMax();
	this->deletarTudo();
	for (int i = 0; i <= primeira.length(); i++)
		this->inserir(primeira[i]);
}

String String::operator*(const int & qtos) const
{
	if (qtos < 0)
		return this->clone();

	String ret((int)(qtos * this->length()));

	for (int i = 0; i < qtos; i++)
		for (int index = 0; index < this->tamanho; index++)
			ret.inserir((*this)[index]);
	*((char*)ret + ret.length()-1) = String::charNull;
	return ret;
}

String operator+ (const String &th, const String &outra)
{
	char *arrai = (char*)malloc((th.tamanho + outra.length() + 1) * sizeof(char));
	int i = 0;

	for (i = 0; i < th.length(); i++)
		*(arrai + i) = (char)*(th.minhaString + i);

	int u = 0;
	for (i = th.length(); i < th.length() + outra.length(); i++, u++)
		*(arrai + i) = (char)*((char*)outra + u);
	
	*(arrai + i) = String::charNull;

	String ret = String(i, arrai);
	delete[] arrai;

	return ret;
}

String operator+ (const String &th, const string &outra)
{
	char *arrai = (char*)malloc((th.tamanho + outra.length() + 1) * sizeof(char));

	int i = 0;

	for (i = 0; i < th.tamanho + 1; i++)
		*(arrai + i) = (char)*((char*)th.minhaString + i);

	int u = 0;
	for (i = th.tamanho; i < th.tamanho + outra.length(); i++, u++)
		*(arrai + i) = (char)outra.at(u);

	*(arrai + i) = String::charNull;
	String ret = String(i, arrai);
	delete[] arrai;

	return ret;
}

String operator+ (const String &th, const char &outra)
{
	char *arrai = (char*)malloc((th.tamanho + 2) * sizeof(char));
	int i;
	for (i = 0; i < th.tamanho; i++)
		*(arrai + i) = (char)*((char*)th.minhaString + i);
	*(arrai + i) = outra;
	*(arrai + i+1) = String::charNull;
	String ret = String(i+1, arrai);
	delete[] arrai;
	return ret;
}

String operator+ (const String &th, const int &outra)
{
	string intEmStr = to_string(outra);

	char *arrai = (char*)malloc((th.tamanho + intEmStr.length() + 1) * sizeof(char));

	int i = 0;
	for (i = 0; i < th.tamanho; i++)
		*(arrai + i) = (char)*((char*)th.minhaString + i);

	int u = 0;
	for (i = th.tamanho; i < th.tamanho + intEmStr.length(); i++, u++)
		*(arrai + i) = (char)intEmStr.at(u);

	*(arrai + i) = String::charNull;
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
	char *arrai = (char*)malloc((th.tamanho + outra.length() + 1) * sizeof(char));

	int i = 0;

	for (i = 0; i < outra.size(); i++)
		*(arrai + i) = (char)outra.at(i);

	int u = 0;
	for (i = outra.size(); i < th.tamanho + outra.size(); i++, u++)
		*(arrai + i) = (char)*((char*)th.minhaString + u);

	*(arrai + i) = String::charNull;
	String ret = String(i, arrai);
	delete[] arrai;

	return ret;
}

String operator+ (const char &outra, const String &th)
{
	char *arrai = (char*)malloc((th.tamanho + 2) * sizeof(char));
	int i;
	*(arrai + 0) = outra;
	for (i = 1; i < th.tamanho+1; i++)
		*(arrai + i) = (char)*((char*)th.minhaString + i-1);
	*(arrai + i) = String::charNull;
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

	char *arrai = (char*)malloc((th.tamanho + intEmStr.length() + 1) * sizeof(char));

	int i = 0;
	for (i = 0; i < th.tamanho; i++)
		*(arrai + i) = (char)intEmStr.at(i);

	int u = 0;
	for (i = th.tamanho; i < th.tamanho + intEmStr.length(); i++, u++)
		*(arrai + i) = (char)*((char*)th.minhaString + i);

	*(arrai + i) = String::charNull;
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
	static char *ret = (char*)malloc((this->tamanho+1) * sizeof(char));
	for (int i = 0; i < this->tamanho; i++)
		*(ret + i) = (char)*((char*)this->minhaString + i);
	*(ret + this->tamanho) = String::charNull;
	return ret;
}

void String::operator+= (const String &outra)
{
	*this = *this + outra;
}

String::operator const char*() const
{
	static char *ret = (char*)malloc((this->tamanho + 1) * sizeof(char));
	for (int i = 0; i < this->tamanho; i++)
		*(ret + i) = (char)*((char*)this->minhaString + i);
	*(ret + this->tamanho) = String::charNull;
	return ret;
}

String::operator string() const
{
	string ret = string();
	for (int i = 0; i < this->tamanho; i++)
		ret.push_back((char)*((char*)this->minhaString + i));
	return ret;
}

ostream& operator<< (ostream &OS, const String &aString)
{
	if (aString.vazia())
		return OS;

	char *pont = (char*)malloc((aString.length()+1) * sizeof(char));
	for (int i = 0; i < aString.length(); i++)
	{
		*(pont + i) = (char)*((char*)aString.minhaString + i);
	}

	for (int i = 0; i < aString.length() - 1; i++) 
		OS << *(pont + i);
	return (OS << *(pont + aString.length() - 1));
}

istream& operator>> (istream &IS, String &aString)
{
	char* lida = (char*)malloc((aString.tamanhoMax + 1) * sizeof(char));

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
		if (*((char*)pri + i) != *((char*)seg + i))
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
		if (*((char*)pri + i) != *((char*)seg + i))
			return true;
	}
	return false;
}

bool operator< (const String &pri, const char* seg)
{
	int i = 0;
	for (i = 0; *(seg + i) != String::charNull; i++)
	{}
	return pri.length() < i;
}

bool operator> (const String &pri, const char* seg)
{
	int i = 0;
	for (i = 0; *(seg + i) != String::charNull; i++)
	{
	}
	return pri.length() > i;
}

bool operator<= (const String &pri, const char* seg)
{
	int i = 0;
	for (i = 0; *(seg + i) != String::charNull; i++)
	{
	}
	return pri.length() <= i;
}

bool operator>= (const String &pri, const char* seg)
{
	int i = 0;
	for (i = 0; *(seg + i) != String::charNull; i++)
	{
	}
	return pri.length() >= i;
}

bool operator== (const String &pri, const char* seg) // verificar conteúdo também
{
	int i = 0;
	for (i = 0; *(seg + i) != String::charNull; i++)
	{
	}
	if (pri.length() != i)
		return false;

	for (int i = 0; i < pri.tamanho; i++)
	{
		if (*((char*)pri + i) != *((char*)seg + i))
			return false;
	}
	return true;
}

bool operator!= (const String &pri, const char* seg) // verificar conteúdo também
{
	int i = 0;
	for (i = 0; *(seg + i) != String::charNull; i++)
	{
	}
	if (pri.length() != i)
		return true;

	for (int i = 0; i < pri.tamanho; i++)
	{
		if (*((char*)pri + i) != *((char*)seg + i))
			return true;
	}
	return false;
}