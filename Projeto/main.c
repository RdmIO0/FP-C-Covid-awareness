//
//  main.c
//  Projeto Programação
//
//  Created by Artem Alekseev on 05/01/2021 & Rafael Matos

 //  Includes + Defines
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_NOME 50
#define MAX_ESCOLAS 5
#define MAX_QUESTIONARIOS 1000
#define FILE_FORM "DATA.bin"


// Estruturas

// Estrutura Escola
typedef struct escola {
    int identificador;
    char nome[50];
    char localidade[50];
} ESCOLA_T;

//Estrutura Hora
typedef struct hora {
    int hora;
    int minutos;
} HORA_T;

//Estrutura Data
typedef struct data {
    int dia;
    int mes;
    int ano;
    HORA_T hora;
} DATA_T;

// Estrutura Questionarios
typedef struct questionario {
    int identificador_q;
    DATA_T data;
    ESCOLA_T escola;
    char risco_c [20];
    int idade;
    char genero [15];
    char localidade[50];
    char participante [30];
    char contacto_covid [15];
    char *sintomas [7];
    char *doencas [8];
    float temperatura;
    char risco[8];
    
} QUESTIONARIO_T;


// Chamada De Funções

//Função Buscar Inteiro
int ler_inteiro(char texto[], int min, int max);
//Função Menu Principal
void menu_opcoesprincipal(void);
//Função Sub-Menu Estatísticas
int menu_opcoesestatisticas(void);
// Funcao Mostrar escolas 1 por 1
int menu_escolas (QUESTIONARIO_T questionario[],ESCOLA_T escola[], int num_escolas1, int num_escolas2, int num_escolas3, int num_escolas4, int num_escolas5, int num_questionarios);
//Função Ler cada 1 escola
int ler_escolas(ESCOLA_T escolas[], int num_escolas);
//Função lê escolas introduzidas
ESCOLA_T ler_escola(int num_escolas);
//Função Regista escolas
int registar_escolas(ESCOLA_T escolas[], int num_escolas);
//Função Mostra Escolas
void mostrar_escola(ESCOLA_T escola);
//Função Contador de mostrar escolas
void mostrar_escolas(ESCOLA_T escolas[], int num_escolas);
//Função Lê uma string
void ler_string(char texto[], char str[], int max);
//Função Regista questionarios
int registar_questionario(QUESTIONARIO_T questionarios[],int num_escolas, int num_questionarios,int escola);
//Função Lê questionarios introduzidos
QUESTIONARIO_T ler_questionario(int num_questionarios, int escola);
//Função Lê a data Introduzida
DATA_T ler_data(void);
//Função Mostra questionarios
void mostrar_questionario(QUESTIONARIO_T questionario);
//Função Contador de mostrar questionários
void mostrar_questionarios(QUESTIONARIO_T questionario[],int num_questionarios);
//Função Lê a idade introduzida
int ler_idade(char texto[]);
//Função selecionar o genero
void selecionar_genero(QUESTIONARIO_T *questionario);
//Função escolha se esteve em contacto
void covid_contacto(QUESTIONARIO_T *questionario);
//Função seleciona as doencas que tem
void doencas(QUESTIONARIO_T *questionario);
//Função Lê a temperatura que introduziu
float ler_temperatura(char texto[]);
//Função Mostra todas as doencas da pessoa que fez o questionario
void mostrar_doencas(char* doencas[]);
//Função diz que esteve em contágio
void verifica_contagio (QUESTIONARIO_T *questionario);
//Função Conta questionários
void conta_questionarios(QUESTIONARIO_T questionario[], int num_questionarios);
//Função pesquisa questionarios por genero ( menu + funçao)
int menu_pesquisar_genero(void);
//Função Mostra os questionarios por genero
void mostrar_questionarios_genero(QUESTIONARIO_T questionario[], int num_questionarios);
//Função Seleciona o tipo de pessoa ( docente , professor, etc..)
void selecionar_tipo(QUESTIONARIO_T *questionario);
//Função  selecionar sintomas que apresenta
void sintomas(QUESTIONARIO_T *questionario);
//Função Mostra que sintomas tem
void mostrar_sintomas(char* sintomas[]);
// Funcao Apresenta questionarios respondidos por escola
int apresenta_questionarios(QUESTIONARIO_T questionario[],ESCOLA_T escola[], int num_escolas1, int num_escolas2, int num_escolas3, int num_escolas4, int num_escolas5, int num_questionarios);
// Funcao Estatisticas Genero
void mostrar_estatisticas_genero (ESCOLA_T escola[],QUESTIONARIO_T questionario[], int num_questionarios,int estatisticas[]);
// Funcao estatisticas Genero part 2
void mostrar_estatisticas_genero_part2(int estatisticas_array[],int num_questionarios);

//Funções ler e gravar dados das escolas e dos questionários

//questionarios
void gravar_forms(QUESTIONARIO_T questionario[], int num_questionarios);
int ler_forms(QUESTIONARIO_T questionario[]);

//escolas
void gravar_schools(ESCOLA_T escola[], int num_escolas);
int ler_schools(ESCOLA_T escola[]);


// Main

int main() {
    ESCOLA_T escolas[MAX_ESCOLAS];
    QUESTIONARIO_T questionario[MAX_QUESTIONARIOS];
    int estatisticas[12];
    int num_escolas = 0;
    int num_escolas1 = 0;
    int num_escolas2 = 0;
    int num_escolas3 = 0;
    int num_escolas4 = 0;
    int num_escolas5 = 0;
    int escola;
    
    int num_questionarios=0;
    int op,op1;
    do {
        op = menu_escolas(questionario,escolas,num_escolas1,num_escolas2,num_escolas3,num_escolas4,num_escolas5,num_questionarios);
        
        switch (op) {
        case 1:
                num_escolas += registar_escolas(escolas, num_escolas);
            break;

        case 2:
                mostrar_escolas(escolas, num_escolas);
            break;

        case 3:
                escola = ler_escolas(escolas,num_escolas);
                switch(escola)
                {
                    case 1:
                        num_escolas1 += registar_questionario(questionario, num_escolas1,num_questionarios,escola);
                        break;
                    case 2:
                        num_escolas2 += registar_questionario(questionario, num_escolas2,num_questionarios,escola);
                        break;
                    case 3:
                        num_escolas3 += registar_questionario(questionario, num_escolas3,num_questionarios,escola);
                        break;
                    case 4:
                        num_escolas4 += registar_questionario(questionario, num_escolas4,num_questionarios,escola);
                        break;
                    case 5:
                        num_escolas5 += registar_questionario(questionario, num_escolas5,num_questionarios,escola);
                        break;
                }
                num_questionarios=num_escolas1+num_escolas2+num_escolas3+num_escolas4+num_escolas5;
            break;

        case 4:
                mostrar_questionarios(questionario, num_questionarios);
            break;

        case 5:
                
                do{
                    op1 = menu_opcoesestatisticas();
                    switch (op1) {
                    case 1:
                            conta_questionarios(questionario, num_questionarios);
                        break;

                    case 2:
                            apresenta_questionarios(questionario, escolas,  num_escolas1,  num_escolas2,  num_escolas3,  num_escolas4,num_escolas5, num_questionarios);
                            
                        break;

                    case 3:
                            mostrar_estatisticas_genero_part2(estatisticas,num_questionarios);
                        break;

                    case 4:

                            
                        break;
                    }
                }while (op1 != 0);

                        break;
                    case 6:
                        gravar_schools(escolas, num_escolas);
                    break;
                    
                    case 7:
                        gravar_forms(questionario,num_questionarios);
                    break;
                    
                    case 8:
                    num_escolas= ler_schools(escolas);
                    break;
                
                    case 9:
                    num_questionarios= ler_forms(questionario);
                    break;
        }
    } while (op != 0);
    return 0;
}
    
// Menus

//Menu Principal
void menu_opcoesprincipal(void) {

    printf("* MENU PRINCIPAL *\n");
    printf("1 - Registar uma Escola\n");
    printf("2 - Consultar todas as Escolas\n");
    printf("3 - Registar um novo questionario\n");
    printf("4 - Consultar questionarios\n");
    printf("5 - Estatisticas\n");
    printf("6 - Guardar ficheiro Escola\n");
    printf("7 - Guardar ficheiro Questionarios\n");
    printf("8 - Ler ficheiros guardados Escolas\n");
    printf("9 - Ler ficheiros guardados Questionarios\n");
    printf("0 - Sair\n");
}
// Sub-Menu Estatísticas
int menu_opcoesestatisticas(void){
    int op1;
    
    printf("* Estatisticas *\n");
    printf("1 - Numero de questionarios respondidos\n");
    printf("2 - Numero de questionarios respondidos (por Escola)\n");
    printf("3 - Total de inquéritos por género e idade\n");
    printf("4 - Percentagem de inquéritos por nível de risco de contágio\n");
    printf("0 - Voltar Atras\n");
    op1 = ler_inteiro("Opcao: ", 0, 4);
    return op1;
}

// Menu Escolas

int menu_escolas (QUESTIONARIO_T questionario[],ESCOLA_T escola[], int num_escolas1, int num_escolas2, int num_escolas3, int num_escolas4, int num_escolas5, int num_questionarios){

    if(num_questionarios==0){
        printf("Não tem nenhum questionario respondido\n\n");
        printf("Por favor Adicione uma escola para poder respoder a Questionarios\n\n");
    }else{
        printf("\nQuestionarios Respondidios Por Escola\n");
        if(num_escolas1>0)
            printf("%s - %i \n",escola[0].nome,num_escolas1);
        if(num_escolas2>0)
            printf("%s - %i \n",escola[1].nome,num_escolas2);
        if(num_escolas3>0)
            printf("%s - %i \n",escola[2].nome,num_escolas3);
        if(num_escolas4>0)
            printf("%s - %i \n",escola[3].nome,num_escolas4);
        if(num_escolas5>0)
            printf("%s - %i \n",escola[4].nome,num_escolas5);
    }
    menu_opcoesprincipal();
    int op=ler_inteiro("Opcao: ", 0, 9);

    return op;
}
//Apresentar Questionarios respondidos por escola
int apresenta_questionarios(QUESTIONARIO_T questionario[],ESCOLA_T escola[], int num_escolas1, int num_escolas2, int num_escolas3, int num_escolas4, int num_escolas5, int num_questionarios){

    printf("* QUESTIONARIOS RESPONDIDOS POR ESCOLA *\n");
    if(num_escolas1>0)
        printf("%s - %i \n\n",escola[0].nome,num_escolas1);
    if(num_escolas2>0)
        printf("%s - %i \n\n",escola[1].nome,num_escolas2);
    if(num_escolas3>0)
        printf("%s - %i \n\n",escola[2].nome,num_escolas3);
    if(num_escolas4>0)
        printf("%s - %i \n\n",escola[3].nome,num_escolas4);
    if(num_escolas5>0)
        printf("%s - %i \n\n",escola[4].nome,num_escolas5);
    
    menu_opcoesprincipal();
    int op=ler_inteiro("Opcao: ", 0, 9);

    return op;
}


//Menu Genero
char menu_genero(void){
    char op_genero;
    
    printf("(F)eminino \n");
    printf("(M)asculino\n");
    printf("(S)air\n");
    printf("OPCAO -->\n");
    fflush(stdin);
    scanf("%c",&op_genero);
    return toupper(op_genero);
}

// Menu Tipo de participante
int menu_tipo(void) {
    int op_tipo;

    printf("* Tipo de Participante  *\n");
    printf("1 - Docente\n");
    printf("2 - Estudante\n");
    printf("3 - Funcionario\n");
    printf("4 - Investigador\n");
    printf("0 - Sair\n");
    op_tipo = ler_inteiro("Opcao: ", 0, 4);
    return op_tipo;
}

//Menu Generos
int menu_pesquisar_genero(void) {
    int op_tipo;

    printf("* Total de Inqueritos por Genero*\n");
    printf("1 - Feminino\n");
    printf("2 - Masculino\n");
    printf("0 - Sair\n");
    op_tipo = ler_inteiro("Opcao: ", 0, 2);
    return op_tipo;
}
//Menu esteve em contacto com alguma pessoa com Covid
char menu_covid(void){
    char op_contacto_covid;
    
    printf("Esteve em contacto com uma pessoa com covid? \n");
    printf("(S)im \n");
    printf("(N)ao\n");
    printf("(D)esconhecido\n");
    printf("(C)oncluir\n");
    printf("OPCAO -->\n");
    fflush(stdin);
    scanf("%c",&op_contacto_covid);
    return toupper(op_contacto_covid);
}

// Menu doencas
int menu_opcoes(void) {
    int op_doencas;

    printf("* Doencas *\n");
    printf("1 - Autoimune\n");
    printf("2 - Cancro\n");
    printf("3 - Cardiovascular\n");
    printf("4 - Diabetes\n");
    printf("5 - Hipertensao\n");
    printf("6 - Obesidade\n");
    printf("7 - Renal\n");
    printf("8 - Respiratoria\n");
    printf("0 - Sair\n");
    op_doencas = ler_inteiro("Opcao: ", 0, 8);
    return op_doencas;
}

// Menu sintomas
int menu_sintomas(void) {
    int op_sintomas;

    printf("* Sintomas  *\n");
    printf("1 - Dificuldade Respiratória\n");
    printf("2 - Dor Muscular\n");
    printf("3 - Fadiga\n");
    printf("4 - Falta de paladar\n");
    printf("5 - Nauseas\n");
    printf("6 - Febre\n");
    printf("7 - Tosse\n");
    printf("0 - Sair\n");
    op_sintomas = ler_inteiro("Opcao: ", 0, 7);
    return op_sintomas;
}

// Fuções de Seleção de Menu

// Funcao- Selecionar genero
void selecionar_genero(QUESTIONARIO_T *questionario){

char op_genero1;
    
    do{
        
        op_genero1=menu_genero();
        switch (op_genero1) {
            case 'F':
                strcpy(questionario->genero,"Feminino");
                break;
            case 'M':
                strcpy(questionario->genero,"Masculino");
                break;
            case 'S':
            default:
                printf("Por favor selecione um genero valido\n");
                break;
        
        }
    }while(op_genero1 !='S');
               
}

// Função - Selecionar Tipo
void selecionar_tipo(QUESTIONARIO_T *questionario){

int op_tipo1;
    
        op_tipo1=menu_tipo();
        switch (op_tipo1) {
            case 1:
                strcpy(questionario->participante,"Docente");
                break;
            case 2:
                strcpy(questionario->participante, "Estudante");
                break;
            case 3:
                strcpy(questionario->participante, "Funcionario");
                break;
            case 4:
                strcpy(questionario->participante, "Investigador");
                break;
            default:
                printf("Indique um Tipo de Participante valido!!\n");
                break;
        }
}

// Função - Esteve em contacto com uma pessoa que tem covid
void covid_contacto(QUESTIONARIO_T *questionario){

char op_contacto_covid;
    
    do{
        op_contacto_covid=menu_covid();
        switch (op_contacto_covid) {
            case 'S':
                strcpy(questionario->contacto_covid,"Sim");
                break;
            case 'N':
                strcpy(questionario->contacto_covid,"Nao");
                break;
            case 'D':
                strcpy(questionario->contacto_covid,"Desconhecido");
                break;
            case 'C':
               
            default:
                printf("Indique se esteve em contacto com uma pessoa com covid!!\n");
                break;
        }
    }while(op_contacto_covid != 'C');
}

//Função - Seleção de Doenças
void doencas(QUESTIONARIO_T *questionario){
    for (int i = 0 ; i< 8; i++){
        questionario->doencas[i] = malloc( 8 * sizeof(char));
    }
char op_doencas;
   do{
        op_doencas=menu_opcoes();
        switch (op_doencas) {
            case 1: strcpy(questionario->doencas[0],"Autoimune");
                break;
            case 2: strcpy(questionario->doencas[1],"Cancro");
                break;
            case 3: strcpy(questionario->doencas[2],"Cardiovascular");
            break;
            case 4: strcpy(questionario->doencas[3],"Diabetes");
                break;
            case 5: strcpy(questionario->doencas[4],"Hipertensao");
                break;
            case 6: strcpy(questionario->doencas[5],"Obesidade");
                break;
            case 7: strcpy(questionario->doencas[6],"Renal");
                break;
            case 8: strcpy(questionario->doencas[7],"Respiratoria");
                break;
                }
    }while(op_doencas !=0); }

//funcao  Selecionar Sintomas
void sintomas(QUESTIONARIO_T *questionario){
    for (int i = 0 ; i< 8; i++){
        questionario->sintomas[i] = malloc( 7 * sizeof(char));
    }
char op_sintomas;
   do{
        op_sintomas=menu_sintomas();
        switch (op_sintomas) {
            case 1: strcpy(questionario->sintomas[0],"Dificuldades Respiratorias");
                break;
            case 2: strcpy(questionario->sintomas[1],"Dor Muscular");
                break;
            case 3: strcpy(questionario->sintomas[2],"Fadiga");
            break;
            case 4: strcpy(questionario->sintomas[3],"Falta de paladar");
                break;
            case 5: strcpy(questionario->sintomas[4],"Nauseas");
                break;
            case 6: strcpy(questionario->sintomas[5],"Febre");
                break;
            case 7: strcpy(questionario->sintomas[6],"Tosse");
                break;
                }
    }while(op_sintomas !=0);
}

// Função condição verificar contágio
void verifica_contagio(QUESTIONARIO_T *questionario){
    
    if (questionario->temperatura <= 36.5 && strcmp ("Nao",questionario->contacto_covid) == 0)
       {
           strcpy(questionario->risco,"Baixo");
           printf("\n %s",questionario->risco);
       }else

       if (questionario->temperatura >=36.5 && questionario->temperatura <38.0 && strcmp ("Sim",questionario->contacto_covid) == 0)
       {
           strcpy(questionario->risco,"medio");
           printf("\n %s",questionario->risco);
       }else

       if (questionario->temperatura >=38 &&  strcmp ("Sim",questionario->contacto_covid) == 0)
       {
           strcpy(questionario->risco,"Alto");
           printf("\n %s",questionario->risco);
       }
}

// Funções de Leitura


//Função Ler Escola (cada uma)
int ler_escolas(ESCOLA_T escola[], int num_escolas)
{
    int escolas;
    if (num_escolas==0){
        printf("Adicione uma escola!!\n\n");
        return 0;
    }else{
    printf("Indique que escola frequenta?\n\n");
    mostrar_escolas(escola, num_escolas);
        escolas=ler_inteiro("Número Identificador: \n",1,num_escolas);
    return escolas;
    }
}
//Função Ler Número
int ler_inteiro(char texto[], int min, int max) {
    int num;

    do {
        printf("%s", texto);
        fflush(stdin);
        scanf("%d", &num);
        if (num < min || num > max) {
            printf("Numero invalido.\n");
        }
    } while (num < min || num > max);
    return num;
}

//Função lê Temperatura
float ler_temperatura(char texto[]) {
    float num;
    do {
        printf("%s", texto);
        fflush(stdin);
        scanf("%f", &num);
        if (num < 35 || num >42 ) {
            printf("Insira uma temperatura entre 35º e 42º.\n");
        }
    } while (num < 35 || num >42);
    return num;
}

// Função Lê escolas introduzidas
ESCOLA_T ler_escola(int num_escolas) {
    ESCOLA_T escola;
    escola.identificador = num_escolas +1;
    ler_string("Nome da escola: ", escola.nome, MAX_NOME);
    ler_string("Nome da localidade: ",escola.localidade, MAX_NOME);
    return escola;
}

// Função Lê strings
void ler_string(char texto[], char str[], int max) {
    printf("%s", texto);
    fflush(stdin);
    fgets(str, max, stdin);
    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

//Função Lê questionarios
QUESTIONARIO_T ler_questionario(int num_questionarios, int escola) {

    QUESTIONARIO_T questionario;
    questionario.escola.identificador=escola;
    questionario.data=ler_data();
    questionario.idade=ler_idade("Idade:");
    selecionar_genero(&questionario);
    selecionar_tipo(&questionario);
    covid_contacto(&questionario);
    doencas(&questionario);
    sintomas(&questionario);
    questionario.temperatura=ler_temperatura("Temperatura:");
    verifica_contagio(&questionario);
    
    return questionario;
}

// função Lê a data introduzida pelo utilizador
DATA_T ler_data(void) {
    DATA_T data;
    data.ano = ler_inteiro("Ano:\n ", 2020,2021);
    data.mes=ler_inteiro("Mês:\n ", 1,12);
    data.dia=ler_inteiro("Dia:\n",1,31);
    data.hora.hora=ler_inteiro("Hora:\n",0,24);
    data.hora.minutos=ler_inteiro("Minutos:\n",0,59);
    
    return data;
}

//Lê(Valida) a  idade

int ler_idade(char texto[]) {
    int num;
    do {
        printf("%s", texto);
        fflush(stdin);
        scanf("%d", &num);
        if (num < 18 ) {
            printf("Menor de 18 anos.\n");
        }
    } while (num < 18);
    return num;
}


//Registos

//Regista escolas
int registar_escolas(ESCOLA_T escolas[], int num_escolas) {
    ESCOLA_T escola;
    if (num_escolas >= MAX_ESCOLAS) {
        printf("Numero maximo de escolas atingido.\n");
        return 0;
    }
    escola = ler_escola(num_escolas);
    escolas[num_escolas] = escola;
    return 1;
}

//Regista questionarios
int registar_questionario(QUESTIONARIO_T questionarios[],int num_escolas, int num_questionarios,int escola) {
    QUESTIONARIO_T questionario;
    if (num_questionarios >= MAX_QUESTIONARIOS) {
        printf("Numero maximo de questionarios atingido.\n");
        return 0;
    }
    questionario = ler_questionario(num_questionarios,escola);
    questionarios[num_questionarios] = questionario;
    return 1;
}

//conta questionarios
void conta_questionarios(QUESTIONARIO_T questionario[], int num_questionarios) {
    int i;

    for (i = 0; i < num_questionarios; i++) {
    }
    questionario->identificador_q=num_questionarios;
    printf("Numero Questionarios Respondidos: %d \n",questionario->identificador_q);
}

// Mostra ao utilizador


//Estatisticas Genero
void mostrar_estatisticas_genero (ESCOLA_T escola[],QUESTIONARIO_T questionario[], int num_questionarios,int estatisticas[])
{
    int num_f=0 , num_m=0 , i=0;
    for(i=0;i<num_questionarios;i++)
    {
        if(strcmp(questionario[i].genero,"Masculino")==0)
            estatisticas[0]=num_m++;
        else
            num_f++;
    }
    mostrar_estatisticas_genero_part2(estatisticas,num_questionarios);
}
//Estatisticas Genero Part 2
void mostrar_estatisticas_genero_part2(int estatisticas_array[],int num_questionarios)
{
    printf("Total Questionarios respondidos do genero Masculino: %d \n",estatisticas_array[0]);
    printf("Total Questionarios respondidos do genero Feminino %d \n",estatisticas_array[1]);
}

// Escolas
void mostrar_escola(ESCOLA_T escola) {
    printf("Numero do identificador da escola: %d\n", escola.identificador);
    printf("Nome da Escola: %s\n", escola.nome);
    printf("Localidade: %s\n", escola.localidade);
}
// Escolas + Escolas
void mostrar_escolas(ESCOLA_T escolas[], int num_escolas) {
    int i;

    for (i = 0; i < num_escolas; i++) {
        mostrar_escola(escolas[i]);
        printf("\n");
    }
}

// Questionarios
void mostrar_questionario(QUESTIONARIO_T questionario) {
    
    printf("Escola: %s",questionario.escola.nome);
    printf("Data/Hora: %d-%d-%d %d:%d \n",questionario.data.ano,questionario.data.mes,questionario.data.dia,questionario.data.hora.hora,questionario.data.hora.minutos);
    printf("Idade: %d\n",questionario.idade);
    printf("Genero: %s\n",questionario.genero);
    printf("Tipo de Participante: %s\n",questionario.participante);
    printf("Esteve em contacto com uma pessoa com covid?: %s\n",questionario.contacto_covid);
    mostrar_doencas(questionario.doencas);
    mostrar_sintomas(questionario.sintomas);
    printf("Temperatura: %.2f\n",questionario.temperatura);
    printf("Risco: %s\n",questionario.risco);

//Questionarios + Questionarios
}
void mostrar_questionarios(QUESTIONARIO_T questionario[], int num_questionarios) {
    int i;

    for (i = 0; i < num_questionarios; i++) {
        mostrar_questionario(questionario[i]);
        printf("\n");
    }
}
//Questionarios por genero
void mostrar_questionarios_genero(QUESTIONARIO_T questionario[], int num_questionarios) {
    
    int i,op_porgenero;
   
    op_porgenero=menu_pesquisar_genero();
    switch (op_porgenero) {
        case 1:
                for (i = 0; i < num_questionarios; i++) {
                    if(strcmp ("Feminino",questionario->genero))
                    {
                    mostrar_questionario(questionario[i]);
                    printf("\n");
                    }
                }
            break;
        case 2:
            for (i = 0; i < num_questionarios; i++) {
                if(strcmp ("Masculino",questionario->genero))
                {
                mostrar_questionario(questionario[i]);
                printf("\n");
                }
            }
    }
}

//Doencas
void mostrar_doencas(char* doencas[]) {
int i=0;
  for (i=0; i < 8; i++) {
      if(strlen(doencas[i])==0){
          
      }
      else{
          printf("Doenças: %s \n", doencas[i]);
      }
  }
}

//Sintomas
void mostrar_sintomas(char* sintomas[]) {
int i=0;
  for (i=0; i < 7; i++) {
      if(strlen(sintomas[i])==0){
          
      }
      else{
          printf("Sintomas: %s \n", sintomas[i]);
      }
  }
}

//GRAVA QUESTIONARIO
void gravar_forms(QUESTIONARIO_T questionario[], int num_questionario){
    ssize_t dataquestionario;
    //1. Abrir ficheiro
    FILE *fich = fopen(FILE_FORM, "wb");
    if (fich == NULL){
        printf("Erro ao abrir o ficheiro para escrita. \n");
    } else {
        //2. ESCREVER (OU LER) PARA FICHEIRO
        dataquestionario = fwrite(&num_questionario, sizeof(int),1, fich);
        if (dataquestionario !=1 ){
            printf("Erro ao escrever para ficheiro. \n");
            } else {
            dataquestionario = fwrite(questionario, sizeof (QUESTIONARIO_T),  num_questionario, fich);
            }
                if ( dataquestionario !=num_questionario){
                printf("Erro ao escrever para ficheiro. \n");
                }
        }
    //3. FECHAR O FICHEIRO
    fclose(fich);
}

//GRAVA ESCOLAS
void gravar_schools(ESCOLA_T  escolas[], int num_escolas){
    ssize_t iswritten;
    FILE *fich = fopen(FILE_FORM, "wb");
    if (fich == NULL){
        printf("Erro ao abrir o ficheiro para escrita. \n");
    } else {
        iswritten = fwrite(&num_escolas, sizeof(int),1, fich);
        if (iswritten !=1){
            printf("Erro ao escrever para ficheiro. \n");
            } else {
            iswritten = fwrite(escolas, sizeof (ESCOLA_T),  num_escolas, fich);
            }
                if (iswritten != num_escolas){
                printf("Erro ao escrever para ficheiro. \n");
                }
        }
    fclose(fich);
}

//LER ESCOLAS DO FICHEIRO
int ler_schools(ESCOLA_T escolas[]) {
    int num=0;
    FILE *fich = fopen(FILE_FORM,"rb");
    if (fich == NULL){
        printf("Erro ao abrir o ficheiro para leitura.\n");
    } else {
        fread(&num, sizeof(int), 1, fich);
        fread(escolas,sizeof(ESCOLA_T),num, fich);
        fclose(fich);
    }
    return num;
    
}
//LER FORMULARIOS DO FICHEIRO
int ler_forms( QUESTIONARIO_T questionario[]) {
    int num=0;
    
    FILE *fich = fopen(FILE_FORM,"rb");
    if (fich == NULL){
        printf("Erro ao abrir o ficheiro para leitura.\n");
    } else {
        fread(&num, sizeof(int), 1, fich);
        fread(questionario,sizeof(QUESTIONARIO_T),num,fich);
        fclose(fich);
    }
    return num;
    
}



