# run:
# > python mac/ana_simc.py
import Initiation as init
from ctypes import c_int, c_char, c_char_p
from ROOT import TString, TPlots, TAnalysisSIMC , TSIMC
from rootpy.interactive import wait

init.createnewdir()

DoSOSgenerated  = False
DoSOS           = False
DoResolution    = False
DoEventsFeatures= False
DoCompareEvents = True



plot            = TPlots()
FileNumbers     = (c_int*2)( 5  , 6 ) # c int array
colors          = (c_int*2)( 6  , 4 )
Names           = (c_char_p*2)( "configuration 1" , "configuration 2" )
N               = len(FileNumbers)
simc            = TSIMC(N , FileNumbers, colors, Names )



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



if DoCompareEvents:
    c = plot.CreateCanvas("CompareEvents","Divide",1,1 )
    c.cd(1)
#    simc.MergeFiles()
#    simc.CompareVariable("hsdeltai","", 5 , 6 ,50  , -10   , 10 , "#delta"      ,"%"   )
    simc.CompareVariable("hsdelta","ok_spec", 5 , 6 ,50  , -10   , 10 , "event number" , "" )
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/CompareEvents.pdf")

