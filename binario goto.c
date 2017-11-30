#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>

//cores do programa
#define PRETO 0
#define AZUL 1
#define VERDE 2
#define VERDE_AGUA 3
#define VERMELHO 4
#define ROXO 5
#define AMARELO 6
#define BRANCO 7
#define CINZA 8
#define AZUL_CLARO 9
#define VERDE_CLARO 10
#define VERDE_AGUA_CLARO 11
#define VERMELHO_CLARO 12
#define LILAS 13
#define AMARELO_CLARO 14
#define BRANCO_BRILHANTE 15

//Estruturas para dados diversos
struct acesso_adm{
	char senha[30];
	char login[40];
};

struct cadastro_cliente{
    char nome_cartao[20];
    char nome_cliente[50];
    char nome_endereco[50];
    char nome_email[30];
    char nome_cidade[20];
    char nome_estado[5];
    int dd;
    unsigned long int cep;
    unsigned long int numero;

};
struct assentos{
    char horario_sala[100];
    char assento[17][37];
};
struct filmes{
	char nome_filme[40];
	char legenda[30];
	int classe_ind;
	int duracao; //duração dos filmes 230min
	char horario[1000];//Horários ex... 17:30h ; 22:10h 23:00 24:00 6:00
	char sala[100];

	struct assentos a;
};

struct venda_dinheiro{
    int qtde;
    char filme[200];
    char hora[30];
    char tipo[30];//inteira,meia, etc;
    char sala;
    char assento[3];
    char tipo_elemento[100];
    float preco;
};

struct ingresso{// Consertar essa funcão
    float ingresso1;
	float ingresso2;
};

struct combo_cinema{
	char nome_combo[20];
	char const_combo[50];
	float valor_combo;
};
struct desconto{
    float desc;
};

struct controle_caixa{
	float dinheiro;
};

//Prototipo das funções do programa
void adm();							//OK
void us();
void venda_dinheiro();
void venda_cartao();
void matriz_assento();
void escolha_assentos(int qtde_ingresso,char lugar[1000],int mat[17][37]);
void controle_vendas();
void caixa_lista();					//OK

void menu_filmes();					//OK
void cadastro_filmes();				//OK
void alterar_filmes();				//OK
void pesquisar_filmes();			//OK
void lista_filmes();				//OK
void excluir_filmes();

void ingresso_menu();				//OK
void ingresso_altmod();
void ingresso_atual();

void menu_combo();
void cadastro_combo();				//OK
void pesquisar_combo();
void lista_combo();
void alterar_combo();
void excluir_combo();

void menu_cliente();
void cadastro_cliente();
void alterar_cadastro();
void pesquisar_cadastro();
void listar_cadastro();
void excluir_cadastro();


void verificar_login();
void adicionar_login();
void excluir_login();
void logar(int x);
void menu();						//OK

void cria_arquivo();
void cria_arquivo2();		    //OK
void controle_caixa();

//Protótipo das funções gráficas
void textcolor(int COLOR);
void gotoxy(int x, int y);
void moldura();
void moldura2(int col_ini, int col_fim, int line_ini, int line_fim, int numero_op);
void desenho();
unsigned char setas;
int x, y;
int letra[17],numero[37];
int m[17][37];

//Arquivos do programa
FILE *cad;
FILE *controle;
FILE *combo;
FILE *ing;
FILE *cliente;
FILE *login;
FILE *rel;

//Função Principal
int main(void){
	system("title CINE AGORA VAI");
	//setlocale(LC_ALL,"portuguese");
	setlocale(LC_CTYPE,"c");
	fflush(stdin);
	cria_arquivo();
	fflush(stdin);
    verificar_login();
}

void cria_arquivo(){
	cad = fopen("cadastro filme.txt","rb");
	if(cad == NULL){
		printf("erro. arquivo corrompido\n");
		cad = fopen("cadastro filme.txt","wb");
	}
	fclose(cad);

	controle = fopen("Controle_diverso.txt","rb");
	if(controle == NULL){
		printf("erro. arquivo corrompido\n");
		controle = fopen("Controle_diverso.txt","wb");
	}
	fclose(controle);

	ing = fopen("Valor ingresso.txt","rb");
	if(controle == NULL){
		printf("erro. arquivo corrompido\n");
		ing = fopen("Valor ingresso.txt","wb");
	}
	fclose(ing);

    cliente = fopen("Cliente_desconto.txt","rb");
	if(cliente == NULL){
        printf("erro. arquivo corrompido\n");
        cliente = fopen("Cliente_desconto.txt","wb");
	}
	fclose(cliente);

	combo = fopen("Arquivo combo.txt","rb");
	if(combo == NULL){
        printf("Erro. arquivo combo corrompido\n");
        combo = fopen("Arquivo combo.txt","wb");
	}
	fclose(combo);

    login = fopen("Arquivo login.txt","rb");
    if(login == NULL){
        printf("Erro. Arquivo login corrompido\n");
        login = fopen("Arquivo login.txt","wb");
    }
    fclose(login);
    rel=fopen("relatorio.txt","rb");
    if(rel == NULL){
        printf("Erro. Arquivo Relatorio corrompido\n");
        rel=fopen("relatorio.txt","wb");
    }
    fclose(rel);
}
void moldura_inicio(){
    int cont, i;
    for(i = 58; i < 113; i++){
        gotoxy(i,15);
        printf("%c",196);
        usleep(1000);
        if(i == 112){
            gotoxy(i,15);
            printf("%c",191);
            usleep(1000);
        }
    }
    for(i = 16; i < 23; i++){
        gotoxy(112,i);
        printf("%c",179);
        usleep(1000);
    }
    for(i = 112; i > 57; i--){
        if(i == 112){
            gotoxy(i,22);
            printf("%c",217);
            usleep(1000);
        }else{
            gotoxy(i,22);
            printf("%c",196);
            usleep(1000);
        }
    }
    for(i = 22; i > 15; i--){
        if(i == 22){
            gotoxy(58,i);
            printf("%c",192);
            usleep(1000);
        }else{
            gotoxy(58,i);
            printf("%c",179);
            usleep(1000);
        }
    }
    gotoxy(58,i);
    printf("%c",218);
    usleep(1000);
}
void verificar_login(){
	struct acesso_adm c;
	int size = 0,i;
	char op;
	login = fopen("Arquivo login.txt","rb");
	if(login == NULL){
		printf("erro no arquivo...");
		main();
	}
	while(fread(&c,sizeof(struct acesso_adm),1,login) == 1){
		size++;
	}
	if(size < 1){
        fclose(login);
        moldura_inicio();
        gotoxy(77,16);
        printf("SEJA BEM-VINDO!!!");
        Sleep(500);
        gotoxy(60,18);
		printf("    O Sistema encontra-se limpo. Cadastre-se como");
        Sleep(500);
        gotoxy(60,19);
        printf("adiminstrador do sistema para manusea-l%c conforme",162);
        Sleep(500);
        gotoxy(60,20);
        Sleep(500);
        printf("a necessidade do seu cinema e suas rotinas di%cri-",160);
        gotoxy(60,21);
        Sleep(500);
        printf("as...");
        fflush(stdin);
		printf("\n");
		op = getchar();
		system("cls");
		adicionar_login();
	}

	fclose(login);
	menu();
}
void adicionar_login(){
    struct acesso_adm c;
	char nome[40];
	char senha[40];
	char senha2[40];
	char op;
	int i, cont = 0;
	int size = 0;

	login = fopen("Arquivo login.txt","rb");
	if(login == NULL){
		printf("erro no arquivo...");
		main();

	}
	while(fread(&c,sizeof(struct acesso_adm),1,login) == 1){
		size++;
	}

    if(size < 1){
        fclose(login);
        login = fopen("Arquivo login.txt","ab");
        if(login == NULL){
            printf("Erro. Arquivo login corrompido\n");
            op = getch();
            fclose(login);
            return;
        }
        volta:
		printf("Adminstrador: ");
		gets(c.login);
		printf("Senha: ");
		cont++;
		i = 0;
		do{
			fflush(stdin);
			op = getch();
			fflush(stdin);
			if(isprint(op) && op != 13 && op != 8 && op!= 127){
				senha[i] = op;
				i++;
				printf("*");
			}else{
				if((op == 8 || op == 10 || op == 127) && i > 0 && i < 11){
					senha[i] = '\0';
					i--;
					printf("\b \b");
				}
			}
		}while(op != 13);
		senha[i] = '\0';
		printf("\nsenha: ");
		i = 0;
		do{
			op = getch();
			fflush(stdin);
			if(isprint(op) && op != 13 && op != 8 && op!= 127){
				senha2[i] = op;
				i++;
				printf("*");
			}else{
				if((op == 8 || op == 10 || op == 127) && i > 0 && i < 11){
					senha2[i] = '\0';
					i--;
					printf("\b \b");
				}
			}
		}while(op != 13);
		senha2[i] = '\0';
		if(strcmp(senha,senha2) == 0){
			printf("\nCadastro realizado com sucesso\n");
			op = getch();
			strcpy(c.senha,senha);
			fwrite(&c,sizeof(struct acesso_adm),1,login);
			fclose(login);
		}else{
			printf("\nDigite um senha valida....\n");
			op = getch();
			goto volta;
		}
	}else{
        login = fopen("Arquivo login.txt","rb");
        if(login == NULL){
            printf("erro no arquivo...");
            main();

        }
		volta2:
        volta3:
        volta4:
		printf("\nLogin: ");
		fflush(stdin);
		gets(nome);
		fflush(stdin);
		while(fread(&c,sizeof(struct acesso_adm),1,login) == 1){
            if(strcmp(c.login,nome) == 0){
                printf("\nUsuario existente\n");
                printf("Deseja cadastra outro usuario?\n");
                printf("Sim - 1\tNao - qualquer tecla\n");
                op = getch();
                if(op == '1'){
                    goto volta2;
                }else{
                    fclose(login);
                    adm();
                }
            }
        }
        fclose(login);
        login = fopen("Arquivo login.txt","ab");
        if(login == NULL){
            printf("Erro no arquivo...\n");
            op = getch();
            main();
        }
		printf("\nsenha: ");
		i = 0;
		do{
			fflush(stdin);
			op = getch();
			fflush(stdin);
			if(isprint(op) && op != 13 && op != 8 && op!= 127){
				senha[i] = op;
				i++;
				printf("*");
			}else{
				if((op == 8 || op == 10 || op == 127) && i > 0 && i < 11){
					senha[i] = '\0';
					i--;
					printf("\b \b");
				}
			}
		}while(op != 13);

		senha[i] = '\0';
		printf("\nsenha: ");
		i = 0;
		do{
			op = getch();
			fflush(stdin);
			if(isprint(op) && op != 13 && op != 8 && op!= 127 && i < 11){
				senha2[i] = op;
				i++;
				printf("*");
			}else{
				if((op == 8 || op == 10 || op == 127) && i > 0){
					senha2[i] = '\0';
					i--;
					printf("\b \b");
				}
			}
		}while(op != 13);
		senha2[i] = '\0';
		if(strcmp(senha,senha2) == 0){
            printf("Voce deseja realmente adicionar esse usuario?\n");
            printf("sim - 1\t nao - qualquer tecla ");
			fflush(stdin);
			op = getch();
			if(op != '1'){
                printf("Usuario cancelado ");
                printf("Deseja cadastra outro usuario?\n");
                printf("Sim - 1\tNao - qualquer tecla\n");
				op = getch();
                if(op == '1'){
                    goto volta3;
                }else{
                    fclose(login);
                    adm();
                }
            }else{
                strcpy(c.login,nome);
                strcpy(c.senha,senha);
                fwrite(&c,sizeof(struct acesso_adm),1,login);
                fclose(login);
                printf("Login cadastrado com sucesso!!!");
                printf("Precione uma tecla para volta ao menu do Adm");
                op = getch();
                adm();
            }
		}else{
			cont++;
			if(cont == 6){
				printf("\nVoce excedeu o numero de tentativas...\n");
				fclose(login);
				op = getch();
				adm();
			}else{
				printf("\nSenha invalida.\nDigite a senha novamente ");
				op = getch();
				goto volta4;
			}
		}
	}
}
void moldurax(){
    int x, y;
    textcolor(5);

    for(x = 65; x < 107; x++){
        gotoxy(x,15);
        printf("%c",254);
        gotoxy(x,20);
        printf("%c",254);
    }
    textcolor(9);
    for(x = 65; x <106; x+=2){
        textcolor(11);
        gotoxy(x,17);
        printf("%c",254);
        gotoxy(x,18);
        printf("%c",254);
    }
    textcolor(5);
    for(y = 15; y < 21; y++){
        gotoxy(65,y);
        printf("%c",254);
        gotoxy(107,y);
        printf("%c",254);
    }
}
void logar(int x){
	struct acesso_adm c;
	char nome[40];
	char senha[40];
	char op;
	int i, cont = 1, cont2 = 1, y;
    volta2:
    system("cls");
	login = fopen("Arquivo login.txt","rb");
	if(login == NULL){
		printf("Erro. Arquivo Login corrompido...\n");
		exit(0);
	}
	moldurax();
	textcolor(11);
    fflush(stdin);
    gotoxy(68,16);
	printf("Login: ");
	gotoxy(68,19);
	fflush(stdin);
	printf("Senha: ");
	gotoxy(76,16);
	textcolor(15);
	gets(nome);
	fflush(stdin);
	gotoxy(76,19);
	i = 0;

	//cont++;
	fflush(stdin);
	do{
		op = getch();
		fflush(stdin);
		if(isprint(op) && op != 13 && op != 8 && op!= 127 && i < 20){
			fflush(stdin);
			senha[i] = op;
			fflush(stdin);
			i++;
			printf("*");
		}else{
			if((op == 8 || op == 10 || op == 127) && i > 0){
				senha[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	}while(op != 13);
	senha[i] = '\0';
    fflush(stdin);
	while(fread(&c,sizeof(struct acesso_adm),1,login) == 1){
		if((strcmp(c.login,nome) == 0)&&(strcmp(c.senha,senha) == 0)){
			if(x == 1 && cont2 == 1){
                gotoxy(68,22);
                printf("ACESSO A OP%c%cO COM SUCESSO!!!\n",128,199);
                op = getch();
                fclose(login);
                adicionar_login();
            }else{
                if(x == 2){
                    fflush(stdin);
                    int z;
                    for(y = 0; y < 10; y++){
                        for(z = 0; z < 16; z++){
                            gotoxy(68,22);
                            textcolor(z);
                            printf("ACESSO AO ADIMINISTRADOR PERMITIDO!!!");
                            usleep(500);
                        }
                    }
                    gotoxy(68,22);
                    textcolor(14);
                    printf("ACESSO AO ADIMINISTRADOR PERMITIDO!!!");
                    Sleep(1000);
                    fclose(login);
                    adm();
                }
			}
        }
        cont2++;
	}
    if(x == 1){
        gotoxy(68,22);
        printf("Somente o administrador principal pode acessar essa opcao");
        op = getch();
        fclose(login);
        adm();
    }else{
        if(cont == 4 && x == 2){
            gotoxy(68,22);
            printf("voce excedeu o numero de tentativas\n");
            op = getch();
            menu();
	    }else{
            if(cont == 4 && x == 1){
                gotoxy(68,22);
                printf("voce excedeu o numero de tentativas\n");
                op = getch();
                menu();
            }else{
                textcolor(13);
                gotoxy(79,22);
                printf("Senha inv%clida\n",160);
                gotoxy(68,23);
                printf("Digite novamente o usu%crio e a senha\n",160);
                op = getch();
                fflush(stdin);
                fclose(login);
                cont++;
                goto volta2;
            }
        }
    }
}
void menu(){
	int y = 21;

	while(1){
		system("cls");
		setlocale(LC_CTYPE,"c");
        moldura();
    	moldura2(73,105,16,26,2);
		desenho();
		fflush(stdin);
        gotoxy(74,21);
        fflush(stdin);
        printf("%c",175);
        fflush(stdin);
		gotoxy(80,17);
		textcolor(15);
        printf("CINEMA AGORA VAI");
		fflush(stdin);
		gotoxy(80,21);
		printf("1 - Administrador");
		gotoxy(80,23);
		printf("2 - Usu%crio",160);
		fflush(stdin);
		gotoxy(80,25);
		printf("0 - Sair");
		fflush(stdin);

		do{
			fflush(stdin);
            setas = getch();
            fflush(stdin);
            if(setas==0x50 && y == 25){
                gotoxy(74,y);
                printf(" ");
                fflush(stdin);
                y=21;
                fflush(stdin);
                gotoxy(74,y);
                fflush(stdin);
                printf("%c", 175);
                continue;
            }
            if(setas==0x48 && y == 21){
                gotoxy(74,y);
                printf(" ");
                y=25;
                gotoxy(74,y);
                printf("%c", 175);
                continue;
            }
            if(setas==0x50 && y<25){
                gotoxy(74,y);
                printf(" ");
                y+=2;
                gotoxy(74,y);
                printf("%c", 175);
                gotoxy(80,23);
            }
            if(setas==0x48 && y>21){
                gotoxy(74,y);
                printf(" ");
                y-=2;
                gotoxy(74,y);
                printf("%c", 175);

            }

        }while(setas!=0xD);
        switch(y){
            case 21: logar(2); break;
            case 23: us(); break;
            case 25: exit(0);
        }
        y = 0;
	}
}

void adm(){
    int y = 16;
	system("cls");
	while(1){
		system("cls");
		moldura();
		moldura2(68,108,11,33,8);
		fflush(stdin);
		gotoxy(69,16);
		fflush(stdin);
		printf("%c",175);
		fflush(stdin);
		gotoxy(78,12);
		fflush(stdin);
		textcolor(15);
		printf("MENU DO ADMINISTRADOR\n\n");
		fflush(stdin);
		gotoxy(75,16);
		fflush(stdin);
		printf("1 - Filmes");
		gotoxy(75,18);
		fflush(stdin);
		printf("2 - Ingresso");
		gotoxy(75,20);
		fflush(stdin);
		printf("3 - Controle de caixa");
		gotoxy(75,22);
		fflush(stdin);
		printf("4 - Combo");
		gotoxy(75,24);
		fflush(stdin);
		printf("5 - Cliente");
		fflush(stdin);
		gotoxy(75,26);
		fflush(stdin);
		printf("6 - Adicionar adiministrador(s)");
		fflush(stdin);
		gotoxy(75,28);
		fflush(stdin);
		printf("7 - Excluir adiminstrador(s)");
		fflush(stdin);
		gotoxy(75,30);
		fflush(stdin);
		printf("8 - Retorna ao menu principal");
		fflush(stdin);
		gotoxy(75,32);
		printf("0 - Sair");
		y = 16;
		do{
            setas = getch();
            fflush(stdin);
            if(setas==0x50 && y == 32){
                gotoxy(69,y);
                fflush(stdin);
                printf(" ");
                fflush(stdin);
                y=16;
                gotoxy(69,y);
                printf("%c", 175);
                fflush(stdin);
                continue;
            }
            if(setas==0x48 && y==16){
                gotoxy(69,y);
                fflush(stdin);
                printf(" ");
                fflush(stdin);
                y=32;
                gotoxy(69,y);
                fflush(stdin);
                printf("%c", 175);
                fflush(stdin);
                continue;
            }
            if(setas==0x50 && y<32){
                gotoxy(69,y);
                printf(" ");
                y+=2;
                gotoxy(69,y);
                printf("%c", 175);
            }
            if(setas==0x48 && y>16){
                gotoxy(69,y);
                printf(" ");
                y-=2;
                gotoxy(69,y);
                printf("%c", 175);
            }
        }while(setas!=0xD);
        switch(y){
            case 16: menu_filmes();break;
            case 18: ingresso_menu();break;
            case 20: controle_vendas();break;
            case 22: menu_combo();break;
            case 24: menu_cliente();break;
            case 26: logar(1);break;
            //case 28: excluir_adm();break;
            case 30: menu();break;
            case 32: exit(0);
        }
    }
}

void menu_filmes(){
	int op, y = 16;
	system("cls");
	while(1){
		system("cls");
		moldura();
		moldura2(68,105,11,29,6);
		gotoxy(69,16);
		printf("%c",175);
		gotoxy(80,12);
		printf(" MENU FILME");
		gotoxy(74,16);
		printf("1 - Cadastrar filmes");
		gotoxy(74,18);
		printf("2 - Alterar filmes");
		gotoxy(74,20);
		printf("3 - Pesquisar filmes");
    	gotoxy(74,22);
		printf("4 - Relat%crio de filmes",162);
		gotoxy(74,24);
		printf("5 - Excluir filmes");
        gotoxy(74,26);
		printf("6 - Retorna ao menu do Adm(a)");
        gotoxy(74,28);
        printf("0 - Sair");
		do{
            setas = getch();
            if(setas==0x50 && y == 28){
                gotoxy(69,y);
                printf(" ");
                y=16;
                gotoxy(69,y);
                printf("%c", 175);
                continue;
            }
            if(setas==0x48 && y==16){
                gotoxy(69,y);
                printf(" ");
                y=28;
                gotoxy(69,y);
                printf("%c", 175);
                continue;
            }
            if(setas==0x50 && y<28){
                gotoxy(69,y);
                printf(" ");
                y+=2;
                gotoxy(69,y);
                printf("%c", 175);
            }
            if(setas==0x48 && y>16){
                gotoxy(69,y);
                printf(" ");
                y-=2;
                gotoxy(69,y);
                printf("%c", 175);
            }
        }while(setas!=0xD);

		switch(y){
        	case 16:cadastro_filmes();break;
			case 18:alterar_filmes();break;
			case 20:pesquisar_filmes();break;
			case 22:lista_filmes();break;
			case 24:excluir_filmes();break;
			case 26:adm();break;
			case 28:exit(0);
		}
	}
}
void cadastro_filmes(){
    int horario_hora;
    int horario_min;
    char doispontos;
    int hora,min,qtde_hora,i;
    char s[1000];
    char s_ass[100];
    char aux[1000];
	char op,nome[40];
	struct filmes c;
	char sala[50],sala2[40];
	int j,sala_verificacao;
	system("cls");
    int x,y;
    cad = fopen("Cadastro filme.txt","rb");
    if(cad == NULL){
        printf("erro no arquivo...\n");
        fclose(cad);
        main();
    }
    gotoxy(40,2);
	printf("Nome do filme: ");
	fflush(stdin);
	gets(nome);

	while(fread(&c,sizeof(struct filmes),1,cad) == 1){
		if(strcmp(c.nome_filme,nome) == 0){
			gotoxy(40,4);
			printf("filme j%c existe",160);
			gotoxy(40,5);
			printf("Deseja cadastrar outro filme?");
			gotoxy(40,6);
			printf("1 - SIM\tQualquer tecla - SAIR\n");
			gotoxy(40,8);
			printf("tDigite: ");
			op = getch();
		    fflush(stdin);
		    if(op == '1'){
		    	fclose(cad);
		    	cadastro_filmes();
			}else{
				fclose(cad);
				return menu_filmes();
			}
		}
	}
    volta20:
    gotoxy(40,3);
	printf("Sala: ");
	scanf("%d",&sala_verificacao);
	sprintf(sala2,"Sala: %d",sala_verificacao);

	while(fread(&c,sizeof(struct filmes),1,cad) == 1){
		if(strcmp(c.sala,sala2) == 0){
            gotoxy(40,5);
			printf("Sala j%c ocupada",160);
            gotoxy(40,6);
			printf("Deseja escolher outra sala?");
			gotoxy(40,7);
			printf("1 - SIM\tQualquer tecla - SAIR");
			gotoxy(40,8);
			printf("Digite: ");
			op = getch();
		    fflush(stdin);
		    if(op == '1'){
		    	fclose(cad);
		    	goto volta20;
			}else{
				fclose(cad);
				gotoxy(40,10);
				printf("Cadastro finalizado...");
				op = getch();
				return menu_filmes();
			}
		}
	}
    fclose(cad);
	cad = fopen("Cadastro filme.txt","ab");
	if(cad == NULL){
        printf("erro no arquivo...");
        op = getch();
        main();
	}
    strcpy(c.sala,sala2);
    strcpy(c.nome_filme,nome);
	setbuf(stdin,NULL);
	gotoxy(40,4);
	printf("Dura%c%co(minutos): ",135,198);
	scanf("%d",&c.duracao);
	fflush(stdin);
	hora=c.duracao/60;
	min=c.duracao%60;
	gotoxy(40,5);
	printf("Legenda: ");
	gets(c.legenda);
	fflush(stdin);
	gotoxy(40,6);
	printf("Clas. Ind: ");
	scanf("%d",&c.classe_ind);
	fflush(stdin);

	//fwrite(&sala,sizeof(sala),1,);
	gotoxy(40,7);
	printf("Quantos hor%crios/sess%ces esse filme ir%c ter: ",160,228,160);
	fflush(stdin);
	scanf("%d",&qtde_hora);
	fflush(stdin);
	gotoxy(40,8);
	printf("Primeiro Hor%crio/Sess%co: ",160,198);
	fflush(stdin);
	scanf("%d %c %d",&horario_hora,&doispontos,&horario_min);
	fflush(stdin);
	for(i=1;i<=qtde_hora;i++){
            if(i==1&&horario_min>9||horario_min>9){
                fflush(stdin);
                sprintf(s,"%d%c%d ",horario_hora,':',horario_min);
                fflush(stdin);
            }else{
                fflush(stdin);
                sprintf(s,"%d%c%c%d ",horario_hora,':','0',horario_min);
                fflush(stdin);
            }
            strcpy(s_ass,s);
            strcpy(c.a.horario_sala,s_ass);
            strcat(aux,s);
            matriz_assento();

            for(x = 0; x < 17;x++){
                for(y = 0; y < 37;y++){
                    c.a.assento[x][y]=m[x][y];
                }
            }
            //fwrite(&c.a,sizeof(struct assentos),17,cad);

            fflush(stdin);
            horario_hora+=hora+1;
            horario_min+=min;
            if(horario_min>=60){
                horario_hora+=horario_min/60;
                horario_min=horario_min%60;
            }
            if(horario_hora>=24)
                break;


    }
    strcpy(c.horario,aux);
    strcpy(aux,"");
    fflush(stdin);
    gotoxy(40,9);
    printf("Sess%ces :",228);
    printf("%s",c.horario);
    fflush(stdin);
	setbuf(stdin,NULL);

	fwrite(&c,sizeof(c),1,cad);

	fflush(stdin);
	setbuf(stdin,NULL);
	gotoxy(40,10);
	printf("Deseja cadastrar outro filme?");
	gotoxy(40,11);
	printf("1 - SIM\tQualquer tecla - SAIR");
	printf("Digite: ");
	op = getch();
    fflush(stdin);


	if(op == '1'){
        system("cls");
        fclose(cad);
		cadastro_filmes();
    }else{
        gotoxy(40,13);
	    printf("Cadastro finalizado");
        system("pause");
        fclose(cad);
        return menu_filmes();
	}
}

void alterar_filmes(){
    system("cls");
    int horario_hora;
    int horario_min;
    char doispontos;
    int hora,min,qtde_hora,i;
    char s[1000];
    char s_ass[100];
    char aux[1000];
	char op,nome[40];
	struct filmes c;
	char sala[50],sala2[40];
	int j,sala_verificacao;
	printf("Entre com o filme que gostaria de alterar: ");
	fflush(stdin);
	gets(nome);
	fflush(stdin);
	cad = fopen("Cadastro filme.txt","rb");
    if(cad == NULL){
        printf("erro no arquivo...\n");
        fclose(cad);
        main();
    }
    while(fread(&c,sizeof(struct filmes),1,cad)==1){
		if(strcmp(c.nome_filme,nome)==0){
            printf("\t-------------------------------------------------------------\n");
            printf("\t\t\t    Nome do filme:%s\n",c.nome_filme);
            printf("\t\t\t    Duração:%d minutos\n",c.duracao);
            printf("\t\t\t    Legenda:%s\n",c.legenda);
            printf("\t\t\t    Classifição Indicativa:%d\n",c.classe_ind);
            printf("\t\t\t    %s\n",c.sala);
            printf("\t\t\t    Horarios/Sessoes :");
            printf("%s\n",c.horario);
            fflush(stdin);
            printf("\t-------------------------------------------------------------\n");

            printf("Tem certeza de que quer alterar esse filme? ");
            printf("\n1-Sim\t\t\tQualquer tecla-Não");
            op=getch();
            fflush(stdin);
            if(op=='1'){
                FILE *aux=fopen("auxiliar.txt","ab");
                rewind(cad);
            while(fread(&c,sizeof(struct filmes),1,cad)==1){
                if(strcmp(nome,c.nome_filme)!=0)
                    fwrite(&c, sizeof(struct filmes), 1, aux);
            }
            fclose(cad);
            fclose(aux);
            remove("Cadastro filme.txt");
            rename("auxiliar.txt","Cadastro filme.txt");
            }
            system("cls");
            printf("\t\t\tNome do filme: ");
            fflush(stdin);
            gets(c.nome_filme);
            printf("\t\t\tDuração(minutos): ");
            scanf("%d",&c.duracao);
            hora=c.duracao/60;
            min=c.duracao%60;
            fflush(stdin);
            printf("\t\t\tLegenda: ");
            gets(c.legenda);
            fflush(stdin);
            printf("\t\t\tClassificação Indicativa: ");
            scanf("%d",&c.classe_ind);
            fflush(stdin);
            printf("\t\t\tSala: ");
            scanf("%d",&c.sala);
            fflush(stdin);
            printf("\t\t\tQuantos horários/sessoes esse filme irá ter: ");
            fflush(stdin);
            scanf("%d",&qtde_hora);
            fflush(stdin);
            printf("\t\t\tPrimeiro Horário/Sessao: ");
            fflush(stdin);
            scanf("%d %c %d",&horario_hora,&doispontos,&horario_min);
            fflush(stdin);
            for(i=1;i<=qtde_hora;i++){
                    if(i==1&&horario_min>9||horario_min>9){
                        fflush(stdin);
                        sprintf(s,"%d%c%d ",horario_hora,':',horario_min);
                        fflush(stdin);
                    }else{
                        fflush(stdin);
                        sprintf(s,"%d%c%c%d ",horario_hora,':','0',horario_min);
                        fflush(stdin);
                    }
                    strcpy(s_ass,s);
                    strcpy(c.a.horario_sala,s_ass);
                    strcat(aux,s);
                    matriz_assento();

                    for(x = 0; x < 17;x++){
                        for(y = 0; y < 37;y++){
                            c.a.assento[x][y]=m[x][y];
                        }
                    }
                    //fwrite(&c.a,sizeof(struct assentos),17,cad);

                    fflush(stdin);
                    horario_hora+=hora+1;
                    horario_min+=min;
                    if(horario_min>=60){
                        horario_hora+=horario_min/60;
                        horario_min=horario_min%60;
                    }
                    if(horario_hora>=24)
                        break;


            }
            strcpy(c.horario,aux);
            strcpy(aux,"");
            fflush(stdin);
            gotoxy(40,9);
            printf("Sess%ces :",228);
            printf("%s",c.horario);
            fflush(stdin);
            setbuf(stdin,NULL);
            cad = fopen("Cadastro filme.txt", "ab");
            fwrite(&c,sizeof(c),1,cad);
            setbuf(stdin,NULL);
            printf("\n\n");
            printf("\t\t\tDeseja alterar outro filme? \n");
            printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
            printf("\t\t\tDigite: ");
            op = getch();
            fflush(stdin);
            if(op == '1'){
            system("cls");
            fclose(cad);
            alterar_filmes();
            }else{
                system("pause");
                fclose(cad);
                return menu_filmes();
            }
        }
    }
	printf("Filme não encontrado\n");
    printf("\t\t\tDeseja alterar outro filme? \n");
    printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
    printf("\t\t\tDigite: \n\t\t\t");
    op = getch();
	fflush(stdin);
	if(op == '1'){
	   	fclose(cad);
	   	alterar_filmes();
	}else{
		fclose(cad);
		system("pause");
		return menu_filmes();
	}
        system("pause");
        return;
}

void pesquisar_filmes(){
    system("cls");
    struct filmes c;
    char nome[40],op;
	cad=fopen("Cadastro filme.txt","rb");
	if(cad == NULL){
        printf("Erro no arquivo...\n");
        return;
	}
	printf("Entre com o filme que gostaria de pesquisar: ");
	fflush(stdin);
	gets(nome);
	while(fread(&c,sizeof(struct filmes),1,cad)==1){
		if(strcmp(c.nome_filme,nome)==0){
            printf("\t-------------------------------------------------------------\n");
            printf("\t\t\t    Nome do filme: %s\n",c.nome_filme);
            printf("\t\t\t    Duraç%co: %d minutos\n",c.duracao);
            printf("\t\t\t    Legenda: %s\n",c.legenda);
            printf("\t\t\t    Classifi%c%co Indicativa: %d\n",135,198,c.classe_ind);
            printf("\t\t\t    %s\n",c.sala);
            printf("\t\t\t    Hor%crios/Sess%ces :",160,228);
            printf("\t\t\t    %s\n ",c.horario);
            fflush(stdin);
            printf("\t-------------------------------------------------------------\n");
            printf("\n");
            printf("\n\n");
            printf("\t\t\tDeseja pesquisar outro filme? \n");
            printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
            printf("\t\t\tDigite: ");
            op = getch();
            fflush(stdin);
            if(op == '1'){
            system("cls");
            fclose(cad);
            pesquisar_filmes();
            }else{
            system("pause");
            fclose(cad);
            return menu_filmes();
            }
        }
    }
    printf("Filme n%co encontrado\n",198);
    printf("\n\n");
	printf("\t\t\tDeseja pesquisar outro filme? \n");
	printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
	printf("\t\t\tDigite: \n");
	op = getch();
    fflush(stdin);
	if(op == '1'){
        system("cls");
        fclose(cad);
		pesquisar_filmes();
    }else{
        system("pause");
        fclose(cad);
        return menu_filmes();
	}
}

void lista_filmes(){
    struct filmes c;
    int i, x = 17, y = 3, x2 = 17;
    int cont = 1, y2 = 3, cont2 = 0;
    int ex1 = 0, ey1 = 0;
    cad=fopen("Cadastro filme.txt","rb");
	if(cad == NULL){
        printf("Erro no arquivo...\n");
        return;
	}
	system("cls");
	for(cont = 0; cont < 2; cont++){
        for(cont2 = 0; cont2 < 16; cont2++){
            gotoxy(67,2);
            textcolor(cont2);
            printf("<<<<<<<LISTA DE FILMES>>>>>>>");
            usleep(50000);
        }
	}
	cont2 = 0;
	cont = 1;
	while((fread(&c,sizeof(struct filmes),1,cad)==1)){
        gotoxy(x,y);
        printf("-------------------------------------------------------------");
        y++;
        gotoxy(x,y);
        printf(" Nome do filme: %s\n",c.nome_filme);
        y++;
        gotoxy(x,y);
        printf(" Dura%c%co: %d minutos",135,198,c.duracao);
        y++;
        gotoxy(x,y);

        printf(" Legenda: %s",c.legenda);
        y++;
        gotoxy(x,y);

        printf(" Clas. Ind.: %d anos",c.classe_ind);
        y++;
        gotoxy(x,y);
        printf(" %s",c.sala);
        x += 40;
        y -= 4;
        gotoxy(x,y);
        printf(" Hor%crios/Sess%ces: ",160,228);
        ex1 = x+1;
        ey1 = y;

        y++;
        x++;
        for(cont = 0; c.horario[cont] != '\0'; cont++){
            fflush(stdin);
            gotoxy(x,y);
            printf("%c",c.horario[cont]);
            x++;
            if(c.horario[cont] == ' '){
                y++;
                x -= 6;
                cont2++;
            }
            if(cont2 == 3){
               // gotoxy(x+5,y);
               // printf("%c",c.horario[cont]);
                y -= 3;
                x += 7;
                cont2 = 0;
            }

        }

        gotoxy(x2,y2+6);
        printf("-------------------------------------------------------------");

        x= ex1 + 29;
        x2 = x;
        y = y2;
        cont2 = 0;
        if(x >= 120){
            x = 17;
            y2 += 7;
            y += 7;
            x2 = 17;
        }
        fflush(stdin);

    }
	fclose(cad);
	printf("\n");
	system("pause");
	return;
}
void excluir_filmes(){
    system("cls");
    char nome[40],op;
    struct filmes c;
	printf("Entre com o filme que gostaria de excluir: ");
	fflush(stdin);
	gets(nome);
	cad=fopen("Cadastro filme.txt","rb");
	if(cad == NULL){
        printf("Erro no arquivo...\n");
        return;
	}
	fflush(stdin);
	while(fread(&c, sizeof(struct filmes), 1, cad)==1){
		if(strcmp(nome, c.nome_filme)==0){
			printf("\t-------------------------------------------------------------\n");
            printf("\t\t\t   Nome do filme: %s\n",c.nome_filme);
            printf("\t\t\t   Dura%c%co: %d minutos\n",135,198,c.duracao);
            printf("\t\t\t   Legenda: %s\n",c.legenda);
            printf("\t\t\t   Class. Ind.: %d Anos\n",c.classe_ind);
            printf("\t\t\t   %s\n",c.sala);
            printf("\t\t\t   Hor%crios/Sess%ces: ",160,228);
            printf("%s\n",c.horario);
            fflush(stdin);
            printf("\t-------------------------------------------------------------\n");
            printf("\n");

            printf("Tem certeza de que quer excluir esse filme? ");
            printf("\n1-Sim\t\t\tQualquer tecla - N%co",198);
            op=getch();
            fflush(stdin);
            if(op=='1'){
            FILE *aux = fopen("auxiliar.txt", "ab");
            rewind(cad);
                while(fread(&c, sizeof(struct filmes), 1, cad)==1){
                    if(strcmp(nome, c.nome_filme)!=0)
                    fwrite(&c, sizeof(struct filmes), 1, aux);
                }
            fclose(cad);
            fclose(aux);
            remove("Cadastro filme.txt");
            rename("auxiliar.txt", "Cadastro filme.txt");
            }
            printf("\n\n");
            printf("\t\t\tDeseja excluir outro filme? \n");
            printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
            printf("\t\t\tDigite: \n");
            op = getch();
            fflush(stdin);
            if(op == '1'){
                system("cls");
                fclose(cad);
                excluir_filmes();
            }else{
                system("pause");
                fclose(cad);
                return menu_filmes();
            }
		}
	}
    printf("Filme não encontrado\n");
    printf("\n\n");
    printf("\t\t\tDeseja excluir outro filme? \n");
    printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
    printf("\t\t\tDigite: \n");
    op = getch();
    fflush(stdin);
    if(op == '1'){
       system("cls");
       fclose(cad);
       excluir_filmes();
    }else{
        system("pause");
        fclose(cad);
        return menu_filmes();
        }
}
void menu_combo(){
    system("cls");
    int y = 16,op;
    moldura();
    moldura2(69,104,11,29,6);
    gotoxy(70,16);
    printf("%c",175);
    gotoxy(81,12);
	printf("MENU COMBO");
	gotoxy(75,16);
	printf("1 - Cadastrar Combo");
	gotoxy(75,18);
	printf("2 - Pesquisar Combo");
	gotoxy(75,20);
	printf("3 - Listar Combo");
	gotoxy(75,22);
    printf("4 - Alterar Combo");
    gotoxy(75,24);
	printf("5 - excluir Combo");
	gotoxy(75,26);
	printf("6 - Retorna ao menu Adm(a)");
	gotoxy(75,28);
	printf("0 - Sair");

    do{
        setas = getch();
        if(setas==0x50 && y == 28){
            gotoxy(70,y);
            printf(" ");
            y=16;
            gotoxy(70,y);
            printf("%c", 175);
            continue;
        }
        if(setas==0x48 && y==16){
            gotoxy(70,y);
            printf(" ");
            y=28;
            gotoxy(70,y);
            printf("%c", 175);
            continue;
        }
        if(setas==0x50 && y<28){
            gotoxy(70,y);
            printf(" ");
            y+=2;
            gotoxy(70,y);
            printf("%c", 175);
        }
        if(setas==0x48 && y>16){
            gotoxy(70,y);
            printf(" ");
            y-=2;
            gotoxy(70,y);
            printf("%c", 175);
        }
    }while(setas!=0xD);

    switch(y){
        case 16:cadastro_combo();break;
        case 18:pesquisar_combo();break;
        case 20:lista_combo();break;
        case 22:alterar_combo();break;
        case 24:excluir_combo();break;
        case 26:adm();break;
        case 28:exit(0);
    }
}

void cadastro_combo(){
	char nome[30], op, entrada;
	struct combo_cinema c;
    system("cls");
    printf("\n\n\n\t\t\tDesejas realmente cadastrar o combo?\n");
    printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
	printf("\t\t\tDigite: \n\t\t\t");
	op = getch();
	fflush(stdin);
	if(op != '1'){
        menu_combo();
	}
	combo = fopen("Arquivo combo.txt","rb");
	if(combo == NULL){
		printf("erro no arquivo...\n");
		system("pause");
		fclose(combo);
	}
	system("cls");
	printf("\n\n\t\t\tEntre com o nome do combo: ");
	fflush(stdin);
	gets(nome);

	while(fread(&c,sizeof(struct combo_cinema),1,combo) == 1){
		if(strcmp(c.nome_combo,nome) == 0){
			printf("\n\n\t\t\tO combo j%c existe\n",160);
			printf("\t\t\tDesejas cadastrar outro combo? \n");
			printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
			printf("\t\t\tDigite: \n\t\t\t");
			op = getch();
		    fflush(stdin);
		    if(op == '1'){
		    	fclose(combo);
		    	cadastro_combo();
			}else{
				fclose(combo);
				system("pause");
				adm();
			}
		}
	}
    fclose(combo);

	combo = fopen("Arquivo combo.txt","ab");
	if(combo == NULL){
		printf("Erro no arquivo.\n");
		system("pause");
		fclose(combo);
		adm();
	}
	strcpy(c.nome_combo,nome);

    printf("\t\t\tProdutos do combo: ");
	gets(c.const_combo);
	printf("\t\t\tValor do combo: ");
	scanf("%f",&c.valor_combo);

	fwrite(&c,sizeof(c),1,combo);

	printf("\n\n");
	printf("\t\t\tDeseja cadastrar outro combo? \n");
	printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
	printf("\t\t\tDigite: ");
	op = getch();
    fflush(stdin);


	if(op == '1'){
        system("cls");
        fclose(combo);
		cadastro_combo();
    }else{
	    printf("\n\n\t\t\tcadastro finalizado\n\n");
        system("pause");
        fclose(combo);
		menu_combo();
	}
}
void pesquisar_combo(){
    system("cls");
    struct combo_cinema c;
    char nome[40],op;
	int cont1;

	combo=fopen("Arquivo combo.txt","rb");
	if(combo == NULL){
        printf("Erro no arquivo...\n");
        return;
	}
	printf("Entre com o combo que gostaria de pesquisar: ");
	fflush(stdin);
	gets(nome);
	while(fread(&c,sizeof(struct combo_cinema),1,combo)==1){
		if(strcmp(c.nome_combo,nome)==0){

            printf("\t----------------------------------------------------------\n");
            printf("\tNome do Combo: %s\n",c.nome_combo);
            printf("\tKit do Combo: %s\n",c.const_combo);
            printf("\tValor: R$ %.2f\n",c.valor_combo);
            printf("\t----------------------------------------------------------\n");
            printf("\n");
            printf("\t\t\tDeseja procurar outro combo? \n");
            printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
            printf("\t\t\tDigite: ");
            op = getch();
            fflush(stdin);
            if(op == '1'){
                system("cls");
                fclose(combo);
                menu_combo();
            }else{
                system("pause");
                fclose(cad);
                menu_combo();
            }
        }
    }
    printf("Combo não encontrado\n");
    printf("\n\n");
	printf("\t\t\tDeseja procurar outro Combo? \n");
	printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
	printf("\t\t\tDigite: \n");
	op = getch();
    fflush(stdin);
	if(op == '1'){
        system("cls");
        fclose(combo);
		pesquisar_combo();
    }else{
        system("pause");
        fclose(combo);
        menu_combo();
	}

}
void moldura3(int x,int y){
    int a,b;

    //linha de cima
    for(a = x; a < x+14;a++){
        b = y;
        printf("%c",205);

    }
    gotoxy(x,y);
    printf("%c",201);
    gotoxy(x+14,y);
    printf("%c",187);

    //Linha de Baixo
    for(a = x; a < y+14; a++){
        b = y+12;
        gotoxy(a,b);
        printf("%c",205);
    }
}
void lista_combo(){
	int x = 15,y = 6;
    int cont = 6;
    char op;

    struct combo_cinema c;

    combo=fopen("Arquivo combo.txt","rb");
	if(combo == NULL){
        printf("Erro no arquivo...\n");
        return;
	}
	system("cls");
    moldura();
    gotoxy(71,4);
	printf("<<<<<<<Lista de Combo>>>>>>>");
	//system("type Cadastro_filme.txt");
	while((fread(&c,sizeof(struct combo_cinema),1,combo)==1)){
        gotoxy(x,y);
        //printf("------------------------");
        y++;
        moldura3(x-1,y-1);
        gotoxy(x,y);
        printf("Nome do Combo:  %s\n",c.nome_combo);
        y+=2;
        gotoxy(x,y);
        printf("Kit do Combo:   %s\n",c.const_combo);
        y+=2;
        gotoxy(x,y);
        printf("Valor:          %.2fR$\n",c.valor_combo);
        //y+=1;
        //gotoxy(x,y);
        //printf("---------------------------------------");
        printf("\n");
        x += 50;

        if(x > 120){
            cont += 8;
            x = 15;
        }
        y = cont;

	}
	op = getch();
    fclose(combo);
    menu_combo();
}
void alterar_combo(){
    struct combo_cinema c;
    char nome[40];
    char op;

    system("cls");
    printf("entre com o nome do combo que gostaria de alterar: ");
    fflush(stdin);
    gets(nome);
    fflush(stdin);

    combo = fopen("Arquivo combo.txt","rb");

    if(combo == NULL){
        printf("Erro no arquivo combo");
        op = getch();
        main();
    }
    while(fread(&c,sizeof(struct combo_cinema),1,combo)==1){
		if(strcmp(c.nome_combo,nome)==0){
            FILE *aux=fopen("auxiliar.txt","ab");
            rewind(combo);
            while(fread(&c,sizeof(struct combo_cinema),1,combo)==1){
            if(strcmp(nome,c.nome_combo)!=0)
                fwrite(&c, sizeof(combo), 1, aux);
            }
            fclose(cad);
            fclose(aux);
            remove("Arquivo combo.txt");
            rename("auxiliar.txt","Arquivo combo.txt");
            system("cls");
            printf("Novo nome do combo: ");
            gets(c.nome_combo);
            printf("\t\t\tProdutos do combo: ");
            gets(c.const_combo);
            printf("\t\t\tValor do combo: ");
            scanf("%f",&c.valor_combo);

            combo = fopen("Arquivo combo.txt", "ab");
            fwrite(&c,sizeof(c),1,combo);

            printf("\n\n");
            printf("\t\t\tDeseja alterar outro combo? \n");
            printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
            printf("\t\t\tDigite: ");
            op = getch();
            fflush(stdin);
            if(op == '1'){
                system("cls");
                fclose(combo);
                alterar_combo();
            }else{
                system("pause");
                fclose(combo);
                menu_combo();
            }
        }
    }
}

void excluir_combo(){
    system("cls");
    char nome[40],op;
    struct combo_cinema c;
	printf("Entre com o combo que gostaria de excluir: ");
	fflush(stdin);
	gets(nome);
	fflush(stdin);
	combo=fopen("Arquivo combo.txt","rb");
	if(combo == NULL){
        printf("Erro no arquivo...\n");
        return;
	}
	fflush(stdin);
	while(fread(&c, sizeof(struct combo_cinema), 1, combo)==1){
		if(strcmp(nome, c.nome_combo)==0){
			printf("\t----------------------------------------------------------\n");
            printf("\tNome do Combo: %s\n",c.nome_combo);
            printf("\tKit do Combo: %s\n",c.const_combo);
            printf("\tValor: %.2f$R\n",c.valor_combo);
            printf("\t----------------------------------------------------------\n");
            printf("\n");
            printf("Tem certeza de que quer excluir esse combo? ");
            printf("\n1-Sim\t\t\tQualquer tecla-Não");
            op=getch();
            fflush(stdin);
            if(op=='1'){
                FILE *aux = fopen("auxiliar.txt", "ab");
                rewind(combo);
                while(fread(&c, sizeof(struct combo_cinema), 1, combo)==1){
                    if(strcmp(nome, c.nome_combo)!=0)
                    fwrite(&c, sizeof(struct combo_cinema), 1, aux);
                }
                fclose(combo);
                fclose(aux);
                remove("Arquivo combo.txt");
                rename("auxiliar.txt", "Arquivo combo.txt");
            }
            printf("\n\n");
            printf("\t\t\tDeseja excluir outro combo? \n");
            printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
            printf("\t\t\tDigite: \n");
            op = getch();
            fflush(stdin);
            if(op == '1'){
                system("cls");
                fclose(combo);
                excluir_combo();
            }else{
                system("pause");
                fclose(combo);
                menu_combo();
            }
		}
	}
    printf("Combo não encontrado\n");
    printf("\n\n");
    printf("\t\t\tDeseja excluir outro combo? \n");
    printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
    printf("\t\t\tDigite: \n");
    op = getch();
    fflush(stdin);
    if(op == '1'){
       system("cls");
       fclose(combo);
       excluir_filmes();
    }else{
        fclose(combo);
        menu_combo();
    }
}

void ingresso_menu(){
	int op;
	moldura();
	system("cls");
	moldura2(64,114,7,20,2);
	gotoxy(64,4);
	printf("                                             ");
	gotoxy(64,5);
	printf("                                             ");
	gotoxy(64,6);
	printf("                                             ");
    gotoxy(64,7);
	printf("                                             ");
	gotoxy(64,8);
	printf("                                             ");
	gotoxy(64,9);
	printf("                                             ");
	gotoxy(64,10);
	printf("                                             ");

	gotoxy(70,12);
    printf("1 - Inserir/Modificar valor do ingresso\n");
    gotoxy(70,14);
    printf("2 - Valor do ingresso atual\n");
    gotoxy(70,16);
    printf("0 - Voltar");
    gotoxy(70,18);
    printf("tDigite a opção:");
    scanf("%d",&op);
    switch(op){
        case 0:{
		    adm();
			break;
		  }
		case 1:{
		    ingresso_altmod();
			break;
		  }
		  case 2:{
		  	ingresso_atual();
			break;
		  }
	}
}
void ingresso_altmod(){
    struct ingresso c1;
    system("cls");
        ing=fopen("Valor ingresso.txt","wb");
        if(ing == NULL){
       		printf("Erro no arquivo...\n");
        	return;
        }
        printf("\n\tValor do ingresso: ");
        printf("\n\tManhã/Tarde:");
        scanf("%f",&c1.ingresso1);
        fflush(stdin);
        printf("\n\tNoite: ");
        scanf(" %f",&c1.ingresso2);
        fflush(stdin);
        fwrite(&c1,sizeof(struct ingresso),1,ing);
        fclose(ing);
        system("pause");
        return ingresso_menu();
}
void ingresso_atual(){
    struct ingresso c1;
    system("cls");
		  	ing=fopen("Valor ingresso.txt","rb");
            if(ing == NULL){
            printf("Erro no arquivo...\n");
            return;
	}
	system("cls");
	printf("\n\t\t\t<<<<<<<Valor do ingresso atual>>>>>>>\n\n");
	while((fread(&c1,sizeof(struct ingresso),1,ing)==1)){
        printf("Valor ingresso:\n");
        printf("Manhã/Tarde: %.2f\n",c1.ingresso1);
        printf("Noite: %.2f\n",c1.ingresso2);
	}
	fclose(ing);
	system("pause");
	return ingresso_menu();
}

void menu_cliente(){
    char op;
    system("cls");
    int y = 16;
    moldura();
   // moldura2();
    moldura2(69,106,11,29,6);
    gotoxy(70,16);
    printf("%c",175);
    gotoxy(81,12);
    printf("MENU CLIENTE");
    gotoxy(75,16);
    printf("1 - Cadastra Cliente");
    gotoxy(75,18);
    printf("2 - Alterar Cliente");
    gotoxy(75,20);
    printf("3 - Pesquisar Cliente");
    gotoxy(75,22);
    printf("4 - Lista Cliente");
    gotoxy(75,24);
    printf("5 - Excluir Cliente");
    gotoxy(75,26);
    printf("6 - Retorna ao menu do Adm(a)");
    gotoxy(75,28);
    printf("0 - Sair");

    do{
        setas = getch();
        if(setas==0x50 && y == 28){
            gotoxy(70,y);
            printf(" ");
            y=16;
            gotoxy(70,y);
            printf("%c", 175);
            continue;
        }
        if(setas==0x48 && y==16){
            gotoxy(70,y);
            printf(" ");
            y=28;
            gotoxy(70,y);
            printf("%c", 175);
            continue;
        }
        if(setas==0x50 && y<28){
            gotoxy(70,y);
            printf(" ");
            y+=2;
            gotoxy(70,y);
            printf("%c", 175);
        }
        if(setas==0x48 && y>16){
            gotoxy(70,y);
            printf(" ");
            y-=2;
            gotoxy(70,y);
            printf("%c", 175);
        }
    }while(setas!=0xD);

    switch(y){
        case 16:cadastro_cliente();break;
        case 18:alterar_cadastro();break;
        case 20:pesquisar_cadastro();break;
        case 22:listar_cadastro();break;
        case 24:excluir_cadastro();break;
        case 26:adm();break;
        case 28:exit(0);
    }
}

void cadastro_cliente(){
        struct cadastro_cliente c;
        char nome[80], nome2[] = "clube cine";
        char numero[15];
        char op, s[20];
        int i = 0;
        system("cls");
        cliente = fopen("Cliente_desconto.txt","rb");

        if(cliente == NULL){
            printf("Erro no arquivo.\n");
            system("pause");
            fclose(cliente);
            main();
        }

        printf("Nome do cliente: ");
        gets(nome);
        fflush(stdin);
        while(fread(&c,sizeof(struct cadastro_cliente),1,cliente) == 1){
            if(strcmp(c.nome_cliente,nome) == 0){
                printf("\n\n\t\t\tO cliente já está cadastrado\n");
                printf("\t\t\tDesejas cadastrar outro cliente? \n");
                printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
                printf("\t\t\tDigite: \n\t\t\t");
                op = getch();
                fflush(stdin);
                if(op == '1'){
                    fclose(cliente);
                    cadastro_cliente();
                }else{
                    fclose(cliente);
                    system("pause");
                    adm();
                }
            }
        }
        fclose(cliente);

    cliente = fopen("Cliente_desconto","ab");
    if(cliente == NULL){
        printf("\t\t\terro no arquivo...");
        op = getch();
        main();
    }
    strcpy(c.nome_cliente,nome);
    fflush(stdin);
    printf("Endere%co: ",135);
    fflush(stdin);
    gets(c.nome_endereco);
    fflush(stdin);
    printf("\nE-Mail: ");
    fflush(stdin);
    gets(c.nome_email);
    fflush(stdin);
    printf("N%cmero do DD: ",163);
    fflush(stdin);
    scanf("%d",&c.dd);
    fflush(stdin);
    printf("\nN%cmero de Telefone: ",163);
    fflush(stdin);
    gets(numero);
    fflush(stdin);
    while(numero[i] != '\0'){
        if(numero[i] < '0' || numero[i] > '9' || i > 10){
            system("cls");
            printf("Nome do cliente: %s\n",c.nome_cliente);
            fflush(stdin);
            printf("Endereço: %s\n",c.nome_endereco);
            fflush(stdin);
            printf("\nE-Mail: %s\n",c.nome_email);
            fflush(stdin);
            printf("\nInforme um número válido\nNúmero de Telefone: ");
            fflush(stdin);
            gets(numero);
            i = 0;
        }
        i++;
    }
    printf("Cep: ");
    gets(s);
    int x = atoi(s);
    c.cep = strtoul(s,'\0',10);
    printf("Cidade: ");
    gets(c.nome_cidade);
    printf("Estado: ");
    gets(c.nome_estado);

	system("cls");
    printf("O cartão que estara disponivel para o cliente e");
    printf("o clube cine, pelo qual, sera dado um desconto de");
    printf("10% a cada compra no cinema AGORA VAI...");
	printf("Cartao - CLUBE CINE\n");
	op = getch();
	strcpy(c.nome_cartao,nome2);
	printf("\n\n\t\t\tcadastro finalizado\n\n");

	fwrite(&c,sizeof(c),1,cliente);

	printf("\n\n");
	printf("\t\t\tDeseja cadastrar outro cliente? \n");
	printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
	printf("\t\t\tDigite: ");
	op = getch();
    fflush(stdin);


	if(op == '1'){
        system("cls");
        fclose(cliente);
		cadastro_cliente();
    }else{
        system("pause");
        fclose(cliente);
		menu_cliente();
	}
}

void alterar_cadastro(){
    struct cadastro_cliente c;
    char nome[40], nomec[] = "Cartao clube cine";
    char numero[20], op, s[20];
    int i;

    cliente = fopen("Cliente_desconto.txt","rb");
    if(cliente == NULL){
        printf("Erro no arquivo cliente...");
        Sleep(2);
        system("cls");
        main();
    }
    printf("Entre com o nome do cliente que deseja alterar: ");
    gets(nome);

    while(fread(&c,sizeof(struct cadastro_cliente),1,cliente) == 1){
        if(strcmp(nome,c.nome_cliente) == 0){
            FILE *aux=fopen("auxiliar.txt","ab");
            rewind(cliente);
            while(fread(&c,sizeof(struct cadastro_cliente),1,cliente)==1){
            if(strcmp(nome,c.nome_cliente)!=0)
                fwrite(&c, sizeof(cliente), 1, aux);
            }
            fclose(cliente);
            fclose(aux);
            remove("Cliente_desconto.txt");
            rename("auxiliar.txt","Cliente_desconto.txt");
            system("cls");
            printf(">>>>> Alteracao <<<<<");
            printf("Nome do cliente: ");
            gets(c.nome_cliente);
            printf("Endere%co: ",135);
            fflush(stdin);
            gets(c.nome_endereco);
            fflush(stdin);
            printf("\nE-Mail: ");
            fflush(stdin);
            gets(c.nome_email);
            fflush(stdin);
            printf("N%cmero do DD: ",163);
            fflush(stdin);
            scanf("%d",&c.dd);
            fflush(stdin);
            printf("\nN%cmero de Telefone: ",163);
            fflush(stdin);
            gets(numero);
            fflush(stdin);
            while(numero[i] != '\0'){
                if(numero[i] < '0' || numero[i] > '9' || i > 10){
                    system("cls");
                    printf("Nome do cliente: %s\n",c.nome_cliente);
                    fflush(stdin);
                    printf("Endereço: %s\n",c.nome_endereco);
                    fflush(stdin);
                    printf("\nE-Mail: %s\n",c.nome_email);
                    fflush(stdin);
                    printf("\nInforme um número válido\nNúmero de Telefone: ");
                    fflush(stdin);
                    gets(numero);
                    i = 0;
                }
                i++;
            }
            printf("Cep: ");
            gets(s);
            int x = atoi(s);
            c.cep = strtoul(s,'\0',10);
            printf("Cidade: ");
            gets(c.nome_cidade);
            printf("Estado: ");
            gets(c.nome_estado);
            strcpy(nomec,c.nome_cartao);

            cliente = fopen("Cliente_desconto.txt", "ab");
            fwrite(&c,sizeof(c),1,cliente);

            printf("\n\n");
            printf("\t\t\tDeseja alterar outro cliente? \n");
            printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
            printf("\t\t\tDigite: \n");
            op = getch();
            fflush(stdin);
            if(op == '1'){
                system("cls");
                fclose(cliente);
                alterar_cadastro();
            }else{
                printf("Altera%c%co realizada com sucesso.\n",135,198);
                printf("pressione qualquer tecla para continuar\n");
                op = getch();
                fclose(cliente);
                menu_cliente();
            }
        }
    }
}
void pesquisar_cadastro(){
    struct cadastro_cliente c;
    char nome[40], op;

    cliente = fopen("Cliente_desconto.txt","rb");
    if(cliente == NULL){
        printf("Erro no arquivo cliente...");
        op = getch();
        main();
    }
    printf("Entre com o nome do cliente que gostaria de pesquisar: ");
    gets(nome);
    fflush(stdin);

    while(fread(&c,sizeof(struct cadastro_cliente),1,cliente) == 1){
        if(strcmp(nome,c.nome_cliente) == 0){
            printf("\t----------------------------------------------------------\n");
            printf("\tNome do cliente: %s\n",c.nome_cliente);
            printf("\tEndereco: %s\n",c.nome_endereco);
            printf("\tE-mail: %s\n",c.nome_email);
            printf("\tN%cmero do DD: %d\n",c.dd);
            printf("\tN%cmero do telefone: %i\n",c.numero);
            printf("\tCep: %i\n",c.cep);
            printf("\tCidade: %s\n",c.nome_cidade);
            printf("\tEstado: %s\n",c.nome_estado);
            printf("\n\tcart%co: %s\n",c.nome_cartao);
            printf("\t----------------------------------------------------------\n");
            printf("Deseja pesquisar outro cliente?");
            printf("Sim - 1\tN%co - Qualquer tecla",198);
            op = getch();
            if(op == '1'){
                system("cls");
                fclose(cliente);
                pesquisar_cadastro();
            }else{
                printf("Pesquisa realizada com sucesso.\n",198);
                printf("pressione qualquer tecla para continuar\n");
                op = getch();
                fclose(cliente);
                menu_cliente();
            }
        }
    }
}
void listar_cadastro(){
    struct cadastro_cliente c;
    char op;
    system("cls");
    cliente = fopen("Cliente_desconto.txt","rb");
    if(cliente == NULL){
        printf("erro no arquivo...\n");
        fclose(cliente);
        main();
    }
    while(fread(&c,sizeof(struct cadastro_cliente),1,cliente) == 1){
        printf("\t----------------------------------------------------------\n");
        printf("\tNome do cliente: %s\n",c.nome_cliente);
        printf("\tEndereco: %s\n",c.nome_endereco);
        printf("\tE-mail: %s\n",c.nome_email);
        printf("\tN%cmero do DD: %d\n",c.dd);
        printf("\tN%cmero do telefone: %i\n",c.numero);
        printf("\tCep: %i\n",c.cep);
        printf("\tCidade: %s\n",c.nome_cidade);
        printf("\tEstado: %s\n",c.nome_estado);
        printf("\n\tcart%co: %s\n",c.nome_cartao);
        printf("\t----------------------------------------------------------\n");
        printf("\n");
    }
    op = getch();
    fclose(cliente);


}
void excluir_cadastro(){
    system("cls");
    char nome[40],op;
    struct cadastro_cliente c;
	printf("Entre com o nome do cliente que gostaria de excluir: ");
	fflush(stdin);
	gets(nome);
	fflush(stdin);
	cliente = fopen("Cliente_desconto.txt","rb");
	if(cliente == NULL){
        printf("Erro no arquivo...\n");
        return;
	}
	fflush(stdin);
	while(fread(&c, sizeof(struct cadastro_cliente), 1, cliente)==1){
		if(strcmp(nome, c.nome_cliente)==0){
			printf("\t----------------------------------------------------------\n");
            printf("\tNome do cliente: %s\n",c.nome_cliente);
            printf("\tEndereco: %s\n",c.nome_endereco);
            printf("\tE-mail: %s\n",c.nome_email);
            printf("\tN%cmero do DD: %d\n",c.dd);
            printf("\tN%cmero do telefone: %i\n",c.numero);
            printf("\tCep: %i\n",c.cep);
            printf("\tCidade: %s\n",c.nome_cidade);
            printf("\tEstado: %s\n",c.nome_estado);
            printf("\n\tcart%co: %s\n",c.nome_cartao);
            printf("\t----------------------------------------------------------\n");
            printf("\n");
            printf("Tem certeza de que quer excluir esse cliente? ");
            printf("\n1-Sim\t\t\tQualquer tecla-Não");
            op=getch();
            fflush(stdin);
            if(op=='1'){
                FILE *aux = fopen("auxiliar.txt", "ab");
                rewind(combo);
                while(fread(&c, sizeof(struct cadastro_cliente), 1, cliente)==1){
                    if(strcmp(nome, c.nome_cliente)!=0)
                    fwrite(&c, sizeof(struct cadastro_cliente), 1, aux);
                }
                fclose(cliente);
                fclose(aux);
                remove("Cliente_desconto.txt");
                rename("auxiliar.txt", "Cliente_desconto.txt");
            }
            printf("\n\n");
            printf("\t\t\tDeseja excluir outro cliente? \n");
            printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
            printf("\t\t\tDigite: \n");
            op = getch();
            fflush(stdin);
            if(op == '1'){
                system("cls");
                fclose(cliente);
                excluir_cadastro();
            }else{
                printf("Exclus%co realizada com sucesso.\n",198);
                printf("pressione qualquer tecla para continuar\n");
                op = getch();
                fclose(cliente);
                menu_cliente();
            }
		}
	}
    printf("Cliente n%co encontrado\n",160);
    printf("\n\n");
    printf("\t\t\tDeseja excluir outro cliente? \n");
    printf("\t\t\t1 - SIM\tQualquer tecla - SAIR\n");
    printf("\t\t\tDigite: \n");
    op = getch();
    fflush(stdin);
    if(op == '1'){
       system("cls");
       fclose(cliente);
       excluir_cadastro();
    }else{
        fclose(cliente);
        adm()
        ;
    }
}

void controle_vendas(){
    struct controle_caixa c;
    char op;
    system("cls");
    rel = fopen("Relatorio.txt","rb");
    if(rel == NULL){
        printf("Erro...\n");
        op = getch();
        fclose(rel);
        rel = fopen("Relatorio.txt","wb");
        c.dinheiro = 0.0;
        fwrite(&c,sizeof(controle_caixa),1,rel);
        fclose(rel);
        main();
    }else{
            gotoxy(13,13);
            printf("Total acumulado at%c agora: \t\tR$ %.2lf",130,36,c.dinheiro);
            fclose(rel);
            op = getch();
            adm();
    }
    op = getch();
}
void us(){
	int y;

	while(1){
		y = 16;
		system("cls");
		moldura();
		moldura2(68,112,11,25,5);
		gotoxy(69,16);
		printf("%c",175);
		gotoxy(82,12);
		printf("MENU DO CAIXA");
		gotoxy(75,16);
		printf("1 - Venda de ingresso");
		gotoxy(75,18);
		printf("2 - Relat%crio de filmes",162);
        gotoxy(75,20);
		printf("3 - Pesquisar filmes");
		gotoxy(75,22);
		printf("5 - Retorna ao menu principal");
		gotoxy(75,24);
		printf("6 - Sair");

		do{
            setas = getch();
            if(setas==0x50 && y == 24){
                fflush(stdin);
				gotoxy(69,y);
                fflush(stdin);
                printf(" ");
                fflush(stdin);
                y=16;
                gotoxy(69,y);
                fflush(stdin);
                printf("%c", 175);
                fflush(stdin);
                continue;
            }
            if(setas==0x48 && y==16){
                gotoxy(69,y);
                fflush(stdin);
                printf(" ");
                fflush(stdin);
                y=24;
                fflush(stdin);
                gotoxy(69,y);
                fflush(stdin);
                printf("%c", 175);
                fflush(stdin);
                continue;
            }
            if(setas==0x50 && y<24){
                gotoxy(69,y);
                fflush(stdin);
                printf(" ");
                fflush(stdin);
                y+=2;
                fflush(stdin);
                gotoxy(69,y);
                fflush(stdin);
                printf("%c", 175);
                fflush(stdin);
            }
            if(setas==0x48 && y>16){
                gotoxy(69,y);
                fflush(stdin);
                printf(" ");
                fflush(stdin);
                y-=2;
                gotoxy(69,y);
                fflush(stdin);
                printf("%c", 175);
                fflush(stdin);
            }
        }while(setas!=0xD);

		switch(y){
        	case 16:venda_dinheiro();break;
			case 18:lista_filmes();break;
			case 20:pesquisar_filmes();break;
			case 22:main();break;
			case 24:exit(0);break;
		}
	}
}
//Funcao para inicializar a matriz de assentos e os vetores da linha e coluna
void matriz_assento(){
    int i,j;
    int letra_ascii;
    char lugar_aux[1000];
    for(x=12,j=1;x<157,j<37;x+=4,j++){
		for(y=2,i=0,letra_ascii=81;y<36,i<17,letra_ascii>=65;y+=2,i++,letra_ascii--){
            if((((x >= 42 && x <= 50) || (x >= 117 && x < 125)) && y!=2) || ((x>11 && x<43 && y==22) || (x>11 && x<20 && y>22 && y<35))){
				m[i][j-1]=0;
			}else{
			    letra[i]=y+letra_ascii;
			    numero[j-1]=j+x;
			    m[i][j-1]=x+y;

            }
        }
	}
}
void escolha_assentos(int qtde_ingresso,char lugar[1000],int mat[17][37]){
	int i,j;
	int a,b;
	int c=81;
	int x,y,z,cont,cont2;
	char letra_lugar, op;
	int num_lugar,letra_ascii;
    int contador;
    char lugar_aux[100];
    textcolor(9);
	//Linha

	for(a = 10; a < 160; a++){
		b = 1;
		if(a == 159){
			gotoxy(a,b);
			printf("%c",187);

            gotoxy(a,39);
			printf("%c",188);
            Sleep(1);
		}else{
			gotoxy(a,b);
			printf("%c",205);
            Sleep(1);
            gotoxy(a,39);
			printf("%c",205);
            Sleep(1);

		}
	}
	//Colunas
	for(b = 2; b < 40; b++){
		a = 10;
		if(b == 39){
			gotoxy(a,b);
			printf("%c",200);
			Sleep(1);
		}else{
			gotoxy(a,b);
			printf("%c",186);
            Sleep(1);
            gotoxy(159,b);
			printf("%c",186);
            Sleep(1);

		}
	}
	gotoxy(10,1);
	printf("%c",201);
    usleep(1);

	textcolor(3);
	//Imprime as letras
	for(b = 3; b < 36; b+=2){
		a = 7;
		gotoxy(a,b);
		printf("%c",c);
		c--;
	}
	b = 0;
	for(a = 11,i=1; a < 157,i<=37; i++, a+=4){
		b = 38;
		gotoxy(a,b);
		printf(" %d",i);

	}
	//Função para imprimir matriz de assentos
	for(x=12;x<157;x+=4){
		for(y=2;y<36;y+=2){
            if((((x >= 42 && x <= 50) || (x >= 117 && x < 125)) && y!=2) || ((x>11 && x<43 && y==22) || (x>11 && x<20 && y>22 && y<35))){
                gotoxy(x,y);
                printf("%c",255);

                gotoxy(x+1,y);
                printf("%c",255);

                gotoxy(x,y+1);
                printf("%c",255);

                gotoxy(x+1,y+1);
                printf("%c",255);

                usleep(0.5);
            //Imprime os assentos
			}else{
                gotoxy(x,y);
                printf("%c",220);

                gotoxy(x+1,y);
                printf("%c",220);

                gotoxy(x,y+1);
                printf("%c",223);

                gotoxy(x+1,y+1);
                printf("%c",223);
                usleep(0.5);
            }
        }
	}
	//Selecona o(s) lugar(es)
    for(cont=0;cont<qtde_ingresso;cont++){
        textcolor(11);
        volta:
        gotoxy(22,40);
        num_lugar=0;
        letra_lugar='0';
        if(cont!=0){
            for(cont2=39;cont2<45;cont2++){
                gotoxy(cont2,40);
                printf("%c",255);
            }
        }
        gotoxy(22,40);
        printf("Escolha o lugar: ");
        scanf("%c %d",&letra_lugar,&num_lugar);
        if(letra_lugar<65||letra_lugar>81||num_lugar<1||num_lugar>37){
            for(i=39;i<=45;i++){
                gotoxy(i,40);
                printf("%c",255);
            }
            printf("\b \b");
            gotoxy(22,41);
            //printf("Assento inv%clido1",160);

            for(j=22;j<38;j++){
                gotoxy(i,41);
                printf("%c",255);
            }
            goto volta;
            gotoxy(22,40);
        }
        sprintf(lugar_aux,"%c %d  ",letra_lugar,num_lugar);
        strcat(lugar,lugar_aux);
        //Formulando a cooordenada y
        for(b = 2,i=0,letra_ascii=81; b < 36,i<17,letra_ascii>=65; i++,b+=2,letra_ascii--){
            if(letra[i] - b==letra_lugar){
                y = letra[i] - letra_lugar;
            }
        }

        //Formulando a cooordenada x
        for(a = 12,j=0; a < 157,j<37; j++, a+=4){
            if(numero[j] - a == num_lugar){
                x = numero[j] - num_lugar;
            }
        }
        if((((x >= 42 && x <= 50) || (x >= 117 && x < 125)) && y!=2) || ((x>11 && x<43 && y==22) || (x>11 && x<20 && y>22 && y<35))){
            gotoxy(39,40);
            printf("%c",255);
            gotoxy(40,40);
            printf("%c",255);
            gotoxy(41,40);
            printf("%c",255);
            printf("\b \b");
            gotoxy(22,41);
            printf("Assento inv%clido",160);
            goto volta;
            gotoxy(22,40);
        }else{
            textcolor(10);
            fflush(stdin);
            gotoxy(x,y);
            printf("%c",220);
            fflush(stdin);
            gotoxy(x+1,y);
            printf("%c",220);
            fflush(stdin);
            gotoxy(x,y+1);
            printf("%c",223);
            fflush(stdin);
            gotoxy(x+1,y+1);
            printf("%c",223);
            fflush(stdin);
        }
    }
    return lugar;
	system("pause");
}
void venda_dinheiro(){
    system("cls");
    struct combo_cinema c;
    struct filmes d;
    struct ingresso c1;
    int opcao;
    char lugar[10000];
    char op, nome[40],hora_aux[10],hora1[10];
    int qtde_meia, qtde_ingresso;
    int tipo, m = 0, num, cont1 = 0, cont2 = 0;
    int ex1, ey1, cont, x2 = 50, y2 = 16;
    int x = 50, y = 16;
    float valor_tarde,valor_noite, valor, valor2;

    int i,j;
    int mat[17][37];
    struct controle_caixa venda;

    int hora;
    char p;
    int minuto;
    gotoxy(62,17);
    printf("Esta fun%c%co est%c destinada a venda de ingressos",135,198,160);
    gotoxy(62,18);
    printf("e abrir%c em uma tela para tal. Deseja continuar ?",160);
    gotoxy(66,20);
    printf("1 - SIM    Qualquer tecla - SAIR");
    gotoxy(66,21);
    printf("Digite: ");
    op = getch();
    fflush(stdin);
    if(op == '1'){
       system("cls");
    }else{
        us();
    }

    lista_filmes();
    //gotoxy();
    printf("Escolha o filme: ");
    gets(nome);
    cad = fopen("cadastro filme.txt","rb");
    if(cad == NULL){
        printf("erro...\n");
        op = getch();
        main();
    }

    system("cls");
    while(fread(&d,sizeof(struct filmes),1,cad) == 1){
        if(strcmp(d.nome_filme,nome) == 0){
        gotoxy(x,y);
        printf("-------------------------------------------------------------");
        y++;
        gotoxy(x,y);
        printf(" Nome do filme: %s\n",d.nome_filme);
        y++;
        gotoxy(x,y);
        printf(" Dura%c%co: %d minutos",135,198,d.duracao);
        y++;
        gotoxy(x,y);

        printf(" Legenda: %s",d.legenda);
        y++;
        gotoxy(x,y);

        printf(" Clas. Ind.: %d anos",d.classe_ind);
        y++;
        gotoxy(x,y);
        printf(" %s",d.sala);
        x += 40;
        y -= 4;
        gotoxy(x,y);
        printf(" Hor%crios/Sess%ces: ",160,228);
        ex1 = x+1;
        ey1 = y;

        y++;
        x++;
        for(cont = 0; d.horario[cont] != '\0'; cont++){
            fflush(stdin);
            gotoxy(x,y);
            printf("%c",d.horario[cont]);
            x++;
            if(d.horario[cont] == ' '){
                y++;
                x -= 6;
                cont2++;
            }
            if(cont2 == 3){
               // gotoxy(x+5,y);
               // printf("%c",c.horario[cont]);
                y -= 3;
                x += 7;
                cont2 = 0;
            }

        }

        gotoxy(x2,y2+6);
        printf("-------------------------------------------------------------");

        x= ex1 + 29;
        x2 = x;
        y = y2;
        cont2 = 0;
        if(x >= 120){
            x = 17;
            y2 += 7;
            y += 7;
            x2 = 17;
        }
        fflush(stdin);
        }
    }
    gotoxy(30,30);
    printf("Horario: ");
    gotoxy(38,30);
    scanf("%d%c%d",&hora,&p,&minuto);
    sprintf(hora_aux,"%d%c%d",hora,p,minuto);

    ing = fopen("Valor ingresso.txt","rb");
    if(ing == NULL){
        printf("Erro no arquivo...\n");
        op = getch();
        return;
	}
	system("cls");
	gotoxy(65,2);
	printf("<<<<<<<Valor do ingresso atual>>>>>>>");
	while((fread(&c1,sizeof(struct ingresso),1,ing)==1)){
        gotoxy(55,4);
        printf("Valor ingresso:");
        if(hora < 18){
            gotoxy(55,5);
            printf("Manh%c/Tarde: %.2f",160,c1.ingresso1);
        }else{
            gotoxy(50,5);
            printf("Noite: %.2f",c1.ingresso2);
        }
	}
	gotoxy(55,7);
    printf("Quantidade de ingressos: ");
    scanf("%d",&qtde_ingresso);
    volta1:
    gotoxy(55,8);
    printf("Tipo (1 - Normal/2- Meia): ");
    scanf("%d",&tipo);
    if(tipo == 2 && qtde_ingresso> 1){
        volta3:
        gotoxy(55,9);
        printf("Quantos ingressos ter%co o valor de meia? ",198);
        scanf("%d",&m);
        if(m > qtde_ingresso){
            gotoxy(55,10);
           printf("O n%cmero de meias n%co corresponde ao n%cmero de ingressos.",163,198,163);
            Sleep(3);
            gotoxy(55,10);
           printf("                                                            ");
           goto volta3;
        }
    }

    fclose(ing);
    gotoxy(55,11);
    printf("Desejas comprar algum combo?\n");
    gotoxy(55,12);
    printf("1 - SIM\t2 - N%cO: \n",199);
    gotoxy(55,13);
    printf("Digite: ");
    scanf("%d",&opcao);
    fflush(stdin);
    combo = fopen("Arquivo combo.txt","rb");
        if(combo == NULL){
            system("cls");
            printf("Erro no arquivo...\n");
            main();
    }
    fflush(stdin);
    if(opcao == 1){
        system("cls");
        while(fread(&c,sizeof(struct combo_cinema),1,combo) == 1){
            printf("\t----------------------------------------------------------\n");
            printf("\tNome do Combo: %s\n",c.nome_combo);
            printf("\tKit do Combo: %s\n",c.const_combo);
            printf("\tValor: R$%.2f\n",c.valor_combo);
            printf("\t----------------------------------------------------------\n");
        }
        rewind(combo);
        printf("Entre com o nome do combo: ");
        fflush(stdin);
        gets(nome);
        fflush(stdin);
        printf("\n\n\n");
        while(fread(&c,sizeof(struct combo_cinema),1,combo) == 1){
            if(strcmp(c.nome_combo,nome) == 0){
                printf("\t----------------------------------------------------------\n");
                printf("\tNome do Combo: %s\n",c.nome_combo);
                printf("\tKit do Combo: %s\n",c.const_combo);
                printf("\tValor: R$%.2f\n",c.valor_combo);
                printf("\t----------------------------------------------------------\n");
                printf("\n Quantos %s(s) voc%c quer vender? \t\t", nome,136);
                scanf("%d",&num);
                valor2 = c.valor_combo*num;
                if(hora < 18 && m > 0){
                    valor = c1.ingresso1*(qtde_ingresso - m) + m*(c1.ingresso1/2);
                }else{
                    if(hora < 18){
                        valor = c1.ingresso1*qtde_ingresso;
                    }
                }
                if(hora > 18 && m > 0){
                    valor = c1.ingresso2*(qtde_ingresso - m) + m*(c1.ingresso2/2);
                }else{
                    valor = c1.ingresso2*qtde_ingresso;
                }
                printf("\n\n");
                printf("VALOR TOTAL INGRESSO: R$ %.2f\n",valor);
                printf("VALOR TOTAL COMBO: R$ %.2f\n",valor2);
                printf("VALOR TOTAL: %.2f\n",valor+valor2);

                op = getch();
            }
        }
    }
    system("cls");
    rel = fopen("Relatorio.txt","rb");
    struct controle_caixa f;
    if(rel == NULL){
        venda.dinheiro = 0.0;
        venda.dinheiro += valor + valor2;
    }else{
        fclose(rel);
        rel = fopen("Relatorio.txt","ab");
        if(rel == NULL){
            printf("erro...\n");
            op = getch();
            fclose(rel);
            main();
        }
        venda.dinheiro += valor + valor2;
        fwrite(&venda,sizeof(controle_caixa),1,rel);
        fclose(rel);
    }
    matriz_assento();
    escolha_assentos(qtde_ingresso,lugar,mat);

    system("cls");

    cad = fopen("cadastro filme.txt","rb");
    if(cad == NULL){
        printf("erro...\n");
        op = getch();
        main();
    }

    system("cls");
    printf("Resumo da compra");
    printf("\n");
    rewind(cad);
    while(fread(&d,sizeof(struct filmes),1,cad) == 1){
        if(strcmp(d.nome_filme,nome) == 0){
            printf("\t-------------------------------------------------------------\n");
            printf("\t\t\t   Nome do filme: %s\n",d.nome_filme);
            printf("\t\t\t   Dura%c%co: %d minutos\n",135,198,d.duracao);
            printf("\t\t\t   Legenda: %s\n",d.legenda);
            printf("\t\t\t   Class. Ind.: %d Anos\n",d.classe_ind);
            printf("\t\t\t   %s\n",d.sala);
            fflush(stdin);
            printf("\t-------------------------------------------------------------\n");
            printf("\n");
        }

    }
    if(hora < 18 && m > 0){
        valor = c1.ingresso1*(qtde_ingresso - m) + m*(c1.ingresso1/2);
    }else{
        if(hora < 18){
            valor = c1.ingresso1*qtde_ingresso;
        }
    }
    if(hora > 18 && m > 0){
        valor = c1.ingresso2*(qtde_ingresso - m) + m*(c1.ingresso2/2);
    }else{
        valor = c1.ingresso2*qtde_ingresso;
    }
    fclose(cad);
    fflush(stdin);
    printf("\nHor%crio: %s\n",160,hora_aux);
    fflush(stdin);
    printf("Quantidade de ingressos: %d",qtde_ingresso);
    printf("\n");
    printf("Lugares: ");
    printf("\n%s",lugar);
    printf("\n");
    printf("VALOR TOTAL INGRESSO: R$ %.2f\n",valor);
    getch();
}


//PARTES DE DESING DO SISTEMA
void gotoxy(int x,int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void textcolor (int COLOR){
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= COLOR);
}

void moldura(){
	int a,b;
    textcolor(13);
	//Linha de Cima

	for(a = 3; a < 167; a++){
		b = 2;
		//textcolor(12);
		if(a == 166){
			gotoxy(a,b);
			printf("%c",178);
		}else{
			gotoxy(a,b);
			printf("%c",178);
		}
		usleep(2000);
	}
	//Linha de Baixo
	for(a = 166; a > 2; a--){
		b = 42;
		if(a == 166){
			gotoxy(a,b);
			printf("%c",178);
		}else{
			gotoxy(a,b);
			printf("%c",178);
		}
		usleep(2000);
	}
	//Coluna da Esquerda
	for(b = 3; b < 43; b++){
		a = 3;
		if(b == 42){
			gotoxy(a,b);
			printf("%c",178);
		}else{
			gotoxy(a,b);
			printf("%c",178);
		}
	}
	gotoxy(3,2);
	printf("%c",178);

	//Coluna da direita
	for(b = 3; b < 43; b++){
		a = 166;
		if(b == 42){
			gotoxy(a,b);
			printf("%c",188);
		}else{
			gotoxy(a,b);
			printf("%c",186);
		}
	}


}

void moldura2(int col_ini, int col_fim, int line_ini, int line_fim, int numero_op){
	int x = 0, y = 0, cont;
	//Nome do menu moldura
	//Linha de cima
	textcolor(11);
	for(x = col_ini; x < col_fim;x+=2){
		y = line_ini;
		if(x == col_fim - 1){
			gotoxy(x,y);
			printf("%c",254);
		}else{
			gotoxy(x,y);
			printf("%c",254);
		}
	//	Sleep(1);
	}
	//Linha de baixo
	y = line_ini + 2;
	for(x = col_ini+1; x < col_fim-2;x++){
        gotoxy(x,y);
        printf("%c",254);
    }
		//Sleep(1);
	//Coluna da esquerda
	textcolor(5);
    gotoxy(x,y);
    printf(" %c",254);
	for(y = line_ini; y < line_ini+3; y++){
		x = col_ini-1;
		gotoxy(x,y);
        printf("%c",254);
		//Sleep(0.4);
	}
	gotoxy(col_fim-1,line_ini);
	printf("%c",254);

	//Coluna da Direita
	gotoxy(col_fim - 1,line_ini+1);
	printf("%c",254);
    //Sleep(0.4);
	/*Moldura das opções*/

	//Linha de cima
	for(x = col_ini; x <col_fim; x++){
		y = line_ini + 4;
		if(x == col_fim - 1){
			gotoxy(col_ini-1,y);
			printf("%c",254);
			gotoxy(col_fim-1,y);
			printf("%c",254);
		}else{
			if(x == col_ini+3){
				gotoxy(x,y);
				printf("%c",254);
			}else{
				gotoxy(x,y);
				printf("%c",254);
			}
		}
		//Sleep(1);
	}
	//Linha de baixo
	gotoxy(col_ini-1,line_fim);
	printf("%c",254);
	for(x = col_ini; x < col_fim; x++){
		y = line_fim;
		if(x == col_fim-1){
			//gotoxy(x,y);
			//printf("%c",200);
			gotoxy(x,y);
			printf("%c",254);
		}else{
			if(x == col_ini+3){
				gotoxy(x,y);
				printf("%c",254);
			}else{
                gotoxy(x,y);
                printf("%c",254);
            }
		}
		//Sleep(1);
	}
	//Linhas paralelas
	y = line_ini+6;
	for(cont = 0; cont < numero_op; cont++){
		for(x = col_ini+3; x < col_fim; x++){
			gotoxy(x,y);
			printf("%c",254);
			if(x == col_fim - 1){
				gotoxy(col_ini+3,y);
				printf("%c",254);
				gotoxy(col_fim-1,y);
				printf("%c",254);
			}
			//Sleep(1);
		}
		y += 2;
	}
    textcolor(11);
	//Coluna da esquerda
	for(y = line_ini + 5; y < line_fim; y++){
		x = col_ini-1;
		gotoxy(x,y);
		printf("%c",254);
        x = col_fim-1;
		gotoxy(x,y);
		printf("%c",254);
        //Sleep(1);
	}
	//Coluna do meio
	x = col_ini+3;
	for(y = line_ini+5; y < line_fim;y++){
		gotoxy(x,y);
		printf("%c",254);
	}
}
void desenho(){
    int x = 4;
        textcolor(15);
        gotoxy(x,11);
        printf("              *    %c %c\n",207,207);
        gotoxy(x,12);
        printf("          *       %c %c %c\n",207,207,207);
        gotoxy(x,13);
        printf("                 %c %c %c %c\n",207,207,207,207);
        gotoxy(x,14);
        printf("      *         %c %c %c %c %c\n",207,207,207,207,207);
        gotoxy(x,15);
        printf("               %c %c %c %c %c %c\n",207,207,207,207,207,207);
        gotoxy(x,16);
        printf("   *          %c %c %c %c %c %c %c  *\n",207,207,207,207,207,207,207,207,207,207,207,207,207,207);
        gotoxy(x,17);
        printf("             %c %c %c %c %c %c %c %c\n",207,207,207,207,207,207,207,207,207,207,207,207,207,207);
        gotoxy(x,18);
        printf(" *          %c %c %c %c %c %c %c %c %c     *\n",207,207,207,207,207,207,207,207,207,207,207,207,207,207,207);
        gotoxy(x,19);
        printf("           %c %c %c %c %c %c %c %c %c %c\n",207,207,207,207,207,207,207,207,207,207,207,207,207,207,207);
        gotoxy(x,20);
        printf("          %c %c %c %c %c %c %c %c %c %c %c\n",207,207,207,207,207,207,207,207,207,207,207,207,207,207,207);
        gotoxy(x,21);
        printf("         %c %c %c %c %c %c %c %c %c %c %c %c      *\n",207,207,207,207,207,207,207,207,207,207,207,207,207,207,207);
        gotoxy(x,22);
        printf("        %c %c %c %c %c %c %c %c %c %c %c %c %c\n",207,207,207,207,207,207,207,207,207,207,207,207,207,207,207);
        gotoxy(x,23);
        printf("       %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n",207,207,207,207,207,207,207,207,207,207,207,207,207,207,207,207);
        textcolor(11);
        gotoxy(x,24);
        printf("    _________________________________    ");
        gotoxy(x,25);
        printf("    \\\\                             //");
        gotoxy(x,26);
        printf("     \\\\                           //");
        gotoxy(x,27);
        printf("      \\\\                         //");
        gotoxy(x,28);
        printf("       \\\\                       //");
        gotoxy(x,29);
        printf("        \\\\                     //");
        gotoxy(x,30);
        printf("         \\\\                   //");
        gotoxy(x,31);
        printf("          \\\\                 //");
        gotoxy(x,32);
        printf("           \\\\               //");
        gotoxy(x,33);
        printf("            \\\\             //");
        gotoxy(x,34);
        printf("             \\\\           //");
        gotoxy(x,35);
        printf("              \\\\_________//");
        x = x*4;
        gotoxy(x,26);
        textcolor(13);
        Sleep(50);
        printf("      \\___/");
        gotoxy(x,27);
        Sleep(50);
        printf("      /- -\\");
        gotoxy(x,28);
        Sleep(50);
        printf("  /--/ (=) \\--\\");
        gotoxy(x,29);
        Sleep(50);
        printf(" /    |___|    \\");
        gotoxy(x,30);
        Sleep(50);
        printf("/    /     \\    \\");
        gotoxy(x,31);
        Sleep(50);
        printf("    /-------\\   ",179);
        gotoxy(x,32);
        Sleep(50);
        printf("      /\\ /\\  \n");
    gotoxy(x,39);
    usleep(1000);

    textcolor(15);
    gotoxy(130,6);
    printf("                           / /\n");
    gotoxy(130,7);
    printf("                          / /\n");
    gotoxy(130,8);
    printf("                         / /\n");
    gotoxy(130,9);
    printf("                        / /\n");
    gotoxy(130,10);
    printf("                       / /\n");
    gotoxy(130,11);
    printf("                      / /\n");
    gotoxy(130,12);
    printf("                     / /\n");
    gotoxy(130,13);
    printf("                    / /\n");
    gotoxy(130,14);
    printf("                   / /\n");
    textcolor(10);
    gotoxy(130,15);
    printf("__________________/ /_\n");
    textcolor(14);
    gotoxy(130,16);
    printf("\\  /\\  /\\  /\\  /\\  / /\n");
    gotoxy(130,17);
    printf(" \\/  \\/  \\/  \\/  \\/ /\n");
    gotoxy(130,18);
    printf("  \\  /\\  /\\  /\\  /\\/\n");
    gotoxy(130,19);
    printf("   \\/  \\/  \\/  \\/ /\n");
    gotoxy(130,20);
    printf("    \\  /\\  /\\  /\\/\n");
    gotoxy(130,21);
    printf("     \\/  \\/  \\/ /\n");
    gotoxy(130,22);
    printf("      \\  /\\  /\\/\n");
    gotoxy(130,23);
    printf("       \\/  \\/ /\n");
    gotoxy(130,24);
    printf("        \\____/\n");
}
