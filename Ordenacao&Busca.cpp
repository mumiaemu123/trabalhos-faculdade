#include <stdio.h>
#include <string.h>
#include <conio2.h>
#include <windows.h>
#include <stdlib.h>

#define TF 20

struct TpProduto
{
	int CodProd, Estoque;
	char Descr[20];
	float Preco;
};

int Busca(struct TpProduto Produto[TF], int TL, int cod)
{
	int i = 0;
	
	while(i < TL && cod != Produto[i].CodProd)
		i++;
	
	if(i<TL && cod == Produto[i].CodProd)
		return -1;
	else
		return 1;
}

void SeqIndex(struct TpProduto V[TF], int TL)
{
	int p = TL-1,i;
	struct TpProduto aux;
	while(p > 0 && V[p].CodProd < V[p-1].CodProd)
	{
		aux = V[p];
		V[p] = V[p-1];
		V[p-1] = aux;
		p--;
	}
	for(i =0; i < TL ;i++){
		printf("\n Codigo: %d, Descricao: %s, Preco: %f, Estoque: %d",V[i].CodProd, V[i].Descr, V[i].Preco, V[i].Estoque);
	}
}

void CadastroProd(struct TpProduto Produtos[TF], int &TL)
{
	int i = 0, verificacao;
	
	printf("\nDigite o codigo do produto: ");
	scanf("%d",& Produtos[TL].CodProd);
	verificacao = Busca(Produtos,TL,Produtos[TL].CodProd);
	
	while(TL<TF && Produtos[TL].CodProd > 0 && verificacao == 1)
	{	
		printf("\nDescricao: ");
		fflush(stdin);
		gets(Produtos[TL].Descr);
		printf("\nPreco: ");
		scanf("%f",& Produtos[TL].Preco);
		printf("\nEstoque: ");
		scanf("%d", & Produtos[TL].Estoque);
		TL++;
		SeqIndex(Produtos,TL);
		printf("\nCodigo: ");
		scanf("%d",& Produtos[TL].CodProd);		
		verificacao = Busca(Produtos,TL,Produtos[TL].CodProd);
		if(verificacao == -1)
		{
			printf("\n Codigo existente!");
		}	
	}
}

int main()
{
	int TL = 0;
	struct TpProduto Produtos[TF];
	CadastroProd(Produtos,TL);
	return 0;
}
