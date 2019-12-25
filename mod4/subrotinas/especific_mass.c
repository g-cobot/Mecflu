double rho( double rho0, double z0, double v0, double t ){
return ( rho0 - (rho0 * (v0 / z0) *t)   ) ;
//double aux1 = z0 * rho0;
//double aux2 = z0 + ( v0 * t );
//return ( aux1 / aux2 ) ;
}
