#include "ListaDuplaCirc.h"
#include "NoLista.h"

// construtores
ListaDuplaCirc::ListaDuplaCirc()
{

}

ListaDuplaCirc::ListaDuplaCirc(const ListaDuplaCirc &original) : atual(original.getValorAtual()), primeiro(original.getValorPrimeiro())
{

}

ListaDuplaCirc::~ListaDuplaCirc()
{

}

// métodos gerais
void ListaDuplaCirc::inserir(String novoElemento)
{
    NoLista* novo = new NoLista(novoElemento);

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
    }
}

bool ListaDuplaCirc::remover(const String &elemento)
{
    NoLista* removido = primeiraOcorrenciaDe(elemento);
    removido->getAnterior()->setProximo(removido->getProximo());
    removido->getProximo()->setAnterior(removido->getAnterior());
    return true;
}

bool ListaDuplaCirc::removerDepois(const String &elemento) //(???)
{

}

NoLista* ListaDuplaCirc::primeiraOcorrenciaDe(const String &procurada)
{
    this->iniciarPercursoSequencial();
    while(this->podePercorrer())
    {
        if (this->atual->getDado() == procurada)
            return this->atual;
    }
    return NoLista::NoListaNull();
}

void ListaDuplaCirc::iniciarPercursoSequencial()
{

}

bool ListaDuplaCirc::podePercorrer()
{

}

void ListaDuplaCirc::avancar()
{
    this->atual = this->atual->getProximo();
}

void ListaDuplaCirc::voltar()
{
    this->atual = this->atual->getAnterior();
}

bool ListaDuplaCirc::estaVazia() const
{
    return (this->primeiro == NoLista::NoListaNull());
}

NoLista* ListaDuplaCirc::getValorAtual() const
{

}

NoLista* ListaDuplaCirc::getValorPrimeiro() const
{

}

// operators
bool ListaDuplaCirc::operator= (ListaDuplaCirc outra)
{

}

