#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Global constant for spatial step [cite: 75]
const double DX = 0.01;

// Problem 1: Triangular Pulse Advection [cite: 80]
void solveProblem1() {
    double L = 1.0, u = 0.6, t_final = 0.5, dt = 0.01;
    int nx = (int)(L / DX) + 1;
    int nt = (int)(t_final / dt);
    double C = (u * dt) / DX; // C = 0.6 [cite: 84]

    vector<double> rho(nx), rho_new(nx);
    for (int i = 0; i < nx; i++) {
        double x = i * DX;
        if (x >= 0.1 && x <= 0.2) rho[i] = 10.0 * (x - 0.1);
        else if (x > 0.2 && x <= 0.3) rho[i] = 10.0 * (0.3 - x);
        else rho[i] = 0.0;
    }

    for (int n = 0; n < nt; n++) {
        for (int i = 1; i < nx; i++) rho_new[i] = rho[i] - C * (rho[i] - rho[i-1]);
        rho_new[0] = 0.0;
        rho = rho_new;
    }
    cout << "Problem 1: rho(0.5, 0.5) = " << fixed << setprecision(4) << rho[(int)(0.5/DX)] << endl;
}

// Problem 2: Exponential Velocity Profile [cite: 87]
void solveProblem2() {
    double L = 2.0, t_final = 0.4, dt = 0.005;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx), rho_new(nx);

    for (int i = 0; i < nx; i++) rho[i] = 1.0 + 0.5 * cos(M_PI * i * DX);

    for (int n = 0; n < nt; n++) {
        for (int i = 1; i < nx; i++) {
            double u_i = exp(-(i * DX));
            double u_prev = exp(-((i-1) * DX));
            // Conservative form [cite: 372, 373]
            rho_new[i] = rho[i] - (dt / DX) * (u_i * rho[i] - u_prev * rho[i-1]);
        }
        rho_new[0] = rho[0]; 
        rho = rho_new;
    }
    cout << "Problem 2: rho(1.0, 0.4) = " << rho[(int)(1.0/DX)] << endl;
}

// Problem 3: Heat-Tracer in a Pulsed Inlet [cite: 91]
void solveProblem3() {
    double L = 3.0, u = 0.3, t_final = 5.0, dt = 0.01;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx, 0.0), rho_new(nx, 0.0);

    for (int n = 0; n < nt; n++) {
        double t = n * dt;
        for (int i = 1; i < nx; i++) rho_new[i] = rho[i] - (u * dt / DX) * (rho[i] - rho[i-1]);
        // Pulsed condition [cite: 93]
        int k = (int)(t / 0.5);
        if (t >= 0.5*k && t <= 0.5*k + 0.25) rho_new[0] = 1.0;
        else rho_new[0] = 0.0;
        rho = rho_new;
    }
    cout << "Problem 3: rho(1.5, 5.0) = " << rho[(int)(1.5/DX)] << endl;
}

// Problem 4: Two-Species Advection [cite: 96]
void solveProblem4() {
    double L = 1.0, u = 0.5, k = 0.5, t_final = 0.5, dt = 0.01;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rA(nx, 1.0), rB(nx), rA_new(nx), rB_new(nx);

    for (int i = 0; i < nx; i++) rB[i] = exp(-50.0 * pow(i*DX - 0.5, 2));

    for (int n = 0; n < nt; n++) {
        for (int i = 1; i < nx; i++) {
            double reaction = k * rA[i] * rB[i] * dt; // Source term [cite: 304]
            rA_new[i] = rA[i] - (u * dt / DX) * (rA[i] - rA[i-1]) - reaction;
            rB_new[i] = rB[i] - (u * dt / DX) * (rB[i] - rB[i-1]) - reaction;
        }
        rA_new[0] = 1.0; rB_new[0] = 0.0;
        rA = rA_new; rB = rB_new;
    }
    cout << "Problem 4: rA(0.7) = " << rA[(int)(0.7/DX)] << ", rB(0.7) = " << rB[(int)(0.7/DX)] << endl;
}

// Problem 5: Reflecting Boundary Condition [cite: 102]
void solveProblem5() {
    double L = 1.0, u = 0.4, t_final = 1.5, dt = 0.005;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx, 0.0), rho_new(nx, 0.0);

    for (int i = 0; i < nx; i++) {
        double x = i * DX;
        if (x >= 0.6 && x <= 0.8) rho[i] = 2.0;
    }

    for (int n = 0; n < nt; n++) {
        for (int i = 1; i < nx - 1; i++) rho_new[i] = rho[i] - (u * dt / DX) * (rho[i] - rho[i-1]);
        rho_new[nx-1] = rho_new[nx-2]; // Reflecting wall/zero-gradient [cite: 103, 320]
        rho_new[0] = 0.0;
        rho = rho_new;
    }
    cout << "Problem 5: rho(0.4, 1.5) = " << rho[(int)(0.4/DX)] << endl;
}

// Problem 6: Lax-Friedrichs vs Upwind [cite: 109]
void solveProblem6() {
    double L = 1.0, u = 1.0, t_final = 0.3, dt = 0.008;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rU(nx), rLF(nx), rU_new(nx), rLF_new(nx);

    for (int i = 0; i < nx; i++) rU[i] = rLF[i] = (i*DX < 0.5) ? 1.0 : 0.0;

    for (int n = 0; n < nt; n++) {
        for (int i = 1; i < nx - 1; i++) {
            rU_new[i] = rU[i] - (u * dt / DX) * (rU[i] - rU[i-1]);
            // Lax-Friedrichs formula [cite: 55, 366]
            rLF_new[i] = 0.5*(rLF[i+1] + rLF[i-1]) - 0.5*(u*dt/DX)*(rLF[i+1] - rLF[i-1]);
        }
        rU_new[0] = rLF_new[0] = 1.0;
        rU = rU_new; rLF = rLF_new;
    }
    cout << "Problem 6: Upwind=" << rU[(int)(0.8/DX)] << ", Lax-Friedrichs=" << rLF[(int)(0.8/DX)] << endl;
}

// Problem 7: Converging-Diverging Nozzle [cite: 117]
void solveProblem7() {
    double L = 2.0, u0 = 1.0, t_final = 0.8, dt = 0.005;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx), rho_new(nx);

    for (int i = 0; i < nx; i++) rho[i] = cos(M_PI * i * DX / 2.0);

    for (int n = 0; n < nt; n++) {
        for (int i = 1; i < nx; i++) {
            double Ax = 1.0 + 0.5 * sin(M_PI * i * DX / 2.0); // Area [cite: 119]
            double ux = u0 / Ax; // Incompressible flow condition [cite: 120]
            rho_new[i] = rho[i] - (ux * dt / DX) * (rho[i] - rho[i-1]);
        }
        rho_new[0] = cos(0);
        rho = rho_new;
    }
    cout << "Problem 7: rho(1.0, 0.8) = " << rho[(int)(1.0/DX)] << endl;
}

// Problem 8: Oscillating Velocity Field [cite: 124]
void solveProblem8() {
    double L = 1.0, t_final = 2.0, dt = 0.001;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx), rho_new(nx);

    for (int i = 0; i < nx; i++) rho[i] = 1.0 + 0.3 * sin(4.0 * M_PI * i * DX);

    for (int n = 0; n < nt; n++) {
        double ut = sin(2.0 * M_PI * n * dt);
        for (int i = 0; i < nx; i++) {
            int im1 = (i - 1 + (nx-1)) % (nx-1); // Periodic indexing [cite: 127, 318]
            int ip1 = (i + 1) % (nx-1);
            if (ut > 0) rho_new[i] = rho[i] - (ut * dt / DX) * (rho[i] - rho[im1]);
            else rho_new[i] = rho[i] - (ut * dt / DX) * (rho[ip1] - rho[i]);
        }
        rho = rho_new;
    }
    cout << "Problem 8: x=0.25: " << rho[(int)(0.25/DX)] << ", x=0.75: " << rho[(int)(0.75/DX)] << endl;
}

// Problem 9: Linear Source Term [cite: 132]
void solveProblem9() {
    double L = 1.0, u = 0.5, alpha = 1.0, t_final = 10.0, dt = 0.01;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx, 0.0), rho_new(nx, 0.0);

    for (int n = 0; n < nt; n++) {
        for (int i = 1; i < nx; i++) {
            double source = alpha * (1.0 - rho[i]) * dt; // Production term [cite: 133]
            rho_new[i] = rho[i] - (u * dt / DX) * (rho[i] - rho[i-1]) + source;
        }
        rho_new[0] = 0.0;
        rho = rho_new;
    }
    cout << "Problem 9: rho(0.6, 10.0) = " << rho[(int)(0.6/DX)] << endl;
}

// Problem 10: Traffic Flow Shock [cite: 139]
void solveProblem10() {
    double L = 1.0, umax = 1.0, rmax = 1.0, t_final = 0.3, dt = 0.001, dx_loc = 0.005;
    int nx = (int)(L / dx_loc) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx), rho_new(nx);

    for (int i = 0; i < nx; i++) rho[i] = (i * dx_loc < 0.4) ? 0.2 : 0.8;

    for (int n = 0; n < nt; n++) {
        for (int i = 1; i < nx; i++) {
            // Nonlinear flux F(rho) [cite: 141, 144]
            double flux_i = rho[i] * umax * (1.0 - rho[i] / rmax);
            double flux_prev = rho[i-1] * umax * (1.0 - rho[i-1] / rmax);
            rho_new[i] = rho[i] - (dt / dx_loc) * (flux_i - flux_prev);
        }
        rho_new[0] = 0.2;
        rho = rho_new;
    }
    cout << "Problem 10: x=0.3: " << rho[(int)(0.3/dx_loc)] << ", x=0.6: " << rho[(int)(0.6/dx_loc)] << endl;
}

// Problem 11: Rotating Drum [cite: 146]
void solveProblem11() {
    double L = 2.0 * M_PI, u = 0.5, t_final = 4.0 * M_PI, ds = 0.01, dt = 0.01;
    int nx = (int)(L / ds) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx), rho_new(nx);

    for (int i = 0; i < nx; i++) rho[i] = exp(-8.0 * pow(i*ds - M_PI, 2));

    for (int n = 0; n < nt; n++) {
        for (int i = 0; i < nx; i++) {
            int im1 = (i - 1 + (nx-1)) % (nx-1); // Periodic [cite: 147]
            rho_new[i] = rho[i] - (u * dt / ds) * (rho[i] - rho[im1]);
        }
        rho = rho_new;
    }
    cout << "Problem 11: rho(pi, 4pi) = " << rho[(int)(M_PI/ds)] << endl;
}

// Problem 12: Double-Peak Initial Condition [cite: 152]
void solveProblem12() {
    double L = 2.0, u = 1.0, t_final = 0.4, dt = 0.005;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx), rho_new(nx);

    for (int i = 0; i < nx; i++) {
        double x = i * DX;
        rho[i] = 2.0 * exp(-100.0 * pow(x-0.3, 2)) + exp(-100.0 * pow(x-0.7, 2));
    }

    for (int n = 0; n < nt; n++) {
        for (int i = 1; i < nx; i++) rho_new[i] = rho[i] - (u * dt / DX) * (rho[i] - rho[i-1]);
        rho_new[0] = 0.0;
        rho = rho_new;
    }
    cout << "Problem 12: x=0.7: " << rho[(int)(0.7/DX)] << ", x=1.1: " << rho[(int)(1.1/DX)] << endl;
}

// Problem 13: Variable Density Inlet [cite: 159]
void solveProblem13() {
    double L = 4.0, u = 0.8, t_final = 5.0, dt = 0.005;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx, 1.0), rho_new(nx, 1.0);

    for (int n = 0; n < nt; n++) {
        double t = n * dt;
        for (int i = 1; i < nx; i++) rho_new[i] = rho[i] - (u * dt / DX) * (rho[i] - rho[i-1]);
        rho_new[0] = 1.0 + 0.5 * t * exp(-0.5 * t); // Inlet [cite: 161]
        rho_new[nx-1] = rho_new[nx-2];
        rho = rho_new;
    }
    cout << "Problem 13: rho(2.0, 5.0) = " << rho[(int)(2.0/DX)] << endl;
}

// Problem 14: Gravitational Source [cite: 165]
void solveProblem14() {
    double L = 1.0, u = 0.3, g = 0.5, t_final = 2.0, dt = 0.025;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx), rho_new(nx);

    for (int i = 0; i < nx; i++) rho[i] = 1.0 + i * DX;

    for (int n = 0; n < nt; n++) {
        for (int i = 1; i < nx; i++) {
            double source = -g * rho[i] * dt; // Gravity [cite: 166]
            rho_new[i] = rho[i] - (u * dt / DX) * (rho[i] - rho[i-1]) + source;
        }
        rho_new[0] = 1.0;
        rho = rho_new;
    }
    cout << "Problem 14: rho(0.5, 2.0) = " << rho[(int)(0.5/DX)] << endl;
}

// Problem 15: High-Frequency Component [cite: 170]
void solveProblem15() {
    double L = 1.0, u = 0.5, t_final = 1.0, dt = 0.01;
    int nx = (int)(L / DX) + 1, nt = (int)(t_final / dt);
    vector<double> rho(nx), rho_new(nx);

    for (int i = 0; i < nx; i++) rho[i] = sin(M_PI * i * DX) + 0.1 * sin(20.0 * M_PI * i * DX);

    for (int n = 0; n < nt; n++) {
        for (int i = 0; i < nx; i++) {
            int im1 = (i - 1 + (nx-1)) % (nx-1);
            rho_new[i] = rho[i] - (u * dt / DX) * (rho[i] - rho[im1]);
        }
        rho = rho_new;
    }
    cout << "Problem 15: rho(0.5, 1.0) = " << rho[(int)(0.5/DX)] << endl;
}

int main() {
    cout << "Numerical Simulation of Continuity Equation Results:" << endl;
    cout << "----------------------------------------------------" << endl;
    solveProblem1(); solveProblem2(); solveProblem3(); solveProblem4(); solveProblem5();
    solveProblem6(); solveProblem7(); solveProblem8(); solveProblem9(); solveProblem10();
    solveProblem11(); solveProblem12(); solveProblem13(); solveProblem14(); solveProblem15();
    return 0;
}
