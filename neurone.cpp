#include "neurone.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

void Neuron::NullClina(){
    double Vmin = -100;
    double Vmax = 100;
    double dV = 0.1;
    std::ofstream Fout("Model3.txt"); 
    for(V_= Vmin; V_<=Vmax; V_+=dV){
        W_ = V_ - std::pow(V_, 3)/3 + I_ ;
        double R = V_ + 1 ;
        Fout<<V_<<'\t'<<W_<<'\t'<<R<<'\n';
    }
    std::cout<<"The V-Nullclina and W-Nullclina points have been saved in Model3.txt"<<'\n';
    Fout.close();
}

std::vector<PhasePoint> Neuron::Xeq(int Option){ //intersezione tra cubica dx/dt=0 e retta dW/dt=0

    std::vector<PhasePoint> Xeq;
    double T = 0.08;
    double A = 0.7;
    double B = 0.8;
    double C = (1-B*T);
    double dV = 0.001;   //granularità, ad es. di 0.1 mV in V e W
    double Vmin = -100;
    double Vmax = 100;

    for(V_=Vmin; V_<=Vmax; V_+=dV){
        W_ = V_ - std::pow(V_, 3)/3 + I_ ;
        if( ( W_ >= 1/C*(V_ - std::pow(V_,3) + I_ - T*V_ - A*T) - 0.01 ) && ( W_ <= 1/C*(V_ - std::pow(V_,3) + I_ - T*V_ - A*T) + 0.01 ) ) {
            PhasePoint X{V_,W_};
            Xeq.push_back(X);
        }
    }
    std::cout<<"# of interceptions found: "<<Xeq.size()<<'\n';

    if (Option == 1) {
        for (int i=0; i<Xeq.size(); ++i){
            std::cout<< "printing equilibrium points in Phase Space (V,W)" << '\n';
            std::cout<< Xeq[i].V <<" ; "<< Xeq[i].W << '\n';
        }
    }

    return Xeq;
}

