#ifndef _CORSIKAROOTREADER_H_
#define _CORSIKAROOTREADER_H_

/*
class TFile;
class TTree;
class TBranch;
class TClonesArray;
class TString; 
*/



#include <crsIO/TRun.h>
#include <crsIO/TShower.h>
#include <crsIO/TParticle.h>
#include <crsIO/TCherenkov.h>
#include <crsIO/TLongitudinal.h>

#include <crsRead/MCorsikaReader.h>

#include <crs/TSubBlock.h>
#include <crs/MRunHeader.h>
#include <crs/MEventHeader.h>
#include <crs/MEventEnd.h>
#include <crs/MParticleBlock.h>
#include <crs/MLongitudinalBlock.h>
#include <crs/MParticle.h>

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TParticle.h>

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

    
class CorsikaROOTReader {
 
 
public:

 	CorsikaROOTReader();
 	~CorsikaROOTReader();
     
	void Init();
	void Read();	
	void Save();
  
	void SetInputFileName(std::string fileName) { fInputFileName = fileName;}
	void SetOutputFileName(std::string fileName) { fOutputFileName = fileName;}
	void SetStoreOnlyMuons(bool choice){fStoreOnlyMuons= choice;}	

	void SetEventToRead(int value){fShowerNoToRead= value;}
	void CalculateNeventsInPartFile();
	int GetNeventsInPartFile(){ return fNeventInPartFile;}

	std::vector<TParticle*> GetParticlesAtGround() { return fParticleList;}
	

private:

	bool fStoreOnlyMuons;
	
	//## Files
	std::string fInputFileName;
	TFile* fInputFile;
	TTree* fSimTreeInfo;
	TTree* fRunTreeInfo;
	crsIO::TShower* fShower;
	crsIO::TParticle* fParticle;
	TClonesArray* fParticleArray;
	std::vector<TParticle*> fParticleList;
	
	std::string fOutputFileName;
	TFile* fOutputFile;
	TTree* fOutputTreeInfo;

	double fShowerEnergy;
	double fShowerTheta;
	double fShowerPhi;	
	static const long long MAXPARTATGROUND= 100000000;
	int fNPartAtGround;
	int fParticleId[MAXPARTATGROUND];
	double fPx[MAXPARTATGROUND];
	double fPy[MAXPARTATGROUND];
	double fPz[MAXPARTATGROUND];
	double fX[MAXPARTATGROUND];
	double fY[MAXPARTATGROUND];
	double fKinEnergy[MAXPARTATGROUND];
	double fTheta[MAXPARTATGROUND];
	double fPhi[MAXPARTATGROUND];
	double fTime[MAXPARTATGROUND];

	//File info
	int fNumberOfObsLevel;
	int fShowerNoToRead;
	int fNeventInPartFile;

	
};//close class

#endif
