#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os Nos da Arvore de Pistas (BST)
typedef struct PistaNode {
    char conteudo[50];
    struct PistaNode *esq, *dir;
} PistaNode;

// Estrutura para os Comodos da Mansao (Arvore Binaria)
typedef struct Sala {
    char nome[50];
    char pista[50]; // Conteudo da pista no comodo
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Funcao para criar um novo no na arvore de pistas (BST)
PistaNode* inserirPista(PistaNode* raiz, char* texto) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->conteudo, texto);
        novo->esq = novo->dir = NULL;
        return novo;
    }
    // Organiza por ordem alfabetica
    if (strcmp(texto, raiz->conteudo) < 0)
        raiz->esq = inserirPista(raiz->esq, texto);
    else
        raiz->dir = inserirPista(raiz->dir, texto);
    return raiz;
}

// Funcao para criar sala com ou sem pista
Sala* criarSala(char* nome, char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

// Exibe as pistas em ordem alfabetica (Percurso Em-ordem)
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esq);
        printf("- %s\n", raiz->conteudo);
        exibirPistas(raiz->dir);
    }
}

// Controla a navegacao e coleta automatica
void explorarSalasComPistas(Sala* raiz) {
    Sala* atual = raiz;
    PistaNode* inventario = NULL;
    char escolha;

    printf("\n--- INVESTIGACAO DA ENIGMA STUDIOS ---\n");

    while (atual != NULL) {
        printf("\nVoce esta na: %s", atual->nome);

        // Coleta automatica se houver pista
        if (strlen(atual->pista) > 0) {
            printf("\n[!] Pista encontrada: %s", atual->pista);
            inventario = inserirPista(inventario, atual->pista);
            strcpy(atual->pista, ""); // Limpa para nao coletar repetido
        }

        printf("\nEscolha: [e] Esquerda, [d] Direita, [s] Sair: ");
        scanf(" %c", &escolha);

        if (escolha == 's') break;
        if (escolha == 'e' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita) atual = atual->direita;
        else printf("\nCaminho sem saida ou opcao invalida!");
    }

    printf("\n--- RELATORIO FINAL DE PISTAS (ORDEM ALFABETICA) ---\n");
    if (inventario == NULL) printf("Nenhuma pista coletada.\n");
    else exibirPistas(inventario);
}

int main() {
    // Montagem do mapa fixo
    Sala* hall = criarSala("Hall de Entrada", "");
    Sala* biblioteca = criarSala("Biblioteca", "Diario Antigo");
    Sala* jardim = criarSala("Jardim", "Pegada na Lama");
    Sala* cozinha = criarSala("Cozinha", "Chave de Prata");
    Sala* adega = criarSala("Adega", "Bilhete Rasgado");

    hall->esquerda = biblioteca;
    hall->direita = cozinha;
    biblioteca->esquerda = jardim;
    cozinha->direita = adega;

    explorarSalasComPistas(hall);

    return 0;
}




