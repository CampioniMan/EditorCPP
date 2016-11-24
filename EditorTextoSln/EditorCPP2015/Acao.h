#pragma once
#include "stdafx.h"
#include "ListaDuplaCirc.h"
#include "String.h"
class Acao
{
public:
	// Construtores
	Acao(const String *novasLinhas, const String &novoTipo, const unsigned int *novoPosY, const unsigned int novoTam, const unsigned int novoPosX);
	Acao(const String &novaLinha, const String &novoTipo, const unsigned int novoPosY, const unsigned int novoPosX);
	Acao(const Acao &original);
	Acao();
	virtual ~Acao();

	// Construtores de Cópia
	Acao* clone();
	void operator= (const Acao& primeira);

	// Getters e Setters
	String* getString() const;
	String getTipo() const;
	unsigned int getPosX() const;
	unsigned int* getPosY() const;
	unsigned int getPosY(const unsigned int pos) const;
	unsigned int getTamanho() const;

	void setString(const String &novaLinha, const unsigned int pos);
	void setString(const string &novaLinha, const unsigned int pos);
	void setString(const char *novaLinha, const unsigned int pos);
	void setFrase(const String &novoTipo);
	void setTipo(const String &novoTipo);
	void setPosX(const unsigned int novoPosX);
	void setPosY(const unsigned int* novoPosY);
	void setPosY(const unsigned int novoPosY, const unsigned int pos);
	void setTamanho(const unsigned int novoTam);

	String toString() const;

protected:
	// Métodods Auxiliares
	void deletarTudo();
	void aloca(const String *novasString, const unsigned int *novoPosY, unsigned int novoTam = 1, unsigned int ehStr = 0, unsigned int ehLinhas = 1);
private:
	// Atributos
	String *palavraMudou, tipo;
	unsigned int *posY, posX, tamanho;
	void(*func)(const ListaDuplaCirc<String> &lst, const Acao &dis);
};

const static String ACAO_ADICAO = "A";
const static String ACAO_REMOVE = "R";
const static String ACAO_CTRL_Z = "Z";
const static String ACAO_CTRL_Y = "Y";
const static String ACAO_CTRL_X = "X";
const static String ACAO_CTRL_H = "H";
