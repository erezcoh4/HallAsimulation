# run:
# > python mac/ana_deep_hallc.py <run number>

import sys, os, Initiation as init
from ctypes import c_int, c_char, c_char_p
import ROOT
from ROOT import TString, TPlots, TAnalysisSIMC , TSIMC
from rootpy.interactive import wait
init.createnewdir()
plot    = TPlots()


Operation   = "Kinematics" #"Werner kinematics" # "Kinematics" # "Plots For Proposal"
Nbins       = 50

cutname = ""



if len(sys.argv)>1:
    run     = int(sys.argv[1])
    if len(sys.argv)>2:
        cutname= sys.argv[2]



ana = TAnalysisSIMC( run , "D" )

Pe_cent = ana.GetPe()
Pp_cent = ana.GetPp()
The_cent = ana.GetThe()
Thp_cent = ana.GetThp()
if run==28:
    Pp_Select = 2.31
    Theta_p_Select = 53.5
elif run==37:
    Pp_Select = 2.993
    Theta_p_Select = 35.1
else:
    Pp_Select = 2.
    Theta_p_Select = 44


WeightCut   = ROOT.TCut("Weight")
SuccessCut  = ROOT.TCut("success")
Q2Cut       = ROOT.TCut("2.5 < Q2")
XbCut       = ROOT.TCut("1.3 < Q2/(2*0.938*nu)")
theta_rqCut = ROOT.TCut("theta_rq<40")
Select_pCut = ROOT.TCut("(fabs(Pp-%f)<%f)"%(Pp_Select,0.1*Pp_Select))
Select_thCut= ROOT.TCut("(fabs(Theta_p-%f)<1.6)"%Theta_p_Select)
PmissCut    = ROOT.TCut("0.35 < Pm && Pm < 0.55")
SHMSFidCut  = ROOT.TCut("(-0.04 < hsyptar && hsyptar < 0.04) && (-0.024 < hsxptar && hsxptar < 0.024)")
HMSthFidCut = ROOT.TCut("(-0.06 < ssyptar && ssyptar < 0.06)")
HMSphFidCut = ROOT.TCut("(-0.035 < ssxptar && ssxptar < 0.035)")
delta_eCut  = ROOT.TCut("(-10 < hsdelta && hsdelta < 22)")
delta_pCut  = ROOT.TCut("(-10 < ssdelta && ssdelta < 10)")

if cutname == "NoCut":
    cut = WeightCut + SHMSFidCut + delta_eCut + HMSphFidCut

elif cutname == "Select_{p}-Select_{#theta}":
    cut = WeightCut + SuccessCut + SHMSFidCut + delta_eCut + HMSphFidCut + Select_pCut + Select_thCut

elif cutname == "x_{B}":
    cut = WeightCut + SuccessCut + SHMSFidCut + delta_eCut + XbCut + HMSphFidCut


elif cutname == "Q^{2}-x_{B}":
    cut = WeightCut + SuccessCut + SHMSFidCut + delta_eCut + XbCut + Q2Cut + HMSphFidCut


elif cutname == "Q^{2}-x_{B}-Select_{p}":
    cut = WeightCut + SuccessCut + SHMSFidCut + delta_eCut + XbCut + Q2Cut + HMSphFidCut + Select_pCut


elif cutname == "Q^{2}-x_{B}-Select_{p}-Select_{#theta}":
    cut = WeightCut + SuccessCut + SHMSFidCut + delta_eCut + XbCut + Q2Cut + HMSphFidCut + Select_pCut + Select_thCut


elif cutname == "Q^{2}-x_{B}-Select_{p}-Select_{#theta}-Fid_{HMS}":
    cut = WeightCut + SuccessCut + SHMSFidCut + delta_eCut + XbCut + Q2Cut + HMSphFidCut + Select_pCut + Select_thCut + PmissCut


elif cutname == "Q^{2}-x_{B}-Select_{p}-Select_{#theta}-Fid_{HMS}-p_{miss}":
    cut = WeightCut + SuccessCut + SHMSFidCut + delta_eCut + XbCut + Q2Cut + HMSphFidCut + Select_pCut + Select_thCut + HMSthFidCut + PmissCut


elif cutname == "Q^{2}-x_{B}-Select_{p}-Select_{#theta}-Fid_{HMS}-p_{miss}-theta_{rq}":
    cut = WeightCut + SuccessCut + SHMSFidCut + delta_eCut + XbCut + Q2Cut + HMSphFidCut + Select_pCut + Select_thCut + HMSthFidCut + PmissCut + theta_rqCut



elif cutname == "Werner-Cuts":
    cut = ROOT.TCut("Weight && success && (-0.05 < hsyptar && hsyptar < 0.05) && (-0.025 < hsxptar && hsxptar < 0.025) && (-8 < hsdelta && hsdelta < 4) && (-0.06 < ssyptar && ssyptar < 0.06) && (-0.035 < ssxptar && ssxptar < 0.035) && (-10 < ssdelta && ssdelta < 10) && (1.3 < Q2/(2*0.938*nu) && Q2/(2*0.938*nu) < 1.4) && (4. < Q2 && Q2 < 4.5)")

else:
    cut = ROOT.TCut()





if Operation=="Kinematics":
    
    c = plot.CreateCanvas("run%d"%run,"Divide",4,3)
    cut.Print()
    c.cd(1)
    ana.H2("Pp"      , "Theta_p", cut , "colz" , Nbins , Pp_cent-1.5 , Pp_cent+1.5, Nbins , Thp_cent-10 , Thp_cent+10 , "run %d"%run , "|p_{p}| [GeV/c]"  , "#theta_{p} [deg.]" )
    c.cd(2)
    ana.H2("Pp"      , "Pm"     , cut , "colz" , Nbins , Pp_cent-1.5 , Pp_cent+1.5, Nbins , 0 , 1.3 , "run %d"%run , "|p_{p}| [GeV/c]"  , "|p_{miss}| [GeV/c]" )
    c.cd(3)
    ana.H2("Theta_p" , "Pm"     , cut , "colz" , Nbins , Thp_cent-10 , Thp_cent+10 , Nbins , 0 , 1.3 , "run %d"%run , "#theta_{p} [deg.]", "|p_{miss}| [GeV/c]" )
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
    ana.H1("zreacti" , cut , "hist" , Nbins , -1 , 1, "run %d"%run , "z(reaction) vertex [cm]" , "" , 38) # for z-reaction see eq. 30 in Hall-A NIM paper
    c.cd(10)
    ana.H1("Pm" , cut , "hist" , 40 , 0 , 1.6, "run %d"%run , "|p_{miss}| [GeV/c]" , "" , 38)
    ROOT.gPad.SetLogy()
    c.cd(11)
    ana.Text(0.1,0.5,cutname,46,0.07)
    ana.Text(0.1,0.4,"%.0f events"%ana.GetYield(),46,0.07)
    ana.Text(0.1,0.3,"per %.0f mC"%ana.GetQ(),46,0.07)

    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/run%d"%run+"_"+cutname+".pdf")



elif Operation=="Werner kinematics":
    
    cut = ROOT.TCut("Weight && success && (-0.05 < hsyptar && hsyptar < 0.05) && (-0.025 < hsxptar && hsxptar < 0.025) && (-8 < hsdelta && hsdelta < 4) && (-0.06 < ssyptar && ssyptar < 0.06) && (-0.035 < ssxptar && ssxptar < 0.035) && (-10 < ssdelta && ssdelta < 10) && (1.3 < Q2/(2*0.938*nu) && Q2/(2*0.938*nu) < 1.4) && (4. < Q2 && Q2 < 4.5)")
    

    c = plot.CreateCanvas("run%d"%run)
    ana.H1("Pm" , cut , "hist" , 40 , 0 , 1.6, "run %d"%run , "|p_{miss}| [GeV/c]" , "" , 38)
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

    cut = WeightCut + SuccessCut + SHMSFidCut + delta_eCut + XbCut + Q2Cut + HMSphFidCut + Select_pCut + Select_thCut + HMSthFidCut + PmissCut + theta_rqCut
    c = plot.CreateCanvas("run%d"%run,"Divide",4,3)


    if (Variable=="Q2"):
        xAxis = [Variable , 1.5 , 5, "Q ^{2} (GeV/c) ^{2}"]

    elif (Variable=="Xb"):
        xAxis = ["Q2/(2*0.938*nu)" , 0.9 , 2, "x_{B}"]
    
    elif (Variable=="Pmiss"):
        xAxis = ["Pm" , 0.2 , 0.8, "|p_{miss}| [GeV/c]"]

    elif (Variable=="SHMS"):
        xyAxes = ["Pe" , "Theta_e" , 0.9*Pe_cent , 1.1*Pe_cent , 0.9*The_cent , 1.3*The_cent , "|p_{e}| [GeV/c]" , "#theta(e) [deg.]" ]
    
    elif (Variable=="HMS"):
        xyAxes = ["Pp" , "Theta_p" , 0.85*Pp_cent , 1.15*Pp_cent , 0.9*Thp_cent , 1.2*Thp_cent , "|p_{p}| [GeV/c]" , "#theta(p) [deg.]" ]
    

    elif (Variable=="Xb_vs_Q2"):
        xyAxes = ["Q2" , "Q2/(2*0.938*nu)" , 1.5 , 5 , 0.9 , 2 , "Q ^{2} (GeV/c) ^{2}" , "x_{B}" ]
    
    elif (Variable=="theta_rq"):
        xAxis = [Variable , 0 , 60, "#theta_{rq} [deg.]"]



    if 'xAxis' in locals():
        ana.H1(xAxis[0] , cut , "hist" , Nbins , xAxis[1] , xAxis[2] , "" ,xAxis[3] , "" ,38)
    elif 'xyAxes' in locals():
        ana.H2(xyAxes[0] , xyAxes[1], cut , "colz" , Nbins , xyAxes[2] , xyAxes[3], Nbins , xyAxes[4] , xyAxes[5] , "" ,xyAxes[6] , xyAxes[7] )

    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/ProposalPlots/"+Variable+".pdf")




