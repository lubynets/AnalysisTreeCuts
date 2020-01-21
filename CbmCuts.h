#include "AnalysisTree/Cuts.h"
#include "AnalysisTree/SimpleCut.h"

AnalysisTree::Cuts* GetCbmEventCuts() {
  AnalysisTree::SimpleCut vtx_x("vtx_x", -10, 10);
  AnalysisTree::SimpleCut vtx_y("vtx_y", -10, 10);
  AnalysisTree::SimpleCut vtx_z("vtx_z", -10, 10);
  AnalysisTree::SimpleCut vtx_chi2("vtx_chi2", 0.5, 3);
  AnalysisTree::Cuts* event_cuts{ new AnalysisTree::Cuts("RecEventHeader")};
  event_cuts->AddCuts({vtx_x, vtx_y, vtx_z, vtx_chi2});
  return event_cuts;
}

AnalysisTree::Cuts* GetCbmTrackCuts() {
  AnalysisTree::SimpleCut vtx_chi2("vtx_chi2", -1000, 18.6);
  AnalysisTree::Cuts* rec_track_cuts{ new AnalysisTree::Cuts("VtxTracks")};
  rec_track_cuts->AddCut(vtx_chi2);
  return rec_track_cuts;
};
