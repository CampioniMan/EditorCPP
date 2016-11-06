#pragma once
#include "stdafx.h"
class Acao
{
public:
	Acao(const String *novaPalavra, const unsigned int novoTam, const String &novoTipo, const unsigned int novoX, const unsigned int novoY);
	Acao(const Acao &original);
	Acao();
	virtual ~Acao();

	Acao* clone() const;
	void operator= (const Acao& primeira);

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
	void deletarTudo();
private:
	String *palavraMudou, tipo;
	unsigned int X, Y, tamanho;
};


