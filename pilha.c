#include "pilha.h"

// Função auxiliar para validar texto
int texto_valido(const char* txt) {
    if (txt == NULL) return 0;

    // ignorar espaços
    while (*txt == ' ' || *txt == '\t') txt++;

    return (*txt != '\0');
}

Pilha* criar_pilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if (pi == NULL) {
        printf("Erro: Memoria cheia (pilha nao foi criada)\n");
        return NULL;
    }
    pi->topo = NULL;
    return pi;
}

void push(Pilha* pi, const char* texto){
    if (pi == NULL) {
        printf("Erro: Pilha inexistente\n");
        return;
    }

    if (!texto_valido(texto)) {
        printf("Erro: Texto vazio nao pode ser adicionado\n");
        return;
    }

    No* novo_no = (No*) malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro: Memoria cheia (nao foi possivel adicionar item)\n");
        return;
    }

    novo_no->texto = strdup(texto);
    if (novo_no->texto == NULL) {
        printf("Erro: Memoria cheia (texto nao duplicado)\n");
        free(novo_no);
        return;
    }

    novo_no->prox = pi->topo;
    pi->topo = novo_no;
}

char* pop(Pilha* pi){
    if (pi == NULL || estaVazia(pi)) {
        printf("Aviso: Nenhum item para remover.\n");
        return NULL;
    }

    No* no_remover = pi->topo;
    char* texto = no_remover->texto;

    pi->topo = no_remover->prox;

    free(no_remover);
    return texto;
}

void display(Pilha* pi){
    if (pi == NULL || estaVazia(pi)){
        printf("Pilha Vazia\n");
        return;
    }

    No* atual = pi->topo;
    printf("--- TOPO ---\n");
    while (atual != NULL){
        printf("  %s\n", atual->texto);
        atual = atual->prox;
    }
    printf("--- BASE ---\n");
}

void limparPilha(Pilha* pi){
    if (pi == NULL) return;

    while (!estaVazia(pi)) {
        char* texto = pop(pi);
        if (texto != NULL) free(texto);
    }
}

int estaVazia(Pilha* pi){
    if (pi == NULL) return 1;
    return (pi->topo == NULL);
}

void limpar_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int contarItens(Pilha* pi){
    if (pi == NULL || estaVazia(pi)) return 0;

    int c = 0;
    No* atual = pi->topo;
    while (atual != NULL){
        c++;
        atual = atual->prox;
    }
    return c;
}
