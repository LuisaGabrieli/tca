#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bib.h"
#include "gea.h"

typedef struct{

	char *nome;
	char *login;
	char *senha;
	int tipo;

}Usuario;

typedef struct{

	char *nomeClube;
	char *cid;
	char *est;
	char *arena;

}Clubes;

typedef struct{

	int golA;
	int golB;
	int casa;
	int visit;
	int cartAmarA;
	int cartVermA;
	int cartAmarB;
	int cartVermB;
}Jogo;

typedef struct{

	char *nome;
	int pontos;
	int jogos;
	int vit;
	int emp;
	int der;
	int gp;
	int gc;
	int sg;
	int mGp;
	int mGc;
	int aprov;
	int move;

}Ranking;



void modificar(Usuario *atual, char *str, int op);
int cadastrar(Usuario user);
int remover(char *login);
int logar(Usuario *user, char *login, char *senha);
int verificar();
void menuAdmin();
void menuUser();
void visualizar();
void cadastra_clube();
void continuar_cadastro();
void ranking();

int main(){

	Usuario user;

	Usuario atual;

	int a, final = 0, login = 0, u, flag;
	char *log, *senha;

	user.nome = malloc(80*sizeof(char));
	user.login = malloc(80*sizeof(char));
	user.senha = malloc(80*sizeof(char));
	atual.nome = malloc(80*sizeof(char));
	atual.login = malloc(80*sizeof(char));
	atual.senha = malloc(80*sizeof(char));

	while(final != 1){
		system("clear");
		if(verificar() == 0){

			COR_BRANCO
			COR_AZUL
			printf("\t\tCADASTRO DE ADMINISTRADOR\n");

			COR_BRANCO
			printf("Digite seu nome: ");
			COR_VERDE
			user.nome = scanfx(); 
			COR_BRANCO
			printf("Digite seu login: ");
			COR_VERDE
			user.login = scanfx();
			COR_BRANCO
			printf("Digite sua senha: ");
			COR_VERDE
			user.senha = scanfx();

			user.tipo = 1;

			cadastrar(user);

		}else{
			system("clear");
			COR_BRANCO
			COR_AZUL
			printf("logar\n");
			COR_BRANCO
			printf("login:\t");
			COR_VERDE
			log = scanfx();
			COR_BRANCO
			printf("senha:\t");
			COR_VERDE
			senha = scanfx();

			u = logar(&atual, log, senha);
			if(u==1){
				login = 1;
				COR_LARANJA
				printf("Seja Bem-vindo %s\n", atual.nome);
				
				while(login == 1){
					menuAdmin(atual);
					scanf("%i", &a);

					system("clear");
					if(a==1){

						COR_BRANCO
						COR_AZUL
						printf("\t\tCADASTRO DE USUARIO\n");
						COR_BRANCO
						printf("Digite seu nome: ");
						COR_VERDE
						user.nome = scanfx(); 
						COR_BRANCO
						printf("Digite seu login: ");
						COR_VERDE
						user.login = scanfx();
						COR_BRANCO
						printf("Digite seua senha: ");
						COR_VERDE
						user.senha = scanfx();

						user.tipo = 2;

						system("clear");
						if(cadastrar(user)==0){
							printf("Cadastrado com sucesso\n");
							
						}
						else{
							printf("login já exitente\n");
							
						}

					}
					else if(a==2){
						visualizar();
						
					}
					else if(a==3){

						do{
							system("clear");
							printf("MODIFICAR ADMINISTRADOR");
							printf("\n1)nome \n2)senha\n");
							scanf("%i", &a);
						}while(a != 1 && a != 2);
						
						if(a==1)
							printf("Digite o novo nome: ");
						else{
							printf("Digite a nova senha: ");
						}	

						log = scanfx();
						modificar(&atual, log, a);
					}
					else if(a==4){
						printf("REMOVER USUARIO\nlogin:");
						log = scanfx();
						flag = remover(log);

						if(flag==1){
							printf("ADMINISTRADOR REMOVIDO\n");
							login=0;
							__fpurge(stdin);
							getchar();
						}
						else if(flag == 2){
							printf("USUARIO REMOVIDO\n");
						}

					}
					else if(a==5){
						login = 0;
					}
					else if(a==6){
						login = 0;
						final = 1;
					}
				}
			}
			else if(u==2){
				COR_LARANJA
				printf("Seja Bem-vindo: %s\n", atual.nome);
				
				login = 1;
				while(login != 0){
					menuUser(atual);
					scanf("%i", &a);

					if(a==1){
						cadastra_clube();
					}
					else if(a==2){
						continuar_cadastro();
					}
					else if(a==3){
						printf("MODIFICAR USUARIO");

						printf("\n1)nome \n2)senha\n");
						scanf("%i", &a);
						
						if(a==1)
							printf("Digite o novo nome: ");
						else{
							printf("Digite a nova senha: ");
						}	

						log = scanfx();
						modificar(&atual, log, a);
						if(a==1){
							printf("alterado para %s\n", atual.nome);
						}
						else{
							printf("alterado para %s\n", atual.senha);
						}
					}
					else if(a==5){
						ranking();
					}
					else if(a==6){
						login = 0;
					}
					else if(a==7){
						login = 0;
						final = 1;
					}
				}
			}
			else{
				printf("deu ruim\n");
				getchar();
			}

		}
	}

	return 0;
}


int verificar(){

	FILE *fp = fopen("usuarios.txt", "a+");
	char *str = malloc(80*sizeof(char));
	int f = 0, usuario = 1; 

	Usuario user; 
	user.nome = malloc(80*sizeof(char));
	user.login = malloc(80*sizeof(char));
	user.senha = malloc(80*sizeof(char));

	if(fp!=NULL){
		while(fgets(str,80, fp)!=NULL){

			if(usuario==1){
				strcpy(user.nome, str);
				usuario++;
			}
			else if(usuario==2){
				strcpy(user.login, str);
				usuario++;
			}
			else if(usuario==3){
				strcpy(user.senha, str);
				usuario++;
			}else if(usuario==4){

				user.tipo = *str-48;
				usuario = 1;
				if(user.tipo==1){
					f  = 1;
					break;				
				}
			}
		}
	}

	return f;
}


int cadastrar(Usuario user){

	FILE *fp = fopen("usuarios.txt", "a+");
	char *login = malloc(80*sizeof(char));
	char *str = malloc(80*sizeof(char));
	int f = 0, usuario = 1;
	if(fp!=NULL){


		while(fgets(str,80, fp)!=NULL){

			if(usuario==2){
				strcpy(login, str);
				usuario++;
			}
			else if(usuario==4){
				usuario = 1;

				if(strcmp(login, user.login)==10){
					f = 1;
				}
			}
			else{

				usuario++;
			}
		}

		if(f == 0)
		fprintf(fp, "%s\n%s\n%s\n%i\n", user.nome, user.login, user.senha, user.tipo);
	}

	fclose(fp);

	return f;
}

int logar(Usuario *user, char *login, char *senha){

	FILE *fp = fopen("usuarios.txt", "r");
	char *str = malloc(80*sizeof(char));
	int f = 0, usuario = 1;


	if(fp!=NULL){

		while(fgets(str,80, fp)!=NULL){
			if(usuario==1){
				strcpy(user->nome, str);
				usuario++;
			}
			else if(usuario==2){
				strcpy(user->login, str);
				usuario++;
			}
			else if(usuario==3){
				strcpy(user->senha, str);
				usuario++;
			}else if(usuario==4){
				user->tipo = *str-48;
				usuario = 1;
				if(strcmp(user->login, login)==10 && strcmp(user->senha, senha)==10){
					f = user->tipo;

					break;
				}
			}
		}
	}

	fclose(fp);

	return f;
}

void menuAdmin(Usuario user){

	__fpurge(stdin);
	getchar();
	system("clear");
	COR_BRANCO
	printf("\t\tMENU DO ADMINISTRADOR\n");
	printf("-> 1) CADASTRAR\n");
	printf("-> 2) VISUALISAR\n");
	printf("-> 3) MODIFICAR ADMINISTRADOR\n");
	printf("-> 4) REMOVER\n");
	printf("-> 5) LOGOFF\n");
	printf("-> 6)");
	COR_VERMELHO
	printf(" SAIR\n");
	COR_BRANCO
}

void menuUser(){
	__fpurge(stdin);
	getchar();
	system("clear");
	COR_BRANCO
	printf("\t\tMENU DO USUARIO\n");
	printf("-> 1) INICIAR O USUARIO\n");
	printf("-> 2) CONTINUAR\n");
	printf("-> 3) MODIFICAR DADOS DE AUTENTICAÇÃO\n");
	printf("-> 4) CONFIGURAÇÃO\n");
	printf("-> 5) RANKING\n");
	printf("-> 6) LOGOFF\n");
	printf("-> 7)");
	COR_VERMELHO
	printf(" SAIR\n");
	COR_BRANCO
}

void visualizar(){
	FILE *fp = fopen("usuarios.txt", "r");
	char *str = malloc(80*sizeof(char));
	int usuario = 1, tipo;


	if(fp!=NULL){

		while(fgets(str,80, fp)!=NULL){
			if(usuario==1){
				COR_BRANCO
				printf("Nome: %s", str);
				usuario++;
			}
			else if(usuario==2){
				COR_BRANCO
				printf("Login: %s", str);
				usuario++;
			}
			else if(usuario==3){
				COR_BRANCO
				printf("Senha: %s", str);
				usuario++;
			}else if(usuario==4){
				tipo = *str-48;
				usuario = 1;
				if(tipo==1){
					COR_AZUL
					printf("ADMINISTRADOR\n\n\n");
				}
				else if(tipo==2){
					COR_AZUL
					printf("USUARIO\n\n\n");
				}
			}
		}
	}

	fclose(fp);
}

int remover(char *login){

	FILE *fa = fopen("auxiliar.txt", "w");
	FILE *fp = fopen("usuarios.txt", "r");
	char *str = malloc(80*sizeof(char));
	int usuario=1, flag=0;

	Usuario user; 
	user.nome = malloc(80*sizeof(char));
	user.login = malloc(80*sizeof(char));
	user.senha = malloc(80*sizeof(char));

	if(fp!=NULL){

		while(fgets(str,80, fp)!=NULL){

			if(usuario==1){
				strcpy(user.nome, str);
				usuario++;
			}
			else if(usuario==2){
				strcpy(user.login, str);
				usuario++;
			}
			else if(usuario==3){
				strcpy(user.senha, str);
				usuario++;
			}else if(usuario==4){

				user.tipo = *str-48;
				usuario = 1;
				if(strcmp(user.login, login)==10){
					flag=user.tipo;				
				}
				else{
					fprintf(fa, "%s%s%s%i\n", user.nome, user.login, user.senha, user.tipo);
				}
			}
		}
	}
	fclose(fa);
	fclose(fp);

	remove("usuarios.txt");
	rename("auxiliar.txt","usuarios.txt");

	return flag;
}

void modificar(Usuario *atual, char *string, int op){

	FILE *fa = fopen("auxiliar.txt", "w");
	FILE *fp = fopen("usuarios.txt", "r");
	int usuario = 1;
	char *str;
	
	Usuario user; 
	user.nome = malloc(80*sizeof(char));
	user.login = malloc(80*sizeof(char));
	user.senha = malloc(80*sizeof(char));
	str = malloc(80*sizeof(char));

	if(fp != NULL){

		while(fgets(str,80, fp)!= NULL){

			if(usuario == 1){
				strcpy(user.nome, str);
				usuario++;
			}
			else if(usuario == 2){
				strcpy(user.login, str);
				usuario++;
			}
			else if(usuario == 3){
				strcpy(user.senha, str);
				usuario++;
			}else if(usuario == 4){
				
				user.tipo = *str-48;
				usuario = 1;
				if(strcmp(user.login, atual->login)==0){
					if(op==1){
						strcpy(user.nome,string);
						strcat(user.nome,"\n");
						strcpy(atual->nome,string);
					}
					else{
						strcpy(user.senha,string);
						strcat(user.senha,"\n");
						strcpy(atual->senha,string);
					}
					fprintf(fa, "%s%s%s%i\n", user.nome, user.login, user.senha, user.tipo);
					
					}
				else{
					fprintf(fa, "%s%s%s%i\n", user.nome, user.login, user.senha, user.tipo);
				}
			}
		}
	}
	fclose(fa);
	fclose(fp);

	remove("usuarios.txt");
	rename("auxiliar.txt","usuarios.txt");
}
void cadastra_clube(){

		FILE *slv = fopen("salvos.txt", "w");

		Clubes info;

		info.nomeClube = malloc(80 * sizeof(char));	
		info.cid = malloc(80 * sizeof(char));	
		info.est = malloc(80 * sizeof(char));	
		info.arena = malloc(80 * sizeof(char));	

		int i;

		char resp;

			printf("\t\tCADASTRO DE CLUBES\n");

			for(i=0; i < 20 && resp != 'n'; i++){

				COR_BRANCO
				printf("Digite o clube : ");
				COR_VERDE
				info.nomeClube = scanfx(); 
				COR_BRANCO
				printf("Digite a cidade: ");
				COR_VERDE
				info.cid = scanfx();
				COR_BRANCO
				printf("Digite o estado: ");
				COR_VERDE
				info.est = scanfx();
				COR_BRANCO
				printf("Digite o estadio: ");
				COR_VERDE
				info.arena = scanfx();

				fprintf(slv, "%s\n%s\n%s\n%s\n", info.nomeClube, info.cid, info.est, info.arena);

				printf("CONTINUAR? S/N\n");
				__fpurge(stdin);
				resp = getchar();
			}

		fclose(slv);
}

void continuar_cadastro(){

		FILE *slv = fopen("salvos.txt", "a+");

		Clubes info;

		int i = 0;

		char resp, *str;

			info.nomeClube = malloc(80 * sizeof(char));	
			info.cid = malloc(80 * sizeof(char));	
			info.est = malloc(80 * sizeof(char));	
			info.arena = malloc(80 * sizeof(char));	
			str = malloc(80 * sizeof(char));	


			while(fgets(str,80, slv)!=NULL){
				i++;
			}

			i = i/4;

			

			for(; i < 20 && resp != 'n'; i++){
			system("clear");
			printf("\t\tCADASTRO DE CLUBES\n");
			COR_BRANCO
			printf("Digite o clube : ");
			COR_VERDE
			info.nomeClube = scanfx(); 
			COR_BRANCO
			printf("Digite a cidade: ");
			COR_VERDE
			info.cid = scanfx();
			COR_BRANCO
			printf("Digite o estado: ");
			COR_VERDE
			info.est = scanfx();
			COR_BRANCO
			printf("Digite o estadio: ");
			COR_VERDE
			info.arena = scanfx();

			fprintf(slv, "%s\n%s\n%s\n%s\n", info.nomeClube, info.cid, info.est, info.arena);

			printf("CONTINUAR? S/N\n");
			__fpurge(stdin);
			resp = getchar();
		}

		fclose(slv);
}
void ranking(){

	srand(time(NULL));
	Ranking r[20], a;
	Jogo vet[190];
	int fase[20][20], flag, i, j, aux;
	
	for(i = 0; i < 20; i++){
		for(j = 0; j < 20;j++){
			fase[i][j] = 0;
		}
	}
	for(i = 0; i < 20;i++){
			r[i].pontos = 0;
			r[i].jogos = 0;
			r[i].vit = 0;
			r[i].emp = 0;
			r[i].der = 0;
			r[i].gp = 0;
			r[i].gc = 0;
			r[i].sg = 0;
		}

	for(i = 0; i < 190; i++){
		vet[i].golA = rand()%10;
		vet[i].golB = rand()%10;
		vet[i].cartAmarA = rand()%10;
		vet[i].cartVermA = rand()%30/10;
		vet[i].cartAmarB = rand()%10;
		vet[i].cartVermB = rand()%30/10;
		
		flag = 0;
		while(flag == 0){
		vet[i].casa = rand()%20;
		vet[i].visit = rand()%20;

			if(fase[vet[i].casa][vet[i].visit] != 1 && vet[i].casa != vet[i].visit){
				fase[vet[i].casa][vet[i].visit] = 1;
				fase[vet[i].visit][vet[i].casa] = 1;
				flag = 1;
			}
		}

	}
	for(i = 0; i < 190; i++){
		if(vet[i].golA > vet[i].golB){
			r[vet[i].casa].pontos += 3;
			r[vet[i].casa].vit++;
			r[vet[i].casa].jogos++;
			r[vet[i].casa].gp += vet[i].golA;
			r[vet[i].casa].gc += vet[i].golB;
			r[vet[i].casa].sg = r[vet[i].casa].gp - r[vet[i].casa].gc;

			r[vet[i].visit].der++;
			r[vet[i].visit].jogos++;
			r[vet[i].visit].gp += vet[i].golB;
			r[vet[i].visit].gc += vet[i].golA;
			r[vet[i].visit].sg = r[vet[i].visit].gp - r[vet[i].visit].gc;
		}
		else if(vet[i].golA = vet[i].golB){
			r[vet[i].casa].pontos++;
			r[vet[i].casa].emp++;
			r[vet[i].casa].jogos++;
			r[vet[i].casa].gp += vet[i].golA;
			r[vet[i].casa].gc += vet[i].golB;
			r[vet[i].casa].sg = r[vet[i].casa].gp - r[vet[i].casa].gc;

			r[vet[i].visit].pontos++;
			r[vet[i].visit].emp++;
			r[vet[i].visit].jogos++;
			r[vet[i].visit].gp += vet[i].golB;
			r[vet[i].visit].gc += vet[i].golA;
			r[vet[i].visit].sg = r[vet[i].visit].gp - r[vet[i].visit].gc;
		}
		else{

			r[vet[i].visit].pontos += 3;
			r[vet[i].visit].vit++;
			r[vet[i].visit].jogos++;
			r[vet[i].visit].gp += vet[i].golA;
			r[vet[i].visit].gc += vet[i].golB;
			r[vet[i].visit].sg = r[vet[i].visit].gp - r[vet[i].visit].gc;

			r[vet[i].casa].der++;
			r[vet[i].casa].jogos++;
			r[vet[i].casa].gp += vet[i].golB;
			r[vet[i].casa].gc += vet[i].golA;
			r[vet[i].casa].sg = r[vet[i].casa].gp - r[vet[i].casa].gc;
		}


		system("clear");
			printf("J\tP\tV\tE\tD\tGP\tGC\tSG\n");

		for(j = 0; j <= 10; j++){
			printf("%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n", r[j].jogos, r[j].pontos, r[j].vit, r[j].emp, r[j].der, r[j].gp, r[j].gc, r[j].sg);
		}
		getchar();
	}

	for(i = 0; i < 190; i++){
		vet[i].golA = rand()%10;
		vet[i].golB = rand()%10;
		vet[i].cartAmarA = rand()%10;
		vet[i].cartVermA = rand()%30/10;
		vet[i].cartAmarB = rand()%10;
		vet[i].cartVermB = rand()%30/10;
	}
	for(i = 0; i < 190; i++){

		aux = vet[i].casa;
		vet[i].casa = vet[i].visit;
		vet[i].visit = aux;

	}
	for(i = 0; i < 190; i++){
		if(vet[i].golA > vet[i].golB){
			r[vet[i].casa].pontos += 3;
			r[vet[i].casa].vit++;
			r[vet[i].casa].jogos++;
			r[vet[i].casa].gp += vet[i].golA;
			r[vet[i].casa].gc += vet[i].golB;
			r[vet[i].casa].sg = r[vet[i].casa].gp - r[vet[i].casa].gc;

			r[vet[i].visit].der++;
			r[vet[i].visit].jogos++;
			r[vet[i].visit].gp += vet[i].golB;
			r[vet[i].visit].gc += vet[i].golA;
			r[vet[i].visit].sg = r[vet[i].visit].gp - r[vet[i].visit].gc;
		}
		else if(vet[i].golA = vet[i].golB){
			r[vet[i].casa].pontos++;
			r[vet[i].casa].emp++;
			r[vet[i].casa].jogos++;
			r[vet[i].casa].gp += vet[i].golA;
			r[vet[i].casa].gc += vet[i].golB;
			r[vet[i].casa].sg = r[vet[i].casa].gp - r[vet[i].casa].gc;

			r[vet[i].visit].pontos++;
			r[vet[i].visit].emp++;
			r[vet[i].visit].jogos++;
			r[vet[i].visit].gp += vet[i].golB;
			r[vet[i].visit].gc += vet[i].golA;
			r[vet[i].visit].sg = r[vet[i].visit].gp - r[vet[i].visit].gc;
		}
		else{

			r[vet[i].visit].pontos += 3;
			r[vet[i].visit].vit++;
			r[vet[i].visit].jogos++;
			r[vet[i].visit].gp += vet[i].golA;
			r[vet[i].visit].gc += vet[i].golB;
			r[vet[i].visit].sg = r[vet[i].visit].gp - r[vet[i].visit].gc;

			r[vet[i].casa].der++;
			r[vet[i].casa].jogos++;
			r[vet[i].casa].gp += vet[i].golB;
			r[vet[i].casa].gc += vet[i].golA;
			r[vet[i].casa].sg = r[vet[i].casa].gp - r[vet[i].casa].gc;
		}
		system("clear");
			printf("J\tP\tV\tE\tD\tGP\tGC\tSG\n");

		for(j = 0; j <= 10; j++){
			printf("%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n", r[j].jogos, r[j].pontos, r[j].vit, r[j].emp, r[j].der, r[j].gp, r[j].gc, r[j].sg);
		}
		getchar();

		for(i = 0; i < 20; i++){
			for(j = i; j < 20;j++){
				if(r[i].pontos < r[j].pontos){
					a = r[i];
					r[i] = r[j];
					r[j] = a;
				}
				else if(r[i].pontos == r[j].pontos){
					if(r[i].sg < r[j].sg){
						a = r[i];
						r[i] = r[j];
						r[j] = a;
					}
					else if(r[i].sg == r[j].sg){
						if(r[i].gp < r[j].gp){
							a = r[i];
							r[i] = r[j];
							r[j] = a;
						}
						else if(r[i].gp == r[j].gp){
							
						}
					}
				}
			}
		}
	}
}