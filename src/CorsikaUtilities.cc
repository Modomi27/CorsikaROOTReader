#include "CorsikaUtilities.h"

#include <TVector3.h>
#include <TRotation.h>
#include <TMath.h>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <map>


using namespace std;

std::map<int,int> CorsikaToPDGMap;


CorsikaUtilities::CorsikaUtilities(){

}//close constructor

CorsikaUtilities::~CorsikaUtilities() {

}//close destructor


void CorsikaUtilities::InsertCorsikaToPDG(int theCorsikaCode, int thePDGCode){

	if (! CorsikaToPDGMap.insert(std::make_pair(theCorsikaCode,thePDGCode)).second ) {
	  ostringstream errMsg;
	  errMsg << "Cannot insert pair ("
	      << theCorsikaCode << ", " << thePDGCode
          << ") into CorsikaToPDG map.";
	  throw std::runtime_error(errMsg.str());
	}//close if
}//close function


void CorsikaUtilities::InitCorsikaToPDGMap(){

	//fill the map	
	InsertCorsikaToPDG(CorsikaUtilities::eUndefined, CorsikaUtilities::ePDGUndefined);

	InsertCorsikaToPDG(CorsikaUtilities::ePhoton, CorsikaUtilities::ePDGPhoton);
	InsertCorsikaToPDG(CorsikaUtilities::ePositron, CorsikaUtilities::ePDGPositron);
	InsertCorsikaToPDG(CorsikaUtilities::eElectron, CorsikaUtilities::ePDGElectron);
 
  InsertCorsikaToPDG(CorsikaUtilities::eAntiMuon, CorsikaUtilities::ePDGAntiMuon);
  InsertCorsikaToPDG(CorsikaUtilities::eMuon, CorsikaUtilities::ePDGMuon);
  InsertCorsikaToPDG(CorsikaUtilities::ePiZero, CorsikaUtilities::ePDGPiZero);
  InsertCorsikaToPDG(CorsikaUtilities::ePiPlus, CorsikaUtilities::ePDGPiPlus);
  InsertCorsikaToPDG(CorsikaUtilities::ePiMinus, CorsikaUtilities::ePDGPiMinus);
 
  InsertCorsikaToPDG(CorsikaUtilities::eKaon0L, CorsikaUtilities::ePDGKaon0L);
  InsertCorsikaToPDG(CorsikaUtilities::eKaonPlus, CorsikaUtilities::ePDGKaonPlus);
  InsertCorsikaToPDG(CorsikaUtilities::eKaonMinus, CorsikaUtilities::ePDGKaonMinus);
  InsertCorsikaToPDG(CorsikaUtilities::eNeutron, CorsikaUtilities::ePDGNeutron);
  InsertCorsikaToPDG(CorsikaUtilities::eProton, CorsikaUtilities::ePDGProton);
  InsertCorsikaToPDG(CorsikaUtilities::eAntiProton, CorsikaUtilities::ePDGAntiProton);
  InsertCorsikaToPDG(CorsikaUtilities::eKaon0S, CorsikaUtilities::ePDGKaon0S);
  InsertCorsikaToPDG(CorsikaUtilities::eEta, CorsikaUtilities::ePDGEta);
  InsertCorsikaToPDG(CorsikaUtilities::eLambda, CorsikaUtilities::ePDGLambda);
 
  InsertCorsikaToPDG(CorsikaUtilities::eAntiNeutron, CorsikaUtilities::ePDGAntiNeutron);
  InsertCorsikaToPDG(CorsikaUtilities::eAntiLambda, CorsikaUtilities::ePDGAntiLambda);

  InsertCorsikaToPDG(CorsikaUtilities::eNuElectron, CorsikaUtilities::ePDGNuElectron);
  InsertCorsikaToPDG(CorsikaUtilities::eAntiNuElectron, CorsikaUtilities::ePDGAntiNuElectron);
  InsertCorsikaToPDG(CorsikaUtilities::eNuMuon, CorsikaUtilities::ePDGNuMuon);
  InsertCorsikaToPDG(CorsikaUtilities::eAntiNuMuon, CorsikaUtilities::ePDGAntiNuMuon);
 
  InsertCorsikaToPDG(71, CorsikaUtilities::ePDGEta);
  InsertCorsikaToPDG(72, CorsikaUtilities::ePDGEta);
  InsertCorsikaToPDG(73, CorsikaUtilities::ePDGEta);
  InsertCorsikaToPDG(74, CorsikaUtilities::ePDGEta);


  InsertCorsikaToPDG(CorsikaUtilities::eMuonPlusAddInfo, CorsikaUtilities::ePDGMuonPlusAddInfo);
  InsertCorsikaToPDG(CorsikaUtilities::eMuonMinusAddInfo, CorsikaUtilities::ePDGMuonMinusAddInfo);

}//close function



int CorsikaUtilities::CorsikaToPDG(int theCorsikaCode){
			
	if (theCorsikaCode < 100) { //particle
		if(!CorsikaToPDGMap.size()) InitCorsikaToPDGMap();
		map<int, int>::const_iterator index = CorsikaToPDGMap.find(theCorsikaCode);
		if (index != CorsikaToPDGMap.end()) return index->second;
		else return CorsikaUtilities::ePDGUndefined;		
  }//close if 
	else if(theCorsikaCode < 9900) {  // nucleus
		unsigned int Z = theCorsikaCode % 100;
	  unsigned int A = theCorsikaCode / 100;
	  //return Particle::NucleusCode(Z, A);
		return CorsikaUtilities::ePDGUndefined;//CHANGE ME!	
	}//close else if 
	else {// Cherenkov
		return CorsikaUtilities::ePDGUndefined;
	}//close else 

			
}//close function 


double CorsikaUtilities::GetParticleMass(int ParticleId){

	switch (ParticleId) {
		case(eUndefined):
			return 0; 
		break;
		case(eProton):
			return kProtonMass; 
		break;
		case(eAntiProton):
			return kProtonMass; 
		break;
		case(eNeutron):
			return kNeutronMass; 
		break;
		case(eAntiNeutron):
			return kNeutronMass; 
		break;
		case(eLambda):
			return kLambdaMass; 
		break;
		case(eAntiLambda):
			return kLambdaMass; 
		break;
		case(eLambdacPlus):
			return kLambdacMass; 
		break;
		case(eKaonPlus):
			return kKaonChargedMass; 
		break;
		case(eKaonMinus):
			return kKaonChargedMass; 
		break;
		case(eKaon0S):
			return kKaonZeroMass; 
		break;
		case(eKaon0L):
			return kKaonZeroMass; 
		break;
		case(eEta):
			return kEtaMass; 
		break;
		case(ePiPlus):
			return kPiChargedMass; 
		break;
		case(ePiMinus):
			return kPiChargedMass; 
		break;
		case(ePiZero):
			return kPiZeroMass; 
		break;
		case(eElectron):
			return kElectronMass; 
		break;
		case(ePositron):
			return kElectronMass; 
		break;
		case(eMuon):
			return kMuonMass; 
		break;
		case(eAntiMuon):
			return kMuonMass; 
		break;



		case(eMuonPlusAddInfo):
			return kMuonMass; 
		break;
		case(eMuonMinusAddInfo):
			return kMuonMass; 
		break;


		case(eTau):
			return kTauMass; 
		break;
		case(eAntiTau):
			return kTauMass; 
		break;
		case(eNuElectron):
			return 0; 
		break;
		case(eAntiNuElectron):
			return 0; 
		break;
		case(eNuMuon):
			return 0; 
		break;
		case(eAntiNuMuon):
			return 0; 
		break;
		case(eNuTau):
			return 0; 
		break;
		case(eAntiNuTau):
			return 0; 
		break;

		case(ePhoton):
			return 0; 
		break;	

		default:
		{
			cerr<<"CorsikaUtilities::GetParticleMass(): WARNING: Cannot assign the mass of this particle (id="<<ParticleId<<")...setting mass=-999!!!"<<endl;
			return -999;
		}
	}//end switch

	return -999;


}//close CorsikaUtilities::GetParticleMass()


TVector3 CorsikaUtilities::CoreCSToShowerCS(double Theta,double Phi,TVector3 Point){

  TVector3 PointInShowerCS;

  TRotation RotationMatrix1;
  RotationMatrix1.RotateZ(Phi);
  TRotation RotationMatrix2;
  RotationMatrix2.RotateY(Theta);
  
  TRotation FinalRotationMatrix;
  FinalRotationMatrix= RotationMatrix2*RotationMatrix1;

  PointInShowerCS= FinalRotationMatrix.Inverse()*Point;

  return PointInShowerCS;

}//close function


double CorsikaUtilities::NormalizeAngle(const double angle){
	
	if (angle > TMath::Pi())
		return angle - int((TMath::Pi()+angle)/(2*TMath::Pi())) * 2*TMath::Pi();
	if (angle < -TMath::Pi())
		return angle + int((TMath::Pi()-angle)/(2*TMath::Pi())) * 2*TMath::Pi();

	return angle;

}//close CorsikaUtilities::NormalizeAngle()


double CorsikaUtilities::CorsikaAzimuthToAuger(double corsikaAzimuth, double magneticFieldDeclination){
	
	//## Returns the azimuth rotated from Corisika's system to Auger standard.
	//## Rotate form the Corsika coordinate system to Auger standard. Auger places the x axis east and the y axis north.
	//## Corsika places the x axis in the magnetic north and the y axis west. Therefore, the geomagnetic field direction 
	//## for the location and time of an event has to be taken into account for the correct transformation.
	//## Auger uses the incomming direction, Corsika the outgoing direction. This adds 180 deg to the difference.
	
	//magneticFieldDeclination = 4.233 deg for Auger

	return NormalizeAngle(corsikaAzimuth + 90.0 - magneticFieldDeclination);

}//close CorsikaUtilities::CorsikaAzimuthToAuger()


