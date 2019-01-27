/* Programa exemplo de utilizacao de ABP
Funcoes de Insercao e Remocao
*/
//Inlcuindo bibliotecas
#include <stdio.h>
#include<stdlib.h>
#include<conio.h>
// Declaracao de estrutura
struct arv{
   int info;
   struct arv *esq;
   struct arv *dir;
   } *p, *raiz, *topo; //variaveis globais tipo ponteiro


//Prototipacao de funcoes
   void insere (int, struct arv*, struct arv*); // funcao de insercao
   struct arv * aloca (int); // funcao de alocacao retorna ponteiro
   void exclui (struct arv *, struct arv *, int); // funcao de exclusao
   void inordem (struct arv *); // funcao de travessia in-order
   void localiza (struct arv *, int ch);

// Funcao principal
void main (){

   int i, num;
   clrscr();
   randomize();
   num = rand (); // gera numero randomico
   raiz = aloca (num);  // preenche raiz chamando funcao de alocacao
   for (i=0; i < 5; i++){  // loop para geracao de 15 outros numeros randomicos
	num = rand ();      // gera numero randomico
	insere (num, NULL, raiz); // insere chamando funcao a partir da raiz
	}
   inordem (raiz);   // chama funcao inordem para verificar se arvore OK
   getch ();
   localiza(raiz, 0);  // localiza o elemento 0
   localiza (raiz,num); // localiza o ultimo elemento inserido
   getch();
   printf("\n");
   exclui (NULL,raiz,0);  //exclusao de um elemento
   printf("\n");
   exclui (NULL,raiz,num);  //exclusao de um elemento
   printf("\n");
   inordem (raiz);   // chama funcao inordem para verificar se arvore OK
   getch ();


}

   struct arv* aloca (int ch){   // funcao de alocao, recebe valor a colocar
       printf ("Elemento inserido: %d \n", ch); // exibe numero a inserir
       p = (struct arv*) malloc (sizeof(struct arv)); // aloca espaco
       if (p != NULL){
	  p->esq = NULL;  // preenche ponteiros esq e dir com NULL
	  p->dir = NULL;
	  p->info = ch;   // preenche informacao com chave informada
       }
	     return (p);  // retorna o endereco alocado
   }

   void inordem (struct arv *r){  // funcao de travessia in-ordem recursiva
       if (r != NULL){
	   inordem (r->esq);
	   printf ("%d  ", r->info);
	   inordem (r->dir);
       }
   }

 void insere (int ch, struct arv * pai, struct arv *a) // insercao de elemento
   { if (a->info == ch)      // se elemento existe, nao insere
	  printf ("Elemento existente\n");
      else
      { if (a==NULL)      // se chegou em espaco em branco...
	   { p = aloca(ch);  // aloca espaco
	     if(ch < pai->info) // testa e ajusta ponteriso do elemento pai
		pai->esq = p;
	     else
		pai->dir = p;
	    }
	  else
	  {  // se ainda nao chegou, continua...
	    if (ch < a->info)
	     insere(ch, a, a->esq); // chama recursividade passando ponteiro esquerdo
	    else
	     insere(ch, a, a->dir);  // chama recursividade passando ponteiro da direita
	  }
      }
   }

void localiza (struct arv * no, int ch)
{  if (no == NULL)
     printf("\n Elemento %d NAO localizado na ABP!", ch);
   else
      if (no->info == ch)
	printf("\n Elemento %d localizado na ABP!", ch);
      else
	if (ch < no->info)
	   localiza(no->esq, ch);
	else
	   localiza(no->dir, ch);
}


   void exclui (struct arv * pai, struct arv * r, int ch)  // funcao de exclusao
{  struct arv * aux, * auxpai;
   if (r == NULL)           // se chegou a NULL, elemento nao existe
    printf ("Elemento %d nao existente na arvore",ch);
  else
     { if (ch < r->info)   // se chave menor, recursao aa esquerda
	  exclui (r, r->esq, ch);
       else
	  if (ch > r->info)   // se chave maior, recursao a direita
	    exclui (r, r->dir, ch);
	  else  // se chegou aqui, achamos a chave
	    { if ((r->dir == NULL) && (r->esq == NULL)) // se dois filhos nulos
		    if (ch < pai->info)
			 pai->esq = NULL;
		    else
			pai->dir = NULL;
	      else
		 if ((r->esq == NULL) && (r->dir != NULL)) // se so direita nao nula
		  { if (ch < pai->info)
		      pai->esq = r->dir;
		    else
		      pai->dir = r->dir;
		   }
		 else
		   if ((r->esq != NULL) && (r->dir == NULL)) // se so esqueda nao nula
		    { if (ch < pai->info)
			pai->esq = r->esq;
		      else
			pai->dir = r->esq;

		     }
		    else  // se dois nao nulos, acha menor elemento da sub-arvore esquerda
		      { auxpai = r;
			aux = r->dir; // pegando elemento da direita
			while (aux -> esq != NULL)  // chando menor elemento
			    { auxpai = aux;
			      aux = aux -> esq;
			     }
			if (raiz == r)
			   { aux->esq = raiz->esq;
			     raiz = aux;
			     auxpai->esq = aux->dir;
			     aux->dir = auxpai;
			   }
			else
			   { aux -> esq = r-> esq;    // ajustando ponteiros
			     if (auxpai != r)
			      auxpai -> esq = aux -> dir;
			     else
			      auxpai -> dir = aux -> dir;
			     aux -> dir = r -> dir;
			     if (ch < pai->info)
			      pai->esq = aux;
			     else
			      pai->dir = aux;
			    }
			}
	 free (r); // liberado espaco
	 printf ("Elemento %d excluido",ch);
     }
}                  
}




