#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define atoa(x)
int main(){
	FILE *fp;
	int n,i,j,k,jump;
	double dt;
	printf("final time step = ");
	scanf("%d",&n);
	printf("time step jump = ");
	scanf("%d",&jump);
	printf("dt = ");
	scanf("%lf",&dt);
	// determining number of node
	char sn[30];
	char temp[4];
    sprintf(sn,"%d",jump);
    printf("first file name = %s\n",sn);
	fp=fopen(sn,"r");
	double *px,*py,*pz,*pt,*ptx,*pty,*ptz;
	double *x,*y,*z,*t,*tx,*ty,*tz;
	double *fx,*fy,*fz,*ft,*ftx,*fty,*ftz;
    double *niyama;
	int lines=1,node;
    char ch;
    printf("calculating line number");
	while ((ch = fgetc(fp)) != EOF){
		if (ch == '\n')
		lines++;
		}
    printf("lines = %d\n",lines);
	fclose(fp);
	px=(double*)malloc(lines*sizeof(double));
	py=(double*)malloc(lines*sizeof(double));
	pz=(double*)malloc(lines*sizeof(double));
	pt=(double*)malloc(lines*sizeof(double));
	ptx=(double*)malloc(lines*sizeof(double));
	pty=(double*)malloc(lines*sizeof(double));
	ptz=(double*)malloc(lines*sizeof(double));
	x=(double*)malloc(lines*sizeof(double));
	y=(double*)malloc(lines*sizeof(double));
	z=(double*)malloc(lines*sizeof(double));
	t=(double*)malloc(lines*sizeof(double));
	tx=(double*)malloc(lines*sizeof(double));
	ty=(double*)malloc(lines*sizeof(double));
	tz=(double*)malloc(lines*sizeof(double));
	fx=(double*)malloc(lines*sizeof(double));
	fy=(double*)malloc(lines*sizeof(double));
	fz=(double*)malloc(lines*sizeof(double));
	ft=(double*)malloc(lines*sizeof(double));
	ftx=(double*)malloc(lines*sizeof(double));
	fty=(double*)malloc(lines*sizeof(double));
	ftz=(double*)malloc(lines*sizeof(double));
    niyama=(double*)malloc(lines*sizeof(double));
	fp=fopen(sn,"r");
    printf("hey\n");
    for(i=0;i<lines-1;i++){
        fscanf(fp,"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&node,&px[i],&py[i],&pz[i],&pt[i],&ptx[i],&pty[i],&ptz[i]);
        if(pt[i]<=1885){
            niyama[i]=3.1e05;
        }
    }
    fclose(fp);
    /*
    sprintf(sn,"%d",jump*2);
    fp=fopen(sn,"r");
    printf("hey\n");
    for(i=0;i<lines-1;i++){
        fscanf(fp,"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&node,&x[i],&y[i],&z[i],&t[i],&tx[i],&ty[i],&tz[i]);
    }
    fclose(fp);
    */
    for(i=jump*2;i<n;i+=jump){
        //reading latest profiles
        sprintf(sn,"%d",i);
        fopen(sn,"r");
        for(j=0;j<lines-1;j++){
            fscanf(fp,"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&node,&fx[j],&fy[j],&fz[j],&ft[j],&ftx[j],&fty[j],&ftz[j]);
            //if solidifying, calculate niyama parameter
            if(ft[j]<=1885.0&&pt[j]>1885.0){
                double tg=sqrt((ftx[j]+ptx[j])*(ftx[j]+ptx[j])/4+(fty[j]+pty[j])*(fty[j]+pty[j])/4+(ftz[j]+ptz[j])*(ftz[j]+ptz[j])/4);
                niyama[j]=tg/sqrt(-(ft[j]-pt[j])/dt);
                //printf("%.6f",niyama[j]);
            }
           
            //printf("%.2f %.2f\n",pt[i],ft[i]);
        }
        //update data
        for(j=0;j<lines-1;j++){
             px[j]=fx[j];
             py[j]=fy[j];
             pz[j]=fz[j];
             pt[j]=ft[j];
             ptx[j]=ftx[j];
             pty[j]=fty[j];
             ptz[j]=ftz[j];
         }
        fclose(fp);
    }
    sprintf(sn,"niyama.csv");
    fp=fopen(sn,"w");
    for(i=0;i<lines;i++)
    fprintf(fp,"%.9lf,%.9lf,%.9lf,%.9lf\n",px[i],py[i],pz[i],niyama[i]);
    fclose(fp);
}
