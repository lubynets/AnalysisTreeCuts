#include "AnalysisTree/Cuts.h"
#include "AnalysisTree/SimpleCut.h"

AnalysisTree::Cuts* GetShineEventCuts() {

  const float big_number = 1000000000.f; //std::numeric_limits<float>::infinity()

  AnalysisTree::SimpleCut vtx_x("vtx_x", -0.740, 0.131);
  AnalysisTree::SimpleCut vtx_y("vtx_y", -0.664, 0.022);
  AnalysisTree::SimpleCut e_psd("Epsd", 0.0000001, big_number);
  AnalysisTree::SimpleCut fitted_vtx("fitted_vtx", 0, 0);

//  AnalysisTree::SimpleCut bpd1_x("bpd1_x", -0.5, 0.3);
//  AnalysisTree::SimpleCut bpd1_y("bpd1_y", -0.7, 1.1);
//  AnalysisTree::SimpleCut bpd2_x("bpd2_x", -0.7, -0.1);
//  AnalysisTree::SimpleCut bpd2_y("bpd2_y", -0.4, 0.3);
//  AnalysisTree::SimpleCut bpd3_x("bpd3_x", -1.05, 0.35);
//  AnalysisTree::SimpleCut bpd3_y("bpd3_y", -0.55, 0.05);

  AnalysisTree::SimpleCut s1("s1", 115, 175);
  AnalysisTree::SimpleCut s2("s2", 150, 500);
  AnalysisTree::SimpleCut s1_s2({"s1", "s2"}, [](std::vector<double>& s) { return s[0]*1.258 + s[1] < 390; } );

  AnalysisTree::SimpleCut wfa_s1("wfa_s1", 4000, big_number );
  AnalysisTree::SimpleCut wfa_t4("wfa_t4", 4000, big_number );

  AnalysisTree::SimpleCut t2_t4({"t2", "t4"}, [](std::vector<double>& t) { return t[0] || t[1]; } );

  AnalysisTree::SimpleCut vtx_z_magic({"vtx_z"}, [](std::vector<double>& v) { return v[0]>-594 && v[0]<-590 && fabs(v[0]+591.9000244) > 0.00001; });

  AnalysisTree::Cuts* event_cuts{ new AnalysisTree::Cuts("RecEventHeader")};
  event_cuts->AddCuts({vtx_x, vtx_y, vtx_z_magic, e_psd, s1, s2, s1_s2, t2_t4, wfa_s1/*, wfa_s4*/});
  return event_cuts;
}

AnalysisTree::Cuts* GetShineTrackCuts() {
  AnalysisTree::SimpleCut dcax("dcax", -2-0.083, 2-0.083);
  AnalysisTree::SimpleCut dcay("dcay", -1+0.006, 1+0.006);
  AnalysisTree::SimpleCut hits({"nhits_vtpc1", "nhits_vtpc2", "nhits_mtpc"},
                               [](std::vector<double>& hits) { return hits[0]+hits[1]>=15 && hits[0]+hits[1]+hits[2]>=30; } );

  AnalysisTree::SimpleCut hits_pot({"nhits_vtpc1", "nhits_vtpc2", "nhits_mtpc", "nhits_pot_vtpc1", "nhits_pot_vtpc2", "nhits_pot_mtpc"},
                                   [](std::vector<double>& hits) {
                                     const double total = hits[0]+hits[1]+hits[2];
                                     const double total_pot = hits[3]+hits[4]+hits[5];
                                     return total/total_pot>0.55 && total/total_pot<1.1;  } );

  AnalysisTree::Cuts* rec_track_cuts{ new AnalysisTree::Cuts("VtxTracks")};
  rec_track_cuts->AddCuts({dcax, dcay, hits, hits_pot});
  return rec_track_cuts;
};
