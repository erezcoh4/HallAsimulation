{
    
    // using TPlots
    TPlots * ana = new TPlots(
                              "/Users/erezcohen/Desktop/A3/Simulation/simc_files/data/run23.root", // file name
                              "h666"  // tree name
                              );
    
    ana -> CreateCanvas("example");
    h = ana -> H1("hsdelta" // variable
              , "success && Weight"      // TCut
              , "hist"          // drawing option
              , 100       // numebr of bins
              , -80       // Xmin
              , 80        // Xmax
              , "example title"   // title
              , "delta of electron arm [%]" // Xtitle
              , ""    // no y title
              , 38    // color
            );
    
    h -> Scale(0.484390E+09 / (h->GetEntries()));
    Printf("integral of h is %f",h->Integral());
    
    
    ana -> CreateCanvas("example2");
    TAnalysisSIMC * anaSIMC = new TAnalysisSIMC(23, "D", 1 , 1000 , 20 , 11 , 9 , 10 , 1.58 , 43);
    h = anaSIMC -> H1("hsdelta" // variable
                  , "success && Weight"      // TCut
                  , "hist"          // drawing option
                  , 100       // numebr of bins
                  , -80       // Xmin
                  , 80        // Xmax
                  , "example title"   // title
                  , "delta of electron arm [%]" // Xtitle
                  , ""    // no y title
                  , 38    // color
                  );
    Printf("integral of h is %f",h->Integral());
 
    
}