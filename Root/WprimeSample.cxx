// WprimeSample.cxx

#include <histPlotter/WprimeSample.h>

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

WprimeSample::WprimeSample(unsigned int runNumber)
: m_alias(""), m_name(""), m_title(""), m_latex(""),
  m_genXSecTimesGenEff(0), m_run(runNumber), m_nEvents(0), 
  m_kFactor(0)  {
  
  if ( m_run == 301060 ){
    m_title = "W^{+}(120, 180) --> e #nu";
    m_alias = "W^{+}(120, 180) --> e #nu";
    m_latex = "W^{+}(120, 180) --> e #nu";
    m_nEvents = 500000;
    m_genXSecTimesGenEff = 32.053;
    

  } else if ( m_run == 301061 ){
    m_title = "W^{+}(180, 250) --> e #nu";
    m_alias = "W^{+}(180, 250) --> e #nu";
    m_latex = "W^{+}(180, 250) --> e #nu";
    m_nEvents = 250000;
    m_genXSecTimesGenEff = 5.0029;
  }

  else {
    cerr << "WprimeSample::WprimeSample: Unknown sample: " << m_name << endl;
  }
}

std::ostream& operator<<(std::ostream& lhs, const WprimeSample& rhs) {
  lhs <<   "             Name: " << rhs.GetName();
  lhs << "\n            Alias: " << rhs.GetAlias();
  lhs << "\n            Title: " << rhs.GetTitle();
  lhs << "\n   Generated xsec: " << rhs.GetXSec() << " pb";
  lhs << "\n          k-actor: " << rhs.GetKFactor();
  lhs << "\n number of events: " << rhs.GetNEvents();
  lhs << "\n    eq. int. lumi: " << rhs.GetIntLumi() << " pb^{-1}";
  lhs << "\n            Latex: " << rhs.GetLatex();
  lhs << "\n              Run: " << rhs.GetRun();
  return lhs;
}
