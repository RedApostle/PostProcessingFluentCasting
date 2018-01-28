#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define atoa(x)
bool equals(double x){
   double ts=0.001;//threshol=ts
    if(1+ts>=x&&1-ts<=x)
    return 1;
    return 0;
}
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
	fp=fopen(sn,"r");///r=read
	double *px,*py,*pz,*ptx,*pty,*ptz,*plf,*pvf,*pt;
	double *x,*y,*z,*tx,*ty,*tz,*lf,*vf,*t;
	double *fx,*fy,*fz,*ftx,*fty,*ftz,*flf,*fvf,*ft;
    double *niyama;
    double *zhang;
	int lines=1,node;
    char ch;//char=ch
    printf("calculating line number");
	while ((ch = fgetc(fp)) != EOF){
		if (ch == '\n')
		lines++;
		}
    printf("lines = %d\n",lines);
    double fls[lines];
	fclose(fp);
	px=(double*)malloc(lines*sizeof(double));
	py=(double*)malloc(lines*sizeof(double));
	pz=(double*)malloc(lines*sizeof(double));
	ptx=(double*)malloc(lines*sizeof(double));
	pty=(double*)malloc(lines*sizeof(double));
	ptz=(double*)malloc(lines*sizeof(double));
    plf=(double*)malloc(lines*sizeof(double));
    pvf=(double*)malloc(lines*sizeof(double));
    pt=(double*)malloc(lines*sizeof(double));
	x=(double*)malloc(lines*sizeof(double));
	y=(double*)malloc(lines*sizeof(double));
	z=(double*)malloc(lines*sizeof(double));
	tx=(double*)malloc(lines*sizeof(double));
	ty=(double*)malloc(lines*sizeof(double));
	tz=(double*)malloc(lines*sizeof(double));
    lf=(double*)malloc(lines*sizeof(double));
    vf=(double*)malloc(lines*sizeof(double));
    t=(double*)malloc(lines*sizeof(double));
	fx=(double*)malloc(lines*sizeof(double));
	fy=(double*)malloc(lines*sizeof(double));
	fz=(double*)malloc(lines*sizeof(double));
	ftx=(double*)malloc(lines*sizeof(double));
	fty=(double*)malloc(lines*sizeof(double));
	ftz=(double*)malloc(lines*sizeof(double));
    flf=(double*)malloc(lines*sizeof(double));
    fvf=(double*)malloc(lines*sizeof(double));
    ft=(double*)malloc(lines*sizeof(double));
    niyama=(double*)malloc(lines*sizeof(double));
    zhang=(double*)malloc(lines*sizeof(double));
	fp=fopen(sn,"r");
    printf("hey\n");
    for(i=0;i<lines-1;i++){
        double h;
        fscanf(fp,"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&node,&px[i],&py[i],&pz[i],&pt[i],&h,&ptx[i],&pty[i],&ptz[i],&pvf[i],&plf[i],&h);
        if(pt[i]<=1885.0&&equals(pvf[i])){
            niyama[i]=3.1e05;
        }
    }
    fclose(fp);
    for(i=jump*2;i<n;i+=jump){
        //reading latest profiles
        sprintf(sn,"%d",i);
        fopen(sn,"r");
        for(j=0;j<lines-1;j++){
            double h;
            fscanf(fp,"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&node,&fx[j],&fy[j],&fz[j],&ft[j],&h,&ftx[j],&fty[j],&ftz[j],&fvf[j],&flf[j],&h);
            if(ft[j]<=1885.0&&pt[j]>1885.0){
                double tg=sqrt((ftx[j]+ptx[j])*(ftx[j]+ptx[j])/4+(fty[j]+pty[j])*(fty[j]+pty[j])/4+(ftz[j]+ptz[j])*(ftz[j]+ptz[j])/4);
                niyama[j]=tg/sqrt(abs(ft[j]-pt[j])/(i*dt));
            }
            if(ft[j]<=1877.0&&pt[j]>=1877.0){
                fls[j]=i*dt;
            }
            if(ft[j]<=1885.0&&pt[j]>1885.0){
                double tg=sqrt((ftx[j]+ptx[j])*(ftx[j]+ptx[j])/4+(fty[j]+pty[j])*(fty[j]+pty[j])/4+(ftz[j]+ptz[j])*(ftz[j]+ptz[j])/4);
                zhang[j]=(fls[j]/tg)*(((1-((pt[j]-1877)/56))-(1-((ft[j]-1877)/56)))/(i*dt))*sqrt(abs(ft[j]-pt[j])/(dt*i));
            }
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
             pvf[j]=fvf[j];
         }
        fclose(fp);
    }

    fp=fopen(sn,"r");
    printf("hey\n");
    for(i=0;i<lines-1;i++){
        double h;
        fscanf(fp,"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&node,&px[i],&py[i],&pz[i],&pt[i],&h,&ptx[i],&pty[i],&ptz[i],&pvf[i],&plf[i],&h);
        if(pt[i]<=1885.0&&equals(pvf[i])){
            niyama[i]=3.1e05;
        }
    }
    fclose(fp);
    for(i=jump*2;i<n;i+=jump){
        //reading latest profiles
        sprintf(sn,"%d",i);
        fopen(sn,"r");
        for(j=0;j<lines-1;j++){
            double h;
            fscanf(fp,"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&node,&fx[j],&fy[j],&fz[j],&ft[j],&h,&ftx[j],&fty[j],&ftz[j],&fvf[j],&flf[j],&h);
            //printf("%d %d %.4f %.4f %.4f\n",i,j,ptx[j],pty[j],ptz[j]);
            //if solidifying, calculate niyama parameter
            //printf("pt = %lf\n",pt[i]);
           // printf("ft = %lf\n",ft[j]);
            if(ft[j]<=1885.0&&pt[j]>1885.0){
                double tg=sqrt((ftx[j]+ptx[j])*(ftx[j]+ptx[j])/4+(fty[j]+pty[j])*(fty[j]+pty[j])/4+(ftz[j]+ptz[j])*(ftz[j]+ptz[j])/4);
                niyama[j]=tg/sqrt(abs(ft[j]-pt[j])/(i*dt));
                //printf("%.6f",niyama[j]);
            }
            //printf("%.2f %.2f\n",pt[i],ft[i]);
            if(ft[j]<=1877.0&&pt[j]>=1877.0){
                fls[j]=i*dt;
                //printf("fls = %lf,at i=%0.4d\n",fls[j],i);
            }
            if(ft[j]<=1885.0&&pt[j]>1885.0){
                double tg=sqrt((ftx[j]+ptx[j])*(ftx[j]+ptx[j])/4+(fty[j]+pty[j])*(fty[j]+pty[j])/4+(ftz[j]+ptz[j])*(ftz[j]+ptz[j])/4);
                zhang[j]=(fls[j]/tg)*(((1-((pt[j]-1877)/56))-(1-((ft[j]-1877)/56)))/(i*dt))*sqrt(abs(ft[j]-pt[j])/(dt*i));
              //  sprintf(sn,"proof%0.4d.csv",i);
               // fp=fopen(sn,"w");
               // for(k=0;k<lines;k++)
               // fprintf(fp,"%.9lf,%.9lf,%.9lf,%.9lf,%.9lf,%.9lf,%.9lf,%.9lf,%.4d\n",px[i],py[i],pz[i],niyama[i],zhang[i],pt[i],ft[i],fls[j],i);
               // fclose(fp);
            }
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
             pvf[j]=fvf[j];
         }
        fclose(fp);
    }
    sprintf(sn,"niyama+zhang.csv");
    fp=fopen(sn,"w");
    for(i=0;i<lines;i++)
    fprintf(fp,"%.9lf,%.9lf,%.9lf,%.9lf,%.9lf\n",px[i],py[i],pz[i],niyama[i],zhang[i]);
    fclose(fp);
}


