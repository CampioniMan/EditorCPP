#pragma once
using namespace std;
#include "NoLista.h"
template <class Tipo>
class ListaDuplaCirc
{
	public:
// construtores e destrutores

		
		ListaDuplaCirc() :
		primeiro(NoLista<Tipo>::NoListaNull()), atual(NoLista<Tipo>::NoListaNull()), anterior(NoLista<Tipo>::NoListaNull()), proximo(NoLista<Tipo>::NoListaNull())
		{

		}

		
		ListaDuplaCirc(const ListaDuplaCirc<Tipo> &original) :
		primeiro(original.getPrimeiro()), atual(original.getAtual()), anterior(original.getAnterior()), proximo(original.getProximo())
		{

		}

		
		ListaDuplaCirc(Tipo novoPrimeiro) : primeiro(novoPrimeiro), atual(novoPrimeiro), anterior(novoPrimeiro), proximo(novoPrimeiro)
		{

		}

		
		~ListaDuplaCirc()
		{

		}

		
		int length() const
		{
			return this->tam;
		}

		// métodos gerais
		
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
				this->primeiro->setAnterior(novo);
				this->primeiro->getAnterior()->setProximo(novo);
				novo->setAnterior(this->primeiro->getAnterior());
				novo->setProximo(this->primeiro);
			}
			this->tam++;
		}

		
		bool remover(const Tipo &elemento)
		{
			NoLista<Tipo>* removido = new NoLista<Tipo>(buscar(elemento));
			Tipo *tipoDefault = new Tipo();
			if (removido->getDado() == *tipoDefault)
				return false;

			anterior->setProximo(proximo);
			proximo->setAnterior(anterior);
			this->tam--;
			return true;
		}

		
		Tipo buscar(const Tipo &procurada)
		{
			this->iniciarPercursoSequencial();
			while (this->podePercorrer())
			{
				if (this->atual->getDado() == procurada)
					return this->atual->getDado();
			}
			return Tipo();
		}

		
		void iniciarPercursoSequencial(const bool &paraFrente = true, const int &opcao = ListaDuplaCirc::PERCORRER_AUTO)
		{
			this->atual = this->primeiro->getAnterior();
			this->anterior = this->atual->getAnterior();
			this->proximo = this->primeiro;
			this->indoParaFrente = paraFrente;
			this->estaPercorrendoAuto = opcao;
		}

		
		bool podePercorrer()
		{
			if (this->estaVazia())
				return false;

			if (this->estaPercorrendoAuto == this->PERCORRER_AUTO)
			{
				if (this->indoParaFrente)
					this->avancar();
				else
					this->voltar();
			}

			return (this->atual != this->primeiro->getAnterior());
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
		}

		
		bool estaVazia() const
		{
			return (this->primeiro == NoLista<Tipo>::NoListaNull());
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

		// operators
		
		bool operator= (const ListaDuplaCirc &outra)
		{
		}

		
		Tipo operator[] (const int &indice) const
		{
			NoLista<Tipo> *atualReserva = new NoLista<Tipo>;
			*atualReserva = *this->primeiro;
			int contador = 0;
			while (contador < indice)
			{
				NoLista<Tipo> atualReserva(atualReserva->getProximo());
				contador++;
			}
			return atualReserva->getDado();
		}

// constantes
		const static int PERCORRER_AUTO = 1;
		const static int PERCORRER_MANUAL = 0;

		friend ListaDuplaCirc;
	protected:
		bool indoParaFrente = true;
		int estaPercorrendoAuto = 1;
	private:
		NoLista<Tipo> *atual, *anterior, *proximo;
		NoLista<Tipo> *primeiro;
		int tam = 0;
};

