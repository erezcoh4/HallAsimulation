# run:
# > python mac/ana_simc.py

import ROOT , os , sys
from ctypes import c_int, c_char
from ROOT import TPlots, TAnalysisSIMC , TSIMC
from rootpy.interactive import wait
ROOT.gStyle.SetOptStat(0000)



DoSOS           = False
DoResolution    = False

simc            = TSIMC()
plot            = TPlots()
FileNumbers     = (c_int*3)( 1 , 2 , 3 ) # c int array
Titles          = [ ROOT.TString("") , ROOT.TString("") , ROOT.TString("") ]
N               = len(FileNumbers)

if DoSOS:
    c = plot.CreateCanvas("SOS","Divide",2,2 )
    c.cd(1)
    simc.DrawQuantity("hsyptar",100 , -0.1 , 0.1   , "#phi_{tag}"  ,"rad"  , N , FileNumbers);
    c.cd(2)
    simc.DrawQuantity("hsxptar",100 , -0.1 , 0.1   , "#theta_{tag}","rad"  , N , FileNumbers);
    c.cd(3)
    simc.DrawQuantity("hsdelta",50  , -6   , 6     , "#delta"      ,"%"    , N , FileNumbers);
    c.cd(4)
    simc.DrawQuantity("hsytar" ,50  , -6   , 6     , "y_{tag}"     ,"cm"   , N , FileNumbers , True);
    c.Update()
    wait()
    c.SaveAs("~/Desktop/SOS.pdf")


if DoResolution:
    cRes = plot.CreateCanvas("Resolutions","Divide",2,2 )
    cRes.cd(1)
    simc.DrawResolution("hsyptar",100 , -0.002 , 0.002      , "#phi_{tag}"  ,"rad"  , N , FileNumbers);
    cRes.cd(2)
    simc.DrawResolution("hsxptar",100 , -0.005 , 0.005      , "#theta_{tag}","rad"  , N , FileNumbers);
    cRes.cd(3)
    simc.DrawResolution("hsdelta",100  , -0.15  , 0.15      , "#Delta p / p","%"    , N , FileNumbers);
    cRes.cd(4)
    simc.DrawResolution("hsytar" ,100  , -0.2   , 0.2       , "y_{tag}"     ,"cm"   , N , FileNumbers);
    cRes.Update()
    wait()
    cRes.SaveAs("~/Desktop/Resolutions.pdf")

