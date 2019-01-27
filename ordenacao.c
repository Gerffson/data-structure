
/****************************************
 * Prática de medida de tempo de execução de algoritmos
 * Atividades:
 *  - Executar o programa e verificar os testes para 100 elementos - comparar os tempos
 *  - Alterar o valor de SIZE para 1000,2000,5000 e 10000 elementos e verificar o tempo
 *  - Retirar o comentario do printf da funcao qs() e verificar como funciona a recursao com SIZE = 20
 *
 * OBS.: OCORRERÁ NO FINAL DA AULA AVALIAÇÃO DO DESEMPENHO DAS ATIVIDADES
 */

#include <time.h>
#include <alloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

void bolha(int);
void qs (int, int);

int *v1, *v2;

main()
{  clrscr();
   // Número de elementos do vetor
   int SIZE = 500;
   int i;
   clock_t time1,time2;

   // Cria e Inicializa o vetor com números aleatórios
   v1 = (int*)malloc(SIZE * sizeof(int));
   v2 = (int*)malloc(SIZE * sizeof(int));
   srand(time(0));
   for (i = 0; i < SIZE; i++) 
    { v1[i] = (rand()%SIZE)+1;
      v2[i] = v1[i];
    }
  // Ordenacao do metodo da bolha
   time1=clock();
   bolha(SIZE);
   time2=clock();
   printf ("\n\n Vetor ordenado pele metodo Bolha (10 elementos): \n");
   for (i=0; i<10; i++)
     printf("%d ", v1[i]);
   printf(" \n BOLHA - Tempo decorrido: %lf ms\n", ((double)(time2-time1))/CLOCKS_PER_SEC*1000);
  // Ordenacaoo do metodo quicksort
   time1=clock();
   qs(0,SIZE-1);     
   time2=clock();
   printf ("\n\n\n Vetor ordenado pele metodo Quicksort (10 elementos): \n");
   for (i=0; i<10; i++)
    printf("%d ", v2[i]);
   printf(" \n QUICKSORT - Tempo decorrido: %lf ms\n", ((double)(time2-time1))/CLOCKS_PER_SEC*1000);

   getchar();
}


void bolha (int n)  // n é o tamanho do vetor
{  int i, j, temp;
   for (i=n-1; i>=1; i--)
      for (j=0; j<i; j++)
        if (v1[j] > v1[j+1])
          { temp = v1[j];
            v1[j] = v1[j+1];
            v1[j+1] = temp;
          }

}




void qs (int left, int right)  
{  register int i, j;
   int x, y;
   i = left;
   j = right;
   x = v2[(left + right) / 2];
   // printf ("\n Estou na recursao com indices %d e %d. O valor central eh %d.", left, right, x);
   do  {  while (v2[i] < x && i < right)   i++;
          while (x < v2[j]  && j > left)   j--;
            if (i <= j)
               { y = v2[i];
                  v2[i] = v2[j];
                  v2[j] = y;
                  i++;   j--;
               }
        } while (i <= j);
   if (left < j)   qs(left, j);
   if (i < right)   qs(i, right);
}


