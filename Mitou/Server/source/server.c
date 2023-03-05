#include "../header/gb_common.h"
#include "../header/gb_server.h"

int main(int argc, char *argv[])
{
  int sockfd;
  struct sockaddr_in serv;
  char addr[16];
  char port[7];

  printf("\x1b[1;32m");
  printf("Server startup...\n");

  inputServer(addr, port);

  printf("\n\n");
  printf("\x1b[1;32m");
  printf("Set up the server...\n");
  printf("\x1b[0m");

  // store the IP address of the host in the global variable
  // and write the IP address to a file
  setServerAddress(inet_ntoa(getAddress(addr)));  // convert in_addr to char*
  setServerPort(port); 

  serverInfo();

  createSocket(getServerAddress(), getServerPort(), &sockfd, &serv);
  connectSocketServer(sockfd, serv);
}
