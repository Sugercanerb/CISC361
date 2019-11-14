#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"
#include <wordexp.h>
#include <glob.h>
//#include <wordexp.h>

int sh( int argc, char **argv, char **envp )
{
  char *prompt = calloc(PROMPTMAX, sizeof(char));
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  char **args; //= calloc(MAXARGS, sizeof(char*));
  int uid, i, status, argsct, go = 1;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;
  uid = getuid();
  password_entry = getpwuid(uid);               /* get passwd info */
  homedir = password_entry->pw_dir;		/* Home directory to start
						  out with*/

  if ( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL )
  {
    perror("getcwd");
    exit(2);
  }
  owd = calloc(PATH_MAX + 1, sizeof(char));
  memcpy(owd, pwd, strlen(pwd));
  prompt[0] = ' '; prompt[1] = '\0';

  /* Put PATH into a linked list */
  pathlist = get_path();

  int code, flag = 0;
  char* cur;
  while ( go )
  {
	  printf("\033[1;32m");
	  printf("%s ", prompt); // printf prompt and cwd
	  printf("\033[0m");
	  printf("[%s]>", pwd);
	  n = 0;
	  char commandline[BUFF];
	  if(fgets(commandline, BUFF, stdin) == NULL)
	  {
		  printf("\n");
		  continue;
	  }
	  if(commandline[strlen(commandline - 1)] == '\n')
		  continue;
	  commandline[strlen(commandline) - 1] = '\0';
	  args = spilit(commandline);
	  if(args[0] == "")
		  continue;
	  code = myHash(args[0]);
	  n = n -1;

	  switch(code)
	  {
	  	  default:
	  		  command = which(args[0], pathlist);
	  		  cur = command;
	  		  if(command == NULL)
	  			  cur = args[0];
				  DIR *dr = opendir(cur);
	  			  if(access(cur, X_OK) == 0)
	  			  {
	  				 if(dr != NULL)
	  				 {
	  					 printf(" This is a absolute path \n");
	  					 if(command != NULL)
	  						 free(command);
	  					 free(dr);
	  					 free(args);
	  					 continue;
	  				 }
	  				  pid = fork();
	  				  if(pid == -1)
	  					  printf("error");
	  				  else if(pid == 0)
	  				  {
	  					  wordexp_t p;
	  					  char **w;
	  					  int i;
	  					  wordexp(args[0], &p, 0);
	  					  for(i = 1; i <= n; i++)
	  					  {
	  						  wordexp(args[i], &p, WRDE_DOOFFS | WRDE_APPEND);
	  					  }
	  					  w = p.we_wordv;

	  					  execvp(cur, w);
	  					wordfree(&p);
						  printf("error");
						  exit(1);
	  				  }
	  				  else if(pid > 0)
	  				  {
	  					  waitpid(pid, NULL, 0);
	  				  }
	  			  }
	  			  else
	  			  {
	  				  cur = strchr(args[0], '\n');
	  				  if(cur)
	  					  break;
	  				printf("command '%s' not found, enter 'help' for more information \n", args[0]);
	  			  }
	  			  if(command != NULL)
	  				  free(command);
	  			  break;
	  	  case 0:
	  		  printf("Executing built-in [%s]\n", args[0]);
	  		  go = 0;
	  		  break;
	  	  case 1:
	  		  if(n == 0)
	  		  {
	  			  printf("  without a path\n");
	  			  break;
	  		  }
	  		  else
	  		  {
			  		printf("Executing built-in [%s]\n", args[0]);
			  		while(n > 0){
			  			command = which(args[n], pathlist);
			  			n--;
			  			free(command);
			  		}
	  		  }
	  		  break;
	  	  case 2:
	  		if(n == 0)
	  		{
	  			printf("  without a path\n");
	  			break;
	  		}
	  		else
	  		{
		  		printf("Executing built-in [%s]\n", args[0]);
	  			while(n > 0)
	  			{
	  				where(args[n], pathlist);
	  				n--;
	  			}
	  		}
	  		break;
	  	  case 3:
	  		  printf("Executing built-in [%s]\n", args[0]);
	  		  if(n == 0)
	  			  chdir(homedir);
	  		  else if(n == 1 && (strcmp(args[1], "-") == 0))
	  			  chdir(owd);
	  		  else if(n == 1)
	  		  {
	  			if(chdir(args[1]) != 0 )
	  			{
	  				printf("no such repository");
	  				break;
	  			}
	  		  }
	  		  else if(n > 1)
	  		  {
	  			  printf("Too many arguments\n");
	  			  break;
	  		  }
	  		  strcpy(owd, pwd);
	  		  free(pwd);
	  		  if( (pwd = getcwd(NULL, PATH_MAX + 1)) == NULL)
	  		  {
	  			  perror("getcwd");
	  			  exit(2);
	  		  }
  			  break;
	  	  case 4:
	  		  printf("Executing built-in [%s]\n", args[0]);
	  		  printf("\033[1;35m");
	  		  if(n == 0)
	  			  printf("%s\n", pwd); //print current working directory
	  		  printf("\033[0m");
	  		  break;
	  	  case 5:
	  		  printf("Executing built-in [%s]\n", args[0]);
	  		  if(n == 0)
	  			  list(pwd);
	  		  else
	  		  {
	  			  for(int i = 1; i <= n; i++){
	  				  printf("_%s\n", args[i]);
	  				  list(args[i]);
	  			  }
	  		  }
	  		  break;
	  	  case 6:
	  		  printf("Executing built-in [%s]\n", args[0]);
	  		  printf("%ld \n", (long)getpid());
	  		  break;
	  	  case 7:
	  		  printf("Executing built-in [%s]\n", args[0]);
	  		  if(n == 1){
	  			  kill(atoi(args[1]), SIGTERM);
	  		  }
	  		  else if(n == 2)
	  		  {
	  			  if(strstr(args[1], "-") != NULL)
	  				  kill(atoi(args[2]), atoi(args[1] + 1));
	  		  }

	  		  break;
	  	  case 8:
	  		  printf("Executing built-in [%s]\n", args[0]);
	  		  if(n == 0){
	  			  printf("  input prompt prefix: hello \n");
	  			  args[0] == "hello";
		  		  strcpy(prompt, args[0]);
	  			  break;
	  		  }
	  		  strcpy(prompt, args[1]);
	  		  break;
	  	  case 9:
	  		  printf("Executing built-in [%s]\n", args[0]);
	  		  if(n == 0)
	  		  {
	  			 for (char **env = envp; *env != 0; env++)
	  			 {
	  			    char *thisEnv = *env;
	  			    printf("%s\n", thisEnv);
	  			 }
	  		  }
	  		  else if(n == 1)
	  			  if(getenv(args[1]) != NULL)
	  				  printf("%s\n", getenv(args[1]));
	  		  else
	  			  fprintf( stderr, " No PATH variable set.\n");
	  		  break;
	  	  case 10:
	  		  printf("Executing built-in [%s]\n", args[0]);
	  		  if(n == 0)
	  		  {
	  			for (char **env = envp; *env != 0; env++)
	  			{
	  				char *thisEnv = *env;
	  				printf("%s\n", thisEnv);
	  			}
	  		  }
	  		  else if(n == 1)
	  		  {
	  			  setenv(args[1], "", 1);
	  			  if(strcmp(args[1], "HOME") == 0)
	  				  homedir = ":";
	  			  else if(strcmp(args[1], "PATH") == 0)
	  			  {
	  				  freePathlist(pathlist);
	  				  free(removea);
	  				  pathlist = get_path();
	  			  }
	  		  }
	  		  else if(n == 2)
	  		  {
	  		  	  setenv(args[1], args[2], 1);
	  		  	  if(strcmp(args[1], "HOME") == 0)
	  		  		  homedir = args[2];
	  		  	  if(strcmp(args[1], "PATH") == 0)
	  		  	  {
	  		  		  freePathlist(pathlist);
	  		  		  free(removea);
	  		  		pathlist = get_path();
	  		  	  }
	  		  }
	  		  else
	  			  fprintf(stderr, " too many arguments for 'setenv'");
	  		  break;
	  	  case 12:
	  		  n = execve(args[0], argv, envp);
	  		  printf("%d", n);
	  		  printf("%s", args[0]);
	  		  break;
	  	  case 13:
	  		  printf("  exit - exit the program \n");
	  		  printf("  cd - to directory given \n");
	  		  printf("  pwd - print the current working directory \n");
	  		  printf("  list - list the files in the current working directory \n");
	  		  printf("  pid - prints the pid of shell \n");
	  		  printf("  kill - followed by pid - followed by one number and pid -- this will send the number to pid \n");
	  		  printf("  prompt - \n");
	  		  printf("  printenv - with no arguments, prints the whole enviroment - with one argument \n");
	  		  printf("  setenv - with no arguments, prints the whole enviroment \n");
	  		  break;
	  }
	  free(args);
  }
  // free function
  freePathlist(pathlist);
  free(removea);
  free(pwd);
  free(owd);
  free(prompt);
  return 0;
} /* sh() */

char *which(char *command, struct pathelement *pathlist )
{
   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */
	while(pathlist)
	{
		char* path = (char*) malloc(PATH_MAX+1);
		sprintf(path, "%s/%s", pathlist->element, command);
		if(access(path, X_OK) == 0)
		{
			printf("[%s]\n", path);
			return path;
		}
		free(path);
		pathlist = pathlist->next;
	}
	return NULL;
} /* which() */

char *where(char *command, struct pathelement *pathlist )
{
  /* similarly loop through finding all locations of command */
	while(pathlist)
	{
		char* path = (char*) malloc(PATH_MAX+1);
		sprintf(path, "%s/%s", pathlist->element, command);
		if(access(path, X_OK) == 0)
		{
			printf("[%s]\n", path);
		}
		free(path);
		pathlist = pathlist->next;
	}
	return NULL;
} /* where() */

void list (char *dir)
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
	struct dirent *de = NULL;

	DIR *dr = opendir(dir);
	if(dr == NULL)
	{
		printf("Could not open current directory\n");
		return;
	}
	while((de = readdir(dr)) != NULL)
		printf("%s\n", de->d_name);
	free(dr);
} /* list() */



//this funciton used to hash the command entered into integer
int myHash(char *command)
{
	int hashCode = -1;
	char curChar[128];
	strcpy(curChar, command);

	if(strcmp(curChar, "exit") == 0)
		hashCode = 0;
	else if(strcmp(curChar, "which") == 0)
		hashCode = 1;
	else if(strcmp(curChar, "where") == 0)
		hashCode = 2;
	else if(strcmp(curChar, "cd") == 0)
		hashCode = 3;
	else if(strcmp(curChar, "pwd") == 0)
		hashCode = 4;
	else if(strcmp(curChar, "list") == 0)
		hashCode = 5;
	else if(strcmp(curChar, "pid") == 0)
		hashCode = 6;
	else if(strcmp(curChar, "kill") == 0)
		hashCode = 7;
	else if(strcmp(curChar, "prompt") == 0)
		hashCode = 8;
	else if(strcmp(curChar, "printenv") == 0)
		hashCode = 9;
	else if(strcmp(curChar, "setenv") == 0)
		hashCode = 10;
	else if(strcmp(curChar, "help") == 0)
		hashCode = 13;
 	else
		hashCode = -1;
	return hashCode;

}
void freePathlist(struct pathelement *pathlist)
{
	 struct pathelement *tmpp;
	  while(pathlist != NULL)
	  {
		  tmpp = pathlist;
		  pathlist = pathlist->next;
		  free(tmpp);
	  }
}

// spilie string into arrays
char** spilit(char *command)
{
	char **res = NULL;
	char *token = strtok(command, " ");
	while(token)
	{
		res = realloc(res, sizeof(char*) *++n);
		if(res == NULL)
			exit(-1);

		res[n - 1] = token;
		token = strtok(NULL, " ");
	}
	if(res == NULL)
	{
		res = realloc(res, sizeof(char*) *++n);
		res[n -1] = " ";
	}
	res = realloc(res, sizeof(char *) *(n + 1));
	res[n] = '\0';
	return res;
}
