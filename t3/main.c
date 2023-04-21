#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listas.h"

int main(void)
{
    int resp;
    Lista* carros = criarLista();
    Arv* aP = criarArvore();
    Arv* aM = criarArvore();
    Arv* aA = criarArvore();
    do {
    printf("\n Digite:\n\n > 1 para inserir\n > 2 para excluir\n > 3 para buscar\n > 4 para listar carros ordenadamente pela placa\n");
    printf(" > 5 para listar carros ordenadamente pela marca\n > 6 para listar carros ordenadamente pelo ano\n > 0 para sair\n\n-> ");
    scanf("%d", &resp);
    if (resp == 1) {
        carros = inserirLista(carros, dadosCarro(), &aP, &aM, &aA);
    } else if (resp == 2 || resp == 3) {
        char* nome = (char*) malloc(40 * sizeof(char));
        printf("\n Qual a placa do carro? ");
        scanf("%s", nome);
        if (resp == 2)
            carros = retirar(carros, nome);
        else {
            if (pertence(aP, nome) == true)
                printf(" \n > Carro com a placa %s encontrado!\n", nome);
            else
                printf(" \n > Carro nao encontrado!\n");
        }
    } else if (resp == 4) {
        printf("\n- Lista de carros ordenada pela placa -\n");
        imprimir(carros);
    } else if (resp == 5) {
        printf("\n- Lista de carros ordenada pela marca -\n");
        imprimirArv(aM);
    } else if (resp == 6) {
        printf("\n- Lista de carros ordenada pelo ano -\n");
        imprimirArv(aA);
    }

    } while(resp != 0);

    liberaLista(carros);
    liberarArv(aP);
    liberarArv(aM);
    liberarArv(aA);
    return 0;
}
