#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Biblioteca necessária para usar funcionalidades de strings (strcpy, strcmp, etc.)

// Define uma constante para o tamanho máximo de texto
#define MAX_STR_LEN 50 // tamanho máximo para strings

// PARTE 1: Lista estatica
// Uma lista estatica é uma estrutura de dados que tem um tamanho fixo definido em tempo de compilação.
// implementada como um array.
// Toda a memoria necessaria para armazenar os elementos da lista é alocada de uma vez quando a variavel é criada.

//Define uma constante para o numero maximo de itens que nossa lista pode conter
#define TAM_MAX 10 // tamanho maximo da lista estatica(Mochila)


// Estrutura que representa a lista estatica
typedef struct{
    char dados[TAM_MAX][MAX_STR_LEN]; // Matriz 10 linhas (itens) e 50 colunas (tamanho maximo de cada string)
    int quantidade; // este é nosso contator de elementos na lista

} ListaEstatica;


// Função da lista estatica para inicializar a lista

void inicializaListaEstatica(ListaEstatica* lista);

void inserirElementoListaEstatica(ListaEstatica* lista, const char* elemento);
void removerElementoListaEstatica(ListaEstatica* lista, const char* elemento);
void listarElementosListaEstatica(const ListaEstatica* lista);



//Função principal e menus

void menuListaEstatica();

int main(){

    int opcao;
    do {
        printf("Deseja acessar a mochila?:\n");
        printf("1. Mochila de loot inicial\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuListaEstatica();
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;

}

// Implementações das funções para lista estatica e lista encadeada estao em outros arquivos

void inicializaListaEstatica(ListaEstatica* lista) {
    lista->quantidade = 0; // Inicializa o contador de elementos como 0
}

void inserirElementoListaEstatica(ListaEstatica *lista, const char *texto){
    // Primeiro, ela verifica se lista -> quantidade ja atingiu TAM_MAX.
    //Se sim, imprime uma mensagem de erro e retorna.
    if(lista->quantidade >= TAM_MAX){
        printf("Erro: Mochila cheia. Nao e possivel inserir mais itens.\n");
        return;
    }

    // A inserçao ocorre na primeira "linha" disponivel do array dados.
    //Para strings, nao podemos fazer "lista->dados[i]  texto", pois arrays nao suportam atribuicoes diretas.
    // precisamos copiar o texto usando a funcao strcpy da biblioteca string.h
strcpy(lista->dados[lista->quantidade], texto);
    lista->quantidade++; // Incrementa o contador de elementos
    printf("Elemento '%s' Item inserido com sucesso.\n", texto);
}


void removerListaEstatica(ListaEstatica *lista, const char *texto){
    int i, pos = -1; // pos ira armazenar a posiçao do elemento a ser removido

    // para comparar strings, usamos strcmp(). retorna 0 se forem iguais
    // A funçao percorre o array dados procurando o texto a ser removido de 0 ate quantidade - 1
    // para comparar strings, usamos strcmp(string1, string2).
    // essa função retorna 0 se as strings forem iguais. se encontrar, armazena a posiçao em pos e sai do loop.

    for (i = 0; i < lista->quantidade; i++){
        if(strcmp(lista->dados[i], texto) == 0){
            pos = i;
            break;
        }
    }

    // tratamento de erro se o loop terminar e pos continuar -1, o item não foi encontrado.
    if (pos == -1){
        printf("Erro: Item '%s' Item não encontrado dentro da mochila.\n", texto);
        return;
    }


    // fechar a lacuna:  para remover um item do meio da lista, criamos um "buraco" que precisamos fechar.
    // para isso, deslocamos todos os elementos apos pos uma posiçao para a esquerda.
    // o loop for começa na posição do item removido e copia cada item i+1 para a posiçao i.
    // deslocar os elementos posteriores para esquerda usando strcpy

    for (i = pos; i < lista->quantidade - 1; i++){
        strcpy(lista->dados[i], lista->dados[i + 1]);
    }

    // Atualização do contador: finalmente, quantidade é decrementado para refletir a remoção do item.
    lista->quantidade--;
    printf("Elemento '%s' removido com sucesso da Mochila.\n", texto);

}

void listarElementosListaEstatica(const ListaEstatica *lista){
    if(lista->quantidade == 0){
        printf("A Mochila esta vazia.\n");
        return;
    }

    printf("Itens dentro da mochila:\n");
    for(int i = 0; i < lista->quantidade; i++){
        printf("%d: %s\n", i + 1, lista->dados[i]);
    }
    printf("\n");
}
// Menus simples para interagir com as listas (implementações mínimas)
void menuListaEstatica() {
    ListaEstatica lista;
    inicializaListaEstatica(&lista);
    int op;
    char texto[MAX_STR_LEN];

    do {
        printf("\n--- Acessando a mochila ---\n");
        printf("1 - Inserir\n2 - Remover\n3 - Listar\n0 - Voltar\nOpcao: ");
        if (scanf("%d", &op) != 1) { // proteger contra entrada invalida
            while (getchar() != '\n');
            op = -1;
        }

        switch (op) {
            case 1:
                printf("Digite o item que deseja inserir (sem espacos): ");
                scanf("%49s", texto);
                inserirElementoListaEstatica(&lista, texto);
                break;
            case 2:
                printf("Digite o item que deseja remover: ");
                scanf("%49s", texto);
                removerListaEstatica(&lista, texto);
                break;
            case 3:
                listarElementosListaEstatica(&lista);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op != 0);
}