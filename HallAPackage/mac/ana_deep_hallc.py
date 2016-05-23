# run:
# > python mac/ana_deep_hallc.py <run number>

import sys, os, Initiation as init
from ctypes import c_int, c_char, c_char_p
import ROOT
from ROOT import TString, TPlots, TAnalysisSIMC , TSIMC
from rootpy.interactive import wait
init.createnewdir()

Operation   = "Draw Variable"

plot   = TPlots()

if len(sys.argv)>2:
    run     = int(sys.argv[1])
    ana     = TAnalysisSIMC( run  , "D" , 1 , 1000 , 20, 11.0 , 9.85 , 10.0, 1.83, 43.7)
    Variable= sys.argv[2]

else:
    anaAll = []
    # look at weighted, accepted events, with the relevant kinematical cuts
    cut    = ROOT.TCut("Weight*success && (theta_rq<40) && (0.350<Pm && Pm<0.600) && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu))")
    Kinematics = {7:"K11" , 8:"K12" , 9:"K13" ,10:"K21", 11:"K22", 12:"K23" }
    E0         = [6.6     , 8.8     , 11      ,6.6     , 8.8     , 11       ]
    Pe         = [5.67    , 7.87    , 10.07   ,5.45    , 7.65    , 9.85     ]
    Theta_e    = [15.6    , 11.4    , 10.0    ,17.4    , 12.7    , 10.0     ]
    Pp         = [1.58    , 1.58    , 1.58    ,1.83    , 1.83    , 1.83     ]
    Theta_p    = [44.2    , 42.2    , 41.1    ,47.2    , 45.0    , 43.7     ]

    if len(sys.argv)>1:
        Variable= sys.argv[1]
    else:
        print "run: \n> python mac/ana_deep_hallc.py <run number> <variable>\n or for all \n> python mac/ana_deep_hallc.py <variable=Q2>"
        Variable = "Q2"
    print 'plotting ' + Variable
    i=0
    for run in Kinematics:
        anaAll.append(TAnalysisSIMC( run  , "D" , 1 , 1000 , 20, E0[i], Pe[i], Theta_e[i], Pp[i], Theta_p[i]))
        print run,Kinematics[run]
        i=i+1


Nbins  = 100

# hs-proton arm, # ss-electron arm (for electron at SHMS - 5)
if Operation=="Draw Variable":
    
    if (Variable=="Q2"):
        xAxis = [Variable , 1.5 , 5, "Q ^{2} (GeV/c) ^{2}"]

    elif (Variable=="theta_rq"):
        xAxis = [Variable , 0 , 180 , "#theta(n_{rec}-q) [deg.]"]

    elif (Variable=="Pp_cent"):
        xAxis = [Variable , 1 , 2 , "|p_{p}| [GeV/c]"]

    elif (Variable=="Pm"):
        xAxis = [Variable , 0 , 2 , "|p_{miss}| [GeV/c]"]
        cut   = ROOT.TCut()

    elif (Variable=="Pp"):
        xAxis = ["Pp_cent*(hsdelta/100+1)" , 1 , 3 , "|p_{p}| [GeV/c]"]
    
    elif (Variable=="theta_p"):
        xAxis = ["Thp_cent + (TMath::RadToDeg()*hsxptar)" , 35 , 60 , "#theta_{p} [deg.]"]
    
    elif (Variable=="Pe_cent"):
        xAxis = [Variable , 1 , 12 , "|p_{e}| [GeV/c]"]
            
    elif (Variable=="Pe"):
        xAxis = ["Pe_cent*(ssdelta/100+1)" , 1 , 12 , "|p_{e}| [GeV/c]"]
    
    elif (Variable=="theta_e"):
        xAxis = ["The_cent + (TMath::RadToDeg()*ssxptar)" , 35 , 60 , "#theta_{e} [deg.]"]
    
    elif (Variable=="phase-space"): # p = p(centeral) x (hsdelta/100 + 1)
        xyAxes = ["Pp_cent*(hsdelta/100+1)" , "Thp_cent + (TMath::RadToDeg()*hsxptar)" , 1.4 , 3.3 , 25 , 62 , "|p_{p}| [GeV/c]" , "#theta_{p} [deg.]" ]
        cut    = ROOT.TCut("Weight && (theta_rq<40)  && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu)) && (0.350<Pm && Pm<0.600)")
    
    
    elif (Variable=="eSpectrometerNoCut"):
        xyAxes = ["Pe_cent*(ssdelta/100+1)" , "The_cent + (TMath::RadToDeg()*ssxptar)" , 5 , 11 , 7 , 20 , "|p_{e}| [GeV/c]" , "#theta_{e} [deg.]" ]
        cut = ROOT.TCut()
    
    elif (Variable=="pSpectrometerNoCut"):
        xyAxes = ["Pp_cent*(hsdelta/100+1)" , "Thp_cent + (TMath::RadToDeg()*hsxptar)" , 1.4 , 2.3 , 35 , 52 , "|p_{p}| [GeV/c]" , "#theta_{p} [deg.]" ]
        cut = ROOT.TCut()
    
    elif (Variable=="Pmiss_vs_Q2"):
        xyAxes = ["Q2" , "Pm" , 2.5 , 4.5 , 0.3 , 0.6 , "Q ^{2} (GeV/c) ^{2}" , "|p_{miss}| [GeV/c]" ]
    
    elif (Variable=="Pmiss_vs_Pp"):
        xyAxes = ["Pp_cent*(hsdelta/100+1)" , "Pm" , 0 , 4 , 0. , 1. , "|p_{p}| [GeV/c]" , "|p_{miss}| [GeV/c]" ]
        cut    = ROOT.TCut("Weight && (theta_rq<40)  && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu))")



    c = plot.CreateCanvas(Variable)

    if len(sys.argv)>2:
        
        if 'xAxis' in locals():
            ana.H1(xAxis[0] , cut , "hist" , Nbins , xAxis[1] , xAxis[2] , "run %d"%run ,xAxis[3] , "" ,38)
        elif 'xyAxes' in locals():
            ana.H2(xyAxes[0] , xyAxes[1], cut , "colz" , Nbins , xyAxes[2] , xyAxes[3], Nbins , xyAxes[4] , xyAxes[5] , "run %d"%run ,xyAxes[6] , xyAxes[7] )


    else:

        c.Divide(3,2)
        i=0
        for run in Kinematics:
            c.cd(i+1)
            if 'xAxis' in locals():
                anaAll[i].H1(xAxis[0] , cut , "hist" , Nbins , xAxis[1] , xAxis[2] , Kinematics[run] ,xAxis[3] , "" ,38)
            elif 'xyAxes' in locals():
                anaAll[i].H2(xyAxes[0] , xyAxes[1], cut , "colz" , Nbins , xyAxes[2] , xyAxes[3], Nbins , xyAxes[4] , xyAxes[5] , Kinematics[run] ,xyAxes[6] , xyAxes[7] )
        i=i+1

    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/"+Variable+".pdf")
