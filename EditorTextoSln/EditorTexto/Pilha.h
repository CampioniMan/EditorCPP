#pragma once
#include "Acao.h"
#include "stdafx.h"
class Pilha
{
public:
	// Construtores
	Pilha(const unsigned int tamanhoMax);
	Pilha(const Pilha &original);
	virtual ~Pilha();
	Pilha* clone() const;

	// Métodos normais
	Acao empilhar(const Acao& feita); // remove a base da pilha e empilha o novo
	Acao desempilhar();
	bool ehCheia() const;
	bool ehVazia() const;

	// getters e setters
	Acao getTopo() const;
	int length() const;

	void operator= (Pilha *primeira) const;
protected:
	Acao valorDe(const int &indice) const;
	void inserir(const Acao& feita);
private:
	Acao* acoes;
	int tamanhoMax;
	int tamanhoAtual;
};

