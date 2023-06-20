#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "crud_pessoa.h"

void printOps()
{
    puts("Escolha uma das seguintes opções:");
    puts("0 - Sair");
    puts("1 - Adicionar pessoas");
    puts("2 - Editar dados da pessoa a partir do código");
    puts("3 - Remover pessoa a partir do código");
    puts("4 - Imprimir os dados de uma pessoa específica.");
    puts("5 - Imprimir os dados de todas as pessoas");
    printf("Opção > ");
    return;
}


void printPessoa(Pessoa pessoa)
{
    puts("####################");
    puts("Dados da pessoa:");
    printf("Código: %llu\n", pessoa.codigo);
    printf("Nome: %s\n", pessoa.nome);
    printf("Idade: %d\n", pessoa.idade);
    printf("Altura: %0.2f\n", pessoa.altura);
    puts("####################");
    return;
}


Pessoa preencherFormulario()
{
    Pessoa pessoa;
    int len;

    puts("Insira o código da pessoa:");
    scanf("%llu", &pessoa.codigo);
    getchar();

    puts("Insira o nome da pessoa:");
    fgets(pessoa.nome, TAMANHO_DO_NOME, stdin);
    len = strlen(pessoa.nome);
    if (len > 0 && pessoa.nome[len - 1] == '\n')
        pessoa.nome[--len] = '\0';

    puts("Insira a idade da pessoa:");
    scanf("%d", &pessoa.idade);
    getchar();

    puts("Insira a altura da pessoa:");
    scanf("%f", &pessoa.altura);
    getchar();

    printPessoa(pessoa);

    return pessoa;
}


void adicionarPessoa(Lista *lista)
{
    Pessoa pessoa = preencherFormulario();
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL)
    {
        puts("Erro ao alocar memória. Encerrando o programa...");
        puts("Pressione uma tecla para encerrar...");
        getchar();
        exit(EXIT_FAILURE);
    }

    novo->pessoa = pessoa;
    novo->ant = NULL;
    novo->prox = NULL;

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
    }
    else if (pessoa.codigo < lista->inicio->pessoa.codigo)
    {
        novo->prox = lista->inicio;
        lista->inicio->ant = novo;
        lista->inicio = novo;
    }
    else
    {
        No *atual = lista->inicio;
        while (
            atual->prox != NULL &&
            pessoa.codigo > atual->prox->pessoa.codigo &&
            pessoa.codigo != atual->pessoa.codigo)
        {
            atual = atual->prox;
        }

        if (atual->pessoa.codigo == pessoa.codigo)
        {
            puts("Codigo já existente! Não foi possível adicionar...");
            free(novo);
            return;
        }

        if (atual->prox != NULL)
        {
            atual->prox->ant = novo;
        }
        novo->ant = atual;
        atual->prox = novo;
    }
    return;
}


void atualizarNome(char* nome){
    int op;
    do{
        puts("Deseja atualizar o nome? [0 - Não, 1- Sim]");
        scanf("%d", &op);
        getchar();
        if (op == 1)
        {
            printf("O valor atual é %s. Entre com o novo nome: \n", nome);
            fgets(nome,TAMANHO_DO_NOME, stdin);
            int len = strlen(nome);
            if (len > 0 && nome[len - 1] == '\n')
                nome[--len] = '\0';
            break;
        }
        else if (op != 0)
        {
            puts("opção inválida");
        }
    } while (op != 0);
    return;
}


void atualizarIdade(int* idade){
    int op;    
    do{
        puts("Deseja atualizar a Idade ? [0 - Não, 1- Sim]");
        scanf("%d", &op);
        getchar();
        if (op == 1)
        {
            printf("A idade atual é %d. Entre com o novo valor para a idade: \n", *idade);
            scanf("%d", idade);
            getchar();
            break;
        }
        else if (op != 0)
        {
            puts("opção inválida");
        }
    } while (op != 0);
    return;
}


void atualizarAltura(float* altura){
    int op;    
    do{
        puts("Deseja atualizar a Altura ? [0 - Não, 1- Sim]");
        scanf("%d", &op);
        getchar();
        if (op == 1)
        {    
            printf("A altura atual é %0.2f. Entre com o novo valor para a altura: \n", *altura);
            scanf("%f", altura);
            getchar();
            break;            
        }
        else if (op != 0)
        {
            puts("opção inválida");
        }
    } while (op != 0);
    return;
}


Pessoa editar(Pessoa pessoa)
{
    int op;
    puts("Editar dados:");
    atualizarNome(pessoa.nome);
    atualizarIdade(&pessoa.idade);
    atualizarAltura(&pessoa.altura);
    return pessoa;
}


void imprime(Lista *lista)
{
    puts("Imprimindo a lista.");

    No *ptr = lista->inicio;
    if (ptr == NULL)
    {
        puts("lista vazia");
    }
    else
    {
        while (ptr != NULL)
        {
            printPessoa(ptr->pessoa);
            ptr = ptr->prox;
        }
    }
    return;
}


No* buscarPorCodigo(Lista* lista, int codigo){
    No* atual = lista->inicio;

    while(atual != NULL && atual->pessoa.codigo != codigo)
        atual = atual->prox;
    return atual;
}


void remover(Lista* lista, int codigo){
    No* atual = buscarPorCodigo(lista, codigo);

    if(atual == NULL){
        puts("código não encontrado");
        return;
    }

    if(atual->ant == NULL){ 
        lista->inicio = atual->prox;
    }else{
        atual->ant->prox = atual->prox;
    }

    if(atual->prox != NULL){
        atual->prox->ant = atual->ant; 
    }
    puts("Pessoa a ser removida");
    printPessoa(atual->pessoa);
    free(atual);
    printf("Pessoa com o código %d removida!\n", codigo);
    return;
}

void menuAdicionar(Lista* lista){
    adicionarPessoa(lista);
    puts("Pressione uma tecla para continuar...");
    getchar();
    return;
}

void menuEditar(Lista* lista){
    int codigo;
    No* no;

    puts("Forneça o código da pessoa: ");
    scanf("%d",&codigo);
    getchar();

    no = buscarPorCodigo(lista, codigo);
    
    if(no == NULL){
        puts("Código não encontrado.");
    }else{
        no->pessoa = editar(no->pessoa);
        puts("Dado Atualizado");
        printPessoa(no->pessoa);
    }

    puts("Pressione enter para continuar...");
    getchar();
    
    return;
}

void menuRemover(Lista* lista){
    int codigo;
    puts("Forneça o código da pessoa a ser removida: ");        
    scanf("%d",&codigo);
    getchar();
    remover(lista, codigo);
    puts("Pressione uma tecla para continuar...");
    getchar();
    return;
}

void menuImprimirPessoa(Lista* lista){
    int codigo;
    No* no;

    puts("Forneça o código da pessoa: ");
    scanf("%d",&codigo);
    getchar();
    
    no = buscarPorCodigo(lista, codigo);
        if(no == NULL){
        puts("Código não encontrado.");
    }else{
        printPessoa(no->pessoa);
    }
    puts("Pressione uma tecla para continuar...");
    getchar();
    return;
}

void menuImprimirLista(Lista* lista){
    imprime(lista);
    puts("Pressione uma tecla para continuar...");
    getchar();
    return;
}

void executa(Lista *lista, int op)
{

    switch (op)
    {
    case 0:
        return;
        break;
    case 1:
        menuAdicionar(lista);
        break;
    case 2:
        menuEditar(lista);
        break;
    case 3:
        menuRemover(lista);
        break;
    case 4:
        menuImprimirPessoa(lista);
        break;
    case 5:
        menuImprimirLista(lista);
        break;
    default:
        break;
    }
}


void menu(Lista *lista)
{
    int op;
    int result = 0;

    do{
        printOps();
        scanf("%d", &op);
        getchar();
        if (0 <= op <= 5)
        {
            executa(lista, op);
        }
        else
        {
            puts("Opção inválida");
        }
    } while (op != 0);
    return;
}


void removerTudo(Lista *lista)
{
    puts("Desalocando memória...");    
    No* atual = lista->inicio;
    while(atual != NULL){
        lista->inicio = atual->prox;
        free(atual);
        atual = lista->inicio;
        if(lista->inicio == NULL){
            puts("Lista Vazia");
        }
    }
    if(lista->inicio == NULL){
        puts("Liberando ponteiro para a lista");
        free(lista);
    }
    return;    
}