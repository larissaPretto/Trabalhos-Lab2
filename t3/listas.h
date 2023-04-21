struct lista {
    void* info;
    struct lista* prox;
};
typedef struct lista Lista;

struct carro {
    char* placa;
    char* marca;
    int ano;
};
typedef struct carro Carro;

struct arv {
    void* info;
    struct arv* esq;
    struct arv* dir;
};
typedef struct arv Arv;

Lista* criarLista(void);
Arv* criarArvore(void);
int listaVazia(Lista* l);
int arvVazia(Arv* a);
Lista* inserirLista(Lista* l, void* v, Arv** aP, Arv** aM, Arv** aA);
Arv* inserirArv(void* v, Arv* a, char* c, int tipo, int ano);
Lista* igual(Lista* l, char* nome);
Lista* retirar(Lista* l, char* nome);
Carro* dadosCarro(void);
void imprimir(Lista* l);
void imprimirArv(Arv* a);
bool pertence(Arv* a, char* c);
void liberaLista(Lista* l);
void liberarArv(Arv* a);
