#ifndef TANALYSISSIMC_CXX
#define TANALYSISSIMC_CXX

#include "TAnalysisSIMC.h"



// two arms
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TAnalysisSIMC::TAnalysisSIMC(TString fInFileName, TString target, int beamdays,float simcQ, float i):
TPlots("$SIMCFiles/data/" + fInFileName + ".root","h666",fInFileName,false){
    
    SetPath         ("$SIMCAnaFiles");
    SetInFileName   ( fInFileName );
    SetInFile       ( new TFile( "$SIMCFiles/data/" + InFileName + ".root"));
    SetTree         ((TTree*) InFile->Get( "h666" ));
    SetBeamDays     ( beamdays );
    SetSIMCQ        ( simcQ );
    SetI            ( i );
    SetTarget       ( target );
    SetExpType      ( "TwoArmsCoincidence" );
    SetAliases      ();
    SetGlobals      ();
    SetNormFact     ();
    
}




// single arm
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TAnalysisSIMC::TAnalysisSIMC(TString path, TString fInFileName, double HRSmomentum)
:TPlots("$SIMCFiles/data" + fInFileName + ".root","h1",fInFileName,false){

    SetPath         ("$SIMCAnaFiles");
    SetInFileName   ( fInFileName );
    SetInFile       ( new TFile( "$SIMCFiles/data/" + InFileName + ".root"));
    SetTree         ((TTree*) InFile->Get( "h1" ));
    SetExpType      ( "SingleArm" );
    SetAliases      ();
    SetGlobals      ();

}








//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysisSIMC::SetGlobals(){
    L           = 118;// HRS equipped with a set of collimators, positioned 1.1097+/-0.005 (RHRS) and 1.1017+/-0.005 (LHRS)
    Nentries    = Tree -> GetEntries();
    totweights  = GetBranchSum((ExpType=="SingleArm")?"ok_spec":"Weight",(ExpType=="SingleArm")?"ok_spec":"Weight");
    printf("Initiating SIMC with %d Nentries\n",Nentries);
}







//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysisSIMC::SetNormFact(){
    ifstream InFile;
    InFile.open(Path+"/hist/"+InFileName+".hist");
    string word     = "normfac";  //this array will save user input
    int array_size  = 10024; // define the size of character array
    int position    = 0; //this will be used incremently to fill characters in the array
    char * array    = new char[array_size];
    char * exp_arr  = new char[2];
    float exponent  = 0;
    char * dig_arr  = new char[8];
    float digits    = 0;
    if (InFile.is_open()) {
        while(!InFile.eof() && position < array_size) {
            InFile.get(array[position]); //reading one character from file to array
            position++;
        }
        array[position-1] = '\0'; //placing character array terminating character
        //this loop is searching for the word in the array
        for(int i = 0; array[i] != '\0'; i++)  {
            for(int j = 0; j < word.size() ; j++) {
                if(array[i] != word[j]) { break; }
                else {
                    i++;
                    if(word[j+1] == '\0') {
                        for (int k = i-word.size()+14 ; k < i-word.size() + 22 ; k++)
                        dig_arr[k-(i-word.size()+14)] = array[k];
                        digits      = atof(dig_arr);
                        for (int k = i-word.size()+24 ; k < i-word.size() + 26 ; k++)
                        exp_arr[k-(i-word.size()+24)] = array[k];
                        exponent    = atof(exp_arr);
                    }
                }
            }
        }
    }
    else{
        cout << "could not open " << Path << "/" << InFileName << ".hist" << endl;
    }
    NormFac = digits * pow(10,exponent);
    SHOW(NormFac);
    InFile.close();
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysisSIMC::SetAliases(){
    SetAlias("Ysieve",Form("hsytar+%f*hsyptar",L));
    Tree -> SetAlias("Ysieve",Form("hsytar+%f*hsyptar",L));
    SetAlias("Xsieve",Form("0+%f*hsxptar",L));
    Tree -> SetAlias("Xsieve",Form("0+%f*hsxptar",L));
    if (strcmp(Target,"D")==0){
        SetAlias("theta_rq","180-TMath::RadToDeg()*TMath::ACos(Pmpar/Pm)");
        Tree -> SetAlias("theta_rq","180-TMath::RadToDeg()*TMath::ACos(Pmpar/Pm)");
    }
}









//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F *  TAnalysisSIMC::H1 (TString var, TCut cut, TString option, int Nbins, double Xlow, double Xup
                           , TString Title, TString XTtitle, TString YTitle, int color){
    TH1F* h = TPlots::H1(var,cut,option,Nbins,Xlow,Xup,Title,XTtitle,YTitle,color,color);
    if(ExpType!="SingleArm") ScaleToYield(h,true);
    return h;
}








//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysisSIMC::ScaleToYield(TH1F * h,bool DoPrint){
    // normfac is retrieved from .hist file, and given per SIMCQ[mC] = 1 hour run at current I[uA]
    float Q         = 24 * BeamDays * (SIMCQ*1000/(I * 60 * 60));//time * (I/(1.e6))*1000;       // [mC]
    float yield     = (totweights * NormFac / Nentries) * Q;           // total yield
    h -> Scale( (Target == "D") ? (NormFac / Nentries) * (Q/1.5) :  (NormFac / Nentries) * Q)  ;
    
    if(DoPrint){
        SHOW(Q);
        SHOW(BeamDays);
        SHOW(totweights);
        SHOW(NormFac);
        SHOW(h -> GetEntries());
        SHOW(yield);
        SHOW(h -> Integral());
    }
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F *  TAnalysisSIMC::Resolution1D(TString var, TCut cut, TString option, int Nbins, double Xlow, double Xup
                                    , TString Title, TString Units, int color){
    return H1(Form("(%s-%si)",var.Data(),var.Data()),cut,option,Nbins,Xlow,Xup
              ,"Res. in "+Title, Title+" ["+Units+"]", "", color);
}


#endif
