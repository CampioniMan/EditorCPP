#ifndef LISTADUPLACIRC_H
#define LISTADUPLACIRC_H
#include <String.h>

class ListaDuplaCirc
{
    public:
        ListaDuplaCirc();// tem que ter 1 linha em branco no fim
        void destroy();
        ListaDuplaCirc(ListaDuplaCirc &original);
        virtual ~ListaDuplaCirc();
        // mexe com atual
        void inserir(String novoElemento);
        String remover();
        String removerDepois();
        void avancar();
        void voltar();
        // getters e setters(???)
        String Atual() const;
bool operator= (ListaDuplaCirc outra);

    protected:
    private:
        int atual; // não serão ints provavelmente
        int primeiro;
};

#endif // LISTADUPLACIRC_H
