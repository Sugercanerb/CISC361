
#include "get_path.h"

int pid;
int sh( int argc, char **argv, char **envp);
char *which(char *command, struct pathelement *pathlist);
char *where(char *command, struct pathelement *pathlist);
void list ( char *dir);
void lista(char *dir, char* wildcard);
void printenv(char **envp);
int myHash(char *command);
char** spilit(char *command);
void mykill(int code, int pid);
void freePathlist(struct pathelement *pathlist);

#define PROMPTMAX 32
#define MAXARGS 10
#define BUFF 256
int n;
