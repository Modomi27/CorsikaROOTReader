void MakePlots(){

  double ObsLevel[3]={0.,2900.,9500.};
  
  /*
  double Ne[3]={376,1156,17359};
  double Netot[3]={758,2216,35226};

  double Nmu[3]={1460,2072,3728};
  double Nmutot[3]={2923,4113,7381};

  double Ngamma[3]={3235,10663,166501};
  double Ngammatot[3]={6227,20979,338442};

  double Np[3]={6,67,674};
  double Nptot[3]={16,138,1383};

  double Nn[3]={27,251,1841};
  double Nntot[3]={63,494,3826};
  */

  double Netot[3];
  double Nmutot[3];
  double Ngammatot[3];
  double Nptot[3];
  double Nntot[3];

  double NetotRUN1[3]={1411,5928,131499};
  double NmutotRUN1[3]={5164,9048,31919};
  double NgammatotRUN1[3]={11963,56757,1221790};
  double NptotRUN1[3]={61,740,24280};
  double NntotRUN1[3]={409,4146,77341};

  double NetotRUN2[3]={1410,6050,131261};
  double NmutotRUN2[3]={5310,9050,32021};
  double NgammatotRUN2[3]={12019,56884,1222810};
  double NptotRUN2[3]={54,725,23762};
  double NntotRUN2[3]={383,3981,76954};

  
  for(int i=0;i<3;i++){
    Netot[i]=NetotRUN1[i]+NetotRUN2[i];
    Nmutot[i]=NmutotRUN1[i]+NmutotRUN2[i];
    Ngammatot[i]=NgammatotRUN1[i]+NgammatotRUN2[i];
    Nptot[i]=NptotRUN1[i]+NptotRUN2[i];
    Nntot[i]=NntotRUN1[i]+NntotRUN2[i];
  }


  TCanvas* Plot=new TCanvas("Plot","");
  Plot->cd();
  Plot->SetBorderMode(0);
  Plot->SetFrameFillColor(0);
  Plot->SetFillColor(0);
  Plot->SetFrameBorderMode(0);
  gStyle->SetOptStat(1110);
  gStyle->SetOptTitle(0);
  gStyle->SetOptLogy(1);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);

  TGraph* Gamma=new TGraph(3,ObsLevel,Ngammatot);
  Gamma->SetMarkerStyle(8);
  Gamma->SetMarkerColor(kGreen);
  Gamma->SetLineColor(kGreen);
  Gamma->Draw("APl");

  TGraph* Electron=new TGraph(3,ObsLevel,Netot);
  Electron->SetMarkerStyle(8);
  Electron->SetMarkerColor(kRed);
  Electron->SetLineColor(kRed);
  Electron->Draw("Pl");

  TGraph* Muon=new TGraph(3,ObsLevel,Nmutot);
  Muon->SetMarkerStyle(8);
  Muon->SetMarkerColor(kBlue);
  Muon->SetLineColor(kBlue);
  Muon->Draw("Pl");

  TGraph* Proton=new TGraph(3,ObsLevel,Nptot);
  Proton->SetMarkerStyle(8);
  Proton->SetMarkerColor(kOrange);
  Proton->SetLineColor(kOrange);
  Proton->Draw("Pl");

  TGraph* Neutron=new TGraph(3,ObsLevel,Nntot);
  Neutron->SetMarkerStyle(8);
  Neutron->SetMarkerColor(kBlack);
  Neutron->SetLineColor(kBlack);
  Neutron->Draw("Pl");


  TLegend* legenda = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legenda->SetFillColor(0);
  legenda->SetTextSize(0.03);
  legenda->AddEntry(Electron,"e+ e-","l");
  legenda->AddEntry(Muon,"mu+ mu-","l");
  legenda->AddEntry(Gamma,"gamma","l");
  legenda->AddEntry(Proton,"p","l");
  legenda->AddEntry(Neutron,"n","l");
  legenda->Draw("same");
}
