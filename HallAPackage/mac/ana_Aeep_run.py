# run:
# > python mac/ana_deep_hallc.py <run number>

import sys, os, Initiation as init
from ctypes import c_int, c_char, c_char_p
import ROOT
from ROOT import TString, TPlots, TAnalysisSIMC , TSIMC
from rootpy.interactive import wait
init.createnewdir()
plot    = TPlots()


Operation   = "Plots For Proposal" #"Pmiss" # "Kinematics" # "Plots For Proposal"
Nbins       = 50
cutname     = ""



if len(sys.argv)>1:
    run     = int(sys.argv[1])
    if len(sys.argv)>2:
        cutname= sys.argv[2]



ana = TAnalysisSIMC( run , "D" )

Pe_cent = ana.GetPe()
Pp_cent = ana.GetPp()
The_cent = ana.GetThe()
Thp_cent = ana.GetThp()

Pp_Select = ana.GetPp() # run 46 is what we use for the proposal - 1.8
Theta_p_Select = ana.GetThp() # run 46 is what we use for the proposal - 43.0


Q2          = "2.5 < Q2"
Q2LowPmiss  = "2. < Q2"
Xb          = "1.2 < Q2/(2*0.938*nu)"
theta_rq    = "theta_rq<50"
Select_p    = "(fabs(Pp-%f)<%f)"%(Pp_Select,0.1*Pp_Select)
Select_theta= "(fabs(Theta_p-%f)<1.6)"%Theta_p_Select
Pmiss       = "0.35 < Pm"
LowPmiss    = "Pm < 0.25"
# electron arm = hs... , hadron arm = ss....
SHMSFid     = "(-0.04 < hsyptar && hsyptar < 0.04) && (-0.024 < hsxptar && hsxptar < 0.024) "
HMSthFid    = "(-0.06 < ssyptar && ssyptar < 0.06)"
HMSphFid    = "(-0.035 < ssxptar && ssxptar < 0.035)"
delta_e     = "(-10 < hsdelta && hsdelta < 22)"
delta_p     = "(-10 < ssdelta && ssdelta < 10)"
WernerCuts  = "(-0.05 < hsyptar && hsyptar < 0.05) && (-0.025 < hsxptar && hsxptar < 0.025) && (-8 < hsdelta && hsdelta < 4) && (-0.06 < ssyptar && ssyptar < 0.06) && (-0.035 < ssxptar && ssxptar < 0.035) && (-10 < ssdelta && ssdelta < 10) && (1.3 < Q2/(2*0.938*nu) && Q2/(2*0.938*nu) < 1.4) && (4. < Q2 && Q2 < 4.5) && (-0.01 < Em && Em < 0.025)"
RanCuts     = "(-0.028 < hsyptar && hsyptar < 0.028) && (-0.060 < hsxptar && hsxptar < 0.060) && (-4.5 < hsdelta && hsdelta < 4.5) && (-0.028 < ssyptar && ssyptar < 0.028) && (-0.060 < ssxptar && ssxptar < 0.060) && (-4.5 < ssdelta && ssdelta < 4.5) && ( 1. < Q2/(2*0.938*nu) )" 


if cutname == "NoCut":
    cuts = "success"


elif cutname == "electron-fiducials":
    cuts = "( %s )"%( SHMSFid  )


elif cutname == "electron-fiducials-HMS_{#phi}":
    cuts = "( %s && %s )"%( SHMSFid , HMSphFid  )


elif cutname == "electron-fiducials-HMS_{#phi}-select_{p}-select_{#theta}":
    cuts = "( %s && %s && %s && %s )"%( SHMSFid , HMSphFid , Select_p , Select_theta )

elif cutname == "electron-fiducials-HMS_{#phi}-select_{p}-select_{#theta}-LowPmiss": # for low Pmiss kinematics
    cuts = "( %s && %s && %s && %s && %s )"%( SHMSFid , HMSphFid , Select_p , Select_theta , LowPmiss)

elif cutname == "electron-fiducials-HMS_{#phi}-select_{p}-select_{#theta}-LowPmiss-Q^{2}": # for low Pmiss kinematics
    cuts = "( %s && %s && %s && %s && %s && %s )"%( SHMSFid , HMSphFid , Select_p , Select_theta , LowPmiss , Q2LowPmiss)


elif cutname == "electron-fiducials-HMS_{#phi}-p_{miss}":
    cuts = "( %s && %s && %s )"%( SHMSFid , HMSphFid  , Pmiss)


elif cutname == "electron-fiducials-HMS_{#phi}-x_{B}-p_{miss}":
    cuts = "( %s && %s && %s && %s )"%( SHMSFid , HMSphFid , Xb , Pmiss )


elif cutname == "electron-fiducials-HMS_{#phi}-x_{B}-select_{p}-p_{miss}":
    cuts = "( %s && %s && %s && %s && %s )"%( SHMSFid , HMSphFid , Xb , Select_p , Pmiss)


elif cutname == "electron-fiducials-HMS_{#phi}-x_{B}-select_{p}-select_{#theta}-p_{miss}":
    cuts = "( %s && %s && %s && %s && %s && %s )"%( SHMSFid , HMSphFid , Xb , Select_p , Select_theta , Pmiss)


elif cutname == "electron-fiducials-HMS_{#phi}-x_{B}-select_{p}-select_{#theta}-p_{miss}-theta_{rq}":
    cuts = "( %s && %s && %s && %s && %s && %s && %s )"%( SHMSFid , HMSphFid , Xb , Select_p , Select_theta , Pmiss , theta_rq)



elif cutname == "electron-fiducials-HMS_{#phi}-Q^{2}-select_{p}-select_{#theta}-LowPmiss":
    cuts = "( %s && %s && %s && %s && %s && %s )"%( SHMSFid , HMSphFid , Q2 , Select_p , Select_theta , LowPmiss )



elif cutname == "Ran-Cuts":
    cuts = RanCuts


elif cutname == "Werner-Cuts":
    cuts = WernerCuts

else:
    cut = ROOT.TCut()





if Operation=="Kinematics":
    
    c = plot.CreateCanvas("run%d"%run,"Divide",4,3)
    c.cd(1)
    ana.H2("Pp"      , "Theta_p", cuts , "colz" , Nbins , Pp_cent-1.5 , Pp_cent+.5, Nbins , Thp_cent-3 , Thp_cent+3 , "run %d"%run , "|p_{p}| [GeV/c]"  , "#theta_{p} [deg.]" )
    c.cd(2)
    ana.H2("Pp"      , "Pm"     , cuts , "colz" , Nbins , Pp_cent-1.5 , Pp_cent+.5, Nbins , 0 , 1.3 , "run %d"%run , "|p_{p}| [GeV/c]"  , "|p_{miss}| [GeV/c]" )
    c.cd(3)
    ana.H2("Theta_p" , "Pm"     , cuts , "colz" , Nbins , Thp_cent-3 , Thp_cent+3 , Nbins , 0 , 1.3 , "run %d"%run , "#theta_{p} [deg.]", "|p_{miss}| [GeV/c]" )
    c.cd(4)
    ana.H2("Pe"      , "Theta_e", cuts , "colz" , Nbins , 0.9*Pe_cent , 1.1*Pe_cent , Nbins , The_cent-2 , The_cent+2 , "run %d"%run , "|p_{e}| [GeV/c]"  , "#theta_{e} [deg.]" )
    c.cd(5)
    ana.H1("theta_rq", cuts , "hist" , Nbins , 0 , 180, "run %d"%run , "#theta_{rq} [deg.]" , "" , 38)
    c.cd(6)
    ana.H1("Q2"     , cuts , "hist" , Nbins , 1 , 5, "run %d"%run , "Q ^{2}  (GeV/c)  ^{2}" , "" , 38)
    c.cd(7)
    ana.H1("Q2/(2*0.938*nu)", cuts , "hist" , Nbins , 0 , 3, "run %d"%run , "Bjorken x" , "" , 38)
    c.cd(8)
    ana.H2("Q2" ,"Q2/(2*0.938*nu)", cuts , "colz" , Nbins , 1 , 5 , Nbins , 0 , 3, "run %d"%run , "Q ^{2}  (GeV/c)  ^{2}" , "Bjorken x" )
    c.cd(9)
    ana.H1("zreacti" , cuts , "hist" , Nbins , -1 , 1, "run %d"%run , "z(reaction) vertex [cm]" , "" , 38) # for z-reaction see eq. 30 in Hall-A NIM paper
    c.cd(10)
    ana.H1("Pm" , cuts , "hist" , 40 , 0 , 1.6, "run %d"%run , "|p_{miss}| [GeV/c]" , "" , 38)
    ROOT.gPad.SetLogy()
    c.cd(11)
    ana.H1("Em" , cuts , "hist" , 80 , -1 , 1, "run %d"%run , "E_{miss} [GeV]" , "" , 38)
    c.cd(12)
    ana.Text(0.1,0.5,cutname,46,0.07)
    ana.Text(0.1,0.4,"%.0f events"%ana.GetYield(),46,0.07)
    ana.Text(0.1,0.3,"per %.0f mC"%ana.GetQ(),46,0.07)
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/run%d"%run+"_"+cutname+".pdf")



elif Operation=="Pmiss":
    

    c = plot.CreateCanvas("run%d"%run)
#    h=ana.H1("Pm" , cuts , "hist" , 40 , 0 , 1.6, "" , "|p_{miss}| [GeV/c]" , "" , 38)
    h=ana.H1("Pm" , cuts , "hist" , 30 , 0 , .6, "" , "|p_{miss}| [GeV/c]" , "" , 38)
    ana.Text(0.4,0.8*h.GetMaximum(),"%.0f events per %.0f mC"%(ana.GetYield(),ana.GetQ()),46,0.03)
    ROOT.gPad.SetLogy()


    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/run%d"%run+"_"+cutname+".pdf")





elif Operation=="Plots For Proposal":

    Nbins = 100
    if len(sys.argv)>2:
        Variable= sys.argv[2]
        if len(sys.argv)>3:
            Nbins= int(sys.argv[3])

    cuts = "( %s && %s && %s && %s && %s && %s && %s )"%( SHMSFid , HMSphFid , Xb , Select_p , Select_theta , Pmiss , theta_rq)
    c = plot.CreateCanvas("run%d"%run,"Divide",4,3)


    if (Variable=="Q2"):
        xAxis = [Variable , 1.5 , 5, "Q ^{2} (GeV/c) ^{2}"]

    elif (Variable=="Xb"):
        xAxis = ["Q2/(2*0.938*nu)" , 0.9 , 2, "x_{B}"]
    
    elif (Variable=="Pmiss"):
        xAxis = ["Pm" , 0.2 , 0.8, "|p_{miss}| [GeV/c]"]

    elif (Variable=="SHMS"):
        xyAxes = ["Pe" , "Theta_e" , 0.9*Pe_cent , 1.1*Pe_cent , 0.8*The_cent , 1.3*The_cent , "|p_{e}| [GeV/c]" , "#theta(e) [deg.]" ]
    
    elif (Variable=="HMS"):
        xyAxes = ["Pp" , "Theta_p" , 0.85*Pp_cent , 1.15*Pp_cent , 0.9*Thp_cent , 1.2*Thp_cent , "|p_{p}| [GeV/c]" , "#theta(p) [deg.]" ]
    

    elif (Variable=="Xb_vs_Q2"):
        xyAxes = ["Q2" , "Q2/(2*0.938*nu)" , 1.5 , 5 , 0.9 , 2 , "Q ^{2} (GeV/c) ^{2}" , "x_{B}" ]
    
    elif (Variable=="theta_rq"):
        xAxis = [Variable , 0 , 60, "#theta_{rq} [deg.]"]



    if 'xAxis' in locals():
        ana.H1(xAxis[0] , cuts , "hist" , Nbins , xAxis[1] , xAxis[2] , "" ,xAxis[3] , "" ,38)
    elif 'xyAxes' in locals():
        ana.H2(xyAxes[0] , xyAxes[1], cuts , "colz" , Nbins , xyAxes[2] , xyAxes[3], Nbins , xyAxes[4] , xyAxes[5] , "" ,xyAxes[6] , xyAxes[7] )

    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/ProposalPlots/"+Variable+".pdf")




