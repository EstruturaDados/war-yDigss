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

void atacar (struct Territorio *atacante, struct Territorio *defensor) {

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

void cadastrarTerritorios(struct Territorio *territorios){
    for(int i = 0; i < MAX_WAR; i++){
        printf("\n--- Cadastrando Territorio %d ---\n", i+1);

        printf("Nome do Territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Cor do Exercito: ");
        scanf("%s", territorios[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
    printf("\nCadastro inicial concluido com sucesso!\n");
}

void exibirMapa(struct Territorio *territorios){
    printf("\n======================================\n");
    printf("\n==== MAPA DO MUNDO - ESTADO ATUAL ====\n");
    printf("\n======================================\n");

    // --- laco de exibicao dos resultados ---
    for(int i = 0; i < MAX_WAR; i++) {

        printf("%d. %s (Exercito %s, Tropas: %d)\n",
            i+1,
            territorios[i].nome,
            territorios[i].cor,
            territorios[i].tropas);
    }
}

void atribuirMissao(char *destino, char *missoes[], int totalMissoes){
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

int verificarMissao(char *missao, struct Territorio *territorios){
    // --- missao de conquistar 3 territorios ---
    if (strcmp(missao, "Conquistar 3 territorios") == 0){
        int contador = 0;
        for(int i = 0; i < MAX_WAR; i++){
            if(strcmp(territorios[i].cor, "azul") == 0){
                contador ++;
            }
        }
        if(contador >= 3){
            return 1;
        }
    }

    // --- Dominar todos os territorios ---
    if(strcmp(missao, "Dominar todos os territorios") == 0){
        int contador = 0;
        for(int i = 0; i < MAX_WAR; i++){
            if(strcmp(territorios[i].cor, "azul") == 0){
                contador ++;
            }
        }

        if(contador == MAX_WAR){
            return 1;
        }
    }
    return 0;
}

void liberarMemoria(struct Territorio *territorios, char *missaoJogador){
    free(territorios);
    free(missaoJogador);
}

// --- funcao principal (main) ---
int main() {

    srand(time(NULL));

    char *missoes[] = {
        "Conquistar 3 territorios",
        "Dominar todos os territorios",
        "Eliminar tropas inimigas",
        "Expandir seu exercito",
        "Conquiste o territorio com maior numero de tropas"
    };

    int totalMissoes = 5;

    struct Territorio *territorios;
    territorios = calloc(MAX_WAR, sizeof(struct Territorio));

    char *missaoJogador;
    missaoJogador = malloc(100 * sizeof(char));

    // --- cadastro de territorios ---
    cadastrarTerritorios(territorios);

    atribuirMissao(missaoJogador, missoes, totalMissoes);

    printf("\n======= SUA MISSAO =======\n");
    printf("%s\n", missaoJogador);

    // --- exibição de mapa ---
    exibirMapa(territorios);

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

        if(verificarMissao(missaoJogador,
                    territorios)){

            printf("\n===========================\n");
            printf("MISSAO CUMPRIDA!\n");
            printf("VOCE VENCEU O JOGO!\n");
            printf("===========================\n");

            break;
        }

        exibirMapa(territorios);

    }

    liberarMemoria(territorios, missaoJogador);

    return 0;
}