#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include "menu.h"

int main()
{
    Lista* L_disci  = criarLista();
    Lista* L_turmas = criarLista();
    Lista* L_cursos = criarLista();
    Lista* p;
    int resp;
    do {
        resp = menuPrincipal();
        if (resp == 1 || resp == 3 || resp == 4 || resp == 5 || resp == 7 || resp == 8) {
            L_turmas = menuEdicao(L_turmas, resp, &L_cursos, &L_disci);
        } else if (resp == 2) {
            L_disci = menuEdicao(L_disci, 2, &L_cursos, &L_disci);
        } else if (resp == 6) {
            L_cursos = menuEdicao(L_cursos, 6, &L_cursos, &L_disci);
        }
    } while(resp != 0);

    liberaLista(L_disci);
    liberaLista(L_cursos);
    for (p = L_turmas; p != NULL; p = p->prox) {
        for (p = ((Turma*)L_turmas->info)->aluno; p != NULL; p = p->prox) {
            liberaLista(((Aluno*)p->info)->Avaliacao);
        }
        liberaLista(((Turma*)L_turmas->info)->aluno);
        liberaLista(((Turma*)L_turmas->info)->aulasM);
        liberaLista(((Turma*)L_turmas->info)->professor);
    }
    liberaLista(L_turmas);
    return 0;
}
