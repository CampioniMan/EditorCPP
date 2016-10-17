#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "ListaDuplaCirc.h"
#include "NoLista.h"
using namespace std;

template <class Tipo>
const int ListaDuplaCirc<Tipo>::PERCORRER_AUTO;

template <class Tipo>
const int ListaDuplaCirc<Tipo>::PERCORRER_MANUAL ;

// construtores
template <class Tipo>
ListaDuplaCirc<Tipo>::ListaDuplaCirc() : primeiro(NoLista<Tipo>::NoListaNull()), atual()
{

}

template <class Tipo>
ListaDuplaCirc<Tipo>::ListaDuplaCirc(const ListaDuplaCirc<Tipo> &original)
{

}

template <class Tipo>
ListaDuplaCirc<Tipo>::~ListaDuplaCirc()
{

}

// métodos gerais
template <class Tipo>
void ListaDuplaCirc<Tipo>::inserir(Tipo novoElemento)
{
    NoLista<Tipo>* novo = new NoLista<Tipo>(novoElemento);



    if (this->estaVazia())
    {
        this->primeiro = novo;
        novo->setAnterior(novo);
        novo->setProximo(novo);
        this->tam = 1;
    }
    else
    {

        NoLista<Tipo>* ultimo = primeiro->getAnterior();

    cout << this->primeiro->getAnterior()->getDado().toString() << endl;
    cout << this->primeiro->getDado().toString() << endl;
    cout << this->primeiro->getAnterior()->getDado().toString() << endl;

        novo->setProximo(this->primeiro);
        novo->setAnterior(ultimo);
        this->primeiro->setAnterior(novo);
        ultimo->setProximo(novo);
        this->tam++;
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
    while(this->podePercorrer())
    {
        if (this->atual->getDado() == procurada)
            return this->atual->getDado();
    }
    return Tipo();
}

template <class Tipo>
void ListaDuplaCirc<Tipo>::iniciarPercursoSequencial()
{
    this->iniciarPercursoSequencial(true, this->PERCORRER_AUTO);
}

template <class Tipo>
void ListaDuplaCirc<Tipo>::iniciarPercursoSequencial(bool paraFrente, const int &opcao)
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

template class ListaDuplaCirc<String>;
