#ifndef STRING_H
#define STRING_H


class String
{
    public:
        // Construtores
        String(const unsigned int &novoTamanho);
        String(const String &original);
        String();
        virtual ~String();

        // M�todos normais
        void deleteCharAt(const unsigned int &posicao);
        void deletar(unsigned int posIni, unsigned int posFim);
        void inserir(const unsigned int &posicao, const char &letra);
        void inserir(const char &letra);
        bool cheia() const;
        bool vazia() const;

        // Apocalipticos
        char* toString() const;
        String clone() const;

        // getters e setters
        int length() const;
        int getTamanhoMax() const;

        // operators
        void operator= (const String &primeira);
        void operator+ (const String &outra);
        char& operator[] (const int &indice) const;

        // constantes
        const char charNull = '\0';
    protected:
    private:
        char* minhaString;
        int tamanho;
        int tamanhoMax;

};
bool operator< (const String &primeira, const String &segunda);
bool operator> (const String &primeira, const String &segunda);
bool operator<= (const String &primeira, const String &segunda);
bool operator>= (const String &primeira, const String &segunda);
bool operator== (const String &primeira, const String &segunda);
bool operator!= (const String &primeira, const String &segunda);

#endif // STRING_H
