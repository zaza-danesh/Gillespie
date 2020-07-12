//
//  3CGillespieDiffusion.cpp
//  
//
//  Created by Zahedeh Bashardanesh on 10/22/12.
//
//

#include "3CGillespieDiffusion.h"
//
//  GillespieDiffusionMComp.cpp
//
//
//  Created by Zahedeh Bashardanesh on 10/21/12.
//
//

#include <stdio.h>
#include <iostream.h>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include "include/mersenne/MersenneTwister.h"
#define V 8
#define nMax 3*V
#define M 3 //number of compartments
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
    long int n1=20, n2=20, n3=20;
    double k1=.2;
    double k2=1.75;
    double kD=1;
    double lambda = 1;
    double iV = 1./(V*kD);
    double randt, randr;
    double t=0.0, tau=0.0, fT=1e9;
    double C, C4, iC4;
    double d12, d21, d23, d32, p11, p12, p21, p22, p31, p32, sump;
    
    double pp;
//    double p1[nMax];
//    double p2[nMax];
//    double p3[nMax];
    double p[M*nMax]={0};
    double D = 1;
    
    
    R = new MTRand();
    
    //    time_t seconds,seconds1;
    //    time(&seconds);
    //    srand(seconds);
    //    idum=rand();
    //    cout<< idum<<endl;
    //    idum=-12375;
    
    
    char filename[132];
//    sprintf(filename, "3CData.dat");
        sprintf(filename, "3CData1.dat");
    ofstream myfile(filename);
    
    while (t<fT){
        C = n1*iV;
        C4 = C*C;
        C4 = C4*C4;
        iC4 = 1./(1+C4);
        
        d12 = D*n1;
        d21 = D*n2;
        p11 = lambda*n1;
        p12 = V*k1 + V*k2*C4*iC4;
        
        C = n2*iV;
        C4 = C*C;
        C4 = C4*C4;
        iC4 = 1./(1+C4);
        
        d23 = d21;
        d32 = D*n3;
        p21 = lambda*n2;
        p22 = V*k1 + V*k2*C4*iC4;
        
        C = n3*iV;
        C4 = C*C;
        C4 = C4*C4;
        iC4 = 1./(1+C4);
        
        p31 = lambda*n3;
        p32 = V*k1 + V*k2*C4*iC4;
        
        
        
        sump = d12 + d21 + d23 + d32 + p11 + p12 + p21 + p22 + p31 + p32;
        
        do { /* Generate random number*/
            randt = 1.0-R->randExc();
            
        } while (!((randt>0)&&(randt<1)));
        
        
        do{
            randr = 1.0-R->randExc();
            
            
        } while(!((randr>0)&& (randr<1)));
      
        tau = -log(randt)/sump; /*Increasing the time*/
        t = t + tau;

        if(n1 + n2 + n3  <M*nMax){p[n1+n2+ n3]=p[n1+n2+ n3]+tau;}

        sump = sump*randr;
        pp = d12;
        if (sump<pp) {      /*Changing number of molecule*/
            n1 = n1-1;
            n2 = n2+1;
            
        } else {pp = pp+d21;

            if (sump<pp) {
                n1 = n1+1;
                n2 = n2-1;            }
            
            else {pp = pp+d23;
                if(sump<pp){
                    n2 = n2-1;
                    n3 = n3+1;}
                else {pp = pp + d32;

                    if(sump<pp){
                        n2 = n2+1;
                        n3 = n3-1;}
                    else{pp = pp + p11;
                    
                        if (sump<pp){
                            n1 = n1-1;}
                        else {pp = pp+p21;
                    
                            if (sump< pp){
                                n2 = n2-1;}
                            else {pp = pp + p31;
                    
                                if (sump<pp){
                                    n3 = n3-1;}
                                else {pp = pp+p12;
                    
                                    if (sump<pp){
                                        n1 = n1+1;}
                                    else {pp = pp + p22;
                                    
                                        if (sump<pp){
                                            n2 = n2+1;}
                                        else {n3 = n3+1;}}}}}}}}}
//                cout << n1 <<SP << n2 <<SP<< n3<<endl;
    }//end while
    
    for (ii=0 ; ii<2*nMax; ii++ )
    {myfile << ii <<SP<<p[ii]<<endl;}
    
}//end main


