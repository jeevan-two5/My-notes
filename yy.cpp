#include <iostream>
#include <complex>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

// Constants
const double PI = std::acos(-1.0);

void problem1() {
    // Uniform Flow Orientation
    double U = 8.0;
    double alpha = PI / 4.0;
    double x = 3.0, y = 2.0;
    // psi = U(y*cos(alpha) - x*sin(alpha))
    double psi = U * (y * cos(alpha) - x * sin(alpha));
    cout << "P1: Stream function at (3,2) = " << psi << endl;
}

void problem2() {
    // Source Strength
    double m = 20.0;
    double x = 5.0, y = 0.0;
    double r = sqrt(x * x + y * y);
    // phi = (m / 2*PI) * ln(r)
    double phi = (m / (2.0 * PI)) * log(r);
    cout << "P2: Velocity potential at (5,0) = " << phi << endl;
}

void problem3() {
    // Stagnation Point of a Source
    double m = 12.0;
    double U = 3.0;
    // u = U + m/(2*PI*x) = 0 => x = -m / (2*PI*U)
    double x_stag = -m / (2.0 * PI * U);
    cout << "P3: x-coordinate of stagnation point = " << x_stag << endl;
}

void problem4() {
    // Sink at Offset
    double m = 15.0; // Sink strength is usually negative in potential, but m is given as 15
    complex<double> z0(2.0, 2.0);
    complex<double> z_eval(0.0, 0.0);
    // w = -(m / 2*PI) * ln(z - z0) for a sink
    complex<double> w = -(m / (2.0 * PI)) * log(z_eval - z0);
    cout << "P4: Velocity potential (phi) at origin = " << w.real() << endl;
}

void problem5() {
    // Source-Sink Interaction
    double m = 10.0;
    complex<double> z_source(-1.0, 0.0);
    complex<double> z_sink(1.0, 0.0);
    complex<double> z_eval(0.0, 2.0);
    
    complex<double> w = (m / (2.0 * PI)) * log(z_eval - z_source) - (m / (2.0 * PI)) * log(z_eval - z_sink);
    cout << "P5: Total velocity potential at (0,2) = " << w.real() << endl;
}

void problem6() {
    // Cylinder Surface Velocity
    double a = 1.0;
    double U = 5.0;
    double theta = PI / 2.0;
    // vt = -2 * U * sin(theta)
    double vt = -2.0 * U * sin(theta);
    cout << "P6: Tangential velocity at theta=pi/2 = " << vt << " m/s" << endl;
}

void problem7() {
    // Streamline on Cylinder
    double a = 1.0;
    double U = 5.0;
    double theta = 0.75; // Arbitrary angle
    complex<double> z = polar(a, theta);
    // w = U(z + a^2/z)
    complex<double> w = U * (z + (a * a) / z);
    double psi = w.imag();
    cout << "P7: Stream function on cylinder surface (r=a) = " << (abs(psi) < 1e-15 ? 0 : psi) << endl;
}

void problem8() {
    // Radial Velocity
    double m = 25.0;
    double r = 10.0;
    // vr = m / (2 * PI * r)
    double vr = m / (2.0 * PI * r);
    cout << "P8: Radial velocity vr at r=10 = " << vr << " m/s" << endl;
}

void problem9() {
    // Doublet Construction
    double mu = 10.0 * PI;
    complex<double> z(1.0, 1.0);
    // w = mu / (2 * PI * z)
    complex<double> w = mu / (2.0 * PI * z);
    cout << "P9: Velocity potential (phi) at (1,1) = " << w.real() << endl;
}

void problem10() {
    // Velocity at Cylinder Top
    double a = 2.0;
    double U = 10.0;
    complex<double> z(0.0, 3.0); // Point (0,3)
    // dw/dz = U(1 - a^2/z^2)
    complex<double> complex_vel = U * (1.0 - (a * a) / (z * z));
    cout << "P10: Magnitude of velocity at (0,3) = " << abs(complex_vel) << endl;
}

void problem11() {
    // Combined Potential
    double U = 2.0;
    double m = 5.0;
    complex<double> z(2.0, 1.0);
    // dw/dz = U + m/(2 * PI * z)
    complex<double> complex_vel = U + (m / (2.0 * PI * z));
    cout << "P11: Complex velocity u-iv at z=2+i = " << complex_vel << endl;
}

void problem12() {
    // Flow past Cylinder (Complex)
    double U = 1.0;
    double a = 1.0;
    complex<double> z(2.0, 2.0);
    // w = U(z + a^2/z)
    complex<double> w = U * (z + (a * a) / z);
    cout << "P12: Velocity potential (phi) at z=2+2i = " << w.real() << endl;
}

void problem13() {
    // Superposition of Sources
    double m = 10.0;
    complex<double> z1(1.0, 0.0);
    complex<double> z2(-1.0, 0.0);
    complex<double> z_eval(0.0, 1.0);
    // w = m/(2*PI) * ln(z-z1) + m/(2*PI) * ln(z-z2)
    complex<double> w = (m / (2.0 * PI)) * (log(z_eval - z1) + log(z_eval - z2));
    cout << "P13: Velocity potential at (0,1) = " << w.real() << endl;
}

void problem14() {
    // Time-Varying Source
    double t = 10.0;
    double m_t = 2.0 * t;
    double r = 2.0;
    // phi = (m/2*PI) * ln(r)
    double phi = (m_t / (2.0 * PI)) * log(r);
    cout << "P14: Velocity potential at r=2, t=10 = " << phi << endl;
}

void problem15() {
    // Cylinder Stagnation
    double a = 3.0;
    cout << "P15: Stagnation points: (" << a << ", 0) and (" << -a << ", 0)" << endl;
}

int main() {
    cout << fixed << setprecision(4);
    problem1();
    problem2();
    problem3();
    problem4();
    problem5();
    problem6();
    problem7();
    problem8();
    problem9();
    problem10();
    problem11();
    problem12();
    problem13();
    problem14();
    problem15();
    return 0;
}
