# run:
# > python mac/ana_deep_hallc.py <run number>

import sys, os, Initiation as init
from ctypes import c_int, c_char, c_char_p
import ROOT
from ROOT import TString, TPlots, TAnalysisSIMC , TSIMC
from rootpy.interactive import wait
init.createnewdir()

Operation   = "proton-Pmiss Plots"

E0      = 11.0
Pe_cent = 9.85
The_cent= 10.0
Pp_cent = 1.83
Thp_cent= 43.7
Nbins   = 50
plot    = TPlots()



if len(sys.argv)>1:
    run     = int(sys.argv[1])
    ana     = TAnalysisSIMC( run  , "D" , 1 , 1000 , 20, E0 , Pe_cent , The_cent, Pp_cent, Thp_cent)
    if len(sys.argv)>2:
        cutname= sys.argv[2]
    if len(sys.argv)>3:
        Variable= sys.argv[3]



if cutname == "NoCut":
    cut = ROOT.TCut("Weight")

elif cutname == "success":
    cut = ROOT.TCut("Weight && success")

elif cutname == "Q^{2}-x_{B}":
    cut = ROOT.TCut("Weight && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu))")

elif cutname == "Q^{2}-x_{B}-success":
    cut = ROOT.TCut("Weight && success && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu))")

elif cutname == "Q^{2}-x_{B}-SHMS_{e}":
    cut = ROOT.TCut("Weight && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu)) && (8.5<Theta_e && Theta_e<11.5) && (9.1<Pe && Pe<9.8)")

elif cutname == "Q^{2}-x_{B}-SHMS_{e}-HMS_{p}":
    cut = ROOT.TCut("Weight && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu)) && (success) && (fabs(Theta_p-41.5) < 1.6) && (fabs(Pp - 2.1) < 0.21)")

elif cutname == "Q^{2}-x_{B}-p_{miss}-#theta_{rq}":
    cut = ROOT.TCut("Weight && (theta_rq<40) && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu)) && (0.350<Pm)")


elif cutname == "Q^{2}-x_{B}-p_{miss}-#theta_{rq}-SHMS_{e}":
    cut = ROOT.TCut("Weight && (theta_rq<40) && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu)) && (0.350<Pm) && (8.5<Theta_e && Theta_e<11.5) && (9.1<Pe && Pe<9.8)")

else:
    cut = ROOT.TCut()






if Operation=="proton-Pmiss Plots":
    
    c = plot.CreateCanvas("run%d"%run,"Divide",4,2)
    cut.Print()
    c.cd(1)
    ana.H2("Pp"      , "Theta_p", cut , "colz" , Nbins , 1.4 , 3.3, Nbins , 20 , 70 , "run %d"%run , "|p_{p}| [GeV/c]"  , "#theta_{p} [deg.]" )
    c.cd(2)
    ana.H2("Pp"      , "Pm"     , cut , "colz" , Nbins , 1.4 , 3.3, Nbins , 0 , 0.8 , "run %d"%run , "|p_{p}| [GeV/c]"  , "|p_{miss}| [GeV/c]" )
    c.cd(3)
    ana.H2("Theta_p" , "Pm"     , cut , "colz" , Nbins , 20  , 70 , Nbins , 0 , 0.8 , "run %d"%run , "#theta_{p} [deg.]", "|p_{miss}| [GeV/c]" )
    c.cd(4)
    ana.H2("Pe"      , "Theta_e", cut , "colz" , Nbins , 8 , 12, Nbins , 6 , 13 , "run %d"%run , "|p_{e}| [GeV/c]"  , "#theta_{e} [deg.]" )
    c.cd(5)
    ana.H1("theta_rq", cut , "hist" , Nbins , 0 , 180, "run %d"%run , "#theta_{rq} [deg.]" , "" , 38)
    c.cd(6)
    ana.H1("Q2", cut , "hist" , Nbins , 2 , 5, "run %d"%run , "Q ^{2}  (GeV/c)  ^{2}" , "" , 38)
    c.cd(7)
    ana.H1("Q2/(2*0.938*nu)", cut , "hist" , Nbins , 0 , 3, "run %d"%run , "Bjorken x" , "" , 38)
    c.cd(8)
    ana.Text(0.2,0.5,cutname,46,0.07)
    ana.Text(0.2,0.4,"%.0f events / 1C"%ana.GetYield(),46,0.07)

    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/"+cutname+".pdf")



