#include <bits/stdc++.h>
using namespace std;

/* ---------- SIR DERIVATIVES ---------- */
void sir(double S, double I, double R,
         double beta, double gamma, double N,
         double &dS, double &dI, double &dR)
{
    dS = -beta * S * I / N;
    dI =  beta * S * I / N - gamma * I;
    dR =  gamma * I;
}

/* ---------- EULER STEP ---------- */
void euler(double &S, double &I, double &R,
           double beta, double gamma, double N, double h)
{
    double dS, dI, dR;
    sir(S, I, R, beta, gamma, N, dS, dI, dR);
    S += h * dS;
    I += h * dI;
    R += h * dR;
}

/* ---------- RK4 STEP ---------- */
void rk4(double &S, double &I, double &R,
         double beta, double gamma, double N, double h)
{
    double dS1,dI1,dR1,dS2,dI2,dR2,dS3,dI3,dR3,dS4,dI4,dR4;

    sir(S,I,R,beta,gamma,N,dS1,dI1,dR1);
    sir(S+h*dS1/2,I+h*dI1/2,R+h*dR1/2,beta,gamma,N,dS2,dI2,dR2);
    sir(S+h*dS2/2,I+h*dI2/2,R+h*dR2/2,beta,gamma,N,dS3,dI3,dR3);
    sir(S+h*dS3,I+h*dI3,R+h*dR3,beta,gamma,N,dS4,dI4,dR4);

    S += (h/6)*(dS1+2*dS2+2*dS3+dS4);
    I += (h/6)*(dI1+2*dI2+2*dI3+dI4);
    R += (h/6)*(dR1+2*dR2+2*dR3+dR4);
}

/* ===================== Q1 ===================== */
void Q1()
{
    double S=999,I=1,R=0,N=1000,beta=0.5,gamma=0.1,h=0.1;
    for(int i=0;i<10/h;i++) euler(S,I,R,beta,gamma,N,h);
    cout<<"Q1 Infected at Day 10 = "<<I<<"\n";
}

/* ===================== Q2 ===================== */
void Q2()
{
    double S=9900,I=100,R=0,N=10000,beta=0.6,gamma=0.2,h=0.05;
    double maxI=I,tpeak=0;
    for(int i=1;i<=50/h;i++){
        euler(S,I,R,beta,gamma,N,h);
        if(I>maxI){ maxI=I; tpeak=i*h; }
    }
    cout<<"Q2 Peak at Day = "<<tpeak<<"\n";
}

/* ===================== Q3 ===================== */
void Q3()
{
    double S1=490,I1=10,R1=0,S2=490,I2=10,R2=0;
    double N=500,beta=0.4,gamma=0.1;

    for(int i=0;i<20;i++) euler(S1,I1,R1,beta,gamma,N,1.0);
    for(int i=0;i<20/0.01;i++) euler(S2,I2,R2,beta,gamma,N,0.01);

    cout<<"Q3 |Difference| = "<<fabs(S1-S2)<<"\n";
}

/* ===================== Q4 ===================== */
void Q4()
{
    double S0=1990,I0=10,N=2000,gamma=0.3,h=0.1;

    auto simulate = [&](double beta){
        double S=S0,I=I0,R=0;
        for(int i=0;i<30/h;i++) euler(S,I,R,beta,gamma,N,h);
        return I;
    };

    cout<<"Q4 Scenario A Epidemic? "<<(simulate(0.2)>I0?"YES":"NO")<<"\n";
    cout<<"Q4 Scenario B Epidemic? "<<(simulate(0.4)>I0?"YES":"NO")<<"\n";
}

/* ===================== Q5 ===================== */
void Q5()
{
    double S=140,I=10,R=850,N=1000,beta=0.5,gamma=0.1,h=0.1;
    double I0=I;
    euler(S,I,R,beta,gamma,N,h);
    cout<<"Q5 Initial slope = "<<(I-I0)/h<<"\n";
}

/* ===================== Q6 ===================== */
void Q6()
{
    double S=99990,I=10,R=0,N=100000,beta=0.4,gamma=0.15,h=0.1;
    for(int i=0;i<200/h;i++) euler(S,I,R,beta,gamma,N,h);
    cout<<"Q6 Total recovered = "<<R<<"\n";
}

/* ===================== Q7 ===================== */
void Q7()
{
    double S=990,I=10,R=0,N=1000,gamma=0.1,h=0.1;
    for(int i=0;i<40/h;i++){
        double t=i*h;
        double beta=(t<20)?0.5:0.15;
        euler(S,I,R,beta,gamma,N,h);
    }
    cout<<"Q7 Infected at Day 40 = "<<I<<"\n";
}

/* ===================== Q8 ===================== */
void Q8()
{
    double S=4995,I=5,R=0,N=5000,beta=0.5,gamma=0.1,h=0.1;
    double maxI=I;
    for(int i=0;i<100/h;i++){
        euler(S,I,R,beta,gamma,N,h);
        maxI=max(maxI,I);
    }
    cout<<"Q8 Capacity breached? "<<(maxI>1500?"YES":"NO")
        <<" | Max I = "<<maxI<<"\n";
}

/* ===================== Q9 ===================== */
void Q9()
{
    double S=99,I=1,R=0,N=100,beta=0.15,gamma=0.1,h=0.5;
    for(int i=0;i<365/h;i++) euler(S,I,R,beta,gamma,N,h);
    cout<<"Q9 Recovered after 1 year = "<<R<<"\n";
}

/* ===================== Q10 ===================== */
void Q10()
{
    double S1=900,I1=100,R1=0,S2=900,I2=100,R2=0;
    double beta=1.0,gamma=0.5,N=1000,h=0.5;

    for(int i=0;i<2/h;i++) euler(S1,I1,R1,beta,gamma,N,h);
    for(int i=0;i<2/h;i++) rk4(S2,I2,R2,beta,gamma,N,h);

    cout<<"Q10 Euler I(2) = "<<I1<<"\n";
    cout<<"Q10 RK4   I(2) = "<<I2<<"\n";
}

/* ===================== MAIN ===================== */
int main()
{
    cout<<fixed<<setprecision(6);

    Q1(); Q2(); Q3(); Q4(); Q5();
    Q6(); Q7(); Q8(); Q9(); Q10();

    return 0;
}
