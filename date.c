void date(char *str,char *xyz){
	pid_t pid=fork();
	if(pid<0){ printf("process failed please try again");}
	else if(pid==0){
		if(strcmp(str,"")==0){//noflag
			if(strcmp(xyz,"#")==0){
				if(execl("/bin/date","date",str,(char *)0)==-1){
				perror("Error : ");
				}	
			}
			else{
				if(execl("/bin/date","date",str,xyz,(char *)0)==-1){
				perror("Error : ");
				}	
			}
		}
		else{
			if(strcmp(xyz,"#")==0){
				if(execl("/bin/date","date",(char *)0)==-1){
				perror("Error : ");
				}	
			}
			else{
				if(execl("/bin/date","date",xyz,(char *)0)==-1){
				perror("Error : ");
				}	
			}
		}
	}
	else{
		wait(NULL);
	}
}