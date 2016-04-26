# run:
# > python mac/ana_simc.py
import Initiation as init
from ctypes import c_int, c_char, c_char_p
import ROOT
from ROOT import TString, TPlots, TAnalysisSIMC , TSIMC
from rootpy.interactive import wait

init.createnewdir()

DoSOSgenerated  = False
DoSOS           = False
DoResolution    = False
DoEventsFeatures= False
DoCompareEvents = False
Do2DResolutions = False
DoMergeFiles    = False
DoOrResolution  = True




plot            = TPlots()
FileNumbers     = (c_int*2)( 5  , 6 ) # c int array
colors          = (c_int*2)( 6  , 4 )
Names           = (c_char_p*2)( "conf. 1" , "conf. 2" )
simc            = TSIMC(len(FileNumbers) , FileNumbers, colors, Names )
i1 = FileNumbers[0]
i2 = FileNumbers[1]
okYcut          = ROOT.TCut("(-5 < hsytar_%d) && (hsytar_%d < 5) && (-5 < hsytar_%d) && (hsytar_%d < 5) && ok_spec_%d && ok_spec_%d"%(i1 ,i1, i2,i2,i1,i2))

if DoSOSgenerated:
    c = plot.CreateCanvas("SOSgenerated","Divide",2,2 )
    c.cd(1)
    simc.DrawQuantity("hsyptari",100 , -0.1 , 0.1   , "#phi_{tag}"  ,"rad"  );
    c.cd(2)
    simc.DrawQuantity("hsxptari",100 , -0.1 , 0.1   , "#theta_{tag}","rad"  );
    c.cd(3)
    simc.DrawQuantity("hsdeltai",50  , -6   , 6     , "#delta"      ,"%"     , False , True , -4.5 , 4.5 );
    c.cd(4)
    simc.DrawQuantity("hsytari" ,50  , -6   , 6     , "y_{tag}"     ,"cm"    , True );
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/SOSgenerated.pdf")

if DoSOS:
    c = plot.CreateCanvas("SOS","Divide",2,2 )
    c.cd(1)
    simc.DrawQuantity("hsyptar",100 , -0.1 , 0.1   , "#phi_{tag}"  ,"rad"  );
    c.cd(2)
    simc.DrawQuantity("hsxptar",100 , -0.1 , 0.1   , "#theta_{tag}","rad"  );
    c.cd(3)
    simc.DrawQuantity("hsdelta",50  , -6   , 6     , "#delta"      ,"%"     , False , True , -4.5 , 4.5 );
    c.cd(4)
    simc.DrawQuantity("hsytar" ,50  , -6   , 6     , "y_{tag}"     ,"cm"    , True );
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/SOS.pdf")

if DoResolution:
    cRes = plot.CreateCanvas("Resolutions","Divide",2,2 )
    cRes.cd(1)
    simc.DrawResolution("hsyptar"       ,100 , -0.003 , 0.003       , 1e3 , "#phi_{tag}"  ,"rad"  );
    cRes.cd(2)
    simc.DrawResolution("hsxptar"       ,100 , -0.006 , 0.006       , 1e3 , "#theta_{tag}","rad"  );
    cRes.cd(3)
    simc.DrawResolution("0.01*hsdelta"  ,100  , -0.0015  , 0.0015   , 1e4 , "#Delta p / p",""  );
    cRes.cd(4)
    simc.DrawResolution("hsytar"        ,100  , -0.3   , 0.3        , 1   , "y_{tag}"     ,"cm"   , True  );
    cRes.Update()
    wait()
    cRes.SaveAs(init.dirname()+"/ResolutionsLogScaleYtg5cm.pdf")

if DoEventsFeatures:
    c = plot.CreateCanvas("EventsFeatures","Divide",1,1 )
    c.cd(1)
    simc.DrawQuantity2D("hsdelta","hsyptar",50  , -6   , 6  ,100 , -0.1 , 0.1   , "#delta"      ,"%"  , "#phi_{tag}"  ,"rad"  );
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/EventsFeatures.pdf")

if DoMergeFiles:
    simc.MergeFiles(FileNumbers[0],FileNumbers[1])

if DoCompareEvents:
    #    simc.MergeFiles(FileNumbers[0],FileNumbers[1])
    c = plot.CreateCanvas("CompareEvents","Divide",2,2 )
    c.cd(1)
    simc.CompareVariable("hsyptar","", FileNumbers[0] , FileNumbers[1] , 100  , -50, 50,  "#phi_{tag}" , "" )
    c.cd(2)
    simc.CompareVariable("hsxptar","", FileNumbers[0] , FileNumbers[1] , 100  , -50, 50, "#theta_{tag}" , "" )
    c.cd(3)
    simc.CompareVariable("0.01*hsdelta","", FileNumbers[0] , FileNumbers[1] , 100  , -40, 40, "#delta" , "" )
    c.cd(4)
    simc.CompareVariable("hsytar","", FileNumbers[0] , FileNumbers[1] , 100  , -40, 40, "y_{tag}" , "" )
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/CompareEvents.pdf")

if Do2DResolutions:
    c = plot.CreateCanvas("CompareEvents","Divide",2,2 )
    c.cd(1)
    simc.CompareVariable2D("hsyptar","", FileNumbers[0] , FileNumbers[1] , 100  , -0.004 , 0.004 ,  "#phi_{tag}" , "rad" )
    c.cd(2)
    simc.CompareVariable2D("hsxptar","", FileNumbers[0] , FileNumbers[1] , 100  , -0.006 , 0.006 ,  "#theta_{tag}" , "rad" )
    c.cd(3)
    simc.CompareVariable2D("0.01*hsdelta","", FileNumbers[0] , FileNumbers[1] , 100  , -0.0015  , 0.0015 ,  "#Delta p / p" , "" )
    c.cd(4)
    simc.CompareVariable2D("hsytar","", FileNumbers[0] , FileNumbers[1] , 100  , -0.3   , 0.3 ,  "y_{tag}" , "cm" )
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/CompareEvents2D.pdf")



if DoOrResolution:
    anaMerged = TAnalysisSIMC("Merged_%d_%d"%(i1 ,i2))
    c = plot.CreateCanvas("Res","Divide",2,2 )
    c.cd(1)
    simc.DrawQuantity("hsdelta",30  , -6  , 6     , "#delta p / p"      ,"%" ) # hsdelta = DP/P [%]
    c.cd(2)
    h2 = anaMerged.H2("(hsdelta_%d-hsdeltai_%d)/(hsdeltai_%d+1)"%(i1,i1,i1),"(hsdelta_%d-hsdeltai_%d)/(hsdeltai_%d+1)"%(i2,i2,i2) , okYcut , "colz" , 100 , -0.06  , 0.15  , 100 , -0.06  , 0.15 , "",  "(p("+Names[0]+") - p(gen))/p(gen)", "(p("+Names[1]+") - p(gen))/p(gen)")
    h2.GetYaxis().SetTitleOffset(1.4)

    c.cd(3)
#    simc.DrawQuantity("hsdelta - hsdeltai",100  , -0.06  , 0.15     , "(p(rec) - p(gen))/ p"      ,"%" ) # hsdelta = DP/P [%]
    # hsdelta = P(rec)/P - 1 -> (P=1.0 GeV/c) -> P(rec) = (1.0 GeV/c) x (hsdelta + 1)
    simc.DrawQuantity("((hsdelta+1) - (hsdeltai+1)) / (hsdeltai+1)",100  , -0.06  , 0.06     , "(p(rec) - p(gen))/ p(gen)"      ,"" )
    c.cd(4)
    simc.DrawQuantity("((hsdelta+1) - (hsdeltai+1)) / (hsdeltai+1)",100  , -0.06  , 0.06     , "(p(rec) - p(gen))/ p(gen)"      ,"" )
#    simc.DrawQuantity("hsdelta - hsdeltai",100  , -0.06  , 0.15     , "(p(rec) - p(gen))/ p"      ,"%" , True ) # hsdelta = DP/P [%]
#    ROOT.gPad.GetYaxis().SetRangeUser(1,gPad.GetYaxis().GetXmax())
#    ROOT.gPad.SetLogy()

    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/Res.pdf")

