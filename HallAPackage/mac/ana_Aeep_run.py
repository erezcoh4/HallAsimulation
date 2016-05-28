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

Pp_Select = Pp_cent
Theta_p_Select = Thp_cent


Weight      = "Weight*%f"%(ana.GetNormfact()/ana.Nentries)
print "Weight = ",Weight

Q2          = "2.5 < Q2"
Xb          = "1.3 < Q2/(2*0.938*nu)"
theta_rq    = "theta_rq<40"
Select_p    = "(fabs(Pp-%f)<%f)"%(Pp_Select,0.1*Pp_Select)
Select_theta= "(fabs(Theta_p-%f)<1.6)"%Theta_p_Select
Pmiss       = "0.35 < Pm && Pm < 0.55"
SHMSFid     = "(-0.04 < hsyptar && hsyptar < 0.04) && (-0.024 < hsxptar && hsxptar < 0.024)"
HMSthFid    = "(-0.06 < ssyptar && ssyptar < 0.06)"
HMSphFid    = "(-0.035 < ssxptar && ssxptar < 0.035)"
delta_e     = "(-10 < hsdelta && hsdelta < 22)"
delta_p     = "(-10 < ssdelta && ssdelta < 10)"
WernerCuts  = "(-0.05 < hsyptar && hsyptar < 0.05) && (-0.025 < hsxptar && hsxptar < 0.025) && (-8 < hsdelta && hsdelta < 4) && (-0.06 < ssyptar && ssyptar < 0.06) && (-0.035 < ssxptar && ssxptar < 0.035) && (-10 < ssdelta && ssdelta < 10) && (1.3 < Q2/(2*0.938*nu) && Q2/(2*0.938*nu) < 1.4) && (4. < Q2 && Q2 < 4.5)"


if cutname == "NoCut":
    cut = ROOT.TCut("%s*( %s )"%(Weight,SHMSFid))

elif cutname == "Werner-Cuts":
    cut = ROOT.TCut("%s*( %s )"%(Weight,WernerCuts))


elif cutname == "Select_{p}-Select_{#theta}":
    cut = ROOT.TCut("%s*( %s && %s && %s && %s && %s )"%(Weight , SHMSFid , delta_e , HMSphFid , Select_p , Select_theta ))


elif cutname == "x_{B}":
    cut = ROOT.TCut("%s*( %s && %s && %s && %s )"%(Weight , SHMSFid , delta_e , HMSphFid , Xb ))


elif cutname == "x_{B}-Q^{2}":
    cut = ROOT.TCut("%s*( %s && %s && %s && %s && %s)"%(Weight , SHMSFid , delta_e , HMSphFid , Xb , Q2 ))


elif cutname == "Q^{2}":
    cut = ROOT.TCut("%s*( %s && %s && %s && %s )"%(Weight , SHMSFid , delta_e , HMSphFid , Q2 ))



elif cutname == "Q^{2}-Select_{p}-Select_{#theta}-Fid_{HMS}":
    cut = ROOT.TCut("%s*( %s && %s && %s && %s && %s && %s && %s )"%(Weight , SHMSFid , delta_e , HMSphFid , Q2 , Select_p , Select_theta , HMSthFid))



elif cutname == "Q^{2}-x_{B}-Select_{p}":
    cut = ROOT.TCut("%s*( %s && %s && %s && %s && %s && %s )"%(Weight , SHMSFid , delta_e , HMSphFid , Q2 , Xb , Select_p ))


elif cutname == "Q^{2}-x_{B}-Select_{p}-Select_{#theta}":
    cut = ROOT.TCut("%s*( %s && %s && %s && %s && %s && %s && %s )"%(Weight , SHMSFid , delta_e , HMSphFid , Q2 , Xb , Select_p , Select_theta))


elif cutname == "Q^{2}-x_{B}-Select_{p}-Select_{#theta}-Fid_{HMS}":
    cut = ROOT.TCut("%s*( %s && %s && %s && %s && %s && %s && %s && %s && %s )"%(Weight , SHMSFid , delta_e , HMSphFid , Q2 , Xb , Select_p , Select_theta , HMSthFid , delta_p ))


elif cutname == "Q^{2}-x_{B}-Select_{p}-Select_{#theta}-Fid_{HMS}-p_{miss}":
    cut = ROOT.TCut("%s*( %s && %s && %s && %s && %s && %s && %s && %s && %s && %s  )"%(Weight , SHMSFid , delta_e , HMSphFid , Q2 , Xb , Select_p , Select_theta , HMSthFid , delta_p , Pmiss ))


elif cutname == "Q^{2}-x_{B}-Select_{p}-Select_{#theta}-Fid_{HMS}-p_{miss}-theta_{rq}":
    cut = ROOT.TCut("%s*( %s && %s && %s && %s && %s && %s && %s && %s && %s && %s && %s )"%(Weight , SHMSFid , delta_e , HMSphFid , Q2 , Xb , Select_p , Select_theta , HMSthFid , delta_p , Pmiss , theta_rq ))


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
    h=ana.H1("Pm" , cut , "hist" , 40 , 0 , 1.6, "run %d"%run , "|p_{miss}| [GeV/c]" , "" , 38)
    ROOT.gPad.SetLogy()
    c.cd(11)
    ana.Text(0.1,0.5,cutname,46,0.07)
    ana.Text(0.1,0.4,"%.0f events"%ana.GetYield(),46,0.07)
    ana.Text(0.1,0.3,"per %.0f mC"%ana.GetQ(),46,0.07)
    print "h  integral= ",h.Integral()
    print "yield = ",ana.GetYield()
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




