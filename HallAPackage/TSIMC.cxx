#ifndef TSIMC_CXX
#define TSIMC_CXX

#include "TSIMC.h"





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TSIMC::DrawQuantity(TString Var, int Nbins,double Xlow, double Xup, TString Title, TString Units, int N, int * FileNumbers , bool DoAddLegend, TCut cut){
    SHOW(sizeof(FileNumbers));
    SHOW(sizeof(FileNumbers)/sizeof(int));
    
    vector      <int> color;
    vector      <float> frac;
    vector      <TAnalysisSIMC> ana;
    TString     Labels[sizeof(FileNumbers)/sizeof(int)];
    float       Maximum = 0;
    TH1F        * h[sizeof(FileNumbers)/sizeof(int)];
    TString     XTitle = (Units!="") ? Title + " [" + Units + "]" : Title;

    for ( int i = 0 ; i < N ; i++ ) {

        color.push_back((i < 4) ? i+1 : i+2);
        ana.push_back(TAnalysisSIMC(FileNumbers[i]));
        h[i]    = ana[i].H1(Var,cut,(i==0)?"HIST e":"same HIST e",Nbins ,Xlow ,Xup,Title,XTitle,"",color[i]);
        Maximum = (h[i] -> GetMaximum() > Maximum) ? h[i] -> GetMaximum() : Maximum;

    }

    int BaseLineEntries = h[0] -> GetEntries();
    for ( int i = 0 ; i < N ; i++ ) {
        frac.push_back((float)h[i]->GetEntries()/BaseLineEntries);
        Labels[i] = Form("file %d [%.0f%%]",FileNumbers[i],100.*frac[i]);
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
void TSIMC::DrawResolution(TString Var, int Nbins,double Xlow, double Xup, TString Title, TString Units, int N, int * FileNumbers , bool DoAddLegend, TCut cut){
    vector      <int> color;
    vector      <float> frac;
    vector      <TAnalysisSIMC> ana;
    TString     Labels[sizeof(FileNumbers)/sizeof(int)];
    float       Maximum = 0;
    TH1F        * h[sizeof(FileNumbers)/sizeof(int)];
    TString     XTitle = (Units!="") ? Title + " [" + Units + "]" : Title;

    
    for ( int i = 0 ; i < N ; i++ ) {
        
        color.push_back((i < 4) ? i+1 : i+2);
        ana.push_back(TAnalysisSIMC(FileNumbers[i]));
        h[i]    = ana[i].Resolution1D(Var,cut,(i==0)?"HIST e":"same HIST e",Nbins ,Xlow ,Xup,Title,XTitle,color[i]);
        Maximum = (h[i] -> GetMaximum() > Maximum) ? h[i] -> GetMaximum() : Maximum;
        
    }
    
    int BaseLineEntries = h[0] -> GetEntries();
    for ( int i = 0 ; i < N ; i++ ) {
        frac.push_back((float)h[i]->GetEntries()/BaseLineEntries);
        Labels[i] = Form("file %d [%.0f%%]",FileNumbers[i],100.*frac[i]);
        ana[i].Text(h[i]->GetMean()+0.5*h[i]->GetRMS(), Maximum*(1-0.1*i)
                     ,Form("RMS=%.2f(%.0f) %s" ,h[i]->GetRMS(),100*h[i]->GetRMSError(),Units.Data()), color[i]);
        h[i] -> GetYaxis() -> SetRangeUser(0,1.1*Maximum);
    }
    if (DoAddLegend){
        ana[0].AddLegend("SOS configurations",N,h,Labels,1,"f");
    }
}



#endif
