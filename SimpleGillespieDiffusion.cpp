//
//  SimpleGillespieDiffusion.cpp
//  
//
//  Created by Zahedeh Bashardanesh on 10/18/12.
//
//

#include "SimpleGillespieDiffusion.h"

#include <stdio.h>
#include <iostream.h>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include "include/mersenne/MersenneTwister.h"
#define V 8
#define nMax 90
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
    //    long i,j,l,k;
    int ii,jj;
    int k= 1;
//    int nstep=0;
    long int n1=0, n2=0;
    double k1=.2;
    double k2=1.75;
    double kD=1;
    double lambda = 1;
    double iV = 1./(V*kD);
    double randt, randr;
    double t, tau, fT=1e4;
    double C, C4, iC4;
    double d12, d21;
    double p11, p12, p21, p22;
    double pp, sump;
    double p1[nMax];
    double p2[nMax];
    double p[M*nMax] = {0};
//    double D12 = 0.01;
//    double D21 = 0.01 ;
    double D = 0.01;

    
    R = new MTRand();
    
    //    time_t seconds,seconds1;
    //    time(&seconds);
    //    srand(seconds);
    //    idum=rand();
    //    cout<< idum<<endl;
    //    idum=-12375;
    
    
    char filename[132];
    sprintf(filename, "DataDiffusion.dat");
    ofstream myfile(filename);
    
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
        
        do { /* Generate random number*/
            randt = 1.0-R->randExc();
            
        } while (!((randt>0)&&(randt<1)));
        
        
        do{
            randr = 1.0-R->randExc();
            
            
        } while(!((randr>0)&& (randr<1)));
        
        
        
        tau = -log(randt)/sump; /*Increasing the time*/
        t = t + tau;
        if(n1 + n2<M*nMax){p[n1+n2]=p[n1+n2]+tau;}

        sump = sump*randr;
//        
//        if (sump<p11) {      /*Changing number of molecule*/
//            n1 = n1-1;
//            n2 = n2+1;
//        } else if (sump<p11+p21) {
//			n1 = n1+1;
//            n2 = n2-1;
//		}
//		else if (sump< p11 + p21 + p12){
//			n1 = n1-1;
//		}
//        else if (sump<p11 + p21 + p12 + p22){
//            n2 = n2-1;
//        }
//        else if (sump<p11 + p21 + p12 + p22 + p13){
//            n1 = n1+1;
//        }
//        else {
//            n2 = n2+1;
//        }
        pp = d12;
        if (sump<pp) {      /*Changing number of molecule*/
            n1 = n1-1;
            n2 = n2+1;
//            cout << "1"<< SP;
            
        
        } else {pp = pp+d21;
        
        if (sump<pp) {
			n1 = n1+1;
            n2 = n2-1;
//            cout << "2"<< SP;
            
		}
		else {pp = pp+p11;
        
        if (sump< pp){
			n1 = n1-1;
//            cout<< "3"<<SP;
            
		}
        else {pp = pp + p21;
        if (sump<pp){
            n2 = n2-1;
//            cout<<"4"<<SP;
            
        }
        else {pp = pp+p12;
        if (sump<pp){
            n1 = n1+1;
//            cout<<"5"<<SP;
        }
        else {
            n2 = n2+1;
//            cout<<"5"<<SP;
        }}}}}
//        myfile << x1 << SP << x2 <<endl;
//            cout << "N1= "<<n1<<SP<< "N2= "<<n2<<endl;
    }
//    cout << "N1= "<<n1<<SP<< "N2= "<<n2<<endl;
    
    for (ii=0 ; ii<M*nMax; ii++ )
    {myfile << ii <<SP<<p[ii]<<endl;
        cout << p[ii] << SP;
        cout << endl;
    }
}


