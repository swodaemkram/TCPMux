/*
============================================================================
 Name        : TCPMux.c
 Author      : Mark Meadows
 Version     :v 0.10.0
 Copyright   : Your copyright notice
 Description : TCPMux in C, Ansi-style
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>

#define BUFLEN 1024
#define VER "v 0.11.0\n"

void help(); /* print help */

int main(int argc, char *argv[]) {
char SERVER1[21] = {0}; /*Blank these variables*/
char SERVER2[21] = {0}; /*Blank these variables*/
char SERVER3[21] = {0}; /*Blank these variables*/
char SERVER4[21] = {0}; /*Blank these variables*/
char  IN_PORT[5] = {0}; /*Blank these variables*/
int PORT1;
int PORT2;
int PORT3;
int PORT4;
/*
=============================================================================
Load Command line arguments
=============================================================================
 */

	int z;
	for (z=1; z < argc; z++)
		{
			if (argv[z][0] == '-')

			{
				switch (argv[z][1])

				{

				case 'P' :

					strcpy(IN_PORT, argv[z+1]);
					break;

				case '1':

					strcpy(SERVER1, argv[z+1]);
					break;

				case '2' :

					strcpy(SERVER2, argv[z+1]);
					break;

				case '3' :

					strcpy(SERVER3, argv[z+1]);
					break;

				case '4' :

					strcpy(SERVER4, argv[z+1]);
					break;

				case 'h' :
				   help();
					break;

				case 'H' :
				   help();
				    break;

				}

			}

		}


/*
=============================================================================
Command line arguments Loaded
=============================================================================
=============================================================================
 Simple Error Checking
=============================================================================
*/
	if(strlen(IN_PORT) < 2) {
		help();
	}

	if(strlen(SERVER1) < 7){
		help();
	}

	if (strlen(SERVER2) < 7){
		help();
	}

	if (strlen(SERVER3) < 9){
		strcpy(SERVER3,"0.0.0.0:0");
	}

	if (strlen(SERVER4) < 9){
		strcpy(SERVER4,"0.0.0.0:0");
	}
/*
==============================================================================
 End of Simple Error Checking
==============================================================================
==============================================================================
Lets Detach the ports from the IPs
==============================================================================
*/
	PORT1 = atoi(strchr(SERVER1,':') +1);
    PORT2 = atoi(strchr(SERVER2,':') +1);

    if (strlen(SERVER3) >=7){
        	PORT3 = atoi(strchr(SERVER3,':') +1);
    }

    if (strlen(SERVER4) >=7){
    PORT4 = atoi(strchr(SERVER4,':') +1);
    }

	const char s[2] = ":";
	char *HOST1;
	char *HOST2;
	char *HOST3;
	char *HOST4;

	HOST1 = strtok(SERVER1,s);
	HOST2 = strtok(SERVER2,s);
	if (strlen(SERVER3) >= 7){
		HOST3 = strtok(SERVER3,s);
	}

	if (strlen(SERVER4) >= 7){
		HOST4 = strtok(SERVER4,s);
	}
/*
==============================================================================
Done with Detaching Ports
==============================================================================
==============================================================================
This is what we are working with let's print it
==============================================================================
*/
	printf("\n");
	printf("IN_PORT = %s\n",IN_PORT);
	printf("HOST1 = %s:%i\n",HOST1,PORT1);
	printf("HOST2 = %s:%i\n",HOST2,PORT2);
	printf("HOST3 = %s:%i\n",HOST3,PORT3);
	printf("HOST4 = %s:%i\n",HOST4,PORT4);
	printf("\n");

/*
==============================================================================
Lets Figure out were we are sending things
==============================================================================
*/
int HOST3_USED = {0};
int HOST4_USED = {0};

if (atoi(HOST3) > 1 ){
	HOST3_USED = 1;
}

if (atoi(HOST4) > 1 ){
	HOST4_USED = 1;
}
/*
==============================================================================
Now we know who we are sending things to
==============================================================================
==============================================================================
Lets setup the server side and wait for a connection
==============================================================================
*/

	int socket_desc , client_sock , c , read_size;
		struct sockaddr_in server , client;
		char client_message[2000];

	    //Create socket
		socket_desc = socket(AF_INET , SOCK_STREAM , 0);
		if (socket_desc == -1)
		{
			printf("Could not create socket");
		}
		puts("Socket created");


		//Prepare the sockaddr_in structure
			server.sin_family = AF_INET;
			server.sin_addr.s_addr = INADDR_ANY;
			server.sin_port = htons( atoi(IN_PORT) );

		//Bind
			if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
			{
				//print the error message
				perror("bind failed. Error");
				return 1;
			}
			puts("bind done");

			//Listen
				listen(socket_desc , 3);

			//Accept and incoming connection
			puts("Waiting for incoming connections...");
			c = sizeof(struct sockaddr_in);

			//accept connection from an incoming client
			client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
			if (client_sock < 0)
			{
				perror("accept failed");
				return 1;
			}
			puts("Connection accepted");


			//Receive a message from client
				while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
				{
					//Send the message back to client
					write(client_sock , client_message , strlen(client_message));
				}

				if(read_size == 0)
				{
					puts("Client disconnected");
					fflush(stdout);
				}
				else if(read_size == -1)
				{
					perror("recv failed");
				}

				return 0;
			}

/*
===============================================================================
 Lets setup The client sides now
===============================================================================
*/

















/*
================================================================================
The end of the program
================================================================================
*/

/*
==============================================================================
Help Function
==============================================================================
*/

void help(void){
	printf("\n");
	printf("     TCPMux by Mark Meadows %s \n", VER);
	printf("     a command line TCP Multiplexer\n");
	printf(" There must be a minimum of two host being relayed to\n" );
	printf(" -P, port of incoming TCP connection \n");
	printf(" -1, first ip address and port for outgoing connection\n");
	printf(" -2, second ip address and port for outgoing connection\n");
	printf(" -3, third ip address and port for outgoing connection\n");
	printf(" -4, forth ip address and port for outgoing connection\n");
	printf(" -h, this help information");
	printf("\n\n");
	printf("  Example usage: TCPMux -P 8080 -1 192.168.1.12:8081 -2 192.168.1.10:8082 -3 192.168.1.11:8083 -4 192.168.1.13:8084\n\n");
	exit(0);

}
