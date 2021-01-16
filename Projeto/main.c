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
    ESCOLA_T escola;
    DATA_T data;
    char risco_c [20];
    int idade;
    char genero [50];
    char localidade[50];
    char participante [30];
    char contacto_covid [10];
    char sintomas [100];
    char doencas [100];
    int temperatura;
    
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

void selecionar_tipo(QUESTIONARIO_T *questionario);
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
                        
                        break;

                    case 2:
                            
                        break;

                    case 3:
                            
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
    printf("6 - Guardar ficheiro\n");
    printf("7 - Ler ficheiros guardados\n");
    printf("0 - Sair\n");
    op = ler_inteiro("Opcao: ", 0, 7);
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
    questionario.identificador_q= ler_inteiro("Identificador do Questionario: ", 1, 250);
    questionario.idade=ler_idade("Idade:");
    selecionar_genero(&questionario);
    selecionar_tipo(&questionario);

    return questionario;
}

void mostrar_questionario(QUESTIONARIO_T questionario) {
    printf("Escola: %s\n", questionario.escola.nome);
    printf("Data/Hora: %d-%d-%d %d:%d \n",questionario.data.ano,questionario.data.mes,questionario.data.dia,questionario.data.hora.hora,questionario.data.hora.minutos);
    printf("Numero do identificador do questionario: %d\n", questionario.identificador_q);
    printf("Idade: %d\n",questionario.idade);
    printf("Genero: %s\n",questionario.genero);
    printf("Tipo de Participante: %s\n",questionario.participante);
    
    
    
}
void mostrar_questionarios(QUESTIONARIO_T questionario[], int num_questionarios) {
    int i;

    for (i = 0; i < num_questionarios; i++) {
        mostrar_questionario(questionario[i]);
        printf("\n");
    }
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
    
    printf("(S)im \n");
    printf("(N)ao\n");
    printf("(D)esconhecido\n");
    printf("(S)air\n");
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
    printf("6 - Renal\n");
    printf("6 - Respiratoria\n");
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
    
        op_genero1=menu_genero();
        switch (op_genero1) {
            case 'F':
            case 'f':
                strcpy(questionario->genero,"Feminino");
                
                break;
            case 'm':
            case 'M':
                strcpy(questionario->genero,"Masculino");
                break;
            default:
                printf("Indique um genero válido!!\n");
                break;
        }
}


//GRAVA QUESTIONARIO
void gravar_forms(QUESTIONARIO_T questionario[], int num_questionario){
    ssize_t dataquestionario;
    //1. Abrir ficheiro
    FILE *fich = fopen(FILE_FORM, "w1b");
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
    FILE *fich = fopen(FILE_FORM, "w1b");
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

//LE ESCOLAS DO FICHEIRO
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
//LE FORMULARIOS DO FICHEIRO
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



