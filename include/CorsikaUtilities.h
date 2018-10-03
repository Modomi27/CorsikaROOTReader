#ifndef _CORSIKAUTILITIES_H_
#define _CORSIKAUTILITIES_H_

#include <TVector3.h>
#include <TRotation.h>
#include <string>
#include <iostream>
#include <sstream>
#include <map>


class CorsikaUtilities {

public:

	CorsikaUtilities();
 	~CorsikaUtilities();	

	static int CorsikaToPDG(int CorsikaId);//convert from Corsika code to PDG code
	static double GetParticleMass(int ParticleId);

	//****************************
	//** convert a point from core system (CORSIKA particle info are given in core system) to the shower system
	//  Shower Coordinate System Z axis along shower axis, X-Y are 2 perpendicular axis in the front plane
  TVector3 CoreCSToShowerCS(double Theta,double Phi,TVector3 point);
	double NormalizeAngle(const double angle);
	double CorsikaAzimuthToAuger(double corsikaAzimuth, double magneticFieldDeclination);

	//define PDG enum codes
	enum PDGParticleType {
		ePDGUndefined = 0,
		ePDGElectron = 11, 
		ePDGPositron = -11,
		ePDGNuElectron = 12,
		ePDGAntiNuElectron = -12,
		ePDGMuon = 13, 
		ePDGAntiMuon = -13,
	        ePDGNuMuon = 14, 
		ePDGAntiNuMuon = -14,
		ePDGTau = 15, 
		ePDGAntiTau = -15,
		ePDGNuTau = 16, 
		ePDGAntiNuTau = -16,
		ePDGPhoton = 22,	
		ePDGPiZero = 111, 
		ePDGPiPlus = 211, 
		ePDGPiMinus = -211,
		ePDGEta = 221,
		ePDGKaon0L = 130, 
		ePDGKaon0S = 310,
		ePDGKaonPlus = 321, 
		ePDGKaonMinus = -321, 
		ePDGLambda = 3122, 
		ePDGAntiLambda = -3122,
		ePDGNeutron = 2112, 
		ePDGAntiNeutron = -2112,
		ePDGProton = 2212, 
		ePDGAntiProton = -2212,
		ePDGMuonPlusAddInfo=75,
		ePDGMuonMinusAddInfo=76
	};

	//define Corsika codes
	enum CorsikaParticleType{
		eUndefined = 0,
		ePhoton = 1,
		eElectron = 3,
		ePositron = 2,
		eMuon = 6,
		eAntiMuon = 5,
		ePiZero = 7,
		ePiPlus = 8,
		ePiMinus = 9,
		eProton = 14,
		eNeutron = 13,
		eAntiNeutron = 25,
		eAntiProton = 15,
		eTau= 132,
		eAntiTau= 131,
		eEta= 17,
		eKaon0L = 10,
		eKaon0S = 16,
		eKaonPlus= 11,
		eKaonMinus= 12,
		eLambda= 18,
		eAntiLambda= 26,
		eLambdacPlus= 137,

		eNuElectron= 66,
		eAntiNuElectron= 67,
		eNuMuon= 68,
		eAntiNuMuon= 69,
		eNuTau= 133,
		eAntiNuTau= 134,
		eMuonPlusAddInfo=75,
		eMuonMinusAddInfo=76
	};


	//## define particle masses
	static constexpr double kProtonMass = 938.271998;//MeV
	static constexpr double kNeutronMass = 939.56533;//MeV
	static constexpr double kLambdaMass = 1115.683;//MeV
	static constexpr double kLambdacMass = 2286.46;//MeV
	static constexpr double kKaonChargedMass = 493.677;//MeV
	static constexpr double kKaonZeroMass = 497.672;//MeV
	static constexpr double kEtaMass = 547.30;//MeV
	static constexpr double kPiChargedMass = 139.57018;//MeV
	static constexpr double kPiZeroMass = 134.9766;//MeV
	static constexpr double kTauMass = 1776.99;//MeV
	static constexpr double kMuonMass = 105.658357;//MeV
	static constexpr double kElectronMass = 0.510998902;//MeV
	

private:

	static void InsertCorsikaToPDG(int theCorsikaCode, int thePDGCode);//insert pairs in map
	static void InitCorsikaToPDGMap();//initialize and fill the map



};//close class

#endif
