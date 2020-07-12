//
//  2CGillespieDiffusion.cpp
//  
//
//  Created by Zahedeh Bashardanesh on 10/22/12.
//
//

//#include "2CGillespieDiffusion.h"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "MersenneTwister.h"
#define V 30
#define nMax 3*V
#define M 2

using namespace std;
#include "st.h"
//#include "aleatoire.h"
//#include "etime.h"
//#define nplot 100000000
//#define iterm 50000000
//#define n 220
//#define M 150
//const double  dt=0.01;
/*dt is the time step*/
/* some constatnts for the algorithm*/

//long idum,nn;
MTRand *R;

int main(){
    int ii=0;
    long int n1=2*V, n2=2*V;
    double k1=.2;
    double k2=1.75;
    double kD=1;
    double lambda = 1;
    double iV = 1./(V*kD);
    double randt, randr;
    double t, tau=0.0;
    double fT=6e6;
    double C, C4, iC4;
    double d12, d21;
    double p11, p12, p21, p22;
    double pp, sump;
    double p[M*nMax] = {0};

    double D = 1;
    
    
    R = new MTRand();
    
    //    time_t seconds,seconds1;
    //    time(&seconds);
    //    srand(seconds);
    //    idum=rand();
    //    cout<< idum<<endl;
    //    idum=-12375;
    
    
//    char filename[132];
////    sprintf(filename, "2CData.dat");
//    ofstream myfile("2CData.dat");
    
    //while(1>0){
        t=0.0;
    while (t<fT){
        C = n1*iV;
        C4 = C*C;
        C4 = C4*C4;
        iC4 = 1./(1+C4);
        
        d12 = D*n1;
        p11 = lambda*n1;
        p12 = V*k1 + V*k2*C4*iC4;
        
        C = n2*iV;
        C4 = C*C;
        C4 = C4*C4;
        iC4 = 1./(1+C4);
        
        d21 = D*n2;
        p21 = lambda*n2;
        p22 = V*k1 + V*k2*C4*iC4;
        
        
        sump = d12 + d21 + p11 + p12 + p21 + p22;
        
        do { /* Generate random number -> time*/
            randt = 1.0-R->randExc();
        } while (!((randt>0)&&(randt<1)));
        
        do{ /*Generate random number -> reaction*/
            randr = 1.0-R->randExc();
        } while(!((randr>0)&& (randr<1)));
        
        
        
        tau = -log(randt)/sump; /*Increasing the time*/
        t = t + tau;
        if(n1 + n2<M*nMax){p[n1+n2]=p[n1+n2]+tau;}
        
        sump = sump*randr;

        pp = d12;
        if (sump<pp) {
            n1 = n1-1;
            n2 = n2+1;}
        
        else {pp = pp+d21;
            if (sump<pp) {
                n1 = n1+1;
                n2 = n2-1;}
            
            else {pp = pp+p11;
                if (sump< pp){
                    n1 = n1-1;}
                
                else {pp = pp + p21;
                    if (sump<pp){
                        n2 = n2-1;}
                    
                    else {pp = pp+p12;
                        if (sump<pp){
                            n1 = n1+1;}
                        
                        else {n2 = n2+1;}}}}}
        
//        cout << n1 <<SP << n2 <<endl;
        //        myfile << x1 << SP << x2 <<endl;
        
    }//end while
    //    cout << "N1= "<<n1<<SP<< "N2= "<<n2<<endl;
    
//    char filename[132];
    //    sprintf(filename, "2CData.dat");
//                 ofstream myfile("2CDatamm.dat");
        
//        myfile.open();
//
        ofstream outfile;
        
        outfile.open ("2CData.dat");
//    
    for (ii=0 ; ii<M*nMax; ii++ )
    {outfile << ii <<SP<<p[ii]<<endl;}
        outfile.close();
	//}
}//end main


