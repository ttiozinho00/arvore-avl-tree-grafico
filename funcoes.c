#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "conio_v3.2.4.h"
#include "console_v1.5.4.h"
#include "funcoes.h"

/*Calcula a altura da raiz*/
int altura_raiz(P_no no)
{
	int h1, h2;
	
	if(no->esq != NULL)
		h1 = altura_raiz(no->esq);
	else
		h1 = 0;
	
	if(no->dir != NULL)
		h2 = altura_raiz(no->dir);
	else 
		h2 = 0;	
	
	return 1 + maior(h1, h2);
}

/*Balanceia a árvore, se a sub-árovre da direita for maior*/
P_no balanco_direita(P_no no, int *h)
{
	P_no no_aux1, no_aux2;
	
	switch(no->balanco)
	{
		case 1:
			no->balanco = 0;
			break;
		case 0:
			no->balanco = -1;
			*h = FALSE;
			break;
		case -1:
			no_aux1 = no->dir;
			
			/*Rotação a esquerda*/
			if(no_aux1->balanco <= 0) 
			{
				printf("Rotacao esquerda, valor: %d", no->valor);
				no->dir = no_aux1->esq;
				no_aux1->esq = no;
				
				/*Atualização do balanço*/
				if(no_aux1->balanco == 0)
				{
					no->balanco = -1;
					no_aux1->balanco = 1;
					*h = FALSE;
				}
				else
				{
					no->balanco = no_aux1->balanco = 0;
				}
				no = no_aux1;
			}
			else /*Rotação dupla a esquerda*/
			{
				printf("Rotacao dupla a esquerda. ");
				printf("Rotacao a direita, valor: %d. ", no_aux1->valor);
				no_aux2 = no_aux1->esq;
				no_aux1->esq = no_aux2->dir;
				no_aux2->dir = no_aux1;
				printf("Rotacao a esquerda, valor: %d", no->valor);
				no->dir = no_aux2->esq;
				no_aux2->esq = no;
				
				/*Atualização do balanço*/
				if(no_aux2->balanco == -1)
					no->balanco = 1;
				else	
					no->balanco = 0;
				if(no_aux2->balanco == 1)
					no_aux1->balanco = -1;
				else
					no_aux1->balanco = 0;
				
				no = no_aux2;
				no_aux2->balanco = 0;
			}
	}
	return no;
}

/*Balanceia a árvore, se a sub-árovre da esquerda for maior*/
P_no balanco_esquerda(P_no no, int *h)
{
	P_no no_aux1, no_aux2;
	
	switch(no->balanco)
	{
		case -1:
			no->balanco = 0;
			break;
		case 0:
			no->balanco = 1;
			*h = FALSE;
			break;
		case 1:
			no_aux1 = no->esq;
			
			if(no_aux1->balanco >= 0)
			{
				/*Rotação a direita*/
				printf("Rotacao a direita, valor: %d", no->valor);
				no->esq = no_aux1->dir;
				no_aux1->dir = no;
				
				/*Atualização do balanço*/
				if(no_aux1->balanco == 0)
				{
					no->balanco = 1;
					no_aux1->balanco = -1;
					*h = FALSE;
				}
				else
				{
					no->balanco = no_aux1->balanco = 0;
				}
				no = no_aux1;
			}
			else
			{
				/*Rotação dupla a direita*/
				printf("Rotação dupla a direita. ");
				printf("Rotacao esquerda, valor: %d. ", no_aux1->valor);
				no_aux2 = no_aux1->dir;
				no_aux1->dir = no_aux2->esq;
				no_aux2->esq = no_aux1;
				printf("Rotacao direita, valor: %d", no->valor);
				no->esq = no_aux2->dir;
				no_aux2->dir = no;
				
				/*Atualização do balanço*/
				if(no_aux2->balanco == 1)
					no->balanco = -1;
				else
					no->balanco = 0;
				
				if(no_aux2->balanco == -1)
					no_aux1->balanco = 1;
				else
					no_aux1->balanco = 0;
				
				no = no_aux2;
				no_aux2->balanco = 0;
			}
	}
	return no;
}

/*Realiza a busca em uma árvore binária*/
P_no busca_avl(P_no no, int valor)
{
	if(no == NULL)
		return no;
	else
	{
		if(no->valor == valor)
			return no;
		else if(no->valor < valor)
			return busca_avl(no->esq, valor);
		else 
			return busca_avl(no->dir, valor);
	}
}

/*Deleta um valor da árvore*/
P_no deleta_avl(P_no no, int valor, int *h)
{
	P_no no_aux;
	
	if(!no)
	{
		printf("Valor nao existe!");
		return no;
	}
	else
	{
		if(valor < no->valor)
		{
			no->esq = deleta_avl(no->esq, valor, h);
			
			if(*h)
				no = balanco_direita(no, h);
		}
		else
		{
			if(valor > no->valor)
			{
				no->dir = deleta_avl(no->dir, valor, h);
				
				if(*h)
					no = balanco_esquerda(no, h);
			}
			else
			{
				no_aux = no;
				
				if(no_aux->dir == NULL)
				{
					no = no_aux->esq;
					*h = TRUE;
					free(no_aux);
				}
				else
				{
					if(no_aux->esq == NULL)
					{
						no = no_aux->dir;
						*h = TRUE;
						free(no_aux);
					}
					else
					{
						no_aux->dir = deleta(no_aux->dir, no_aux, h);
						
						if(*h)
							no = balanco_esquerda(no, h);
					}
				}
			}
		}
	}
	return no;
}

P_no deleta(P_no succ, P_no no, int *h)
{
	P_no aux = succ;
	
	if(succ->esq != NULL)
	{
		succ->esq = deleta(succ->esq, no, h);
		
		if(*h)
			succ = balanco_direita(succ, h);
	}
	else
	{
		aux = succ;
		no->valor = succ->valor;
		succ = succ ->dir;
		free(aux);
		*h = TRUE;
	}
	return succ;
}

/*Desenha a árvore AVL*/
void imprime_arvore(P_no no, int coluna, int linha, int level, int lado)
{
	int coluna_limite, distancia, i;
	COORD max_dimensao;
	
	max_dimensao = MaxDimensaoJanela();
	coluna_limite = max_dimensao.X; 
	
	/*Ajuste do limite da coluna de acordo com o tamanho da tela*/
	if (coluna_limite < 247)
		coluna_limite = 128; 
	else
		coluna_limite = 256; 
	
	if (no != NULL)
	{
		/*Cálcula o espaçamento entre os nós, diminuindo a cada nível*/
		distancia = ceil((coluna_limite/2) / pow(2, level)); 
		
		/*Imprime o valor*/
		quadrado(no->valor, coluna-1, linha);
		
		/*lado = 0, nó raiz, não faz nenhuma ligação
		  lado = 1, ligação a esquerda
		  lado = 2, ligação a direita*/
		if(lado)
		{
			if(lado == 1)
			{
				for(i = coluna; i <= (coluna+(distancia*2)); i++)
				{
					gotoxy(i, linha-1);
					if (i == coluna) /*Conecta um nó filho com a ligação do nó pai*/
					{
						printf("%c", CANTO_SUPERIOR_ESQUERDO);
						gotoxy(i, linha);
						printf("%c", LIGACAO_SUPERIOR);
					}
					else if (i == (coluna+(distancia*2))) /*Ponto de encontro entre dois nós filhos*/
					{
						printf("%c", LIGACAO_SUPERIOR);
						
						if(lado > 0)
						{
							gotoxy(i, linha-2);
							printf("%c", LIGACAO_INFERIOR);
						}
							
					}
					else
						printf("%c", LINHA_HORIZONTAL);
				}
			}
			
			if(lado == 2) 
			{
				for(i = coluna; i >= coluna-(distancia*2); i--)
				{
					gotoxy(i, linha-1);
					
					if(i == coluna) /*Conecta um nó filho com a ligação do nó pai*/
					{
						printf("%c", CANTO_SUPERIOR_DIREITO);
						gotoxy(i, linha);
						printf("%c", LIGACAO_SUPERIOR);
					}
					else if (i == (coluna-(distancia*2))) /*Ponto de encontro entre dois nós filhos*/
					{
						printf("%c", LIGACAO_SUPERIOR);
						
						if (lado > 0)
						{
							gotoxy(i, linha-2);
							printf("%c", LIGACAO_INFERIOR);
						}
					}
						
					else 
						printf("%c", LINHA_HORIZONTAL);
				}
			}
		}
				
		lado = 1;
		imprime_arvore(no->esq, coluna-distancia, linha+4, level+1, lado); 
		lado = 2;
		imprime_arvore(no->dir, coluna+distancia, linha+4, level+1, lado);
	}
	linha = linha-4;
}

/*Insere um valor na árvore, váriavel h indica se houve ou não alteração na altura da sub-árvore do nó em questão*/
P_no insere_avl(P_no no, int valor, int *h)
{
	P_no no_aux, no_aux2;
	
	/*Encontra o local onde o nó será inserido*/
	if (no == NULL)
	{
		*h = TRUE;
		no = novo_no(valor);
		return no;
		
	}
	else if (valor < no->valor)
	{
		no->esq = insere_avl(no->esq, valor, h);
		
		if(*h)
		{
			switch(no->balanco)
			{
				case -1 :
					no->balanco = 0;
					*h = FALSE;
					break;
				case 0 :
					no->balanco = 1;
					break;
				case 1 :
					no_aux = no->esq;
					
					/*Rotação a direita*/
					if (no_aux->balanco == 1) 
					{
						printf("Rotacao a direita, valor: %d", no->valor);
						no->esq = no_aux->dir;
						no_aux->dir = no;
						no->balanco = 0;
						no = no_aux;
					}
					else /*Rotação dupla a direita*/
					{
						printf("Rotacao dupla a direita. ");
						printf("Rotacao a esquerda, valor: %d. ", no_aux->valor);
						no_aux2 = no_aux->dir;
						no_aux->dir = no_aux2->esq;
						printf("Rotacao a direita, valor: %d", no->valor);
						no_aux2->esq = no_aux;
						no->esq = no_aux2->dir;
						no_aux2->dir = no;
						
						/*Atualização do balanco*/
						if (no_aux2->balanco == 1)
							no->balanco = -1;
						else
							no->balanco = 0;
						if (no_aux2->balanco == -1)
							no->balanco = 1;
						else
							no_aux->balanco = 0;
						
						no = no_aux2;
					}
					no->balanco = 0;
					*h = FALSE;
					break;
			}
		}
	}
	else if (valor > no->valor)
	{
		no->dir = insere_avl(no->dir, valor, h);
		
		if(*h)
		{
			switch(no->balanco)
			{
				case 1 :
					no->balanco = 0;
					*h = FALSE;
					break;
				case 0 :
					no->balanco = -1;
					break;
				case -1 :
					no_aux = no->dir;
					
					/*Rotação a esquerda*/
					if (no_aux->balanco == -1) 
					{
						printf("Rotacao a esquerda, valor: %d", no->valor);
						no->dir = no_aux->esq;
						no_aux->esq = no;
						no->balanco = 0;
						no = no_aux;
					}
					else /*Rotação dupla a esquerda*/
					{
						printf("Rotacao dupla a esquerda. ");
						printf("Rotacao a direita, valor: %d. ", no_aux->valor);
						no_aux2 = no_aux->esq;
						no_aux->esq = no_aux2->dir;
						no_aux2->dir = no_aux;
						printf("Rotacao a esquerda, valor: %d", no->valor);
						no->dir = no_aux2->esq;
						no_aux2->esq = no;
						
						/*Atualização do balanço*/
						if (no_aux2->balanco == -1)
							no->balanco = 1;
						else
							no->balanco = 0;
						if (no_aux2->balanco == 1)
							no->balanco = -1;
						else
							no_aux->balanco = 0;
						
						no = no_aux2;
					}
					no->balanco = 0;
					*h = FALSE;
					break;
			}
		}
	}
	else if (valor == no->valor)
	{
		printf("O valor ja existe!");
		return no;
	}
	
	return no;
}

/*Retorna o maior valor*/
int maior(int a, int b)
{
	if (a > b)
		return a;
	else 
		return b;
}

/*Cria um novo nó*/
P_no novo_no(int valor)
{
	P_no no;
	
	no = (P_no) malloc(sizeof(T_no));
	no->valor = valor;
	no->esq = NULL;
	no->dir = NULL;
	no->balanco = 0;
	
	return no;
}

/*Cria um quadrado em volta de um valor*/
void quadrado(int valor, int coluna, int linha)
{
	int i, numero_digitos;
	
	numero_digitos = quantidade_digitos(valor);
	
	/*Reserva um espaço a mais, caso o número seja negativo*/
	if (valor < 0)
		numero_digitos++;

	coluna = coluna - (ceil(numero_digitos/2));
	
	gotoxy(coluna, linha);
	printf("%c", CANTO_SUPERIOR_ESQUERDO);
	
	for (i = 0; i < numero_digitos; i++)
		printf("%c", LINHA_HORIZONTAL);
	
	printf("%c", CANTO_SUPERIOR_DIREITO);
	printf("\n");
	
	gotoxy(coluna, linha+1);
	
	printf("%c", LINHA_VERTICAL);
	printf("%d", valor);
	printf("%c", LINHA_VERTICAL);
	printf("\n");
	
	gotoxy(coluna, linha + 2);
	
	printf("%c", CANTO_INFERIOR_ESQUERDO);
	
	for (i = 0; i < numero_digitos; i++)
		printf("%c", LINHA_HORIZONTAL);
	
	printf("%c", CANTO_INFERIOR_DIREITO);
	printf("\n");
}

/*Retorna a quantidade de dígitos de um número*/
int quantidade_digitos(int valor)
{
	int contador = 0;
	
	if(valor == 0)
		return 1;
	else
	{
		while(valor != 0)
		{
			contador++;
			valor = valor/10;
		}
	}
	return contador;
}










