#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HAB 5

// Função para inicializar o tabuleiro com zeros
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para imprimir o tabuleiro no console
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0)
                printf(". ");
            else if (tabuleiro[i][j] == 3)
                printf("N ");  // Navio
            else if (tabuleiro[i][j] == 5)
                printf("* ");  // Habilidade
        }
        printf("\n");
    }
}

// Posiciona navios no tabuleiro
void posicionarNavios(int tabuleiro[TAM][TAM]) {
    // Horizontal
    int linha1 = 1, coluna1 = 1;
    for (int i = 0; i < 3; i++) {
        tabuleiro[linha1][coluna1 + i] = 3;
    }

    // Vertical
    int linha2 = 4, coluna2 = 3;
    for (int i = 0; i < 3; i++) {
        tabuleiro[linha2 + i][coluna2] = 3;
    }

    // Diagonal principal
    int linha3 = 0, coluna3 = 7;
    for (int i = 0; i < 3; i++) {
        tabuleiro[linha3 + i][coluna3 + i] = 3;
    }

    // Diagonal secundária
    int linha4 = 6, coluna4 = 2;
    for (int i = 0; i < 3; i++) {
        tabuleiro[linha4 + i][coluna4 - i] = 3;
    }
}

// Constrói a matriz de habilidade Cone (apontando para baixo)
void construirCone(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            habilidade[i][j] = 0;
            if (j >= (TAM_HAB / 2) - i && j <= (TAM_HAB / 2) + i && i <= TAM_HAB / 2) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Constrói a matriz de habilidade Cruz
void construirCruz(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Constrói a matriz de habilidade Octaedro (losango)
void construirOctaedro(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            habilidade[i][j] = 0;
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Sobrepõe a matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linha = origemLinha - TAM_HAB / 2 + i;
            int coluna = origemColuna - TAM_HAB / 2 + j;

            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = 5; // Marca como área de habilidade
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Posiciona os 4 navios
    posicionarNavios(tabuleiro);

    // Cria as áreas de efeito
    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Define origens das habilidades
    int origemConeLinha = 2, origemConeColuna = 2;
    int origemCruzLinha = 5, origemCruzColuna = 5;
    int origemOctaedroLinha = 7, origemOctaedroColuna = 7;

    // Aplica habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicarHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicarHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Exibe o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}