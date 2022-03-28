#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    int id ;
    char nome[20];
    int quantidade;
    float vl_unitario;
    float vl_total;
    int qt;
    int vendido;
} estoque;

estoque *PRODUTOS;
void cadastrar_produto();
void consultar_produto();
void adicionar();
void venda();
void caixa();
int tabela();
void w_file();
void sair();

int TAMANHO = 10;
int n = 0;
int POSICAO = 0;

//Coloca os dados do arquivo dentro de um array de struct,se o arquivo existe

void Arquivo(){
    FILE *produtos_arquivos; 
    produtos_arquivos = fopen("produtos.ily","rb"); //PRODUTOS-ponteiro para armazenar o endereço do bloco alocado
    PRODUTOS = (estoque *)malloc(TAMANHO*(sizeof(estoque))); //chamada da função malloc para reservar espaço para 10 elementos do tipo estoque
    if(produtos_arquivos != NULL){ //verifica se o endereço de retorno é válido
        while(fread(&PRODUTOS[POSICAO],sizeof(PRODUTOS[POSICAO]),1,produtos_arquivos)){
            if(POSICAO >= TAMANHO-1){
                TAMANHO = TAMANHO*2;
                PRODUTOS= (estoque *)realloc(PRODUTOS,TAMANHO*(sizeof(estoque)));
            }
            POSICAO++;
        }
    }
    fclose(produtos_arquivos);
}

int main(void){
    setlocale(LC_ALL, "Portuguese");
    system("color F0");
    Arquivo();
    //FILE *produtos_arquivo;
    int opcao = 0;
    while (opcao!=7){
    system("cls");

        printf("--------------------------------------------------------------------------------\n");
        printf("----------------------------GERENCIADOR DE SUPERMERCADO-------------------------\n");
        printf("--------------------------------------------------------------------------------\n");

        printf("1 - CADASTRAR PRODUTOS.\n");
        printf("2 - ADICIONAR NOVA QUANTIDADE.\n");
        printf("3 - VENDER PRODUTOS.\n");
        printf("4 - CONSULTAR PRODUTOS CADASTRADOS.\n");
        printf("5 - CAIXA E ESTOQUE.\n");
        printf("6 - TABELA DE INFORMAÇÕES.\n");
        printf("7 - SAIR.\n\n");
        printf("Escolha uma opção: \n");
        scanf("%d", &opcao);
        
        // Os produtos cadastrados serao escritos no arquivo depois do usuario digitar o numero pra sair

        switch (opcao) {
            case 1:
                cadastrar_produto();
                break;
            case 2:
                adicionar();
                break;
            case 3:
                venda();
                break;
            case 4:
                consultar_produto();
                break;
            case 5:
                caixa();
                break;
            case 6:
                tabela();
                break;
            case 7:
                w_file();
                sair();
                break;
            default:
                system("cls");
                printf("Opção inválida. Tente novamente.\n\n");                
    			sleep(1);
        }
    }
    return 0;

}
//cadastrar produtos
void cadastrar_produto() {
    system("cls");
    estoque produto;
    produto.id = POSICAO;
    int i;

    if(POSICAO >= TAMANHO-1){
        TAMANHO = TAMANHO*2;
        PRODUTOS = (estoque *)realloc(PRODUTOS,TAMANHO*(sizeof(estoque)));
    }

    produto.vendido = 0;

    printf("Digite o nome do produto: ");
    scanf ("%s", &produto.nome);
    	if(strcmp(produto.nome, "0") == 0)
    		return;

    for(i=0; i<=POSICAO; i++){
        while(strcmp (produto.nome, PRODUTOS[i].nome) == 0 ){  // strcmp-comparar strings
            printf("Produto já cadastrado \n");
            printf("Digite o nome de um novo produto: ");
            scanf ("%s", &produto.nome);
            i=0;
		} 
        
    }

    printf("Quantos produtos você quer armazenar? ");
    scanf ("%d", &produto.quantidade);
    printf("Qual o valor unitário do produto? ");
    scanf ("%f", &produto.vl_unitario);

    system("cls");

    printf("Produto %d: %s\n", produto.id, produto.nome);
    printf("Quantidade armazenada: %d\n", produto.quantidade);
    printf("Valor unitário: R$ %.2f", produto.vl_unitario);
    n++;

    PRODUTOS[POSICAO] = produto;
    POSICAO++;
    printf("\n\nProduto %d cadastrado com sucesso.\n\n", POSICAO - 1);
    system("pause");

}

//adicionar quantidade
void adicionar(){
    system("cls");
    int i;
    int qtd1 = 0;
    char op[50];
    int p_n = 0;

    system("cls");
    for (i=0; i<= POSICAO-1; i++){
        printf("%s | ", PRODUTOS[i].nome);
    }

    printf("\n\nQual produto quer adicionar? ");
    scanf ("%s", &op);

    for (i=0; i<= POSICAO-1; i++){
        if (strcmp(op, PRODUTOS[i].nome)==0){
            p_n = 1;
            printf("Digite a quantidade a armazenar:");
            scanf("%d",&qtd1);
            PRODUTOS[i].quantidade = PRODUTOS[i].quantidade + qtd1;
            printf("Quantidade adicionada. \n");
        }
    }
    if(p_n == 0){
        printf("Produto não cadastrado. \n");
    }
    system("pause");
}

//venda de produtos
void venda(){
    char vend[20];
    int qtd;
    int p_nao_cad = 0;
    int i;

    system("cls");
    for (i=0; i<= POSICAO-1; i++){
        printf("%s | ", PRODUTOS[i].nome);
    }

    printf("\n\nQual produto você quer vender? ");
    scanf("%s", &vend);

    for (i=0; i<= POSICAO-1; i++){
        if (strcmp(vend, PRODUTOS[i].nome)==0){
            p_nao_cad = 1;
            printf("Quantos produtos você quer vender? ");
            scanf("%d",&qtd);
            if (qtd > 0 && qtd <= PRODUTOS[i].quantidade){
                PRODUTOS[i].vendido += qtd;
                PRODUTOS[i].quantidade = PRODUTOS[i].quantidade - qtd;
                PRODUTOS[i].vl_total = PRODUTOS[i].vendido * PRODUTOS[i].vl_unitario;

                printf("Foram vendidos %d produto(s).\n", qtd);

            }else
                printf("Quantidade não cadastrada. \n");
            printf("Você tem apenas: %d produto(s) no estoque.\n", PRODUTOS[i].quantidade);
        }
    }

    if(p_nao_cad == 0){
        printf("Produto não cadastrado. \n");
    }

    system("pause");
}

//consultar produtos cadastrados
void consultar_produto() {
    int i;
    int n;
    system("cls");

    for (i=0; i < POSICAO; i++){
        printf("Produto %d: %s\n", PRODUTOS[i].id, PRODUTOS[i].nome);
        printf("Quantidade no estoque: %d\n", PRODUTOS[i].quantidade);
        printf("Valor unitário: R$ %.2f\n\n", PRODUTOS[i].vl_unitario);
        printf("--------------------------------------------------------------------------------\n");
    }

    system("pause");

}
//caixa e estoque
void caixa(){
    char prod[30];
    int j, i;
    int p_nao_cad = 0;
    float vl_total;
    int qtd;
    int qt;

    system("cls");
    
    for (i=0; i<= POSICAO-1; i++){ 
        printf("%s | ", PRODUTOS[i].nome);
    }
	    
    printf("\nQual produto você quer consultar?\n");
    scanf("%s", &prod);
    for (j=0; j<= TAMANHO; j++){ 
        if (strcmp(prod, PRODUTOS[j].nome)==0){
            p_nao_cad = 1;	
            
            printf("Produto %d: %s\n", PRODUTOS[j].id, PRODUTOS[j].nome);
            printf("Quantidade no estoque: %d\n", PRODUTOS[j].quantidade);
            printf("Valor unitário: R$ %.2f\n\n", PRODUTOS[j].vl_unitario);

            printf("Foram vendidos: %d produto(s).\n", PRODUTOS[j].vendido);
            printf("Valor total: R$ %.2f\n", PRODUTOS[j].vl_total);
        }
    }
    
        if(p_nao_cad == 0){
            printf("Produto não cadastrado.\n");
        }

    system("Pause");
}

//Tabela de informacoes
int tabela(){
    int i;
    int j;
    
    int b;
    system("cls");

    for (b=0; b<POSICAO; b++){
        printf("Produto %d: %s\n", PRODUTOS[b].id, PRODUTOS[b].nome);
        printf("Valor obtido com a venda do produto: R$ %.2f\n\n", PRODUTOS[b].vl_total);
        printf("Foram vendidos: %d\n", PRODUTOS[b].vendido);
        printf("Quantidade no estoque: %d\n\n", PRODUTOS[b].quantidade);
        printf("--------------------------------------------------------------------------------\n");

    }
    system("Pause");
}
//escreve no arquivo
void w_file(){
    int i;
    FILE *produtos_arquivo;
    produtos_arquivo = fopen("produtos.ily","wb");
    for(i=0;i<POSICAO;i++){
        fwrite(&PRODUTOS[i],sizeof(PRODUTOS[i]),1,produtos_arquivo);
    }
    fflush(produtos_arquivo);
    fclose(produtos_arquivo);
}
//sair
void sair(){	
    system("cls");
    printf("--------------------------------------------------------------------------------\n");
    printf("---------------------------------*VOLTE SEMPRE!*--------------------------------\n");
    printf("--------------------------------------------------------------------------------\n");
    system("Pause");
}

