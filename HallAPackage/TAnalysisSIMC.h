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
    float   NormFac  , SIMCQ , totweights , I;
    int     BeamDays;
    TString ExpType;
    
    
    
    
    TString Path , InFileName;
    TFile * InFile;
    TTree * Tree;
    TString Target;

    

    
    
    TAnalysisSIMC (int filenumber, TString target, int beamdays = 1,float simcQ = 90, float i = 25); // two arms
    TAnalysisSIMC (int filenumber=1, double p=1.);    // single arm
    ~TAnalysisSIMC (){};

    
    // GETs
    TString           GetPath (){return Path;};
    
    
    
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
    
    
    void           SetGlobals ();
    void           SetAliases ();
    void          SetNormFact ();
    
    
    
    // yield
    void        ScaleToYield (TH1F *,bool DoPrint=false);
    
    
    // TH1F
    TH1F *  H1          (TString, TCut, TString, int Nbins, double Xlow, double Xup,TString T="",TString XT="",TString YT="",int c=1);
    TH1F *  Resolution1D(TString, TCut, TString, int Nbins, double Xlow, double Xup,TString T="",TString XT="",int c=1);
    

};

#endif
/** @} */ // end of doxygen group 

