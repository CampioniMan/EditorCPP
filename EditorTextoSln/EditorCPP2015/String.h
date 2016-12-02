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
		String(const char &caracter);
		String(const int &novoTamanho);
		String(const int &n, char novaString[]);
		String();
		virtual ~String();

		// Métodos normais
		char deleteCharAt(const unsigned int &posicao);
		String deletar(unsigned int posIni, unsigned int qtos);
		String deletarTudo();
		void inserir(const char &letra, const unsigned int &posicao);
		void inserir(const char &letra);
		void inserirNoComeco(const char &letra);
		void inserir(const String &letra, const unsigned int &posicao);
		void inserir(const String &letra);
		String substr(int posIni, int qtos) const;
		String substr(int posIni) const;
		int StrToInt() const;
		bool cheia() const;
		bool vazia() const;
		static int tamanhoDe(const char* ch);

		// Apocalipticos
		char* toString() const;
		String clone() const;

		// getters e setters
		int length() const;
		int getTamanhoMax() const;

		// operators
		void operator= (const String &primeira);
		String operator*(const int &qtos) const;
		friend String operator+ (const String &th, const String &outra);
		friend String operator+ (const String &th, const std::string &outra);
		friend String operator+ (const String &th, const char &outra);
		friend String operator+ (const String &th, const char* &outra);
		friend String operator+ (const String &th, const char* outra);
		friend String operator+ (const String &th, const int &outra);
		

		friend String operator+ (const std::string &outra, const String &th);
		friend String operator+ (const char &outra, const String &th);
		friend String operator+ (const char* &outra, const String &th);
		friend String operator+ (const char* outra, const String &th);
		friend String operator+ (const int &outra, const String &th);

		char& operator[] (const int &indice) const;
		void operator+= (const String &outra);
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
		friend class String;

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
