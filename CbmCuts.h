#include "AnalysisTree/Cuts.h"
#include "AnalysisTree/SimpleCut.h"

namespace AnalysisTree{

Cuts* GetCbmEventCuts(std::string branch, std::string name="CbmGoodEvent") {
  Cuts* event_cuts = new Cuts(std::move(name), std::move(branch));
  SimpleCut vtx_x_cut("vtx_x", -0.5, 0.5);
  SimpleCut vtx_y_cut("vtx_y", -0.5, 0.5);
  SimpleCut vtx_z_cut("vtx_z", -0.03, 0.03);
  SimpleCut vtx_chi2_cut("vtx_chi2", 0.5, 2);
  event_cuts->AddCuts( {vtx_x_cut, vtx_y_cut, vtx_z_cut, vtx_chi2_cut} );
  return event_cuts;
}

Cuts* GetCbmTrackCuts(std::string branch, std::string name="CbmGoodVertexTrack") {
  Cuts* vertex_tracks_cuts = new Cuts(std::move(name), std::move(branch));
  SimpleCut vtx_chi2_track_cut("vtx_chi2", 0, 3);
  SimpleCut nhits_cut("nhits", 4, 100);
  SimpleCut chi2_cut({"chi2", "ndf"}, [](std::vector<double> par){ return par[0]/par[1] < 3; });
  SimpleCut eta_cut("eta", 0.2, 6);

  vertex_tracks_cuts->AddCuts({vtx_chi2_track_cut, nhits_cut, chi2_cut, eta_cut});
  return vertex_tracks_cuts;
};

Cuts* GetCbmCentralityTrackCuts(std::string branch, std::string name="CbmGoodCentralityTrack") {
  Cuts* vertex_tracks_cuts = new Cuts(std::move(name), std::move(branch));
  SimpleCut vtx_chi2_track_cut("vtx_chi2", 0, 3);
  SimpleCut nhits_cut("nhits", 4, 100);
  SimpleCut chi2_cut({"chi2", "ndf"}, [](std::vector<double> par){ return par[0]/par[1] < 10; });
  SimpleCut eta_cut("eta", 0, 3);

  vertex_tracks_cuts->AddCuts({vtx_chi2_track_cut, nhits_cut, chi2_cut, eta_cut});
  return vertex_tracks_cuts;
};

Cuts* GetCbmTofHitsCuts(std::string branch, std::string name="CbmGoodTofHit") {
  Cuts* tof_cuts = new Cuts(std::move(name), std::move(branch));
  SimpleCut tof_cuts_dx("dx", -2, 2);
  SimpleCut tof_cuts_dy("dy", -1, 1);

  tof_cuts->AddCuts({tof_cuts_dx, tof_cuts_dy});
  return tof_cuts;
};

Cuts* GetCbmMcTracksCuts(std::string branch, std::string name="CbmMcPrimaryTrack") {

  Cuts* sim_tracks_cut = new Cuts(std::move(name), std::move(branch));
  SimpleCut mother_id_cut("mother_id", -1000, -0.5);
  sim_tracks_cut->AddCuts({mother_id_cut});

  return sim_tracks_cut;
};

}



