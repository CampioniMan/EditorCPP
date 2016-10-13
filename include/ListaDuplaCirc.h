#ifndef LISTADUPLACIRC_H
#define LISTADUPLACIRC_H
#include "String.h"
#include "NoLista.h"

class ListaDuplaCirc
{
    public:
        ListaDuplaCirc();// tem que ter 1 linha em branco no fim
        ListaDuplaCirc(const ListaDuplaCirc &original);
        virtual ~ListaDuplaCirc();
        // mexe com atual
        void inserir(String novoElemento);
        bool remover(const String &elemento);
        bool removerDepois(const String &elemento);
        void avancar();
        void voltar();
        void iniciarPercursoSequencial();
        bool podePercorrer();
        bool existe() const;
        bool estaVazia() const;
        NoLista* primeiraOcorrenciaDe(const String &procurada);
        // getters e setters()
        NoLista* getValorAtual() const;
        int getIndiceAtual() const;
        NoLista* getValorPrimeiro() const;
        int getIndicePrimeiro() const;

        bool operator= (ListaDuplaCirc outra);
        String operator[] (const int &indice) const;

    protected:
    private:
        NoLista *atual; // não serão ints provavelmente
        NoLista *primeiro;
};

#endif // LISTADUPLACIRC_H
