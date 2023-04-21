#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"
#include "menu.h"
#include "lerDados.h"

int tipoDeEdicao(void)
{
    int edicao;
    do {
        printf("\n Digite:\n\n > 1 para cadastrar\n > 2 para remover\n > 3 para alterar os dados\n > 4 para imprimir");
        printf("\n > 5 para buscar\n > 0 para sair\n\n-> ");
        scanf("%d", &edicao);
    } while (edicao < 0 || edicao > 5);
    return edicao;
}

void tipoDeDados(int tipo, char** m, int* n)
{
    if (tipo == 1 || tipo == 2 || tipo == 3 || tipo == 5 || tipo == 6)
        varTxt("o nome", &*m);
    else {
        printf("\n Digite o codigo/data: ");
        scanf("%d", &*n);
    }
}

Lista* menuEdicao(Lista* l, int tipo, Lista** curso, Lista** disci)
{
    int n, edicao = 0;
    char* m = (char*) malloc(40 * sizeof(char));
    char* test;
    Lista* p = l;
    Lista* a = *curso;
    Lista* b = *disci;
    Lista* c;
    if (tipo != 8) {
        edicao = tipoDeEdicao();
    }
    if (edicao == 1) { //Cadastro
        if (tipo == 1) { //Cadastro Aluno
            p = verificarTurma(l, n, m, &b, &a);
            if (p == NULL) {
                return l;
            } else {
                int cont = 0;
                for (c = ((Turma*)p->info)->aluno; c != NULL; c = p->prox) {
                    cont++;
                }
                if (cont < 50) {
                    ((Turma*)p->info)->aluno = inserirLista(((Turma*)p->info)->aluno, dadosAluno(&a));
                    l = p;
                } else {
                    printf("\n > Turma cheia\n");
                    return l;
                }
            }
        } else if (tipo == 2) { //Cadastro Disciplina
            l = inserirLista(l, dadosDisciplina("a", &a));
        } else if (tipo == 3) { //Cadastro Prof
            p = verificarTurma(l, n, m, &b, &a);
            if (p == NULL)
                return l;
            else {
                ((Turma*)p->info)->professor = inserirLista(((Turma*)p->info)->professor, dadosProfessor());
                l = p;
            }
        } else if (tipo == 4) { //Cadastro Turma
            l = inserirLista(l, dadosTurma(&b, &a, -1));
        } else if (tipo == 5) { //Cadastro Avaliação
            if (p == NULL) {
                printf("\n > Cadastre um aluno primeiro\n");
                return l;
            }
            p = verificarTurma(l, n, m, &b, &a);
            if (l == NULL)
                return l;
            else {
                char* nome = (char*) malloc(40 * sizeof(char));
                varTxt("o nome da avaliacao", &nome);
                for (c = ((Turma*)p->info)->aluno ; c != NULL; c = c->prox) {
                    ((Aluno*)c->info)->Avaliacao = inserirLista(((Aluno*)c->info)->Avaliacao, dadosAvaliacao(((Aluno*)c->info)->nome, nome));
                }
                l = p;
            }
        } else if (tipo == 6) { //Cadastro Curso
            l = inserirLista(l, dadosCurso("a"));
        } else if (tipo == 7) { //Cadastro Aulas
            if (listaVazia(p)) {
                printf("\n > Cadastre uma turma primeiro\n");
                return l;
            }
            p = verificarTurma(l, n, m, &b, &a);
            if (listaVazia(p)) {
                return l;
            } else {
                int qtd;
                ((Turma*)l->info)->aulasM = inserirLista(((Turma*)p->info)->aulasM, dadosAulaM());
                varInt("quantos alunos faltaram a aula", &qtd);
                for (int i = 0; i < qtd; i++) {
                    c = ((Turma*)l->info)->aluno;
                    varTxt("o nome do aluno", &m);
                    c = buscar(c, m, 0, 1);
                    if (c != NULL)
                        ((Aluno*)c->info)->faltas += 1;
                    else
                        printf("\n > Aluno nao encontrado\n");
                }
            }
            l = p;
        }
        printf("\n > Cadastrado/a com sucesso!\n\n");

    } else if (edicao == 2) { // Remover
        tipoDeDados(tipo, &m, &n);
        if (tipo == 1 || tipo == 3 || tipo == 7 || tipo == 5) {
            c = listasDentroTurma(p, tipo, &test, b);
            if (c != NULL)
               c =  retirarLista(c, m, n, tipo);
        } else
            c = retirarLista(p, m, n, tipo);
        l = p;
    } else if (edicao == 3) { // Alterar Dados
        if (tipo == 1 || tipo == 3 || tipo == 7 ) {
            tipoDeDados(tipo, &m, &n);
            c = listasDentroTurma(l, tipo, &test, b);
            if (c != NULL) {
                alterarDados(c, m, n, tipo, &b, &a, 1);
            }
        } else if (tipo == 5){
            c = listasDentroTurma(p, 1, &test, b);
            if (c != NULL) {
                char* nome = (char*) malloc(40 * sizeof(char));
                varTxt("nome do aluno", &nome);
                alterarDados(c, nome, n, 1, &b, &a, 0);
            }
        } else {
            tipoDeDados(tipo, &m, &n);
            alterarDados(l, m, n, tipo, &b, &a, 0);
        }

    } else if (edicao == 4) { // Imprimir
        if (tipo == 1 || tipo == 3 || tipo == 7 || tipo == 5) {
            c = listasDentroTurma(l, tipo, &test, b);
            if (c != NULL)
                imprimirDados(c, tipo, 1);
        } else
            imprimirDados(l, tipo, 1);

    } else if (edicao == 5) { // Buscar
        tipoDeDados(tipo, &m, &n);
        if (tipo == 1 || tipo == 3 || tipo == 7 || tipo == 5) {
            c = listasDentroTurma(p, tipo, &test, b);
            if (c != NULL) {
                c = buscar(c, m, n, tipo);
                imprimirDados(c, tipo, 0);
            }
        } else {
            c = buscar(l, m, n, tipo);
            imprimirDados(c, tipo, 0);
        }
    }
    *curso = a;
    *disci = b;
    if (tipo == 8) {
        relatorio(l, b);
    }
    return l;
}

int menuPrincipal(void)
{
    int resp;
    printf("\n Escolha a categoria, digite:\n\n > 1 para alunos\n > 2 para disciplina\n > 3 para professores\n > 4 para turmas\n ");
    printf("> 5 para avaliacoes\n > 6 para cursos\n > 7 para aulas ministradas\n > 8 para relatorio de aprovados e reprovados\n > 0 para sair\n\n-> ");
    scanf("%d", &resp);
    return resp;
}
