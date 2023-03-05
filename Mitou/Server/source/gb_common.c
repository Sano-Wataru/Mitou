#include "../header/gb_common.h"
#include <netdb.h>

// Global variable ----------------------------------------
static struct in_addr g_addr;
static u_short g_port;

// Function declaration -----------------------------------

void inputServer(char *addr, char *port)
{
  printf("\x1b[36m");
  printf("address: ");
  printf("\x1b[0m");
  if (fgets(addr, BUFSIZ, stdin) < 0)
  {
    perror("fgets");
    exit(1);
  }

  addr[strlen(addr) - 1] = '\0';

  printf("\x1b[1;36m");
  printf("port: ");
  printf("\x1b[0m");
  if (fgets(port, BUFSIZ, stdin) < 0)
  {
    perror("fgets");
    exit(1);
  }

  port[strlen(port) - 1] = '\0';
}

struct in_addr getServerAddress()
{
  return g_addr;
}

void setServerAddress(const char *addr)
{
  // convert internet address format into binary
  inet_aton(addr, &g_addr);
}

u_short getServerPort()
{
  return g_port;
}

void setServerPort(const char *port)
{
  int p;
  p = strtol(port, NULL, 10);
  g_port = htons(p);
}

struct in_addr getAddress(const char* hostname)
{
  struct addrinfo hints, *res;
  struct in_addr addr;
  int err;

  // init hints
  memset(&hints, 0, sizeof(hints));

  // indicate the socket type
  hints.ai_socktype = SOCK_STREAM;
  // set address family (IPv4)
  hints.ai_family = AF_INET;

  if ((err = getaddrinfo(hostname, NULL, &hints, &res)) != 0)
  {
    fprintf(stderr, "error %d\n", err);
    exit(1);
  }

  // get in_addr from addrinfo
  addr.s_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.s_addr;

  // free up addrinfo
  freeaddrinfo(res);

  return addr;
}

int readFile(const char *path, char *ret)
{
  FILE *fp;
  char buf[BUFSIZ];
  memset(buf, 0, BUFSIZ);

  if ((fp = fopen(path, "r")) == NULL)
  {
    perror("file");
    return -1;
  }

  while (fgets(buf, BUFSIZ, fp))
    strcat(ret, buf);
  
  fclose(fp);

  return 0;
}

int writeFile(const char *path, char *cont)
{
  FILE *fp;
  
  if ((fp = fopen(path, "w")) == NULL)
  {
    perror("file");
    return -1;
  }

  fputs(cont, fp);

  fclose(fp);

  return 0;
}

int copyFile(const char *from, const char *to)
{
  char buf[BUFSIZ];
  memset(buf, 0, BUFSIZ);

  if (readFile(from, buf) < 0)
    return -1;

  if (writeFile(to, buf) < 0)
    return -1;
  
  return 0;
}

void createSocket(const struct in_addr addr, const u_short port, 
                  int *sockfd, struct sockaddr_in *serv)
{
  if ((*sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("socket");
    exit(1);
  }
  calledMsg("Socket");

  // init socket (set address and port to socket)
  setSocket(addr, port, serv);
}

void setSocket(const struct in_addr addr, const u_short port, 
               struct sockaddr_in *serv)
{
  // define p for converting port string to integer

  serv->sin_family = PF_INET;
  serv->sin_port = port;
  serv->sin_addr = addr;
}

void serverInfo()
{
  printf("\x1b[1;33m");
  printf("----------\n");
  printf("\x1b[1;36m");
  printf("address: \x1b[0m%s\n", inet_ntoa(getServerAddress()));
  printf("\x1b[1;36m");
  printf("port: \x1b[0m%d\n", htons(getServerPort()));
  printf("\x1b[1;33m");
  printf("----------\n\n");
  printf("\x1b[0m");
}

void calledMsg(char *str)
{
  printf("%s \x1b[32;1mcalled\x1b[0m\n", str);
}

void pathFile(char *path, char *file)
{
  char ptmp[strlen(path)];
  strcpy(ptmp, path);
  char *token = strtok(ptmp, "/");
  char *ptoken;

  while (token != NULL)
  {
      ptoken = token;
      token = strtok(NULL, "/");
  }  
  strcpy(file, ptoken);
}

void infoMsg(char *msg, enum information info)
{
  switch(info)
  {
    case task:
      printf("[TASK] %s\n", msg);
      break;
    case progress:
      printf("\x1b[94m[PROGRESS] %s\x1b[0m\n", msg);
      break;
    case complete:
      printf("\x1b[94m[COMPLETE] %s\n\x1b[0m", msg);
      break;
    case warning:
      printf("\x1b[93m[WARNING] %s\n\x1b[0m", msg);
      break;
    case error:
      printf("\x1b[91m[ERROR] %s\n\x1b[0m", msg);
      break;
  }
}
