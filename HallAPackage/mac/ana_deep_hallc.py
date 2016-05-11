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
Nbins       = 150

if len(sys.argv)>1:
    run     = int(sys.argv[1])
    ana = TAnalysisSIMC( run  , "D" )
else:
    run     = 0
    print "run: \n> python mac/ana_deep_hallc.py <run number>\n or for all > python mac/ana_deep_hallc.py"

plot   = TPlots()
anaAll = []
Kinematics = {1:"K11" , 2:"K12" , 3:"K13" ,4:"K21" , 5:"K22" , 6:"K23"}
#for run,name in Kinematics.items():
for run in Kinematics:
    anaAll.append(TAnalysisSIMC( run  , "D" ))
    print run,Kinematics[run]


if Operation=="Draw Variable":
    c = plot.CreateCanvas(Variable)
    
    if (Variable=="Q2"):
        xAxis = [Variable , 1.5 , 5, "Q^{2} (GeV/c)^{2}"]
    
    
    
    c = plot.CreateCanvas(Variable,"Divide",3,2)
#    for run,name in Kinematics.items():
    i=0
    for run in Kinematics:
        c.cd(i+1)
        anaAll[i].H1(xAxis[0] , ROOT.TCut() , "BAR E" , Nbins , xAxis[1] , xAxis[2] , Kinematics[run] ,xAxis[3] , "" ,38)
        i=i+1

    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/run%d"%run+"_"+Variable+".pdf")
