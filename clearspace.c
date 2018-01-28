#include<stdio.h>
#include<stdlib.h>
int main(){
    char a[200];
    char sn[30];
    char fn[30];
    int n,jump,i,j;
    printf("final time step = ");
	scanf("%d",&n);
	printf("time step jump = ");
	scanf("%d",&jump);
    FILE *fp,*fout;
    for(i=jump;i<=n;i+=jump){
        sprintf(sn,"FFF-%04d.1",i);
        fp=fopen(sn,"r");
        char out[30];
        sprintf(out,"%d",i);
        fout=fopen(out,"w");
        char buffer[2000];
	    fgets(buffer,2000,fp);
        while(!feof(fp)){
            char temp=fgetc(fp);
            if(temp!=' '&&temp!=EOF)
            fprintf(fout,"%c",temp);
        }
        fclose(fp);
        fclose(fout);
    }
}