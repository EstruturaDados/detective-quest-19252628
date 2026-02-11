#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

// Estruturas do Jogo
typedef struct PistaNode {
    char conteudo[50];
    struct PistaNode *esq, *dir;
} PistaNode;

typedef struct HashNode {
    char pista[50];
    char suspeito[50];
    struct HashNode *proximo;
} HashNode;

typedef struct Sala {
    char nome[50];
    char pista[50];
    struct Sala *esquerda, *direita;
} Sala;

// --- FUNCOES DE TABELA HASH ---
int gerarHash(char *str) {
    int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) hash += str[i];
    return hash % TAM_HASH;
}

// inserirNaHash() – insere associação pista/suspeito
void inserirNaHash(HashNode *tabela[], char *pista, char *suspeito) {
    int indice = gerarHash(pista);
    HashNode *novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = tabela[indice];
    tabela[indice] = novo;
}

// encontrarSuspeito() – consulta o suspeito de uma pista
char* encontrarSuspeito(HashNode *tabela[], char *pista) {
    int indice = gerarHash(pista);
    HashNode *atual = tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) return atual->suspeito;
        atual = atual->proximo;
    }
    return "Desconhecido";
}

// --- FUNCOES DE ARVORE BST (PISTAS) ---
PistaNode* inserirPista(PistaNode *raiz, char *texto) {
    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->conteudo, texto);
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (strcmp(texto, raiz->conteudo) < 0) raiz->esq = inserirPista(raiz->esq, texto);
    else raiz->dir = inserirPista(raiz->dir, texto);
    return raiz;
}

// --- FUNCOES DA MANSÃO ---
Sala* criarSala(char *nome, char *pista) {
    Sala *nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

// --- LOGICA DE JULGAMENTO ---
void verificarSuspeitoFinal(PistaNode *inventario, HashNode *tabela[]) {
    char acusacao[50];
    int provas = 0;

    printf("\n--- HORA DA ACUSACAO ---");
    printf("\nQuem e o culpado? (Suspeitos: Mordomo, Cozinheira, Jardineiro): ");
    scanf(" %[^\n]s", acusacao);

    // Funcao auxiliar para contar provas na BST
    void contarProvas(PistaNode *n) {
        if (n == NULL) return;
        contarProvas(n->esq);
        if (strcmp(encontrarSuspeito(tabela, n->conteudo), acusacao) == 0) provas++;
        contarProvas(n->dir);
    }
    
    contarProvas(inventario);

    if (provas >= 2) {
        printf("\nPARABENS! Com %d pistas, voce provou que %s e o culpado!\n", provas, acusacao);
    } else {
        printf("\nFRACASSO... Voce nao tem provas suficientes contra %s.\n", acusacao);
    }
}

int main() {
    HashNode *dossie[TAM_HASH] = {NULL};
    PistaNode *inventario = NULL;
    
    // Configura Suspeitos na Hash
    inserirNaHash(dossie, "Veneno", "Cozinheira");
    inserirNaHash(dossie, "Faca", "Cozinheira");
    inserirNaHash(dossie, "Luvas", "Mordomo");
    inserirNaHash(dossie, "Chave", "Mordomo");

    // Monta Mansao
    Sala *hall = criarSala("Hall", "");
    Sala *cozinha = criarSala("Cozinha", "Veneno");
    Sala *despensa = criarSala("Despensa", "Faca");
    hall->esquerda = cozinha;
    cozinha->direita = despensa;

    // ExplorarSalas() - Navegação
    Sala *atual = hall;
    char escolha;
    while (atual) {
        printf("\nSala: %s", atual->nome);
        if (strlen(atual->pista) > 0) {
            printf("\n[!] Pista: %s", atual->pista);
            inventario = inserirPista(inventario, atual->pista);
            strcpy(atual->pista, "");
        }
        printf("\n[e]Esq [d]Dir [s]Sair: ");
        scanf(" %c", &escolha);
        if (escolha == 's') break;
        atual = (escolha == 'e') ? atual->esquerda : atual->direita;
    }

    verificarSuspeitoFinal(inventario, dossie);
    return 0;
}





