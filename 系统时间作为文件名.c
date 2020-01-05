#include <time.h> 
#include <stdio.h>
#include <stdlib.h> 

#define FILE_NAME_ROOM	50


char *txt_name(){
	
	time_t t_name = (time(0)-864000);	// 10*86400=864000£¬ÍùÇ°10Ìì
	
	static char F_name[FILE_NAME_ROOM];
	
	strftime(F_name, FILE_NAME_ROOM, "%Y%m%d%H%M%S.txt",localtime(&t_name) ); 
	
	return F_name ; 
	
}

int main(int argc, char *argv[]){ 
	
	char *F_name;
	
	F_name=txt_name();
	
    printf("%s\n",F_name);

    return 0; 
} 


/*

char *txt_name(char * F_name){
	
	time_t t_name = (time(0)-864000);	// 10*86400=864000

	strftime(F_name, FILE_NAME_ROOM, "%Y%m%d%H%M%S.txt",localtime(&t_name) ); 
	
	return F_name ; 
	
}

int main(int argc, char *argv[]){ 
	
	char *F_name;
	
	if((F_name=(char*)malloc(FILE_NAME_ROOM * sizeof(char)))==NULL){
		printf("FILE_NAME_ROOM not able to allocate memory.\n");
		exit(1);
	}
	
	txt_name(F_name);
    printf("%s\n",F_name);

	free(F_name);
    return 0; 
} 

*/
