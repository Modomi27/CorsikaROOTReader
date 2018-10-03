#include "CorsikaROOTReader.h"
#include "CorsikaUtilities.h"

#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TObjectTable.h>
#include <TParticle.h>
 
#include <crsIO/TRun.h>
#include <crsIO/TShower.h>
#include <crsIO/TParticle.h>
#include <crsIO/TCherenkov.h>
#include <crsIO/TLongitudinal.h>

#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdexcept>
#include <utility>


using namespace std;


CorsikaROOTReader::CorsikaROOTReader(){

	fShowerNoToRead= 1;//if not specified read first shower as default, otherwise set which shower to read in CORSIKA file
	fStoreOnlyMuons= false;
}//close constructor


CorsikaROOTReader::~CorsikaROOTReader(){


}//close destructor


void CorsikaROOTReader::Init(){

	cout<<"CorsikaROOTReader::Init(): INFO: Init reading..."<<endl;

	//## Open file to read
	fInputFile= new TFile(fInputFileName.c_str(),"READ");

	if(!fInputFile || fInputFile->IsZombie() || !fInputFile->IsOpen() ){
		cerr<<"CorsikaROOTReader::Init(): ERROR: Cannot open ROOT file "<<fInputFileName.c_str()<<" with Corsika data...exit!"<<endl;
		exit(1);
	}

	cout<<"CorsikaROOTReader::Init(): INFO: Reading Corsika file "<<fInputFileName.c_str()<<"..."<<endl;

	//## Get trees
	fSimTreeInfo= (TTree*)fInputFile->Get("sim");
	fRunTreeInfo= (TTree*)fInputFile->Get("run");

	if(!fSimTreeInfo || !fRunTreeInfo ){
		cerr<<"CorsikaROOTReader::Init(): ERROR: Cannot get tree with Corsika data ...exit!"<<endl;
		exit(1);
	}

	fShower= 0;
	//fParticle= 0;

	fParticleArray = new TClonesArray("crsIO::TParticle");
   
	fSimTreeInfo->SetBranchAddress("shower.",&fShower);
	fSimTreeInfo->GetBranch("particle.")->SetAutoDelete(kFALSE);
	fSimTreeInfo->SetBranchAddress("particle.",&fParticleArray);
	

	//## Create output tree
	fOutputFile= new TFile(fOutputFileName.c_str(),"RECREATE");
	fOutputTreeInfo= new TTree("data","data");
	
	fOutputTreeInfo->Branch("ShowerEnergy",&fShowerEnergy,"ShowerEnergy/D");
	fOutputTreeInfo->Branch("ShowerTheta",&fShowerTheta,"ShowerTheta/D");
	fOutputTreeInfo->Branch("ShowerPhi",&fShowerPhi,"ShowerPhi/D");
	fOutputTreeInfo->Branch("nParticles",&fNPartAtGround,"nParticles/I");
	fOutputTreeInfo->Branch("ParticleId",&fParticleId,"ParticleId[nParticles]/I");
	fOutputTreeInfo->Branch("Px",&fPx,"Px[nParticles]/D");
	fOutputTreeInfo->Branch("Py",&fPy,"Py[nParticles]/D");
	fOutputTreeInfo->Branch("Pz",&fPz,"Pz[nParticles]/D");
	fOutputTreeInfo->Branch("KinEnergy",&fKinEnergy,"KinEnergy[nParticles]/D");
	fOutputTreeInfo->Branch("X",&fX,"X[nParticles]/D");
	fOutputTreeInfo->Branch("Y",&fY,"Y[nParticles]/D");
	fOutputTreeInfo->Branch("Theta",&fTheta,"Theta[nParticles]/D");
	fOutputTreeInfo->Branch("Phi",&fPhi,"Phi[nParticles]/D");
	fOutputTreeInfo->Branch("Time",&fTime,"Time[nParticles]/D");
	

}//close CorsikaROOTReader::Init()


void CorsikaROOTReader::Read(){

	cout<<"CorsikaROOTReader::Init(): INFO: Reading data..."<<endl;

	int nShowers= fSimTreeInfo->GetEntries();
	cout<<"CorsikaROOTReader::Read(): INFO: Reading "<<nShowers<<" simulated showers in file..."<<endl;

	for(int i=0;i<nShowers;i++){

		fParticleArray->Clear();

		fSimTreeInfo->GetEntry(i);
		
		fShowerEnergy= log10(fShower->Energy*1.e+9);
		fShowerTheta= fShower->Theta*180./TMath::Pi();
		fShowerPhi= fShower->Phi*180./TMath::Pi();
		
		fNPartAtGround = fParticleArray->GetEntriesFast();

		if(i%10000==0) {
		  cout<<"CorsikaROOTReader::Read(): INFO: Shower no. "<<i+1<<"  lgE="<<fShowerEnergy<<"  Theta="<<fShowerTheta<<"  nParticles="<<fNPartAtGround<<endl;	
		}



    int particleCounter= 0;

    for(int j=0;j<fNPartAtGround;j++) {
    	fParticle = (crsIO::TParticle*)fParticleArray->At(j);

			int particleId= fParticle->ParticleID;
			int particlePDGId= CorsikaUtilities::CorsikaToPDG(particleId);

			double mass= CorsikaUtilities::GetParticleMass(particleId);
			if(mass==-999) continue;
                        if(particleId==CorsikaUtilities::eMuonPlusAddInfo || particleId==CorsikaUtilities::eMuonMinusAddInfo) continue;
			if(fStoreOnlyMuons && particleId!=CorsikaUtilities::eMuon && particleId!=CorsikaUtilities::eAntiMuon) continue;	

			mass/= 1000;//convert to GeV
			double Px= fParticle->Px;
			double Py= fParticle->Py;
			double Pz= fParticle->Pz;
			double X= fParticle->x/100.;//in m
			double Y= fParticle->y/100.;//in m

			double P2= Px*Px + Py*Py + Pz*Pz;
			double P= sqrt(P2);
			double TotEnergy= sqrt(P2 + mass*mass);
			double KinEnergy= TotEnergy - mass;

			TVector3 direction(Px/P2,Py/P2,Pz/P2);
			double theta= direction.Theta()*180./TMath::Pi(); 
			double phi= direction.Phi()*180./TMath::Pi(); 

			double time= fParticle->Time;
			double weight= fParticle->Weight;

			fParticleId[particleCounter]= particleId;
			//fParticleId[particleCounter]= particlePDGId;
                        fPx[particleCounter]= Px;
			fPy[particleCounter]= Py;
			fPz[particleCounter]= Pz;
			fX[particleCounter]= X;
			fY[particleCounter]= Y;
			
			fKinEnergy[particleCounter] = KinEnergy;
			fTheta[particleCounter]= theta;
			fPhi[particleCounter]= phi;
			fTime[particleCounter]= time;

                        particleCounter++;

			//if(particleId==0) cout<<"ParticleId="<<fParticleId[j]<<"  CorsikaId="<<fParticle->CorsikaID<<"  X="<<fX[j]<<"  Y="<<fY[j]<<"  E="<<KinEnergy<<endl;
    }//end loop particles


fNPartAtGround= particleCounter;
		//if(fNPartAtGround>0){
                        cout<<"CorsikaROOTReader::Read(): INFO: Filling tree..."<<endl;
			fOutputTreeInfo->Fill(); 
		//}

	}//end loop events


}//close CorsikaROOTReader::Read()


void CorsikaROOTReader::Save(){

        cout<<"CorsikaROOTReader::Save(): INFO: Saving data to file..."<<endl;     
	fOutputFile->cd();
	fOutputTreeInfo->Write();
	fOutputFile->Close();


}//close CorsikaROOTReader::Save()


