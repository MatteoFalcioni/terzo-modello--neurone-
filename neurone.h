#ifndef NEURONE_H
#define NEURONE_H

#include <vector>
#include <cmath>

enum class Parameter{Tau, Alpha, Beta};

struct PhasePoint{  //punto nello spazio delle fasi
    double V;
    double W;
};

class Neuron{
    
    double V_;
    double I_;  //I = I(t)
    double W_;  //W = W(V)
    //come faccio a mantenere costantemente la relazione dV/dt = 0? se la scrivo qua W rimane sempre lo stesso

    public:
    Neuron(double V, double I): V_{V}, I_{I} {} 
    Neuron(){}

    void SetV(double v) { V_ = v; }
    void SetI(double i) { I_ = i; }
    void SetW(double w) { W_ = w; }
    double GetV() { return V_; }
    double GetI() { return I_; }
    double GetW() { return W_; }

    void NullClina();
    std::vector<PhasePoint> Xeq(int Option);

};

#endif