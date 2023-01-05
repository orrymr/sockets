#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main(){

		// https://www.youtube.com/watch?v=LtXEMwSG5-8
		// let's create a client socket (one side of network comms)
		// create a socket
		// first parameter - AF_INET (it's an internet socket). This is the "domain"
		// SOCK_STREAM - a TCP socket (not UDP)
		int network_socket;
		network_socket = socket(AF_INET, SOCK_STREAM, 0); // This creates the network socket

		// need to call connect() to connect to another side of network comms.
		// Before we can call connect(), we need to specify an address to connect to. netinet/in.h for creating address
		// specify an address for the socket:
		struct sockaddr_in server_address;
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(9002);
		server_address.sin_addr.s_addr = INADDR_ANY; //connects to local

		int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
		// connect returns an int telling us if connection was success or no
		if (connection_status == -1) {
				printf("There was an error making a connection to remote socket \n\n");
		}

		// Next thing to do once we have the connection is to send/ receive data.
		// Let's receive 
		char server_response[256];
		recv(network_socket, &server_response, sizeof(server_response), 0); // data we get back from server will end up in "server_response"

		// print out the server's response
		printf("The server sent the data: %s", server_response);	
		close(network_socket);


		return 0;
}
