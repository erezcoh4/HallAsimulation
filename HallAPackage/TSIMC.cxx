#ifndef TSIMC_CXX
#define TSIMC_CXX

#include "TSIMC.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TSIMC::TSIMC(int fN, int * fFileNumbers , int fcolors[] , char ** fNames){
    SetCuts();
    N = fN;
    NFilesStr = "";
    for ( int i = 0 ; i < N ; i++ ) {
        
        FileNumbers[i]  = fFileNumbers[i];
        ana.push_back(TAnalysisSIMC(FileNumbers[i]));
        Names.push_back(fNames[i]);
        colors.push_back(fcolors[i]);
        NFilesStr += Form("_%d",FileNumbers[i]);
       
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::SetCuts(){
    okCut   = "ok_spec==1 ";
    YtagCut = " (-5 < hsytar) && (hsytar < 5)" ;
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::DrawQuantity(TString Var, int Nbins,
                         double Xlow, double Xup,
                         TString Title, TString Units,
                         bool DoAddLegend, bool DoAddCuts, double cutXlow, double cutXup){
    TCut cut = YtagCut && okCut;
    vector      <float> frac;
    TString     Labels[sizeof(FileNumbers)/sizeof(int)];
    float       Maximum = 0;
    TH1F        * h[sizeof(FileNumbers)/sizeof(int)];
    TString     XTitle = (Units!=""&&Units!="e-4") ? Title + " [" + Units + "]" : Title;
    
    for ( int i = 0 ; i < N ; i++ ) {
        
        h[i]    = ana[i].H1(Var,cut,(i==0)?"HIST e":"same HIST e",Nbins ,Xlow ,Xup,Title,XTitle,"",colors[i]);
        Maximum = (h[i] -> GetMaximum() > Maximum) ? h[i] -> GetMaximum() : Maximum;
        
    }
    
    int BaseLineEntries = h[0] -> GetEntries();
    for ( int i = 0 ; i < N ; i++ ) {
        frac.push_back((float)h[i]->GetEntries()/BaseLineEntries);
        Labels[i] = (Names.empty()) ? Form("file %d [%.0f%%]",FileNumbers[i],100.*frac[i])
        : Form("%s [%.0f%%]",Names[i].Data(),100.*frac[i]);
        h[i] -> GetYaxis() -> SetRangeUser(0,1.1*Maximum);
    }
    
    if (DoAddCuts) {
        ana[0].Line(cutXlow,0,cutXlow,1.1*Maximum,2,2);
        ana[0].Line(cutXup,0,cutXup,1.1*Maximum,2,2);
    }
    
    if (DoAddLegend){
        ana[0].AddLegend(N,h,Labels,"f");
    }
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::DrawQuantity2D(TString VarX, TString VarY,
                           int NbinsX,double Xlow, double Xup,
                           int NbinsY,double Ylow, double Yup,
                           TString XTitle, TString XUnits, TString YTitle, TString YUnits,
                           bool DoAddLegend, bool DoAddCuts,
                           double cutXlow, double cutXup,
                           double cutYlow, double cutYup){
    TCut cut = YtagCut && okCut;
    vector      <float> frac;
    TString     Labels[sizeof(FileNumbers)/sizeof(int)];
    float       Maximum = 0;
    TH2F        * h2[sizeof(FileNumbers)/sizeof(int)];
    TString Title   = XTitle + " vs. " + YTitle;
    XTitle = (XUnits=="") ? XTitle : (XTitle + " [" + XUnits + "] ") ;
    YTitle = (YUnits=="") ? YTitle : (YTitle + " [" + YUnits + "] ") ;
    
    for ( int i = 0 ; i < N ; i++ ) {
        
        h2[i]   = ana[i].H2(VarX, VarY,cut,(i==0)?"":"same",NbinsX ,Xlow ,Xup,NbinsY ,Ylow ,Yup ,Title ,XTitle ,YTitle ,colors[i], 20, 0.9 , 1);
    }
    
    int BaseLineEntries = h2[0] -> GetEntries();
    for ( int i = 0 ; i < N ; i++ ) {
        frac.push_back((float)h2[i]->GetEntries()/BaseLineEntries);
        Labels[i] = (Names.empty()) ? Form("file %d [%.0f%%]",FileNumbers[i],100.*frac[i])
        : Form("%s [%.0f%%]",Names[i].Data(),100.*frac[i]);
    }
    
    if (DoAddCuts) {
        ana[0].Box(cutXlow,cutYlow,cutXup,cutYup,2,2);
    }
    
    if (DoAddLegend){
        ana[0].AddLegend(N,h2,Labels,"p");
    }
}










//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::DrawResolution(TString Var, int Nbins,double Xlow, double Xup, float MulFac
                           , TString Title, TString Units , bool DoAddLegend){
    TCut cut = YtagCut && okCut;
    vector      <float> frac;
    TString     Labels[sizeof(FileNumbers)/sizeof(int)];
    float       Maximum = 0;
    TH1F        * h[sizeof(FileNumbers)/sizeof(int)];
    Units       = (MulFac==1e6) ? "u"+Units : ( (MulFac==1e4) ? "e-4"+Units :  ((MulFac==1e3) ? "m"+Units : Units));
    TString     XTitle = (Units!=""&&Units!="e-4") ? Title + " [" + Units + "]" : Title;

    
    for ( int i = 0 ; i < N ; i++ ) {
        
        ana.push_back(TAnalysisSIMC(FileNumbers[i]));
        h[i]    = ana[i].Resolution1D(Var,cut,(i==0)?"HIST e":"same HIST e",Nbins ,Xlow ,Xup,Title,XTitle,colors[i]);
        Maximum = (h[i] -> GetMaximum() > Maximum) ? h[i] -> GetMaximum() : Maximum;
        
    }
    
    int BaseLineEntries = h[0] -> GetEntries();
    
    for ( int i = 0 ; i < N ; i++ ) {
        
        frac.push_back((float)h[i]->GetEntries()/BaseLineEntries);
        Labels[i] = (Names.empty()) ? Form("file %d [%.0f%%]",FileNumbers[i],100.*frac[i])
        : Form("%s [%.0f%%]",Names[i].Data(),100.*frac[i]);
        TString txt = Form("RMS=%.2f(%.0f) %s" ,MulFac*h[i]->GetRMS(),100*MulFac*h[i]->GetRMSError(),Units.Data());
        ana[i].Text(h[i]->GetMean()+0.1*h[i]->GetRMS(), Maximum*(1-0.1*i) ,txt , colors[i]);
        h[i] -> GetYaxis() -> SetRangeUser(0,1.1*Maximum);
        
    }
    
    if (DoAddLegend){
        ana[0].AddLegend(N,h,Labels,"f");
    }
}










//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::MergeFiles(){
    // look for difference in resolution of Var between Files 1...N
    TCut cut = YtagCut && okCut;
    TFile * MergedFile = new TFile(ana[0].GetPath()+"/data/Merged"+NFilesStr+".root","recreate");
    cout << MergedFile->GetName() << endl;
    TTree * MergedTree = new TTree("h1","Merged"+NFilesStr);
    
    
    Float_t hsyptari    , hsxptari  , hsdeltai  , hsytari;
    Float_t hsyptar     , hsxptar   , hsdelta   , hsytar , ok_spec;
    Int_t   entry     ;
    
    for (int i = 0 ; i < N ; i++) {
        
        MergedTree -> Branch(Form("hsyptari_%d",FileNumbers[i])      ,&hsyptari  , Form("hsyptari_%d/F",FileNumbers[i]));
        MergedTree -> Branch(Form("hsxptari_%d",FileNumbers[i])      ,&hsxptari  , Form("hsxptari_%d/F",FileNumbers[i]));
        MergedTree -> Branch(Form("hsdeltai_%d",FileNumbers[i])      ,&hsdeltai  , Form("hsdeltai_%d/F",FileNumbers[i]));
        MergedTree -> Branch(Form("hsytari_%d",FileNumbers[i])       ,&hsytari   , Form("hsytari_%d/F",FileNumbers[i]));
        MergedTree -> Branch(Form("hsyptar_%d",FileNumbers[i])       ,&hsyptar   , Form("hsyptar_%d/F",FileNumbers[i]));
        MergedTree -> Branch(Form("hsxptar_%d",FileNumbers[i])       ,&hsxptar   , Form("hsxptar_%d/F",FileNumbers[i]));
        MergedTree -> Branch(Form("hsdelta_%d",FileNumbers[i])       ,&hsdelta   , Form("hsdelta_%d/F",FileNumbers[i]));
        MergedTree -> Branch(Form("hsytar_%d",FileNumbers[i])        ,&hsytar    , Form("hsytar_%d/F",FileNumbers[i]));
        MergedTree -> Branch(Form("ok_spec_%d",FileNumbers[i])       ,&ok_spec   , Form("ok_spec_%d/F",FileNumbers[i]));
        MergedTree -> Branch("ok_spec"                               ,&ok_spec   , "ok_spec/F");
        MergedTree -> Branch(Form("entry_%d",FileNumbers[i])         ,&entry     , Form("entry_%d/I",FileNumbers[i]));

        
        TTree * TmpTree = ana[i].GetTree();
        
        TmpTree -> SetBranchAddress("hsyptari"          , &hsyptari);
        TmpTree -> SetBranchAddress("hsxptari"          , &hsxptari);
        TmpTree -> SetBranchAddress("hsdeltai"          , &hsdeltai);
        TmpTree -> SetBranchAddress("hsytari"           , &hsytari);
        TmpTree -> SetBranchAddress("hsyptar"           , &hsyptar);
        TmpTree -> SetBranchAddress("hsxptar"           , &hsxptar);
        TmpTree -> SetBranchAddress("hsdelta"           , &hsdelta);
        TmpTree -> SetBranchAddress("hsytar"            , &hsytar);
        TmpTree -> SetBranchAddress("ok_spec"           , &ok_spec);
        
        
        for (entry = 0; entry < TmpTree->GetEntries() ; entry++) {
            TmpTree     -> GetEntry();
            MergedTree  -> Fill();
            if (entry%(100000) == 0) {
                Printf("[%.0f%%] of file %d",100*((float)entry/ana[i].GetEntries()),FileNumbers[i]);
            }
        }
        
        delete TmpTree;
    }
    
    MergedTree -> Write();
    MergedFile -> Close();

}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::CompareVariable(TString Var, TString cut,
                            int fNum1, int fNum2,
                            int Nbins, double Xlow, double Xup,
                            TString Title, TString Units){
    TAnalysisSIMC anaMerged("Merged"+NFilesStr);
    TString XTitle = Form("%s (%d) - %s (%d)",Var.Data(),fNum1,Var.Data(),fNum2);
    XTitle += (Units!="") ? " [" + Units + "]" : "";
    TCut compareCut = Form("entry_%d == entry_%d",fNum1,fNum2);
    anaMerged.H1(Form("%s_%d - %s_%d",Var.Data(),fNum1,Var.Data(),fNum2),Form("%s",cut.Data()) && compareCut,"HIST e",Nbins ,Xlow ,Xup,Title,XTitle);
}




#endif
