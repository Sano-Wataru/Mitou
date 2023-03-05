#include "../header/gb_common.h"
#include "../header/gb_client.h"

int main()
{
  int sockfd;
  struct sockaddr_in serv;
  char addr[16];
  char port[7];

  printf("\x1b[1;32m");
  printf("Please input IP address and port...\n");
  inputServer(addr, port);

  printf("\n\n");
  printf("\x1b[1;32m");
  printf("connected to the server...\n");
  printf("\x1b[0m");

  setServerAddress(inet_ntoa(getAddress(ADDR)));
  setServerPort(port);

  createSocket(getServerAddress(), getServerPort(), &sockfd, &serv);
  connectSocketClient(sockfd, serv);
}

