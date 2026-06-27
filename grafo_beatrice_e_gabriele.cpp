/* LABIRINTO COM GRAFOS - BUSCA EM LARGURA (BFS)
   
   ALUNAS: Beatrice Fischer e Gabriele Maria Freiberger*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 

#define LINHAS 21
#define COLUNAS 49
#define PAREDE  '#'
#define LIVRE   '.'
#define ENTRADA 'E'
#define SAIDA   'S'
#define CAMINHO '*'
#define MAX_FILA (LINHAS * COLUNAS)

typedef struct {
    int linha;
    int coluna;
} Posicao;

void exibirLabirinto(void);
Posicao localizarEntrada(void);
Posicao localizarSaida(void);
int posicaoValida(int linha, int coluna);
int bfs(Posicao entrada, Posicao saida);
int marcarCaminho(Posicao entrada, Posicao saida);

char labirinto[LINHAS][COLUNAS + 1] = { 
    "#################################################",
    "E.....#...........#.................#...........#",
    "#.###.#.#.#######.#.#####.#########.#.#####.###.#",
    "#...#...#.......#.#.....#.....#.....#.....#...#.#",
    "###.#.#.#######.#.#####.#####.#.#########.###.#.#",
    "#...#.#.......#.....#...#.....#.......#.....#...#",
    "#.###.#######.#######.###.###########.#.#####.###",
    "#.....#.....#.......#...#.....#.......#.....#...#",
    "#####.#.###.#######.###.###.#.#.#####.#####.###.#",
    "#.....#...#.......#.....#...#.#.....#.......#...#",
    "#.#######.#######.#######.###.#####.#.#######.#.#",
    "#.......#.....#.........#...#.....#.#.......#.#.#",
    "#######.#####.#.#######.###.#####.#.#######.#.#.#",
    "#.....#.....#.#.....#...#.......#.#.....#...#.#.#",
    "#.###.#####.#.###.#.#.#########.#.#####.#.###.#.#",
    "#...#.......#.....#.#.........#.#.......#.....#.#",
    "###.###############.#########.#.###############.#",
    "#.................#.........#.#.................#",
    "#.#########################.#.#################.#",
    "#...........................#...................S",
    "#################################################"
};

Posicao fila[MAX_FILA];
int fila_inicio; 
int fila_fim; 

int visitado[LINHAS][COLUNAS]; 
Posicao pai[LINHAS][COLUNAS]; 

int direcao_linha[4] = {-1, 1,  0, 0};
int direcao_col[4]   = { 0, 0, -1, 1};

int main(void){
    Posicao entrada, saida;
    int encontrou, passos;

    printf("            LABIRINTO COM GRAFOS (BFS) \n\n");

    entrada = localizarEntrada();
    saida   = localizarSaida();

    if (entrada.linha == -1) {
        printf("Erro: entrada 'E' nao encontrada no labirinto.\n");
        return 1;
    }
    if (saida.linha == -1) {
        printf("Erro: saida 'S' nao encontrada no labirinto.\n");
        return 1;
    }

    printf("Legenda: '#'=parede, '*'=caminho, '.'=livre, 'E'=entrada, 'S'=saida\n");
    printf("Entrada encontrada em: linha %i, coluna %d\n", entrada.linha, entrada.coluna);
    printf("Saida encontrada em: linha %i, coluna %d\n\n", saida.linha, saida.coluna);

    printf("               LABIRINTO ORIGINAL \n");
    exibirLabirinto();
    printf("\n");

    printf("\n Pressione ENTER para exibir o labirinto resolvido.");
	fflush(stdin);
	getchar();
	system("cls");

    encontrou = bfs(entrada, saida); 
    if (!encontrou) {
        printf("Nao existe caminho entre a entrada e a saida.\n");
        return 0;
    }
    passos = marcarCaminho(entrada, saida); 

    printf("\n               LABIRINTO RESOLVIDO \n");
    exibirLabirinto();
    printf("\n");
    printf("Caminho encontrado! Quantidade de passos: %i\n", passos);

    return 0;
}

void exibirLabirinto(void){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (labirinto[i][j] == CAMINHO) {
                SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY); 
                printf("%c", labirinto[i][j]);
                SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
            } else if ((labirinto[i][j] == ENTRADA) || (labirinto[i][j] == SAIDA)){
                SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY); 
                printf("%c", labirinto[i][j]);
                SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
            } else {
                printf("%c", labirinto[i][j]);
            }
        }
        printf("\n");
    }
}

Posicao localizarEntrada(void){
    Posicao entrada;
    entrada.linha  = -1;
    entrada.coluna = -1;

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (labirinto[i][j] == ENTRADA) {
                entrada.linha  = i;
                entrada.coluna = j;
                return entrada;
            }
        }
    }
    return entrada;
}

Posicao localizarSaida(void)
{
    Posicao saida;
    saida.linha  = -1;
    saida.coluna = -1;

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (labirinto[i][j] == SAIDA) {
                saida.linha  = i;
                saida.coluna = j;
                return saida;
            }
        }
    }
    return saida;
}

int posicaoValida(int linha, int coluna)
{
    if (linha < 0 || linha >= LINHAS) return 0; 
    if (coluna < 0 || coluna >= COLUNAS) return 0; 
    if (labirinto[linha][coluna] == PAREDE) return 0; 
    if (visitado[linha][coluna]) return 0; 
    return 1;
}

int bfs(Posicao entrada, Posicao saida)
{
    Posicao atual, vizinho;

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            visitado[i][j]    = 0;
            pai[i][j].linha   = -1;
            pai[i][j].coluna  = -1;
        }
    }

    fila_inicio = 0;
    fila_fim    = 0;

    fila[fila_fim] = entrada;
    fila_fim++;
    visitado[entrada.linha][entrada.coluna] = 1;

    while (fila_inicio < fila_fim) {

        atual = fila[fila_inicio]; 
        fila_inicio++;

        if (atual.linha == saida.linha && atual.coluna == saida.coluna) {
            return 1; 
        }

        for (int d = 0; d < 4; d++) {
            vizinho.linha  = atual.linha  + direcao_linha[d];
            vizinho.coluna = atual.coluna + direcao_col[d];

            if (posicaoValida(vizinho.linha, vizinho.coluna)) {
                visitado[vizinho.linha][vizinho.coluna] = 1;
                pai[vizinho.linha][vizinho.coluna] = atual; 

                fila[fila_fim] = vizinho;
                fila_fim++;
            }
        }
    }
    return 0; 
}

int marcarCaminho(Posicao entrada, Posicao saida){
    
    Posicao atual;
    int passos = 0;
    atual = saida; 

    while (!(atual.linha == entrada.linha && atual.coluna == entrada.coluna)) {
        if (labirinto[atual.linha][atual.coluna] != ENTRADA && labirinto[atual.linha][atual.coluna] != SAIDA) {
            labirinto[atual.linha][atual.coluna] = CAMINHO; 
        }
        passos++;
        atual = pai[atual.linha][atual.coluna]; 
        
    }
    passos++; 
    return passos;
}