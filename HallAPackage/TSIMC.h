/**
 * \file TSIMC.h
 *
 * \ingroup HallAPackage
 *
 * \brief Class def header for a class TSIMC
 *
 * @author erezcohen
 */

/** \addtogroup HallAPackage
 
 @{*/
#ifndef TSIMC_H
#define TSIMC_H

#include <iostream>
#include "TAnalysisSIMC.h"

/**
 \class TSIMC
 User defined class TSIMC ... these comments are used to generate
 doxygen documentation!
 */
class TSIMC{
    
public:
    
    TAnalysis   analysis;
    TCut okCut , YtagCut;
    TAnalysisSIMC * ana[10];
    vector      <TString> Names;
    TString     NFilesStr;
    vector      <int> FileNumbers;
    vector      <int> colors;
    int         N;
    
    /// Default constructor
    TSIMC (){};
    TSIMC (int, int * , int *, char **);
    
    /// Default destructor
    ~TSIMC() { }
    
 
//    void      DrawQuantity (TString, int,double, double, TString, TString, bool DoAddLegend = false, bool DoAddCuts = false , double cXl=0, double cXu=0);
//    void    DrawQuantity2D (TString, TString, int,double, double,int,double, double, TString, TString, TString, TString,
//                            bool DoAddLegend = false, bool DoAddCuts = false,double cXl=0, double cXu=0,double cYl=0, double cYu=0);
//    void    DrawResolution (TString, int,double, double, float MulFac, TString, TString, bool DoAddLegend = false);
//    void           DrawRes (TString, int,double, double, TString, TString, bool DoAddLegend = false);

    void           SetCuts ();


    void         MergeFiles (int, int);
//    TH1F*   CompareVariable (TString, TString, int, int, int, double, double, TString, TString);
//    TH2F* CompareVariable2D (TString, TString, int, int, int, double, double, TString, TString);



};

#endif
/** @} */ // end of doxygen group

