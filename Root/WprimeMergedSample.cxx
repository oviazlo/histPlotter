#include <histPlotter/WprimeMergedSample.h>

/// this is needed to distribute the algorithm to the workers
// ClassImp(WprimeMergedSample)

void SamplePool::AddElement(string systematicsTag, unsigned int DCID,
                            SH::Sample* sample){
    if (std::find(m_includedSystematicsTags.begin(), m_includedSystematicsTags.end(),
        systematicsTag) == m_includedSystematicsTags.end()){
        m_includedSystematicsTags.push_back(systematicsTag);
        map<unsigned int, vector<SH::Sample*> > tmpMap;
        vector<SH::Sample*> tmpVec;
        tmpVec.push_back(sample);
        tmpMap[DCID] = tmpVec;
        m_internalMap[systematicsTag] = tmpMap;
    }
    else if (std::find(m_internalMap[systematicsTag][DCID].begin(), 
            m_internalMap[systematicsTag][DCID].end(),sample) ==
            m_internalMap[systematicsTag][DCID].end()){
            m_internalMap[systematicsTag][DCID].push_back(sample);
        }
    else{
        /// do nothing, because this sample is already in the map 
    }
            
}


map<unsigned int, vector<SH::Sample*> > SamplePool::GetMap(string systematicsTag){
    if (std::find(m_includedSystematicsTags.begin(), m_includedSystematicsTags.end(),
        systematicsTag) == m_includedSystematicsTags.end())
        cout << "[ERROR]\tSamplePool::GetMap - na map exist for systematicsTag: " <<
        systematicsTag << endl;
    return m_internalMap[systematicsTag];
}

WprimeMergedSample::WprimeMergedSample(){
    
/// FIXME WARNING no mc15b samples for: 361081, 361082, 361083, 361087
/// there are only mc15a...

  
vector<unsigned int> dibosonDSID = {361063,361064,361065,361066,361067,361068,
    361081,361082,361083,361084,361086,361087};

vector<unsigned int> topDSID = {410000,410011,410012,410013,410014};

vector<unsigned int> ztautauDSID = {361108,301040,301041,301042,301043,301044,
    301045,301046,301047,301048,301049,301050,301051,301052,301053,301054,
    301055,301056,301057,301058};

vector<unsigned int> zmumuDSID = {361107,301020,301021,301022,301023,301024,
    301025,301026,301027,301028,301029,301030,301031,301032,301033,301034,
    301035,301036,301037,301038};  
    
vector<unsigned int> zeeDSID = {361106,301000,301001,301002,301003,301004,
    301005,301006,301007,301008,301009,301010,301011,301012,301013,301014,
    301014,301015,301016,301017,301018};

vector<unsigned int> wtaunuDSID = {361102,361105,301140,301141,301142,301143,
    301144,301145,301146,301147,301148,301149,301150,301151,301152,301153,
    301154,301155,301156,301157,301158,301160,301161,301162,301163,301164,
    301165,301166,301167,301168,301169,301170,301171,301172,301173,301174,
    301175,301176,301177,301178};
    
vector<unsigned int> wmunuDSID = {361101,361104,301100,301101,301102,301103,
    301104,301105,301106,301107,301108,301109,301110,301111,301112,301113,
    301114,301115,301116,301117,301118,301120,301121,301122,301123,301124,
    301125,301126,301127,301128,301129,301130,301131,301132,301133,301134,
    301135,301136,301137,301138};
    
vector<unsigned int> wenuDSID = {361100,361103,301060,301061,301062,301063,
    301064,301065,301066,301067,301068,301069,301070,301071,301072,301073,
    301074,301075,301076,301077,301078,301080,301081,301082,301083,301084,
    301085,301086,301087,301088,301089,301090,301091,301092,301093,301094,
    301095,301096,301097,301098};
    
vector<unsigned int> wprimeDSID ={301533,301534,301242,301243,301244,301245,
    301246,301247,301248,301249};

  
    vector<unsigned int> tmpVec(wmunuDSID.begin(),wmunuDSID.begin()+2);
    m_globalSampleDefiner["wmunu_inclusive"] = tmpVec;
    vector<unsigned int> tmpVec2(wmunuDSID.begin()+2,wmunuDSID.end());
    m_globalSampleDefiner["wmunu_massbinned"] = tmpVec2;
    vector<unsigned int> tmpVec3(wmunuDSID.begin(),wmunuDSID.begin()+1);
    m_globalSampleDefiner["wmunuplus_inclusive"] = tmpVec3;
    vector<unsigned int> tmpVec4(wmunuDSID.begin()+1,wmunuDSID.begin()+2);
    m_globalSampleDefiner["wmunuminus_inclusive"] = tmpVec4;
    
    
    m_globalSampleDefiner["diboson"] = dibosonDSID;
    m_globalSampleDefiner["top"] = topDSID;
    m_globalSampleDefiner["ztautau"] = ztautauDSID;
    m_globalSampleDefiner["zmumu"] = zmumuDSID;
    m_globalSampleDefiner["zee"] = zeeDSID;
    m_globalSampleDefiner["wtaunu"] = wtaunuDSID;
    m_globalSampleDefiner["wmunu"] = wmunuDSID;
    m_globalSampleDefiner["wenu"] = wenuDSID;
    m_globalSampleDefiner["wprime"] = wprimeDSID;

    vector<unsigned int> zDSID;
    zDSID.reserve(ztautauDSID.size()+zmumuDSID.size());
    zDSID.insert(zDSID.end(),ztautauDSID.begin(),ztautauDSID.end());
    zDSID.insert(zDSID.end(),zmumuDSID.begin(),zmumuDSID.end());
    m_globalSampleDefiner["z"] = zDSID;
    
    vector<unsigned int> wDSID;
    wDSID.reserve(wtaunuDSID.size()+wmunuDSID.size());
    wDSID.insert(wDSID.end(),wtaunuDSID.begin(),wtaunuDSID.end());
    wDSID.insert(wDSID.end(),wmunuDSID.begin(),wmunuDSID.end());
    m_globalSampleDefiner["w"] = wDSID;
    
    /// FIXME for testing
    vector<unsigned int> testing;
    testing.push_back(301102);
    
//     testing.push_back(361101);
//     testing.push_back(361102);
//     testing.push_back(361104);
//     testing.push_back(361105);
    m_globalSampleDefiner["testing"] = testing;
    
    vector<unsigned int> emptyVec;
    m_globalSampleDefiner["data"] = emptyVec;
}

vector<string> WprimeMergedSample::GetAllSupportedGlobalSampleTags(){
    vector<string> outVec;
    for (map<string, vector<unsigned int> >::iterator it = 
        m_globalSampleDefiner.begin(); it!=m_globalSampleDefiner.end(); ++it){
        outVec.push_back((*it).first);
    }
    return outVec;
}

/// TODO implement function
string WprimeMergedSample::GetSystematicsTag(string shDirName){
    return "";
}

void WprimeMergedSample::AddSampleHandler(SH::SampleHandler sh, string shDirName){
    m_notSortedSHMap[shDirName] = sh;
    this->SortInputSH();
}

void WprimeMergedSample::SortInputSH(){
    for (map<string, SH::SampleHandler>::iterator it = 
        m_notSortedSHMap.begin(); it!=m_notSortedSHMap.end(); ++it){
        string currentSystematicsTag = GetSystematicsTag((*it).first);
        SH::SampleHandler currentSH = (*it).second;
        for (SH::SampleHandler::iterator shIter = currentSH.begin(); 
             shIter != currentSH.end(); ++shIter){
            SH::Sample* sample = *shIter;
            m_samplePool.AddElement(currentSystematicsTag,
                                    GetDSID((*shIter)->name()),sample);
        }
    }
}

void WprimeMergedSample::PrintSamplePool(){
    cout << "[INFO]\tPrint m_samplePool content!!!" << endl;
    for (unsigned int i=0; i<m_samplePool.m_includedSystematicsTags.size(); i++){
        string tmpSysTag = m_samplePool.m_includedSystematicsTags[i];
        map<unsigned int, vector<SH::Sample*> > tmpMap = 
        m_samplePool.GetMap(tmpSysTag);
        cout << "Systematics tag: " << tmpSysTag << endl;
        cout << "Map size: " << tmpMap.size() << endl;
        for(map<unsigned int, vector<SH::Sample*> >::iterator it = 
            tmpMap.begin(); it!=tmpMap.end(); ++it){
            vector<SH::Sample*> sampleVec = (*it).second;
            for (unsigned int i=0; i<sampleVec.size(); i++){
                cout << (*it).first << ":\t" << sampleVec[i]->name() << endl;    
            }
        }
    }
}

unsigned int WprimeMergedSample::GetDSID(string sampleName){
    string tmpSampleName = "";
    stringstream strStream(sampleName);

    getline (strStream, tmpSampleName, '.'); /// return mc15_13TeV
    getline (strStream, tmpSampleName, '.'); /// return DSID
    
    return atoi(tmpSampleName.c_str());
}

TH1D* WprimeMergedSample::GetMergedHist(string globalSampleTag, string histName,
                        string systematicsTag){
    map<unsigned int, vector<SH::Sample*> > currentMap =
    m_samplePool.GetMap(systematicsTag);
    
    /// make sure that input globalSampleTag is supported
    if (m_globalSampleDefiner[globalSampleTag].size()==0)
        cout << "[ERROR]\tWprimeMergedSample::GetMergedHist - globalSampleTag: " 
        << globalSampleTag << " is not supported!!!" << endl;
    
    /// verification if we have all needed DSID (according to m_globalSampleDefiner)
    if (currentMap.size()<m_globalSampleDefiner[globalSampleTag].size()){
        cout << "[ERROR]\tWprimeMergedSample::GetMergedHist - number of read samples"
        " are not as expected!!!" << endl;
        cout << "globalSampleTag: " << globalSampleTag << endl;
        cout << "systematicsTag: " << systematicsTag << endl;
        cout << "Expected:\t" << m_globalSampleDefiner[globalSampleTag].size() << endl;
        cout << "Existed:\t" << currentMap.size() << endl;
        cout << "TERMINATE!!!" << endl;
        return NULL;
    }
    
    TH1D* outHist = NULL;
    for (unsigned int i=0; i<m_globalSampleDefiner[globalSampleTag].size(); i++){
        unsigned int currentDSID = m_globalSampleDefiner[globalSampleTag][i];
        vector<SH::Sample*> sampleVec = currentMap[currentDSID];
        if (sampleVec.size()==0)
            cout << "[ERROR]\tWprimeMergedSample::GetMergedHist - sample for DSID: "
                << currentDSID << " is not found!!! Terminate!!!" << endl;
        for (unsigned int k=0; k<sampleVec.size(); k++){
            SH::Sample* sample = sampleVec[k];
            if (sample==NULL){
                cout << "[ERROR]\tWprimeMergedSample::GetMergedHist - sample for DSID: "
                << currentDSID << " is not found!!! Terminate!!!" << endl;
                return NULL;
            }
            TH1D* tmpHist = (TH1D*)sample->readHist(histName.c_str());
            if (tmpHist==NULL){
              cout << "[WARNING]\tSample *" << sample->name() << "* don't contain histogram *"
              << histName << "*\n";
              continue;
            }
//             /// FIXME hardcoded scale of W-sample
//             if (currentDSID==361101){
//               cout << "do scaling for 361101" << endl;
//               tmpHist->Scale(19997800./928281.);
//             }
//             if (currentDSID==361104){
//               cout << "do scaling for 361104" << endl;
//               tmpHist->Scale(19970400./1083408.); 
//             }
            
//             cout << "[DEBUG]\thistName = " << histName << "; currentDSID = " 
//             << currentDSID << endl;
            if (outHist==NULL)
                outHist = (TH1D*)tmpHist->Clone((histName+"_summed").c_str());
            else
                outHist->Add(tmpHist);  
        }
    }
    
    return outHist;
}





TH1D* WprimeMergedSample::GetMergedDataHist(string histName){
    map<unsigned int, vector<SH::Sample*> > currentMap =
    m_samplePool.GetMap("");

    TH1D* outHist = NULL;
    for (unsigned int i=270000; i<290000; i++){
        vector<SH::Sample*> sampleVec = currentMap[i];
        if (sampleVec.size()==0)
          continue;
        
        for (unsigned int k=0; k<sampleVec.size(); k++){
            SH::Sample* sample = sampleVec[k];
            if (sample==NULL){
                cout << "[ERROR]\tWprimeMergedSample::GetMergedHist - sample for DSID: "
                << i << " is not found!!! Terminate!!!" << endl;
                return NULL;
            }
            TH1D* tmpHist = (TH1D*)sample->readHist(histName.c_str());
            if (tmpHist==NULL){
              cout << "[WARNING]\tSample *" << sample->name() << "* don't contain histogram *"
              << histName << "*\n";
              continue;
            }
            if (outHist==NULL)
                outHist = (TH1D*)tmpHist->Clone((histName+"_summed").c_str());
            else
                outHist->Add(tmpHist);  
        }
    }
    
    return outHist;
}







std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> GetWords(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
