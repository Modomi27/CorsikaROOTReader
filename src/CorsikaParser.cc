#include "CorsikaParser.h"
#include "CorsikaUtilities.h"
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TObjectTable.h>
#include <TParticle.h>
 
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdexcept>
#include <utility>


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

using namespace std;

CorsikaParser::CorsikaParser(){

	fShowerNoToRead= 1;//if not specified read first shower as default, otherwise set which shower to read in CORSIKA file

}//close constructor

CorsikaParser::~CorsikaParser() {

	cout<<"Call CorsikaParser::~CorsikaParser"<<endl; 
	cout<<"Free allocated memory"<<endl;
	for(unsigned int i=0;i<fGroundParticles.size();i++) delete fGroundParticles[i];

	if(fParticle!=NULL) delete fParticle;

}//close destructor


void CorsikaParser::CalculateNeventsInPartFile(){

	crsRead::MCorsikaReader theCorsikaReader(fPartFileName,3);
	int ShowerCounter = 0;
  int RunCounter = 0;

	while(theCorsikaReader.GetRun(fRunHeader)) {
		RunCounter++;
			
		while(theCorsikaReader.GetShower(fEventHeader)) {//loop over all showers present in the CORSIKA file
			ShowerCounter++;
		}	//close while events
	}//close while run

	fNeventInPartFile= ShowerCounter;

}//close function


bool CorsikaParser::ReadPartFile() {
 
   crsRead::MCorsikaReader theCorsikaReader(fPartFileName,3);

   int ShowerCounter = 0;
   int RunCounter = 0;

   int PartCounter=0;
   int Nel=0;
   int Nmu=0;
   int Ngamma=0;
   int Npn=0;
   int Npi=0;
   int Npi0=0;
   int Neta=0;
   int Nkaon=0;
   int Ntau=0;
   int Nundef=0;
   int Nothers=0;
	
	 fParticleAngles.clear();
	 fParticleAngles.resize(0);

	 fGroundParticles.clear();
	 fGroundParticles.resize(0);
	 
	 	
   while(theCorsikaReader.GetRun(fRunHeader)) {
		RunCounter++;
		
		fNumberOfObsLevel= fRunHeader.GetNObservationLevels();//number of observation level for this run	
		cout<<"NObsLevel ==> "<<fNumberOfObsLevel<<endl;
		cout<<"ObsLevel height"<<fRunHeader.GetObservationHeight(fNumberOfObsLevel)<<endl;
			
		while(theCorsikaReader.GetShower(fEventHeader)) {//loop over all showers present in the CORSIKA file
	    	
			ShowerCounter++;

			//check here which shower to read (skip others)
			// it would be better to seek the desired shower block... come si fa a posizionarsi ad un dato eventheader? BOH!??
			//cout<<"thisEventNumber ==> "<< fEventHeader.GetEventNumber()<<"  "<<fShowerNoToRead<<endl;
			if(ShowerCounter!=fShowerNoToRead) continue;
			else{
	    			
				fTheta= fEventHeader.GetTheta();//GetTheta() returns in rad
				fPhi= fEventHeader.GetPhi();//GetPhi() returns in rad
				fEnergy= fEventHeader.GetEnergy();//GetEnergy in GeV
				fCutoffHadrons= fEventHeader.GetCutoffHadrons();//in GeV
				fCutoffMuons= fEventHeader.GetCutoffMuons();//in GeV
				fCutoffElectrons= fEventHeader.GetCutoffElectrons();//in GeV
				fCutoffPhotons= fEventHeader.GetCutoffPhotons();//in GeV
				fEFractThinH= fEventHeader.GetEFractionThinningH();
				fEFractThinEM= fEventHeader.GetEFractionThinningEM();
				fWMaxHadronic= fEventHeader.GetWMaxHadronic();
				fWMaxEM= fEventHeader.GetWMaxEM();


				cout<<"*** SHOWER INFO ***"<<endl;
				cout<<"Theta ==> "<<fTheta*180./TMath::Pi()<<endl;
				cout<<"Phi   ==> "<<fPhi*180./TMath::Pi()<<endl;
				cout<<"Energy ==>"<<fEnergy<<endl;
				cout<<"WmaxH ==> "<<fWMaxHadronic<<endl;
				cout<<"WmaxEM ==> "<<fWMaxEM<<endl;
				cout<<"EFractThinH ==>  "<<fEFractThinH<<endl;
				cout<<"EFractThinEM ==>  "<<fEFractThinEM<<endl;


	    		while(theCorsikaReader.GetData(fDataSubBlock)) {
		
					switch (fDataSubBlock.GetBlockType()){
		    
						//########################
						//###  BLOCK PART
						//########################
		    			case crs::TSubBlock::ePARTDATA:
							const crs::MParticleBlock & fParticleBlock= fDataSubBlock;							
    						crs::MParticleBlock::ParticleListConstIterator particleIter;//define a particle iterator

    						for(particleIter=fParticleBlock.FirstParticle();particleIter!=fParticleBlock.LastParticle();++particleIter) {//loop over all particles	
																
								crs::MParticle iPart (*particleIter);
								//cout<<"this ObsLevel ==> "<<iPart.GetObservationLevel()<<endl;

								//Get only particles (not nucleus,cherenkov) and only particles at the last OBS LEVEL
								if(!iPart.IsParticle()||iPart.GetObservationLevel()!=fNumberOfObsLevel) continue;//skip 
	    					
								int ParticleId= iPart.GetParticleID();
								int ParticlePDGId= iPart.GetPDGCode();

								//if(ParticlePDGId==CorsikaUtilities::ePDGUndefined) cout<<"ParticleId="<<ParticleId<<"  ParticlePDGId="<<ParticlePDGId<<endl;

								if(ParticlePDGId==CorsikaUtilities::ePDGElectron||ParticlePDGId==CorsikaUtilities::ePDGPositron) Nel++;
								else if(ParticlePDGId==CorsikaUtilities::ePDGMuon||ParticlePDGId==CorsikaUtilities::ePDGAntiMuon) Nmu++;
								else if(ParticlePDGId==CorsikaUtilities::ePDGPhoton) Ngamma++;
								else if(ParticlePDGId==CorsikaUtilities::ePDGProton||ParticlePDGId==CorsikaUtilities::ePDGNeutron||ParticlePDGId==CorsikaUtilities::ePDGAntiProton||ParticlePDGId==CorsikaUtilities::ePDGAntiNeutron) Npn++;
								else if(ParticlePDGId==CorsikaUtilities::ePDGPiPlus||ParticlePDGId==CorsikaUtilities::ePDGPiMinus) Npi++;
								else if(ParticlePDGId==CorsikaUtilities::ePDGPiZero) Npi0++;
								else if(ParticlePDGId==CorsikaUtilities::ePDGEta) Neta++;
								else if(ParticlePDGId==CorsikaUtilities::ePDGTau||ParticlePDGId==CorsikaUtilities::ePDGAntiTau) Ntau++;
								else if(ParticlePDGId==CorsikaUtilities::ePDGKaon0L||ParticlePDGId==CorsikaUtilities::ePDGKaon0S||ParticlePDGId==CorsikaUtilities::ePDGKaonPlus||ParticlePDGId==CorsikaUtilities::ePDGKaonMinus) Nkaon++;
								else if(ParticlePDGId==CorsikaUtilities::ePDGUndefined) Nundef++;
								//else continue;
								else Nothers++;


								double ParticleMass= iPart.GetMass();//in GeV
								double ParticleX= iPart.GetX();
								double ParticleY= iPart.GetY();
								double ParticlePx= iPart.GetPx();
								double ParticlePy= iPart.GetPy();
								double ParticlePz= iPart.GetPz();
								double ParticleKinEnergy= iPart.GetKinEnergy();//in GeV
								double ParticleTotEnergy= ParticleMass+ ParticleKinEnergy;
								double ParticleTime= iPart.GetTime();
								double ParticleWeight= iPart.GetWeight();
								double ParticleTheta= iPart.GetTheta();
	
								int mother1= 0;
								int mother2= 0;
								int daughter1= 0;
								int daughter2= 0;
								
								if(ParticlePDGId==CorsikaUtilities::ePDGElectron||ParticlePDGId==CorsikaUtilities::ePDGPositron||ParticlePDGId==CorsikaUtilities::ePDGMuon||ParticlePDGId==CorsikaUtilities::ePDGAntiMuon){
									fParticle= new TParticle(ParticlePDGId,-1, mother1, mother2, daughter1, daughter2, ParticlePx, ParticlePy, ParticlePz, ParticleTotEnergy, ParticleX, ParticleY, 0., ParticleTime);
									fParticle->SetWeight(ParticleWeight);
									fParticle->SetPolarisation(0,0,0);

									fGroundParticles.push_back(fParticle);
									fParticleAngles.push_back(ParticleTheta);
								}

								unsigned int Npart_stored= fGroundParticles.size();
								if(Npart_stored%1000000==0) cout<<Npart_stored<< " particles stored "<<endl;
								

								PartCounter++;
								if(PartCounter%1000000==0) cout<<PartCounter<< " particles looped "<<endl;

    						}//close loop for particles
						break;

						//########################
						//###  BLOCK LONG
						//########################
		    			//case crs::TSubBlock::eLONG:
						//	continue;
						//break;

		    			//default:
						//	continue;
						//break;
					}//close switch
			
				}// loop data
		
			crs::MEventEnd ShowerSummary;
			theCorsikaReader.GetShowerSummary(ShowerSummary);
						
			break;//skip all other events
		}//	close else	
		

	}//loop shower
	
		
  }//loop runs (usually just 1)    
   
  //cout<<"Read "<<fGroundParticles.size()<<" particles."<<endl;
  cout<<"Read "<<PartCounter<<" particles."<<endl;
  cout<<"Nelectrons="<<Nel<<endl;
  cout<<"Nmuons="<<Nmu<<endl;
  cout<<"Ngamma="<<Ngamma<<endl;
  cout<<"Npn="<<Npn<<endl;
  cout<<"Npi="<<Npi<<endl;
  cout<<"Npi0="<<Npi0<<endl;
  cout<<"Ntau="<<Ntau<<endl;
  cout<<"Neta="<<Neta<<endl;
  cout<<"Nkaon="<<Nkaon<<endl;
  cout<<"Nundef="<<Nundef<<endl;
  cout<<"Nothers="<<Nothers<<endl;

  
  if(ShowerCounter==0){
	ostringstream errMsg;
	errMsg << "No shower has been read...check ShowerNoToRead!";
	throw std::runtime_error(errMsg.str());
	return false;
  }//close if

  
  if(fGroundParticles.size()==0){
	ostringstream errMsg;
	errMsg << "WARNING: No ground particles stored!";
	//throw std::runtime_error(errMsg.str());
	//return false;
  }//close if

  


  return true; 

}//close function


bool CorsikaParser::ReadLongFile(){

  cout<<"Calling CorsikaParser::ReadLongFile()"<<endl;

  const double cosZenith = cos(fTheta);

  // Read CORSIKA profile if available
  ifstream longDataFile;
   
  longDataFile.open(fLongFileName.c_str());
  if (!longDataFile.is_open()) {
	 ostringstream errMsg;
     errMsg << "Cannot find file: " << fLongFileName;
     throw std::runtime_error(errMsg.str());
	 exit(1);
  }

  char line[256] = "";
  char auxline[256] = "";
  float dum = 0.0;
  char startstr0[256] = " LONGITUDINAL DISTRIBUTION IN";
  char endstr0[256] = " DEPTH     GAMMAS   POSITRONS";
  char endstr1[256] = " LONGITUDINAL ENERGY DEPOSIT";
  char endstr2[256] = " DEPTH       GAMMA    EM IONIZ     EM CUT";
  char endstr3[256] = " FIT OF THE HILLAS CURVE";
  int i = 0;
  int j = 0;
  int nBinsParticles = 0;  
  int nBinsEnergyDeposit = 0;  
  float dX = 0; // dEdX depth step width [g/cm2]
 
  float nbr = 0.;
  float maxi = 0.;
  float maxdepth = 0.;

  // scan for number of bins in depth of particle number profiles, 
  // energy deposit profiles and dX the step-width of the dEdX profile
  bool HaveParticleProfile = false;
  bool HaveEnergyDepositProfile = false;
  bool isSlantDepthProfile = false;


	
  while (longDataFile.getline(line, 140) && (!HaveParticleProfile || !HaveEnergyDepositProfile)) {

	// LONGITUDINAL DISTRIBUTION IN 174 VERTICAL STEPS OF 5. G/CM**2 FOR SHOWER 25250
    if (strstr(line, startstr0) != NULL){//find start string in current line 
       HaveParticleProfile = true;
       char s1[50], s2[50], s3[50], isVertOrSlant[50];
	   sscanf(line, "%s %s %s %i %s", s1, s2, s3, &nBinsParticles, isVertOrSlant);

	   cout<<"s1="<<s1<<" s2="<<s2<<" s3="<<s3<<" nBinsParticles="<<nBinsParticles<<" isVertOrSlant="<<isVertOrSlant<<endl;

       string testStr(isVertOrSlant);
       
	   if(testStr == "VERTICAL") isSlantDepthProfile = false;
	   else if (testStr == "SLANT") isSlantDepthProfile = true;
       else {
         ostringstream err;
         err << "Corsika longitunal file \"" << fLongFileName << "\" is invalid:\n"
                "line: \"" << line << "\" "
                "contains invalid string at                ^^^^^^^\n"
                "which is neither VERTICAL nor SLANT !";
         throw std::runtime_error(err.str());
	     exit(1); 
	   }//close else
	}//close if

	// LONGITUDINAL ENERGY DEPOSIT IN 174 VERTICAL STEPS OF 5. G/CM**2 FOR SHOWER 25250
    if (strstr(line, endstr1) != NULL) {
          
		HaveEnergyDepositProfile = true;    
		char s1[50], s2[50], s3[50], s4[50], isVertOrSlant[50], s5 [50], s6 [50];
		sscanf(line,"%s %s %s %s %i %s %s %s %f", s1, s2, s3, s4, &nBinsEnergyDeposit, isVertOrSlant, s5, s6, &dX);
		string testStr(isVertOrSlant);
		if(testStr == "VERTICAL") {
			isSlantDepthProfile = false;
			dX /= cosZenith;//convert vertical depth in slant depth
		} 
		else if (testStr == "SLANT") isSlantDepthProfile = true;
		else {
			ostringstream err;
			err << "Corsika longitunal file \"" << fLongFileName << "\" is invalid:\n"
	               "line: \"" << line << "\" "
			       "contains invalid string at                ^^^^^^^\n"
                   " which is neither VERTICAL nor SLANT !";
            throw std::runtime_error(err.str());
			exit(1); 
		}//close else
     }//close if

   } //close while --  end scan file  ---


   //NOW READ ENTRIES
   //dummy read of first 2 lines
   longDataFile.getline(line, 140);
   longDataFile.getline(line, 140);
   sscanf(line, "%f", &nbr);
 
   fDepth.resize(nBinsParticles);
   fLongCharged.resize(nBinsParticles);
   fLongMuons.resize(nBinsParticles);
   fLongGammas.resize(nBinsParticles);
   fLongElectrons.resize(nBinsParticles);

   fDepth_dE.resize(nBinsEnergyDeposit);
   fDeltaEn.resize(nBinsEnergyDeposit);

   longDataFile.close();

   longDataFile.open(fLongFileName.c_str());
 
   //### SEARCH SHOWER NO ###
   int sh = 0;
   int findShower = 0;
   findShower = fShowerNoToRead-1;
   bool find = true;
   while(sh!=findShower) {
	 if(longDataFile.getline(line, 140)) {
	   if(strstr(line, startstr0)) ++sh;
     }//close if
	 else{
	   sh = findShower;
	   find = false;
	 }//close else
   }//close while

   if (!find) {
	 ostringstream msg;
     msg << "Cannot find shower " << findShower << " in file.";
     throw std::runtime_error(msg.str());
	 exit(1);
   } 

   while(longDataFile.getline(line, 140)) {
      if(strstr(line, startstr0)) longDataFile.getline(line, 140);
      if(strstr(line, endstr1) || strstr(auxline, endstr2)) {
		if(strstr(line, endstr1))
			longDataFile.getline(line, 140);
			if(strstr(line, endstr2)) {            
			  for(int ll = 0; ll < 132; ++ll) auxline[ll] = line[ll];
			  longDataFile.getline(line, 140);
			}
			if (strstr(line, endstr3)) break;
			if (strstr(auxline, endstr2) && j < nBinsParticles) {

			  float xdepth = 0.0;
			  float sumenergy = 0.0;
			  float neutrino = 0.0;
	          float hadroncut = 0.0;
			  float muoncut = 0.0;

	          sscanf(line, "%f %f %f %f %f %f %f %f %f %f",&xdepth, &dum, &dum, &dum, &dum, &muoncut,&dum, &hadroncut, &neutrino, &sumenergy);

			  if (!isSlantDepthProfile) xdepth /= cosZenith;

 
	          // dEdX profile has slightly different depth-bins
	          fDepth_dE[j] = xdepth;
	          // Subtracting neutrino energy 
	          // and take fraction for muons and hadrons from 
	          //  Barbosa et al Astro. Part. Phys. 22, (2004) p. 159
	          static float muonFraction = 0.575;
              static float hadronFraction = 0.261;
	          fDeltaEn[j] = sumenergy - neutrino - muonFraction * muoncut - hadronFraction * hadroncut;

		      fDeltaEn[j] /= dX;
              ++j;
	       }//close if
	     }//close if
     
         if (!strstr(line, endstr1) || strstr(line, endstr0) && i < nBinsParticles) {
             if (strstr(auxline, endstr2)) continue;
	         float xdepth = 0.0;
			 float chargedparticles = 0.0;
			 float gammas, positrons, electrons, muplus, muminus, hadrons;
		     float nuclei, cerenkov;
             sscanf(line, "%f %f %f %f %f %f %f %f %f %f",&xdepth, &gammas, &positrons, &electrons, &muplus, &muminus,&hadrons, &chargedparticles, &nuclei, &cerenkov);

			 if (xdepth > 0) {
			   //BRD 17/2/05 CORSIKA depths are vertical assuming a flat
               //Earth.  So apply cosTheta correction here.  
               // RU Wed Jun 13 14:46:44 CEST 2007
               // if SLANT was used in CORSIKA, don't do the cosZenith correction
			  if (!isSlantDepthProfile) xdepth /= cosZenith;
         
			  fDepth[i] = xdepth;
              fLongCharged[i] = chargedparticles;
              fLongMuons[i] = muplus + muminus;
              fLongGammas[i] = gammas;
              fLongElectrons[i] = electrons + positrons;
              if (chargedparticles > maxi) {
                maxi = chargedparticles;
				maxdepth = xdepth;
			  }
			  ++i;
			}//close if xdepth>0
		}//close if
   }//close while
   
   

   while (longDataFile.getline(line, 140))
	  if (strstr(line, " PARAMETERS         = ")) {

      sscanf(line, " PARAMETERS         =   %f %f %f %f %f %f", &fNmax, &fX0, &fXmax, &fGH_a, &fGH_b, &fGH_c); 
	  longDataFile.getline(line, 140);
      sscanf(line, " CHI**2/DOF         = %f", &fGHChi);
 

      if (!isSlantDepthProfile) {
         fGH_a /= cosZenith;
         fGH_b /= cosZenith;
         fGH_c /= cosZenith;
         fXmax /= cosZenith;
      }
 
     
      cout << "Nmax = " << fNmax << "  Xmax = " << fXmax << "  X0 = " << fX0 << "  Zenith = " << acos(cosZenith)<< (isSlantDepthProfile ? " (SLANT DEPTH)" : " (VERTICAL DEPTH)")<<endl;
    
 
     break;
  }//close while
  // end of read profile

 longDataFile.close();

 cout<<"*** depth, gamma, muons, charged...***"<<endl;
 for(unsigned int jj=0;jj<fDepth.size();jj++) cout<<fDepth[jj]<<"  "<<fLongGammas[jj]<<"  "<<fLongMuons[jj]<<"  "<<fLongCharged[jj]<<endl;

	return true;

}//close function
