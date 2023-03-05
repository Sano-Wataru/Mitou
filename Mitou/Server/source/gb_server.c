// Include libraries --------------------------------------
#include "../header/gb_common.h"
#include "../header/gb_server.h"
#include <time.h>

// Function declaration -----------------------------------
void connectSocketServer(const int sockfd, const struct sockaddr_in serv)
{
  char buf[BUFSIZ];
  int new_sockfd, len;      // socket for holding client data
  socklen_t sin_siz;        // get s_socket size
  struct sockaddr_in clnt; 
  pid_t pid;

  if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
  {
    perror("bind");
    exit(1);
  }
  calledMsg("Bind");

  if (listen(sockfd, SOMAXCONN) < 0)
  {
    perror("listen");
    exit(1);
  }
  calledMsg("Listen");

  // wait for the server to connect with the client
  while (1)
  {
    // get client data and set to new_socket
    if ((new_sockfd = accept(sockfd, (struct sockaddr*)
      &clnt, &sin_siz)) < 0)
    {
      perror("accept");
    }

    if ((pid = fork()) < 0)
    {
      perror("pid");
      exit(1);  
    }

    // child process
    if (pid == 0)
    {
      // connected messege
      printf("\x1b[36;1mConnect from \x1b[0m%s: %d\n", 
      inet_ntoa(clnt.sin_addr), ntohs(clnt.sin_port));

      // init buffer
      memset(buf, 0, BUFSIZ);

      while (strncmp(buf, "exit\n", 5) != 0)
      {
        infoMsg("Waiting for the client order", task);

        // receive order from client
        len = recv(new_sockfd, buf, BUFSIZ, 0);
        // remove \n
        buf[len-1] = '\0';

        commandOrder(new_sockfd, buf);
        infoMsg("Client order completed", task);
      }

      // connection end
      printf("\x1b[36;1mConnection end from \x1b[0m%s: %d\n", 
      inet_ntoa(clnt.sin_addr), ntohs(clnt.sin_port));

      close(new_sockfd);
    }
    // parent process
    else
    {
      close(new_sockfd);
    }
  }
  close(sockfd);
}

enum control commandOrder(const int sockfd, const char *order)
{
  int n = strlenes(order);        // string size excluding space
  char torder[strlen(order)];     // copy order
  strcpy(torder, order);        
  char *token = strtok(torder, " ");

  // determine the order

  // in case only up
  if (n == 2 && strncmp(token, "up", 2) == 0)
    return oupdateTask(sockfd, token);

  // in case up ~
  else if (strncmp(token, "up", 2) == 0)
    return updateTask(sockfd, token);

  // in case only down
  else if (n == 4 && strncmp(token, "down", 4) == 0)
    return odownloadTask(sockfd, token);
  // in case down ~
  else if (strncmp(token, "down", 4) == 0)
    return downloadTask(sockfd, token);

  else if (strncmp(token, "list", 4) == 0)
    return listTask(sockfd);

  // in case exit
  else if (strncmp(token, "exit", 4) == 0)
    return exitTask(sockfd);
  // in case other
  else
    return otherTask(sockfd);
}

enum control oupdateTask(const int sockfd, char *token)
{
  enum control c;
  int len;
  char command[BUFSIZ];
  char path[BUFSIZ];

  memset(path, 0, BUFSIZ);
  memset(command, 0, BUFSIZ);

  strncpy(command, "up ", 4);

  // send result of command analysis
  c = conlyup;
  send(sockfd, &c, sizeof(enum control), 0);

  infoMsg("Upload task in only \"up\" input", task);

  printf(" Waiting for client input...\n");

  // get file path from the client
  len = recv(sockfd, path, BUFSIZ, 0);
  path[len] = '\0';

  printf(" Received path from clients \"%s\"\n", path);
  
  // combine "up" and file path from the client
  strncat(command, path, sizeof(char) * (strlen(command) + strlen(path) + 1));
  len = strlen(command);
  c = commandOrder(sockfd, command);
}

enum control updateTask(const int sockfd, char *token)
{
  enum control c;
  char path[BUFSIZ];                // for result path
  char cpath[BUFSIZ];               // client data directory path
  char *fname;
  char buf[BUFSIZ];                 // for receiving data from client
  
  memset(buf, 0, BUFSIZ);           // init buffer
  memset(path, 0, BUFSIZ);
  memset(cpath, 0, BUFSIZ);

  strncpy(cpath, CLIENT_DATA, sizeof(char) * (strlen(CLIENT_DATA) + 1));

  // send result of command analysis
  c = cup;
  send(sockfd, &c, sizeof(enum control), 0);

  // get path from token
  token = strtok(NULL, " ");
  printf(" Sending path \"%s\"...\n", token);
  // send path of the file to read
  send(sockfd, token, strlen(token), 0);

  infoMsg("Upload task", task);
  infoMsg("Receiving data from the client...", progress);

  // receive data from client
  recv(sockfd, buf, BUFSIZ, 0);

  // in case error
  if (strncmp(buf, "nofile", 6) == 0)
  {
    infoMsg("Client error, \"no such file or directory\"", error);
    printf(" Stopped task and process\n");
    return cnofile;
  }

  infoMsg("Received data from clients!", complete);

  // make directory for clients data
  if (mkdir(cpath, S_IRWXU) < 0)
    infoMsg("Make directory for clients data", task);
  else
    printf(" Already maded directory for clients data\n");

  infoMsg("Stores data from clients...", progress);

  // get file name from path
  fname = (char *)malloc(sizeof(char) * strlen(token));
  pathFile(token, fname);

  // attach time stamp
  strncpy(path, fname, sizeof(char) * (strlen(fname) + 1));
  attachTS(path);
  
  // join token to path => CLIENT_DATA + {client data path}
  strncat(cpath, path, sizeof(char) * (strlen(cpath) + strlen(path) + 1));

  printf(" Data from client is written...\n");
  printf(" client directory:%s => server directory:%s\n", token, path);
  
  // write client data to server directory
  printf("cpath=%s\n", cpath);
  writeFile(cpath, buf);

  infoMsg("Stored data from clients to the server!", complete);

  // write file information
  infoMsg("Writing the file information...", progress);
  writeInfo(token);
  infoMsg("Writing the file information completed!", complete);
  return cup;
}

enum control odownloadTask(const int sockfd, char *token)
{
  enum control c;
  int len;
  char command[BUFSIZ];
  char path[BUFSIZ];
  char times[BUFSIZ];
  char cpath[BUFSIZ];

  memset(path, 0, BUFSIZ);
  memset(times, 0, BUFSIZ);
  memset(command, 0, BUFSIZ);
  memset(cpath, 0, BUFSIZ);

  // send result of command analysis
  c = conlydown;
  send(sockfd, &c, sizeof(enum control), 0);

  infoMsg("Download task in only \"down\" input", task);

  printf(" Waiting for client input...\n");

  // get file path from the client
  printf(" Receiving \"from\" file path\n");
  len = recv(sockfd, path, BUFSIZ, 0);
  path[len] = '\0';

  printf(" Received \"from\" file path \"%s\"\n", path);

  // get timestamp from the client
  printf(" Receiving timestamp\n");
  len = recv(sockfd, times, BUFSIZ, 0);
  times[len] = '\0';

  printf(" Received timestamp from clients \"%s\"\n", times);

  // get timestamp from the client
  printf(" Receiving \"to\" file path\n");
  len = recv(sockfd, cpath, BUFSIZ, 0);
  times[len] = '\0';

  printf(" Received \"to\" file path \"%s\"\n", cpath);
  
  // combine "down", file path, and timestamp from the client
  snprintf(command, sizeof(char) * (8 + strlen(path) + strlen(times) + strlen(cpath)),
    "%s %s %s %s", "down", path, times, cpath);

  printf("command=%s\n", command);

  c = commandOrder(sockfd, command);
}

enum control downloadTask(const int sockfd, char *token)
{
  enum control c;
  char path[BUFSIZ];            // for sending path       
  char cpath[BUFSIZ];
  char buf[BUFSIZ];             // for receiving data from client

  memset(path, 0, BUFSIZ);
  memset(cpath, 0, BUFSIZ);
  memset(buf, 0, BUFSIZ);

  strncpy(cpath, CLIENT_DATA, sizeof(char) * (strlen(CLIENT_DATA) + 1));

  // send result of command analysis
  c = cdown;
  send(sockfd, &c, sizeof(enum control), 0);

  // get path from token
  token = strtok(NULL, " ");
  strncpy(path, token, sizeof(char) * (strlen(token) + 1));

  // get timestamp from token
  token = strtok(NULL, " ");

  if (token != NULL)
    // adding timestamp inputted to path
    getTSpath(path, token);
  else
    // adding the newest timestamp to path
    getTSpath(path, "new");

  // get distination path from token
  token = strtok(NULL, " ");

  printf(" Sending path \"%s\" to the client...\n", token);
  // send distination path to the client
  sleep(1);
  send(sockfd, token, sizeof(char) * strlen(token), 0);

  // adding directory paths
  strncat(cpath, path, 
    sizeof(char) * (strlen(cpath) + strlen(path) + 1));  
  strncpy(path, cpath, sizeof(char) * (strlen(path) + strlen(cpath) + 1));
  
  // reading data stored in the server directory
  printf(" Reading data \"%s\"\n", path);
  if (readFile(path, buf) < 0)
  {
    // error process
    infoMsg("Server error, \"no such file or directory\"", error);
    send(sockfd, "nofile", 6, 0);
    printf(" Stopped task and process\n");
    return cnofile;
  }
  else
  {
    // send data to the server
    infoMsg("Sending data to the client", progress);
    send(sockfd, buf, strlen(buf), 0);
    infoMsg("Sending data has been completed", complete);
  }

  infoMsg("Download task", task);

  return cdown;
}

enum control listTask(const int sockfd)
{
  enum control c;
  char buf[BUFSIZ];

  memset(buf, 0, BUFSIZ);

  // send result of command analysis
  c = clist;
  send(sockfd, &c, sizeof(enum control), 0);

  infoMsg("Listing task", task);

  infoMsg("Sending information to the client", progress);
  // get stored data information
  if (readFile(DATA_INFO, buf) < 0)
  {
    // error process
    infoMsg("Server error, \"no such file or directory\"", error);
    send(sockfd, "nofile", 6, 0);
    printf(" Stopped task and process\n");
    return cnofile;
  }
  else
  {
    // send information to the client
    send(sockfd, buf, BUFSIZ, 0);

    infoMsg("Information has been sent to the client", complete);
  }

  return clist;
}

enum control exitTask(const int sockfd)
{
  enum control c;

  // send result of command analysis
  c = cexit;
  send(sockfd, &c, sizeof(enum control), 0);

  infoMsg("Exit task", task);

  infoMsg("deconnecting from the client...", progress);
  
  infoMsg("deconnecting!", complete);

  return clist;
}

enum control otherTask(const int sockfd)
{
  enum control c;

  infoMsg("No such command", error);

  // send resutl of command analysis
  c = cother;
  send(sockfd, &c, sizeof(enum control), 0);

  return cother;
}

int writeInfo(char *path)
{
  FILE *fp;
  char pinfo[] = DATA_INFO;
  char fname[BUFSIZ];
  
  struct tm tm;
  time_t t = time(NULL);
  localtime_r(&t, &tm);

  // get file name
  pathFile(path, fname);
  
  if ((fp = fopen(pinfo, "a")) < 0)
  {
    perror("file");
    return -1;
  }

  fprintf(fp, "%s %04d%02d%02d%02d%02d%02d\n", fname,
    tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, 
    tm.tm_min, tm.tm_sec);

  fclose(fp);

  return 0;
}

void searchFile()
{

}

// strlen excluding space
int strlenes(const char *str)
{
  int i;
  int n = 0;
  for (i = 0; i < strlen(str); ++i)
  {
    if (str[i] != ' ')
      n++;
  }
  return n;
}

void attachTS(char *str)
{
  int i;
  bool c = false;
  char *rs = NULL;
  char *token = strtok_r(str, ".", &rs);
  char fname[BUFSIZ];
  char opt[BUFSIZ];
  char times[BUFSIZ];

  time_t t = time(NULL);
  struct tm tm;
  localtime_r(&t, &tm);

  memset(fname, 0, BUFSIZ);
  memset(opt, 0, BUFSIZ);
  memset(times, 0, BUFSIZ);

  // get file name and extension
  strncpy(fname, token, BUFSIZ);
  token = strtok_r(NULL, ".", &rs);
  strncpy(opt, token, BUFSIZ);

  // add a time stamp
  snprintf(times, BUFSIZ, 
    "%04d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, 
    tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  snprintf(str, BUFSIZ, 
    "%s_%s.%s", fname, times, opt);
}

void getTSpath(char *path, char *times)
{
  char *rs = NULL;

  // create copy path 
  char spath[strlen(path) + 1];
  strncpy(spath, path, sizeof(char) * (strlen(path) + 1));

  // get file name
  char *token = strtok_r(spath, ".", &rs);
  char fname[strlen(token) + 1];
  strncpy(fname, token, sizeof(char) * (strlen(token) + 1));

  // get extension
  token = strtok_r(NULL, ".", &rs);
  char opt[strlen(token) + 1];
  strncpy(opt, token, sizeof(char) * (strlen(token) + 1));

  snprintf(path, sizeof(char) * (strlen(fname) + 1 + 
    strlen(times) + 1 + strlen(opt) + 1), "%s_%s.%s", fname, times, opt);
}
