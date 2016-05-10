# run:
# > python mac/ana_deep_hallc.py <run number>

import sys, os, Initiation as init
from ctypes import c_int, c_char, c_char_p
import ROOT
from ROOT import TString, TPlots, TAnalysisSIMC , TSIMC
from rootpy.interactive import wait
init.createnewdir()

Operation   = "Draw Variable"
Variable    = "Q2"
Nbins       = 100

if len(sys.argv)>1:
    run     = int(sys.argv[1])
else:
    print "run: \n> python mac/ana_deep_hallc.py <run number>\n"
    exit(0)




ana = TAnalysisSIMC( run  , "D" )




if Operation=="Draw Variable":
    c = ana.CreateCanvas(Variable)
    
    if (Variable=="Q2"):
        xAxis = [Variable , 0 , 4, "Q^{2} (GeV/c)^{2}"]
    
    ana.H1(xAxis[0] , ROOT.TCut() , "BAR E" , Nbins , xAxis[1] , xAxis[2] , "",xAxis[3])

    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/deep_hallc_"+Variable+".pdf")

