void graphic(double z0, int k, double t){
//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//#include<string.h>
//int main(){

//double z0=10;
//int k=0;
FILE *fp;

int i;
#define STR_SIZE 14

char result[STR_SIZE] = {0};
char s1[] ="img";
char s2[] =".png";
char* filename = "./geometria/geometria.dat";

float x_coord[9],y_coord[9];

fp=fopen(filename,"r");

if (fp == NULL){
        printf("Could not open file %s \n",filename);
        exit(1);
    }

for (i=0;i<=9;i++){
  fscanf(fp,"%f", & x_coord[i] );;
  fscanf(fp,"%f", & y_coord[i] );;
}
fclose(fp);

filename = "./data/data.dat";
if(t==0){
  fp=fopen(filename,"w");
}
else{
  fp=fopen(filename,"a");
}

  fprintf(fp,"%.5f %.5f\n",t,z0);

  fclose(fp);


  snprintf(result, sizeof(result), "%s%06d%s", s1, k, s2);


fp = popen("gnuplot","w");
// REINICIALIZANDO GNUPLOT
fprintf(fp,"reset\n");

//DETERMINAÇAO DOS PARAMETROS DA IMAGEM
//750,550
fprintf(fp,"set terminal pngcairo size 900,900 enhanced font 'Verdana,10'\n");
fprintf(fp,"set output './animation/%s'\n", result);
fprintf(fp,"unset key\n");

//HABILITAÇAO DO MODO MULTIPLOT
fprintf(fp,"set multiplot layout 1,2 title \"2° Modelo Força Constante\" font \",14\"\n");
fprintf(fp,"set title \"Modelo Fisico\"\n");
fprintf(fp,"unset key\n");

fprintf(fp,"set xrange [0:%.3f]\n",((1.5*x_coord[7])));
fprintf(fp,"set yrange [-0.2:%.3f]\n",(1.5*y_coord[1]));

fprintf(fp,"unset border\n");

fprintf(fp,"unset ylabel\n");
fprintf(fp,"unset ytics\n");
fprintf(fp,"unset xlabel\n");
fprintf(fp,"unset xtics\n");

fprintf(fp,"set object 1 poly from %.2f,%.2f to %.2f,%.2f to %.2f,%.2f to %.2f,%.2f to %.2f,%.2f to %.2f,%.2f to %.2f,%.2f to %.2f,%.2f to %.2f,%.2f fc rgb 'black' fs pattern 4 \n",  x_coord[0],y_coord[0],x_coord[1],y_coord[1],x_coord[2],y_coord[2],x_coord[3],y_coord[3],x_coord[4],y_coord[4],x_coord[5],y_coord[5],x_coord[6],y_coord[6],x_coord[7],y_coord[7],x_coord[8],y_coord[8]);

fprintf(fp,"#retangulos moveis \n");

fprintf(fp,"set object 2 rect from %.3f,%.3f to %.3f,%.3f fc rgb \"gray\" fs solid 1.0 noborder #fs pattern 2 #rgb 'black'\n",x_coord[4], (z0-Zi*0.2), x_coord[3],(z0+Zi*0.2));
fprintf(fp,"set object 3 rect from %.3f,%.3f to %.3f,%.3f fc rgb \"#0060ad\" \n", x_coord[3],y_coord[3], x_coord[4], (z0-Zi*0.2) );
fprintf(fp,"set angle degrees\n");

fprintf(fp,"# use 'square' aspect ratio else calculated angles don't match display angles\n");
fprintf(fp,"set size square\n");

fprintf(fp,"# draw a 3,4,5 right triangle as a polygon - f[ill]s[tyle] empty border 1 (red)\n");
fprintf(fp,"set object 4 poly from %.3f,%.3f to %.3f,%.3f to %.3f,%.3f to %.3f,%.3f fillstyle pattern 4 transparent fc rgb 'black' #empty border 1\n",x_coord[6]*1.1,z0, x_coord[6]*1.4,z0, x_coord[6]*1.1,y_coord[3], x_coord[6]*1.1,z0);//(x_coord[6]*1.1),(z0*0.8), (x_coord[6]*1.4),(z0*0.8), (x_coord[6]*1.1),y_coord[3], (x_coord[6]*1.1),(z0*0.8);//x_coord[6]+0.1,z0, x_coord[6]+0.2,z0, x_coord[6]+0.1,y_coord[3], x_coord[6]+0.1,z0);
fprintf(fp,"plot 0 , 0 notitle\n");
fprintf(fp,"unset object 1\n");
fprintf(fp,"unset object 2\n");
fprintf(fp,"unset object 3\n");
fprintf(fp,"unset object 4\n");

fprintf(fp,"set border linewidth 1\n");
//fprintf(fp,"set xrange [0:1]\n");
//fprintf(fp,"set yrange [0:1]\n");

fprintf(fp,"set autoscale y\n");
if (t==0){
fprintf(fp,"set xrange [0:%.5f]\n",0.1);
}
else{
  fprintf(fp,"set xrange [0:%.5f]\n",t);
}

//fprintf(fp,"set yrange [%.3f:%.3f]\n",(0.5-0.5),(0.5+0.5));

fprintf(fp,"set ytics \n");
//fprintf(fp,"set tics scale 0.75\n");
//fprintf(fp,"set xlabel\n");
fprintf(fp,"set xtics scale %.4f\n",t/2500);

fprintf(fp,"set title \"L x t\" \n");
fprintf(fp,"unset key\n");
fprintf(fp,"plot \"./data/data.dat\" u 1:2 lt 3 lw 3\n");

fprintf(fp,"unset multiplot\n");
fflush(fp);
pclose(fp);
//return 0;
}
