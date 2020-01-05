
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;//�ļ�ָ��
    int i, d;

    /*�ļ��Ĵ�*/
    fp=fopen("data.txt","w");//fopen���ļ�������ļ������ǵ�ǰ�����ڵġ���w����д�����ʽ�򿪣���r���Զ�����ʽ��
    if(fp==NULL) //�ж�����ļ�ָ��Ϊ��
    {
        printf("File cannot open! " );
        exit(0);//����0����ʽ�˳����������ļ���ͷ��#include <stdlib.h>,stdlib ͷ�ļ���standard library��׼��ͷ�ļ�
    }

    //д�붫��
    for(i=0; i<10; i++)
    {
        scanf("%d", &d);//�û�����
        fprintf(fp,"%d\t", d);//д��ָ��fp��д��Ķ������Ǹղŵ��û������d,ע�������fp��dû������
    }

     //�ر��ļ�
    fclose(fp);
    return 0;
}

//*************************************************************************************************************

#include <time.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#define FILE_NAME_ROOM	50
#define DATA_TIME_ROOM	24


void savevalue(double a,double b){
	
	time_t t_name = time(0); 
	
	static char F_name[50]; 
	static char F_time[24]; 
	
	char data_dir[]="/root/Documents/RASY_data";

	if(access(data_dir,0) != 0){

		mkdir(data_dir,0744);	//owner:r,w,x; group && others :only r

	}
	
	strftime(F_name, FILE_NAME_ROOM, "/root/Documents/RASY_data/%Y%m%d%H%M.txt",localtime(&t_name) ); //%Y%m%d%H:%M:%S
	strftime(F_time, DATA_TIME_ROOM, "%Y-%m-%d\t%H:%M:%S",localtime(&t_name) ); 
	
	FILE *fp;//�ļ�ָ��

    fp=fopen(F_name,"a");	//����a��׷������
	
    if(fp==NULL) //�ж�����ļ�ָ��Ϊ��
    {
        printf("File cannot open! " );
        exit(0);
    }

  
    fprintf(fp,"\t%s:\n\tV4:%9.8lf\tV8:%9.8lf\t\n\n",F_time,a,b);
    

     //�ر��ļ�
    fclose(fp);

}

int main(int argc, char *argv[]){
	
	savevalue(1,2);
	return 0;
}

