#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"
#include "lerDados.h"

void varTxt(const char* texto, char** txt)
{
    printf("\n Qual %s: ", texto);
    scanf("%s", *txt);
}

void varInt(const char* texto, int* num)
{
    printf("\n Qual %s: ", texto);
    scanf("%d", &*num);
}

Avaliacao* dadosAvaliacao(char* m, char* nome)
{
    Avaliacao* info = (Avaliacao*) malloc(sizeof(Avaliacao));
    info->nome = (char*) malloc(40 * sizeof(char));
    info->nome = nome;
    printf("\n Qual a nota de %s? ", m);
    scanf("%d", &info->nota);
    return info;
}

Aluno* dadosAluno(Lista** curso)
{
    Lista* a = *curso;
    char* nomeC;
    Aluno* info = (Aluno*) malloc(sizeof(Aluno));
    varInt("a matricula do aluno", &info->matricula);
    info->nome = (char*) malloc(40 * sizeof(char));
    varTxt("o nome do aluno", &info->nome);
    info->Avaliacao = criarLista();
    info->faltas = 0;
    info->curso = (char*) malloc(40 * sizeof(char));
    nomeC = (char*) malloc(40 * sizeof(char));
    varTxt("o curso do aluno", &nomeC);
    a = buscar(a, nomeC, 0, 6);
    if (a == NULL) {
        printf("\n > Curso nao encontrado. Ele sera cadastrado!\n");
        a = inserirLista(*curso, dadosCurso(nomeC));
        *curso = a;
    }
    info->curso = nomeC;
    return info;
}

Disciplina* dadosDisciplina(char* nomeD, Lista** curso)
{
    char* nomeC;
    Lista* a = *curso;
    Disciplina* info = (Disciplina*) malloc(sizeof(Disciplina));
    varInt("o codigo da disciplina", &info->codigo);
    varInt("a carga horaria da disciplina", &info->cargaHoraria);
    varInt("a quantidade de pre-requisitos", &info->qtd);
    info->preReq = (char**) malloc(info->qtd * sizeof(char*));
    for(int i = 0; i < info->qtd; i++) {
        info->preReq[i] = (char*) malloc(40 * sizeof(char));
        varTxt("os pre-requisitos", &info->preReq[i]);
    }
    info->nome = (char*) malloc(40 * sizeof(char));
    if (strcmp(nomeD, "a") == 0) {
        varTxt("o nome da disciplina", &info->nome);
    } else {
        info->nome = nomeD;
    }
    info->curso = (char*) malloc(sizeof(char));
    nomeC = (char*) malloc(40 * sizeof(char));
    varTxt("curso esta diciplina pertence", &nomeC);
    a = buscar(a, nomeC, 0, 6);
    if (a == NULL) {
        printf("\n > Curso nao encontrado. Ele sera cadastrado!\n");
        a = inserirLista(*curso, dadosCurso(nomeC));
        *curso = a;
    }
    info->curso = nomeC;
    return info;
}

Professor* dadosProfessor(void)
{
    Professor* info = (Professor*) malloc(sizeof(Professor));
    varInt("o siope do professor", &info->siape);
    info->areaAtuacao = (char*) malloc(40 * sizeof(char));
    varTxt("a area de atuacao do professor", &info->areaAtuacao);
    info->titulacao = (char*) malloc(40 * sizeof(char));
    varTxt("a titulacao do professor", &info->titulacao);
    info->nome = (char*) malloc(40 * sizeof(char));
    varTxt("o nome do professor", &info->nome);
    return info;
}

Turma* dadosTurma(Lista** discip, Lista** curso, int cod)
{
    char* nome;
    Lista* a = *discip;
    Lista* b = *curso;
    Turma* info = (Turma*) malloc(sizeof(Turma));
    if (cod == -1)
        varInt("o codigo da turma", &info->codigo);
    else
        info->codigo = cod;
    info->aluno = criarLista();
    info->professor = criarLista();
    info->aulasM = criarLista();
    info->disciplina = (char*) malloc(40 * sizeof(char));
    nome = (char*) malloc(40 * sizeof(char));
    varTxt("a disciplina", &nome);
    a = buscar(a, nome, 0, 2);
    if (a == NULL) {
        printf("\n > Disciplina nao encontrada. Ela sera criada! Preencha as informacoes sobre ela e continue o cadastro inicial\n ");
        a = inserirLista(*discip, dadosDisciplina(nome, &b));
    }
    *discip = a;
    *curso = b;
    info->disciplina = nome;
    return info;
}
Curso* dadosCurso(char* nome)
{
    Curso* info = (Curso*) malloc(sizeof(Curso));
    info->nome = (char*) malloc(40 * sizeof(char));
    if (strcmp(nome, "a") == 0) {
        varTxt("o nome do curso", &info->nome);
    } else {
        info->nome = nome;
    }
    return info;
}

AulasM* dadosAulaM(void)
{
    AulasM* info = (AulasM*) malloc(sizeof(AulasM));
    varInt("a data da aula", &info->data);
    varInt("a quantidade de conteudos", &info->qtd);
    info->conteudoM = (char**) malloc(info->qtd * sizeof(char*));
    for(int i = 0; i < info->qtd; i++) {
        info->conteudoM[i] = (char*) malloc(40 * sizeof(char));
        varTxt("os conteudos", &info->conteudoM[i]);
    }
    return info;
}
