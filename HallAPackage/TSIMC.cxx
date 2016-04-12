#ifndef TSIMC_CXX
#define TSIMC_CXX

#include "TSIMC.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TSIMC::TSIMC(int fN, int * fFileNumbers , int fcolors[] , char ** fNames){
    SetCuts();
    N = fN;
    for ( int i = 0 ; i < N ; i++ ) {
        
        FileNumbers[i]  = fFileNumbers[i];
        ana.push_back(TAnalysisSIMC(FileNumbers[i]));
        Names.push_back(fNames[i]);
        colors.push_back(fcolors[i]);
        
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::SetCuts(){
    okCut   = "ok_spec==1 ";
    YtagCut = " (-5 < hsytar) && (hsytar < 5)" ;
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::DrawQuantity(TString Var, int Nbins,double Xlow, double Xup, TString Title, TString Units
                         , bool DoAddLegend){
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
    if (DoAddLegend){
        ana[0].AddLegend("SOS configurations",N,h,Labels,1,"f");
    }
}





//
//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//void TAnalysisSIMC::Draw2DQuantity(TString VarX, TString VarY
//                                   , int NbinsX,double Xlow, double Xup
//                                   , int NbinsY,double Ylow, double Yup
//                                   , TString XTitle, TString XUnits, TString YTitle, TString YUnits
//                                   , const int N, TAnalysisSIMC * simc[N], int color[N], TString * Labels
//                                   , bool DoAddLegend = false, TCut cut = "ok_spec==1"&&YtagCut){
//    //    int TotEntries = simc[N-1] -> totweights;
//    TString Title   = XTitle + " vs. " + YTitle;
//    XTitle = (XUnits=="") ? XTitle : (XTitle + " [" + XUnits + "] ") ;
//    YTitle = (YUnits=="") ? YTitle : (YTitle + " [" + YUnits + "] ") ;
//    TH2F  * h[N];
//    TString newLabesls[N];
//    for (int i = 0 ; i < N ; i++ ){
//        h[i] = simc[i] -> H2(VarX, VarY,cut,(i==0)?"":"same"
//                             ,NbinsX ,Xlow ,Xup, NbinsY , Ylow , Yup
//                             ,Title,XTitle,YTitle,color[i],20,0.9,1);
//    }
//    for (int i = 0 ; i < N ; i++ )
//    newLabesls[i] = Labels[i] + " [" + plot->PercentStr(h[i]->GetEntries()/h[N-1]->GetEntries()) + "]";
//    
//    if (DoAddLegend)
//    plot -> AddLegend("SOS configurations",N,h,newLabesls,1,"p");
//}
//
//
//
//
//








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
        ana[0].AddLegend("SOS configurations",N,h,Labels,1,"f");
    }
}



#endif
