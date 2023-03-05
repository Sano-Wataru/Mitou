#include "../header/gb_common.h"
#include "../header/gb_client.h"

void connectSocketClient(const int sockfd, const struct sockaddr_in serv)
{
  char buf[BUFSIZ];
  memset(buf, 0, BUFSIZ);

  if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
  {
    perror("connect");
    exit(1);
  }

  printf("connected to server\n");
  serverInfo();

  // operation explanation
  printf("\n");
  printf("-------------------------\n");
  printf("\x1b[36;1mup:   \x1b[0mupload items\n");
  printf("\x1b[36;1mdown: \x1b[0mdownload items\n");
  printf("\x1b[36;1mlist: \x1b[0mview item list\n");
  printf("\x1b[36;1mexit: \x1b[0mend this session\n");
  printf("-------------------------\n\n");

  // get user ID
  printf("\x1b[32;1mPlease input the command...\n\x1b[0m");
  while (strncasecmp(buf, "exit\n", 5) != 0)
  {
    printf("==> ");

    if ((fgets(buf, BUFSIZ, stdin)) < 0)
    {
      perror("fgets");
      exit(1);
    }
    // send command
    send(sockfd, buf, strlen(buf), 0);

    controlTask(sockfd, buf);
    printf("<== %s\n", buf);
  }

  close(sockfd);
}

// perform tasks in response to commands from the server
void controlTask(const int sockfd, char *msg)
{
  enum control c;

  // receive command analysis result
  recv(sockfd, &c, BUFSIZ, 0);

  switch(c)
  {
    case cup:
      updateTask(sockfd, msg);
      break;
    case conlyup:
      oupdateTask(sockfd, msg);
      break;
    case clist: 
      listTask(sockfd, msg);
      break;
    case cnofile:
      // print out command line
      strcpy(msg, "No such file or directory");
      break;
    case cdown:
      downloadTask(sockfd, msg);
      break;
    case conlydown:
      odownloadTask(sockfd, msg);
      break;
    case cexit:
      exitTask(sockfd);
      break;
    case cother:
      otherTask(sockfd, msg);
      break;
    default:
      break;
  }
}

void oupdateTask(const int sockfd, char *msg)
{
  // declaration
  char path[BUFSIZ];
  enum control c;

  // init buffer
  memset(path, 0, BUFSIZ);

  printf("Please input the file path: ");
      
  if ((fgets(path, BUFSIZ, stdin)) < 0)
  {
    perror("fgets");
    exit(1);
  }
  // remove line breaks
  path[strlen(path) - 1] = '\0';

  // send inputted path to the server
  printf(" Sending entered path...\n");
  send(sockfd, path, strlen(path), 0);
  printf(" Sended entered path\n");

  controlTask(sockfd, msg);
}

void updateTask(const int sockfd, char *msg)
{
  char path[BUFSIZ];
  char buf[BUFSIZ];
  int len;

  // init buffer
  memset(path, 0, BUFSIZ);
  memset(buf, 0, BUFSIZ);

  printf("\x1b[32;1mUploading the file...\x1b[0m\n");
  // receive the path from the server
  len = recv(sockfd, path, BUFSIZ, 0);
  path[len] = '\0';
  printf(" Received path \"%s\"\n", path);

  // read file from client directory
  printf(" Reading data \"%s\"\n", path);
  if (readFile(path, buf) < 0)
  {
    // error process
    printf(" Informing error to the server\n");
    strncpy(buf, "nofile", 7);
    send(sockfd, buf, strlen(buf), 0);

    strncpy(msg, "Failured upload the file...", 28);
  }
  else
  {
    // send data to the server
    printf(" Sending data...\n");
    send(sockfd, buf, strlen(buf), 0);

    // print out command line
    strncpy(msg, "Uploaded the file!", 19);
  }
}

void odownloadTask(const int sockfd, char *msg)
{
  // declaration
  char path[BUFSIZ];
  char times[BUFSIZ];
  char cpath[BUFSIZ];
  enum control c;

  // init buffer
  memset(path, 0, BUFSIZ);
  memset(times, 0, BUFSIZ);
  memset(cpath, 0, BUFSIZ);

  printf("Please enter the \"from\" file path: ");
      
  if ((fgets(path, BUFSIZ, stdin)) < 0)
  {
    perror("fgets");
    exit(1);
  }
  // remove line breaks
  path[strlen(path) - 1] = '\0';

  // send entered path to the server
  printf(" Sending entered \"from\" path...\n");
  send(sockfd, path, strlen(path), 0);
  printf(" Sended entered \"from\" path\n");


  printf("Please enter the timestamp: ");
      
  if ((fgets(times, BUFSIZ, stdin)) < 0)
  {
    perror("fgets");
    exit(1);
  }
  // remove line breaks
  times[strlen(times) - 1] = '\0';

  // send entered path to the server
  printf(" Sending entered timestamp...\n");
  send(sockfd, times, strlen(times), 0);
  printf(" Sended entered timestamp\n");


  printf("Please enter the \"to\" file path: ");
      
  if ((fgets(cpath, BUFSIZ, stdin)) < 0)
  {
    perror("fgets");
    exit(1);
  }
  // remove line breaks
  cpath[strlen(cpath) - 1] = '\0';

  // send entered path to the server
  printf(" Sending entered \"to\" path...\n");
  send(sockfd, cpath, strlen(cpath), 0);
  printf(" Sended entered \"to\" path\n");

  controlTask(sockfd, msg);
}

void downloadTask(const int sockfd, char *msg)
{
  char path[BUFSIZ];
  char buf[BUFSIZ];
  int len;

  memset(path, 0, BUFSIZ);
  memset(buf, 0, BUFSIZ);

  printf("\x1b[32;1mDownloading the stored file in the server...\x1b[0m\n");

  // reveiving path from the server
  len = recv(sockfd, path, BUFSIZ, 0);
  path[len] = '\0';
  printf(" Received path \"%s\"\n", path);

  printf(" Receiving data...\n");
  len = recv(sockfd, buf, BUFSIZ, 0);
  buf[len] = '\0';

  if (strncmp(buf, "nofile", 6) == 0)
  {
    printf(" \x1b[31mServer error, \"No such file or directory\"[x1b[0m");
    printf(" Stopped task and process\n");
  }
  else
  {
    writeFile(path, buf);

    strncpy(msg, "Download the file!", 19);
  }
}

void listTask(const int sockfd, char *msg)
{
  char buf[BUFSIZ];

  // init buffer
  memset(buf, 0, BUFSIZ);

  printf("\x1b[32;1mListing the stored file in the server...\x1b[0m\n");

  // receive information from the server
  recv(sockfd, buf, BUFSIZ, 0);
  if (strncmp(buf, "nofile", 6) == 0)
  {
    printf(" \x1b[31mServer error, \"No such file or directory\"[x1b[0m");
    printf(" Stopped task and process\n");
  }
  else
  {
    // print information
    printf("%s\n", buf);

    // print out command line
    strncpy(msg, "Listing information stored to the server!", 42);
  }
}

void exitTask(const int sockfd)
{
  printf(" Disconnect from the server...\n");
  exit(1);
}

void otherTask(const int sockfd, char *msg)
{
  strcpy(msg, "Invalid command...");
}
