#ifndef _FUNCOES
#define _FUNCOES

#define CANTO_INFERIOR_DIREITO 217
#define CANTO_INFERIOR_ESQUERDO 192
#define CANTO_SUPERIOR_DIREITO 191
#define CANTO_SUPERIOR_ESQUERDO 218
#define LIGACAO_INFERIOR 194
#define LIGACAO_SUPERIOR 193
#define LINHA_HORIZONTAL 196
#define LINHA_VERTICAL 179
#define FALSE 0
#define TRUE 1

typedef struct no {
	int valor;
	struct no *esq;
	struct no *dir;
	int balanco;
}T_no, *P_no;
			
int altura_raiz(P_no);
P_no balanco_direita(P_no, int *);
P_no balanco_esquerda(P_no, int *);
P_no busca_avl(P_no, int);
P_no deleta_avl(P_no, int, int *);
P_no deleta(P_no, P_no, int *);
void imprime_arvore(P_no, int, int, int, int);
P_no insere_avl(P_no, int, int *);
int maior(int, int);
P_no novo_no(int);
void quadrado(int, int, int);
int quantidade_digitos(int);

#endif
				  
				  
				  
				  
				  
				  
				  
				  
				  
				  
				  
				  
				  
				  