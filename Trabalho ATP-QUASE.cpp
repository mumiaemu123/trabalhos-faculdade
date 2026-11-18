#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

struct TpProduto
{              //32B
    int CodProd, Estoque;
    char Descr[20];
    float Preco;
};

void VerifArquivo(char NomeArq[80])
{
	FILE *PtrArq = fopen(NomeArq,"rb");
	if (PtrArq == NULL) //Não abriu o Arquivo
	{
		printf("\nErro de Abertura!\nDeseja cria-lo (S/N)? ");
		if (toupper(getche()) == 'S')
		{
			PtrArq = fopen(NomeArq,"wb");
			fclose(PtrArq);
			printf("\nArquivo criado com sucesso!\n");
		}
	}
	else
		{
			printf("\nO Arquivo esta pronto para uso!\n");
			fclose(PtrArq);
		}
	getch();
}

int BuscaCodProd(FILE *PtrArq, int Codigo)
{
	TpProduto RP;
	rewind(PtrArq);
	fread(&RP,sizeof(TpProduto),1,PtrArq);
	while (!feof(PtrArq) && Codigo!=RP.CodProd)
		fread(&RP,sizeof(TpProduto),1,PtrArq);
	
	if (!feof(PtrArq))
		return ftell(PtrArq)-sizeof(TpProduto);
	else
		return -1;
}

void CADProd(void)
{
	TpProduto RProd;
	int pos;
	FILE *PtrProd = fopen("Produtos.dat","ab+");
	clrscr();
	printf("*** Cadastro de Produtos ***\n");
	printf("Codigo: "); scanf("%d",&RProd.CodProd);
	while (RProd.CodProd>0)
	{
		pos = BuscaCodProd(PtrProd,RProd.CodProd);
		if (pos == -1) //Não encontrou
		{
			printf("Descricao: ");  fflush(stdin);
			gets(RProd.Descr);
			printf("Estoque: ");  scanf("%d",&RProd.Estoque);
			printf("Preco: R$ ");  scanf("%f",&RProd.Preco);
			
			fwrite(&RProd,sizeof(TpProduto),1,PtrProd);
		}
		else
			printf("\nCodigo ja Cadastrado!\n");
		
		Sleep(1000);
		printf("\nCodigo: "); scanf("%d",&RProd.CodProd);
	}
	fclose(PtrProd);
}

void CONSProd(void)
{
	TpProduto R;
	int p;
	FILE *PtrProd = fopen("Produtos.dat","rb");
	clrscr();	
	printf("\n### Consulta por Codigo do Produto ###\n");
	if(PtrProd == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("\nCodigo a procurar: ");
			scanf("%d",&R.CodProd);
			while (R.CodProd>0)
			{
				p = BuscaCodProd(PtrProd,R.CodProd); //Bytes
				if(p==-1)
					printf("\nProduto nao encontrado!\n");
				else
					{
						fseek(PtrProd,p,0);  // 0 ... SEEK_SET
						fread(&R,sizeof(TpProduto),1,PtrProd);
						printf("\nDetalhes do Produto:\n");
						printf("Codigo: %d\n",R.CodProd);
						printf("Descricao: %s\n",R.Descr);
						printf("Estoque: %d\n",R.Estoque);
						printf("Preco: R$ %.2f\n",R.Preco);
					}
				
				Sleep(1000);
				printf("\nCodigo a procurar: ");
				scanf("%d",&R.CodProd);
			}
			fclose(PtrProd);
		}
}


void ALTProd(void)
{
	TpProduto R;
	int p;
	FILE *PtrProd = fopen("Produtos.dat","rb+");
	clrscr();	
	printf("\n### Altera por Codigo do Produto ###\n");
	if(PtrProd == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("\nCodigo a alterar: ");
			scanf("%d",&R.CodProd);
			while (R.CodProd>0)
			{
				p = BuscaCodProd(PtrProd,R.CodProd); //Bytes
				if(p==-1)
					printf("\nProduto nao encontrado!\n");
				else
					{
						fseek(PtrProd,p,0);  // 0 ... SEEK_SET
						fread(&R,sizeof(TpProduto),1,PtrProd);
						printf("\nDetalhes do Produto:\n");
						printf("Codigo: %d\n",R.CodProd);
						printf("Descricao: %s\n",R.Descr);
						printf("Estoque: %d\n",R.Estoque);
						printf("Preco: R$ %.2f\n",R.Preco);
						printf("\nDeseja alterar (S/N)? ");
						if(toupper(getche())=='S')
						{
							printf("Descricao: "); fflush(stdin);
							gets(R.Descr);
							printf("Estoque: ");  scanf("%d",&R.Estoque);
							printf("Preco: R$ "); scanf("%f",&R.Preco);
							fseek(PtrProd,p,0);
							fwrite(&R,sizeof(TpProduto),1,PtrProd);
							printf("\nProduto alterado com Suuuucesso!\n");
						}
					}
				
				Sleep(1000);
				printf("\nCodigo a alterar: ");
				scanf("%d",&R.CodProd);
			}
			fclose(PtrProd);
		}
}

void EXCFISProd(void)
{
	TpProduto R;
	int p, Codigo;
	FILE *PtrProd = fopen("Produtos.dat","rb");
	clrscr();	
	printf("\n### Excluir por Codigo do Produto ###\n");
	if(PtrProd == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("\nCodigo a excluir: ");
			scanf("%d",&Codigo);
			if (Codigo>0)
			{
				p = BuscaCodProd(PtrProd,Codigo); //Bytes
				if(p==-1)
					printf("\nProduto nao encontrado!\n");
				else
					{
						fseek(PtrProd,p,0);  // 0 ... SEEK_SET
						fread(&R,sizeof(TpProduto),1,PtrProd);
						printf("\nDetalhes do Produto:\n");
						printf("Codigo: %d\n",R.CodProd);
						printf("Descricao: %s\n",R.Descr);
						printf("Estoque: %d\n",R.Estoque);
						printf("Preco: R$ %.2f\n",R.Preco);
						printf("\nConfirma Exclusao (S/N)? ");
						if(toupper(getche())=='S')
						{
							FILE *PtrTemp = fopen("Temp.dat","wb");
							rewind(PtrProd); // fseek(PtrProd,0,0);
							fread(&R,sizeof(TpProduto),1,PtrProd);
							while(!feof(PtrProd))
							{
								if (Codigo != R.CodProd)
									fwrite(&R,sizeof(TpProduto),1,PtrTemp);
									
								fread(&R,sizeof(TpProduto),1,PtrProd);
							}
							fclose(PtrTemp);
							fclose(PtrProd);
							remove("Produtos.dat");
							rename("Temp.dat","Produtos.dat");
							printf("\nProduto excluido com Suuuucesso!\n");
							getch();
						}
						else fclose(PtrProd);
					}
			}
			else fclose(PtrProd);
		}
}

void RELProd(void)
{
	TpProduto RP;
	FILE *Ptr = fopen("Produtos.dat","rb");
	clrscr();
	printf("\n*** Relatorio de Produtos ***\n");
	if (Ptr==NULL)
		printf("\nArquivo nao encontrado!\n");
	else
		{
			fread(&RP,sizeof(TpProduto),1,Ptr);
			while(!feof(Ptr))
			{
				printf("%d - %s - %d - %.2f\n",RP.CodProd,RP.Descr,RP.Estoque,RP.Preco);
				fread(&RP,sizeof(TpProduto),1,Ptr);
			}
			fclose(Ptr);
		}
	
	getch();
}

//Não é o Bubble Sort
void ORDCodProd(void)
{
	int a,b,QtdeReg;
	TpProduto RA, RB;
	FILE *PtrProd = fopen("Produtos.dat","rb+");
	if(PtrProd==NULL)
		printf("\nErro de abertura!\n");
	else
		{
		  fseek(PtrProd,0,2); // fseek(Ptr,0,SEEK_END);
		  QtdeReg = ftell(PtrProd)/sizeof(TpProduto);
		  for(a=0; a<QtdeReg-1; a++)
			for(b=a+1; b<QtdeReg; b++)
			{
				fseek(PtrProd,a*sizeof(TpProduto),0);
				fread(&RA,sizeof(TpProduto),1,PtrProd);
				
				fseek(PtrProd,b*sizeof(TpProduto),0);
				fread(&RB,sizeof(TpProduto),1,PtrProd);
				
				if (RA.CodProd > RB.CodProd) //Troca
				{
					fseek(PtrProd,a*sizeof(TpProduto),0);
					fwrite(&RB,sizeof(TpProduto),1,PtrProd);
				
					fseek(PtrProd,b*sizeof(TpProduto),0);
					fwrite(&RA,sizeof(TpProduto),1,PtrProd);
				}
			}
			
			fclose(PtrProd);
			printf("\nArquivo Ordenado com Suuuucesso!\n");
		}
	getch();
}

//Exercio F
int PosicaoMaior(FILE * PtrMaior,int TL)
{
	int i,PosMaior = 0;
	TpProduto Maior, Aux;
	
	fseek(PtrMaior,0,0);
	fread(&Maior,sizeof(TpProduto),1,PtrMaior);

	for (i = 1; i < TL; i++)
	{
		fseek(PtrMaior,i*sizeof(TpProduto),0);
		fread(&Aux,sizeof(TpProduto),1,PtrMaior);
		if (Aux.Preco > Maior.Preco)
		{
			Maior = Aux;
			PosMaior = i;
		}
	}
	return PosMaior;
}

void Selecaodireta(struct TpProduto Produto[TF], int TL)
{
	int a,posMaior,Qtde;
	TpProduto RA, Maior;
	FILE *PtrOrdem = fopen("Produtos.dat","rb+");
	if(PtrProd==NULL)
		printf("\nErro de abertura!\n");
	else
		{
		  fseek(PtrOrdem,0,2); 
		  Qtde = ftell(PtrOrdem)/sizeof(TpProduto);
		  for(a=0; a<Qtde; a++)
		  {
		  	fseek(PtrOrdem,a*sizeof(TpProduto),0);
			fread(&RA,sizeof(TpProduto),1,PtrProd);
			
			posMaior = PosicaoMaior(PtrProd,TL);
				
			fseek(PtrOrdem,posMaior*sizeof(TpProduto),0);
			fread(&Maior,sizeof(TpProduto),1,PtrProd);
				
			if (posMaior < Qtde - 1) 
			{
				fseek(PtrOrdem,a*sizeof(TpProduto),0);
				fwrite(&Maior,sizeof(TpProduto),1,PtrProd);
				
				fseek(PtrOrdem,posMaior*sizeof(TpProduto),0);
				fwrite(&RA,sizeof(TpProduto),1,PtrProd);
			}
		  }		
			fclose(PtrProd);
			printf("\nArquivo Ordenado com Suuuucesso!\n");
		}
	getch();

	
	int i, PosMaior;
	struct TpProduto Aux;

	while (TL > 1)
	{
		PosMaior = PosicaoMaior(Produto, TL);
		if (PosMaior < TL - 1)
		{
			Aux = Produto[PosMaior];
			Produto[PosMaior] = Produto[TL - 1];
			Produto[TL - 1] = Aux;
		}
		TL--;
	}
}

void Relatorio(struct TpProduto Produto[TF],int TL)
{
	printf("\n*** Produtos por preco em ordem descrecente ***\n");
	while(TL > 0)
	{
		printf("\n Codigo: %d, Descricao: %s, Preco: %.2f, Estoque: %d \n", Produto[TL-1].CodProd, Produto[TL-1].Descr, Produto[TL-1].Preco, Produto[TL-1].Estoque);
		TL--;
	}
}
//Fim do Exercicio F
// Começo do exercicio G

void Explicacao(void)
{
	printf("\n*** Explicacao sobre a complexidade dos algoritmos de Busca e Ordenacao ***\n");

	printf("\n\n### 1. O que e complexidade? ###\n\n");
	printf("\nA complexidade de um algoritmo representa o esforco necessario para sua execucao, considerando principalmente a quantidade de operacoes realizadas. Quanto maior a quantidade de elementos processados, maior pode ser o tempo necessario para concluir a tarefa.\n");

	printf("\n\n### 2. Complexidade dos algoritmos de busca ###\n\n");
	printf("\nBusca Exaustiva: Percorre os elementos um por um ate encontrar o valor procurado. Quanto maior a lista, maior podera ser a quantidade de verificacoes necessarias.\n");
	printf("\nBusca com Sentinela: Funciona de maneira semelhante a Busca Exaustiva, mas utiliza uma posicao adicional para facilitar o encerramento da busca. Mesmo assim, pode precisar percorrer todos os elementos.\n");
	printf("\nBusca Sequencial Indexada: Trabalha com uma lista ordenada e percorre os elementos ate encontrar o valor procurado ou um elemento maior que ele. A ordenacao permite encerrar a busca antecipadamente em algumas situacoes.\n");
	printf("\nBusca Binaria: E mais eficiente para localizar elementos, pois verifica o valor central e descarta metade da lista a cada comparacao. Dessa forma, consegue encontrar informacoes com poucas verificacoes, mesmo em listas grandes. Porem, exige que os elementos estejam ordenados.");

	printf("\n\n### 3. Complexidade dos algoritmos de ordenacao ###\n\n");

	printf("\nInsercao Direta: Organiza os elementos inserindo cada valor em sua posicao correta. Apresenta melhor desempenho quando os dados ja estao ordenados ou parcialmente organizados, mas exige mais operacoes quando estao em ordem inversa.\n");
	printf("\nOrdenacao por Bolhas (Bubble Sort): Compara elementos vizinhos e realiza trocas ate organizar toda a lista. Como precisa realizar varias passagens pelo vetor, pode exigir muitas operacoes, principalmente quando existem muitos elementos.\n");
	printf("\nSelecao Direta: Procura o maior elemento da parte ainda nao ordenada e coloca-o na posicao correta. Repete esse processo ate organizar toda a lista, realizando varias verificacoes mesmo quando os dados ja estao ordenados.\n");
}
//Fim exercico G
		

int main(void)
{
	char Arquivo[80];
	printf("\nDigite o Caminho/Arquivo: ");
	fflush(stdin);
	gets(Arquivo);
	VerifArquivo(Arquivo);
	CADProd();
	RELProd();
	CONSProd();
	ALTProd();
	RELProd();
	ORDCodProd();
	RELProd();
	EXCFISProd();
	RELProd();
	return 0;
}
