#pragma once
#include "stdafx.h"
class Acao
{
public:
	Acao(String &novaPalavra, String &novoTipo, unsigned int novoX, unsigned int novoY);
	Acao(const Acao &original);
	Acao();
	virtual ~Acao();

	Acao* clone() const;
	void operator= (Acao *primeira) const;

	String getPalavra() const;
	String getTipo() const;
	unsigned int getX() const;
	unsigned int getY() const;

	void setPalavra(String &novaPalavra);
	void setTipo(String &novoTipo);
	void setX(unsigned int novoX);
	void setY(unsigned int novoY);

	static Acao acaoNull();
protected:
	String palavraMudou, tipo;
	unsigned int X, Y;
private:
};


