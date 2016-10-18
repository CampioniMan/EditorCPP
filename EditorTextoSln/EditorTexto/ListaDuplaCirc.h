#pragma once
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
		void inserir();
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


