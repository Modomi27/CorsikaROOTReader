enum ParticleType { 
	eMuon = 13, 
	eAntiMuon = -13, 
	eElectron = 11, 
	ePositron = -11, 
	eGamma= 22, 
	eProton= 2212, 
	eNeutron= 2112
};

void ReadCorsikaROOT(char* filename=""){

	TFile* inputFile= new TFile(filename,"READ");
	if(!inputFile || inputFile->IsZombie() || !inputFile->IsOpen() ){
		cerr<<"ERROR: Cannot open input file...exit!"<<endl;
		exit(1);
	}

	double ShowerEnergy;
	double ShowerTheta;
	double ShowerPhi;
	int nParticles;
	const int MAXPARTATGROUND= 1000000;
	int ParticleId[MAXPARTATGROUND];
	double KinEnergy[MAXPARTATGROUND];
	double Px[MAXPARTATGROUND];
	double Py[MAXPARTATGROUND];
	double Pz[MAXPARTATGROUND];
	double X[MAXPARTATGROUND];
	double Y[MAXPARTATGROUND];
	double Theta[MAXPARTATGROUND];
	double Phi[MAXPARTATGROUND];

	TTree* data= (TTree*)inputFile->Get("data");
	if(!data){
		cerr<<"ERROR: Cannot get data tree from input file...exit!"<<endl;
		exit(1);
	}
	data->SetBranchAddress("ShowerEnergy",&ShowerEnergy);//log10(PrimaryEnergy[eV])
	data->SetBranchAddress("ShowerTheta",&ShowerTheta);//PrimaryTheta [deg]
	data->SetBranchAddress("ShowerPhi",&ShowerPhi);//Primary Phi [deg]
	data->SetBranchAddress("nParticles",&nParticles);//n Particles at ground for this shower
	data->SetBranchAddress("ParticleId",ParticleId);//particle id: 1=gamma, 2=e+, 3=e-, 5=mu+, 6=mu-
	data->SetBranchAddress("KinEnergy",KinEnergy);//KinEnergy in GeV
	data->SetBranchAddress("Px",Px);//Px in GeV
	data->SetBranchAddress("Py",Py);//Py in GeV
	data->SetBranchAddress("Pz",Pz);//Pz in GeV
	data->SetBranchAddress("X",X);//X particle vertex in m
	data->SetBranchAddress("Y",Y);//Y particle vertex in m
	data->SetBranchAddress("Theta",Theta);//particle theta in degree
	data->SetBranchAddress("Phi",Phi);//particle phi in degree

	
	//## Histograms
	//mu-
	TH1D* muonEnergy= new TH1D("muonEnergy","muonEnergy",100,-3,3);
	muonEnergy->Sumw2();
	TH1D* muonTheta= new TH1D("muonTheta","muonTheta",100,0,180);	
	muonTheta->Sumw2();
	TH1D* muonPhi= new TH1D("muonPhi","muonPhi",100,0,180);
	muonPhi->Sumw2();
	TH1D* muonX= new TH1D("muonX","muonX",100,-1,1);
	muonX->Sumw2();
	TH1D* muonY= new TH1D("muonY","muonY",100,-1,1);
	muonY->Sumw2();
	
	//mu+
	TH1D* antimuonEnergy= new TH1D("antimuonEnergy","antimuonEnergy",100,-3,3);
	antimuonEnergy->Sumw2();
	TH1D* antimuonTheta= new TH1D("antimuonTheta","antimuonTheta",100,0,180);	
	antimuonTheta->Sumw2();
	TH1D* antimuonPhi= new TH1D("antimuonPhi","antimuonPhi",100,0,180);
	antimuonPhi->Sumw2();
	TH1D* antimuonX= new TH1D("antimuonX","antimuonX",100,-1,1);
	antimuonX->Sumw2();
	TH1D* antimuonY= new TH1D("antimuonY","antimuonY",100,-1,1);
	antimuonY->Sumw2();
	
	//e-
	TH1D* electronEnergy= new TH1D("electronEnergy","electronEnergy",100,-3,3);
	electronEnergy->Sumw2();
	TH1D* electronTheta= new TH1D("electronTheta","electronTheta",100,0,180);
	electronTheta->Sumw2();
	TH1D* electronPhi= new TH1D("electronPhi","electronPhi",100,0,180);
	electronPhi->Sumw2();
	TH1D* electronX= new TH1D("electronX","electronX",100,-1,1);
	electronX->Sumw2();
	TH1D* electronY= new TH1D("electronY","electronY",100,-1,1);
	electronY->Sumw2();
	
	//e+
	TH1D* positronEnergy= new TH1D("positronEnergy","positronEnergy",100,-3,3);
	positronEnergy->Sumw2();
	TH1D* positronTheta= new TH1D("positronTheta","positronTheta",100,0,180);
	positronTheta->Sumw2();
	TH1D* positronPhi= new TH1D("positronPhi","positronPhi",100,0,180);
	positronPhi->Sumw2();
	TH1D* positronX= new TH1D("positronX","positronX",100,-1,1);
	positronX->Sumw2();
	TH1D* positronY= new TH1D("positronY","positronY",100,-1,1);
	positronY->Sumw2();
	
	//gamma
	TH1D* gammaEnergy= new TH1D("gammaEnergy","gammaEnergy",100,-3,3);
	gammaEnergy->Sumw2();
	TH1D* gammaTheta= new TH1D("gammaTheta","gammaTheta",100,0,180);
	gammaTheta->Sumw2();
	TH1D* gammaPhi= new TH1D("gammaPhi","gammaPhi",100,0,180);
	gammaPhi->Sumw2();
	TH1D* gammaX= new TH1D("gammaX","gammaX",100,-1,1);
	gammaX->Sumw2();
	TH1D* gammaY= new TH1D("gammaY","gammaY",100,-1,1);
	gammaY->Sumw2();
	
	//p
	TH1D* protonEnergy= new TH1D("protonEnergy","protonEnergy",100,-3,3);
	protonEnergy->Sumw2();
	TH1D* protonTheta= new TH1D("protonTheta","protonTheta",100,0,180);
	protonTheta->Sumw2();
	TH1D* protonPhi= new TH1D("protonPhi","protonPhi",100,0,180);
	protonPhi->Sumw2();
	TH1D* protonX= new TH1D("protonX","protonX",100,-1,1);
	protonX->Sumw2();
	TH1D* protonY= new TH1D("protonY","protonY",100,-1,1);
	protonY->Sumw2();
	
	//n
	TH1D* neutronEnergy= new TH1D("neutronEnergy","neutronEnergy",100,-3,3);
	neutronEnergy->Sumw2();
	TH1D* neutronTheta= new TH1D("neutronTheta","neutronTheta",100,0,180);
	neutronTheta->Sumw2();
	TH1D* neutronPhi= new TH1D("neutronPhi","neutronPhi",100,0,180);
	neutronPhi->Sumw2();
	TH1D* neutronX= new TH1D("neutronX","neutronX",100,-1,1);
	neutronX->Sumw2();
	TH1D* neutronY= new TH1D("neutronY","neutronY",100,-1,1);
	neutronY->Sumw2();
	
	TH2D* MuonDistrHisto= new TH2D("MuonDistrHisto","MuonDistrHisto",100,0,180,100,-3,3);
	TH2D* EmDistrHisto= new TH2D("EmDistrHisto","EmDistrHisto",100,0,180,100,-2,3);


	//## Loop over events
	int nEntries= data->GetEntries();
	for(int i=0;i<nEntries;i++){
		data->GetEntry(i);

		
		//cout<<"SHOWER INFO: lgE="<<ShowerEnergy<<"  Theta="<<ShowerTheta<<endl;
		
		//## Loop over particles at ground for current shower	
		//cout<<"--> PART INFO: "<<nParticles<<" particles at ground"<<endl;
		for(int j=0;j<nParticles;j++){
			int id= ParticleId[j];
			int particleType= id;
			double lgE_part= log10(KinEnergy[j]);
			double Theta_part= Theta[j];
			double Phi_part= Phi[j];
			double X_part= X[j];
			double Y_part= Y[j];

			//cout<<"id="<<id<<"  E="<<KinEnergy[j]<<"  Theta="<<Theta[j]<<"  (X,Y)=("<<X[j]<<","<<Y[j]<<")"<<endl;

			if(particleType == eMuon){
				muonEnergy->Fill(lgE_part);	
				muonTheta->Fill(Theta_part);	
				muonPhi->Fill(Phi_part);	
				muonX->Fill(X_part);	
				muonY->Fill(Y_part);	
				MuonDistrHisto->Fill(Theta_part,lgE_part);
			}	
			else if(particleType == eAntiMuon){
				antimuonEnergy->Fill(lgE_part);	
				antimuonTheta->Fill(Theta_part);	
				antimuonPhi->Fill(Phi_part);	
				antimuonX->Fill(X_part);	
				antimuonY->Fill(Y_part);
				MuonDistrHisto->Fill(Theta_part,lgE_part);			
			}	
			else if(particleType == eElectron){
				electronEnergy->Fill(lgE_part);	
				electronTheta->Fill(Theta_part);	
				electronPhi->Fill(Phi_part);	
				electronX->Fill(X_part);	
				electronY->Fill(Y_part);			
				EmDistrHisto->Fill(Theta_part,lgE_part);			
			}
			else if(particleType == ePositron){
				positronEnergy->Fill(lgE_part);	
				positronTheta->Fill(Theta_part);	
				positronPhi->Fill(Phi_part);	
				positronX->Fill(X_part);	
				positronY->Fill(Y_part);	
				EmDistrHisto->Fill(Theta_part,lgE_part);		
			}
			else if(particleType == eGamma){
				gammaEnergy->Fill(lgE_part);	
				gammaTheta->Fill(Theta_part);	
				gammaPhi->Fill(Phi_part);	
				gammaX->Fill(X_part);	
				gammaY->Fill(Y_part);	
				EmDistrHisto->Fill(Theta_part,lgE_part);		
			}
			else if(particleType == eProton){
				protonEnergy->Fill(lgE_part);	
				protonTheta->Fill(Theta_part);	
				protonPhi->Fill(Phi_part);	
				protonX->Fill(X_part);	
				protonY->Fill(Y_part);			
			}
			else if(particleType == eNeutron){
				neutronEnergy->Fill(lgE_part);	
				neutronTheta->Fill(Theta_part);	
				neutronPhi->Fill(Phi_part);	
				neutronX->Fill(X_part);	
				neutronY->Fill(Y_part);			
			}

		}//end loop particles in shower

		//cout<<endl;
	}//end loop events

	TFile* OutputFile= new TFile("ProcessedOutputFile.root","RECREATE");
	OutputFile->cd();

	muonEnergy->Write();
	muonTheta->Write();
	muonPhi->Write();
	muonX->Write();
	muonY->Write();
	
	antimuonEnergy->Write();
	antimuonTheta->Write();
	antimuonPhi->Write();
	antimuonX->Write();
	antimuonY->Write();

	electronEnergy->Write();
	electronTheta->Write();
	electronPhi->Write();
	electronX->Write();
	electronY->Write();
	
	positronEnergy->Write();
	positronTheta->Write();
	positronPhi->Write();
	positronX->Write();
	positronY->Write();

	gammaEnergy->Write();
	gammaTheta->Write();
	gammaPhi->Write();
	gammaX->Write();
	gammaY->Write();
	
	protonEnergy->Write();
	protonTheta->Write();
	protonPhi->Write();
	protonX->Write();
	protonY->Write();

	neutronEnergy->Write();
	neutronTheta->Write();
	neutronPhi->Write();
	neutronX->Write();
	neutronY->Write();
	
	TCanvas* MuonDistrPlot= new TCanvas("MuonDistrPlot","MuonDistrPlot");
	MuonDistrPlot->cd();
	MuonDistrHisto->GetXaxis()->SetTitle("Theta [deg]");
	MuonDistrHisto->GetYaxis()->SetTitle("log_{10}[E/GeV]");
	MuonDistrHisto->Draw("LEGO");
	MuonDistrHisto->Write();

	TCanvas* EmDistrPlot= new TCanvas("EmDistrPlot","EmDistrPlot");
	EmDistrPlot->cd();
	EmDistrHisto->GetXaxis()->SetTitle("Theta [deg]");
	EmDistrHisto->GetYaxis()->SetTitle("log_{10}[E/GeV]");
	EmDistrHisto->Draw("LEGO");
	EmDistrHisto->Write();

	OutputFile->Close();

}//close macro
