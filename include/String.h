#ifndef STRING_H
#define STRING_H


class String
{
    public:
        // Construtores
        String(int novoTamanho);
        String(String &original);
        virtual ~String();

        // Métodos normais
        char charAt(int indice) const;
        void deleteCharAt(unsigned int posicao);
        void deletar(unsigned int posIni, unsigned int posFim);
        void inserir(unsigned int posicao, char letra);
        void append(char letra);
        void replace(unsigned int posicao, char letra);
        void destroy();

        // Apocalipticos
        char* toString() const;
        String clone() const;

        // getters e setters
        int length() const;

        // operators
        void operator= (String primeira);
        void operator+ (String outra);
    protected:
    private:
        char* minhaString;
        int tamanho;

};
bool operator< (String primeira, String segunda);
bool operator> (String primeira, String segunda);
bool operator<= (String primeira, String segunda);
bool operator>= (String primeira, String segunda);
bool operator== (String primeira, String segunda);
bool operator!= (String primeira, String segunda);

#endif // STRING_H
