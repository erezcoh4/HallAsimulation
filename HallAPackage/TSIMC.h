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
    
    
    
    
    /// Default constructor
    TSIMC(){ YtagCut = "(-5 < hsytar) && (hsytar < 5)"; }
    
    /// Default destructor
    ~TSIMC(){}
    
    
    // cuts
    TCut YtagCut;

    void DrawQuantity (TString, int,double, double, TString, TString, int , int *
                      , bool DoAddLegend = false, TCut cut = "ok_spec==1 && (-5 < hsytar) && (hsytar < 5)");
    void DrawResolution (TString, int,double, double, TString, TString, int , int *
                      , bool DoAddLegend = false, TCut cut = "ok_spec==1 && (-5 < hsytar) && (hsytar < 5)");

    
};

#endif
/** @} */ // end of doxygen group

