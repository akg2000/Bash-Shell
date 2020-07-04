#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <curses.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include "ls.c"
#include "rm.c"
#include "date.c"
#include "mkdir.c"
#include "cat.c"

int takeInput(char** str){ 
    char* input=malloc(sizeof(char *)); 
    input = readline(">>> ");
    if (strlen(input)!=0) {
        add_history(input);
        *str=input;
        return 0; 
    } else { 
        return 1; 
    }  
}
void printDir(){ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("\nDir: %s\n", cwd); 
} 
int countspaces(char input[]){
    int count=0;
    for(int i=0;i<strlen(input)-1;i++){
        if((input[i]!=input[i+1]) && input[i]==' '){
            count++;
        }
    }
    return count;
}
void find_arguments(char** arguments,char* input,int gaps){
    int counter=0;
    char* token = strtok(input, " "); 
	// printf("here \n");
	arguments[counter]=malloc(strlen(token)*sizeof(char));
	strcpy(arguments[counter],token);
	// printf("%s\n", arguments[counter]);
	counter++;
    while (token != NULL) { 
    	arguments[counter]=malloc(strlen(token)*sizeof(char));
    	// arguments=realloc(arguments,sizeof(char *)*counter+1);
	    // arguments[counter]=malloc(sizeof(char *));
        token = strtok(NULL, " ");
        if(token!=NULL){
	        strcpy(arguments[counter],token); 
	        // printf("%s\n", argumnets[counter]);
        }
        // printf("%s\n", arguments[counter]);
        counter++;
    }
 	return;
} 
int main(){
    char* input;
    char** last_commands;
    char cur_dir[1024];
    // char** arguments;
    int ptr=0;
    char *xyz;
    // char* temp;
    char** hist=malloc(sizeof(char *));
    int status=1;
    hist[0]=malloc(sizeof(char)*10);
    printDir();
    while(status){
    	// printf("1111111111111\n");
        if (takeInput(&input)) 
            continue;
	    ptr++;
	    // printf("0000000000000000000000");
	    // hist=realloc(hist,sizeof(char *)*ptr);
	    hist=realloc(hist,10000);
	    // printf("asdfghjklsdfghjk");
	    hist[ptr]=malloc(sizeof(char)*strlen(input));
	    strcpy(hist[ptr],input);
	    // printf("%s\n",hist[ptr] );
	    char copy[10000];
	    strcpy(copy,input);
	    int spaces_count = countspaces(copy);
	    int no_of_arguments=spaces_count+1;
	    // printf("jkl");
	    // printf("%d\n",no_of_arguments);
	    char** arguments=malloc(sizeof(char *)*(no_of_arguments+2));
	    find_arguments(arguments,input,no_of_arguments);
	    char *abc;
	    // printf("%s\n",arguments[1] );
		if(arguments[1][0]=='-' && arguments[2]!=NULL && arguments[2][0]=='-' && arguments[3]!=NULL && arguments[3][0]=='-' && arguments[4]!=NULL && arguments[4][0]=='-'){
	    	arguments[1][2]=arguments[2][1];
	    	arguments[1][3]=arguments[3][1];
	    	arguments[1][4]=arguments[4][1];
	    	// printf("%s\n",arguments[1]);
	    	// strcat(arguments[0][0],arguments[1][0]);
	    	// strcat(arguments[0][0],arguments[2][0]);
	    }	    
	    else if(arguments[1][0]=='-' && arguments[2]!=NULL && arguments[2][0]=='-' && arguments[3]!=NULL && arguments[3][0]=='-'){
	    	arguments[1][2]=arguments[2][1];
	    	arguments[1][3]=arguments[3][1];
	    	// printf("%s\n",arguments[1] );
	    	// strcat(arguments[0][0],arguments[1][0]);
	    	// strcat(arguments[0][0],arguments[2][0]);
	    }
	    else if(arguments[1][0]=='-' && arguments[2]!=NULL && arguments[2][0]=='-'){
	    	arguments[1][2]=arguments[2][1];
	    	// printf("%s\n",arguments[1]);
	    	// strcat(arguments[0][0],arguments[1][0]);
	    	// strcat(arguments[0][0],arguments[2][0]);
	    }
	    // if(arguments[1]!=NULL){
		   //  int l=strlen(arguments[1]);
		   //  temp=malloc(sizeof(char)*(l-1));
		   //  for(int i=0;i<l-1;i++){
		   //  	temp[i]=arguments[1][i+1];
		   //  }

	    // }
		if(arguments[1]!=NULL && arguments[1][0]!='-'){
			xyz=malloc(sizeof(char)*strlen(arguments[1]));
			xyz=arguments[1];
		}
		else if(arguments[1]!=NULL && arguments[1][0]=='-' && arguments[2]!=NULL && arguments[2][0]!='-'){
			xyz=malloc(sizeof(char)*strlen(arguments[2]));
			xyz=arguments[2];
		}
		else if(arguments[1]!=NULL && arguments[1][0]=='-' && arguments[2]!=NULL && arguments[2][0]=='-' && arguments[3]!=NULL && arguments[3][0]!='-'){
			xyz=malloc(sizeof(char)*strlen(arguments[3]));
			xyz=arguments[3];
		}
		else if(arguments[1]!=NULL && arguments[1][0]=='-' && arguments[2]!=NULL && arguments[2][0]=='-' && arguments[3]!=NULL && arguments[3][0]=='-' && arguments[4]!=NULL && arguments[4][0]!='-'){
			xyz=malloc(sizeof(char)*strlen(arguments[4]));
			xyz=arguments[4];
		}
		else if(arguments[1]!=NULL && arguments[1][0]=='-' && arguments[2]!=NULL && arguments[2][0]=='-' && arguments[3]!=NULL && arguments[3][0]=='-' && arguments[4]!=NULL && arguments[4][0]=='-' && arguments[5]!=NULL && arguments[5][0]!='-'){
			xyz=malloc(sizeof(char)*strlen(arguments[5]));
			xyz=arguments[5];
		}
		else{
			xyz=malloc(sizeof(char));
			xyz="#";
		}
	    if(strcmp(arguments[0],"history")==0){
	    	for(int i=1;i<ptr+1;i++){
	    		printf("%s \n",hist[i]);
	    	}
	    }
	    else if(strcmp(arguments[0],"echo")==0){		// echo
				if(strcmp(arguments[1],"-E")==0){
	                for(int i=2; i<(no_of_arguments); i++){
	                    printf("%s ",arguments[i]);
	                }
	                printf("\n");    
	            }
	            else if(strcmp(arguments[1],"-n")==0){
	                for(int i=2; i<(no_of_arguments); i++){
	                    printf("%s ",arguments[i]);
	                }
	            }
	            else{
	                for(int i=1; i<no_of_arguments; i++){
	                    printf("%s ",arguments[i]);
	                }
	                printf("\n");
	            }   
		}
		else if(strcmp(arguments[0],"pwd")==0){
	        if(strcmp(arguments[1],"--help")==0){
	            printf("pwd - print name of current/working directory");
	        }
	        else{
	            getcwd(cur_dir,sizeof(cur_dir));
	            printf("%s\n",cur_dir);
	        }
		}
	    else if(strcmp(arguments[0],"cd")==0){
	        if(chdir(arguments[1])!=0){
	            perror("Bash : cd :");
	        }
	    }
		else if(strcmp(arguments[0],"exit")==0){
	        printf("Thanks for using my shell :) \n");
	        exit(0);
	    }
	    else if(strcmp(arguments[0],"ls")==0){
	    	ls(arguments[1],xyz);
	    }
	    else if(strcmp(arguments[0],"cat")==0){
	    	cat(arguments[1],xyz);
	    }
	    else if(strcmp(arguments[0],"date")==0){
	    	date(arguments[1],xyz);
	    }
	    else if(strcmp(arguments[0],"rm")==0){
	    	rm(arguments[1],xyz);
	    }
	    else if(strcmp(arguments[0],"mkdir")==0){
	    	mkdir(arguments[1],xyz);
	    }
	    else{
	    	printf("Not Supported yet");
	    }
    }
}
