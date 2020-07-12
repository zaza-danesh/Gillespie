//
//  GillespieDiffusionM.cpp
//  
//
//  Created by Zahedeh Bashardanesh on 10/20/12.
//
//

#include "GillespieDiffusionM.h"

#include <stdio.h>
#include <iostream.h>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include "include/mersenne/MersenneTwister.h"
#define V 30
#define nMax 90
#define nM  3
#define pS 9
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
//    int ii,jj;
    long int  ip=0;
    int i,j= 0;
    int N[nM] = {1, 1, 1};
    
    //    int nstep=0;
//    long int n1=0;
//    long int n2=0;
    
    double k1=.2;
    double k2=1.75;
    double kD=1;
    double lambda = 1;
    double iV = 1./(V*kD);
    double randt, randr;
    double t=0.0, tau=0.0, fT=1e3;
    double C, C4, iC4;
//    double C2, C24, iC24;
    double p11, p12, p13, sump=0.0, cumsum=0.0;
    double p21, p22, p23;
    double pp;
    double p1[nMax];
    double p2[nMax];
    double p[pS] = {0,0,0,0,0,0,0,0,0};
    double D = 0.01;
    
    R = new MTRand();
    
    
    
    char filename[132];
    sprintf(filename, "DataDiffusion.dat");
    ofstream myfile(filename);
    
    cout << N[0] << SP << N[1] <<SP << N[2]<<endl;
    
    while (t<fT){
 cout << N[0] << SP << N[1] <<SP << N[2]<<endl;
        for (i=0; i<nM ; i++){
            C = N[j]*iV;
            C4 = C*C;
            C4 = C4*C4;
            iC4 = 1./(1+C4);
            j=3*i;
            p[j] = D*N[i];
            p[j+1] = lambda*N[i];
            p[j+2] = V*k1 + V*k2*iC4;
//            cout << i << endl;
//            cout <<"p0= " << p[0]<< SP <<"p1= " << p[1]<< SP << "p2= "<< p[2]<< SP<<"p3= " <<p[3]<< SP <<"p4= " << p[4]<< SP << "p5= "<< p[5]<<endl;
        }
        
        do { /* Generate random number*/
            randt = 1.0-R->randExc();
//            cout <<randt<<endl;
        } while (!((randt>0)&&(randt<1)));
        
        
        do{
            randr = 1.0-R->randExc();
            
            
        } while(!((randr>0)&& (randr<1)));
        
        
//        if(n1 + n2<2*nMax){p[n1+n2]=p[n1+n2]+tau;}
        
        
        for (i = 0 ;i< pS; i++){
            sump+= p[i];
//            cout << "I= "<< i <<endl;
        }
        
        tau = -log(randt)/sump; /*Increasing the time*/
        t = t + tau;
        
//        cout << "SUMP " << sump <<endl;
        sump = sump*randr;
//                cout << "RANDR " << randr <<endl;
//        cout << "SUMPR " << sump <<endl;
        ip = 0;
        cumsum = 0.0;
        while (cumsum < sump){
            cumsum += p[ip];
            ip++;
//            cout << cumsum << endl;
        }
//        cout <<"ip= "<< ip << endl;
        
        int comp = (int)ip/3;
        int reaction = ip%3;
//        cout << comp <<endl;
//        cout << reaction <<endl;
        if(comp==(nM-1) && reaction == 0){}
        else{
            
        switch (reaction) {
            case 0 : N[comp] -= 1; N[comp+1] += 1; break; //Diffusion happens
            case 1 : N[comp] -= 1; break; //Decay happens
            case 2 : N[comp] += 1; break; //Production happens

        }}
        
//        cout << N[1] << SP << N[2] <<SP<<N[0]<<endl;
//        cout << pS<<endl;
        
     
        
    }//end while
}//end main


