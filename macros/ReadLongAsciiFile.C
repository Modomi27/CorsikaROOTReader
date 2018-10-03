void ReadLongAsciiFile(char* filename=""){

  
  FILE* f;
  f=fopen(filename,"r");
  

  //ifstream f(filename);


  char LineMunnizza[10000]; 
  char Line[3000];  // or appropriate
  char* buffer;

  const int Ndepths=52;

  float Depth[Ndepths];
  float Gamma[Ndepths],Positrons[Ndepths],Electrons[Ndepths],MuPlus[Ndepths],Mu[Ndepths],Hadrons[Ndepths],Charged[Ndepths],Nuclei[Ndepths],Cherenkov[Ndepths]; 

  float GammaTot[Ndepths],PositronsTot[Ndepths],ElectronsTot[Ndepths],MuPlusTot[Ndepths],MuTot[Ndepths],HadronsTot[Ndepths],ChargedTot[Ndepths],NucleiTot[Ndepths],CherenkovTot[Ndepths];

  float AllElectronsTot[Ndepths],AllMuonsTot[Ndepths];

  for(int i=0;i<Ndepths;i++){
    GammaTot[i]=0.;
    PositronsTot[i]=0.;
    ElectronsTot[i]=0.;
     AllElectronsTot[i]=0.;
     AllMuonsTot[i]=0.;
    MuPlusTot[i]=0.;
    MuTot[i]=0.;
    HadronsTot[i]=0.;
    ChargedTot[i]=0.;
    NucleiTot[i]=0.;
    CherenkovTot[i]=0.;
  }

  TString currentCanvasName;
  TCanvas* ElectronPlot;
  TCanvas* PositronPlot;
  TCanvas* MuonPlot;
  TCanvas* MuonPlusPlot;
  TCanvas* HadronPlot;
  
  TCanvas* ElectronTotPlot;
  TCanvas* PositronTotPlot;
  TCanvas* MuonTotPlot;
  TCanvas* MuonPlusTotPlot;
  TCanvas* HadronTotPlot;
  TCanvas* ChargedTotPlot;
  TCanvas* NucleiTotPlot;
  TCanvas* TotPlot;

  TGraph* ElectronProfile;
  TGraph* PositronProfile;
  TGraph* MuonProfile;
  TGraph* MuonPlusProfile;
  TGraph* HadronProfile;

  TGraph* GammaTotProfile;
  TGraph* AllElectronTotProfile;
  TGraph* ElectronTotProfile;
  TGraph* PositronTotProfile;
  TGraph* AllMuonTotProfile;
  TGraph* MuonTotProfile;
  TGraph* MuonPlusTotProfile;
  TGraph* HadronTotProfile;
  TGraph* ChargedTotProfile;
  TGraph* NucleiTotProfile;

  
  GammaTotPlot=new TCanvas("GammaTotPlot","GammaTotPlot");
  AllElectronTotPlot=new TCanvas("AllElectronTotPlot","AllElectronTotPlot");
  ElectronTotPlot=new TCanvas("ElectronTotPlot","ElectronTotPlot");
  PositronTotPlot=new TCanvas("PositronTotPlot","PositronTotPlot");
  AllMuonTotPlot=new TCanvas("AllMuonTotPlot","AllMuonTotPlot");
  MuonTotPlot=new TCanvas("MuonTotPlot","MuonTotPlot");
  MuonPlusTotPlot=new TCanvas("MuonPlusTotPlot","MuonPlusTotPlot");
  HadronTotPlot=new TCanvas("HadronTotPlot","HadronTotPlot");
  ChargedTotPlot=new TCanvas("ChargedTotPlot","ChargedTotPlot");
  NucleiTotPlot=new TCanvas("NucleiTotPlot","NucleiTotPlot");

  TotPlot=new TCanvas("TotPlot","TotPlot");

  TFile* fout=new TFile("ProfileFigure.root","RECREATE");
  
  
  for(int i=0;i<1000;i++){
    
    cout<<"EVT==> "<<i+1<<endl;

    /*
    currentCanvasName=Form("ElectronPlot_%d",i+1);
    ElectronPlot=new TCanvas(currentCanvasName,currentCanvasName);
    
    currentCanvasName=Form("PositronPlot_%d",i+1);
    PositronPlot=new TCanvas(currentCanvasName,currentCanvasName);

    currentCanvasName=Form("MuonPlot_%d",i+1);
    MuonPlot=new TCanvas(currentCanvasName,currentCanvasName);

    currentCanvasName=Form("MuonPlusPlot_%d",i+1);
    MuonPlusPlot=new TCanvas(currentCanvasName,currentCanvasName);

    currentCanvasName=Form("HadronPlot_%d",i+1);
    HadronPlot=new TCanvas(currentCanvasName,currentCanvasName);
    */
   
    

    for(int j=0;j<2;j++){
      fgets(Line,3000,f); 
      sscanf(Line,"%[^\n]\n",LineMunnizza);
      //f.getline(Line,3000);

      //cout<<"Line "<<Line<<endl;
    }
    
  
    for(int j=0;j<Ndepths;j++){
      fscanf(f,"%f %f %f %f %f %f %f %f %f %f\n",&Depth[j],&Gamma[j],&Positrons[j],&Electrons[j],&MuPlus[j],&Mu[j],&Hadrons[j],&Charged[j],&Nuclei[j],&Cherenkov[j]);
      //f>>Depth>>Gamma>>Positrons>>Electrons>>MuPlus>>Mu>>Hadrons>>Charged>>Nuclei>>Cherenkov;
      //cout<<"INFO ==> "<<Depth[j]<<"  "<<Gamma[j]<<"  "<<Positrons[j]<<"  "<<Electrons[j]<<"  "<<MuPlus[j]<<"  "<<Mu[j]<<"  "<<Hadrons[j]<<"  "<<Charged[j]<<"  "<<Nuclei[j]<<"  "<<Cherenkov[j]<<endl;

      GammaTot[j]=GammaTot[j]+Gamma[j];
      ElectronsTot[j]=ElectronsTot[j]+Electrons[j];
      PositronsTot[j]=PositronsTot[j]+Positrons[j];
      MuPlusTot[j]=MuPlusTot[j]+MuPlus[j];
      MuTot[j]=MuTot[j]+Mu[j];
      HadronsTot[j]=HadronsTot[j]+Hadrons[j];
      ChargedTot[j]=ChargedTot[j]+Charged[j];
      NucleiTot[j]=NucleiTot[j]+Nuclei[j];

      AllElectronsTot[j]=AllElectronsTot[j]+ElectronsTot[j]+PositronsTot[j];
      AllMuonsTot[j]=AllMuonsTot[j]+MuPlusTot[j]+MuTot[j];

    }

    /*
    ElectronPlot->cd();
    ElectronProfile=new TGraph(Ndepths,Depth,Electrons);
    ElectronProfile->SetMarkerStyle(8);    
    if(i==0) ElectronProfile->Draw("AP");
    else ElectronProfile->Draw("AP");


    PositronPlot->cd();
    PositronProfile=new TGraph(Ndepths,Depth,Positrons);
    PositronProfile->SetMarkerStyle(8);  
    if(i==0) PositronProfile->Draw("AP");
    else PositronProfile->Draw("AP");

    MuonPlot->cd();
    MuonProfile=new TGraph(Ndepths,Depth,Mu);
    MuonProfile->SetMarkerStyle(8);  
    if(i==0) MuonProfile->Draw("AP");
    else MuonProfile->Draw("AP");

    MuonPlusPlot->cd();
    MuonPlusProfile=new TGraph(Ndepths,Depth,MuPlus);
    MuonPlusProfile->SetMarkerStyle(8);  
    if(i==0) MuonPlusProfile->Draw("AP");
    else MuonPlusProfile->Draw("AP");

    HadronPlot->cd();
    HadronProfile=new TGraph(Ndepths,Depth,Hadrons);
    HadronProfile->SetMarkerStyle(8);  
    if(i==0) HadronProfile->Draw("AP");
    else HadronProfile->Draw("AP");
    */
    
    for(int j=0;j<60;j++){
      fgets(Line,3000,f); 
      sscanf(Line,"%[^\n]\n",LineMunnizza);
      //cout<<"Line "<<Line<<endl;
      
      //f.getline(Line,3000);
    }

    /*
    ElectronPlot->Write();
    PositronPlot->Write();
    MuonPlot->Write();
    MuonPlusPlot->Write();
    HadronPlot->Write();
    */
  
  }


  GammaTotPlot->cd();
  GammaTotProfile=new TGraph(Ndepths,Depth,GammaTot);
  GammaTotProfile->SetMarkerStyle(8);    
  GammaTotProfile->Draw("AP");
  GammaTotPlot->Write();
   
  AllElectronTotPlot->cd();
  AllElectronTotProfile=new TGraph(Ndepths,Depth,AllElectronsTot);
  AllElectronTotProfile->SetMarkerStyle(8);    
  AllElectronTotProfile->Draw("AP");
  AllElectronTotPlot->Write();

  ElectronTotPlot->cd();
  ElectronTotProfile=new TGraph(Ndepths,Depth,ElectronsTot);
  ElectronTotProfile->SetMarkerStyle(8);    
  ElectronTotProfile->Draw("AP");
  ElectronTotPlot->Write();

  PositronTotPlot->cd();
  PositronTotProfile=new TGraph(Ndepths,Depth,PositronsTot);
  PositronTotProfile->SetMarkerStyle(8);  
  PositronTotProfile->Draw("AP");
  PositronTotPlot->Write();

  AllMuonTotPlot->cd();
  AllMuonTotProfile=new TGraph(Ndepths,Depth,AllMuonsTot);
  AllMuonTotProfile->SetMarkerStyle(8);  
  AllMuonTotProfile->Draw("AP");
  AllMuonTotPlot->Write();
  

  MuonTotPlot->cd();
  MuonTotProfile=new TGraph(Ndepths,Depth,MuTot);
  MuonTotProfile->SetMarkerStyle(8);  
  MuonTotProfile->Draw("AP");
  MuonTotPlot->Write();

  MuonPlusTotPlot->cd();
  MuonPlusTotProfile=new TGraph(Ndepths,Depth,MuPlusTot);
  MuonPlusTotProfile->SetMarkerStyle(8);  
  MuonPlusTotProfile->Draw("AP");
  MuonPlusTotPlot->Write();

  HadronTotPlot->cd();
  HadronTotProfile=new TGraph(Ndepths,Depth,HadronsTot);
  HadronTotProfile->SetMarkerStyle(8);  
  HadronTotProfile->Draw("AP");
  HadronTotPlot->Write();

  ChargedTotPlot->cd();
  ChargedTotProfile=new TGraph(Ndepths,Depth,ChargedTot);
  ChargedTotProfile->SetMarkerStyle(8);  
  ChargedTotProfile->Draw("AP");
  ChargedTotPlot->Write();

  NucleiTotPlot->cd();
  NucleiTotProfile=new TGraph(Ndepths,Depth,NucleiTot);
  NucleiTotProfile->SetMarkerStyle(8);  
  NucleiTotProfile->Draw("AP");
  NucleiTotPlot->Write();

  TotPlot->cd();
  gStyle->SetOptStat(1);
  gStyle->SetOptTitle(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  TotPlot->SetFillColor(0);
  TotPlot->SetGridx(1);
  TotPlot->SetGridy(1);
  

  AllElectronTotProfile->SetMarkerStyle(8);    
  AllElectronTotProfile->SetMarkerColor(kRed);    
  AllElectronTotProfile->Draw("AP");
  /*
  ElectronTotProfile->SetMarkerStyle(8);    
  ElectronTotProfile->SetMarkerColor(kRed);    
  ElectronTotProfile->Draw("AP");
  PositronTotProfile->SetMarkerStyle(8);    
  PositronTotProfile->SetMarkerColor(kRed+2);    
  PositronTotProfile->Draw("P");
  */
  
  AllMuonTotProfile->SetMarkerStyle(8);  
  AllMuonTotProfile->SetMarkerColor(kBlue);  
  AllMuonTotProfile->Draw("P");
  /*
  MuonTotProfile->SetMarkerStyle(8);  
  MuonTotProfile->SetMarkerColor(kBlue);  
  MuonTotProfile->Draw("P");
  MuonPlusTotProfile->SetMarkerStyle(8);  
  MuonPlusTotProfile->SetMarkerColor(kBlue+2);  
  MuonPlusTotProfile->Draw("P");
  */
  HadronTotProfile->SetMarkerStyle(8); 
  HadronTotProfile->SetMarkerColor(kCyan); 
  HadronTotProfile->Draw("P");
  GammaTotProfile->SetMarkerStyle(8); 
  GammaTotProfile->SetMarkerColor(kGreen); 
  GammaTotProfile->Draw("P");
  ChargedTotProfile->SetMarkerStyle(8); 
  ChargedTotProfile->SetMarkerColor(kOrange); 
  ChargedTotProfile->Draw("P");
  NucleiTotProfile->SetMarkerStyle(8); 
  NucleiTotProfile->SetMarkerColor(kMagenta); 
  NucleiTotProfile->Draw("P");

  TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetTextSize(0.03);
  legend->AddEntry(AllElectronTotProfile,"e+ e-","p");
  /*
  legend->AddEntry(ElectronTotProfile,"e-","p");
  legend->AddEntry(PositronTotProfile,"e+","p");
  */
  
  legend->AddEntry(AllMuonTotProfile,"mu+ mu-","p");
  /*
  legend->AddEntry(MuonTotProfile,"mu-","p");
  legend->AddEntry(MuonPlusTotProfile,"mu+","p");
  */
  legend->AddEntry(HadronTotProfile,"hadrons","p");
  legend->AddEntry(GammaTotProfile,"gamma","p");
  legend->AddEntry(ChargedTotProfile,"charged","p");
  legend->AddEntry(NucleiTotProfile,"nuclei","p");
  legend->Draw("same");

  fclose(f);

}//close macro
