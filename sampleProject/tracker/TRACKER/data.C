#include <fstream>
#include <iostream>

void data(TString dirPath="./", TString fileName="data.root"){

  TFile* file = new TFile(dirPath + fileName, "READ");
  Int_t numOfHist = file->GetNkeys();

  for(Int_t i = 0; i < numOfHist; i++){
      TH1D* hist = (TH1D*)file->Get(Form("%d", i+1));
      TString title = hist->GetTitle();
      const char* xUnit = hist->GetXaxis()->GetTitle();

      TCanvas* canvas = new TCanvas(Form("canvas%d", i+1), title, 1200, 800);
      canvas->cd();
      hist->Draw("HIST");
      hist->SetXTitle(Form("Energy%s", xUnit));
      hist->SetYTitle("Count");
      canvas->SaveAs("./" + title + ".jpg");
  }
}