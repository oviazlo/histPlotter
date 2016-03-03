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

/// ROOT
#include <TH1.h>

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
    /// TODO what about implementation for data?
    WprimeMergedSample();
    /// TODO get rid of *double free or corruption (!prev)* execution error
    ~WprimeMergedSample();

    void AddSampleHandler(SH::SampleHandler sh, string shDirName);
    TH1D* GetMergedHist(string globalSampleTag, string histName,
                        string systematicsTag = "");
    /// based on m_globalSampleDefiner map
    /// TODO write print-function of all supported GlobalSampleTags
    vector<string> GetAllSupportedGlobalSampleTags();
    /// TODO think about implementation
    vector<string> GetAllSupportedSystematicsTags();
        
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
    
    /// this is needed to distribute the algorithm to the workers
//     ClassDef(WprimeMergedSample, 1);
};

std::vector<std::string> &split(const std::string &s, char delim, 
                                std::vector<std::string> &elems);


std::vector<std::string> GetWords(const std::string &s, char delim=' ');

/// FIXME WARNING no mc15b samples for: 361081, 361082, 361083, 361087
/// there are only mc15a...
// unsigned int dibosonDSIDArr[] = {361063,361064,361065,361066,361067,361068,
//     361081,361082,361083,361084,361086,361087};
unsigned int dibosonDSIDArr[] = {361063,361064,361065,361066,361067,361068,
    361084,361086};    
    
unsigned int topDSIDArr[] = {410000,410011,410012,410013,410014};

unsigned int ztautauDSIDArr[] = {361108,301040,301041,301042,301043,301044,
    301045,301046,301047,301048,301049,301050,301051,301052,301053,301054,
    301055,301056,301057,301058};

unsigned int zmumuDSIDArr[] = {361107,301020,301021,301022,301023,301024,
    301025,301026,301027,301028,301029,301030,301031,301032,301033,301034,
    301035,301036,301037,301038};  
    
unsigned int zeeDSIDArr[] = {361106,301000,301001,301002,301003,301004,
    301005,301006,301007,301008,301009,301010,301011,301012,301013,301014,
    301014,301015,301016,301017,301018};

unsigned int wtaunuDSIDArr[] = {361102,361105,301140,301141,301142,301143,
    301144,301145,301146,301147,301148,301149,301150,301151,301152,301153,
    301154,301155,301156,301157,301158,301160,301161,301162,301163,301164,
    301165,301166,301167,301168,301169,301170,301171,301172,301173,301174,
    301175,301176,301177,301178};
    
unsigned int wmunuDSIDArr[] = {361101,361104,301100,301101,301102,301103,
    301104,301105,301106,301107,301108,301109,301110,301111,301112,301113,
    301114,301115,301116,301117,301118,301120,301121,301122,301123,301124,
    301125,301126,301127,301128,301129,301130,301131,301132,301133,301134,
    301135,301136,301137,301138};
    
unsigned int wenuDSIDArr[] = {361100,361103,301060,301061,301062,301063,
    301064,301065,301066,301067,301068,301069,301070,301071,301072,301073,
    301074,301075,301076,301077,301078,301080,301081,301082,301083,301084,
    301085,301086,301087,301088,301089,301090,301091,301092,301093,301094,
    301095,301096,301097,301098};
    
unsigned int wprimeDSIDArr[] ={301533,301534,301242,301243,301244,301245,
    301246,301247,301248,301249};
    
vector<unsigned int> dibosonDSID (dibosonDSIDArr, 
                                  dibosonDSIDArr + sizeof(dibosonDSIDArr) /
                                  sizeof(unsigned int) );
vector<unsigned int> topDSID (topDSIDArr, 
                                  topDSIDArr + sizeof(topDSIDArr) /
                                  sizeof(unsigned int) );
vector<unsigned int> ztautauDSID (ztautauDSIDArr, 
                                  ztautauDSIDArr + sizeof(ztautauDSIDArr) /
                                  sizeof(unsigned int) );
vector<unsigned int> zmumuDSID (zmumuDSIDArr, 
                                  zmumuDSIDArr + sizeof(zmumuDSIDArr) /
                                  sizeof(unsigned int) );
vector<unsigned int> zeeDSID (zeeDSIDArr, 
                                  zeeDSIDArr + sizeof(zeeDSIDArr) /
                                  sizeof(unsigned int) );
vector<unsigned int> wtaunuDSID (wtaunuDSIDArr, 
                                  wtaunuDSIDArr + sizeof(wtaunuDSIDArr) /
                                  sizeof(unsigned int) );
vector<unsigned int> wmunuDSID (wmunuDSIDArr, 
                                  wmunuDSIDArr + sizeof(wmunuDSIDArr) /
                                  sizeof(unsigned int) );
vector<unsigned int> wenuDSID (wenuDSIDArr, 
                                  wenuDSIDArr + sizeof(wenuDSIDArr) /
                                  sizeof(unsigned int) );
vector<unsigned int> wprimeDSID (wprimeDSIDArr, 
                                  wprimeDSIDArr + sizeof(wprimeDSIDArr) /
                                  sizeof(unsigned int) );

// vector<unsigned int> dibosonDSID = {361063,361064,361065,361066,361067,361068,
//     361081,361082,361083,361084,361086,361087};
// 
// vector<unsigned int> topDSID = {410000,410011,410012,410013,410014};
// 
// vector<unsigned int> ztautauDSID = {361108,301040,301041,301042,301043,301044,
//     301045,301046,301047,301048,301049,301050,301051,301052,301053,301054,
//     301055,301056,301057,301058};
// 
// vector<unsigned int> zmumuDSID = {361107,301020,301021,301022,301023,301024,
//     301025,301026,301027,301028,301029,301030,301031,301032,301033,301034,
//     301035,301036,301037,301038};  
//     
// vector<unsigned int> zeeDSID = {361106,301000,301001,301002,301003,301004,
//     301005,301006,301007,301008,301009,301010,301011,301012,301013,301014,
//     301014,301015,301016,301017,301018};
// 
// vector<unsigned int> wtaunuDSID = {361102,361105,301140,301141,301142,301143,
//     301144,301145,301146,301147,301148,301149,301150,301151,301152,301153,
//     301154,301155,301156,301157,301158,301160,301161,301162,301163,301164,
//     301165,301166,301167,301168,301169,301170,301171,301172,301173,301174,
//     301175,301176,301177,301178};
//     
// vector<unsigned int> wmunuDSID = {361101,361104,301100,301101,301102,301103,
//     301104,301105,301106,301107,301108,301109,301110,301111,301112,301113,
//     301114,301115,301116,301117,301118,301120,301121,301122,301123,301124,
//     301125,301126,301127,301128,301129,301130,301131,301132,301133,301134,
//     301135,301136,301137,301138};
//     
// vector<unsigned int> wenuDSID = {361100,361103,301060,301061,301062,301063,
//     301064,301065,301066,301067,301068,301069,301070,301071,301072,301073,
//     301074,301075,301076,301077,301078,301080,301081,301082,301083,301084,
//     301085,301086,301087,301088,301089,301090,301091,301092,301093,301094,
//     301095,301096,301097,301098};
//     
// vector<unsigned int> wprimeDSID ={301533,301534,301242,301243,301244,301245,
//     301246,301247,301248,301249};

#endif
