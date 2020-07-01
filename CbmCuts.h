#include "AnalysisTree/Cuts.hpp"
#include "AnalysisTree/SimpleCut.hpp"

namespace AnalysisTree{

Cuts* GetCbmEventCuts(std::string branch, std::string name="CbmGoodEvent") {
  Cuts* event_cuts = new Cuts(std::move(name));
  SimpleCut vtx_x_cut({branch, "vtx_x"}, -0.5, 0.5);
  SimpleCut vtx_y_cut({branch, "vtx_y"}, -0.5, 0.5);
  SimpleCut vtx_z_cut({branch, "vtx_z"}, -0.03, 0.03);
  SimpleCut vtx_chi2_cut({branch, "vtx_chi2"}, 0.5, 2);
  event_cuts->AddCuts( {vtx_x_cut, vtx_y_cut, vtx_z_cut, vtx_chi2_cut} );
  return event_cuts;
}

Cuts* GetCbmTrackCuts(std::string branch, std::string name="CbmGoodVertexTrack") {
  Cuts* vertex_tracks_cuts = new Cuts(std::move(name));
  SimpleCut vtx_chi2_track_cut({branch, "vtx_chi2"}, 0, 3);
  SimpleCut nhits_cut({branch, "nhits"}, 4, 100);
  SimpleCut chi2_cut({{branch, "chi2"}, {branch, "ndf"}}, [](std::vector<double> par){ return par[0]/par[1] < 3; });
  SimpleCut eta_cut({branch, "eta"}, 0.2, 6);

  vertex_tracks_cuts->AddCuts({vtx_chi2_track_cut, nhits_cut, chi2_cut, eta_cut});
  return vertex_tracks_cuts;
};

Cuts* GetCbmCentralityTrackCuts(std::string branch, std::string name="CbmGoodCentralityTrack") {
  Cuts* vertex_tracks_cuts = new Cuts(std::move(name));
  SimpleCut vtx_chi2_track_cut({branch, "vtx_chi2"}, 0, 3);
  SimpleCut nhits_cut({branch, "nhits"}, 4, 100);
  SimpleCut chi2_cut({{branch, "chi2"}, {branch, "ndf"}}, [](std::vector<double> par){ return par[0]/par[1] < 10; });
  SimpleCut eta_cut({branch, "eta"}, 0, 3);

  vertex_tracks_cuts->AddCuts({vtx_chi2_track_cut, nhits_cut, chi2_cut, eta_cut});
  return vertex_tracks_cuts;
};

Cuts* GetCbmTofHitsCuts(std::string branch, std::string name="CbmGoodTofHit") {
  Cuts* tof_cuts = new Cuts(std::move(name));
  SimpleCut tof_cuts_dx({branch, "dx"}, -2, 2);
  SimpleCut tof_cuts_dy({branch, "dy"}, -1, 1);

  tof_cuts->AddCuts({tof_cuts_dx, tof_cuts_dy});
  return tof_cuts;
};

Cuts* GetCbmMcTracksCuts(std::string branch, std::string name="CbmMcPrimaryTrack") {
  Cuts* sim_tracks_cut = new Cuts(std::move(name), {{{branch, "mother_id"}, -1}});
  return sim_tracks_cut;
};

}



