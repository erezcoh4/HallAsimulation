/**
 * \file TAnalysisSIMC.h
 *
 * \ingroup HallAPackage
 * 
 * \brief Class def header for a class TAnalysisSIMC
 *
 * @author erezcohen
 */

/** \addtogroup HallAPackage

    @{*/
#ifndef TANALYSISSIMC_H
#define TANALYSISSIMC_H

#include <iostream>
#include "MySoftwarePackage/TPlots.h"
#include "MySoftwarePackage/TCalculations.h"
#include "MySoftwarePackage/TAnalysis.h"
using namespace std;


/**
   \class TAnalysisSIMC
   User defined class TAnalysisSIMC ... these comments are used to generate
   doxygen documentation!
 */
class TAnalysisSIMC: public TPlots{

public:

    
    // globals
    float   L     ;    // L is the distance from Hall center to the sieve plane
    int     Nentries;
    float   NormFac     , SIMCQ , totweights, I;
    int     BeamDays    , run ;
    TString ExpType;
    Float_t E0          , Pe    , The       , Pp    , Thp;
    Float_t yield;
    
    
    
    TString Path , InFileName;
    TFile * InFile;
    TTree * Tree;
    TString Target;

    

    
    TAnalysisSIMC (){};
//    TAnalysisSIMC (int filenumber, TString target, int beamdays = 100,float simcQ = 1, float i = 25); // two arms
    TAnalysisSIMC (int filenumber, TString target, int beamdays ,float simcQ , float i = 25, float fE0 = 1 , Float_t fPe = 1 , Float_t fThe = 10, Float_t fPp = 1 , Float_t fThp = 10); // two arms
    
    TAnalysisSIMC (int run_number, TString target);
    
    
    TAnalysisSIMC (int filenumber);         // single arm
    TAnalysisSIMC (TString fFileName);      // single arm
    ~TAnalysisSIMC (){};

    
    // GETs
    TString           GetPath (){return Path;};
    Float_t          GetYield (){return yield;};
    Float_t              GetQ (){return SIMCQ;};
    Float_t             GetE0 (){return E0;};
    Float_t             GetPe (){return Pe;};
    Float_t             GetPp (){return Pp;};
    Float_t            GetThe (){return The;};
    Float_t            GetThp (){return Thp;};
    
    
    // SETs
    void        SetInFileName (TString name)    {InFileName = name;};
    void            SetInFile (TFile * file)    {InFile = file;};
    void              SetTree (TTree * tree)    {Tree = tree;};
    void              SetPath (TString path)    {Path = path;};
    
    void          SetBeamDays ( int beamdays )  {BeamDays = beamdays;};
    void             SetSIMCQ ( float simcQ )   {SIMCQ = simcQ;};
    void                 SetI ( float i )       {I = i;};
    void            SetTarget ( TString target ){Target = target;};
    void                 SetL ( float l )       {L = l;};
    void           SetExpType ( TString etype ) {ExpType = etype;};
    
    
    void           SetGlobals (TString s = "HRS");
    void           SetAliases ();
    void          SetNormFact ();
    
    
    
    // yield
    void        ScaleToYield (TH1F *,bool DoPrint=false);
    
    
    // TH1F
    TH1F *           H1 (TString, TCut, TString, int Nbins, double Xlow, double Xup,TString T="",TString XT="",TString YT="",int c=1);

    TH2F *           H2 (TString,TString, TCut, TString
                         , int NbinsX, double Xlow, double Xup, int NbinsY, double Ylow, double Yup
                         , TString T="", TString XT="", TString YT="", int c=1);

    
    TH1F * Resolution1D (TString, TCut, TString, int Nbins, double Xlow, double Xup,TString T="",TString XT="",int c=1);
    TH1F *          Res (TString, TCut, TString, int Nbins, double Xlow, double Xup,TString T="",TString XT="",int c=1);
    
    
    
    

};

#endif
/** @} */ // end of doxygen group 

