#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

int** criar_matriz(int m, int n)
{
    int** mat = (int**) malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        mat[i] = (int*) malloc(n * sizeof(int));
    }
    return mat;
}

void liberar_matriz(int** tab, int m)
{
    for (int i = 0; i < m; i++) {
        free(tab[i]);
    }
    free(tab);
}

typedef struct
{
    int l[3], c[3], tamanho;
} frota;

void apresentacao(void)
{
    printf(" Bem vindo ao jogo Batalha naval!\n\n");
    printf(" Voce pode jogar sozinho, em que o objetivo eh afundar os navios.\n");
    printf(" Ou contra o computador, em que o objetivo eh afundar os navios inimigos antes que ele afunde os seus.\n");
    printf(" Serao colocados aleatoriamente pelo tabuleiro navios Corvetas(C), Submarinos(S) e Destroyer(D).\n");
    printf(" Eles ocupam, respectivamente, 1, 2 e 3 posicoes.\n");
    printf(" A cada jogada correta voce podera jogar novamente.\n\n");
}

int modo_de_jogo(void)
{
    int resposta;
    do {
        printf("\n Digite 1 para jogar sozinho ou 2 para jogar contra o computador: ");
        scanf("%d", &resposta);
    } while (resposta < 1 || resposta > 2 );
    return resposta;
}

int sorteio(int max)
{
    return rand() % max;
}

void desenhar_tabuleiro(int** tab, frota navio[], int qL, int qC, int nTotal)
{
    printf("\n      ");
    for (int i = 0; i < qC; i++) {
        printf("%-3d ", i+1);
    }
    printf("\n    -");
    for (int i = 0; i < qC; i++) {
        printf("----");
    }
    printf("\n  1 ");
    for (int i = 0; i < qL; i++) {
        for (int j = 0; j < qC; j++) {
            printf("|");
            if (tab[i][j] == 0 || tab[i][j] == 2) {
                printf("   ");
            } else if (tab[i][j] == -1) {
                printf(" * ");
            } else if (tab[i][j] == 1) {
                for (int k = 0; k < nTotal; k++) {
                    for (int m = 0; m < 3; m++) {
                        if (i == navio[k].l[m] && j == navio[k].c[m]) {
                            if (navio[k].tamanho == 1) {
                                printf(" C ");
                            } else if (navio[k].tamanho == 2) {
                                printf(" S ");
                            } else if (navio[k].tamanho == 3) {
                                printf(" D ");
                            }
                        }
                    }
                }
            }
        }
        if (i+2 <= qL) {
            printf("|\n %2d ", i+2 );
        } else {
             printf("|\n");
        }
    }
    printf("    -");
    for (int i = 0; i < qC; i++) {
        printf("----");
    }
}

bool verificar_posicao(int** tab, int l, int c, int direcao, int tamanho, int qL, int qC)
{
    if (direcao == 3 && (tab[l][c] == 0 || tab[l][c] == 2)) {
        return true;
    }
    for (int i = 0; i < tamanho; i++) {
        if (direcao == 1) {
            if (c+i >= qC || tab[l][c+i] != 0) {
                return false;
            }
        } else {
            if (l+i >= qL || tab[l+i][c] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool colocar_navios(int** tab, frota navio[], int n1, int n2, int n3, int qL, int qC)
{
    int l, c, direcao, tamanho, espaco = qL*qC;
    for (int i = 0; i < n1+n2+n3; i++) {
        if (i < n1 ) {
            tamanho = 1;
        } else if (i >= n1 && i < n1+n2) {
            tamanho = 2;
        } else if (i >= n1+n2 && i < n1+n2+n3) {
            tamanho = 3;
        }
        espaco -= tamanho;
        do {
            l = sorteio(qL);
            c = sorteio(qC);
            direcao = sorteio(2);
            if (espaco < tamanho) {
                printf("\n Navios demais para o tamanho do tabuleiro. Tente novamente\n");
                return true;
            }
        } while (!verificar_posicao(tab, l, c, direcao, tamanho, qL, qC));
        navio[i].tamanho = tamanho;
        for (int j = 0; j < tamanho; j++) {
            if (direcao == 1) {
                tab[l][c+j] = 2;
                navio[i].l[j] = l;
                navio[i].c[j] = c+j;
            } else {
                tab[l+j][c] = 2;
                navio[i].l[j] = l+j;
                navio[i].c[j] = c;
            }
        }
        for (int j = tamanho; j < 3; j++) {
            navio[i].l[j] = -1;
        }
    }
    return false;
}

bool fim_de_jogo(int** tab, int qL, int qC)
{
    for (int i = 0; i < qL; i++) {
        for (int j = 0; j < qC; j++) {
            if (tab[i][j] == 2) {
                return true;
            }
        }
    }
    return false;
}

void preencher_tabuleiro(int** tab, int qL, int qC)
{
    for (int i = 0; i < qL; i++) {
        for (int j = 0; j < qC; j++) {
            tab[i][j] = 0;
        }
    }
}

void le_jogada(int *lin, int *col, int qL, int qC)
{
    int x, y;
    do {
        printf("\n  Digite a linha e coluna onde quer jogar: ");
        scanf("%d%d", &x, &y);
    } while (x <= 0 || x > qL || y <= 0 || y > qC);
    *lin = x-1;
    *col = y-1;
}

bool jogada(int l, int c, int** tab, int modo)
{
    if (tab[l][c] == 2) {
        tab[l][c] = 1;
        if (modo == 1) {
            printf("\n  Correto!");
        }
        return true;
    } else if (tab[l][c] == 0) {
        tab[l][c] = -1;
    }
    return false;
}

void espacamento_titulo(int qC, char nome[])
{
    printf("\n");
    for (int i = 5; i < qC; i++) {
        printf("  ");
    }
    printf("  Tabuleiro do %s   \n", nome);
}

void mensagem_final(int modo, time_t fim, int** tab, int** tabPC, frota navio[], frota navioPC[], int vitoria, int qL, int qC, int nTotal)
{
    printf("\n-------------------------------------------------\n");
    espacamento_titulo(qC, "Computador");
    desenhar_tabuleiro(tab, navio, qL, qC, nTotal);

    if (modo == 2) {
        printf("\n");
        espacamento_titulo(qC, "Jogador");
        desenhar_tabuleiro(tabPC, navioPC, qL, qC, nTotal);
    }
    if (vitoria == 1) {
        printf("\n\n Parabens!! voce ganhou!\n");
    } else {
        printf("\n\n Voce perdeu!\n");
    }
    printf(" Tempo de jogo: %d segundos\n\n", (int)fim);
}

void modo_solo(int** tab, int qL, int qC, int n1, int n2, int n3)
{
    int l, c;
    time_t inicio = time(NULL);
    frota navio[n1+n2+n3];
    colocar_navios(tab, navio, n1, n2, n3, qL, qC);
    while (fim_de_jogo(tab, qL, qC)) {
        printf("\n");
        espacamento_titulo(qC, "Computador");
        desenhar_tabuleiro(tab, navio, qL, qC, n1+n2+n3);

        do {
            le_jogada(&l, &c, qL, qC);
        } while (tab[l][c] != 0 & tab[l][c] != 2);
        jogada(l, c, tab, 1);
    }
    time_t fim = time(NULL) - inicio;
    mensagem_final(1, fim, tab, tab, navio, navio, 1, qL, qC, n1+n2+n3);
}

bool verificar_continuacao_navio(int** tab, int *l, int *c, int qL, int qC)
{
    for (int i = 0; i < qL; i++) {
        for (int j = 0; j < qC; j++) {
            if (tab[i][j] == 1) {
                if (j+1 < qC && (tab[i][j+1] == 0 || tab[i][j+1] == 2)) {
                    *l = i;
                    *c = j+1;
                    return false;
                }
                if (j-1 >= 0 && (tab[i][j-1] == 0 || tab[i][j-1] == 2)) {
                    *l = i;
                    *c = j-1;
                    return false;
                }
                if (i+1 < qL && (tab[i+1][j] == 0 || tab[i+1][j] == 2)) {
                    *l = i+1;
                    *c = j;
                    return false;
                }
                if (i-1 >= 0 && (tab[i-1][j] == 0 || tab[i-1][j] == 2)) {
                    *l = i-1;
                    *c = j;
                    return false;
                }
            }
        }
    }
    return true;
}

void modo_contra_pc(int** tab, int** tabPC, int qL, int qC, int n1, int n2, int n3)
{
    int l, c, vitoria = 1, l_PC, c_PC;
    bool jog;
    time_t inicio = time(NULL);
    frota navio[n1+n2+n3];
    frota navioPC[n1+n2+n3];
    colocar_navios(tab, navio, n1, n2, n3, qL, qC);
    colocar_navios(tabPC, navioPC, n1, n2, n3, qL, qC);
    while (fim_de_jogo(tab, qL, qC)) {
        do {
            if (verificar_continuacao_navio(tabPC, &l_PC, &c_PC, qL, qC)){
                do {
                    l_PC = sorteio(qL);
                    c_PC = sorteio(qC);
                } while (!verificar_posicao(tabPC, l_PC, c_PC, 3, 1, qL, qC));
            }
            espacamento_titulo(qC, "Jogador");
            jog = jogada(l_PC, c_PC, tabPC, 2);
            desenhar_tabuleiro(tabPC, navioPC, qL, qC, n1+n2+n3);

            if (jog) {
                printf("\n\n  Correto!\n");
            }
            if (!fim_de_jogo(tabPC, qL, qC)) {
                break;
            }
        } while (jog);

        if (!fim_de_jogo(tabPC, qL, qC)) {
            vitoria = 2;
            break;
        }
        do {
            if (!fim_de_jogo(tab, qL, qC)) {
                break;
            }
            printf("\n");
            espacamento_titulo(qC, "Computador");
            desenhar_tabuleiro(tab, navio, qL, qC, n1+n2+n3);

            do {
                le_jogada(&l, &c, qL, qC);
            } while (tab[l][c] != 0 & tab[l][c] != 2);
        } while (jogada(l,c, tab, 1));
    }
    time_t fim = time(NULL) - inicio;
    mensagem_final(2, fim, tab, tabPC, navio, navioPC, vitoria, qL, qC, n1+n2+n3);
}

int main()
{
    int qL, qC, n1, n2, n3;
    bool teste;
    apresentacao();
    srand(time(0));
    printf(" Digite a quantidade de linhas e colunas do tabuleiro: ");
    scanf("%d%d", &qL, &qC);

    int** tab = criar_matriz(qL, qC);
    int** tabPC = criar_matriz(qL, qC);

    if (tab == NULL || tabPC == NULL) {
        printf(" Erro de alocacao");
        exit(1);
    }
    do {
        preencher_tabuleiro(tab, qL, qC);
        printf("\n Digite, respectivamente, quantos navios Corvetas(C), Submarinos(S) e Destroyer(D): ");
        scanf("%d%d%d", &n1, &n2, &n3);
        frota navioTeste[n1+n2+n3];
        teste = colocar_navios(tab, navioTeste, n1, n2, n3, qL, qC);
    } while (teste);

    preencher_tabuleiro(tab, qL, qC);
    preencher_tabuleiro(tabPC, qL, qC);

    if (modo_de_jogo() == 1) {
        modo_solo(tab, qL, qC, n1, n2, n3);
    } else {
        modo_contra_pc(tab, tabPC, qL, qC, n1, n2, n3);
    }

    liberar_matriz(tab, qL);
    liberar_matriz(tabPC, qL);
    return 0;
}
