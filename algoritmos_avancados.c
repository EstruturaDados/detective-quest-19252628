#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da Sala (Nó da Árvore)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função para criar uma nova sala (Alocação Dinâmica)
Sala* criarSala(char *nome) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Função para explorar a mansão
void explorarMansao(Sala *raiz) {
    Sala *atual = raiz;
    char escolha;

    printf("\n--- Inicio da Investigacao ---\n");

    while (atual != NULL) {
        printf("\nVoce esta na: %s", atual->nome);

        // Verifica se eh um no-folha (fim do caminho)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\nVoce chegou a um comodo sem saidas. Investigacao finalizada!\n");
            break;
        }

        printf("\nCaminhos disponiveis:");
        if (atual->esquerda != NULL) printf("\n[e] Esquerda: %s", atual->esquerda->nome);
        if (atual->direita != NULL) printf("\n[d] Direita: %s", atual->direita->nome);
        printf("\n[s] Sair do jogo");
        
        printf("\nEscolha sua direcao: ");
        scanf(" %c", &escolha);

        if (escolha == 's') {
            printf("Saindo da mansao...\n");
            break;
        } else if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else {
            printf("\nOpcao invalida ou caminho inexistente!");
        }
    }
}

int main() {
    // Montando a mansao (Arvore Binaria) manualmente conforme requisito
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *porao = criarSala("Porao");

    // Conectando as salas
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->esquerda = porao; // Cozinha so tem caminho para o porao

    // Inicia a exploracao
    explorarMansao(hall);

    // No nivel mestre aprenderemos a liberar a memoria aqui!
    return 0;
}

