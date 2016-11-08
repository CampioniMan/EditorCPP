#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

class String
{
	public:
		// Construtores
		String(const unsigned int &novoTamanho);
		String(const String &original);
		String(const string &original);
		String(const char* original);
		String(const int &n, char novaString[]);
		String();
		virtual ~String();

		// Métodos normais
		void deleteCharAt(const unsigned int &posicao);
		void deletar(unsigned int posIni, unsigned int qtos);
		void deletarTudo();
		void inserir(const char &letra, const unsigned int &posicao);
		void inserir(const char &letra);
		bool cheia() const;
		bool vazia() const;

		// Apocalipticos
		char* toString() const;
		String clone() const;

		// getters e setters
		int length() const;
		int getTamanhoMax() const;

		// operators
		void operator= (const String &primeira);
		friend String operator+ (const String &th, const String &outra);
		friend String operator+ (const String &th, const std::string &outra);
		friend String operator+ (const String &th, const char &outra);
		friend String operator+ (const String &th, const char* &outra);
		friend String operator+ (const String &th, const char* outra);
		friend String operator+ (const String &th, const int &outra);

		friend String operator+ (const String &outra, const String &th);
		friend String operator+ (const std::string &outra, const String &th);
		friend String operator+ (const char &outra, const String &th);
		friend String operator+ (const char* &outra, const String &th);
		friend String operator+ (const char* outra, const String &th);
		friend String operator+ (const int &outra, const String &th);

		char& operator[] (const int &indice) const;
		operator char*() const;
		operator string() const;
		operator const char*() const;

		friend ostream& operator<< (ostream &OS, const String &aString);
		friend istream& operator>> (istream &IS, String &aString);
		friend bool operator!= (const String &pri, const String &seg);
		friend bool operator== (const String &pri, const String &seg);
		friend bool operator< (const String &pri, const String &seg);
		friend bool operator> (const String &pri, const String &seg);
		friend bool operator<= (const String &pri, const String &seg);
		friend bool operator>= (const String &pri, const String &seg);

		friend bool operator!= (const String &pri, const char* seg);
		friend bool operator== (const String &pri, const char* seg);
		friend bool operator< (const String &pri, const char* seg);
		friend bool operator> (const String &pri, const char* seg);
		friend bool operator<= (const String &pri, const char* seg);
		friend bool operator>= (const String &pri, const char* seg);
		

		// constantes
		const static char charNull = '\0';

		// amizades
		friend String;

	protected:
	private:
		char* minhaString;
		int tamanho;
		int tamanhoMax;

};

bool operator== (const String &pri, const String &seg);
bool operator!= (const String &pri, const String &seg);
bool operator< (const String &pri, const String &seg);
bool operator> (const String &pri, const String &seg);
bool operator<= (const String &pri, const String &seg);
bool operator>= (const String &pri, const String &seg);
