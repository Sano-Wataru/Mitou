#ifndef CLIENT_H_
#define CLIENT_H_

// Prototype declaration ----------------------------------
void connectSocketClient(const int, const struct sockaddr_in);
void controlTask(const int, char*);

void oupdateTask(const int, char *);
void updateTask(const int, char *);
void odownloadTask(const int, char *);
void downloadTask(const int, char *);
void listTask(const int, char *);
void exitTask(const int);
void otherTask(const int, char *);

// --------------------------------------------------------
#endif
