#include "CorsikaParser.h"
#include "CorsikaROOTReader.h"
#include "CorsikaUtilities.h"
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TMath.h>
#include <TVector3.h>
#include <TString.h>
#include <TParticle.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdexcept>


using namespace std;


std::string inputFileName= "";
std::string outputFileName= "";
bool storeOnlyMuons= false;
void ReadPartData();
void ReadROOTData();

void Usage(){
	cout<<"**********************"<<endl;
	cout<<"*** MACRO USAGE    ***"<<endl;
	cout<<"**********************"<<endl;
	cout<<"CorsikaReader --[runmode] --input=[path-to-inputfile] --output=[outputfile] --storeOnlyMuons=[storeOnlyMuons]"<<endl;
	cout<<"	[runmode]"<<endl;
	cout<<"      part: Read Corsika data in binary format"<<endl;
	cout<<"      root: Read Corsika data in ROOT format"<<endl;
	cout<<"      storeOnlyMuons: Store only muons in output file"<<endl;
	cout<<endl;
}

int main(int argc, char **argv){

  if (argc<3) {	
   cout << "ERROR: Incorrect number of arguments...see macro usage!" << endl;
   Usage();
   return 0;
  }

	//## handle input arguments
	std::string arg_format="--input=";
	std::string arg_format_out="--output=";
	std::string arg_format_storeOnlyMuons="--storeOnlyMuons=";
	inputFileName="";
	outputFileName="";
	storeOnlyMuons=false;

	if(!strstr(argv[2],arg_format.c_str())){//mistake in giving the config argument	 
		std::string errMsg = "ERROR: Give the config argument in form --input=[path-to-file]...exit!";
    		throw std::runtime_error(errMsg);	
		exit(1);
	}
	else{//config argument specified correctly => get the file
		
		std::string input_arg= std::string(argv[2]);
		int readpos = input_arg.find("="); 
		inputFileName = input_arg.substr(readpos+1);// get from "--config=" to the end
	}
	cout<<"INFO: Reading Corsika data from file "<<inputFileName.c_str()<<"..."<<endl;


	if(argc==3){
	  outputFileName = "Output.root";
        }
        else{
	  if(!strstr(argv[3],arg_format_out.c_str())){//mistake in giving the config argument	 
		std::string errMsg = "ERROR: Give the config argument in form --input=[path-to-file]...exit!";
    		throw std::runtime_error(errMsg);	
		exit(1);
	  }
	  else{//config argument specified correctly => get the file	
		std::string output_arg= std::string(argv[3]);
		int readpos = output_arg.find("="); 
		outputFileName = output_arg.substr(readpos+1);// get from "--config=" to the end
	  }
        } 
	cout<<"INFO: Saving output to file "<<outputFileName.c_str()<<"..."<<endl;


	//## store only muons
	if(argc==4){
	  storeOnlyMuons= false;
	}
	else{
	  if(!strstr(argv[4],arg_format_storeOnlyMuons.c_str())){//mistake in giving the config argument
                std::string errMsg = "ERROR: Give the config argument in form --storeOnlyMuons=[path-to-file]...exit!";
                throw std::runtime_error(errMsg);
                exit(1);
          }
          else{//config argument specified correctly => get the option
                std::string storeOnlyMuons_arg= std::string(argv[4]);
                int readpos = storeOnlyMuons_arg.find("=");
                storeOnlyMuons = atoi(storeOnlyMuons_arg.substr(readpos+1).c_str());// get from "--[...]=" to the end
          }
	cout<<"storeOnlyMuons? "<<storeOnlyMuons<<endl;
	}
	//## get run mode
	if(strcmp(argv[1],"--part")==0) {	
		cout<<"**********************"<<endl;
		cout<<"** PART READING   ****"<<endl;
		cout<<"**********************"<<endl;
		ReadPartData();
	}
	else if(strcmp(argv[1],"--root")==0) {
		cout<<"**********************"<<endl;
		cout<<"** ROOT READING   ****"<<endl;
		cout<<"**********************"<<endl;
		ReadROOTData();	
	}
	else{
		//mistake in giving the run mode argument
		std::string errMsg = "ERROR: Execution mode " + string(argv[1])
      + " not defined...exit!";
    throw std::runtime_error(errMsg);	 
		exit(1);
	}  
  
  return 0;


}//close main


void ReadROOTData(){

	cout<<"ReadROOTData(): INFO: Reading data from file "<<inputFileName.c_str()<<"..."<<endl;
	CorsikaROOTReader* reader= new CorsikaROOTReader();
	reader->SetInputFileName(inputFileName);
	reader->SetOutputFileName(outputFileName);
	reader->SetStoreOnlyMuons(storeOnlyMuons);

	reader->Init();
	reader->Read();
	reader->Save();
	

}//close ReadROOTData


void ReadPartData(){

	cout<<"INFO: Reading Corsika data in binary format..."<<endl;

	double ShowerTheta, ShowerPhi, ShowerEnergy;
	double X,Y,Z,Px,Py,Pz,E,t,W,Theta;
	double Xproj,Yproj,Zproj;
	double r,rproj;
	int EventId,ParticleId;

	FILE* fout= fopen("AsciiOutput.txt","w");

  TFile* f= new TFile("RootOutput.root","RECREATE");

	TTree* SimInfo= new TTree("SimInfo","SimInfo");
	SimInfo->Branch("EventId",&EventId,"EventId/I");
	SimInfo->Branch("ParticleId",&ParticleId,"ParticleId/I");
	SimInfo->Branch("X",&X,"X/D");
	SimInfo->Branch("Y",&Y,"Y/D");
	SimInfo->Branch("Z",&Z,"Z/D");
	SimInfo->Branch("Xproj",&Xproj,"Xproj/D");
	SimInfo->Branch("Yproj",&Yproj,"Yproj/D");
	SimInfo->Branch("Zproj",&Zproj,"Zproj/D");
	SimInfo->Branch("Px",&Px,"Px/D");
	SimInfo->Branch("Py",&Py,"Py/D");
	SimInfo->Branch("Pz",&Pz,"Pz/D");
	SimInfo->Branch("E",&E,"E/D");
	SimInfo->Branch("t",&t,"t/D");
	SimInfo->Branch("Theta",&Theta,"Theta/D");
	SimInfo->Branch("W",&W,"W/D");  

  //std::string filename(argv[1]);
	std::string filename= inputFileName;
  string longfilename= filename+".long";
  cout<<"LONG ==> "<<longfilename<<endl;
    
  CorsikaParser* theCorsikaParser= new CorsikaParser();
	theCorsikaParser->SetInputPartFileName(filename);
	theCorsikaParser->SetInputLongFileName(longfilename);

	theCorsikaParser->CalculateNeventsInPartFile();
	int Nevents= theCorsikaParser->GetNeventsInPartFile();
	cout<<"Nevents="<<Nevents<<endl;

	CorsikaUtilities* theCorsikaUtils= new CorsikaUtilities();

	for(int i=0;i<Nevents;i++){
		cout<<"*****************************"<<endl;
		cout<<"** reading EVENT "<<i+1<<" **"<<endl;
		cout<<"*****************************"<<endl;
		theCorsikaParser->SetEventToRead(i+1);
  	theCorsikaParser->ReadPartFile();
  	//theCorsikaParser->ReadLongFile();
		cout<<endl;
		cout<<endl;

		//shower info
		ShowerEnergy= theCorsikaParser->GetEnergy();
		ShowerTheta= theCorsikaParser->GetTheta();
		ShowerPhi= theCorsikaParser->GetPhi();

		std::vector<TParticle*> grdParticles= theCorsikaParser->GetParticlesAtGround();
		std::vector<double> grdParticleAngles= theCorsikaParser->GetParticleAnglesAtGround();
		cout<<"Number of ground particles ==> "<<grdParticles.size()<<endl;

		for(unsigned int k=0;k<grdParticles.size();k++){
			//get only muons
    	int currentId= grdParticles[k]->GetPdgCode();
			//cout<<"currentId="<<currentId<<endl;
			if(currentId!=CorsikaUtilities::ePDGMuon && currentId!=CorsikaUtilities::ePDGAntiMuon) continue;

			//cout<<"currentId="<<currentId<<endl;
			EventId= i+1;
			ParticleId= currentId;
			X= grdParticles[k]->Vx()/100.;//in meter
			Y= grdParticles[k]->Vy()/100.;//in meter
			
			
			Px= grdParticles[k]->Px();//in GeV
			Py= grdParticles[k]->Py();//in GeV
			Pz= grdParticles[k]->Pz();//in GeV
	
			E= grdParticles[k]->Energy();
			t= grdParticles[k]->T();
		  W= grdParticles[k]->GetWeight();
			Theta= grdParticleAngles[k];

			
			TVector3 thisPoint;
			thisPoint.SetXYZ(X,Y,Z);
			TVector3 thisPointInShowerCS;
			thisPointInShowerCS= theCorsikaUtils->CoreCSToShowerCS(ShowerTheta,ShowerPhi,thisPoint);
			cout<<"thisPointInShowerCS="<<thisPointInShowerCS.X()<<"  "<<thisPointInShowerCS.Y()<<"  "<<thisPointInShowerCS.Z()<<endl;
			Xproj= thisPointInShowerCS.X();
			Yproj= thisPointInShowerCS.Y();
			Zproj= thisPointInShowerCS.Z();

			r= sqrt(X*X+Y*Y);
			rproj= sqrt(Xproj*Xproj+Yproj*Yproj);

			fprintf(fout,"%d    %d    %g    %g    %g    %g    %g    %g    %g    %g    %g\n",i+1,ParticleId,X,Y,Px,Py,Pz,E,t,Theta,W);

			SimInfo->Fill();
		}//close loop ground particles

  }//close loop events

	fclose(fout);

	SimInfo->Write();
	f->Close();

  /*
  
	
  std::vector<TParticle*> grdParticles= theCorsikaParser->GetParticlesAtGround();
  double Theta= theCorsikaParser->GetTheta();
  double Phi= theCorsikaParser->GetPhi();


	std::vector<double> depth= theCorsikaParser->GetLongitudinalDepth();
	std::vector<double> longCharged= theCorsikaParser->GetLongitudinalCharged();
	std::vector<double> longMuons= theCorsikaParser->GetLongitudinalMuons();
	std::vector<double> longElectrons= theCorsikaParser->GetLongitudinalElectrons();
	std::vector<double> longGammas= theCorsikaParser->GetLongitudinalGammas();
	const unsigned int Ndepth= depth.size();
	
	double x,y,z,px,py,pz,E,Rgrd,Rplane,t,weight;
	int type;


	//search minimum time@ground
	double MinTime= 1.e+99;
	double MaxTime= -999;

	for(unsigned int i=0;i<grdParticles.size();i++){
		double time= grdParticles[i]->T();
		if(time<MinTime) MinTime= time;
		if(time>MaxTime) MaxTime= time;
 	}//close for
	cout<<"MIN TIME ==> "<<MinTime<<endl;
	cout<<"MAX TIME ==> "<<MaxTime<<endl;

  TFile* f= new TFile("out.root","RECREATE");

	TTree* SimInfo= new TTree();
	SimInfo->Branch("x",&x,"x/D");
	SimInfo->Branch("y",&y,"y/D");
	SimInfo->Branch("px",&px,"px/D");
	SimInfo->Branch("py",&py,"py/D");
	SimInfo->Branch("pz",&pz,"pz/D");
	SimInfo->Branch("E",&E,"E/D");
	SimInfo->Branch("t",&t,"t/D");
	SimInfo->Branch("type",&type,"type/I");
	SimInfo->Branch("Rgrd",&Rgrd,"Rgrd/D");
	SimInfo->Branch("Rplane",&Rplane,"Rplane/D");
	SimInfo->Branch("weight",&weight,"weight/D");

  TH2D* EventMap=new TH2D("EventMap","",100,-10000,10000,100,-10000,10000);
  EventMap->Sumw2();

  TH1D* ElectronLDFHisto=new TH1D("ElectronLDFHisto","",100,0,10000);
  ElectronLDFHisto->Sumw2();

  TH1D* ElectronLDFDensityHisto=new TH1D("ElectronLDFDensityHisto","",100,0,10000);
  ElectronLDFDensityHisto->Sumw2();

  TH1D* ElectronLDFInShowerPlaneHisto=new TH1D("ElectronLDFInShowerPlaneHisto","",100,0,10000);
  ElectronLDFInShowerPlaneHisto->Sumw2();

  TH1D* ElectronLDFDensityInShowerPlaneHisto=new TH1D("ElectronLDFDensityInShowerPlaneHisto","",100,0,10000);
  ElectronLDFDensityInShowerPlaneHisto->Sumw2();

	TH1D* ElectronEnergyHisto=new TH1D("ElectronEnergyHisto","",100,0,100);
  ElectronEnergyHisto->Sumw2();

	TH1D* ElectronTimeHisto=new TH1D("ElectronTimeHisto","",100,0,30000);
  ElectronTimeHisto->Sumw2();
	TH1D* ElectronTimeFromInteractionHisto=new TH1D("ElectronTimeFromInteractionHisto","",100,MinTime-1000,MaxTime+1000);
  ElectronTimeFromInteractionHisto->Sumw2();

  TH1D* MuonLDFHisto=new TH1D("MuonLDFHisto","",100,0,10000);
  MuonLDFHisto->Sumw2();
  
  TH1D* MuonLDFDensityHisto=new TH1D("MuonLDFDensityHisto","",100,0,10000);
  MuonLDFDensityHisto->Sumw2();

  TH1D* MuonLDFInShowerPlaneHisto=new TH1D("MuonLDFInShowerPlaneHisto","",100,0,10000);
  MuonLDFInShowerPlaneHisto->Sumw2();

  TH1D* MuonLDFDensityInShowerPlaneHisto=new TH1D("MuonLDFDensityInShowerPlaneHisto","",100,0,10000);
  MuonLDFDensityInShowerPlaneHisto->Sumw2();

	TH1D* MuonEnergyHisto=new TH1D("MuonEnergyHisto","",100,0,100);
  MuonEnergyHisto->Sumw2();

	TH1D* MuonTimeHisto=new TH1D("MuonTimeHisto","",100,0,30000);
  MuonTimeHisto->Sumw2();
	TH1D* MuonTimeFromInteractionHisto=new TH1D("MuonTimeFromInteractionHisto","",100,MinTime-1000,MaxTime+1000);
  MuonTimeFromInteractionHisto->Sumw2();

	

  for(unsigned int i=0;i<grdParticles.size();i++){
	//get only e+e-
    int currentId= grdParticles[i]->GetPdgCode();
		type= currentId;
		x= grdParticles[i]->Vx()/100.;//in meter
		y= grdParticles[i]->Vy()/100.;//in meter
		z= 0.;
		px= grdParticles[i]->Px();//in GeV
		py= grdParticles[i]->Py();//in GeV
		pz= grdParticles[i]->Pz();//in GeV
	
		E= grdParticles[i]->Energy();
		t= grdParticles[i]->T();
		weight= grdParticles[i]->GetWeight();

		TVector3 thisPoint;
		thisPoint.SetXYZ(x,y,z);
		TVector3 thisPointInShowerCS;
		thisPointInShowerCS= theCorsikaUtils->CoreCSToShowerCS(Theta,Phi,thisPoint);

		double x_plane= thisPointInShowerCS.X();
		double y_plane= thisPointInShowerCS.Y();
		double z_plane= thisPointInShowerCS.Z();

		Rgrd= sqrt(x*x+y*y);
		Rplane= sqrt(x_plane*x_plane+y_plane*y_plane);


		if(currentId==CorsikaUtilities::ePDGElectron||currentId==CorsikaUtilities::ePDGPositron){
				
			ElectronLDFHisto->Fill(Rgrd,weight);
			ElectronLDFInShowerPlaneHisto->Fill(Rplane,weight);

			ElectronLDFDensityHisto->Fill(Rgrd,weight);
			ElectronLDFDensityInShowerPlaneHisto->Fill(Rplane,weight);

			EventMap->Fill(x,y,weight);

			ElectronEnergyHisto->Fill(E,weight);
			ElectronTimeHisto->Fill(t-MinTime,weight);
			ElectronTimeFromInteractionHisto->Fill(t,weight);

			SimInfo->Fill();
		}
		else if(currentId==CorsikaUtilities::ePDGMuon||currentId==CorsikaUtilities::ePDGAntiMuon){
			MuonLDFHisto->Fill(Rgrd,weight);
			MuonLDFInShowerPlaneHisto->Fill(Rplane,weight);

			MuonLDFDensityHisto->Fill(Rgrd,weight);
			MuonLDFDensityInShowerPlaneHisto->Fill(Rplane,weight);

			MuonEnergyHisto->Fill(E,weight);
			MuonTimeHisto->Fill(t-MinTime,weight);
			MuonTimeFromInteractionHisto->Fill(t,weight);

			SimInfo->Fill();
		}
		else continue;
  
  }//close for 

  //Divide number of particles for ring area 2 x pi x r dr	
  for(int i=0;i<ElectronLDFDensityHisto->GetNbinsX();i++){
	 double r= ElectronLDFDensityHisto->GetBinCenter(i+1);
	 double dr= ElectronLDFDensityHisto->GetBinWidth(i+1);
	 double Nr= ElectronLDFDensityHisto->GetBinContent(i+1);
	 double NrErr= ElectronLDFDensityHisto->GetBinError(i+1);
	 double Area= 2.*TMath::Pi()*r*dr;
	 //cout<<"r="<<r<<"  dr="<<dr<<"  Nr="<<Nr<<"  Area="<<Area<<endl;
	 ElectronLDFDensityHisto->SetBinContent(i+1,Nr/Area);
	 ElectronLDFDensityHisto->SetBinError(i+1,NrErr/Area);

	 r= ElectronLDFDensityInShowerPlaneHisto->GetBinCenter(i+1);
	 dr= ElectronLDFDensityInShowerPlaneHisto->GetBinWidth(i+1);
	 Nr= ElectronLDFDensityInShowerPlaneHisto->GetBinContent(i+1);
	 NrErr= ElectronLDFDensityInShowerPlaneHisto->GetBinError(i+1);
	 Area= 2.*TMath::Pi()*r*dr;
	 //cout<<"r="<<r<<"  dr="<<dr<<"  Nr="<<Nr<<"  Area="<<Area<<endl;
	 ElectronLDFDensityInShowerPlaneHisto->SetBinContent(i+1,Nr/Area);
	 ElectronLDFDensityInShowerPlaneHisto->SetBinError(i+1,NrErr/Area);
  }
  for(int i=0;i<MuonLDFDensityHisto->GetNbinsX();i++){
	 double r= MuonLDFDensityHisto->GetBinCenter(i+1);
	 double dr= MuonLDFDensityHisto->GetBinWidth(i+1);
	 double Nr= MuonLDFDensityHisto->GetBinContent(i+1);
	 double NrErr= MuonLDFDensityHisto->GetBinError(i+1);
	 double Area= 2.*TMath::Pi()*r*dr;
	 //cout<<"r="<<r<<"  dr="<<dr<<"  Nr="<<Nr<<"  Area="<<Area<<endl;
	 MuonLDFDensityHisto->SetBinContent(i+1,Nr/Area);
	 MuonLDFDensityHisto->SetBinError(i+1,NrErr/Area);

	 r= MuonLDFDensityInShowerPlaneHisto->GetBinCenter(i+1);
	 dr= MuonLDFDensityInShowerPlaneHisto->GetBinWidth(i+1);
	 Nr= MuonLDFDensityInShowerPlaneHisto->GetBinContent(i+1);
	 NrErr= MuonLDFDensityInShowerPlaneHisto->GetBinError(i+1);
	 Area= 2.*TMath::Pi()*r*dr;
	 //cout<<"r="<<r<<"  dr="<<dr<<"  Nr="<<Nr<<"  Area="<<Area<<endl;
	 MuonLDFDensityInShowerPlaneHisto->SetBinContent(i+1,Nr/Area);
	 MuonLDFDensityInShowerPlaneHisto->SetBinError(i+1,NrErr/Area);
  }


	double Xdepth[Ndepth],Ncharged[Ndepth],Nmuons[Ndepth],Nelectrons[Ndepth],Ngammas[Ndepth];
	for(int i=0;i<Ndepth;i++){
		Xdepth[i]= depth[i];
		Ncharged[i]= longCharged[i];
		Nmuons[i]= longMuons[i];
		Ngammas[i]= longGammas[i];
		Nelectrons[i]= longElectrons[i];
	}//close for


	TGraph* MuonLongProfile= new TGraph(Ndepth,Xdepth,Nmuons);
	MuonLongProfile->SetName("MuonLongProfile");
	MuonLongProfile->SetMarkerStyle(8);

	TGraph* ElectronLongProfile= new TGraph(Ndepth,Xdepth,Nelectrons);
	ElectronLongProfile->SetName("ElectronLongProfile");
  ElectronLongProfile->SetMarkerStyle(8);

	TGraph* ChargedLongProfile= new TGraph(Ndepth,Xdepth,Ncharged);
	ChargedLongProfile->SetName("ChargedLongProfile");
	ChargedLongProfile->SetMarkerStyle(8);

	TGraph* GammaLongProfile= new TGraph(Ndepth,Xdepth,Ngammas);
	GammaLongProfile->SetName("GammaLongProfile");
	GammaLongProfile->SetMarkerStyle(8);

	MuonLongProfile->Write();
	ElectronLongProfile->Write();
	GammaLongProfile->Write();
	ChargedLongProfile->Write();


  ElectronLDFHisto->Write();
  ElectronLDFDensityHisto->Write();
  ElectronLDFInShowerPlaneHisto->Write();
  ElectronLDFDensityInShowerPlaneHisto->Write();
	ElectronEnergyHisto->Write();
	ElectronTimeHisto->Write();
	ElectronTimeFromInteractionHisto->Write();

  MuonLDFHisto->Write();
  MuonLDFDensityHisto->Write();
  MuonLDFInShowerPlaneHisto->Write();
  MuonLDFDensityInShowerPlaneHisto->Write();
  EventMap->Write();
	MuonEnergyHisto->Write();
	MuonTimeHisto->Write();
	MuonTimeFromInteractionHisto->Write();
	SimInfo->SetName("SimInfo");
	SimInfo->Write();
  f->Close();

  cout<<"end main "<<endl;
*/
	
}//close ReadPartData()
