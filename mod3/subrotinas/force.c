double f( double p0,double v0,double z0 ){
double aux1,aux2,aux3;
aux1 =  (A * ( p0 - patm ));
aux2 =  (M * g);
aux3 =  ( -2 * mi * A1 * v0/z0);
return( aux1 - aux2 + aux3 );
}
