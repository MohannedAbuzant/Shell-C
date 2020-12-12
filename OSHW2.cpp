#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include "vector"
#include <iostream>
#include <fcntl.h> 
#include <unistd.h> 
using namespace std;



int main(int argc,char **argv){
	int  processList [100] ;
	int k=0;
    string l [99];	
    
    while(1){
   bool bg=false;
   char* Dist[50];
   bool red =false;
   bool inred=false;
   bool pFlag=false;
  
printf("$MohannedAbuzant \n");
char Location[50];
char UserInput[50];
char line[1000];
char* command_array[100];
printf("Please enter a command \n");
fgets(UserInput,sizeof(UserInput),stdin);
char *token = strtok(UserInput," \n");
char  *command[50];
memset( command, 0, sizeof(command) );
int pid;
int i=0;
while(token!=NULL){
	if(strcmp(strdup(token),"&")==0){
		bg=true;
		l[k]=command[0];
	
	}

    else if(strcmp(strdup(token),">")==0){
		 token=strtok(NULL," \n");
		 red =true;
		 Dist[0]=strdup(token);
		
	}
	 else if(strcmp(strdup(token),"<")==0){
		 
		 token=strtok(NULL," \n");
		 inred =true;
		 Dist[0]=strdup(token);
		
	}
	else if(strcmp(strdup(token),"|")==0){
		pFlag=true;
		
		
	}
	else{
    command[i]=strdup(token);
	i++;
	}
	  
	  token=strtok(NULL," \n");
    
	
}


int lastindex=i-1;

if(command[0] !=NULL){
	
if (strcmp(command[0],"jobs")==0){
	for(int j=0;j<k;j++){
		
	if(waitpid(processList[j], NULL, WNOHANG) == 0){
		cout<< processList[j]<<"\t"<<l[j]<<endl;
		
		
	}
	
	else{
		continue;
	}
  }
  continue;
}
else if(strcmp(command[0],"cd")==0){
	int ch =chdir(command[1]);
	   if(ch<0)
    printf("chdir change of directory not successful\n");
}
else if(strcmp(command[0],"exit")==0){
	exit(0);
}

else if((pid=fork())==0){
	
         
		if(red==true){
		freopen(Dist[0],"w",stdout);
		execvp(command[0],command);
		 fclose (stdout);
	}
	else if(inred==true){
    int fd0;
    if ((fd0 = open(Dist[0], O_RDONLY)) == -1) {
        perror (Dist[0]);
        exit (EXIT_FAILURE);
    }

	
    dup2(fd0, 0);
    close(fd0);
	execvp(command[0],command);
	
	
		 
	}
	
	else if(pFlag == true){
		
            int pipefd[2];
         if( pipe(pipefd)==-1){
			 cout<< "error during piping";
			 exit(0);
		 }
		 int ppid;

		ppid=fork();
		int status;
		if(ppid==0)
		{
		dup2(pipefd[1],1);
		close(pipefd[0]);//this parent dose not need this end of pipe
		char *command1 []= {command[0],NULL};
		if(execvp(command[0],command1)==-1)
		cout<<"this is not command\n";
		//perror(args[0]);
		}
		else
		{
		waitpid(pid,&status,0);
		dup2(pipefd[0],0);
		close(pipefd[1]);//this child dose not need this end of pipe
		char *command2 []= {command[1],NULL};
		if(execvp(command[1],command2)==-1)
		cout<<"this is not command\n";
  
		}
		
    
   
		
	}
	else if(execvp(command[0],command)==-1){
        printf("error during exec \n");
        exit(1);
    }

	

}
    else if(pid>0){
		   
      if(bg==false){
		    wait(&pid);
         	
		}
		else{
			
			processList[k]=pid;	
			k++;
		
		}
		
        fflush(stdin);
        fflush(stdout);
    }
    else{
        printf("error during forking! \n");
        exit(1);
    }
}
else{
	continue;
	
}
 
 }
}