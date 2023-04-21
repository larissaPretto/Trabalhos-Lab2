struct lista {
    void* info;
    struct lista* prox;
};
typedef struct lista Lista;

struct aluno {
    int matricula;
    char* nome;
    char* curso;
    Lista* Avaliacao;
    int faltas;
};
typedef struct aluno Aluno;

struct professor {
    int siape;
    char* nome;
    char* areaAtuacao;
    char* titulacao;
};
typedef struct professor Professor;

struct disciplina {
    int codigo;
    char* nome;
    char* curso;
    int cargaHoraria;
    char** preReq;
    int qtd;
};
typedef struct disciplina Disciplina;

struct turma {
    int codigo;
    Lista* aluno;
    Lista* professor;
    Lista* aulasM;
    char* disciplina;
};
typedef struct turma Turma;

struct avaliacao {
    char* nome;
    int  nota;
};
typedef struct avaliacao Avaliacao;

struct curso {
    char* nome;
};
typedef struct curso Curso;

struct aulasM {
    int data;
    char** conteudoM;
    int qtd;
};
typedef struct aulasM AulasM;

Lista* criarLista(void);
Lista* inserirLista(Lista* l, void* v);
int listaVazia(Lista* l);
Lista* igual(Lista* l, char* m, int n, int tipo);
Lista* buscar(Lista* l, char* m, int n, int tipo);
Lista* alterarDados(Lista* l, char* m, int n, int tipo, Lista** discip, Lista** curso, int test);
Lista* retirarLista(Lista* l, char* m, int n, int tipo);
Lista* verificarTurma(Lista* l, int n, char* m, Lista** discip, Lista** curso);
Lista* listasDentroTurma(Lista* l, int tipo, char** disci, Lista* d);
void relatorio(Lista* l, Lista* b);
void imprimirDados(Lista* l, int tipo, int busca);
void imprimirProf(Lista* p, int listar);
void imprimirAluno(Lista* p, int listar);
void imprimirAulasM(Lista* p);
void liberaLista(Lista* l);

