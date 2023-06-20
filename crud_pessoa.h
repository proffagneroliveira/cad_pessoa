#ifndef CRUD_PESSOA
#define CRUD_PESSOA

#define TAMANHO_DO_NOME 65

typedef struct Pessoa
{
    unsigned long long int codigo;
    char nome[TAMANHO_DO_NOME];
    int idade;
    float altura;
} Pessoa;

typedef struct No
{
    struct No *ant;
    struct Pessoa pessoa;
    struct No *prox;
} No;

typedef struct Lista
{
    No *inicio;
} Lista;

void printOps();
void printPessoa(Pessoa pessoa);
Pessoa preencherFormulario();
void adicionarPessoa(Lista *lista);
void atualizarNome(char* nome);
void atualizarIdade(int* idade);
void atualizarAltura(float* altura);
Pessoa editar(Pessoa pessoa);
void imprime(Lista *lista);
No* buscarPorCodigo(Lista* lista, int codigo);
void remover(Lista* lista,int codigo);
void menuAdicionar(Lista* lista);
void menuEditar(Lista* lista);
void menuRemover(Lista* lista);
void menuImprimirPessoa(Lista* lista);
void menuImprimirLista(Lista* lista);
void executa(Lista *lista, int op);
void menu(Lista *lista);
void removerTudo(Lista *lista);

#endif