#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

struct TpProduto
{	//32B
	int CodProd, Estoque;
	char Descr[20];
	float Preco;
};

void VerifArquivo(char NomeArq[80])
{
	FILE * PtrArq = fopen(NomeArq,"rb");
	if (PtrArq == NULL) // Não encontrou o arquivo
	{
		printf("\nErro de Abertura!");
		printf("\nDeseja cria-lo (s/n) ?: ");
		if (toupper(getche()) == 'S')
		{
			PtrArq = fopen(NomeArq,"wb");
			fclose(PtrArq);
			printf("\nArquivo criado com sucesso!");
		}
		else
		{
			printf("\nO arquivo esta pronto para uso!");
			fclose(PtrArq);
		}
		getch();
	}
}

void CadProd(void)
{
	TpProduto RProd;
	FILE * PtrProd = fopen("Produtos.dat","ab+"); // Como estamos ab+ como metodo de abrir o arquivo, não é necessario verificar se ele existe ou não
	clrscr();
	printf("\n*****Cadastro de Produtos****");
	printf("\nDigite o Codigo do produto: ");
	scanf("%d", &RProd.CodProd);
	while(RProd.CodProd > 0)	
	{
		printf("\nDescricao: ")	;
		fflush(stdin);
		gets(RProd.Descr);
		
		printf("\nEstoque: ");
		scanf("%d",&RProd.Estoque);
		
		printf("\nPreco: ");
		scanf("%d",&RProd.Preco);
		fwrite(&RProd,sizeof(TpProduto),1,PtrProd);
		printf("\nCodigo: ");
		scanf("%d", &RProd.CodProd);
	}
	fclose(PtrProd);
}

void RELProd(void)
{
	TpProduto RP;	
	FILE * Ptr = fopen("Produtos.dat","rb");
	clrscr();
	printf("\n*** Relatorio de Produtos ***\n");
	if (Ptr == NULL)
		printf("\nArquivo nao encontrado!");
	else
	{
		fread(&RP,sizeof(TpProduto),1,Ptr);
		while(!feof(Ptr)) // feof(nome_buffer) é retorno de um acesso de um arquivo
		{		
			printf("d - %s - %d - %.2f\n",RP.CodProd,RP.Descr,RP.Estoque,RP.Preco);
			fread(&RP,sizeof(TpProduto),1,Ptr);
		}
	}
	getch();
	fclose(Ptr);
}


int main(void){
	char Arquivo[80];
	/*printf("\nDigite o caminho/Arquivo: ");
	fflush(stdin);
	gets(Arquivo);
	VerifArquivo(Arquivo);*/
	//CadProd();
	RELProd();
	return 0;
}
