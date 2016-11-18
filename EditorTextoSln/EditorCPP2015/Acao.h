#pragma once
#include "stdafx.h"
#include "ListaDuplaCirc.h"
#include "String.h"
class Acao
{
public:
	// Construtores
	Acao(const String *novasLinhas, const String &novoTipo, const unsigned int *novaLinhaOcorren, const unsigned int novoTam);
	Acao(const String &novaLinha, const String &novoTipo, const unsigned int novaLinhaOcorren);
	Acao(const Acao &original);
	Acao();
	virtual ~Acao();

	// Construtores de Cópia
	Acao* clone() const;
	void operator= (const Acao& primeira);

	// Getters e Setters
	String* getString() const;
	String getTipo() const;
	unsigned int* getLinhasOcorrencias() const;
	unsigned int getLinhaOcorrencia(const unsigned int pos) const;
	unsigned int getTamanho() const;

	void setString(const String &novaLinha, const unsigned int pos);
	void setString(const string &novaLinha, const unsigned int pos);
	void setString(const char *novaLinha, const unsigned int pos);
	void setFrase(const String &novoTipo);
	void setTipo(const String &novoTipo);
	void setLinhasOcorrencias(const unsigned int* novasLinhas);
	void setLinhaOcorrencia(const unsigned int novaLinha, const unsigned int pos);
	void setTamanho(const unsigned int novoTam);

	static Acao acaoNull();
	String toString() const;

protected:
	// Métodods Auxiliares
	void deletarTudo();
	void aloca(const String *novasString, const unsigned int *novaLinhaOcorren, unsigned int novoTam = 1, unsigned int ehStr = 0, unsigned int ehLinhas  =1);
private:
	// Atributos
	String *palavraMudou, tipo;
	unsigned int *linhaOcorrencia, tamanho;
	void(*func)(const ListaDuplaCirc<String> &lst, const Acao &dis);
};

const static String ACAO_ADICAO = "A";
const static String ACAO_REMOVE = "R";
const static String ACAO_CTRL_Z = "Z";
const static String ACAO_CTRL_Y = "Y";
const static String ACAO_CTRL_X = "X";
const static String ACAO_CTRL_H = "H";
