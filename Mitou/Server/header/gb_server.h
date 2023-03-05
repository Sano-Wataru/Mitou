#ifndef SERVER_H
#define SERVER_H

// Macro definition ---------------------------------------
#define SERVER_DATA "./data/server_data.txt"
#define CLIENT_DATA "./data/clients/"
#define DATA_INFO "./data/data_info.txt"

// include libraries --------------------------------------

// Prototype declaration ----------------------------------
void connectSocketServer(const int, const struct sockaddr_in);
enum control commandOrder(const int, const char *);

enum control oupdateTask(const int, char *);
enum control updateTask(const int, char *);
enum control listTask(const int);
enum control odownloadTask(const int, char *);
enum control downloadTask(const int, char *);
enum control exitTask(const int);
enum control otherTask(const int);

int writeInfo(char *);
void attachTS(char *);
void getTSpath(char *, char *);
void listFile();

int strlenes(const char *);

// --------------------------------------------------------
#endif
