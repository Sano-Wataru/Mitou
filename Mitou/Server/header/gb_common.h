#ifndef COMMON_H
#define COMMON_H

// Macro definition ---------------------------------------
#define ADDR "yli003.sic.shibaura-it.ac.jp" // for test

// include libraries --------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <sys/stat.h>

// Enum declaration
enum control
{ 
  cup, conlyup, cdown, conlydown, clist, cexit, cnofile,
  cother 
};

enum information
{
  task, progress, complete, warning, error
};

// Global variables ---------------------------------------

// Prototype declaration ----------------------------------
struct in_addr getServerAddress();
void setServerAddress(const char*);
u_short getServerPort();
void setServerPort(const char*);
struct in_addr getAddress(const char*);

void inputServer(char*, char*);
// void writeServerData();
// void readServerData();

int readFile(const char *, char *);
int writeFile(const char *, char *);
int copyFile(const char *, const char *);
void pathFile(char *, char *);

void createSocket(const struct in_addr, const u_short, 
                  int*, struct sockaddr_in*);
void setSocket(const struct in_addr, const u_short, struct sockaddr_in*);

void serverInfo();
void calledMsg(char *);
void infoMsg(char *, enum information);

// --------------------------------------------------------
#endif
