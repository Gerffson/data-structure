/* 
Programa de teste de funcao de hashing
   Compile o programa e execute, fazendo os testes de insercao/localizacao/remocao dos elementos.
   Altere o codigo fazendo novas insercoes e remocoes, verificando ANTES como ficara o vetor;
   Aletere a funcao main para criar um menu para chamar as funcoes respectivas.

*/
#include <stdio.h>
#include <conio.h>

#define TAM 10 // tamanho do hashing
void inicializa();
void exibe();
void insere (int);
void consulta (int);
void remove (int);
//variavel global
int h[TAM];

main ()
{ clrscr();
  inicializa();
  insere(3);
  exibe();
  getch();
  insere(13);
  exibe();
  getch();
  insere(0);
  exibe();
  getch();
  consulta(0);
  getch();
  consulta(20);
  getch();
  remove(13);
  exibe();
  getch();
  remove(2);
  exibe();
  getch();
}

void inicializa ( )
{  int i;
   for (i=0; i<TAM; i++)
     h[i] = -1;
}

void exibe ( )
{  int i;
   printf ("\n Como ficou o vetor: ");
   for (i=0; i<TAM; i++)
     printf("%2d   ", h[i]);
}


void insere (int n)
{ int a, aux;
  a = n % TAM;
  if (h[a] < 0)
    { h[a] = n;
      printf ("\n Elemento %d incluido!", n);
    }
  else
    { aux = (a+1) % TAM;
      while ((h[aux] >= 0) && (aux != a))
	aux = (aux+1) % TAM;
      if (aux != a)
	{ h[aux] = n;
	  printf ("\n Elemento %d incluido!", n);
	}
      else
	printf ("\n Elemento %d nao incluido - vetor cheio!, n");
     }
}



void consulta (int n)

{ int a, aux;
  a = n % TAM;
  if (h[a] == n)
     printf ("\n Elemento %d localizado!", n);
  else
    { aux = (a+1) % TAM;
      while ((h[aux] != -1) && (aux != a) && (h[aux] != n))
	aux = (aux+1) % TAM;
      if (h[aux] != n)
	printf ("\n Elemento %d nao localizado!", n);
      else
	printf ("\n Elemento %d localizado!", n);
     }
}


void remove (int n)
{ int a, aux;
  a = n % TAM;
  if (h[a] == n)
     { printf ("\n Elemento excluido!");
       h[a] = -2;
     }
  else
    { aux = (a+1) % TAM;
      while ((h[aux] != -1) && (aux != a) && (h[aux] != n))
	aux = (aux+1) % TAM;
      if (h[aux] != n)
	printf ("\n Elemento %d nao localizado para exclusao!", n);
      else
	{ printf ("\n Elemento %d excluido!", n);
	  h[aux] = -2;
	}
     }
}

