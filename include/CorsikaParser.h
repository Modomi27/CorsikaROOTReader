#ifndef _CORSIKAPARSER_H_
#define _CORSIKAPARSER_H_

/*
class TFile;
class TTree;
class TBranch;
class TClonesArray;
class TString; 
*/

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TParticle.h>

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
/*
namespace crsIO {
	class TRun;
	class TShower;
	class TParticle;
};

namespace crs {
	class TSubBlock;
	class MRunHeader;
	class MEventHeader;
	class MEventEnd;
	class MParticleBlock;
	class MLongitudinalBlock;
	class MParticle;
};


namespace crsRead {
	class MCorsikaReader;
};
*/


//namespace CorsikaParser {
    
class CorsikaParser {
 
 
public:
 	CorsikaParser();
 	~CorsikaParser();
     
	bool ReadPartFile();
  bool ReadLongFile();

	void SetInputPartFileName(std::string & fileName) { fPartFileName = fileName;}
	void SetInputLongFileName(std::string & fileName) { fLongFileName = fileName;}

	void SetEventToRead(int value){fShowerNoToRead= value;}
	void CalculateNeventsInPartFile();
	int GetNeventsInPartFile(){ return fNeventInPartFile;}

	std::vector<TParticle*> GetParticlesAtGround() { return fGroundParticles;}
	std::vector<double> GetParticleAnglesAtGround() { return fParticleAngles;}

	std::vector<double> GetLongitudinalDepth() { return fDepth;}
	std::vector<double> GetLongitudinalCharged() { return fLongCharged;}
	std::vector<double> GetLongitudinalMuons() { return fLongMuons;}
	std::vector<double> GetLongitudinalElectrons() { return fLongElectrons;}
	std::vector<double> GetLongitudinalGammas() { return fLongGammas;}
	
	double GetEnergy() { return fEnergy;}
  double GetTheta() { return fTheta;}
	double GetPhi() { return fPhi;}

private:

	std::string fPartFileName;
	std::string fLongFileName;

	//FILE VARs
	crs::MRunHeader fRunHeader;//define the file run header
	crs::MEventHeader fEventHeader;//define the file event header
  crs::TSubBlock fDataSubBlock;

	//File info
	int fNumberOfObsLevel;
	int fShowerNoToRead;
	int fNeventInPartFile;

	//Shower info
	double fTheta;
	double fPhi;
	double fEnergy;
	double fCutoffHadrons;
	double fCutoffMuons;
	double fCutoffElectrons;
	double fCutoffPhotons;
	double fEFractThinH;
	double fEFractThinEM;
	double fWMaxHadronic;
	double fWMaxEM;

	std::vector<double> fDepth;
  std::vector<double> fLongCharged;
  std::vector<double> fLongMuons;
  std::vector<double> fLongGammas;
  std::vector<double> fLongElectrons;

  std::vector<double> fDepth_dE;
  std::vector<double> fDeltaEn;

	float fNmax;
  float fX0;
  float fXmax;
  float fGHChi;
  float fGH_a;
  float fGH_b;
  float fGH_c;

	std::vector<TParticle*> fGroundParticles;
	TParticle* fParticle;
	
	std::vector<double> fParticleAngles;

};//close class
//};//close namespace

#endif
