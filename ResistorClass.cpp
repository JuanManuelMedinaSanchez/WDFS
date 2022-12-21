//==============================================================================
/**
    WDFComponents: TwoPortResistorUnitElement   
-------------
    Wave Digital electric components, based in the theory of A. Feitweiss and other source like DAFX Knowledge Created By Juan Manuel Medina for own proposes and Prismatik LAB division: DSP.Erience.**/ This Class is oriented to linear 2PN (Two Port Networks), for implementation / feedback or more info,  write to: prismatiklab@gmail.com
-------------
This class is a model for one resistor with the most posible WDF elements like parasites, reflection, propagation, Transfer function, Z, Y and others parameters. The non-linear coefficient is 0, because the nature of behavior of resistors, capacitors and inductors (linear components)
 **/


class TwoPortResistorUnitElement {
public:
  TwoPortResistorUnitElement(double resistance, int numResistors, bool isParallel)
    : R(resistance), numResistors(numResistors), isParallel(isParallel), Lp(0), Cp(0) {}
  void setTransferFunction(std::complex<double> H) {
    this->H = H;
  }
  //parasites
  void setParasiticInductance(double Lp) {
    this->Lp = Lp;
  }
  void setParasiticCapacitance(double Cp) {
    this->Cp = Cp;
  }

  //Z
  void setImpedance() {
    if (isParallel) {
      Z = numResistors / R + Lp; // Take into account the parasitic inductance
    } else {
      Z = numResistors * R + Lp; // Take into account the parasitic inductance
    }
  }

  //Admittance Y
  void setAdmittance() {
      if (isParallel) {
      Y = numResistors / (R + 1 / Cp); // Take into account the parasitic capacitance
    } else {
      Y = numResistors / (numResistors * R + 1 / Cp); // Take into account the parasitic capacitance
    }
  }

  //Scattering
  void setWaveformScatteringFunction(std::array<std::complex<double>, 4> k) {
    this->k = k;
  }

  //nonlinearity coefficient
  void setNonlinearityCoefficient(double nl) {
    this->nl = nl;
  }
  // K Matrix
  void calcInputOutputWaveforms(std::complex<double> V2, std::complex<double> I2) {
    v1 = k[0] * V2 - k[1] * I2;
    i1 = k[2] * V2 - k[3] * I2;
    v2 = v1;
    i2 = (v2 - v1) / Z;
  }

//Steady state
  void calcSteadyStateQuantities() {
    A = V1 + Z * I1;
    B = V2 - Z * I2;
    a = (A + B) / 2;
    b = (A - B) / 2;
    K = {a, b, b, a};
    psi = (z - 1) / (z + 1);
  }
private:
  double R; 
  int numResistors; 
  bool isParallel; 
  double Cp; 
  std::complex<double> H; 
  double Z; 
  double Y; 
  std::array<std::complex<double>, 4> k; 
  double nl; 
  std::complex<double> v1, v2; 
  std::complex<double> i1, i2;
  std::complex<double> A, B; //waves
  std::complex<double> a, b; // Reflections and Scattering 
  std::array<std::complex<double>, 4> K; // K matrix
  std::array<std::complex<double>, 4> K; // K matrix
  std::complex<double> psi; // Psi
  std::complex<double> V1, V2; // I/O Voltages
  std::complex<double> I1, I2; // I/O currents 
};
