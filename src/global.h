#ifndef FeynCalc_global_h
#define FeynCalc_global_h

#include "utility/vector.h"
#include <math.h>
#include <string>
#include <vector>

// turn off all assert
const bool DEBUGMODE = true;
// const bool DEBUGMODE = false;
//#define NDEBUG
// define NDEBUG will turn off debug checking, including the boundary check in
// array.h
/////////// Global Parameter ////////////////////
struct parameter {
  double Rs, Ef, Kf,
      Mu;            // r_s, fermi energy, fermi momentum, chemical potential
  double Beta;       // inverse temperature
  double UVScale;    // the UV bound of the energy scale
  double UVCoupling; // the coupling constant at the UV scale
  double Mass2;      // screening length^2
  double MaxExtMom;  // the maximum external momentum
  int TotalStep;     // total steps of the Monte Carlo
  int ObsType;       // 0: static polarization, 1: equal-time polarization
  int Seed;          // rng seed
  int PID;           // ID of the job
  long long int Counter; // counter to save the current MC step
  int Sweep;             // how many MC steps between two measuring
  int PrinterTimer;      // how many seconds between to printing to screen
  int SaveFileTimer;     // how many secondes between saving to file
  int MessageTimer;      // how many secondes between two checking for message
  int ReweightTimer;     // how many secondes between two reweighting
  std::string DiagFileFormat;   // the diagram file needs to be loaded
  std::vector<int> GroupID;     // ID for each group
  std::vector<double> ReWeight; // reweight factor for each group
};

///////////  Global Constants ////////////////////
const int D = 2;               // D=2 or D=3
const int ExtMomBinSize = 64;  // number of q bins of the external momentum
const bool UseVertex4 = false; // Use 4-vertex or interaction line
const int InInAngleBinSize =
    32; // number of bins for the angle between InL and InR legs
const int InOutAngleBinSize =
    32; // number of bins for the angle between InL and OutL legs
const int ScaleBinSize =
    32; // number of energy scales, only useful in RG approach

//////////   Diagram  ////////////////////////////
const int MaxOrder = 8;        // Max diagram order
const int MaxGroupNum = 8;     // Max number of diagram groups
const int MaxDiagNum = 1024;   // Max number of Hugenholtz diagrams in one group
const int MaxGPoolSize = 8192; // Max total indepdent G for all diagrams
const int MaxVerPoolSize = 4096; // Max total indepdent vertex for all diagrams
const int MaxLoopNum = MaxOrder; // Max loop number in one group
const int MaxTauNum = 2 * MaxOrder; // Max tau number in one group
const int MaxGNum = 2 * MaxOrder;   // Max G number in one group
const int MaxVer4Num = MaxOrder;    // Max Ver4 number in one group

//////////   Generic Global Constants  /////////////////
const double TM32 = 1.0 / (pow(2.0, 32));
const double EPS = 1.0e-9;
const int MAXINT = 2147483647;
const int MININT = -2147483647;
const double PI = 3.1415926535897932384626433832795;
const double MACHEPS = 2.22044604925031E-16; // Macheps + 1.0 > 1.0
const double MAXREAL = 1.0e30;
const double MINREAL = -1.0e30;

enum spin { DOWN, UP };

#define FLIPSPIN(x) spin(1 - x)
// Spin DOWN: 0,  Spin UP:1

const int IN = 0;
const int OUT = 1;

const int LEFT = 0;
const int RIGHT = 1;

const int INL = 0, INR = 1, OUTL = 3, OUTR = 4;
#define FLIP(x) (1 - x)
//////////////////////////////////////////////////////

typedef Vec<double, D> momentum;

// typedef std::array<double, D> momentum;

#define FMT_HEADER_ONLY

#endif
