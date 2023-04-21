#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"
#include "lerDados.h"

Lista* criarLista(void)
{
    return NULL;
}

Lista* inserirLista(Lista* l, void* v)
{
    Lista* n = (Lista*) malloc(sizeof(Lista));
    n->info = v;
    n->prox = l;
    return n;
}

int listaVazia(Lista* l)
{
     return (l == NULL);
}

Lista* igual(Lista* l, char* m, int n, int tipo)
{
    Lista* p = l;
    if (tipo == 1 && strcmp(((Aluno*)p->info)->nome,m) == 0)
        return p;
    else if (tipo == 3 && strcmp(((Professor*)p->info)->nome,m) == 0)
        return p;
    else if (tipo == 2 && strcmp(((Disciplina*)p->info)->nome,m) == 0)
        return p;
    else if (tipo == 5 && strcmp(((Avaliacao*)p->info)->nome,m) == 0)
        return p;
    else if (tipo == 6 && strcmp(((Curso*)p->info)->nome,m) == 0)
        return p;
    else if (tipo == 4 && ((Turma*)p->info)->codigo == n)
        return p;
    else if (tipo == 7 && ((AulasM*)p->info)->data == n )
        return p;
    return NULL;
}

Lista* buscar(Lista* l, char* m, int n, int tipo)
{
    Lista* p;
    Lista* a;
    if (listaVazia(l)) {
        printf("\n > Lista Vazia");
        return NULL;
    }
    for (p = l; p != NULL; p = p->prox) {
        a = igual(p, m, n, tipo);
        if (a != NULL)
            return a;
    }
    printf("\n > Nao encontrado\n");
    return NULL;
}

Lista* alterarDados(Lista* l, char* m, int n, int tipo, Lista** discip, Lista** curso, int test)
{
    Lista* p = l;
    Lista* a = *discip;
    Lista* b = *curso;
    Lista* c;
    while (!listaVazia(p) && buscar(p, m, n, tipo) == NULL) {
        p = p->prox;
    }
    if (p == NULL) {
        printf("\n > Nao encontrado\n");
        return l;
    }
    printf("\n Dados atuais ---\n");
    imprimirDados(p, tipo, 0);
    printf("\n Editar dados: \n");
    if (tipo == 1 && test == 1) {
        p->info = dadosAluno(&b);
    } else if (tipo == 2) {
        p->info = dadosDisciplina("a", &a);
    } else if (tipo == 3) {
        p->info = dadosProfessor();
    } else if (tipo == 4) {
        p->info = dadosTurma(&b, &a, -1);
    } else if (tipo == 1) {
        char* nome = (char*) malloc(40 * sizeof(char));
        varTxt("o nome da avaliacao que sera editada", &nome);
        for (c = ((Aluno*)p->info)->Avaliacao ; c != NULL; c = c->prox) {
            if (buscar(c, nome, 0, 5) != NULL) {
                c->info = dadosAvaliacao(((Aluno*)p->info)->nome, nome);
                break;
            }
        }
    } else if (tipo == 6) {
        p->info = dadosCurso("a");
    } else if (tipo == 7) {
        p->info = dadosAulaM();
    }
    *discip = a;
    *curso = b;
    return p;
}

Lista* retirarLista(Lista* l, char* m, int n, int tipo)
{
    Lista* ant = NULL;
    Lista* p = l;
    while (p != NULL && igual(p, m, n, tipo) == NULL) {
        ant = p;
        p = p->prox;
    }
    if (p == NULL) {
        printf("\n > Nao encontrado\n");
        return l;
    }
    if (ant == NULL) {
        l = p->prox;
    } else {
        ant->prox = p->prox;
    }
    free(p);
    printf("\n > Removido/a com sucesso!\n\n");
    l = p;
    return l;
}

Lista* verificarTurma(Lista* l, int n, char* m, Lista** discip, Lista** curso)
{
    Lista* p = l;
    Lista* a = *discip;
    Lista* b = *curso;
    printf("\n Qual o codigo da turma? ");
    scanf("%d", &n);
    p = buscar(l, m, n, 4);
    if (p == NULL) {
        printf("\n > Turma nao encontrada. Deseja cria-la?(s/n): ");
        scanf("%s", m);
        if (strcmp(m, "s") == 0) {
            l = inserirLista(l, dadosTurma(&a, &b, n));
            p = l;
        } else {
            return NULL;
        }
    }
    *discip = a;
    *curso = b;
    return p;
}

Lista* listasDentroTurma(Lista* l, int tipo, char** disci, Lista* d)
{
    int cod;
    Lista* b;
    Lista* a;
    varInt("o codigo da turma", &cod);
    b = buscar(l, "a", cod, 4);
    if (b != NULL) {
        if (tipo == 1)
            b = ((Turma*)b->info)->aluno;
        else if (tipo == 3)
            b = ((Turma*)b->info)->professor;
        else if (tipo == 5) {
            a = ((Turma*)b->info)->aluno;
            b = ((Aluno*)a->info)->Avaliacao;
        } else if (tipo == 7)
            b = ((Turma*)b->info)->aulasM;
        else if (tipo == 8){
            *disci = ((Turma*)b->info)->disciplina;
            b = ((Turma*)b->info)->aluno;
        }
    }
    return b;
}

void relatorio(Lista* l, Lista* disc)
{
    float nota = 0, freq, cargH;
    int cont = 0;
    char* nomeD = (char*) malloc(40 * sizeof(char));
    Lista* a = listasDentroTurma(l, 8, &nomeD, disc);
    Lista* c;
    Lista* p;
    Lista* b;
    if (a != NULL) {
        b = buscar(disc, nomeD, 0, 2);
        if (b != NULL) {
            cargH = ((Disciplina*)b->info)->cargaHoraria;
            printf("\n------------------------------------------------------------------------\n");
            printf("\n Aluno         Media final      Frequencia             Situacao\n");
            for (c = a; c != NULL; c = c->prox) {
                printf("\n %-17s", ((Aluno*)c->info)->nome);
                for (p = ((Aluno*)c->info)->Avaliacao; p != NULL; p = p->prox) {
                    nota += ((Avaliacao*)p->info)->nota;
                    cont++;
                }
                freq = ((cargH-((Aluno*)c->info)->faltas)/cargH)*100;
                if (nota == 0)
                    printf("%-16.2f", 0.0);
                else
                    printf("%-16.2f", nota/cont);
                printf("%-13.2f ", freq);
                if (nota/cont >= 7 && freq >= 75.0) {
                    printf("       Aprovado\n");
                } else if (nota/cont <= 7 && (freq >= 75.0 || freq <= 75.0)) {
                    printf("       Reprovado\n");
                } else if (freq <= 75.0){
                    printf("Reprovado por frequencia\n");
                }
                cont = 0;
                nota = 0;
            }
        }
    }
    printf("\n------------------------------------------------------------------------\n");
}

void imprimirAluno(Lista* p, int listar)
{
    Lista* t;
    printf("\n Nome: %s\n", ((Aluno*)p->info)->nome);
    if (listar == 1) {
        printf(" Matricula: %d\n", ((Aluno*)p->info)->matricula);
        printf(" Curso: %s\n", ((Aluno*)p->info)->curso);
        printf(" Faltas: %d \n", ((Aluno*)p->info)->faltas);
        printf("\n Notas nas avaliacoes: \n");
        for (t = ((Aluno*)p->info)->Avaliacao; t != NULL; t = t->prox) {
            printf("\n %s: %d\n", ((Avaliacao*)t->info)->nome, ((Avaliacao*)t->info)->nota);
        }
    }
}

void imprimirProf(Lista* p, int listar)
{
    printf("\n Nome: %s\n", ((Professor*)p->info)->nome);
    if (listar == 1) {
        printf(" Siape: %d\n", ((Professor*)p->info)->siape);
        printf(" Area de atuacao: %s\n", ((Professor*)p->info)->areaAtuacao);
        printf(" Titulacao: %s\n", ((Professor*)p->info)->titulacao);
    }
}

void imprimirAulasM(Lista* p)
{
    printf("\n Data: %d\n", ((AulasM*)p->info)->data);
    for (int i = 0; i < ((AulasM*)p->info)->qtd; i++) {
        printf(" Conteudo: %s\n", ((AulasM*)p->info)->conteudoM[i]);
    }
}
void imprimirDados(Lista* l, int tipo, int busca)
{
    Lista* p;
    Lista* t;
    if (listaVazia(l)){
        printf("\n > Lista Vazia");
    }
    for (p = l; p != NULL; p = p->prox) {
        if (tipo == 1) {
            printf("\n Aluno\n -----------------------------");
            imprimirAluno(p, 1);
        } else if (tipo == 2) {
            printf("\n Disciplina\n -----------------------------");
            printf("\n Nome: %s\n", ((Disciplina*)p->info)->nome);
            printf(" Codigo: %d\n", ((Disciplina*)p->info)->codigo);
            printf(" Carga Horaria: %d\n", ((Disciplina*)p->info)->cargaHoraria);
            printf(" Curso: %s\n", ((Disciplina*)p->info)->curso);
            for (int i = 0; i < ((Disciplina*)p->info)->qtd; i++) {
                printf(" Pre-requisito: %s\n", ((Disciplina*)p->info)->preReq[i]);
            }
        } else if (tipo == 3) {
            printf("\n Professor \n -----------------------------");
            imprimirProf(p, 1);
        } else if (tipo == 4) {
            printf("\n -----------------------------\n");
            printf("\n Codigo da turma: %d\n", ((Turma*)p->info)->codigo);
            printf("\n Disciplina: %s\n", ((Turma*)p->info)->disciplina);
            printf("\n Alunos --- \n");
            for (t = ((Turma*)p->info)->aluno ; t != NULL; t = t->prox) {
                imprimirAluno(t, 0);
            }
            printf("\n Professores --- \n");
            for (t = ((Turma*)p->info)->professor ; t != NULL; t = t->prox) {
                imprimirProf(t, 0);
            }
            printf("\n Aulas Ministradas --- \n");
            for (t = ((Turma*)p->info)->aulasM ; t != NULL; t = t->prox) {
                imprimirAulasM(t);
            }
        } else if (tipo == 5) {
            printf("\n Nome: %s\n", ((Avaliacao*)p->info)->nome);
        } else if (tipo == 6) {
            printf("\n Nome: %s\n", ((Curso*)p->info)->nome);
        } else if (tipo == 7) {
            printf("\n Aula Ministrada\n -----------------------------");
            imprimirAulasM(p);
        }
        if (busca == 0)
            break;
    }
    printf("\n");
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
