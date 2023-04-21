#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "listas.h"

Lista* criarLista(void)
{
    return NULL;
}

Arv* criarArvore(void)
{
    return NULL;
}

int listaVazia(Lista* l)
{
    return (l == NULL);
}

int arvVazia(Arv* a)
{
    return (a == NULL);
}

Arv* inserirArv(void* v, Arv* a, char* c, int tipo, int ano)
{
    if (arvVazia(a)) {
        a = (Arv*) malloc (sizeof(Arv));
        a->info = v;
        a->esq = NULL;
        a->dir = NULL;
    } else if(tipo == 1) {
        if (strcmp(((Carro*)a->info)->placa, c) > 0)
            a->esq = inserirArv(v, a->esq, c, 1, ano);
        else if (strcmp(((Carro*)a->info)->placa, c) <= 0)
            a->dir = inserirArv(v, a->dir, c, 1, ano);
    } else if(tipo == 2) {
        if (strcmp(((Carro*)a->info)->marca, c) > 0)
            a->esq = inserirArv(v, a->esq, c, 2, ano);
        else if (strcmp(((Carro*)a->info)->marca, c) <= 0)
            a->dir = inserirArv(v, a->dir, c, 2, ano);
    } else if(tipo == 3) {
        if (((Carro*)a->info)->ano > ano)
            a->esq = inserirArv(v, a->esq, c, 3, ano);
        else if (((Carro*)a->info)->ano <= ano)
            a->dir = inserirArv(v, a->dir, c, 3, ano);
    }
    return a;
}

Lista* inserirLista(Lista* l, void* v, Arv** aP, Arv** aM, Arv** aA)
{
    Lista* n = (Lista*) malloc(sizeof(Lista));
    n->info = v;
    Lista* ant = NULL;
    Lista* p = l;
    while (!listaVazia(p) && strcmp(((Carro*)p->info)->placa,((Carro*)n->info)->placa) < 0){
        ant = p;
        p = p->prox;
    }

    if (ant == NULL) {
        n->prox = l;
        l = n;
    } else {
        n->prox = ant->prox;
        ant->prox = n;
    }
    *aP = inserirArv(v, *aP, ((Carro*)n->info)->placa, 1, ((Carro*)n->info)->ano);
    *aM = inserirArv(v, *aM, ((Carro*)n->info)->marca, 2, ((Carro*)n->info)->ano);
    *aA = inserirArv(v, *aA, ((Carro*)n->info)->placa, 3, ((Carro*)n->info)->ano);
    return l;
}

Carro* dadosCarro(void)
{
    Carro* info = (Carro*) malloc(sizeof(Carro));
    info->placa = (char*) malloc(40 * sizeof(char));
    printf("\n Qual a placa do carro? ");
    scanf("%s", info->placa);
    info->marca = (char*) malloc(40 * sizeof(char));
    printf("\n Qual a marca do carro? ");
    scanf("%s", info->marca);
    printf("\n Qual o ano do carro? ");
    scanf("%d", &info->ano);
    return info;
}

Lista* igual(Lista* l, char* nome)
{
    Lista* p = l;
    if (strcmp(((Carro*)p->info)->placa,nome) == 0)
        return p;
    return NULL;
}

Lista* retirar(Lista* l, char* nome)
{
   Lista* ant = NULL;
   Lista* p = l;
   while(!listaVazia(p) && igual(p, nome) == NULL){
      ant = p;
      p = p->prox;
   }
   if (listaVazia(p)) {
        printf("\n > Carro nao encontrado\n");
        return l;
   }
   if (ant == NULL)
      l = p->prox;
   else
      ant->prox = p->prox;
   free(p);
   return l;
}

void imprimir(Lista* l)
{
    Lista* p;
    if (listaVazia(l)){
        printf("\n > Lista Vazia\n");
    }

    for (p = l; p != NULL; p = p->prox) {
        printf("\n Placa: %s", ((Carro*)p->info)->placa);
        printf("\n Marca: %s", ((Carro*)p->info)->marca);
        printf("\n Ano: %d \n", ((Carro*)p->info)->ano);
    }
}

void imprimirArv(Arv* a)
{
    if (!arvVazia(a)) {
        imprimirArv(a->esq);
        printf("\n Placa: %s", ((Carro*)a->info)->placa);
        printf("\n Marca: %s", ((Carro*)a->info)->marca);
        printf("\n Ano: %d\n", ((Carro*)a->info)->ano);
        imprimirArv(a->dir);
    }
}

bool pertence(Arv* a, char* c)
{
    if (arvVazia(a))
        return false;
    else
        return strcmp(((Carro*)a->info)->placa, c) == 0 || pertence(a->esq, c) || pertence(a->dir, c);
}

void liberaLista(Lista* l)
{
    Lista* p = l;
    while (p != NULL){
        Lista* t = p->prox;
        free(p);
        p = t;
    }
}

void liberarArv(Arv* a)
{
    if (!arvVazia(a)){
        liberarArv(a->esq);
        liberarArv(a->dir);
        free(a);
    }
}
