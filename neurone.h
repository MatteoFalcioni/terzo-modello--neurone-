#ifndef NEURONE_H
#define NEURONE_H

#include <vector>
#include <cmath>

struct PhasePoint{  //punto nello spazio delle fasi
    double V;
    double W;
};

class Neuron{
    
    double V_;
    double I_;  //I = I(t)
    double W_;  

    double T = 0.08;
    double A = 0.7;
    double B = 0.8;

    public:
    Neuron(double V, double I, double W): V_{V}, I_{I}, W_{W} {} 
    Neuron(){}

    void SetV(double v) { V_ = v; }
    void SetI(double i) { I_ = i; }
    void SetW(double w) { W_ = w; }
    void SetT(double t) { T = t; }
    void SetA(double a) { A = a; } 
    void SetB(double b) { B = b; }   
    double GetV() { return V_; }
    double GetI() { return I_; }
    double GetW() { return W_; }

    void NullClina();
    void Xeq(int Option);
    void Evolve(double Tmax);

};

#endif