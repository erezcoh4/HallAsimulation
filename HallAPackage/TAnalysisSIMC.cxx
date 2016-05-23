#ifndef TANALYSISSIMC_CXX
#define TANALYSISSIMC_CXX

#include "TAnalysisSIMC.h"



// two arms
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TAnalysisSIMC::TAnalysisSIMC(int fFileNumber, TString target, int beamdays , float simcQ, float i, Float_t fE0, Float_t fPe, Float_t fThe, Float_t fPp, Float_t fThp):
TPlots(Form("$SIMCFiles/data/run%d.root",fFileNumber),"h666",Form("run%d",fFileNumber),false){

    E0  = fE0;
    Pe  = fPe;
    The = fThe;
    Pp  = fPp;
    Thp = fThp;
    Printf("starting SIMC with E0=%f, P(e)=%f, Theta(e)=%f, P(p)=%f, Theta(p)=%f ",E0,Pe,The,Pp,Thp);
    
    SetPath         ("/Users/erezcohen/Desktop/A3/Simulation/simc_files/");
    SetInFileName   ( Form("run%d",fFileNumber) );
    SetInFile       ( new TFile( Path + "/data/" + InFileName + ".root"));
    SetTree         ((TTree*) InFile->Get( "h666" ));
    SetBeamDays     ( beamdays );
    SetSIMCQ        ( simcQ );
    SetI            ( i );
    SetTarget       ( target );
    SetExpType      ( "TwoArmsCoincidence" );
    SetGlobals      ();
    SetAliases      ();
    SetNormFact     ();
}

// single arm
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TAnalysisSIMC::TAnalysisSIMC(int fFileNumber)
:TPlots(Form("$SIMCFiles/data/SingleArm_%d.root",fFileNumber),"h1",Form("SingleArm_%d",fFileNumber),true){
    
    SetPath         ("/Users/erezcohen/Desktop/A3/Simulation/simc_files/");
    SetInFileName   ( Form("SingleArm_%d",fFileNumber) );
    SetInFile       ( new TFile( Path + "/data/" + InFileName + ".root"));
    SetTree         ((TTree*) InFile->Get( "h1" ));
    cout << "opeining " << InFile->GetName() << endl;
    SetExpType      ( "SingleArm" );
    SetGlobals      ();
    
}

// single arm - from a different file name (e.g. merged) - April 15,2016
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TAnalysisSIMC::TAnalysisSIMC(TString fFileName)
:TPlots(Form("$SIMCFiles/data/%s.root",fFileName.Data()),"h1",fFileName,true){
    
    SetPath         ("/Users/erezcohen/Desktop/A3/Simulation/simc_files/");
    SetInFileName   ( fFileName );
    SetInFile       ( new TFile( Path + "/data/" + InFileName + ".root"));
    SetTree         ((TTree*) InFile->Get( "h1" ));
    SetExpType      ( "SingleArm" );
    SetGlobals      ();
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysisSIMC::SetGlobals(TString Spectrometers){
    
    if (Spectrometers == "HRS")
        L = 118;// HRS equipped with a set of collimators, positioned 1.1097+/-0.005 (RHRS) and 1.1017+/-0.005 (LHRS)
    else
        L = 0;
    Nentries    = Tree -> GetEntries();
    totweights  = GetBranchSum((ExpType=="SingleArm")?"ok_spec":"Weight","");
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
        cout << "opened " << Path << "/hist/" << InFileName << ".hist" << endl;
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
        cout << "could not open " << Path << "/hist/" << InFileName << ".hist" << endl;
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
    if (ExpType!="SingleArm" && strcmp(Target,"D")==0){
        SetAlias("theta_rq","180-TMath::RadToDeg()*TMath::ACos(Pmpar/Pm)");
        Tree -> SetAlias("theta_rq","180-TMath::RadToDeg()*TMath::ACos(Pmpar/Pm)");
        SetAlias("Pp_cent",Form("(Q2/Q2)*%f",Pp));
        Tree -> SetAlias("Pp_cent",Form("(Q2/Q2)*%f",Pp));
        SetAlias("Pp","Pp_cent*(hsdelta/100+1)");
        Tree -> SetAlias("Pp","Pp_cent*(hsdelta/100+1)");
        SetAlias("Theta_p","Thp_cent + (TMath::RadToDeg()*hsyptar)");
        Tree -> SetAlias("Theta_p","Thp_cent + (TMath::RadToDeg()*hsyptar)");
        
        SetAlias("Thp_cent",Form("(Q2/Q2)*%f",Thp));
        Tree -> SetAlias("Thp_cent",Form("(Q2/Q2)*%f",Thp));
        SetAlias("Pe_cent",Form("(Q2/Q2)*%f",Pe));
        Tree -> SetAlias("Pp_cent",Form("(Q2/Q2)*%f",Pe));
        SetAlias("The_cent",Form("(Q2/Q2)*%f",The));
        Tree -> SetAlias("The_cent",Form("(Q2/Q2)*%f",The));
        SetAlias("Pe","Pe_cent*(ssdelta/100+1)");
        Tree -> SetAlias("Pe","Pe_cent*(ssdelta/100+1)");

        SetAlias("Theta_e","The_cent + (TMath::RadToDeg()*ssyptar)"); 
        Tree -> SetAlias("Theta_e","The_cent + (TMath::RadToDeg()*ssyptar)");
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
TH2F *  TAnalysisSIMC::H2 (TString varX,TString varY, TCut cut, TString option
                           , int NbinsX, double Xlow, double Xup, int NbinsY, double Ylow, double Yup
                           , TString Title, TString XTtitle, TString YTitle, int color){
    TH2F* h = TPlots::H2(varX,varY,cut,option,NbinsX,Xlow,Xup,NbinsY,Ylow,Yup,Title,XTtitle,YTitle,color);
    if(ExpType!="SingleArm") ScaleToYield((TH1F*)h,true);
    return h;
}








//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysisSIMC::ScaleToYield(TH1F * h,bool DoPrint){
    // normfac is retrieved from .hist file, and given per SIMCQ[mC] = 1 hour run at current I[uA]
    float Q     = SIMCQ;//24 * BeamDays * (SIMCQ*1000/(I * 60 * 60));       //time * (I/(1.e6))*1000;       // [mC]
    yield       = (totweights * NormFac / Nentries) * ((float)h->GetEntries()/Nentries);           // total yield
    //    h -> Scale( (Target == "D") ? (NormFac / Nentries) * (Q/1.5) :  (NormFac / Nentries) * Q)  ; // Hall-A (A=3) scaling of 3/2
    float ScaleFactor = ( NormFac / Nentries ) * ((float)h->GetEntries()/Nentries) ;
    h -> Scale( yield/(h->GetEntries()) )  ;
    if (typeid(h)==typeid(TH1F)) h -> GetYaxis() -> SetRangeUser(0,1.1*h->GetMaximum());
    
    if(DoPrint){
        Printf("for beam charge of %.1f mC:",Q);
        SHOW(Q);
        SHOW(NormFac);
        SHOW(Nentries);
        SHOW((float)h->GetEntries()/Nentries);
        SHOW(ScaleFactor);
        SHOW(totweights);
        SHOW(totweights * NormFac / Nentries );
        SHOW(yield);
        SHOW(h -> Integral());
    }
    Printf("expected %.1f events/%.1f Coulomb",yield,Q/1000.);
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F *  TAnalysisSIMC::Resolution1D(TString var, TCut cut, TString option, int Nbins, double Xlow, double Xup
                                    , TString Title, TString XTitle, int color){
    return H1(Form("(%s-%si)",var.Data(),var.Data()),cut,option,Nbins,Xlow,Xup
              ,"Res. in "+Title, XTitle, "", color);
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F *  TAnalysisSIMC::Res(TString var, TCut cut, TString option, int Nbins, double Xlow, double Xup
                                , TString Title, TString XTitle, int color){
    return H1(Form("100*(%s-%si)/%si",var.Data(),var.Data(),var.Data()),cut,option,Nbins,Xlow,Xup
              ,Form("(%s(rec.)-%s(gen.))/%s(gen.)",Title.Data(),Title.Data(),Title.Data()), Form("#Delta %s/%s(gen.) [%%]",Title.Data(),Title.Data()), "", color);
}











#endif
