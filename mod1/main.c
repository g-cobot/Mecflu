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
#define v -40.5
#define Zi 0.200//8.571341116          //em (m)

//DEFINICAO DAS VARIAVEIS NO DOMINIO DISCRETO
//-----------------------------------------------
int k;                          // VARIAVEL DE INTERAÇAO DO TEMPO NO DOMINIO DISCRETO
double pn;                      // PRESSAO [Pa]
double zn;                      // POSICAO [m]
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
#include</home/gabriel/Desktop/MecFlu/mod1/subrotinas/pression.c>
#include</home/gabriel/Desktop/MecFlu/mod1/subrotinas/force.c>
#include</home/gabriel/Desktop/MecFlu/mod1/subrotinas/position.c>
#include</home/gabriel/Desktop/MecFlu/mod1/subrotinas/especific_mass.c>
#include</home/gabriel/Desktop/MecFlu/mod1/subrotinas/volume.c>
#include</home/gabriel/Desktop/MecFlu/mod1/subrotinas/graphic.c>
//-----------------------------------------------
//PROGRAMA PRINCIPAL
//-----------------------------------------------
int main (void){
//DEFINICAO ESTADO INICIAL DO SISTEMA
//-----------------------------------------------
double z0 = Zi;               // POSICAO VERTICAL [m]

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

double rho0 = 1.2928;          // RHO INICIAL  [Kg/m³]
kappa = patm * vol(rho0) ;       // KAPPA = PATM * VOLUME INICIAL

//GERAÇAO DA IMAGEM INICIAL
graphic(z0 , 0 , 0);

//printf("Gerando figura 000000,z=%4.3f v=%4.3f kappa=%4.3f vol=%4.3f \n",z0,v0,kappa,vol(rho0));
printf("Gerando simulaçao do sistema: \n");

printf("z=%4.3f v=%4.3f kappa=%4.3f vol=%4.3f \n",z0,v,kappa,vol(rho0));
dt    = (double) 1 / 150000;
rhon = rho( rho0 , dt );
voln = vol( rho0 );
pn   = p( rhon ) ;
fn   = f( voln );
printf("tempo terminal= %4.3f \n",(z0/v)/dt);
//-----------------------------------------------
for(k=1;k<500;k++){
  t    = (double) k*dt;
  zn   = z( z0 , dt );
  rhon = rho( rho0 , dt );
  voln = vol( rho0 );
  fn   = f( voln );
  pn   = p( rhon ) ;


//ATUALIZACAO DAS VARIAVEIS K-1
//-----------------------------------------------
  z0   = zn;
  rho0 = rhon;
  graphic( z0, k , t );

  //printf("Gerando figura %06d,z=%4.3f v=%4.3f rho=%4.3f vol=%4.3f p=%4.3f f=%4.3f tempo= %4.4f s \n",k,zn,vn,rhon,voln,pn,fn,t);
  printf("k=%d z=%4.3f v=%4.3f rho=%4.3f vol=%4.3f p=%4.3f f=%4.3f tempo= %4.4f s \n",k,zn,v,rhon,voln,pn,fn,t);
  }
return 0;
}
