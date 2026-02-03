#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

class BioModels {
public:
    // Problem 1: Reaching Carrying Capacity (Logistic Growth)
    static void problem1_LogisticGrowth() {
        double N = 10.0, r = 0.5, K = 1000.0, dt = 0.01, t = 0;
        bool crossed95 = false;

        while (t < 50.0) { // Time limit to prevent infinite loops
            double dN = r * N * (1 - N / K);
            N += dN * dt;
            t += dt;

            if (!crossed95 && N >= 0.95 * K) {
                cout << "Problem 1: Population crossed 95% of K at t = " << t << endl;
                crossed95 = true;
                break;
            }
        }
    }

    // Problem 2: The Epidemic Peak (SIR Model)
    static void problem2_SIRModel() {
        double S = 999.0, I = 1.0, R = 0.0, beta = 0.001, gamma = 0.1, dt = 0.01;
        double maxI = 0, peakDay = 0;

        for (double t = 0; t < 100; t += dt) {
            double dS = -beta * S * I;
            double dI = beta * S * I - gamma * I;
            double dR = gamma * I;

            S += dS * dt;
            I += dI * dt;
            R += dR * dt;

            if (I > maxI) {
                maxI = I;
                peakDay = t;
            }
        }
        cout << "Problem 2: Max Infected = " << maxI << " on Day " << peakDay << endl;
    }

    // Problem 3: Predator-Prey Cycle (Lotka-Volterra)
    static void problem3_LotkaVolterra() {
        double x = 10.0, y = 5.0, alpha = 1.1, beta = 0.4, delta = 0.1, gamma = 0.4, dt = 0.01;
        ofstream file("lotka_volterra.csv");
        file << "t,prey,predator\n";

        for (double t = 0; t < 50; t += dt) {
            file << t << "," << x << "," << y << "\n";
            double dx = alpha * x - beta * x * y;
            double dy = delta * x * y - gamma * y;
            x += dx * dt;
            y += dy * dt;
        }
        cout << "Problem 3: Data saved to lotka_volterra.csv" << endl;
        file.close();
    }

    // Problem 4: Impact of Maturity Lags (Delay Model)
    static void problem4_DelayModel(double tau) {
        double r = 0.1, K = 1000.0, dt = 0.01;
        vector<double> history( (int)(tau/dt) + 1, 10.0); // History buffer
        double N = 10.0;

        for (double t = 0; t < 100; t += dt) {
            double N_delayed = history.front();
            double dN = r * N_delayed * (1 - N_delayed / K);
            N += dN * dt;
            
            history.erase(history.begin());
            history.push_back(N);
        }
        cout << "Problem 4 (tau=" << tau << "): Final Population = " << N << endl;
    }

    // Problem 6: Allee Effect (Extinction Vortex)
    static void problem6_AlleeEffect(double initialN) {
        double r = 0.3, A = 20.0, K = 100.0, dt = 0.01, N = initialN;
        for (int i = 0; i < 5000; i++) {
            double dN = r * N * (N / A - 1) * (1 - N / K);
            N += dN * dt;
        }
        cout << "Problem 6: Initial " << initialN << " results in final pop: " << (N < 1 ? 0 : N) << endl;
    }

    // Problem 7: Vaccination Strategy
    static void problem7_Vaccination() {
        double totalPop = 1000.0;
        for (double v = 0.0; v <= 1.0; v += 0.05) {
            double S = 999.0, I = 1.0, beta = 0.001, gamma = 0.1, dt = 0.01;
            double maxI = 0;
            for (double t = 0; t < 100; t += dt) {
                double dS = -beta * S * I - (v * S);
                double dI = beta * S * I - gamma * I;
                S += dS * dt;
                I += dI * dt;
                if (I > maxI) maxI = I;
            }
            if (maxI < 0.1 * totalPop) {
                cout << "Problem 7: Minimum vaccination rate v = " << v << endl;
                break;
            }
        }
    }

    // Problem 8: Non-linear Predation (Holling Type II) using RK4
    static void problem8_RK4_Holling() {
        auto deriv = [](double x) {
            double r = 0.5, K = 100.0, a = 2.0, b = 10.0, y = 2.0;
            return r * x * (1 - x / K) - (a * x * y) / (b + x);
        };

        double x = 20.0, dt = 0.1;
        for (double t = 0; t < 10; t += dt) {
            double k1 = dt * deriv(x);
            double k2 = dt * deriv(x + k1 / 2.0);
            double k3 = dt * deriv(x + k2 / 2.0);
            double k4 = dt * deriv(x + k3);
            x += (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
        }
        cout << "Problem 8 (RK4): Final Population x = " << x << endl;
    }

    // Problem 10: Local Stability (Numerical Jacobian)
    static void problem10_Jacobian() {
        auto f1 = [](double x, double y) { return 1.1 * x - 0.4 * x * y; };
        auto f2 = [](double x, double y) { return 0.1 * x * y - 0.4 * y; };
        
        double x = 4.0, y = 2.75; // Equilibrium point for LV
        double h = 1e-5;

        double df1dx = (f1(x + h, y) - f1(x - h, y)) / (2 * h);
        double df1dy = (f1(x, y + h) - f1(x, y - h)) / (2 * h);
        double df2dx = (f2(x + h, y) - f2(x - h, y)) / (2 * h);
        double df2dy = (f2(x, y + h) - f2(x, y - h)) / (2 * h);

        cout << "Problem 10: Jacobian Matrix at (" << x << "," << y << "):" << endl;
        cout << "[" << df1dx << "  " << df1dy << "]" << endl;
        cout << "[" << df2dx << "  " << df2dy << "]" << endl;
    }
};

int main() {
    BioModels::problem1_LogisticGrowth();
    BioModels::problem2_SIRModel();
    BioModels::problem3_LotkaVolterra();
    BioModels::problem4_DelayModel(5.0);  // Stable
    BioModels::problem4_DelayModel(20.0); // Oscillatory
    BioModels::problem6_AlleeEffect(25.0); // Above A
    BioModels::problem6_AlleeEffect(15.0); // Below A
    BioModels::problem7_Vaccination();
    BioModels::problem8_RK4_Holling();
    BioModels::problem10_Jacobian();

    return 0;
}
