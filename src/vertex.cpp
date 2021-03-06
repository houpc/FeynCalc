#include "vertex.h"
#include "global.h"
#include "utility/abort.h"
#include <cmath>
#include <iostream>

using namespace diag;
using namespace std;

extern parameter Para;

// double sum2(const momentum &Mom) {
//   double Sum2 = 0.0;
//   for (int i = 0; i < D; i++)
//     Sum2 += Mom[i] * Mom[i];
//   return Sum2;
// }

// double norm2(const momentum &Mom) { return sqrt(sum2(Mom)); }

double bose::Interaction(double Tau, const momentum &Mom, int VerType) {
  if (VerType < 0)
    ABORT("VerType can not be " << VerType);
  double interaction = 8.0 * PI / (Mom.squaredNorm() + Para.Mass2);

  if (VerType > 0) {
    // the interaction contains counter-terms
    interaction *= pow(Para.Mass2 / (Mom.squaredNorm() + Para.Mass2), VerType);
    interaction *= pow(-1, VerType);
  }
  return interaction;
}

double fermi::Fock(double k) {
  double l = sqrt(Para.Mass2);
  double kF = Para.Kf;
  double fock = 1.0 + l / kF * atan((k - kF) / l);
  fock -= l / kF * atan((k + kF) / l);
  fock -= (l * l - k * k + kF * kF) / 4.0 / k / kF *
          log((l * l + (k - kF) * (k - kF)) / (l * l + (k + kF) * (k + kF)));
  fock *= (-2.0 * kF) / PI;

  double shift = 1.0 - l / kF * atan(2.0 * kF / l);
  shift -= l * l / 4.0 / kF / kF * log(l * l / (l * l + 4.0 * kF * kF));
  shift *= (-2.0 * kF) / PI;

  return k * k + fock - shift;
}

double fermi::GetSigma(double k) { return 0.0; }

double fermi::BuildFockSigma() {
  for (int i = 0; i < MAXSIGMABIN; ++i) {
  }
};

double fermi::FockSigma(const momentum &Mom) {
  double k = Mom.norm(); // bare propagator
  if (k > UpBound * Para.Ef)
    return Fock(k);
  else
    GetSigma(k);
}

double fermi::PhyGreen(double Tau, const momentum &Mom) {
  // if tau is exactly zero, set tau=0^-
  double green, Ek;
  if (Tau == 0.0) {
    return EPS;
  }

  double s = 1.0;
  if (Tau < 0.0) {
    Tau += Para.Beta;
    s = -s;
  } else if (Tau >= Para.Beta) {
    Tau -= Para.Beta;
    s = -s;
  }
  Ek = Mom.squaredNorm(); // bare propagator

  // Ek = FockKinetic(Mom); // Fock diagram dressed propagator

  //// enforce an UV cutoff for the Green's function ////////
  // if(Ek>8.0*EF) then
  //   PhyGreen=0.0
  //   return
  // endif

  double x = Para.Beta * (Ek - Para.Mu) / 2.0;
  double y = 2.0 * Tau / Para.Beta - 1.0;
  if (x > 100.0)
    green = exp(-x * (y + 1.0));
  else if (x < -100.0)
    green = exp(x * (1.0 - y));
  else
    green = exp(-x * y) / (2.0 * cosh(x));

  green *= s;

  // if (Debug) { //   cout << "Tau=" << Tau << endl;
  //   cout << "Counter" << Para.Counter << endl;
  //   cout << "Tau=" << Tau << endl;
  //   cout << "Mom=(" << Mom[0] << ", " << Mom[1] << ")" << endl;
  //   cout << "Mom2=" << Mom[0] * Mom[0] + Mom[1] * Mom[1] << endl;
  //   cout << "Ek=" << Ek << endl;
  //   cout << "x=" << x << endl;
  //   cout << "y=" << y << endl;
  //   cout << "Green=" << green << endl << endl;
  // }

  // cout << "x: " << x << ", y: " << y << ", G: " << green << endl;
  // cout << "G: " << green << endl;

  if (std::isnan(green))
    ABORT("Green is too large!" << Tau << " " << Ek << " " << green);
  return green;
}

double fermi::Green(double Tau, const momentum &Mom, spin Spin, int GType) {
  double green;
  if (GType == 0) {
    green = PhyGreen(Tau, Mom);
  } else
    ABORT("GType " << GType << " has not yet been implemented!");
  // return FakeGreen(Tau, Mom);
  return green;
}