#include <stdio.h>
#include <stdlib.h>

typedef struct{
int dia,mes,ano;
}Data;

typedef struct{
    char nome[50];
    Data data;
}Pessoa;

typedef struct no{
    Pessoa p;
    struct no *proximo;
}No;

Pessoa ler_pessoa(){
    Pessoa p;
    printf("\nNome: ");
    fgets(p.nome, 49, stdin);
    printf("\nData de nascimento: ");
    scanf("%2d/%2d/%4d", &p.data.dia,&p.data.mes,&p.data.ano);
    return p;
}

void imprimirPessoa(Pessoa p){
    printf("\n\tNome: %s", p.nome);
    printf("\tData de nas.:%2d/%2d/%4d", p.data.dia,p.data.mes,p.data.ano);
}

//Funcao para a operação push(empilhar)
No* empilhar(No *topo){
    No *novo = malloc(sizeof(No));

    if(novo){
        novo-> p = ler_pessoa();
        novo->proximo = topo;
        return novo;
    }
    else
        printf("\n\nErro ao alocar memoria");
    return NULL;
}

No* desempilhar(No **topo){
    if(*topo!=NULL){
        No *remover = *topo;
        *topo = remover->proximo;
        return remover;
    }
    else
        printf("\n\nPilha vazia!");
    return NULL;
}

void imprimir_pilha(No *topo){
    printf("\n----------Pilha-----------\n");
    while(topo){
        imprimir_pessoa(topo->p);
        topo = topo->proximo;
    }
    printf("\n-------Fim da Pilha-------\n");
}

int main()
{
    No *remover, *topo = NULL;
    int opcao;

    do{
        printf("\n0 - Sair\n1 - Empilhar\n2 - Desempilhar\n3 - Imprimir\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
        case 1:
            topo = empilhar(topo);
            break;
        case 2:
            remover = desempilhar(&topo);
            if(remover){
                    printf("Elemento removido com sucesso.\n");
                imprimir_pessoa(remover->p);
            }
            else
                printf("Sem No a remover.\n");
            break;
        case 3:
            imprimir_pilha(topo);
            break;
        default:
            if(opcao!=0)
                printf("\nOpcao invalida\n");
        }
    }while(opcao!=0);
    return 0;
}
