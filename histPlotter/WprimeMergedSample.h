/* Copyright 2016 Oleksandr Viazlo */

///*****************************************************************************
///
/// Class which take care of merging histogram from many samples.
///
///*****************************************************************************

#ifndef WprimeMergedSample_H
#define WprimeMergedSample_H

/// std c++
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>    // std::find
#include <stdlib.h>     /* getenv */

/// ROOT
#include <TH1.h>
#include <TH1D.h>
#include <TFile.h>

/// EventLoop/xAOD
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/Sample.h"

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::stringstream;
    
class SamplePool
{
public:
    void AddElement(string systematicsTag, unsigned int DCID,
                            SH::Sample* sample);
    map<unsigned int, vector<SH::Sample*> > GetMap(string systematicsTag);
    vector<string> m_includedSystematicsTags;
    
private:
    map<string, map<unsigned int, vector<SH::Sample*> > > m_internalMap;
    
};

class WprimeMergedSample
{

public:
    WprimeMergedSample();
    ~WprimeMergedSample();

    void AddSampleHandler(SH::SampleHandler sh, string shDirName);
    TH1D* GetMergedHist(string globalSampleTag, string histName,
                        string systematicsTag = "");
    TH1D* GetMergedDataHist(string histName);
    /// based on m_globalSampleDefiner map
    /// TODO write print-function of all supported GlobalSampleTags
    vector<string> GetAllSupportedGlobalSampleTags();
    /// TODO think about implementation
    vector<string> GetAllSupportedSystematicsTags();
        
    TH1D* GetMergedMultijetHist(string histName);
    
    void PrintSamplePool();
     
private:

    /// map< shDirName,sh >
    map<string, SH::SampleHandler> m_notSortedSHMap;
    /// map< systematicsTag, map< DSID, sh > >
    SamplePool m_samplePool;
    
    /// TODO add description
    string GetSystematicsTag(string shDirName); 
    
    unsigned int GetDSID(string sampleName);
    
    /// hardcoded relationship between globalSampleTags and corresponding DSIDs
    map<string, vector<unsigned int> > m_globalSampleDefiner;
    
    /// convert notSortedSHMap --> samplePool
    /// if sample already included in the map - skip it
    void SortInputSH();
    
    double getRealEff(double lepPt);
    double getFakeEff(double lepPt);
    
    TH1D *realEffHist;
    TH1D *fakeEffHist;
    
    /// this is needed to distribute the algorithm to the workers
//     ClassDef(WprimeMergedSample, 1);
};

std::vector<std::string> &split(const std::string &s, char delim, 
                                std::vector<std::string> &elems);


std::vector<std::string> GetWords(const std::string &s, char delim=' ');

bool replace(std::string& str, const std::string& from, const std::string& to);

#endif
