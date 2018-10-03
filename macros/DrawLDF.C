void DrawLDF() {

  
  gROOT->SetStyle("Plain");
  gStyle->SetOptLogy(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  //#####################
  //###  PROTON  ########
  //#####################
  TFile* fp_E18= new TFile("LDF_protonQGSJETII_Energy18_Zenith0.root");
  TH1D* ElectronLDF_E18_p=(TH1D*)fp_E18->Get("ElectronLDFDensityHisto");
  TH1D* MuonLDF_E18_p=(TH1D*)fp_E18->Get("MuonLDFDensityHisto");
  TGraph* ElectronProfile_E18_p=(TGraph*)fp_E18->Get("ChargedLongProfile");
  TGraph* MuonProfile_E18_p=(TGraph*)fp_E18->Get("MuonLongProfile");
  TH1D* ElectronEnergy_E18_p=(TH1D*)fp_E18->Get("ElectronEnergyHisto");
  TH1D* MuonEnergy_E18_p=(TH1D*)fp_E18->Get("MuonEnergyHisto");
  TH1D* ElectronTime_E18_p=(TH1D*)fp_E18->Get("ElectronTimeHisto");
  TH1D* MuonTime_E18_p=(TH1D*)fp_E18->Get("MuonTimeHisto");
  cout<<"get tree E18 p"<<endl;
  TTree* SimInfo_E18_p=(TTree*)fp_E18->Get("SimInfo");


  TFile* fp_E19= new TFile("LDF_protonQGSJETII_Energy19_Zenith0.root");
  TH1D* ElectronLDF_E19_p=(TH1D*)fp_E19->Get("ElectronLDFDensityHisto");
  TH1D* MuonLDF_E19_p=(TH1D*)fp_E19->Get("MuonLDFDensityHisto");
  TGraph* ElectronProfile_E19_p=(TGraph*)fp_E19->Get("ChargedLongProfile");
  TGraph* MuonProfile_E19_p=(TGraph*)fp_E19->Get("MuonLongProfile");
  TH1D* ElectronEnergy_E19_p=(TH1D*)fp_E19->Get("ElectronEnergyHisto");
  TH1D* MuonEnergy_E19_p=(TH1D*)fp_E19->Get("MuonEnergyHisto");
  TH1D* ElectronTime_E19_p=(TH1D*)fp_E19->Get("ElectronTimeHisto");
  TH1D* MuonTime_E19_p=(TH1D*)fp_E19->Get("MuonTimeHisto");
  //cout<<"get tree E19 p"<<endl;
  //TTree* SimInfo_E19_p=(TTree*)fp_E19->Get("SimInfo");

  //#####################
  //###  IRON  ########
  //#####################
  TFile* fFe_E18= new TFile("LDF_ironQGSJETII_Energy18_Zenith0.root");
  TH1D* ElectronLDF_E18_Fe=(TH1D*)fFe_E18->Get("ElectronLDFDensityHisto");
  TH1D* MuonLDF_E18_Fe=(TH1D*)fFe_E18->Get("MuonLDFDensityHisto");
  TGraph* ElectronProfile_E18_Fe=(TGraph*)fFe_E18->Get("ChargedLongProfile");
  TGraph* MuonProfile_E18_Fe=(TGraph*)fFe_E18->Get("MuonLongProfile");
  TH1D* ElectronEnergy_E18_Fe=(TH1D*)fFe_E18->Get("ElectronEnergyHisto");
  TH1D* MuonEnergy_E18_Fe=(TH1D*)fFe_E18->Get("MuonEnergyHisto");
  TH1D* ElectronTime_E18_Fe=(TH1D*)fFe_E18->Get("ElectronTimeHisto");
  TH1D* MuonTime_E18_Fe=(TH1D*)fFe_E18->Get("MuonTimeHisto");
  // TTree* SimInfo_E18_Fe=(TTree*)fFe_E18->Get("SimInfo");

  TFile* fFe_E19= new TFile("LDF_ironQGSJETII_Energy19_Zenith0.root");
  TH1D* ElectronLDF_E19_Fe=(TH1D*)fFe_E19->Get("ElectronLDFDensityHisto");
  TH1D* MuonLDF_E19_Fe=(TH1D*)fFe_E19->Get("MuonLDFDensityHisto");
  TGraph* ElectronProfile_E19_Fe=(TGraph*)fFe_E19->Get("ChargedLongProfile");
  TGraph* MuonProfile_E19_Fe=(TGraph*)fFe_E19->Get("MuonLongProfile");
  TH1D* ElectronEnergy_E19_Fe=(TH1D*)fFe_E19->Get("ElectronEnergyHisto");
  TH1D* MuonEnergy_E19_Fe=(TH1D*)fFe_E19->Get("MuonEnergyHisto");
  TH1D* ElectronTime_E19_Fe=(TH1D*)fFe_E19->Get("ElectronTimeHisto");
  TH1D* MuonTime_E19_Fe=(TH1D*)fFe_E19->Get("MuonTimeHisto");
  //TTree* SimInfo_E19_Fe=(TTree*)fFe_E19->Get("SimInfo");


  //#####################
  //###  OXYGEN  ########
  //#####################
  TFile* fOx_E18= new TFile("LDF_oxygenQGSJETII_Energy18_Zenith0.root");
  TH1D* ElectronLDF_E18_Ox=(TH1D*)fOx_E18->Get("ElectronLDFDensityHisto");
  TH1D* MuonLDF_E18_Ox=(TH1D*)fOx_E18->Get("MuonLDFDensityHisto");
  TGraph* ElectronProfile_E18_Ox=(TGraph*)fOx_E18->Get("ChargedLongProfile");
  TGraph* MuonProfile_E18_Ox=(TGraph*)fOx_E18->Get("MuonLongProfile");
  /*TH1D* ElectronEnergy_E18_Ox=(TH1D*)fOx_E18->Get("ElectronEnergyHisto");
  TH1D* MuonEnergy_E18_Ox=(TH1D*)fOx_E18->Get("MuonEnergyHisto");
  TH1D* ElectronTime_E18_Ox=(TH1D*)fOx_E18->Get("ElectronTimeHisto");
  TH1D* MuonTime_E18_Ox=(TH1D*)fOx_E18->Get("MuonTimeHisto");
  */
  TFile* fOx_E19= new TFile("LDF_oxygenQGSJETII_Energy19_Zenith0.root");
  TH1D* ElectronLDF_E19_Ox=(TH1D*)fOx_E19->Get("ElectronLDFDensityHisto");
  TH1D* MuonLDF_E19_Ox=(TH1D*)fOx_E19->Get("MuonLDFDensityHisto");
  TGraph* ElectronProfile_E19_Ox=(TGraph*)fOx_E19->Get("ChargedLongProfile");
  TGraph* MuonProfile_E19_Ox=(TGraph*)fOx_E19->Get("MuonLongProfile");
  /* TH1D* ElectronEnergy_E19_Ox=(TH1D*)fOx_E19->Get("ElectronEnergyHisto");
  TH1D* MuonEnergy_E19_Ox=(TH1D*)fOx_E19->Get("MuonEnergyHisto");
  TH1D* ElectronTime_E19_Ox=(TH1D*)fOx_E19->Get("ElectronTimeHisto");
  TH1D* MuonTime_E19_Ox=(TH1D*)fOx_E19->Get("MuonTimeHisto");
  */
  
  TCanvas* LDFPlot_E18=new TCanvas("LDFPlot_E18","LDFPlot_E18");
  LDFPlot_E18->cd();

  TH2D* back=new TH2D("back","",100,-10,6000,100,0.0001,1000000);
  back->GetXaxis()->SetTitle("r [m]");
  back->GetXaxis()->SetLabelSize(0.04);
  back->GetXaxis()->SetTitleSize(0.05);
  back->GetXaxis()->SetTitleOffset(0.8);
  back->GetYaxis()->SetTitle("density [m^{-2}]");
  back->GetYaxis()->SetTitleSize(0.05);
  back->GetYaxis()->SetLabelSize(0.04);
  back->Draw();
    

  ElectronLDF_E18_p->SetMarkerStyle(8);
  ElectronLDF_E18_p->SetMarkerColor(kRed);
  ElectronLDF_E18_p->SetMarkerSize(0.9);
  ElectronLDF_E18_p->SetLineColor(kRed);
  ElectronLDF_E18_p->Draw("E1p same");

  MuonLDF_E18_p->SetMarkerStyle(4);
  MuonLDF_E18_p->SetMarkerColor(kMagenta+2);
  MuonLDF_E18_p->SetMarkerSize(0.8);
  MuonLDF_E18_p->SetLineColor(kMagenta+2);
  MuonLDF_E18_p->Draw("E1p same");

  ElectronLDF_E18_Fe->SetMarkerStyle(22);
  ElectronLDF_E18_Fe->SetMarkerColor(kBlue);
  ElectronLDF_E18_Fe->SetMarkerSize(1.2);
  ElectronLDF_E18_Fe->SetLineColor(kBlue);
  ElectronLDF_E18_Fe->Draw("E1p same");

  MuonLDF_E18_Fe->SetMarkerStyle(26);
  MuonLDF_E18_Fe->SetMarkerColor(kBlue+2);
  MuonLDF_E18_Fe->SetMarkerSize(1.);
  MuonLDF_E18_Fe->SetLineColor(kBlue+2);
  MuonLDF_E18_Fe->Draw("E1p same");

  /*
  ElectronLDF_E18_Ox->SetMarkerStyle(29);
  ElectronLDF_E18_Ox->SetMarkerColor(kGreen);
  ElectronLDF_E18_Ox->SetMarkerSize(1);
  ElectronLDF_E18_Ox->SetLineColor(kGreen);
  ElectronLDF_E18_Ox->Draw("E1p same");

  MuonLDF_E18_Ox->SetMarkerStyle(30);
  MuonLDF_E18_Ox->SetMarkerColor(kGreen+2);
  MuonLDF_E18_Ox->SetMarkerSize(1);
  MuonLDF_E18_Ox->SetLineColor(kGreen+2);
  MuonLDF_E18_Ox->Draw("E1p same");
  */

  TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(ElectronLDF_E18_p,"e^{+}e^{-} - proton","p");
  legend->AddEntry(MuonLDF_E18_p,"#mu^{+}#mu^{-} - proton","p");
  legend->AddEntry(ElectronLDF_E18_Fe,"e^{+}e^{-} - iron","p");
  legend->AddEntry(MuonLDF_E18_Fe,"#mu^{+}#mu^{-} - iron","p");
  //legend->AddEntry(ElectronLDF_E18_Ox,"e^{+}e^{-} - oxygen","p");
  //legend->AddEntry(MuonLDF_E18_Ox,"#mu^{+}#mu^{-} - oxygen","p");
  legend->Draw("same");

  TCanvas* LDFPlot_E19=new TCanvas("LDFPlot_E19","LDFPlot_E19");
  LDFPlot_E19->cd();
  
  back->Draw();
    

  ElectronLDF_E19_p->SetMarkerStyle(8);
  ElectronLDF_E19_p->SetMarkerColor(kRed);
  ElectronLDF_E19_p->SetMarkerSize(0.9);
  ElectronLDF_E19_p->SetLineColor(kRed);
  ElectronLDF_E19_p->Draw("E1p same");

  MuonLDF_E19_p->SetMarkerStyle(4);
  MuonLDF_E19_p->SetMarkerColor(kMagenta+2);
  MuonLDF_E19_p->SetMarkerSize(0.8);
  MuonLDF_E19_p->SetLineColor(kMagenta+2);
  MuonLDF_E19_p->Draw("E1p same");

  ElectronLDF_E19_Fe->SetMarkerStyle(22);
  ElectronLDF_E19_Fe->SetMarkerColor(kBlue);
  ElectronLDF_E19_Fe->SetMarkerSize(1.2);
  ElectronLDF_E19_Fe->SetLineColor(kBlue);
  ElectronLDF_E19_Fe->Draw("E1p same");

  MuonLDF_E19_Fe->SetMarkerStyle(26);
  MuonLDF_E19_Fe->SetMarkerColor(kBlue+2);
  MuonLDF_E19_Fe->SetMarkerSize(1.);
  MuonLDF_E19_Fe->SetLineColor(kBlue+2);
  MuonLDF_E19_Fe->Draw("E1p same");

  /*
  ElectronLDF_E19_Ox->SetMarkerStyle(29);
  ElectronLDF_E19_Ox->SetMarkerColor(kGreen);
  ElectronLDF_E19_Ox->SetMarkerSize(1);
  ElectronLDF_E19_Ox->SetLineColor(kGreen);
  ElectronLDF_E19_Ox->Draw("E1p same");

  MuonLDF_E19_Ox->SetMarkerStyle(30);
  MuonLDF_E19_Ox->SetMarkerColor(kGreen+2);
  MuonLDF_E19_Ox->SetMarkerSize(1);
  MuonLDF_E19_Ox->SetLineColor(kGreen+2);
  MuonLDF_E19_Ox->Draw("E1p same");
  */

  TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(ElectronLDF_E19_p,"e^{+}e^{-} - proton","p");
  legend->AddEntry(MuonLDF_E19_p,"#mu^{+}#mu^{-} - proton","p");
  legend->AddEntry(ElectronLDF_E19_Fe,"e^{+}e^{-} - iron","p");
  legend->AddEntry(MuonLDF_E19_Fe,"#mu^{+}#mu^{-} - iron","p");
  //legend->AddEntry(ElectronLDF_E19_Ox,"e^{+}e^{-} - oxygen","p");
  //legend->AddEntry(MuonLDF_E19_Ox,"#mu^{+}#mu^{-} - oxygen","p");
  legend->Draw("same");


 

  TCanvas* LongProfilePlot_E18_charged=new TCanvas("LongProfilePlot_E18_charged","LongProfilePlot_E18_charged");
  LongProfilePlot_E18_charged->cd();

  gStyle->SetOptLogy(0);

  TH2D* back=new TH2D("back2","",100,0,930,100,0,1.e+9);
  back->GetXaxis()->SetTitle("X [g cm^{-2}]");
  back->GetXaxis()->SetLabelSize(0.04);
  back->GetXaxis()->SetTitleSize(0.05);
  back->GetXaxis()->SetTitleOffset(0.8);
  back->GetYaxis()->SetTitle("N(X)");
  back->GetYaxis()->SetTitleSize(0.05);
  back->GetYaxis()->SetLabelSize(0.04);
  back->Draw();

  TPaveLabel* label=new TPaveLabel(877.098823,80e+06,877.098823,115e+06,"OBS LEVEL");
  label->SetTextSize(0.7);
  label->SetFillColor(0);
  label->Draw("same");


  //OBS LEVEL 877.098823 g/cm^2
  TArrow* arrow=new TArrow(877.098823,22e+06,877.098823,80e+06,0.05,"|>");
  arrow->SetLineWidth(2);
  arrow->Draw("same");

  //gPad->RedrawAxis();

  ElectronProfile_E18_p->SetMarkerStyle(8);
  ElectronProfile_E18_p->SetMarkerColor(kRed);
  ElectronProfile_E18_p->SetMarkerSize(0.3);
  ElectronProfile_E18_p->SetLineColor(kRed);
  ElectronProfile_E18_p->Draw("Pl");

  ElectronProfile_E18_Fe->SetMarkerStyle(22);
  ElectronProfile_E18_Fe->SetMarkerColor(kBlue);
  ElectronProfile_E18_Fe->SetMarkerSize(0.4);
  ElectronProfile_E18_Fe->SetLineColor(kBlue);
  ElectronProfile_E18_Fe->Draw("Pl");

  TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(ElectronProfile_E18_p,"charged - proton","pl");
  legend->AddEntry(ElectronProfile_E18_Fe,"charged - iron","pl");
  legend->Draw("same");
  



  TCanvas* LongProfilePlot_E19_charged=new TCanvas("LongProfilePlot_E19_charged","LongProfilePlot_E19_charged");
  LongProfilePlot_E19_charged->cd();

  TH2D* back=new TH2D("back3","",100,0,930,100,0,1.e+10);
  back->GetXaxis()->SetTitle("X [g cm^{-2}]");
  back->GetXaxis()->SetLabelSize(0.04);
  back->GetXaxis()->SetTitleSize(0.05);
  back->GetXaxis()->SetTitleOffset(0.8);
  back->GetYaxis()->SetTitle("N(X)");
  back->GetYaxis()->SetTitleSize(0.05);
  back->GetYaxis()->SetLabelSize(0.04);
  back->Draw();
 
  TPaveLabel* label=new TPaveLabel(877.098823,80e+07,877.098823,115e+07,"OBS LEVEL");
  label->SetTextSize(0.7);
  label->SetFillColor(0);
  label->Draw("same");


  //OBS LEVEL 877.098823 g/cm^2
  TArrow* arrow=new TArrow(877.098823,22e+07,877.098823,80e+07,0.05,"|>");
  arrow->SetLineWidth(2);
  arrow->Draw("same");



  ElectronProfile_E19_p->SetMarkerStyle(8);
  ElectronProfile_E19_p->SetMarkerColor(kRed);
  ElectronProfile_E19_p->SetMarkerSize(0.3);
  ElectronProfile_E19_p->SetLineColor(kRed);
  ElectronProfile_E19_p->Draw("Pl");

  ElectronProfile_E19_Fe->SetMarkerStyle(22);
  ElectronProfile_E19_Fe->SetMarkerColor(kBlue);
  ElectronProfile_E19_Fe->SetMarkerSize(0.4);
  ElectronProfile_E19_Fe->SetLineColor(kBlue);
  ElectronProfile_E19_Fe->Draw("Pl");

  TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(ElectronProfile_E19_p,"charged - proton","pl");
  legend->AddEntry(ElectronProfile_E19_Fe,"charged - iron","pl");
  legend->Draw("same");


  TCanvas* LongProfilePlot_E18_muon=new TCanvas("LongProfilePlot_E18_muon","LongProfilePlot_E18_muon");
  LongProfilePlot_E18_muon->cd();

  TH2D* back=new TH2D("back4","",100,0,930,100,0,2.e+7);
  back->GetXaxis()->SetTitle("X [g cm^{-2}]");
  back->GetXaxis()->SetLabelSize(0.04);
  back->GetXaxis()->SetTitleSize(0.05);
  back->GetXaxis()->SetTitleOffset(0.8);
  back->GetYaxis()->SetTitle("N(X)");
  back->GetYaxis()->SetTitleSize(0.05);
  back->GetYaxis()->SetLabelSize(0.04);
  back->Draw();

  TPaveLabel* label=new TPaveLabel(877.098823,1.5e+06,877.098823,2.3e+06,"OBS LEVEL");
  label->SetTextSize(0.7);
  label->SetFillColor(0);
  label->Draw("same");


  //OBS LEVEL 877.098823 g/cm^2
  TArrow* arrow=new TArrow(877.098823,0.5e+06,877.098823,1.5e+06,0.05,"|>");
  arrow->SetLineWidth(2);
  arrow->Draw("same");



 


  MuonProfile_E18_p->SetMarkerStyle(4);
  MuonProfile_E18_p->SetMarkerColor(kMagenta+2);
  MuonProfile_E18_p->SetMarkerSize(0.2);
  MuonProfile_E18_p->SetLineColor(kMagenta+2);
  MuonProfile_E18_p->Draw("Pl");

  MuonProfile_E18_Fe->SetMarkerStyle(26);
  MuonProfile_E18_Fe->SetMarkerColor(kBlue+2);
  MuonProfile_E18_Fe->SetMarkerSize(0.2);
  MuonProfile_E18_Fe->SetLineColor(kBlue+2);
  MuonProfile_E18_Fe->Draw("Pl");

  TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(MuonProfile_E18_p,"#mu^{+}#mu^{-} - proton","pl");
  legend->AddEntry(MuonProfile_E18_Fe,"#mu^{+}#mu^{-} - iron","pl");
  legend->Draw("same");
  





   TCanvas* LongProfilePlot_E19_muon=new TCanvas("LongProfilePlot_E19_muon","LongProfilePlot_E19_muon");
  LongProfilePlot_E19_muon->cd();

  TH2D* back=new TH2D("back5","",100,0,930,100,0,1.e+8);
  back->GetXaxis()->SetTitle("X [g cm^{-2}]");
  back->GetXaxis()->SetLabelSize(0.04);
  back->GetXaxis()->SetTitleSize(0.05);
  back->GetXaxis()->SetTitleOffset(0.8);
  back->GetYaxis()->SetTitle("N(X)");
  back->GetYaxis()->SetTitleSize(0.05);
  back->GetYaxis()->SetLabelSize(0.04);
  back->Draw();

  TPaveLabel* label=new TPaveLabel(877.098823,6.5e+06,877.098823,10.e+06,"OBS LEVEL");
  label->SetTextSize(0.7);
  label->SetFillColor(0);
  label->Draw("same");


  //OBS LEVEL 877.098823 g/cm^2
  TArrow* arrow=new TArrow(877.098823,1.5e+06,877.098823,6.5e+06,0.05,"|>");
  arrow->SetLineWidth(2);
  arrow->Draw("same");


  MuonProfile_E19_p->SetMarkerStyle(4);
  MuonProfile_E19_p->SetMarkerColor(kMagenta+2);
  MuonProfile_E19_p->SetMarkerSize(0.2);
  MuonProfile_E19_p->SetLineColor(kMagenta+2);
  MuonProfile_E19_p->Draw("Pl");

  MuonProfile_E19_Fe->SetMarkerStyle(26);
  MuonProfile_E19_Fe->SetMarkerColor(kBlue+2);
  MuonProfile_E19_Fe->SetMarkerSize(0.2);
  MuonProfile_E19_Fe->SetLineColor(kBlue+2);
  MuonProfile_E19_Fe->Draw("Pl");

   TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(MuonProfile_E19_p,"#mu^{+}#mu^{-} - proton","pl");
  legend->AddEntry(MuonProfile_E19_Fe,"#mu^{+}#mu^{-} - iron","pl");
  legend->Draw("same");


  TCanvas* EnergySpectrumPlot_E18=new TCanvas("EnergySpectrumPlot_E18","EnergySpectrumPlot_E18");
  EnergySpectrumPlot_E18->cd();

  TH2D* back=new TH2D("back6","",100,0,100,100,10,1.e+9);
  back->GetXaxis()->SetTitle("Energy [GeV]");
  back->GetXaxis()->SetLabelSize(0.04);
  back->GetXaxis()->SetTitleSize(0.05);
  back->GetXaxis()->SetTitleOffset(0.8);
  back->GetYaxis()->SetTitle("entries");
  back->GetYaxis()->SetTitleSize(0.05);
  back->GetYaxis()->SetLabelSize(0.04);
  back->Draw();  

  ElectronEnergy_E18_p->SetMarkerStyle(8);
  ElectronEnergy_E18_p->SetMarkerColor(kRed);
  ElectronEnergy_E18_p->SetMarkerSize(0.9);
  ElectronEnergy_E18_p->SetLineColor(kRed);
  ElectronEnergy_E18_p->Draw("E1p same");

  MuonEnergy_E18_p->SetMarkerStyle(4);
  MuonEnergy_E18_p->SetMarkerColor(kMagenta+2);
  MuonEnergy_E18_p->SetMarkerSize(0.8);
  MuonEnergy_E18_p->SetLineColor(kMagenta+2);
  MuonEnergy_E18_p->Draw("E1p same");

  ElectronEnergy_E18_Fe->SetMarkerStyle(22);
  ElectronEnergy_E18_Fe->SetMarkerColor(kBlue);
  ElectronEnergy_E18_Fe->SetMarkerSize(1.2);
  ElectronEnergy_E18_Fe->SetLineColor(kBlue);
  ElectronEnergy_E18_Fe->Draw("E1p same");

  MuonEnergy_E18_Fe->SetMarkerStyle(26);
  MuonEnergy_E18_Fe->SetMarkerColor(kBlue+2);
  MuonEnergy_E18_Fe->SetMarkerSize(1.);
  MuonEnergy_E18_Fe->SetLineColor(kBlue+2);
  MuonEnergy_E18_Fe->Draw("E1p same");

  //gPad->RedrawAxis();

  TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(ElectronEnergy_E18_p,"e^{+}e^{-} - proton","p");
  legend->AddEntry(MuonEnergy_E18_p,"#mu^{+}#mu^{-} - proton","p");
  legend->AddEntry(ElectronEnergy_E18_Fe,"e^{+}e^{-} - iron","p");
  legend->AddEntry(MuonEnergy_E18_Fe,"#mu^{+}#mu^{-} - iron","p");
  legend->Draw("same");

   TCanvas* EnergySpectrumPlot_E19=new TCanvas("EnergySpectrumPlot_E19","EnergySpectrumPlot_E19");
  EnergySpectrumPlot_E19->cd();

  
  TH2D* back=new TH2D("back7","",100,0,100,100,1,1.e+9);
  back->GetXaxis()->SetTitle("Energy [GeV]");
  back->GetXaxis()->SetLabelSize(0.04);
  back->GetXaxis()->SetTitleSize(0.05);
  back->GetXaxis()->SetTitleOffset(0.8);
  back->GetYaxis()->SetTitle("entries");
  back->GetYaxis()->SetTitleSize(0.05);
  back->GetYaxis()->SetLabelSize(0.04);
  back->Draw();  
  

  ElectronEnergy_E19_p->SetMarkerStyle(8);
  ElectronEnergy_E19_p->SetMarkerColor(kRed);
  ElectronEnergy_E19_p->SetMarkerSize(0.9);
  ElectronEnergy_E19_p->SetLineColor(kRed);
  ElectronEnergy_E19_p->Draw("hist same");

  MuonEnergy_E19_p->SetMarkerStyle(4);
  MuonEnergy_E19_p->SetMarkerColor(kMagenta+2);
  MuonEnergy_E19_p->SetMarkerSize(0.8);
  MuonEnergy_E19_p->SetLineColor(kMagenta+2);
  MuonEnergy_E19_p->Draw("hist same");

  ElectronEnergy_E19_Fe->SetMarkerStyle(22);
  ElectronEnergy_E19_Fe->SetMarkerColor(kBlue);
  ElectronEnergy_E19_Fe->SetMarkerSize(1.2);
  ElectronEnergy_E19_Fe->SetLineColor(kBlue);
  ElectronEnergy_E19_Fe->Draw("hist same");

  MuonEnergy_E19_Fe->SetMarkerStyle(26);
  MuonEnergy_E19_Fe->SetMarkerColor(kBlue+2);
  MuonEnergy_E19_Fe->SetMarkerSize(1.);
  MuonEnergy_E19_Fe->SetLineColor(kBlue+2);
  MuonEnergy_E19_Fe->Draw("hist same");

   TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(ElectronEnergy_E19_p,"e^{+}e^{-} - proton","l");
  legend->AddEntry(MuonEnergy_E19_p,"#mu^{+}#mu^{-} - proton","l");
  legend->AddEntry(ElectronEnergy_E19_Fe,"e^{+}e^{-} - iron","l");
  legend->AddEntry(MuonEnergy_E19_Fe,"#mu^{+}#mu^{-} - iron","l");
  legend->Draw("same");


   TCanvas* TimeSpectrumPlot_E18=new TCanvas("TimeSpectrumPlot_E18","TimeSpectrumPlot_E18");
  TimeSpectrumPlot_E18->cd();

  TH2D* back=new TH2D("back8","",100,0,30000,100,10,1.e+10);
  back->GetXaxis()->SetTitle("#Delta t [ns]");
  back->GetXaxis()->SetLabelSize(0.04);
  back->GetXaxis()->SetTitleSize(0.05);
  back->GetXaxis()->SetTitleOffset(0.8);
  back->GetYaxis()->SetTitle("entries");
  back->GetYaxis()->SetTitleSize(0.05);
  back->GetYaxis()->SetLabelSize(0.04);
  back->Draw();  

  ElectronTime_E18_p->SetMarkerStyle(8);
  ElectronTime_E18_p->SetMarkerColor(kRed);
  ElectronTime_E18_p->SetMarkerSize(0.9);
  ElectronTime_E18_p->SetLineColor(kRed);
  ElectronTime_E18_p->Draw("E1p same");

  MuonTime_E18_p->SetMarkerStyle(4);
  MuonTime_E18_p->SetMarkerColor(kMagenta+2);
  MuonTime_E18_p->SetMarkerSize(0.8);
  MuonTime_E18_p->SetLineColor(kMagenta+2);
  MuonTime_E18_p->Draw("E1p same");

  ElectronTime_E18_Fe->SetMarkerStyle(22);
  ElectronTime_E18_Fe->SetMarkerColor(kBlue);
  ElectronTime_E18_Fe->SetMarkerSize(1.2);
  ElectronTime_E18_Fe->SetLineColor(kBlue);
  ElectronTime_E18_Fe->Draw("E1p same");

  MuonTime_E18_Fe->SetMarkerStyle(26);
  MuonTime_E18_Fe->SetMarkerColor(kBlue+2);
  MuonTime_E18_Fe->SetMarkerSize(1.);
  MuonTime_E18_Fe->SetLineColor(kBlue+2);
  MuonTime_E18_Fe->Draw("E1p same");

  TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(ElectronTime_E18_p,"e^{+}e^{-} - proton","p");
  legend->AddEntry(MuonTime_E18_p,"#mu^{+}#mu^{-} - proton","p");
  legend->AddEntry(ElectronTime_E18_Fe,"e^{+}e^{-} - iron","p");
  legend->AddEntry(MuonTime_E18_Fe,"#mu^{+}#mu^{-} - iron","p");
  legend->Draw("same");

   TCanvas* TimeSpectrumPlot_E19=new TCanvas("TimeSpectrumPlot_E19","TimeSpectrumPlot_E19");
  TimeSpectrumPlot_E19->cd();

  TH2D* back=new TH2D("back9","",100,0,30000,100,10,1.e+10);
  back->GetXaxis()->SetTitle("#Delta t [ns]");
  back->GetXaxis()->SetLabelSize(0.04);
  back->GetXaxis()->SetTitleSize(0.05);
  back->GetXaxis()->SetTitleOffset(0.8);
  back->GetYaxis()->SetTitle("entries");
  back->GetYaxis()->SetTitleSize(0.05);
  back->GetYaxis()->SetLabelSize(0.04);
  back->Draw();  

  ElectronTime_E19_p->SetMarkerStyle(8);
  ElectronTime_E19_p->SetMarkerColor(kRed);
  ElectronTime_E19_p->SetMarkerSize(0.9);
  ElectronTime_E19_p->SetLineColor(kRed);
  ElectronTime_E19_p->Draw("E1p same");

  MuonTime_E19_p->SetMarkerStyle(4);
  MuonTime_E19_p->SetMarkerColor(kMagenta+2);
  MuonTime_E19_p->SetMarkerSize(0.8);
  MuonTime_E19_p->SetLineColor(kMagenta+2);
  MuonTime_E19_p->Draw("E1p same");

  ElectronTime_E19_Fe->SetMarkerStyle(22);
  ElectronTime_E19_Fe->SetMarkerColor(kBlue);
  ElectronTime_E19_Fe->SetMarkerSize(1.2);
  ElectronTime_E19_Fe->SetLineColor(kBlue);
  ElectronTime_E19_Fe->Draw("E1p same");

  MuonTime_E19_Fe->SetMarkerStyle(26);
  MuonTime_E19_Fe->SetMarkerColor(kBlue+2);
  MuonTime_E19_Fe->SetMarkerSize(1.);
  MuonTime_E19_Fe->SetLineColor(kBlue+2);
  MuonTime_E19_Fe->Draw("E1p same");

  TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(ElectronTime_E19_p,"e^{+}e^{-} - proton","p");
  legend->AddEntry(MuonTime_E19_p,"#mu^{+}#mu^{-} - proton","p");
  legend->AddEntry(ElectronTime_E19_Fe,"e^{+}e^{-} - iron","p");
  legend->AddEntry(MuonTime_E19_Fe,"#mu^{+}#mu^{-} - iron","p");
  legend->Draw("same");

  cout<<"End function "<<endl;

  
  double x,y,Rgrd,Rplane,px,py,pz,E,t,weight;
  int type;

  SimInfo_E18_p->SetBranchAddress("x",&x);
  SimInfo_E18_p->SetBranchAddress("y",&y);
  SimInfo_E18_p->SetBranchAddress("px",&px); 
  SimInfo_E18_p->SetBranchAddress("py",&py);
  SimInfo_E18_p->SetBranchAddress("pz",&pz); 
  SimInfo_E18_p->SetBranchAddress("Rgrd",&Rgrd);
  SimInfo_E18_p->SetBranchAddress("Rplane",&Rplane);
  SimInfo_E18_p->SetBranchAddress("E",&E); 
  SimInfo_E18_p->SetBranchAddress("t",&t);
  SimInfo_E18_p->SetBranchAddress("weight",&weight);
  SimInfo_E18_p->SetBranchAddress("type",&type);

  TH1D* ElectronTimeSpectrum_closecore=new TH1D("ElectronTimeSpectrum_closecore","",100,78,85);
  ElectronTimeSpectrum_closecore->Sumw2();
  TH1D* ElectronTimeSpectrum_farcore=new TH1D("ElectronTimeSpectrum_farcore","",100,78,85);
  ElectronTimeSpectrum_farcore->Sumw2();

  TH1D* MuonTimeSpectrum_closecore=new TH1D("MuonTimeSpectrum_closecore","",100,78,85);
  MuonTimeSpectrum_closecore->Sumw2();
  TH1D* MuonTimeSpectrum_farcore=new TH1D("MuonTimeSpectrum_farcore","",100,78,85);
  MuonTimeSpectrum_farcore->Sumw2();


  for(int i=0;i<SimInfo_E18_p->GetEntries();i++){
    SimInfo_E18_p->GetEntry(i);
    if(Rgrd>=100&&Rgrd<=200){

      if(type==13||type==-13){
	MuonTimeSpectrum_closecore->Fill(t/1000.,weight);
      }
      if(type==11||type==-11){
	ElectronTimeSpectrum_closecore->Fill(t/1000.,weight);
      }      

    }//close if

    if(Rgrd>=1000&&Rgrd<=2000){
      if(type==13||type==-13){
	//cout<<"t="<<t<<endl;
	MuonTimeSpectrum_farcore->Fill(t/1000.,weight);
      }
      if(type==11||type==-11){
	ElectronTimeSpectrum_farcore->Fill(t/1000.,weight);
      } 
    }//close if

  }//close for

  cout<<"**entries**"<<endl;
  cout<<"ElectronTimeSpectrum_closecore ==> "<<ElectronTimeSpectrum_closecore->GetEntries()<<"  mean="<<ElectronTimeSpectrum_closecore->GetMean()<<"  rms="<<ElectronTimeSpectrum_closecore->GetRMS()<<endl;
  cout<<"ElectronTimeSpectrum_farcore ==> "<<ElectronTimeSpectrum_farcore->GetEntries()<<"  mean="<<ElectronTimeSpectrum_farcore->GetMean()<<"  rms="<<ElectronTimeSpectrum_farcore->GetRMS()<<endl;
  cout<<"MuonTimeSpectrum_closecore ==> "<<MuonTimeSpectrum_closecore->GetEntries()<<"  mean="<<MuonTimeSpectrum_closecore->GetMean()<<"  rms="<<MuonTimeSpectrum_closecore->GetRMS()<<endl;
  cout<<"MuonTimeSpectrum_farcore ==> "<<MuonTimeSpectrum_farcore->GetEntries()<<"  mean="<<MuonTimeSpectrum_farcore->GetMean()<<"  rms="<<MuonTimeSpectrum_farcore->GetRMS()<<endl;




  TCanvas* TimeSpectrumPlot_E18_vsdist=new TCanvas("TimeSpectrumPlot_E18_vsdist","TimeSpectrumPlot_E18_vsdist");
  TimeSpectrumPlot_E18_vsdist->cd();
  
  TH2D* back=new TH2D("back10","",100,78,85,100,0.0001,1);
  back->GetXaxis()->SetTitle("t [#mu s]");
  back->GetXaxis()->SetLabelSize(0.04);
  back->GetXaxis()->SetTitleSize(0.05);
  back->GetXaxis()->SetTitleOffset(0.8);
  back->GetYaxis()->SetTitle("entries");
  back->GetYaxis()->SetTitleSize(0.05);
  back->GetYaxis()->SetLabelSize(0.04);
  back->Draw();  
  
  ElectronTimeSpectrum_closecore->SetMarkerStyle(8);
  ElectronTimeSpectrum_closecore->SetMarkerColor(kRed);
  ElectronTimeSpectrum_closecore->SetMarkerSize(0.9);
  ElectronTimeSpectrum_closecore->SetLineColor(kRed);
  ElectronTimeSpectrum_closecore->DrawNormalized("hist same");

  MuonTimeSpectrum_closecore->SetMarkerStyle(4);
  MuonTimeSpectrum_closecore->SetMarkerColor(kMagenta+2);
  MuonTimeSpectrum_closecore->SetMarkerSize(0.8);
  MuonTimeSpectrum_closecore->SetLineColor(kMagenta+2);
  MuonTimeSpectrum_closecore->SetLineStyle(2);
  MuonTimeSpectrum_closecore->DrawNormalized("hist same");

  ElectronTimeSpectrum_farcore->SetMarkerStyle(22);
  ElectronTimeSpectrum_farcore->SetMarkerColor(kBlue);
  ElectronTimeSpectrum_farcore->SetMarkerSize(0.9);
  ElectronTimeSpectrum_farcore->SetLineColor(kBlue);
  ElectronTimeSpectrum_farcore->SetLineStyle(3);
  ElectronTimeSpectrum_farcore->DrawNormalized("hist same");

  MuonTimeSpectrum_farcore->SetMarkerStyle(26);
  MuonTimeSpectrum_farcore->SetMarkerColor(kBlue+2);
  MuonTimeSpectrum_farcore->SetMarkerSize(0.8);
  MuonTimeSpectrum_farcore->SetLineColor(kBlue+2);
  MuonTimeSpectrum_farcore->SetLineStyle(4);
  MuonTimeSpectrum_farcore->DrawNormalized("hist same");
  
  TLegend* legend = new TLegend(0.6,0.5,0.7,0.6,"","brNDC");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.025);
  legend->AddEntry(ElectronTimeSpectrum_closecore,"e^{+}e^{-} - 100-200 m","l");
  legend->AddEntry(MuonTimeSpectrum_closecore,"#mu^{+}#mu^{-} - 100-200 m","l");
  legend->AddEntry(ElectronTimeSpectrum_farcore,"e^{+}e^{-} - 1000-2000 m","l");
  legend->AddEntry(MuonTimeSpectrum_farcore,"#mu^{+}#mu^{-} - 1000-2000 m","l");
  legend->Draw("same");


}//close function
