#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// --- Problem 1: Streamline Equation in 2D Steady Flow ---
void solveProblem1() {
    double x = 1.0, y = 1.0; // Starting point (1,1)
    double targetX = 2.5;
    double dx = 0.001; // Step size for Euler integration
    
    // Streamline: dy/dx = v/u
    while (x < targetX) {
        double u = pow(x, 2) - pow(y, 2);
        double v = -2 * x * y;
        y += (v / u) * dx;
        x += dx;
    }
    cout << "Problem 1: y-coordinate at x=2.5 is " << fixed << setprecision(4) << y << endl;
}

// --- Problem 2: Pathline in Unsteady Flow ---
void solveProblem2() {
    double x = 1.0, y = 1.0; // (1,1) at t=0
    double t = 0.0;
    double dt = 0.001;
    double targetT = 0.5;

    while (t < targetT) {
        double u = x * (1 + 2 * t);
        double v = y;
        x += u * dt;
        y += v * dt;
        t += dt;
    }
    cout << "Problem 2: Particle position at t=0.5 is (" << x << ", " << y << ")" << endl;
}

// --- Problem 3: Stream Function and Flow Rate ---
void solveProblem3() {
    double x = 2.0, y = 3.0; // Point (2,3)
    // u = d(psi)/dy, v = -d(psi)/dx
    double u = pow(x, 2) - pow(y, 2);
    double v = -(2 * x * y);
    
    // Flow rate Q = psi(1,1) - psi(0,0)
    auto psi = [](double x_val, double y_val) { return pow(x_val, 2) * y_val - (1.0/3.0) * pow(y_val, 3); };
    double Q = abs(psi(1, 1) - psi(0, 0));
    
    cout << "Problem 3: Velocity at (2,3) is u=" << u << ", v=" << v << ". Volume flow rate Q=" << Q << endl;
}

// --- Problem 4: Velocity Potential ---
void solveProblem4() {
    double A = 0.5, x = 3.0, y = 4.0;
    // u = d(phi)/dx = 2Ax, v = d(phi)/dy = -2Ay
    double u = 2 * A * x;
    double v = -2 * A * y;
    double velocityMag = sqrt(u*u + v*v);
    cout << "Problem 4: Velocity magnitude at (3,4) is " << velocityMag << endl;
}

// --- Problem 5: Incompressible Continuity Check ---
void solveProblem5() {
    double x = 1.0, y = 2.0, h = 0.001;
    auto getU = [](double _x, double _y) { return (10 * _x) / (pow(_x, 2) + pow(_y, 2)); };
    auto getV = [](double _x, double _y) { return (10 * _y) / (pow(_x, 2) + pow(_y, 2)); };

    double dudx = (getU(x + h, y) - getU(x - h, y)) / (2 * h);
    double dvdy = (getV(x, y + h) - getV(x, y - h)) / (2 * h);
    double divergence = dudx + dvdy;

    cout << "Problem 5: Divergence at (1,2) is " << divergence << (abs(divergence) < 1e-5 ? " (Incompressible)" : " (Compressible)") << endl;
}

// --- Problem 6: Integrated Potential and Stream Function ---
void solveProblem6() {
    double x = 1.5, y = 2.5;
    // phi = x^2 + 4xy - y^2
    // u = d(phi)/dx = 2x + 4y | v = d(phi)/dy = 4x - 2y
    double u = 2*x + 4*y;
    double v = 4*x - 2*y;
    double V = sqrt(u*u + v*v);
    
    // From u = d(psi)/dy and v = -d(psi)/dx: psi = 2y^2 - 2x^2 + 4xy
    double psi = 2*pow(y, 2) - 2*pow(x, 2) + 4*x*y;
    
    cout << "Problem 6: Velocity Mag=" << V << ", Stream Function=" << psi << endl;
}

// --- Problem 7: Vorticity ---
void solveProblem7() {
    double x = 1.0, y = 1.0;
    // u = y^2, v = x^2
    // omega_z = dv/dx - du/dy = 2x - 2y
    double vorticity = 2*x - 2*y;
    cout << "Problem 7: Vorticity at (1,1) is " << vorticity << endl;
}

// --- Problem 8: Equation of Continuity (Compressible) ---
void solveProblem8() {
    double x = 2.0, t = 1.0, a = 0.2, rho0 = 1.2;
    // drho/dt + d(rho*u)/dx = 0  => drho/dt + u(drho/dx) + rho(du/dx) = 0
    // rho = rho0 * e^-t  => drho/dt = -rho0 * e^-t
    // u = ax => du/dx = a
    double rho = rho0 * exp(-t);
    double drhodt = -rho;
    double dudx = a;
    double u = a * x;
    
    // Solve for drho/dx: drho/dx = (-drhodt - rho*dudx) / u
    double drhodx = (-drhodt - (rho * dudx)) / u;
    cout << "Problem 8: drho/dx at x=2.0 is " << drhodx << endl;
}

// --- Problem 9: Acceleration of a Fluid Particle ---
void solveProblem9() {
    double x = 5.0, t = 2.0, U0 = 2.0, a = 0.1, L = 10.0;
    // Du/Dt = du/dt + u(du/dx)
    double denom = (1.0 - x/L);
    double dudt = (U0 * a) / denom;
    double u = (U0 * (1 + a * t)) / denom;
    double dudx = (U0 * (1 + a * t) * (1.0/L)) / pow(denom, 2);
    
    double totalAcc = dudt + u * dudx;
    cout << "Problem 9: Total acceleration Du/Dt is " << totalAcc << endl;
}

// --- Problem 10: Potential Flow around Cylinder ---
void solveProblem10() {
    double x = 3.0, y = 2.0;
    // phi = 2xy => u = dphi/dx = 2y, v = dphi/dy = 2x
    double u = 2 * y;
    double v = 2 * x;
    double speed = sqrt(u*u + v*v);
    cout << "Problem 10: Speed at (3,2) is " << speed << endl;
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
