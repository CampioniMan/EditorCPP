#pragma once
using namespace std;
#include "NoLista.h"

template <class Tipo>
class ListaDuplaCirc
{
public:
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//-------------------------------------------------------------CONSTRUTORES/DESTRUTOR--------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//

	ListaDuplaCirc() : primeiro(NULL), atual(NULL), anterior(NULL), proximo(NULL){}

	ListaDuplaCirc(const ListaDuplaCirc<Tipo> &original) : primeiro(original.getPrimeiro()), atual(original.getAtual()), 
			                                                anterior(original.getAnterior()), proximo(original.getProximo()){}

	ListaDuplaCirc(Tipo novoPrimeiro) : primeiro(novoPrimeiro), atual(novoPrimeiro), anterior(novoPrimeiro), proximo(novoPrimeiro){}

	~ListaDuplaCirc(){}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//---------------------------------------------------------------GETTERS E SETTERS-----------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
		
	int length() const
	{
		return this->tam;
	}

	Tipo getValorAtual() const
	{
		return this->atual->getDado();
	}

	Tipo getValorPrimeiro() const
	{
		return this->primeiro->getDado();
	}

	NoLista<Tipo> getPrimeiro() const
	{
		return *this->primeiro;
	}

	NoLista<Tipo> getAtual() const
	{
		return *this->atual;
	}
		
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------------------------------MÉTODOS PRINCIPAIS---------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//

	void inserirNoFinal(const Tipo &novoElemento)
	{
		NoLista<Tipo>* novo = new NoLista<Tipo>(novoElemento);

		if (this->estaVazia())
		{
			this->primeiro = novo;
			novo->setAnterior(novo);
			novo->setProximo(novo);
		}
		else
		{
			novo->setAnterior(this->primeiro->getAnterior());
			novo->setProximo(this->primeiro);
			this->primeiro->getAnterior()->setProximo(novo);
			this->primeiro->setAnterior(novo);
		}
		this->tam++;
	}

	void inserirNoComeco(const Tipo &novoElemento)
	{
		NoLista<Tipo>* novo = new NoLista<Tipo>(novoElemento);

		if (estaVazia())
		{
			this->primeiro = novo;
			novo->setProximo(novo);
			novo->setAnterior(novo);
		}
		else
		{
			novo->setProximo(primeiro);
			novo->setAnterior(primeiro->getAnterior());

			this->primeiro->getAnterior()->setProximo(novo);
			this->primeiro->setAnterior(novo);

			this->primeiro = novo;
		}
		this->tam++;
	}
		
	bool remover(const Tipo &elemento)
	{
		if (this->estaVazia() || !this->existe(elemento) || elemento == Tipo())
			return false;

		if (this->tam > 1)
		{
			anterior->setProximo(proximo);
			proximo->setAnterior(anterior);
			atual = proximo;
			proximo = proximo->getProximo();
			if (primeiro->getDado() == elemento)
				this->primeiro = atual;
		}
		else
		{
			atual = NULL;
			primeiro = NULL;
			anterior = NULL;
			proximo = NULL;
		}
		this->tam--;
		return true;
	}
		
	int buscar(const Tipo &procurada)
	{
		NoLista<Tipo>* reserva = this->atual;
		int index = 0;
		this->iniciarPercursoSequencial();
		while (this->podePercorrer())
		{
			if (this->atual->getDado() == procurada)
			{
				this->voltarPara(reserva);
				return index;
			}
			index++;
		}

		this->voltarPara(reserva);
		return -1;
	}

	bool existe(const Tipo &procurada) // já posiciona os ponteiros
	{
		int index = 0;
		this->iniciarPercursoSequencial();
		while (this->podePercorrer())
		{
			if (this->atual->getDado() == procurada)
			{
				return true;
			}
		}
		return false;
	}
		
	//----------------------------------------------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------------------------------MÉTODOS DE PERCURSSÃO---------------------------------------------------------------------//
	//----------------------------------------------------------------------------------------------------------------------------------------------------------//

	void iniciarPercursoSequencial(const bool &paraFrente = true)
	{
		this->atual = NULL;
		this->proximo = NULL;
		this->anterior = NULL;
		this->indoParaFrente = paraFrente;
	}

	bool podePercorrer()
	{
		if (this->estaVazia())
			return false;

		bool ret = this->atual != this->primeiro->getAnterior();
		if (this->atual == NULL)
		{
			this->atual = this->primeiro->getAnterior();
			this->proximo = this->primeiro;
			this->anterior = this->primeiro->getAnterior()->getAnterior();
		}

		if (this->indoParaFrente)
			this->avancar();
		else
			this->voltar();
			

		return ret;
	}

	void avancar()
	{
		this->anterior = this->anterior->getProximo();
		this->atual = this->atual->getProximo();
		this->proximo = this->proximo->getProximo();
	}

	void voltar()
	{
		this->atual = this->atual->getAnterior();
		this->anterior = this->anterior->getAnterior();
		this->proximo = this->proximo->getAnterior();
	}
		
	bool estaVazia() const
	{
		return (this->primeiro == NULL);
	}

	//----------------------------------------------------------------------------------------------------------------------------------------------------------//
	//--------------------------------------------------------------------OPERATORS-----------------------------------------------------------------------------//
	//----------------------------------------------------------------------------------------------------------------------------------------------------------//
		
	bool operator= (const ListaDuplaCirc &outra)
	{
		return true;
	}

	Tipo& operator[] (const int &indice) const
	{
		NoLista<Tipo> *atualReserva = new NoLista<Tipo>;
		*atualReserva = *this->primeiro;
		int contador = 0;
		while (contador < indice)
		{
			atualReserva = atualReserva->getProximo();
			contador++;
		}
		return atualReserva->getDado();
	}

	friend ListaDuplaCirc;
protected:
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------------------------------MÉTODOS AUXILIARES---------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	bool indoParaFrente = true;

	void voltarPara(NoLista<Tipo>* voltador)
	{
		if (voltador != NULL)
		{
			this->atual = voltador;
			this->anterior = this->atual->getAnterior();
			this->proximo = this->atual->getProximo();
		}
	}
private:
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//-------------------------------------------------------------------ATRIBUTOS---------------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	NoLista<Tipo> *atual, *anterior, *proximo, *primeiro;
	int tam = 0;
};

