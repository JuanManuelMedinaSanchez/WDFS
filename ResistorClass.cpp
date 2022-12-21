/*
    WDFComponents: TwoPortResistorUnitElement   
-------------
    Wave Digital electric components, based in the theory of A. Feitweiss and other source like DAFX Knowledge 
    Created By Juan Manuel Medina for own proposes and Prismatik LAB division: DSP.Erience. This Class is oriented 
    to linear 2PN (Two Port Networks), for implementation / feedback or more info,  write to: prismatiklab@gmail.com
-------------
    This class is a model for one resistor with the most posible WDF elements like parasites, reflection, propagation, 
    Transfer function, Z, Y and others parameters. The non-linear coefficient is 0, because the nature of behavior of resistors, 
    capacitors and inductors (linear components). 
 */


class TwoPortResistorUnitElement {
public:
  // Constructor
  TwoPortResistorUnitElement(double resistance) : R(resistance), Lp(0), Cp(0) {}

  // Set the transfer function
  void setTransferFunction(std::complex<double> H) {
    this->H = H;
  }

  // Set the parasitic inductance
  void setParasiticInductance(double Lp) {
    this->Lp = Lp;
  }

  // Set the parasitic capacitance
  void setParasiticCapacitance(double Cp) {
    this->Cp = Cp;
  }

  // Set the impedance
  void setImpedance() {
    Z = 2 * R + Lp; // Take into account the parasitic inductance
  }

  // Set the admittance
  void setAdmittance() {
    Y = 1 / (2 * R + 1 / Cp); // Take into account the parasitic capacitance
  }

  // Set the waveform scattering function
  void setWaveformScatteringFunction(std::array<std::complex<double>, 4> k) {
    this->k = k;
  }

  // Set the nonlinearity coefficient
  void setNonlinearityCoefficient(double nl) {
    this->nl = nl;
  }

  // Calculate the input and output waveforms
  void calcInputOutputWaveforms(std::complex<double> V2, std::complex<double> I2) {
    v1 = k[0] * V2 - k[1] * I2;
    i1 = k[2] * V2 - k[3] * I2;
    v2 = v1;
    i2 = (v2 - v1) / (2 * R);
  }

  // Calculate the steady-state waves, scattering and reflection functions, and transmittance
  void calcSteadyStateQuantities() {
    A = V1 + (2 * R) * I1;
    B = V2 - (2 * R) * I2;
    a = (A + B) / 2;
    b = (A - B) / 2;  
    K = {a, b, b, a};
    psi = (z - 1) / (z + 1);
  }
private:
  double R;
  double Lp;
  double Cp; 
  std::complex<double> H; 
  double Z; // 
  double Y; //
  std::array<std::complex<double>, 4> k; 
  double nl; 
  std::complex<double> v1, v2; 
  std::complex<double> i1, i2; 
  std::complex<double> A, B; 
  std::complex<double> a, b; 
  std::array<std::complex<double>, 4> K; 
  std::complex<double> psi; 
  std::complex<double> z; 
  std::complex<double> V1, I1; 
  std::complex<double> V2, I2; // Vout, Iout
};
