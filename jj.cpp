#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Q1: Numerical Integration (RK4)
void solveQ1() {
    double x = 0.0, y = 1.0, h = 0.1;
    auto f = [](double x, double y) { return x + y; };

    cout << "--- Q1: RK4 Intermediate Values (First Step) ---" << endl;
    for (int i = 0; i < 3; i++) {
        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2.0, y + k1 / 2.0);
        double k3 = h * f(x + h / 2.0, y + k2 / 2.0);
        double k4 = h * f(x + h, y + k3);
        
        if (i == 0) {
            cout << "k1: " << k1 << ", k2: " << k2 << ", k3: " << k3 << ", k4: " << k4 << endl;
        }
        
        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
        x += h;
    }
    cout << "Final Result y(0.3): " << y << "\n" << endl;
}

// Q2: Delay Differential Equations (Hutchinson's Equation)
void solveQ2() {
    double r = 1.2, K = 100.0, tau = 0.8, dt = 0.01, T = 5.0;
    int steps = (int)(T / dt);
    int delay_steps = (int)(tau / dt);
    vector<double> N(steps + 1, 10.0); // N(t)=10 for t <= 0

    for (int i = 0; i < steps; i++) {
        double N_delayed = (i - delay_steps < 0) ? 10.0 : N[i - delay_steps];
        double dN = r * N[i] * (1.0 - N_delayed / K);
        N[i + 1] = N[i] + dN * dt;
    }
    cout << "--- Q2: Hutchinson's Equation ---" << endl;
    cout << "N(5.0): " << N[steps] << "\n" << endl;
}

// Q3: Predator-Prey (Lotka-Volterra)
void solveQ3() {
    double x = 20.0, y = 10.0, t = 0.0, T = 20.0, h = 0.01;
    auto fx = [](double x, double y) { return 1.2 * x - 0.6 * x * y; };
    auto fy = [](double x, double y) { return 0.3 * x * y - 0.8 * y; };

    while (t < T) {
        double kx1 = h * fx(x, y), ky1 = h * fy(x, y);
        double kx2 = h * fx(x + kx1/2, y + ky1/2), ky2 = h * fy(x + kx1/2, y + ky1/2);
        double kx3 = h * fx(x + kx2/2, y + ky2/2), ky3 = h * fy(x + kx2/2, y + ky2/2);
        double kx4 = h * fx(x + kx3, y + ky3), ky4 = h * fy(x + kx3, y + ky3);
        
        x += (kx1 + 2 * kx2 + 2 * kx3 + kx4) / 6.0;
        y += (ky1 + 2 * ky2 + 2 * ky3 + ky4) / 6.0;
        t += h;
    }
    cout << "--- Q3: Lotka-Volterra at T=20 ---" << endl;
    cout << "Prey (x): " << x << ", Predator (y): " << y << "\n" << endl;
}

// Q4: Piecewise Disease Modeling (SIR logic)
void solveQ4() {
    double S = 990.0, I = 10.0, gamma = 0.1, N = 1000.0, h = 0.1;
    for (double t = 0; t < 40.0; t += h) {
        double beta = (t < 20.0) ? 0.5 : 0.15;
        double dS = -beta * S * I / N;
        double dI = (beta * S * I / N) - (gamma * I);
        S += dS * h;
        I += dI * h;
    }
    cout << "--- Q4: Epidemic Intervention ---" << endl;
    cout << "Infected (I) at t=40: " << I << "\n" << endl;
}

// Q5: Parameter Sensitivity (R0 Matrix)
void solveQ5() {
    double beta_min = 0.1, beta_max = 0.5;
    double gamma_min = 0.05, gamma_max = 0.25;
    cout << "--- Q5: R0 Matrix (Beta rows, Gamma cols) ---" << endl;
    for (int i = 0; i < 5; i++) {
        double b = beta_min + i * (beta_max - beta_min) / 4.0;
        for (int j = 0; j < 5; j++) {
            double g = gamma_min + j * (gamma_max - gamma_min) / 4.0;
            cout << setw(8) << b / g << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Q6: Reaction-Diffusion (FTCS)
void solveQ6() {
    double D = 0.1, r = 0.2, K = 100.0, dx = 1.0, dt = 0.1;
    int nx = 101, nt = 100; // 100m domain, 10s time
    vector<double> u(nx, 0.0), unew(nx, 0.0);
    u[50] = 1.0; // Seed at center

    for (int t = 0; t < nt; t++) {
        for (int i = 1; i < nx - 1; i++) {
            double diffusion = D * (u[i + 1] - 2 * u[i] + u[i - 1]) / (dx * dx);
            double reaction = r * u[i] * (1.0 - u[i] / K);
            unew[i] = u[i] + (diffusion + reaction) * dt;
        }
        u = unew;
    }
    cout << "--- Q6: Reaction-Diffusion ---" << endl;
    cout << "u at x=70, t=10: " << u[70] << "\n" << endl;
}

// Q7: Advection (Upwind Scheme)
void solveQ7() {
    double u_vel = 0.8, dx = 0.1, dt = 0.01, T = 0.4;
    int nx = 20, nt = (int)(T / dt);
    vector<double> rho(nx, 0.0);
    for (int i = 0; i < 10; i++) rho[i] = 1.0; // Step function

    for (int t = 0; t < nt; t++) {
        vector<double> next_rho = rho;
        for (int i = 1; i < nx; i++) {
            next_rho[i] = rho[i] - u_vel * (dt / dx) * (rho[i] - rho[i - 1]);
        }
        rho = next_rho;
    }
    cout << "--- Q7: Upwind Advection ---" << endl;
    cout << "rho at x=0.6, t=0.4: " << rho[6] << "\n" << endl;
}

// Q8: Continuity Equation
void solveQ8() {
    // d(rho)/dt + d(rho*u)/dx = 0
    // d(rho)/dt = -rho0 * e^-t
    // d(rho*u)/dx = rho * du/dx + u * d(rho)/dx
    // Since u = ax, du/dx = a.
    // -rho = rho*a + u * d(rho)/dx  => d(rho)/dx = (-rho - rho*a) / u
    double rho0 = 1.2, a = 0.2, t = 1.0, x = 2.0;
    double rho = rho0 * exp(-t);
    double u = a * x;
    double drho_dt = -rho0 * exp(-t);
    double drho_dx = (-drho_dt - rho * a) / u;

    cout << "--- Q8: Continuity Equation ---" << endl;
    cout << "d(rho)/dx at x=2.0, t=1.0: " << drho_dx << "\n" << endl;
}

// Q9: Stagnation Point
void solveQ9() {
    double m = 12.0, U = 3.0;
    // Velocity u = U + m / (2 * PI * x)
    // Stagnation: U + m / (2 * PI * x) = 0 => x = -m / (2 * PI * U)
    double x_stag = -m / (2.0 * M_PI * U);
    cout << "--- Q9: Stagnation Point ---" << endl;
    cout << "x-coordinate: " << x_stag << "\n" << endl;
}

// Q10: Pathline Tracking (Euler Integration)
void solveQ10() {
    double x = 1.0, y = 1.0, t = 0.0, dt = 0.001;
    while (t < 0.5) {
        x += (x * (1.0 + 2.0 * t)) * dt;
        y += y * dt;
        t += dt;
    }
    cout << "--- Q10: Pathline Tracking ---" << endl;
    cout << "Position at t=0.5: (" << x << ", " << y << ")" << endl;
}

int main() {
    cout << fixed << setprecision(6);
    solveQ1();
    solveQ2();
    solveQ3();
    solveQ4();
    solveQ5();
    solveQ6();
    solveQ7();
    solveQ8();
    solveQ9();
    solveQ10();
    return 0;
}
