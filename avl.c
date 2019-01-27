//Inlcuindo bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

/****************************************
 * Prática de Árvores AVL
 */

#define max(x,y) ((x>y) ? x : y)
#define mesmo_sinal(x,y) ( ((x>0)&&(y>0)) || ((x<0)&&(y<0)) )
#define fatal_error(s) (printf("%s\n",s), exit(1))

struct avl_node
{
   int chave;
   struct avl_node *esq;
   struct avl_node *dir;
   int altura;
};
typedef struct avl_node *AVL_PTR;

// Fornece a altura da árvore
int altura( AVL_PTR p )
{
   if( p == 0 )
      return -1;
   else
      return p->altura;
}

// Fornece o fator de balanceamento de um nó
int FB( AVL_PTR p )
{
   if (p == 0) return 0;
   return altura(p->dir) - altura(p->esq);
}

/* Esta função deve ser chamada apenas se k2 tem o filho esquerdo. */
/* Realiza uma rotação simples entre k2 e seu filho da esquerda. */
/* Atualiza as alturas. Retorna a nova raiz. */
AVL_PTR rotacao_simples_esq( AVL_PTR k2 )
{
printf("Aplicando rotacao simples a esquerda em %d\n", k2->chave);
   AVL_PTR k1;
   k1 = k2->esq;
   k2->esq = k1->dir;
   k1->dir = k2;
   k2->altura = max( altura(k2->esq), altura(k2->dir) ) + 1;
   k1->altura = max( altura(k1->esq), k2->altura ) + 1;
   return k1;  /* Nova raiz */
}

/* Esta função deve ser chamada apenas se k2 tem o filho direito. */
/* Realiza uma rotação simples entre k2 e seu filho da direita. */
/* Atualiza as alturas. Retorna a nova raiz. */
AVL_PTR rotacao_simples_dir( AVL_PTR k1 )
{
printf("Aplicando rotacao simples a direita em %d\n", k1->chave);
   AVL_PTR k2;
   k2 = k1->dir;
   k1->dir = k2->esq;
   k2->esq = k1;
   k1->altura = max( altura(k1->dir), altura(k1->esq) ) + 1;
   k2->altura = max( k1->altura, altura(k2->dir) ) + 1;
   return k2;  /* Nova raiz */
}

/* Esta função deve ser chamada apenas se k3 tem o filho esquerdo. */
/* e o filho esquerdo de k3 tem um filho direito */
/* Realiza uma rotação dupla pela esquerda. Atualiza as alturas */
AVL_PTR rotacao_dupla_esq( AVL_PTR k3 )
{
printf("Aplicando rotacao dupla a esquerda em %d\n", k3->chave);
   /* rotação simples entre k1 e k2 */
   k3->esq = rotacao_simples_dir( k3->esq );
   /* rotação simples entre k3 e k2 */
   return( rotacao_simples_esq( k3 ) );
}

/* Esta função deve ser chamada apenas se k3 tem o filho direito. */
/* e o filho direito de k3 tem um filho esquerdo */
/* Realiza uma rotação dupla pela direita. Atualiza as alturas */
AVL_PTR rotacao_dupla_dir( AVL_PTR k3 )
{
printf("Aplicando rotacao dupla a direita em %d\n", k3->chave);
   /* rotação simples entre k1 e k2 */
   k3->dir = rotacao_simples_esq( k3->dir );
   /* rotação simples entre k3 e k2 */
   return( rotacao_simples_dir( k3 ) );
}

// Insere uma chave x em uma subárvore T
AVL_PTR avl_insere( int x, AVL_PTR T )
{
   if( T == 0 )
   {  /* Cria e retorna uma árvore com um nó */
      T = (AVL_PTR) malloc ( sizeof (struct avl_node) );
      if( T == 0 ) fatal_error("Memoria insuficiente!!!");
      else
      {
         T->chave = x; T->altura = 0;
         T->esq = T->dir = 0;
      }
   }
   else
      if( x < T->chave )
      {
         T->esq = avl_insere( x, T->esq );
         if( ( altura( T->esq ) - altura( T->dir ) ) == 2 )
         {
            if( x < T->esq->chave )
               T = rotacao_simples_esq( T );
            else
               T = rotacao_dupla_esq( T );
         }
         T->altura = max( altura(T->esq), altura(T->dir) ) + 1;
      }
      else /* Caso simétrico para a sub-árvore da direita */;
         if( x > T->chave )
         {
            T->dir = avl_insere( x, T->dir );
            if( ( altura( T->dir ) - altura( T->esq ) ) == 2 )
            {
               if( x > T->dir->chave )
                  T = rotacao_simples_dir( T );
               else
                  T = rotacao_dupla_dir( T );
            }
            T->altura = max( altura(T->esq), altura(T->dir) ) + 1;
         }
         /* Senão, x já está na árvore. Não fazer nada */
   return T;
}

// Remove uma chave x em uma subárvore T
AVL_PTR avl_retira (int x, AVL_PTR T)
{
   int fb_t, fb_esq, fb_dir;
   if (T == 0)
      return 0;
   else if (T->chave > x)
   {
      T->esq = avl_retira(x, T->esq);
      if ((FB(T) > 1) || (FB(T) < -1))
         if (mesmo_sinal(FB(T), FB(T->esq))) T = rotacao_simples_dir(T);
         else T = rotacao_dupla_dir(T);
   }
   else if (T->chave < x)
   {
      T->dir = avl_retira(x, T->dir);
      if ((FB(T) > 1) || (FB(T) < -1))
         if (mesmo_sinal(FB(T), FB(T->dir))) T = rotacao_simples_esq(T);
         else T = rotacao_dupla_esq(T);
   }
   else /* achou o elemento */
   {
      if (T->esq == 0 && T->dir == 0) /* elemento sem filhos */
      {
         free (T);
         T = 0;
      }
      else if (T->esq == 0) /* só tem filho à direita */
      {
         AVL_PTR n = T;
         T = T->dir;
         free (n);
      }
      else if (T->dir == 0) /* só tem filho à esquerda */
      {
         AVL_PTR n = T;
         T = T->esq;
         free (n);
      }
      else /* tem os dois filhos */
      {
         AVL_PTR f = T->esq;
         while (f->dir != 0)
            f = f->dir;
         T->chave = f->chave; /* troca as informações */
         f->chave = x;
         T->esq = avl_retira(x, T->esq);
         if ((FB(T) > 1) || (FB(T) < -1))
            if (mesmo_sinal(FB(T), FB(T->esq))) T = rotacao_simples_dir(T);
            else T = rotacao_dupla_dir(T);
      }
   }
   if (T != 0) T->altura = max( altura(T->esq), altura(T->dir) ) + 1;
   return T;
}

/* void avl_imprime(AVL_PTR T, int espacos)
{

   int i;

   for (i = 0; i < espacos; i++) printf(" ");
   if (T == 0)
   {
      //printf("X");
      return;
   }
   printf("%d", T->chave);
   printf("\n");
   avl_imprime(T->esq, espacos-4);
   avl_imprime(T->dir, espacos+4);
   printf("\n");
}

*/

void avl_imprime(AVL_PTR T, int espacos)
{

   if (T == NULL)
     return;
   avl_imprime(T->esq, 0);
   printf("%d  ", T->chave);
   avl_imprime(T->dir, espacos+4);

}

main()
{
/*
   int i, SIZE = 100;
   AVL_PTR T = 0;

   srand(time(0));
   for (i = 0; i < SIZE; i++)
      T = avl_insere((rand()%SIZE)+1, T);
   avl_imprime(T,0);
   printf("Altura: %d\n", altura(T));
   getchar();
 */
   clrscr();
   AVL_PTR T = 0;
   T = avl_insere(47, T);
   T = avl_insere(32, T);
   T = avl_insere(68, T);
   avl_imprime(T,20); getch();
   clrscr();
   T = avl_insere(5 , T);
   avl_imprime(T,20); getch();
   clrscr();
   T = avl_insere(40, T);
   avl_imprime(T,20); getch();
   clrscr();
   T = avl_insere(60, T);
   avl_imprime(T,20); getch();
   clrscr();
   T = avl_insere(88, T);
   avl_imprime(T,20); getch();
   clrscr();
   T = avl_insere(15, T);
   avl_imprime(T,20); getch();
   clrscr();
   T = avl_insere(54, T);
   avl_imprime(T,20); getch();
   clrscr();
   T = avl_insere(61, T);
   avl_imprime(T,20); getch();
   clrscr();
   T = avl_insere(90, T);
   avl_imprime(T,20); getch();
   clrscr();
   T = avl_insere(50, T);
   avl_imprime(T,20); getch();
   clrscr();

   printf("Removendo 47...\n");
   T = avl_retira(47, T);
   avl_imprime(T,0); getch();
}
