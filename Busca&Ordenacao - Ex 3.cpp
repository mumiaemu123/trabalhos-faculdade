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

int BuscaBinaria(TpProduto Prod[TF], int TL, int cod)
{
	int inicio = 0, fim = TL-1, meio;
	meio = fim/2;
	while(inicio <= fim && cod != Prod[meio].CodProd)
	{
		if(cod > Prod[meio].CodProd)
			inicio = meio + 1;
		else
			fim = meio - 1;	
				
		meio = (inicio+fim)/2;	
	}
	if (cod == Prod[meio].CodProd)
		return meio;		
	else
		return -1;
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

void Buble(TpProduto Produto[TF], int TL)
{
	int i,aux;
	
	while(TL > 0) 
	{
		for(i = 0; i < TL - 1; i++)
		{
			if (Produto[i].CodProd > Produto[i+1].CodProd)
			{
				aux = Produto[i].CodProd;
				Produto[i].CodProd = Produto[i+1].CodProd;
				Produto[i+1].CodProd = aux;
			}
		}
		TL--;
	}
	printf("\nCodigos ordenados!\n");
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

void ConsultaProduto(TpProduto Produtos[TF], int TL)
{
	int verf;
	printf("\nConsulta de produtos\n");
	printf("\nDigite o codigo que se procura:\n");
	scanf("%d",&Produtos[TL].CodProd);
	
	while (Produtos[TL].CodProd != 0)
	{
		verf = BuscaBinaria(Produtos, TL, Produtos[TL].CodProd);
		if (verf != -1)
		{
			printf("\nCodigo: %d \n",Produtos[verf].CodProd);
			printf("\nDescricao: %s \n",Produtos[verf].Descr);
			printf("\nEstoque: %d \n",Produtos[verf].Estoque);
			printf("\nPreco: %f \n",Produtos[verf].Preco);
		}
		else
			printf("\nProduto nao encontrado!");
		
		printf("\nDigite o codigo que se procura:\n");
		scanf("%d",&Produtos[TL].CodProd);
	}
		
}

void Relatorio(TpProduto Produto[TF],int TL)
{
	printf("\n*** Relatorio de Produtos ***\n");
	int i;
	Buble(Produto,TL);
	for (i = 0; i<TL; i++)
	{
		printf("\nCodigo: %d",Produto[i].CodProd);
		printf("\nDescr: %s",Produto[i].Descr);
		printf("\nEstoque: %d",Produto[i].Estoque);
		printf("\nPreco: %f\n",Produto[i].Preco);
	}
	
}

int main()
{
	int TL = 0;
	struct TpProduto Produtos[TF];
	CadastroProd(Produtos,TL);
	ConsultaProduto(Produtos, TL);
	Relatorio(Produtos,TL);
	return 0;
}
