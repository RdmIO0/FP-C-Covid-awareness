//
//  main.c
//  Projeto
//
//  Created by Artem Alekseev on 05/01/2021.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_NOME 50
#define MAX_ESCOLAS 5
#define MAX_QUESTIONARIOS 1000
//RAFAEL TENTATIVA DE SAVE
#define FILE_FORM "DATA.bin"

// Estrutura Escola
typedef struct escola {
    int identificador;
    char nome[50];
    char localidade[50];
} ESCOLA_T;

typedef struct hora {
    int hora;
    int minutos;
} HORA_T;

typedef struct data {
    int dia;
    int mes;
    int ano;
    HORA_T hora;
} DATA_T;

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





int ler_inteiro(char texto[], int min, int max);
int menu_opcoesprincipal(void);
int menu_opcoesestatisticas(void);
ESCOLA_T ler_escola(void);
int registar_escolas(ESCOLA_T escolas[], int num_escolas);
void mostrar_escola(ESCOLA_T escola);
void mostrar_escolas(ESCOLA_T escolas[], int num_escolas);
void ler_string(char texto[], char str[], int max);
int registar_questionario(QUESTIONARIO_T questionarios[], int num_questionarios);
QUESTIONARIO_T ler_questionario(void);
DATA_T ler_data(void);
void mostrar_questionario(QUESTIONARIO_T questionario);
void mostrar_questionarios(QUESTIONARIO_T questionario[],int num_questionarios);
int ler_idade(char texto[]);
void selecionar_genero(QUESTIONARIO_T *questionario);
void covid_contacto(QUESTIONARIO_T *questionario);
void doencas(QUESTIONARIO_T *questionario);
float ler_temperatura(char texto[]);
void mostrar_doencas(char* doencas[]);
//teste
char verifica_contagio (QUESTIONARIO_T questionario);
//conta questionarios
void conta_questionarios(QUESTIONARIO_T questionario[], int num_questionarios);
//pesquisa questionarios por genero ( menu + funçao)
int menu_pesquisar_genero(void);
void mostrar_questionarios_genero(QUESTIONARIO_T questionario[], int num_questionarios);
void selecionar_tipo(QUESTIONARIO_T *questionario);
//selecionar sintomas que apresenta
void sintomas(QUESTIONARIO_T *questionario);
void mostrar_sintomas(char* sintomas[]);
//menu Selecionar a escola onde e feito o questionario
char menu_escolas(ESCOLA_T escolas[]);

//RAFAEL TENTIVA DE FICHEIRO

void gravar_forms(QUESTIONARIO_T questionario[], int num_questionarios);
int ler_forms(QUESTIONARIO_T questionario[]);

void gravar_schools(ESCOLA_T escola[], int num_escolas);
int ler_schools(ESCOLA_T escola[]);

int main() {
    ESCOLA_T escolas[MAX_ESCOLAS];
    QUESTIONARIO_T questionario[MAX_QUESTIONARIOS];
    int num_escolas = 0;
    int num_questionarios=0;
    int op,op1;
    
    
    
    do {
        op = menu_opcoesprincipal();
        switch (op) {
        case 1:
                num_escolas += registar_escolas(escolas, num_escolas);
            break;

        case 2:
                mostrar_escolas(escolas, num_escolas);
            break;

        case 3:
                num_questionarios += registar_questionario(questionario, num_questionarios);
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
                            
                        break;

                    case 3:
                            mostrar_questionarios_genero(questionario,num_questionarios);
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
    


int menu_opcoesprincipal(void) {
    int op;

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
    op = ler_inteiro("Opcao: ", 0, 9);
    return op;
}

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

int registar_escolas(ESCOLA_T escolas[], int num_escolas) {
    ESCOLA_T escola;
    if (num_escolas >= MAX_ESCOLAS) {
        printf("Numero maximo de escolas atingido.\n");
        return 0;
    }
    escola = ler_escola();
    escolas[num_escolas] = escola;
    return 1;
}
ESCOLA_T ler_escola(void) {
    ESCOLA_T escola;
    escola.identificador = ler_inteiro("Identificador da escola: ", 1, 5);
    ler_string("Nome da escola: ", escola.nome, MAX_NOME);
    ler_string("Nome da localidade: ",escola.localidade, MAX_NOME);
    return escola;
}
void ler_string(char texto[], char str[], int max) {
    printf("%s", texto);
    fflush(stdin);
    fgets(str, max, stdin);
    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}



void mostrar_escola(ESCOLA_T escola) {
    printf("Numero do identificador da escola: %d\n", escola.identificador);
    printf("Nome da Escola: %s\n", escola.nome);
    printf("Localidade: %s\n", escola.localidade);
}
void mostrar_escolas(ESCOLA_T escolas[], int num_escolas) {
    int i;

    for (i = 0; i < num_escolas; i++) {
        mostrar_escola(escolas[i]);
        printf("\n");
    }
}
// menu escola onde é feito o questionario
char menu_escolas(ESCOLA_T escola[]) {
    int op_tipo;

    printf("* Selecione a sua Escola *\n");
    printf("1 - %s\n",escola[0].nome);
    printf("2 - %s\n",escola[1].nome);
    printf("3 - %s\n",escola[2].nome);
    printf("4 - %s\n",escola[3].nome);
    printf("5 - %s\n",escola[4].nome);
    printf("0 - Sair\n");
    op_tipo = ler_inteiro("Opcao: ", 0, 5);
    return op_tipo;
}


int registar_questionario(QUESTIONARIO_T questionarios[], int num_questionarios) {
    QUESTIONARIO_T questionario;
    if (num_questionarios >= MAX_QUESTIONARIOS) {
        printf("Numero maximo de questionarios atingido.\n");
        return 0;
    }
    questionario = ler_questionario();
    questionarios[num_questionarios] = questionario;
    return 1;
}
QUESTIONARIO_T ler_questionario(void) {

    QUESTIONARIO_T questionario;
    
    questionario.data=ler_data();
    questionario.idade=ler_idade("Idade:");
    selecionar_genero(&questionario);
    selecionar_tipo(&questionario);
    covid_contacto(&questionario);
    doencas(&questionario);
    sintomas(&questionario);
    questionario.temperatura=ler_temperatura("Temperatura:");
    verifica_contagio(questionario);
    
    return questionario;
}

void mostrar_questionario(QUESTIONARIO_T questionario) {
    printf("Data/Hora: %d-%d-%d %d:%d \n",questionario.data.ano,questionario.data.mes,questionario.data.dia,questionario.data.hora.hora,questionario.data.hora.minutos);
    printf("Idade: %d\n",questionario.idade);
    printf("Genero: %s\n",questionario.genero);
    printf("Tipo de Participante: %s\n",questionario.participante);
    printf("Esteve em contacto com uma pessoa com covid?: %s\n",questionario.contacto_covid);
    mostrar_doencas(questionario.doencas);
    mostrar_sintomas(questionario.sintomas);
    printf("Temperatura: %.2f\n",questionario.temperatura);
    printf("Risco: %s\n",questionario.risco);
    
    
}
void mostrar_questionarios(QUESTIONARIO_T questionario[], int num_questionarios) {
    int i;

    for (i = 0; i < num_questionarios; i++) {
        mostrar_questionario(questionario[i]);
        printf("\n");
    }
}
//conta questionarios
void conta_questionarios(QUESTIONARIO_T questionario[], int num_questionarios) {
    int i;

    for (i = 0; i < num_questionarios; i++) {
    }
    questionario->identificador_q=num_questionarios;
    printf("Numero Questionarios Respondidos: %d \n",questionario->identificador_q);
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

int menu_pesquisar_genero(void) {
    int op_tipo;

    printf("* Total de Inqueritos por Genero*\n");
    printf("1 - Feminino\n");
    printf("2 - Masculino\n");
    printf("0 - Sair\n");
    op_tipo = ler_inteiro("Opcao: ", 0, 2);
    return op_tipo;
}
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

// Funcao Case - Esteve em contacto com uma pessoa que tem covid
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
//funcao Sintomas
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
//*validar contagio
//estatistica_contagio(QUESTIONARIO_T questionario ){
//     char *contagio[6];
  //   if (questionario.temperatura >=38.0 && strcmp("sim", questionario.contacto_covid)){
    //    *contagio = "alto";
    //      strcpy(questionario.contacto_covid, *contagio);
     //   printf("\n %s", questionario.contacto_covid);
   //	        }
//

char verifica_contagio(QUESTIONARIO_T questionario){
    char *nivel_contagio[6];
    
    if (questionario.temperatura <= 36.5 && strcmp ("Nao",questionario.contacto_covid))
    {
        *nivel_contagio="Baixo";
        strcpy(questionario.risco,*nivel_contagio);
        printf("\n %s",questionario.risco);

    }
    return *questionario.risco;
}



//Validadar idade

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

// Funcao Case - Selecionar genero
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



