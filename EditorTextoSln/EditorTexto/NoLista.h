#pragma once
template <class Tipo>
class NoLista
{
public:
	
	NoLista() : dado()
	{

	}

	
	NoLista(const Tipo &novoDado) : dado(novoDado)
	{

	}

	
	NoLista(const Tipo &novoDado, NoLista* Proximo, NoLista* Anterior) : dado(novoDado), prox(Proximo), ante(Anterior)
	{

	}

	
	NoLista(const NoLista<Tipo> &novoDado) : dado(novoDado.getDado()), prox(novoDado.getProximo()), ante(novoDado.getAnterior())
	{

	}

	
	NoLista(NoLista<Tipo> *novoDado) // atualiza apenas a info
	{
		this->dado = Tipo(novoDado->getDado());
		this->ante = NULL;
		this->prox = NULL;
	}

	
	NoLista(NoLista<Tipo> *novoDado, NoLista<Tipo> *novoProximo, NoLista<Tipo> *novoAnte) : dado(novoDado->getDado()), prox(novoProximo), ante(novoAnte)
	{
		/*this->dado = Tipo(novoDado->getDado());
		this->prox = new NoLista<Tipo>(novoProximo);
		this->ante = new NoLista<Tipo>(novoAnte);*/
	}

	
	~NoLista()
	{

	}

	
	NoLista<Tipo>* getProximo() const
	{
		return prox;
	}

	
	Tipo getDado() const
	{
		return dado;
	}

	
	NoLista<Tipo>* getAnterior() const
	{
		return ante;
	}

	
	void setProximo(NoLista *NovoProx)
	{
		this->prox = NovoProx;
	}

	
	void setDado(Tipo novoDado)
	{
		this->dado = novoDado;
	}

	
	void setAnterior(NoLista *NovoAnte)
	{
		this->ante = NovoAnte;
	}

	
	void setProximo(NoLista NovoProx)
	{
		*this->prox = NovoProx;
	}

	
	void setAnterior(NoLista NovoAnte)
	{
		*this->ante = NovoAnte;
	}

protected:
	Tipo dado;
	NoLista<Tipo>* ante;
	NoLista<Tipo>* prox;
private:
};