#pragma once
using namespace std;
#include "NoLista.h"
template <class Tipo>
class ListaDuplaCirc
{
	public:
		ListaDuplaCirc();
		ListaDuplaCirc(const ListaDuplaCirc<Tipo> &original);
		ListaDuplaCirc(Tipo novoPrimeiro);
		virtual ~ListaDuplaCirc();

		// mexe com atual
		void inserir(const Tipo &novoElemento);
		bool remover(const Tipo &elemento);
		void avancar();
		void voltar();
		void iniciarPercursoSequencial(bool paraFrente, const int &opcao);
		bool podePercorrer();
		bool existe() const;
		bool estaVazia() const;
		Tipo primeiraOcorrenciaDe(const Tipo &procurada);

		// getters e setters()
		Tipo getValorAtual() const;
		int getIndiceAtual() const;
		Tipo getValorPrimeiro() const;
		int getIndicePrimeiro() const;
		NoLista<Tipo> getPrimeiro() const;
		NoLista<Tipo> getAtual() const;

		//operators
		bool operator= (const ListaDuplaCirc &outra);
		Tipo operator[] (const int &indice) const;

		// constantes
		const static int PERCORRER_AUTO = 1;
		const static int PERCORRER_MANUAL = 0;

	protected:
		bool indoParaFrente = true;
		int estaPercorrendoAuto = 1;
	private:
		NoLista<Tipo> *atual;
		NoLista<Tipo> *primeiro;
		int tam = 0;
};

template <class Tipo>
ListaDuplaCirc<Tipo>::ListaDuplaCirc() : primeiro(NoLista<Tipo>::NoListaNull()), atual(NoLista<Tipo>::NoListaNull())
{

}

template <class Tipo>
ListaDuplaCirc<Tipo>::ListaDuplaCirc(const ListaDuplaCirc<Tipo> &original)
{

}

template <class Tipo>
ListaDuplaCirc<Tipo>::ListaDuplaCirc(Tipo novoPrimeiro) : primeiro(novoPrimeiro), atual(novoPrimeiro)
{

}

template <class Tipo>
ListaDuplaCirc<Tipo>::~ListaDuplaCirc()
{

}

// métodos gerais
template <class Tipo>
void ListaDuplaCirc<Tipo>::inserir(const Tipo &novoElemento)
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
		this->primeiro->setAnterior(novo);
		this->primeiro->getAnterior()->setProximo(novo);
		novo->setAnterior(this->primeiro->getAnterior());
		novo->setProximo(this->primeiro);
	}
}

template <class Tipo>
bool ListaDuplaCirc<Tipo>::remover(const Tipo &elemento)
{
	NoLista<Tipo>* removido = new NoLista<Tipo>(primeiraOcorrenciaDe(elemento));
	removido->getAnterior()->setProximo(removido->getProximo());
	removido->getProximo()->setAnterior(removido->getAnterior());
	return true;
}

template <class Tipo>
Tipo ListaDuplaCirc<Tipo>::primeiraOcorrenciaDe(const Tipo &procurada)
{
	this->iniciarPercursoSequencial();
	while (this->podePercorrer())
	{
		if (this->atual->getDado() == procurada)
			return this->atual->getDado();
	}
	return Tipo();
}

template <class Tipo>
void ListaDuplaCirc<Tipo>::iniciarPercursoSequencial(bool paraFrente = true, const int &opcao = ListaDuplaCirc::PERCORRER_AUTO)
{
	this->atual = this->primeiro->getAnterior();
	this->indoParaFrente = paraFrente;
	this->estaPercorrendoAuto = opcao;
}

template <class Tipo>
bool ListaDuplaCirc<Tipo>::podePercorrer()
{
	if (this->estaPercorrendoAuto == this->PERCORRER_AUTO)
	{
		if (this->indoParaFrente)
			this->avancar();
		else
			this->voltar();
	}

	return (this->atual != this->primeiro->getAnterior());
}

template <class Tipo>
void ListaDuplaCirc<Tipo>::avancar()
{
	this->atual = this->atual->getProximo();
}

template <class Tipo>
void ListaDuplaCirc<Tipo>::voltar()
{
	this->atual = this->atual->getAnterior();
}

template <class Tipo>
bool ListaDuplaCirc<Tipo>::estaVazia() const
{
	return (this->primeiro == NoLista<Tipo>::NoListaNull());
}

template <class Tipo>
Tipo ListaDuplaCirc<Tipo>::getValorAtual() const
{
	return this->atual->getDado();
}

template <class Tipo>
Tipo ListaDuplaCirc<Tipo>::getValorPrimeiro() const
{
	return this->primeiro->getDado();
}

template <class Tipo>
NoLista<Tipo> ListaDuplaCirc<Tipo>::getPrimeiro() const
{
	return *this->primeiro;
}

template <class Tipo>
NoLista<Tipo> ListaDuplaCirc<Tipo>::getAtual() const
{
	return *this->atual;
}

// operators
template <class Tipo>
bool ListaDuplaCirc<Tipo>::operator= (const ListaDuplaCirc &outra)
{
}

template <class Tipo>
Tipo ListaDuplaCirc<Tipo>::operator[] (const int &indice) const
{
	NoLista<Tipo>* atualReserva = this->atual;
	int contador = 0;
	while (atualReserva != this->primeiro && contador < indice)
	{
		atualReserva = atualReserva->getProximo();
	}
	return atualReserva->getDado();
}
