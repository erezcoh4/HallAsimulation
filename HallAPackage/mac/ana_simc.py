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
Names           = (c_char_p*2)( "configuration 1" , "configuration 2" )
simc            = TSIMC(len(FileNumbers) , FileNumbers, colors, Names )



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
    c = plot.CreateCanvas("Res","Divide",1,2 )
    c.cd(1)
    simc.DrawRes("hsdelta",100  , -5  , 5     , "#delta"      ,"%" , True )
    c.cd(2)
    i1 = FileNumbers[0]
    i2 = FileNumbers[1]
    anaMerged = TAnalysisSIMC("Merged_%d_%d"%(i1 ,i2))
    anaMerged.H2("hsdeltai_5","hsdeltai_6" , ROOT.TCut("") , "colz" , 100 , -10 , 10  , 100 , -10 , 10  )
#    anaMerged.H1("fabs(hsdelta_%d-hsdeltai_%d) / fabs(hsdelta_%d-hsdeltai_%d)"%(i1,i1,i2,i2)
#                    , ROOT.TCut("(-5 < hsytar_5) && (hsytar_5 < 5) && (-5 < hsytar_6) && (hsytar_6 < 5)  && ok_spec_5 && ok_spec_6 && fabs(hsytari_5-hsytari_6)<0.01") , "hist" , 100 , -2 , 3 , "ratio of (rec.-gen.)" , "|#delta(%d)-#delta(gen.)| / |#delta(%d)-#delta(gen.)|"%(i1 ,i2)  )
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/Res.pdf")

