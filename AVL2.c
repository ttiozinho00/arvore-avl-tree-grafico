#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "conio_v3.2.4.h"
#include "console_v1.5.4.h"
#include "funcoes.h"

int main(int argc, char *argv[])
{
	int i, centro, coluna_limite, valor, linha_limite, level=1, fim_arvore_antes=1, h = FALSE, opcao, flag=1;
	P_no raiz = NULL, raiz_busca = NULL;
	COORD max_dimensao;
	
	/*Silenciar parâmetros argc, argv*/
	argc = argc;
	argv = argv;

	/*Dimensoes limite*/
	max_dimensao = MaxDimensaoJanela();
	coluna_limite = max_dimensao.X;
	linha_limite = max_dimensao.Y;

	/*Redimensionamento da tela*/
	setDimensaoJanela(coluna_limite, linha_limite);
	setPosicaoJanela(1, 1);
	
	/*limite da área de impressão da árvore, de acordo com o tamanho da tela*/
	if(coluna_limite < 200)
		coluna_limite = 128; 
	else
		coluna_limite = 256; 
	
	centro = (coluna_limite/2) + ((max_dimensao.X - coluna_limite)/2) ;
	
	clrscr();
	highvideo();
	
	while(flag)
	{
		
		gotoxy(1, 10);
		for(i = 0; i < max_dimensao.X; i++)
			printf("%c", LINHA_HORIZONTAL);
		
		imprime_arvore(raiz, centro, 11, level, 0); /*Imprime a árvore antes da operação*/
		
		if(raiz) 
			fim_arvore_antes = altura_raiz(raiz); /* Calcula a altura da raiz, para localizar o final da mesma*/
		
		gotoxy(1, 1);
		printf("1- Inserir\n");
		printf("2- Deletar\n");
		printf("3- Buscar\n");
		printf("4- Sair\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		
		switch(opcao)
		{
			case 1:
				printf("INSERIR VALOR: ");
				scanf("%d", &valor);
				raiz = insere_avl(raiz, valor, &h);
				break;
			case 2:
				printf("DELETAR VALOR: ");
				scanf("%d", &valor);
				raiz = deleta_avl(raiz, valor, &h);
				break;
			case 3:
				printf("BUSCAR VALOR: ");
				scanf("%d", &valor);
				
				raiz_busca = raiz;
				raiz_busca = busca_avl(raiz_busca, valor);
				
				if(raiz_busca)
					printf("Valor encontrado: %d", raiz_busca->valor);
				else
					printf("Valor nao encontrado.");
				break;
			case 4:
				flag = 0;
				break;
		}
		
		imprime_arvore(raiz, centro, (fim_arvore_antes*4)+15, level, 0); /*Imprime a árvore após a operação*/
	
		gotoxy(1, 9);
		printf("Pressione qualquer tecla para continuar...");
		
		getch();
		clrscr();
	}
	
	return 0;
}