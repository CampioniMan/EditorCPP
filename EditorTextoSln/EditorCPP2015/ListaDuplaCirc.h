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

	ListaDuplaCirc() : primeiro(NULL), atual(NULL), anterior(NULL), proximo(NULL), indexAtual(0){}

	ListaDuplaCirc(const ListaDuplaCirc<Tipo> &original) : primeiro(original.getPrimeiro()), atual(original.getAtual()), 
			                                                anterior(original.getAnterior()), proximo(original.getProximo(), indexAtual(original.getIndexAtual())){}

	ListaDuplaCirc(Tipo novoPrimeiro) : primeiro(novoPrimeiro), atual(novoPrimeiro), anterior(novoPrimeiro), proximo(novoPrimeiro), indexAtual(0) {}

	~ListaDuplaCirc(){}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//---------------------------------------------------------------GETTERS E SETTERS-----------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
		
	int length() const
	{
		return this->tam;
	}

	Tipo getAtual() const
	{
		return this->atual->getDado();
	}

	int getIndexAtual() const
	{
		return this->indexAtual;
	}

	Tipo getPrimeiro() const
	{
		return this->primeiro->getDado();
	}

	void setAtual(Tipo novoDado)
	{
		this->atual->setDado(novoDado);
	}

	void setPrimeiro(Tipo novoDado)
	{
		this->primeiro->setDado(novoDado);
	}
		
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------------------------------MÉTODOS PRINCIPAIS---------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------------------------------------------------------------//

	void inserirNoFinal(const Tipo &novoElemento)
	{
		static NoLista<Tipo>* novo = new NoLista<Tipo>(novoElemento);

		if (this->estaVazia())
		{
			this->primeiro = new NoLista<Tipo>(novo);
			primeiro->setAnterior(primeiro);
			primeiro->setProximo(primeiro);
			atual = primeiro;
			proximo = primeiro;
			anterior = primeiro;
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

	void inserirDepois(const Tipo &novoElemento)
	{
		static NoLista<Tipo>* novo = new NoLista<Tipo>(novoElemento);

		if (this->estaVazia())
		{
			this->primeiro = new NoLista<Tipo>(novo);
			primeiro->setAnterior(primeiro);
			primeiro->setProximo(primeiro);
			atual = primeiro;
			proximo = primeiro;
			anterior = primeiro;
		}
		else
		{
			novo->setAnterior(this->atual);
			novo->setProximo(this->proximo);
			this->atual->setProximo(novo);
			this->proximo->setAnterior(novo);
		}
		this->tam++;
	}

	void inserirNoComeco(const Tipo &novoElemento)
	{
		static NoLista<Tipo> *novo = new NoLista<Tipo>(novoElemento);

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
		
	bool removaAtual()
	{
		if (this->estaVazia())
			return false;

		if (this->tam > 1)
		{
			anterior->setProximo(proximo);
			proximo->setAnterior(anterior);
			atual = proximo;
			proximo = proximo->getProximo();
			if (this->indexAtual == 0)
				this->primeiro = atual;
			if (this->indexAtual == this->tam - 1)
				this->indexAtual--;
		}
		else
		{
			atual = NULL;
			primeiro = NULL;
			anterior = NULL;
			proximo = NULL;
			this->indexAtual = 0;
		}
		this->tam--;
		return true;
	}

	bool removaDepois()
	{
		if (this->estaVazia())
			return false;

		if (this->tam > 1)
		{
			proximo = proximo->getProximo();
			atual->setProximo(proximo);
			proximo->setAnterior(atual);
		}
		else
		{
			atual = NULL;
			primeiro = NULL;
			anterior = NULL;
			proximo = NULL;
			this->indexAtual = 0;
		}
		this->tam--;
		return true;
	}

	bool remover(const int &elemento = this->getIndexAtual())
	{
		if (this->estaVazia() || elemento < 0 || elemento >= this->tam)
			return false;

		
		for (int i = elemento; i <= this->tam - 1; i++)
			this->operator[](i) = this->operator[](i + 1);
		this->remover(this->operator[](-1));
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
				this->indexAtual = index;
				return index;
			}
			index++;
		}
		return -1;
	}

	int indiceDe(const Tipo &procurada) const
	{
		int index = 0;
		while (this->length() > index)
		{
			if (this->operator[](index) == procurada)
			{
				return index;
			}
			index++;
		}
		return -1;
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
		this->indexAtual = -1;
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
		this->indexAtual++;
		if (this->indexAtual >= this->tam)
			this->indexAtual = 0;
	}

	void voltar()
	{
		this->atual = this->atual->getAnterior();
		this->anterior = this->anterior->getAnterior();
		this->proximo = this->proximo->getAnterior();
		this->indexAtual--;
		if (this->indexAtual < 0)
			this->indexAtual = this->tam-1;
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
		if (indice >= 0)
		{
			while (contador < indice)
			{
				atualReserva = atualReserva->getProximo();
				contador++;
			}
		}
		else
		{
			while (contador > indice)
			{
				atualReserva = atualReserva->getAnterior();
				contador--;
			}
		}
		return (*(atualReserva->dado));
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
	int tam = 0, indexAtual = 0;
};

