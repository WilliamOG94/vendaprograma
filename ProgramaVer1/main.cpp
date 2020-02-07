#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include <mysql.h>
#include <winsock2.h>
#include <string.h>
#define servidor "localhost"
#define usuario "root"
#define senha ""
#define bd "estoque"
#include<string>
#include <stdlib.h>
#include <cctype>
#include <cstring>
#include <cstdio>

//Identifica as cores do sistema
/*             0     1    2     3   4      5     6       7         8      */
typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,
LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;
/* 9         10        11        12        13          14    15          */
//declara as cores plano de fundo e o contorno da linha
static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;

void textcolor (int letra, int fundo)
{//Para mudar a cor de fundo do sistema ou a letra
    __FOREGROUND = letra;//cor da Letra
    __BACKGROUND = fundo;//cor do Fundo
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letra + (__BACKGROUND << 4));
}
void gotoxy(int x,int y)
{//Permite se movimentar por localização utilizado junto com o teclado (kbit)
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void cadastrar_Cliente()
    {//Cadastro de clientes no banco de dados MySqL

    textcolor(0,15);/* primeiro cor letra segundo cor fundo */
    MYSQL conexao;
    MYSQL_RES *resp;
    MYSQL_ROW linhas;
    MYSQL_FIELD *campos;
    char comando[         500] = "INSERT INTO cliente(nome_Cliente) VALUES ('";
    char comando_Pesquisa[500] = "SELECT \""                                  ;
    char nome_c[          100]= ""                                            ;
    char zera_Nome[       100]= ""                                            ;
    int i                     = 0                                             ;
    printf("Entre com o nome do cliente\n");
    strupr(gets(nome_c));//Usando gets para armazenazar espaços ou seja nome e sobrenome
        while( i < strlen(nome_c))
            {
                i++;
                    if(isdigit(nome_c[i]))
                    {
                        printf("DIGITE UM NOME SEM NUMEROS\n");
                        strcpy(nome_c,zera_Nome);
                        getch();
                    }
            }

    //strcat(comando_Pesquisa,nome_c);//strcat usado para concatenar frases no querry do mysql
    //strcat(comando_Pesquisa,"\" FROM cliente WHERE nome_Cliente = \"");
    //strcat(comando_Pesquisa,nome_c);
    //strcat(comando_Pesquisa,"\";");

    strcat(comando,nome_c);
    strcat(comando,"');");




    mysql_init(&conexao);//Testa conexção
        if ( mysql_real_connect(&conexao, servidor, usuario, senha, bd,0,NULL,0) )//se conectar
        {

            if (mysql_query(&conexao,comando))//Se Retornar ERRO faça
            {
                printf("NOME JÁ CADASTRADO OU CADASTRO CONTEM NUMERO");
                printf("\n");
                //printf(comando);
                getch();
            }

              // PASSADO PELOS TRATAMENTOS TUDO OK AGORA LANÇA NO BANCO DE DADOS
              //Se nao retornar erro ;
        else
            {
            //mysql_query(&conexao,comando);
            printf("Cadastro EFETUADO");
            getch();
            }
        }
    }


void cadastrar_Produto(){
    textcolor(0,15);

    MYSQL conexao;
    char comando[500] = "INSERT INTO produto(nome_Produto, quantidade_Produto) values('";
    char nome_p[100] = "";
    char quant_p[100]="";
    char erroJaCadast[25]="NOME JA CADASTRADO \n";
    int i = 0;
    char zera_Comando[100]="";
    printf("Entre com o nome do produto\n");
    strupr(gets(nome_p));
    printf("Entre com a quantidade\n");
    gets(quant_p);


    strcat(comando, nome_p);
    strcat(comando, "','");
    strcat(comando, quant_p);
    strcat(comando, "');");

    mysql_init(&conexao);
    if ( mysql_real_connect(&conexao, servidor, usuario, senha, bd,0,NULL,0) )
    {
        for (i=0;i < strlen(quant_p); i++){

                if ( ! isdigit(quant_p[i]))
                    {
                    printf("ERRO ENCONTRADO: DIGITE QUANTIDADE COM APENAS NUMEROS \n ");
                    strcpy(comando,zera_Comando);
                    strcpy(erroJaCadast,zera_Comando);
                    getch();
                    break;
                    }
        }

        for (i=0;i < strlen(nome_p); i++){

                if ( isdigit(nome_p[i]))
                    {
                    printf("ERRO ENCONTRADO: DIGITE APENAS LETRAS NO NOME \n ");
                    strcpy(comando,zera_Comando);
                    strcpy(erroJaCadast,zera_Comando);
                    getch();
                    break;
                    }
        }

                if ( (mysql_query(&conexao,comando)))//Se Retornar ERRO faça
                    {
                printf(erroJaCadast);
                printf("\n");
                //printf(comando);
                getch();
                    }



              // PASSADO PELOS TRATAMENTOS TUDO OK AGORA LANÇA NO BANCO DE DADOS
              //Se nao retornar erro ;
            else
            {
            //mysql_query(&conexao,comando);
            printf("Cadastro EFETUADO");
            getch();
            }
            getch();
    }
}



void listar_Produto(){
    textcolor(0,15);
    printf("| Nome | Quantidade |");

   MYSQL conexao;
   MYSQL_RES *resp;
   MYSQL_ROW linhas;
   MYSQL_FIELD *campos;
   char query[]="SELECT nome_Produto, quantidade_Produto FROM produto;";
   int conta; //Contador comum

   mysql_init(&conexao);
   if (mysql_real_connect(&conexao,servidor, usuario, senha, bd,0,NULL,0))
   {
      printf("                                   Conectado com Sucesso!\n");
      if (mysql_query(&conexao,query))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
         resp = mysql_store_result(&conexao);//recebe a consulta
        if (resp) //se houver consulta
        {

            //enquanto retonrnar registros, conta até o
              //número de colunas que a tabela tem e escreve na
              //tela com um tab, depois pula a linha e tenta
              //pegar outro registro
              while ((linhas=mysql_fetch_row(resp)) != NULL)
              {
                 for (conta=0;conta<mysql_num_fields(resp);conta++)

                    printf("%s\t",linhas[conta]);
                 printf("\n");
              }
          }
          mysql_free_result(resp);//limpa a variável do resultado: resp
        }
        mysql_close(&conexao);
   }
   else
   {
      printf("Conexao Falhou\n");
      if (mysql_errno(&conexao))
         printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
   }
   printf("\n");
    printf("Aperte qual quer tecla para voltar ao MENU");
    getch();
}



void listar_Cliente(){
    textcolor(0,15);
    printf("| Clientes |");

       MYSQL conexao;
   MYSQL_RES *resp;
   MYSQL_ROW linhas;
   MYSQL_FIELD *campos;
   char query[]="SELECT nome_Cliente FROM cliente;";
   int conta; //Contador comum

   mysql_init(&conexao);
   if (mysql_real_connect(&conexao,servidor, usuario, senha, bd,0,NULL,0))
   {
      printf("                                   Conectado com Sucesso!\n");
      if (mysql_query(&conexao,query))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
         resp = mysql_store_result(&conexao);//recebe a consulta
        if (resp) //se houver consulta
        {

            //enquanto retonrnar registros, conta até o
              //número de colunas que a tabela tem e escreve na
              //tela com um tab, depois pula a linha e tenta
              //pegar outro registro
              while ((linhas=mysql_fetch_row(resp)) != NULL)
              {
                 for (conta=0;conta<mysql_num_fields(resp);conta++)

                    printf("%s\t",linhas[conta]);
                 printf("\n");
              }
          }
          mysql_free_result(resp);//limpa a variável do resultado: resp
        }
        mysql_close(&conexao);
   }
   else
   {
      printf("Conexao Falhou\n");
      if (mysql_errno(&conexao))
         printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
   }
   printf("\n");
    printf("Aperte qual quer tecla para voltar ao MENU");






    getch();
}



void menu_Vendas(){
    textcolor(0,15);
    char nome_c[100]="";
    char nome_p[100]="";
    printf("VENDAS\n");
    printf("Entre com o nome do Cliente\n");
    gets(nome_c);
    printf("| Codigo |     |   Cliente   |");

    MYSQL conexao;
   MYSQL_RES *resp;
   MYSQL_ROW linhas;
   MYSQL_FIELD *campos;
   char query[500]="SELECT * FROM cliente WHERE nome_Cliente LIKE ";
   int conta; //Contador comum

   strcat(query, "'%");
   strcat(query, nome_c);
   strcat(query, "%'");

   mysql_init(&conexao);
   if (mysql_real_connect(&conexao,servidor, usuario, senha, bd,0,NULL,0))
   {
    printf("                                   Conectado com Sucesso!\n");
      if (mysql_query(&conexao,query))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
         resp = mysql_store_result(&conexao);//recebe a consulta
        if (resp) //se houver consulta
        {
        while ((linhas=mysql_fetch_row(resp))!= NULL)
              {
                 for (conta=0;conta<mysql_num_fields(resp);conta++)

                    printf("   %s    \t",linhas[conta]);
                    printf("\n");

                }
             if (mysql_num_rows(resp) == 0) {
              printf( "Cliente nao cadastrado, CUIDADO COM O CAPSLOCK");
                }
            }
        }
    }


        mysql_init(&conexao);
   if (mysql_real_connect(&conexao,servidor, usuario, senha, bd,0,NULL,0))
   {
                printf("Digite o Nome do Produto\n");
                gets(nome_p);
                char query_Produto[500]="SELECT * FROM `produto` WHERE `nome_Produto` LIKE ";
                printf("| Codigo | Nome | Quantidade\n");
        strcat(query_Produto, "'%");
        strcat(query_Produto, nome_p);
        strcat(query_Produto, "%'");

      if (mysql_query(&conexao,query_Produto))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
         resp = mysql_store_result(&conexao);//recebe a consulta
        if (resp) //se houver consulta
        {
        while ((linhas=mysql_fetch_row(resp))!= NULL)
              {
                 for (conta=0;conta<mysql_num_fields(resp);conta++)

                    printf("  %s   \t",linhas[conta]);
                    printf("\n");
                }
             if (mysql_num_rows(resp) == 0) {
              printf( "PRODUTO NAO CADASTRADO ");
                }
            }
        }













}
printf(nome_c);
printf("\n");
printf(nome_p);
getch();


}



void sair(){
    textcolor(11,3);
    gotoxy(0,20);
    printf("Saindo . . . !    tecle\n\n");
    getch();
    textcolor(7,0);
    exit(0);
}



int main(){

    system("MODE con cols=168 lines=60");
    system("title Programa Vendas");




    int li=1,tecla;
    setlocale(LC_ALL,"");
    do{
        textcolor(9,15);
        system("cls");
        printf("\t\tMENU\n");

        printf("\t1 - CADASTRAR CLIENTE         \n");
        printf("\t2 - CADASTRAR PRODUTO         \n");
        printf("\t3 - LISTAR PRODUTOS           \n");
        printf("\t4 - LISTAR CLIENTES           \n");
        printf("\t5 - VENDAS                    \n");
        printf("\t6 - SAIR                      \n");

        gotoxy(4,li);
        printf("->");
        gotoxy(79,24);
        do{
            tecla=0;
            if(kbhit()){
                tecla = getch();
                gotoxy(4,li);
                printf("  ");
                if(tecla==224)
                    tecla = getch();
                if(tecla == 72)
                    li--;
                else
                    if(tecla == 80)
                        li++;
                if(li > 6)
                    li=1;
                else
                    if(li < 1)
                        li=6;
                gotoxy(4,li);
                printf("->");
                gotoxy(79,24); /* se não quiser que cursor fique piscando ali */
            }
        }while(tecla != 13);
        system("cls");
        switch(li){
        case 1:
            cadastrar_Cliente();
            break;
        case 2:
            cadastrar_Produto();
            break;
        case 3:
            listar_Produto();
            break;
        case 4:
            listar_Cliente();
            break;
        case 5:
            menu_Vendas();
            break;
        case 6:
            sair();
        }
    }while(li != 6);
    textcolor(7,0);
    return 0;
}
