# include <stdio.h>
# include <conio.h>
# include <stdlib.h>

//definição da estrutura do hashing e definição do vetor
struct hash 
{
       int num;
       struct colisao * lista;
}h[10];
//definição da estrutura do tratamentode cosisão 
struct colisao
{
       int num;
       struct colisao * prox;
};

//Prototipo de funções
void insere (int n);
void consulta (int n);
void consultalista (int n, struct colisao *lista);
void remocao(int n);
void removelista (int n, struct colisao *lista);
void inicializa();
int menu(int opcao);

int main ()
{
     inicializa();
     int n,i,opcao = 0;
     struct colisao * aux;
     while (opcao != 4)
     {
     system("cls");
     printf("Digite 1 para inserir:\n");
     printf("Digite 2 para consultar:\n");
     printf("Digite 3 para remover:\n");
     printf("Digite 4 para sair:\n\n");
     printf("Digite a opcao desejada: ");
     scanf("%d", &opcao);
     switch (opcao)
     {
            case 1:
            {
                 for (i=0; i<10 ; i++)
                 {
                     printf("\nDigite o valor para a posicao %2d: ",i+1);
                     scanf("%d",&n);
                     fflush(stdin);
                     insere(n);
                 }
                 printf("O vetor ficou:\n");
                 for (i=0; i<10; i++)
                 {
                     printf("\n Posicao %2d: %2d --->>>  ",i,h[i].num);
                     aux = h[i].lista;
                     while (aux != NULL)
                     {
                           printf("%2d -> ", aux->num);
                           aux = aux-> prox;
                     }              
                 }
                 getch();
                 break;
            }
            case 2:
            {
                 printf("\nDigite o numero a ser consultado: ");
                 scanf("%d", &n);
                 fflush(stdin);
                 consulta(n);
                 getch();
                 break;
            }
            case 3:
            {
                 printf("\nDigite o numero a ser removido: ");
                 scanf("%d", &n);
                 fflush(stdin);
                 remocao(n);
                 printf("O vetor ficou:\n");
                 for (i=0; i<10; i++)
                 {
                     printf("\n Posicao %2d: %2d --->>>  ",i,h[i].num);
                     aux = h[i].lista;
                     while (aux != NULL)
                     {
                           printf("%2d -> ", aux->num);
                           aux = aux-> prox;
                     }              
                 }
                 getch();
                 break;
            }
            case 4:
            {
                 printf("Programa finalizado!");
                 getch();
                 break;
            }
            default: 
            {
                     printf("Opcao invalida!");
            }
     }
     }
     getch();    
     return 1;
}

void inicializa()
{
     int i;
     for (i=0; i<10; i++)
     {
         h[i].num = -1;
         h[i].lista = NULL;
     }
}

void insere (int n)
{
     struct colisao *p, *aux;
     int a;
     a= n % 10;
     if (h[a].num < 0)
        h[a].num = n;
     else
     {
         p = (struct colisao*)malloc(sizeof (struct colisao));
         if (p == NULL)
            printf("Erro de alocacao de memoria!");
         else
         {
             p->prox = NULL;
             p->num = n;
             if (h[a].lista == NULL)
                h[a].lista = p;
             else
             {
                 aux = h[a].lista;
                 while (aux->prox != NULL)
                       aux = aux->prox;
                 aux->prox = p;
             }
         }
     }
}

void consulta (int n)
{
     int a;
     a = n % 10;
     if (h[a].num == n)
        printf("Elemento encontrado!");
     else
         consultalista(n,h[a].lista);
}

void consultalista (int n, struct colisao *lista)
{
     struct colisao * aux;
     if (lista == NULL)
        printf("Elemento nao encontrado!");
     else
     {
         aux = lista;
         while (aux != NULL)
         {
               if (aux->num == n)
               {
                            printf("Elemento encontrado!");
                            return;
               }
               aux = aux->prox;
         }
         printf("Elemento nao encontrado!");
         return;
     }
}

void remocao(int n)
{
     int a;
     a = n % 10;
     if (h[a].num == n)
        h[a].num = -2;
     else
         removelista(n,h[a].lista);
}

void removelista (int n, struct colisao *lista)
{
     struct colisao * aux, *aux2;
     int a;
     a = n % 10;
     if (lista == NULL)
        printf("Elemento nao existe!");
     else
     {
         aux = lista;
         aux2 = NULL;
         while (aux != NULL)
         {
               if (aux->num == n)
               {    if (aux2 != NULL)
                       aux2 = aux->prox;
                    else
                       h[a].lista = aux->prox;        
                    free(aux);                          
                    return;
               }
               aux2 = aux;
               aux = aux->prox;
         }
         printf("Elemento nao existe!");
         return;
     }
}

