#include <stdio.h>
#include <string.h>

// --- Definindo constantes de string e territorios ---
#define MAX_WAR 5
#define MAX_STRING 50

// --- criando a estrutura ---
struct Territorio{
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int tropas;
};

// --- funcao principal (main) ---
int main() {

    struct Territorio territorios[MAX_WAR];

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
        printf("\nTERRITORIO %d:\n", i+1);
        printf("- Nome: %s\n", territorios[i].nome);
        printf("- Dominado por: Exercito %s\n", territorios[i].cor);
        printf("- Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}