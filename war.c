#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Definindo constantes de string e territorios ---
#define MAX_WAR 5
#define MAX_NOME 50

// --- criando a estrutura ---
struct Territorio{
    char nome[MAX_NOME];
    char cor[MAX_NOME];
    int tropas;
};

void atacar (struct Territorio *atacante,
             struct Territorio *defensor) {

                if(strcmp(atacante->cor, defensor->cor) == 0){

                    printf("\nVoce nao pode atacar um territorio aliado!\n");
                    return;
                }

                if(atacante->tropas <=1){

                    printf("\nTropas insuficientes para atacar!\n");
                    return;
                }

                int dadoAtacante = rand() % 6 + 1;
                int dadoDefensor = rand() % 6 + 1;

                printf("\n======= BATALHA =======\n");

                printf("\n%s atacou %s!\n", atacante->nome, defensor->nome);

                printf("\nDado atacante: %d\n", dadoAtacante);
                printf("\nDado defensor: %d\n", dadoDefensor);

                if(dadoAtacante > dadoDefensor){
                    printf("\nO atacante venceu!\n");
                    strcpy(defensor->cor, atacante->cor);
                    int tropasTransferidas = atacante->tropas / 2;
                    defensor->tropas = tropasTransferidas;
                    atacante->tropas -=tropasTransferidas;
                } else{
                    printf("\nO defensor venceu!\n");
                    atacante->tropas--;
                }
            }

// --- funcao principal (main) ---
int main() {

    srand(time(NULL));

    struct Territorio *territorios;
    territorios = calloc(MAX_WAR, sizeof(struct Territorio));

    // -- laco principal de cadastro ---
    for(int i = 0; i<MAX_WAR; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i+1);

        printf("Nome do Territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf("%s", territorios[i].cor);

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    printf("\nCadastro inicial concluido com sucesso!\n");

    printf("\n======================================\n");
    printf("\n==== MAPA DO MUNDO - ESTADO ATUAL ====\n");
    printf("\n======================================\n");

    // --- laco de exibicao dos resultados ---
    for(int i = 0; i < MAX_WAR; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i+1, territorios[i].nome,
                                    territorios[i].cor, territorios[i].tropas);
    }

    int atacanteIndex;
    int defensorIndex;

    while(1){

        printf("\n======= ATAQUE =======\n");

        printf("\nDigite 0 para sair.\n");

        printf("\nEscolha o territorio atacante (1 a %d): ", MAX_WAR);
        scanf("%d", &atacanteIndex);

        if(atacanteIndex == 0){
            printf("\nSaindo do jogo...\n");
            break;
        }

        printf("\nEscolha o territorio defensor (1 a %d): ", MAX_WAR);
        scanf("%d", &defensorIndex);

        atacanteIndex--;
        defensorIndex--;

        if(atacanteIndex < 0 || atacanteIndex >= MAX_WAR ||
        defensorIndex < 0 || defensorIndex >= MAX_WAR){

            printf("\nTerritorio invalido!\n");
        }else{
            atacar(&territorios[atacanteIndex],
                &territorios[defensorIndex]);
        }

        printf("\n======================================\n");
        printf("\n==== MAPA DO MUNDO - APOS ATAQUE ====\n");
        printf("\n======================================\n");

        // --- laco de exibicao dos resultados ---
        for(int i = 0; i < MAX_WAR; i++) {
            printf("%d. %s (Exercito %s, Tropas: %d)\n", i+1, territorios[i].nome,
                                        territorios[i].cor, territorios[i].tropas);
        }

    }

    free (territorios);

    return 0;
}