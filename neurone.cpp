#include "neurone.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

void Neuron::NullClina(){
    double Vmin = -2.5;
    double Vmax = 2.5;
    double dV = 0.1;
    std::ofstream Fout("Model3.txt"); 
    for(V_= Vmin; V_<=Vmax; V_+=dV){
        W_ = V_ - std::pow(V_, 3)/3 + I_ ;
        double R = (1/0.8)*V_ + 0.7/0.8 ;
        Fout<<V_<<'\t'<<W_<<'\t'<<R<<'\n';
    }
    std::cout<<"The V-Nullclina and W-Nullclina have been saved in Model3.txt"<<'\n';
    Fout.close();
}

std::vector<PhasePoint> Neuron::Xeq(int Option){ //intersezione tra cubica dx/dt=0 e retta dW/dt=0

    std::vector<PhasePoint> Xeq;
    double T = 0.08;
    double A = 0.7;
    double B = 0.8;
    double dV = 0.001;   //granularità, ad es. di 0.1 mV in V e W
    double Vmin = -2.5;
    double Vmax = 2.5;

    for(V_=Vmin; V_<=Vmax; V_+=dV){
        W_ = V_ - std::pow(V_, 3)/3 + I_ ;
        if( ( V_ - std::pow(V_,3) - W_ + I_ >= V_ + A - B*W_ - 0.01 ) && ( V_ - std::pow(V_,3) - W_ + I_ <= V_ + A - B*W_ + 0.01 ) ) { //è sbagliato il calcolo
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

