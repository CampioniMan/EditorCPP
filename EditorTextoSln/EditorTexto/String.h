#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
class String
{
	public:
		// Construtores
		String(const unsigned int &novoTamanho);
		String(const String &original);
		String();
		String(const string &novaString);
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
		void operator+ (const String &outra);
		char& operator[] (const int &indice) const;

		friend ostream& operator<< (ostream &OS, const String &aString);
		friend istream& operator>> (istream &IS, String &aString);
		friend bool operator!= (const String &pri, const String &seg);
		friend bool operator== (const String &pri, const String &seg);
		friend bool operator< (const String &pri, const String &seg);
		friend bool operator> (const String &pri, const String &seg);
		friend bool operator<= (const String &pri, const String &seg);
		friend bool operator>= (const String &pri, const String &seg);
		

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
