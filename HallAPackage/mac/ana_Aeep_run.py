# run:
# > python mac/ana_deep_hallc.py <run number>

import sys, os, Initiation as init
from ctypes import c_int, c_char, c_char_p
import ROOT
from ROOT import TString, TPlots, TAnalysisSIMC , TSIMC
from rootpy.interactive import wait
init.createnewdir()
plot    = TPlots()


Operation   = "proton-Pmiss Plots1"
Nbins   = 50




if len(sys.argv)>1:
    run     = int(sys.argv[1])
    if len(sys.argv)>2:
        cutname= sys.argv[2]
    if len(sys.argv)>3:
        Variable= sys.argv[3]
#
#if run == 16 or run == 25: # 11 GeV
#    E0      = 11.0
#    Pe_cent = 9.85
#    The_cent= 10.0
#    Pp_cent = 1.83
#    Thp_cent= 43.7
#    Pp_Selected = 2.1
#    Theta_p_Selected = 41.5
#elif run == 20: # 8.8 GeV
#    E0      = 8.8
#    Pe_cent = 7.87
#    The_cent= 11.4
#    Pp_cent = 1.58
#    Thp_cent= 42.2
#    Pp_Selected = 1.6
#    Theta_p_Selected = 42
#elif run == 21: # 8.8 GeV
#    E0      = 8.8
#    Pe_cent = 8.2
#    The_cent= 10.0
#    Pp_cent = 1.58
#    Thp_cent= 42.2
#    Pp_Selected = 1.6
#    Theta_p_Selected = 42
#elif run == 22: # 8.8 GeV
#    E0      = 8.8
#    Pe_cent = 8.03
#    The_cent= 10.4
#    Pp_cent = 1.39
#    Thp_cent= 39.9
#    Pp_Selected = 1.6
#    Theta_p_Selected = 42
#elif run == 23: # 11 GeV
#    E0      = 11
#    Pe_cent = 9.0
#    The_cent= 10.0
#    Pp_cent = 1.83
#    Thp_cent= 43.7
#    Pp_Selected = 2.1
#    Theta_p_Selected = 41.5
#elif run == 24: # 8.8 GeV
#    E0      = 8.8
#    Pe_cent = 7.5
#    The_cent= 11.1
#    Pp_cent = 2.
#    Thp_cent= 41.
#    Pp_Selected = 1.6
#    Theta_p_Selected = 42
#


#ana = TAnalysisSIMC( run  , "D" , 1 , 1152 , 40 , E0 , Pe_cent , The_cent, Pp_cent, Thp_cent )

ana = TAnalysisSIMC( run , "D" )






if cutname == "NoCut":
    cut = ROOT.TCut("Weight")

elif cutname == "success no weight":
    cut = ROOT.TCut("Weight && success")

elif cutname == "success":
    cut = ROOT.TCut("Weight && success")

elif cutname == "success-x_{B}":
    cut = ROOT.TCut("Weight && success && (1.3 < Q2/(2*0.938*nu))")

elif cutname == "Q^{2}-x_{B}":
    cut = ROOT.TCut("Weight && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu))")

elif cutname == "Q^{2}-x_{B}-SHMS_{e}":
    cut = ROOT.TCut("Weight && success && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu))")


elif cutname == "Q^{2}-x_{B}-SHMS_{e}-HMS_{p}":
    cut = ROOT.TCut("Weight && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu)) && (success) && (fabs(Theta_p-%f) < 1.6) && (fabs(Pp - %f) < %f)"%(Theta_p_Selected,Pp_Selected,0.1*Pp_Selected))

elif cutname == "Q^{2}-theta_{rq}-SHMS_{e}-HMS_{p}":
    cut = ROOT.TCut("Weight && (2.5 < Q2) && (theta_rq<40) && (success) && (fabs(Theta_p-%f) < 1.6) && (fabs(Pp - %f) < %f)"%(Theta_p_Selected,Pp_Selected,0.1*Pp_Selected))

elif cutname == "Q^{2}-x_{B}-theta_{rq}-SHMS_{e}-HMS_{p}":
    cut = ROOT.TCut("Weight && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu))  && (theta_rq<40) && (success) && (fabs(Theta_p-%f) < 1.6) && (fabs(Pp - %f) < %f)"%(Theta_p_Selected,Pp_Selected,0.1*Pp_Selected))

elif cutname == "Q^{2}-x_{B}-p_{miss}-#theta_{rq}":
    cut = ROOT.TCut("Weight && (theta_rq<40) && (2.5 < Q2) && (1.3 < Q2/(2*0.938*nu)) && (0.350<Pm)")

else:
    cut = ROOT.TCut()






if Operation=="proton-Pmiss Plots":
    
    c = plot.CreateCanvas("run%d"%run,"Divide",4,3)
    cut.Print()
    c.cd(1)
    ana.H2("Pp"      , "Theta_p", cut , "colz" , Nbins , 1.4 , 3.3, Nbins , 20 , 70 , "run %d"%run , "|p_{p}| [GeV/c]"  , "#theta_{p} [deg.]" )
    c.cd(2)
    ana.H2("Pp"      , "Pm"     , cut , "colz" , Nbins , 1.4 , 3.3, Nbins , 0 , 0.8 , "run %d"%run , "|p_{p}| [GeV/c]"  , "|p_{miss}| [GeV/c]" )
    c.cd(3)
    ana.H2("Theta_p" , "Pm"     , cut , "colz" , Nbins , 20  , 70 , Nbins , 0 , 0.8 , "run %d"%run , "#theta_{p} [deg.]", "|p_{miss}| [GeV/c]" )
    c.cd(4)
    ana.H2("Pe"      , "Theta_e", cut , "colz" , Nbins , 0.9*Pe_cent , 1.1*Pe_cent , Nbins , 0.8*The_cent , 1.3*The_cent , "run %d"%run , "|p_{e}| [GeV/c]"  , "#theta_{e} [deg.]" )
    c.cd(5)
    ana.H1("theta_rq", cut , "hist" , Nbins , 0 , 180, "run %d"%run , "#theta_{rq} [deg.]" , "" , 38)
    c.cd(6)
    ana.H1("Q2"     , cut , "hist" , Nbins , 1 , 5, "run %d"%run , "Q ^{2}  (GeV/c)  ^{2}" , "" , 38)
    c.cd(7)
    ana.H1("Q2/(2*0.938*nu)", cut , "hist" , Nbins , 0 , 3, "run %d"%run , "Bjorken x" , "" , 38)
    c.cd(8)
    ana.H2("Q2"     ,"Q2/(2*0.938*nu)", cut , "colz" , Nbins , 1 , 5 , Nbins , 0 , 3, "run %d"%run , "Q ^{2}  (GeV/c)  ^{2}" , "Bjorken x" )
    c.cd(9)
    ana.H1("zreacti" , cut , "hist" , Nbins , -3 , 3, "run %d"%run , "z(reaction) vertex [cm]" , "" , 38) # for z-reaction see eq. 30 in Hall-A NIM paper
    c.cd(10)
    ana.Text(0.1,0.5,cutname,46,0.05)
    ana.Text(0.1,0.4,"%.0f events"%ana.GetYield(),46,0.05)
    ana.Text(0.1,0.3,"per 1.152 C (1 shift)",46,0.05)

    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/run%d"%run+"_"+cutname+".pdf")



