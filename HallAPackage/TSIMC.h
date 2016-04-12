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
    
    
    TCut okCut , YtagCut;
    vector      <TAnalysisSIMC> ana;
//    char    ** Names;
    vector      <TString> Names;

    int     * FileNumbers;
    vector      <int> colors;
    int     N;
    
    /// Default constructor
    TSIMC(int, int * , int *, char **);
    
    /// Default destructor
    ~TSIMC(){}
    
    
 
    void DrawQuantity (TString, int,double, double, TString, TString, bool DoAddLegend = false);
    void DrawResolution (TString, int,double, double, float MulFac, TString, TString, bool DoAddLegend = false);

    void SetCuts();
};

#endif
/** @} */ // end of doxygen group

