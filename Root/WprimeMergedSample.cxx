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
    zDSID.reserve(ztautauDSID.size()+zmumuDSID.size()+zeeDSID.size());
    zDSID.insert(zDSID.end(),ztautauDSID.begin(),ztautauDSID.end());
    zDSID.insert(zDSID.end(),zmumuDSID.begin(),zmumuDSID.end());
    zDSID.insert(zDSID.end(),zeeDSID.begin(),zeeDSID.end());
    m_globalSampleDefiner["z"] = zDSID;
    
    vector<unsigned int> wDSID;
    wDSID.reserve(wtaunuDSID.size()+wmunuDSID.size()+wenuDSID.size());
    wDSID.insert(wDSID.end(),wtaunuDSID.begin(),wtaunuDSID.end());
    wDSID.insert(wDSID.end(),wmunuDSID.begin(),wmunuDSID.end());
    wDSID.insert(wDSID.end(),wenuDSID.begin(),wenuDSID.end());
    m_globalSampleDefiner["w"] = wDSID;
    
};

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
    for (int i=0; i<m_samplePool.m_includedSystematicsTags.size(); i++){
        string tmpSysTag = m_samplePool.m_includedSystematicsTags[i];
        map<unsigned int, vector<SH::Sample*> > tmpMap = 
        m_samplePool.GetMap(tmpSysTag);
        cout << "Systematics tag: " << tmpSysTag << endl;
        cout << "Map size: " << tmpMap.size() << endl;
        for(map<unsigned int, vector<SH::Sample*> >::iterator it = 
            tmpMap.begin(); it!=tmpMap.end(); ++it){
            vector<SH::Sample*> sampleVec = (*it).second;
            for (int i=0; i<sampleVec.size(); i++){
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
    if (currentMap.size()<=m_globalSampleDefiner[globalSampleTag].size()){
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
    for (int i=0; i<m_globalSampleDefiner[globalSampleTag].size(); i++){
        unsigned int currentDSID = m_globalSampleDefiner[globalSampleTag][i];
        vector<SH::Sample*> sampleVec = currentMap[currentDSID];
        if (sampleVec.size()==0)
            cout << "[ERROR]\tWprimeMergedSample::GetMergedHist - sample for DSID: "
                << currentDSID << " is not found!!! Terminate!!!" << endl;
        for (int k=0; k<sampleVec.size(); k++){
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
