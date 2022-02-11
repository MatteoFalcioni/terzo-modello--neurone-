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
        W_ = V_ - std::pow(V_, 3)/3 + I_ ;  //V nullclina, cioè dV/dt = 0
        double R = (1/B)*V_ + A/B ;   //W nullclina, dW/dt = 0
        Fout<<V_<<'\t'<<W_<<'\t'<<R<<'\n';
    }
    std::cout<<"The V-Nullclina and W-Nullclina have been saved in Nullclina.txt"<<'\n';
    Fout.close();
}

void Neuron::Xeq(int Option){ //intersezione tra cubica dx/dt=0 e retta dW/dt=0

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

    PhasePoint Xavg{};
    for(int i=0; i<Xeq.size(); ++i){
        Xavg.V += ( Xeq[i].V / Xeq.size() ) ;
        Xavg.W += ( Xeq[i].W / Xeq.size() ) ;
    }
    std::cout<<"The average position of the equilibrium point is: ("<<Xavg.V<<","<<Xavg.W<<")"<<'\n';

    if (Option == 1) {
        for (int i=0; i<Xeq.size(); ++i){
            std::cout<< "printing equilibrium points in Phase Space (V,W)" << '\n';
            std::cout<< Xeq[i].V <<" ; "<< Xeq[i].W << '\n';
        }
    }

}

void Neuron::Evolve(double Tmax){  //T in millisecondi
    double dt = 1; 
    double dI = 0.5;            
    std::ofstream Fout1("V(t).txt");  //potenziale d'azione del neurone
    std::ofstream Fout2("W(V).txt");  //traiettoria effettiva nella sp. delle fasi

    for(double t=0; t<Tmax; t+=dt){
        double dV = (V_ - std::pow(V_,3)/3 - W_ + I_)*dt; 
        double dW = T*(V_ + A - B*W_)*dt;
        V_ += dV;
        W_ += dW;
        if (t==2) {I_ += dI;}
        if (t==3) {I_ -= dI;}
        Fout1<<t<<'\t'<<V_<<'\n';
        Fout2<<V_<<'\t'<<W_<<'\n';
    }
    
    std::cout<< "the neuron's action potential and its trajectory in phase space have been saved in files V(t) and W(V) respectively" << '\n';
    Fout1.close();
    Fout2.close();
}