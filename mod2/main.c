//-----------------------------------------------
//Universidade Federal de Uberlândia
//Faculdade de Engenharia Mecânica
//-----------------------------------------------
//Bibliotecas
//-----------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//-----------------------------------------------
//Definicao de arquivos
//-----------------------------------------------


//-----------------------------------------------
//DEFINICAO DAS VARIAVEIS GLOBAIS
//-----------------------------------------------
#define pi 3.141592654          // PI
#define patm 101052             // PRESSAO ATMOSFERICA [Pa]
#define M 0.261381//0.5                   // MASSA DO PISTAO [Kg]
#define A 0.02016//0.1256              // AREA DA SESSAO TRANSVERSAL DO CILINDRO [m²]
#define g 9.8107000000          // ACELERACAO GRAVITACIONAL [m/s²]
#define T 293.15
#define R 287.0530
#define Zi 0.100
//DEFINICAO DAS VARIAVEIS NO DOMINIO DISCRETO
//-----------------------------------------------
int k;                          // VARIAVEL DE INTERAÇAO DO TEMPO NO DOMINIO DISCRETO
double pn;                      // PRESSAO [Pa]
double zn;                      // POSICAO [m]
double vn;                      // VELOCIDADE [m/s]
double voln;                    // VOLUME [m^3]
double fn;                      // FORÇA [N]
double rhon;                    // MASSA ESPECIFICA [Kg/m^3]
double kappa;                   // CONSTANTE GAS PERFEITO (nRT)
//DEFINICAO DAS VARIAVEIS NO DOMINIO ANALOGICO
//-----------------------------------------------
double t;                       // TEMPO ABSOLUTO [ms](tinicial=0)
double dt;                      // TEMPO ABSOLUTO [ms](tinicial=0)

FILE *fp;
char* filename = "./geometria/geometria.dat";
//-----------------------------------------------
//SUBROTINAS
//-----------------------------------------------
#include</home/gabriel/Desktop/MecFlu/mod2/subrotinas/pression.c>
#include</home/gabriel/Desktop/MecFlu/mod2/subrotinas/force.c>
#include</home/gabriel/Desktop/MecFlu/mod2/subrotinas/position.c>
#include</home/gabriel/Desktop/MecFlu/mod2/subrotinas/speed.c>
#include</home/gabriel/Desktop/MecFlu/mod2/subrotinas/especific_mass.c>
#include</home/gabriel/Desktop/MecFlu/mod2/subrotinas/volume.c>
#include</home/gabriel/Desktop/MecFlu/mod2/subrotinas/graphic.c>
//-----------------------------------------------
//PROGRAMA PRINCIPAL
//-----------------------------------------------
int main (void){
//DEFINICAO ESTADO INICIAL DO SISTEMA
//-----------------------------------------------
double z0 = 0.100;//8.571341116;               // POSICAO VERTICAL [m]

fp=fopen(filename,"w");
fprintf(fp,"%.2f %.2f\n",0.00,0.00);
fprintf(fp,"%.2f %.2f\n",0.00,1.5*z0);
fprintf(fp,"%.2f %.2f\n",(z0/10),1.5*z0);
fprintf(fp,"%.2f %.2f\n",(z0/10),(z0/10));
fprintf(fp,"%.2f %.2f\n",z0,(z0/10));
fprintf(fp,"%.2f %.2f\n",z0,1.5*z0);
fprintf(fp,"%.2f %.2f\n",(11*z0/10),1.5*z0);
fprintf(fp,"%.2f %.2f\n",(11*z0/10),0.00);
fprintf(fp,"%.2f %.2f\n",0.00,0.00);

fclose(fp);

double v0 = 0.00;              // VELOCIDADE VERTICAL INICIAL [m/s]
double rho0 = 1.2928;          // RHO INICIAL  [Kg/m³]
kappa = patm * vol(z0) ;       // KAPPA = PATM * VOLUME INICIAL
kappa = (T*R*rho0)-kappa;
//kappa = patm * vol(z0) ;        // KAPPA = PATM * VOLUME INICIAL



//kappa= rho0 * T * R ;          // KAPPA = PATM * VOLUME INICIAL

//GERAÇAO DA IMAGEM INICIAL
graphic(z0 , 0 , 0);

//printf("Gerando figura 000000,z=%4.3f v=%4.3f kappa=%4.3f vol=%4.3f \n",z0,v0,kappa,vol(rho0));
printf("Gerando simulaçao do sistema: \n");

printf("z=%4.3f v=%4.3f kappa=%4.3f vol=%4.3f \n",z0,v0,kappa,vol(rho0));
dt    = (double) 1 / 10000;//2000;
rhon = rho( rho0 , z0 , v0 , dt );
voln = vol( z0 );
pn   = p( rhon ) ;
fn   = f( pn );

//-----------------------------------------------
for(k=1;k<500;k++){
  t    = (double) k*dt;
  vn   = v( v0, fn, dt );
  zn   = z( z0 , v0 , dt );
  rhon = rho( rho0 , zn , vn , dt );
  voln = vol( z0 );
  pn   = p( rhon ) ;
  fn   = f( pn );

//ATUALIZACAO DAS VARIAVEIS K-1
//-----------------------------------------------
  z0   = zn;
  v0   = vn;
  rho0 = rhon;
  graphic( z0, k , t );

  //printf("Gerando figura %06d,z=%4.3f v=%4.3f rho=%4.3f vol=%4.3f p=%4.3f f=%4.3f tempo= %4.4f s \n",k,zn,vn,rhon,voln,pn,fn,t);
  printf("k=%d z=%4.3f v=%4.3f rho=%4.3f vol=%4.3f p=%4.3f f=%4.3f tempo= %4.4f s \n",k,zn,vn,rhon,voln,pn,fn,t);
  }
return 0;
}
