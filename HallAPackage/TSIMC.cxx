#ifndef TSIMC_CXX
#define TSIMC_CXX

#include "TSIMC.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TSIMC::TSIMC(const int fN, int fFileNumbers[fN] , int fcolors[fN]  , char ** fNames){
    SetCuts();
    N = fN;
    NFilesStr = "";

    for ( int i = 0 ; i < N ; i++ ) {

        FileNumbers.push_back(fFileNumbers[i]);
        ana[i] = new TAnalysisSIMC(FileNumbers[i]);//(FileNumbers[i]);
        Names.push_back(Form("%s",fNames[i]));
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
        
        h[i]    = ana[i]->H1(Var,cut,(i==0)?"HIST e":"same HIST e",Nbins ,Xlow ,Xup,Title,XTitle,"",colors[i]);
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
        ana[0]->Line(cutXlow,0,cutXlow,1.1*Maximum,2,2);
        ana[0]->Line(cutXup,0,cutXup,1.1*Maximum,2,2);
    }
    
    if (DoAddLegend){
        ana[0]->AddLegend(N,h,Labels,"f");
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
        
        h2[i]   = ana[i]->H2(VarX, VarY,cut,(i==0)?"":"same",NbinsX ,Xlow ,Xup,NbinsY ,Ylow ,Yup ,Title ,XTitle ,YTitle ,colors[i], 20, 0.9 , 1);
    }
    
    int BaseLineEntries = h2[0] -> GetEntries();
    for ( int i = 0 ; i < N ; i++ ) {
        frac.push_back((float)h2[i]->GetEntries()/BaseLineEntries);
        Labels[i] = (Names.empty()) ? Form("file %d [%.0f%%]",FileNumbers[i],100.*frac[i])
        : Form("%s [%.0f%%]",Names[i].Data(),100.*frac[i]);
    }
    
    if (DoAddCuts) {
        ana[0]->Box(cutXlow,cutYlow,cutXup,cutYup,2,2);
    }
    
    if (DoAddLegend){
        ana[0]->AddLegend(N,h2,Labels,"p");
    }
}







//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::DrawRes(TString Var, int Nbins,double Xlow, double Xup , TString Title, TString Units , bool DoAddLegend){
    TCut cut = YtagCut && okCut;
    vector      <float> frac;
    float       Maximum = 0;
    TString     Labels[sizeof(FileNumbers)/sizeof(int)];
    TH1F        * h[sizeof(FileNumbers)/sizeof(int)];
    TString     XTitle = (Units!="") ? Title + " [" + Units + "]" : Title;
    
    
    for ( int i = 0 ; i < N ; i++ ) {
        
        h[i]    = ana[i] -> Res(Var,cut,(i==0)?"HIST e":"same HIST e",Nbins ,Xlow ,Xup,Title,XTitle,colors[i]);
        Maximum = (h[i] -> GetMaximum() > Maximum) ? h[i] -> GetMaximum() : Maximum;
 
    }
    
    int BaseLineEntries = h[0] -> GetEntries();
    for ( int i = 0 ; i < N ; i++ ) {
        
        frac.push_back((float)h[i]->GetEntries()/BaseLineEntries);
        h[i] -> GetYaxis() -> SetRangeUser(0,1.1*Maximum);
        Labels[i] = (Names.empty()) ? Form("file %d [%.0f%%]",FileNumbers[i],100.*frac[i])
        : Form("%s [%.0f%%]",Names[i].Data(),100.*frac[i]);
        
    }
    
    if (DoAddLegend){
        ana[0]->AddLegend(N,h,Labels,"f");
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
        
        h[i]    = ana[i]->Resolution1D(Var,cut,(i==0)?"HIST e":"same HIST e",Nbins ,Xlow ,Xup,Title,XTitle,colors[i]);
        Maximum = (h[i] -> GetMaximum() > Maximum) ? h[i] -> GetMaximum() : Maximum;
        
    }
    
    int BaseLineEntries = h[0] -> GetEntries();
    
    for ( int i = 0 ; i < N ; i++ ) {
        
        frac.push_back((float)h[i]->GetEntries()/BaseLineEntries);
        Labels[i] = (Names.empty()) ? Form("file %d [%.0f%%]",FileNumbers[i],100.*frac[i])
        : Form("%s [%.0f%%]",Names[i].Data(),100.*frac[i]);
        TString txt = Form("RMS=%.2f(%.0f) %s" ,MulFac*h[i]->GetRMS(),100*MulFac*h[i]->GetRMSError(),Units.Data());
        ana[i]->Text(h[i]->GetMean()+0.1*h[i]->GetRMS(), Maximum*(1-0.1*i) ,txt , colors[i]);
        h[i] -> GetYaxis() -> SetRangeUser(0,1.1*Maximum);
        
    }
    
    if (DoAddLegend){
        ana[0]->AddLegend(N,h,Labels,"f");
    }
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::MergeFiles( int i1, int i2){
    // merge Files i1 and i2
    TAnalysisSIMC * ana1 = new TAnalysisSIMC(i1);
    TAnalysisSIMC * ana2 = new TAnalysisSIMC(i2);
    NFilesStr = Form("_%d_%d",i1,i2);
    TFile * MergedFile = new TFile(ana1->GetPath()+"/data/Merged"+NFilesStr+".root","recreate");
    TTree * MergedTree = new TTree("h1","Merged"+NFilesStr);
    TTree * T1 = ana1->GetTree() , * T2 = ana2->GetTree();
    
    Float_t hsyptari_1  , hsxptari_1    , hsdeltai_1    , hsytari_1 ,   ok_spec_1;
    Float_t hsyptari_2  , hsxptari_2    , hsdeltai_2    , hsytari_2 ,   ok_spec_2;
    Float_t hsyptar_1   , hsxptar_1     , hsdelta_1     , hsytar_1;
    Float_t hsyptar_2   , hsxptar_2     , hsdelta_2     , hsytar_2;
    Int_t   entry       ;
    
    
    
    MergedTree -> Branch("entry"                    ,&entry         , "entry/I");
    
    T1 -> SetBranchAddress("hsyptari"               , &hsyptari_1);
    T1 -> SetBranchAddress("hsxptari"               , &hsxptari_1);
    T1 -> SetBranchAddress("hsdeltai"               , &hsdeltai_1);
    T1 -> SetBranchAddress("hsytari"                , &hsytari_1);
    T1 -> SetBranchAddress("hsyptar"                , &hsyptar_1);
    T1 -> SetBranchAddress("hsxptar"                , &hsxptar_1);
    T1 -> SetBranchAddress("hsdelta"                , &hsdelta_1);
    T1 -> SetBranchAddress("hsytar"                 , &hsytar_1);
    T1 -> SetBranchAddress("ok_spec"                , &ok_spec_1);
    MergedTree -> Branch(Form("hsyptari_%d",i1)     ,&hsyptari_1    , Form("hsyptari_%d/F",i1));
    MergedTree -> Branch(Form("hsxptari_%d",i1)     ,&hsxptari_1    , Form("hsxptari_%d/F",i1));
    MergedTree -> Branch(Form("hsdeltai_%d",i1)     ,&hsdeltai_1    , Form("hsdeltai_%d/F",i1));
    MergedTree -> Branch(Form("hsytari_%d",i1)      ,&hsytari_1     , Form("hsytari_%d/F",i1));
    MergedTree -> Branch(Form("hsyptar_%d",i1)      ,&hsyptar_1     , Form("hsyptar_%d/F",i1));
    MergedTree -> Branch(Form("hsxptar_%d",i1)      ,&hsxptar_1     , Form("hsxptar_%d/F",i1));
    MergedTree -> Branch(Form("hsdelta_%d",i1)      ,&hsdelta_1     , Form("hsdelta_%d/F",i1));
    MergedTree -> Branch(Form("hsytar_%d",i1)       ,&hsytar_1      , Form("hsytar_%d/F",i1));
    MergedTree -> Branch(Form("ok_spec_%d",i1)      ,&ok_spec_1     , Form("ok_spec_%d/F",i1));
    
    T2 -> SetBranchAddress("hsyptari"               , &hsyptari_2);
    T2 -> SetBranchAddress("hsxptari"               , &hsxptari_2);
    T2 -> SetBranchAddress("hsdeltai"               , &hsdeltai_2);
    T2 -> SetBranchAddress("hsytari"                , &hsytari_2);
    T2 -> SetBranchAddress("hsyptar"                , &hsyptar_2);
    T2 -> SetBranchAddress("hsxptar"                , &hsxptar_2);
    T2 -> SetBranchAddress("hsdelta"                , &hsdelta_2);
    T2 -> SetBranchAddress("hsytar"                 , &hsytar_2);
    T2 -> SetBranchAddress("ok_spec"                , &ok_spec_2);
    MergedTree -> Branch(Form("hsyptari_%d",i2)     ,&hsyptari_2    , Form("hsyptari_%d/F",i2));
    MergedTree -> Branch(Form("hsxptari_%d",i2)     ,&hsxptari_2    , Form("hsxptari_%d/F",i2));
    MergedTree -> Branch(Form("hsdeltai_%d",i2)     ,&hsdeltai_2    , Form("hsdeltai_%d/F",i2));
    MergedTree -> Branch(Form("hsytari_%d",i2)      ,&hsytari_2     , Form("hsytari_%d/F",i2));
    MergedTree -> Branch(Form("hsyptar_%d",i2)      ,&hsyptar_2     , Form("hsyptar_%d/F",i2));
    MergedTree -> Branch(Form("hsxptar_%d",i2)      ,&hsxptar_2     , Form("hsxptar_%d/F",i2));
    MergedTree -> Branch(Form("hsdelta_%d",i2)      ,&hsdelta_2     , Form("hsdelta_%d/F",i2));
    MergedTree -> Branch(Form("hsytar_%d",i2)       ,&hsytar_2      , Form("hsytar_%d/F",i2));
    MergedTree -> Branch(Form("ok_spec_%d",i2)      ,&ok_spec_2     , Form("ok_spec_%d/F",i2));
    
    

    for (entry = 0; entry < T1->GetEntries() ; entry++) {
        T1 -> GetEntry(entry);
        T2 -> GetEntry(entry);
        SHOW(hsyptari_1);
        SHOW(hsyptari_2);
        SHOW(hsytar_1);
        SHOW(hsytar_2);
        MergedTree -> Fill();
        if (entry%(100000) == 0) {
            Printf("[%.0f%%]",100*((float)entry/T1->GetEntries()));
        }
    }
    
    MergedTree -> Write();
    MergedFile -> Close();
    
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F* TSIMC::CompareVariable(TString Var, TString cutstr,
                             int i1, int i2,
                             int Nbins, double Xlow, double Xup,
                             TString Title, TString Units){
    
    TAnalysisSIMC anaMerged(Form("Merged_%d_%d",i1,i2));
    TString XTitle  = Form("[ #Delta(%s)_{%d} - #Delta(%s)_{%d} ] / %s(gen.) [%%]",Title.Data(),i1,Title.Data(),i2,Title.Data()) ;
    Title           = "diff. in resolution in " + Title;
    TCut cut        = Form("%s",cutstr.Data());
    cut             = cut && Form("ok_spec_%d &&  ok_spec_%d ",i1,i2);
    TString Res1    = Form("%s_%d - %si_%d",Var.Data(),i1,Var.Data(),i1) , Res2 = Form("%s_%d - %si_%d",Var.Data(),i2,Var.Data(),i2);
    TH1F * h        = anaMerged.H1(Form("100.*((%s) - (%s))/%si_%d",Res1.Data(),Res2.Data(),Var.Data(),i1),cut,"HIST e",Nbins ,Xlow ,Xup,Title,XTitle);
    anaMerged.Text( h->GetMean()+0.1*h->GetRMS() , h->GetMaximum() , Form("Mean=%.1f %%" ,h->GetMean()) );
    //    anaMerged.Text( h->GetMean()+0.1*h->GetRMS() , 0.8*h->GetMaximum() , Form("RMS=%.1f(%.0f) %%" ,h->GetRMS(),10*h->GetRMSError()) );
    return h;
    
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH2F* TSIMC::CompareVariable2D(TString Var, TString cutstr,
                             int i1, int i2,
                             int Nbins, double Xlow, double Xup,
                             TString Title, TString Units){
    
    TAnalysisSIMC anaMerged(Form("Merged_%d_%d",i1,i2));
    Units           = (Units!=""&&Units!="e-4") ? " [" + Units + "]" : "";
    TString XT1     = Title + Form("_{%d} - ",i1) + Title + Units;
    TString XT2     = Title + Form("_{%d} - ",i2) + Title + Units;
    TCut cut        = Form("%s",cutstr.Data());
    cut             = cut && Form("ok_spec_%d &&  ok_spec_%d ",i1,i2);
    //    TString Res1    = Form("%s_%d - %si_%d",Var.Data(),i1,Var.Data(),i1) ;
    //    TString Res2    = Form("%s_%d - %si_%d",Var.Data(),i2,Var.Data(),i2);
    TString Res1    = Form("%si_%d",Var.Data(),i1) ;
    TString Res2    = Form("%si_%d",Var.Data(),i2) ;
    TH2F * h        = anaMerged.H2(Res1,Res2,cut,"colz",Nbins ,Xlow ,Xup,Nbins ,Xlow ,Xup,Title,XT1,XT2);
    return h;
    
}




#endif
