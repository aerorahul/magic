// (C) Copyright 2019- NOAA/NWS/NCEP/EMC

#include "magic/Traits.h"
#include "oops/runs/Run.h"
#include "test/interface/Geometry.h"

int main(int argc,  char ** argv) {
  oops::Run run(argc, argv);
  test::Geometry<magic::Traits> tests;
  return run.execute(tests);
}
