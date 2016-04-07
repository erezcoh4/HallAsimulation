import sys
from ROOT import gSystem
gSystem.Load("libHallAsimulation_HallAPackage")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing HallAPackage..."

sys.exit(0)

