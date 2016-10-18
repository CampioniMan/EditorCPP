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
		String(const std::string &novaString);
		virtual ~String();

		// Métodos normais
		void deleteCharAt(const unsigned int &posicao);
		void deletar(unsigned int posIni, unsigned int posFim);
		void inserir(const unsigned int &posicao, const char &letra);
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
		char operator[] (const int &indice) const;
		bool operator== (const String &outra);
		bool operator!= (const String &outra);
		bool operator< (const String &outra);
		bool operator> (const String &outra);
		bool operator<= (const String &outra);
		bool operator>= (const String &outra);

		friend ostream& operator<< (ostream &OS, const String &aString);
		friend istream& operator>> (istream &IS, String &aString);
		

		// constantes
		const static char charNull = '\0';
	protected:
	private:
		char* minhaString;
		int tamanho;
		int tamanhoMax;

};

