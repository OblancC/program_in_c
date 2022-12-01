#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int dia,mes,ano;
}Data;

typedef struct{
    char rua[50];
    char bairro[50];
    char cidade[50];
    char pais[50];
    int num, cep;
}Endereco;

typedef struct{
    int codigo;
    Data dataAss;
    char cargo[50];
    float salario;
}Contrato;

typedef struct {
    char nome[50];
    Data dataNas;
    Endereco end;
    Contrato contr;
}Pessoa;

typedef struct no{
    Pessoa p;
    struct no *proximo;
}No;

//Impressoes das informa�oes de uma pessoa

void imprimirData(Data d){
    printf("%d/%d/%d\n", d.dia,d.mes,d.ano);
}

void imprimirEndereco(Endereco end){
    printf("\tEndereco:\n");
    printf("\t\tRua: %s:",end.rua);
    printf("\t\tBairro: %s", end.bairro);
    printf("\t\tCidade: %s", end.cidade);
    printf("\t\tPais: %s", end.pais);
    printf("\t\tNumero: %d\n", end.num);
    printf("\t\tCEP: %d\n", end.cep);
}

void imprimirContrato(Contrato c){
    printf("\tContrato %d:\n", c.codigo);
    printf("\t\tCargo: %s", c.cargo);
    printf("\t\tSalario R$%.2f\n", c.salario);
    printf("\t\tData de ad.: ");
    imprimirData(c.dataAss);
}

void imprimirPessoa(Pessoa p){
    printf("\n\tNome: %s", p.nome);
    printf("\tData de nas.:");
    imprimirData(p.dataNas);
    imprimirEndereco(p.end);
    imprimirContrato(p.contr);
}

//--------------Fim da Impress�o

Data lerData(){
    Data d;
    printf("\nDigite a data no formato dd mm aaaa: ");
    scanf("%d %d %d", &d.dia,&d.mes, &d.ano);
    return d;
}

Endereco lerEndereco(){
    Endereco end;
    printf("\nRua: ");
    fgets(end.rua, 49, stdin);
    printf("\nBairro:");
    fgets(end.bairro, 49, stdin);
    printf("\nCidade: ");
    fgets(end.cidade, 49, stdin);
    printf("\nPais: ");
    fgets(end.pais, 49, stdin);
    printf("\nNumero: \n");
    scanf("%d", &end.num);
    printf("\nCEP: ");
    scanf("%d", &end.cep);
    getchar();
    return end;
}

Contrato lerContrato(){
    Contrato c;
    printf("\nCodigo do contrato: ");
    scanf("%d", &c.codigo);
    printf("\nData de Assinatura: ");
    c.dataAss = lerData();
    getchar();
    printf("\nCargo: ");
    fgets(c.cargo, 49, stdin);
    printf("\nSalario: R$");
    scanf("%f", &c.salario);
    getchar();
    return c;
}

Pessoa lerPessoa(){
    Pessoa p;
    printf("\nNome: ");
    fgets(p.nome, 49, stdin);
    printf("\nData de nascimento: ");
    p.dataNas = lerData();
    p.contr = lerContrato();
    p.end = lerEndereco();
    return p;
}

void inserir_na_fila(No **fila, Pessoa pessoa){
    No *aux, *novo = malloc(sizeof(No));
    if(novo){
        novo->p = pessoa;
        novo->proximo = NULL;
        if(*fila == NULL)   //Caso seja o primeiro valor na fila.
            *fila = novo;
        else{
            aux = *fila;
            while(aux->proximo) //Caminha para o ultima posi��o da fila.
                aux = aux->proximo;
            aux->proximo = novo;
        }

    }
    else
        printf("\nErro ao alocar memoria\n");
}

No* remover_da_fila(No **fila){
    No *remover = NULL;

    if(*fila){
        remover = *fila;
        *fila = remover->proximo;
    }
    else
        printf("Fila Vazia\n");
    return remover;
}

void imprimir(No *fila){
    printf("\t------FILA------\n");
    while(fila){
        imprimirPessoa(fila->p);
        fila = fila->proximo;
        if(fila)
            printf("\t--------------\n\t");
    }
    printf("\n\t-----FIM DA FILA-----\n");
}

int main()
{
    No *r, *fila = NULL;
    int opcao;
    Pessoa p;

    do{
        printf("\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
        case 1:
            p = lerPessoa();
            inserir_na_fila(&fila,p);
            break;
        case 2:
            r = remover_da_fila(&fila);
            if(r){
                imprimirPessoa(r->p);
                free(r);
            }
            break;

        case 3:
            imprimir(fila);
            break;
        default:
            if(opcao!= 0){
                printf("Opcao invalida\n");
            }
            break;

        }
    }while(opcao!=0);
    return 0;
}