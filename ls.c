void ls(char *str,char *xyz){
	char cur_dir[1024];
	pid_t pid=fork();
	if(pid<0){ printf("process failed please try again");}
	else if(pid==0){
		getcwd(cur_dir,sizeof(cur_dir));
		if(strcmp(str,"")==0){//noflag
			if(strcmp(xyz,"#")==0){
				if(execl("/bin/ls","ls",str,cur_dir,(char *)0)==-1){
				perror("Error : ");
				}	
			}
			else{
				if(execl("/bin/ls","ls",str,xyz,(char *)0)==-1){
				perror("Error : ");
				}	
			}
		}
		else{
			if(strcmp(xyz,"#")==0){
				if(execl("/bin/ls","ls",cur_dir,(char *)0)==-1){
				perror("Error : ");
				}	
			}
			else{
				if(execl("/bin/ls","ls",xyz,(char *)0)==-1){
				perror("Error : ");
				}	
			}
		}
	}
	else{
		wait(NULL);
	}
}