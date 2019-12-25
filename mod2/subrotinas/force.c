double f( double p0 ){
double aux1,aux2;
aux1 =  (A * ( p0 - patm ));
aux2 =  (M * g);
return( aux1 - aux2 );
}
