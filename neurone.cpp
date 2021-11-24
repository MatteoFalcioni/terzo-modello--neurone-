#include "neurone.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

void Neuron::NullClina(){
    double Vmin = -2.5;
    double Vmax = 2.5;
    double dV = 0.001;
    std::ofstream Fout("Nullclina.txt"); 
    for(V_= Vmin; V_<=Vmax; V_+=dV){
        W_ = V_ - std::pow(V_, 3)/3 + I_ ;  //V nullclina
        double R = (1/0.8)*V_ + 0.7/0.8 ;  //W nullclina
        Fout<<V_<<'\t'<<W_<<'\t'<<R<<'\n';
    }
    std::cout<<"The V-Nullclina and W-Nullclina have been saved in Model3.txt"<<'\n';
    Fout.close();
}

std::vector<PhasePoint> Neuron::Xeq(int Option){ //intersezione tra cubica dx/dt=0 e retta dW/dt=0

    std::vector<PhasePoint> Xeq;
    double dV = 0.001;   //granularità, ad es. di 0.1 mV in V e W
    double Vmin = -2.5;
    double Vmax = 2.5;

    for(V_=Vmin; V_<=Vmax; V_+=dV){
        W_ = V_ - std::pow(V_, 3)/3 + I_ ;
        if( ( V_ - std::pow(V_,3)/3 - W_ + I_ >= V_ + A - B*W_ - 0.01 ) && ( V_ - std::pow(V_,3)/3 - W_ + I_ <= V_ + A - B*W_ + 0.01 ) ) { 
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

void Neuron::Evolve(double Tmax){
    double dt = 0.001; //misura in millisecondi
    double dV = (V_ - std::pow(V_,3) - W_ + I_)*dt; 
    double dW = (V_ + A - B*W_)*dt;
    double dI = 0.01;
    std::ofstream Fout1("V(t).txt");  //potenziale d'azione del neurone
    std::ofstream Fout2("W(V).txt");  //traiettoria effettiva nella sp. delle fasi

    for(double t=0; t<Tmax; t+=dt){
        V_ += dV;
        W_ += dW;
        I_ += dI;
        Fout1<<t<<'\t'<<V_<<'\n';
        Fout2<<V_<<'\t'<<W_<<'\n';
    }
    Fout1.close();
    Fout2.close();
}