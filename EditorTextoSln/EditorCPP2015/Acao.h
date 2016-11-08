#pragma once
#include "stdafx.h"
class Acao
{
public:
	// Construtores
	Acao(const String *novaPalavra, unsigned int novoTam, const String &novoTipo, unsigned int novoX, unsigned int novoY);
	Acao(const Acao &original);
	Acao();
	virtual ~Acao();

	// Construtores de Cópia
	Acao* clone() const;
	void operator= (const Acao& primeira);

	// Getters e Setters
	String* getPalavra() const;
	String getTipo() const;
	unsigned int getX() const;
	unsigned int getY() const;
	unsigned int getTamanho() const;

	void setPalavra(const String &novaPalavra, const unsigned int pos);
	void setPalavra(const string &novaPalavra, const unsigned int pos);
	void setPalavra(const char *novaPalavra, const unsigned int pos);
	void setFrase(const String &novoTipo);
	void setTipo(const String &novoTipo);
	void setX(const unsigned int novoX);
	void setY(const unsigned int novoY);
	void setTamanho(const unsigned int novoTam);

	static Acao acaoNull();
	String toString() const;
protected:
	// Métodods Auxiliares
	void deletarTudo();
	void alocaPalavra(const String *novaPalavra, const unsigned int tam);
private:
	// Atributos
	String *palavraMudou, tipo;
	unsigned int X, Y, tamanho;
};


