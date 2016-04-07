# run:
# > python mac/ana_simc.py <target A>

import ROOT , os , sys
from ROOT import TAnalysisSIMC , TSIMC
from rootpy.interactive import wait
ROOT.gStyle.SetOptStat(0000)



DoCuts              = False

Nbins               = 50

if len(sys.argv)>1:
    A   = int(sys.argv[1])
    ana = TAnalysisSIMC()
else:
    print "operate with \n > python mac/ana_simc.py <target A>"
    exit(0)


if DoCuts:
    c = anaEG2.CreateCanvas("canvas","Divide",1,1 )
    c.cd(1)
    ana.H1("" , ROOT.TCut() , "BAR E" , 20 , 0 , 1.1, "","")
    c.Update()
    wait()
    c.SaveAs("~/Desktop/simc.pdf")


