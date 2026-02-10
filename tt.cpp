#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Global simulation parameters based on lab theory
const int NX = 101;          // 101 points to cover 100m (dx = 1.0)
const double dx = 1.0;       // Spatial step [cite: 5]
const double dt = 0.01;      // Small time step for stability [cite: 69]

// --- PROBLEM 1: Spatial Logistic Growth ---
void solveProblem1() {
    double D = 0.1, r = 0.2, K = 100.0; // [cite: 12]
    vector<double> u(NX, 0.0), u_new(NX, 0.0);
    u[NX/2] = 10.0; // Small seed population at center [cite: 12]

    for (double t = 0; t < 10.0; t += dt) {
        for (int i = 1; i < NX - 1; i++) {
            double diffusion = D * (u[i+1] - 2*u[i] + u[i-1]) / (dx*dx); // [cite: 66]
            double reaction = r * u[i] * (1.0 - u[i]/K); // [cite: 11]
            u_new[i] = u[i] + dt * (diffusion + reaction);
        }
        u = u_new;
        u[0] = 0; u[NX-1] = 0; // Dirichlet BCs [cite: 79]
    }
    cout << "Problem 1: Population at x=70, t=10: " << u[70] << endl;
}

// --- PROBLEM 2: Diffusive SIR Model ---
void solveProblem2() {
    double D = 0.1, beta = 0.001, gamma = 0.1, S = 1000.0; // [cite: 17]
    vector<double> I(NX, 0.0), I_new(NX, 0.0);
    I[0] = 50.0; // Outbreak starts at x=0 [cite: 17]

    for (double t = 0; t < 5.0; t += dt) {
        for (int i = 1; i < NX - 1; i++) {
            double diff = D * (I[i+1] - 2*I[i] + I[i-1]) / (dx*dx);
            double react = beta * S * I[i] - gamma * I[i]; // [cite: 16]
            I_new[i] = I[i] + dt * (diff + react);
        }
        I = I_new;
        I[0] = I[1]; // Neumann condition at x=0 [cite: 81]
    }
    cout << "Problem 2: Infected at x=20, t=5: " << I[20] << endl;
}

// --- PROBLEM 3: Fisher-KPP Equation ---
void solveProblem3() {
    vector<double> u(NX, 0.0), u_new(NX, 0.0);
    for(int i=0; i <= 5; i++) u[i] = 1.0; // Initial u=1 for x<=5 [cite: 21]

    for (double t = 0; t < 15.0; t += dt) {
        for (int i = 1; i < NX - 1; i++) {
            double diff = 1.0 * (u[i+1] - 2*u[i] + u[i-1]) / (dx*dx); // D=1 [cite: 20]
            double react = u[i] * (1.0 - u[i]); // [cite: 20]
            u_new[i] = u[i] + dt * (diff + react);
        }
        u = u_new;
    }
    int wave_pos = 0;
    for(int i=NX-1; i>=0; i--) { if(u[i] >= 0.5) { wave_pos = i; break; } } // [cite: 21]
    cout << "Problem 3: Wave front (u~0.5) position at t=15: x=" << wave_pos << endl;
}

// --- PROBLEM 4: Delay-Diffusion Population Model ---
void solveProblem4() {
    double D = 0.1, r = 0.2, K = 100.0, tau = 2.0; // [cite: 25]
    int delay_index = (int)(tau / dt);
    vector<vector<double>> history; // Buffer for time steps [cite: 25]
    vector<double> u(NX, 10.0);

    for (double t = 0; t < 30.0; t += dt) {
        history.push_back(u);
        vector<double> u_old = (history.size() > delay_index) ? history[history.size() - delay_index] : history[0];
        vector<double> u_new(NX, 0.0);
        for (int i = 1; i < NX - 1; i++) {
            double diff = D * (u[i+1] - 2*u[i] + u[i-1]) / (dx*dx);
            double react = r * u[i] * (1.0 - u_old[i]/K); // Delayed growth [cite: 24]
            u_new[i] = u[i] + dt * (diff + react);
        }
        u = u_new;
    }
    cout << "Problem 4: Population at x=50, t=30: " << u[50] << endl;
}

// --- PROBLEM 5: Prey-Predator Diffusion ---
void solveProblem5() {
    double D1=0.1, D2=0.05, a=0.5, b=0.02, c=0.01, d=0.2; // [cite: 28]
    vector<double> u(NX, 10.0), v(NX, 5.0), u_next(NX), v_next(NX);
    u[0] = 50.0; // Localized prey cluster [cite: 29]

    for (double t = 0; t < 10.0; t += dt) {
        for (int i = 1; i < NX - 1; i++) {
            u_next[i] = u[i] + dt * (D1*(u[i+1]-2*u[i]+u[i-1])/(dx*dx) + a*u[i] - b*u[i]*v[i]);
            v_next[i] = v[i] + dt * (D2*(v[i+1]-2*v[i]+v[i-1])/(dx*dx) + c*u[i]*v[i] - d*v[i]);
        }
        u = u_next; v = v_next;
    }
    cout << "Problem 5: Predator density v at x=10, t=10: " << v[10] << endl;
}

// --- PROBLEM 6: Chemotaxis ---
void solveProblem6() {
    double D = 0.1, chi = 0.2, dgdx = 0.5; // [cite: 35]
    vector<double> b(NX, 5.0), b_new(NX, 0.0);

    for (double t = 0; t < 20.0; t += dt) {
        for (int i = 1; i < NX - 1; i++) {
            double diff = D * (b[i+1] - 2*b[i] + b[i-1]) / (dx*dx);
            double chemotaxis = -chi * ( (b[i+1]-b[i-1])/(2*dx) * dgdx ); // [cite: 34]
            b_new[i] = b[i] + dt * (diff + chemotaxis);
        }
        b = b_new;
    }
    cout << "Problem 6: Bacterial density at x=80, t=20: " << b[80] << endl;
}

// --- PROBLEM 7: Age-Structured Population Diffusion ---
void solveProblem7() {
    double D = 0.1, mu = 0.05, da = 1.0; // [cite: 38]
    vector<double> n(NX, 10.0), n_new(NX, 0.0);

    for (double t = 0; t < 5.0; t += dt) {
        for (int i = 1; i < NX - 1; i++) {
            double diff = D * (n[i+1] - 2*n[i] + n[i-1]) / (dx*dx);
            // dn/dt = -dn/da + diff - mu*n. Using dt=da for simple age step.
            n_new[i] = n[i] + dt * (diff - mu * n[i] - n[i]/da); 
        }
        n = n_new;
    }
    cout << "Problem 7: Age density at x=10, t=5: " << n[10] << endl;
}

// --- PROBLEM 8: Advection-Reaction ---
void solveProblem8() {
    double v_river = 0.5, r = 0.2, K = 100.0; // [cite: 41, 42]
    vector<double> u(NX, 10.0), u_new(NX, 0.0);

    for (double t = 0; t < 50.0; t += dt) {
        for (int i = 1; i < NX - 1; i++) {
            double advection = -v_river * (u[i] - u[i-1]) / dx; // Upwind scheme [cite: 42]
            double reaction = r * u[i] * (1.0 - u[i]/K);
            u_new[i] = u[i] + dt * (advection + reaction);
        }
        u = u_new;
    }
    cout << "Problem 8: Density at source x=0, t=50: " << u[0] << endl;
}

// --- PROBLEM 9: Gray-Scott Pattern Formation ---
void solveProblem9() {
    double Du = 0.16, Dv = 0.08, F = 0.035, k = 0.06; // [cite: 46]
    vector<double> u(NX, 1.0), v(NX, 0.0), u_n(NX), v_n(NX);
    u[NX/2] = 0.5; v[NX/2] = 0.25; // Seed center [cite: 47]

    for (double t = 0; t < 100.0; t += dt) {
        for (int i = 1; i < NX - 1; i++) {
            u_n[i] = u[i] + dt * (Du*(u[i+1]-2*u[i]+u[i-1])/(dx*dx) - u[i]*v[i]*v[i] + F*(1.0-u[i]));
            v_n[i] = v[i] + dt * (Dv*(v[i+1]-2*v[i]+v[i-1])/(dx*dx) + u[i]*v[i]*v[i] - (F+k)*v[i]);
        }
        u = u_n; v = v_n;
    }
    cout << "Problem 9: Chemical u at center, t=100: " << u[NX/2] << endl;
}

// --- PROBLEM 10: Wound Healing ---
void solveProblem10() {
    double D = 0.05, rho = 0.1, K = 1.0; // [cite: 50]
    vector<double> c(NX, 1.0), c_new(NX, 0.0);
    for(int i=45; i<=55; i++) c[i] = 0.0; // Initial wound gap [cite: 49]

    for (double t = 0; t < 48.0; t += dt) {
        for (int i = 1; i < NX - 1; i++) {
            double diff = D * (c[i+1] - 2*c[i] + c[i-1]) / (dx*dx);
            double growth = rho * c[i] * (1.0 - c[i]/K);
            c_new[i] = c[i] + dt * (diff + growth);
        }
        c = c_new;
    }
    cout << "Problem 10: Cell density at wound center, t=48: " << c[NX/2] << endl;
}

int main() {
    solveProblem1();
    solveProblem2();
    solveProblem3();
    solveProblem4();
    solveProblem5();
    solveProblem6();
    solveProblem7();
    solveProblem8();
    solveProblem9();
    solveProblem10();
    return 0;
}
