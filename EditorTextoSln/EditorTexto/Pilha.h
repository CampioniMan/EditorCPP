#pragma once
#include "Acao.h"
#include "stdafx.h"
class Pilha
{
public:
	// Construtores
	Pilha(const unsigned int tamanhoMax);
	Pilha(const Pilha &original);
	Pilha();
	virtual ~Pilha();

	Pilha* clone() const;
	void operator= (Pilha *primeira) const;

	// Métodos normais
	Acao empilhar(const Acao& feita); // remove a base da pilha e empilha o novo
	Acao desempilhar();
	bool ehCheia() const;
	bool ehVazia() const;

	// getters e setters
	Acao getTopo() const;
	int length() const;

	String toString() const;
protected:
	Acao valorDe(const int &indice) const;
	void Pilha::alocaPalavra(const Acao *novaAcao, const unsigned int tam);
private:
	Acao *acoes;
	unsigned int tamanhoMax, tamanhoAtual;
};

