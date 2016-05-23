#ifndef TCALCSIMC_CXX
#define TCALCSIMC_CXX

#include "TCalcSIMC.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TCalcSIMC::TCalcSIMC( TTree * fInTree, TTree * fOutTree, int fA , Float_t fE0, Float_t fPeC, Float_t fTheC, Float_t fPpC, Float_t fThpC){
    SetInTree       (fInTree);
    SetOutTree      (fOutTree);
    InitGlobals     (fA , fE0 , fPeC, fTheC, fPpC, fThpC);
    InitInputTree   ();
    InitOutputTree  ();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TCalcSIMC::InitInputTree(){

    InTree -> SetBranchAddress("Xb"     , &Xb);
    InTree -> SetBranchAddress("Q2"     , &Q2);
    InTree -> SetBranchAddress("q"      , &q3mag);
    InTree -> SetBranchAddress("Weight" , &Weight);
    InTree -> SetBranchAddress("Pmx"    , &Pmx);
    InTree -> SetBranchAddress("Pmy"    , &Pmy);
    InTree -> SetBranchAddress("Pmz"    , &Pmz);
    InTree -> SetBranchAddress("Em"     , &Em);
    InTree -> SetBranchAddress("Pm"     , &Pm);
    InTree -> SetBranchAddress("thetapq", &thetapq);
    InTree -> SetBranchAddress("phipq"  , &phipq);
    
    // hs-proton arm, ss-electron arm (for electron at SHMS - 5)

    // hs-electron arm
    InTree -> SetBranchAddress("hsxfp"  , &hsxfp);
    InTree -> SetBranchAddress("hsypfp" , &hsypfp);
    InTree -> SetBranchAddress("hsxpfp" , &hsxpfp);
    InTree -> SetBranchAddress("hsyfp"  , &hsyfp);
    InTree -> SetBranchAddress("hsdelta", &hsdelta);
    InTree -> SetBranchAddress("hsyptar", &hsyptar);
    InTree -> SetBranchAddress("hsxptar", &hsxptar);
    InTree -> SetBranchAddress("hsytar" , &hsytar);
    // ss-hadron arm
    InTree -> SetBranchAddress("ssxfp"  , &ssxfp);
    InTree -> SetBranchAddress("ssypfp" , &ssypfp);
    InTree -> SetBranchAddress("ssxpfp" , &ssxpfp);
    InTree -> SetBranchAddress("ssyfp"  , &ssyfp);
    InTree -> SetBranchAddress("ssdelta", &ssdelta);
    InTree -> SetBranchAddress("ssyptar", &ssyptar);
    InTree -> SetBranchAddress("ssxptar", &ssxptar);
    InTree -> SetBranchAddress("ssytar" , &ssytar);

     Nentries    = InTree -> GetEntries();
    std::cout << "Initialized Input InTree TCalcSIMC for " << InTree -> GetName() <<", Nentries = " <<  Nentries << std::endl;
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TCalcSIMC::InitOutputTree(){
    
    // Integer branches
    OutTree -> Branch("A"                   ,&A                     ,"A/I");
    OutTree -> Branch("Np"                  ,&Np                    ,"Np/I");
    
    
    // Float_t branches
    OutTree -> Branch("Xb"                  ,&Xb                    , "Xb/F");
    OutTree -> Branch("Q2"                  ,&Q2                    , "Q2/F");
    OutTree -> Branch("thetapq"             ,&thetapq               , "thetapq/F");
    OutTree -> Branch("phipq"               ,&phipq                 , "phipq/F");
    
    
    // TLorentzVector branches
    OutTree -> Branch("Pmiss"               ,"TLorentzVector"       ,&Pmiss);
    OutTree -> Branch("Pcm"                 ,"TLorentzVector"       ,&Pcm);
    OutTree -> Branch("Plead"               ,"TLorentzVector"       ,&Plead);
    OutTree -> Branch("Prec"                ,"TLorentzVector"       ,&Prec);
    OutTree -> Branch("Beam"                ,"TLorentzVector"       ,&Beam);
    OutTree -> Branch("e"                   ,"TLorentzVector"       ,&e);
    OutTree -> Branch("q"                   ,"TLorentzVector"       ,&q);
    OutTree -> Branch("p"                   ,"TLorentzVector"       ,&p);
    
    
    std::cout << "Initialized Output Tree TCalcSIMC on " << OutTree -> GetTitle() << std::endl;
    
    
    
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TCalcSIMC::InitGlobals(int fA, Float_t fE0 , Float_t fPeC , Float_t fTheC, Float_t fPpC , Float_t fThpC){
    A       = fA;
    E0      = fE0;
    PeC     = fPeC;
    TheC    = fTheC;
    PpC     = fPpC;
    ThpC    = fThpC;

    Beam = TLorentzVector( 0 , 0 , E0 , E0 );
    
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TCalcSIMC::InitEvent(){
    Plead = Pcm = p = q = Prec = e = Beam = TLorentzVector();
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TCalcSIMC::ComputePhysVars(int entry){
    
    InitEvent();
    InTree -> GetEntry(entry);
    
//    // electron
//    PeMag = hsdelta
//    Pe.SetVectM( Px_e , Py_e , Pz_e );
//    e.SetVectM( Pe , Me );
//    q = Beam - e;
//    Q2 = -q.Mag2();
//    
//    
//    
//    // get protons - energy loss correction and Coulomb corrections
//    for (int i = 0 ; i < Np ; i++ ){
//        
//        p3vec.push_back( TVector3 (PpX[i],PpY[i],PpZ[i] ) );
//        EnergyLossCorrrection( p3vec.back() );
//        CoulombCorrection( p3vec.back() , CoulombDeltaE );
//        if ( p3vec.back().Mag() > Plead.P() )
//        Plead.SetVectM( p3vec.back() , Mp ) ;           // Plead is first calculated in Lab-Frame
//        
//    }
//    
//    // Pmiss , p/q , 𝜃(p,q)
//    Pmiss       = Plead - q;
//    // p(A-1) = -p(init) , and E(A-1) + E(p(init)) = m(A) => E(p(init)) = m(A) - E(A-1)
//    E_p_init    = mA - sqrt( pow( m_A_1 , 2 ) + pow( Pmiss.P() , 2 ) );
//    M_p_init    = Mp;
//    TpMiss      = E_p_init - M_p_init; // should be < 0, since the nucleon is bound - the p is off the energy shell
//    
//    theta_pq    = r2d * Plead.Vect().Angle(q.Vect());
//    p_over_q    = Plead.P() / q.P();
//    
//    
//    
//
//    // c.m. momentum
//    Pcm         = -q;
//    
//    
//
//    // all recoil protons together (just without the leading proton)
//    Plead       = protons.at(0);            // now Plead is calculated in q-Pmiss frame
//    Prec        = Pcm - (Plead - q);        // Prec is the 4-vector sum of all recoiling protons
//    
//    // finally, fill the TTree output
//    OutTree -> Fill();
    
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TCalcSIMC::PrintData(int entry){
    
    SHOW(entry);
    SHOW(Xb);
    SHOW(Q2);
    SHOWTLorentzVector(e);
    SHOWTLorentzVector(q);
    SHOWTLorentzVector(Plead);
    SHOWTLorentzVector(Pmiss);
    SHOWTLorentzVector(Prec);
    SHOWTLorentzVector(Pcm);
    SHOW(thetapq);
    PrintLine();
}



#endif
