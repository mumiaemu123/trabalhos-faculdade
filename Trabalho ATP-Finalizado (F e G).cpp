//Exercio F

void Relatorio(void)
{
	
	int Qtde;
	TpProduto RE;
	FILE * PtrR = fopen("Produtos.dat","rb");
	
	if(PtrR==NULL)
		printf("\nErro de abertura!\n");
	else 
	{
		printf("\n*** Produtos por preco em ordem descrecente ***\n");
		fseek(PtrR,0,2); 
		Qtde = ftell(PtrR)/sizeof(TpProduto);
		while(Qtde > 0)
		{
			fseek(PtrR,(Qtde - 1)*sizeof(TpProduto),0);
			fread(&RE,sizeof(TpProduto),1,PtrR);
			printf("\n Codigo: %d, Descricao: %s, Preco: %.2f, Estoque: %d \n", RE.CodProd, RE.Descr, RE.Preco, RE.Estoque);
			Qtde--;
		}
		fclose(PtrR);
	}	
	getch();
}

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

void Selecaodireta(void)
{
	int posMaior,Qtde;
	TpProduto RA, Maior;
	FILE *PtrOrdem = fopen("Produtos.dat","rb+");
	FILE * PtrTemp = fopen("Temp.dat","wb");
	if(PtrOrdem==NULL)
		printf("\nErro de abertura!\n");
	else
	{
		  while(!feof)
		  {
		  	fread(&RA,sizeof(TpProduto),1,PtrOrdem);
		  	fwrite(&RA,sizeof(TpProduto),1,PtrTemp);
		  }
		  fclose(PtrTemp);
		  fclose(PtrOrdem);
		  PtrTemp = fopen("Temp.dat","rb+");
		  fseek(PtrOrdem,0,2); 
		  Qtde = ftell(PtrOrdem)/sizeof(TpProduto);
		  while(Qtde > 1)
		  {
		  	fseek(PtrTemp,(Qtde - 1)*sizeof(TpProduto),0);
			fread(&RA,sizeof(TpProduto),1,PtrTemp);
			
			posMaior = PosicaoMaior(PtrTemp,Qtde);
				
			fseek(PtrTemp,posMaior*sizeof(TpProduto),0);
			fread(&Maior,sizeof(TpProduto),1,PtrTemp);
				
			if (posMaior < Qtde - 1) 
			{
				fseek(PtrTemp,(Qtde - 1)*sizeof(TpProduto),0);
				fwrite(&Maior,sizeof(TpProduto),1,PtrTemp);
					
				fseek(PtrTemp,posMaior*sizeof(TpProduto),0);
				fwrite(&RA,sizeof(TpProduto),1,PtrTemp);
			}
			Qtde--;
		  }		
		printf("\nArquivo Ordenado com Sucesso!\n");
		fclose(PtrTemp);
	}
	getch();
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
	getch();
}
//Fim exercico G
