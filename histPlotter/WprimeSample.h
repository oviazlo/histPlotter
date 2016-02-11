/// WprimeSample.h

/// David Adams
/// May 2011

/// Class to describe each of the wprime samples.

#include <string>
#include <iostream>

class WprimeSample {

public:

  typedef std::string Name;

public:

  /// Construct a sample from an alias.
  /// If the alias is know, the sample properties (including
  /// the name) will be set.
  explicit WprimeSample(unsigned int runNumber);

  /// Return the alias used to construct the sample.
  Name GetAlias() const { return m_alias; }

  /// Return the name used to identify the sample.
  Name GetName() const { return m_name; }

  /// Return a description of the sample.
  Name GetTitle() const { return m_title; }

  /// Return a latex name for the sample.
  Name GetLatex() const { return m_latex; }

  /// Return the generator cross section in pb
  /// (including BR and generator efficiency).
  double GetXSec() const { return m_genXSecTimesGenEff; }

  double GetKFactor() const { return m_kFactor; }
  
  unsigned int GetNEvents() const { return m_nEvents; }

  double GetIntLumi() const { 
      return (double)m_nEvents/m_genXSecTimesGenEff*m_kFactor; 
  }
  
  /// Return the run number.
  unsigned int GetRun() const { return m_run; }

private:

  Name m_alias;
  Name m_name;
  Name m_title;
  Name m_latex;
  double m_genXSecTimesGenEff;
  unsigned int m_run;
  unsigned int m_nEvents;
  double m_kFactor;

};

/// Output stream.
std::ostream& operator<<(std::ostream& lhs, const WprimeSample& rhs);

