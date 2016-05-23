/**
 * \file TCalcSIMC.h
 *
 * \ingroup HallAPackage
 * 
 * \brief Class def header for a class TCalcSIMC
 *
 * @author erezcohen
 */

/** \addtogroup HallAPackage

    @{*/
#ifndef TCALCSIMC_H
#define TCALCSIMC_H

#include <iostream>
#include "TCalcSIMC.h"
#include <iostream>
#include "TRandom3.h"
#include <algorithm>
#include "MySoftwarePackage/TPlots.h"
#include "MySoftwarePackage/TCalculations.h"
#include "MySoftwarePackage/TAnalysis.h"

using namespace std;

/**
   \class TCalcSIMC
   User defined class TCalcSIMC ... these comments are used to generate
   doxygen documentation!
 */
class TCalcSIMC : public TCalculations{

public:

    
    
    
    TString Path , InFileName  , InTreeName , OutFileName , OutTreeName;
    
    TFile   * InFile    , * OutFile;
    TTree   * InTree    , * OutTree;
    TPlots  plot;
    TRandom3  rand;
    
    int     Nentries    , Entry;
    
    
    
    // PARTICLES....
    Int_t   A , Np;
    

    // reconstructed
    Float_t Xb          , Q2        , q3mag     , Nu    ;
    Float_t hsdelta     , hsyptar   , hsxptar   , hsytar;
    Float_t hsxfp       , hsxpfp    , hsyfp     , hsypfp;
    Float_t ssdelta     , ssyptar   , ssxptar   , ssytar;
    Float_t ssxfp       , ssxpfp    , ssyfp     , ssypfp;
    Float_t Em          , Pm        , thetapq   , phipq;
    Float_t Pmx         , Pmy       , Pmz;
    Float_t Weight      , E0;
    
    
    Float_t PeC , TheC, PpC , ThpC;
    
    
    TVector3            Pbeam       , Pe;
    vector<TVector3>    p3vec       ;
    TLorentzVector      Beam        , e         , q     , p;
    TLorentzVector      Plead       , Pmiss     , Pcm   , Prec;
    
    
    
    
    
    
    /// Default constructor
    TCalcSIMC(){}
    TCalcSIMC(TTree * fInTree, TTree * fOutTree
              , int fA = 2 // target
              , Float_t fE0 = 1 // beam energy
              , Float_t fPeC = 1 // electron arm centeral momentum
              , Float_t fTheC = 10 // electron arm angle
              , Float_t fPpC = 1 // hadron arm centeral momentum
              , Float_t fThpC = 10 // hadron arm angle
            );
    ~TCalcSIMC(){}
    
    
    
    
    // GETs
    
    
    // SETs
    void          SetPath (TString path){Path = path;};
    void        SetInTree (TTree * tree){InTree = tree;};
    void       SetOutTree (TTree * tree){OutTree = tree;};
    
    // initializations
    void    InitInputTree ();
    void   InitOutputTree ();
    void      InitGlobals (int fA, Float_t fE0 , Float_t fPeC , Float_t fTheC, Float_t fPpC , Float_t fThpC);
    void        InitEvent ();
    
    
    void  ComputePhysVars (int entry);
    
    void       PrintData (int);

};

#endif
/** @} */ // end of doxygen group 

