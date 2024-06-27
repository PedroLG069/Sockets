#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX 100
#define SA struct sockaddr

void enviarInstruccion(int miSocket, char *instruccion){
	char buff[MAX], res[MAX];
	
	strcpy(buff, instruccion);
	
	write(miSocket, buff, sizeof(buff));
	
	strcpy(buff, "                        ");        
	read(miSocket, buff, sizeof(buff));
	strcpy(res, buff);
	
	printf("\n\tResultado = %s\n", res);
}

int main(int argc, char *argv[]){
	int miSocket;
	int puerto = 1024;
	struct sockaddr_in dirServ;
	char opcion[2];

	int continuar = 1;
	while(continuar == 1){
		miSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (miSocket == -1) {
			printf("ERROR: No se pudo crear el socket.\n");
			exit(0);
		}
			
		bzero(&dirServ, sizeof(dirServ));

		dirServ.sin_family = AF_INET;
		dirServ.sin_addr.s_addr = inet_addr("127.0.0.1");
		dirServ.sin_port = htons(puerto);
		if (connect(miSocket, (SA*)&dirServ, sizeof(dirServ)) != 0) {
			printf("ERROR: No se pudo conectar con el servidor.\n");
			exit(0);
		}
		
		printf("\n1. Suma\n2. Resta\n3. Multiplicacion\n4. Division\n5. Salir\n> Seleccione una opcion: ");
		scanf("%s", opcion);
		
		if(strcmp(opcion, "5") == 0){
			close(miSocket);
			break;
		}
		
		char num1[MAX];
		printf("\tNumero 1: ");
		scanf("%s", num1);
		
		char num2[MAX];
		printf("\tNumero 2: ");
		scanf("%s", num2);
		
		char separador[2];
		strcpy(separador," ");
		
		char instruccion[MAX];
		strcat(strcpy(instruccion, opcion), separador);
		strcat(instruccion, num1);
		strcat(instruccion, separador);
		strcat(instruccion, num2);		
		strcat(instruccion, separador);
		enviarInstruccion(miSocket, instruccion);
		
		close(miSocket);		
		
		while ( getchar() != '\n')
		;
	}
}
