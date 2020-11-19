#include "AnalysisTree/SimpleCut.hpp"
#include "AnalysisTree/Cuts.hpp"
#include "CutsRegistry.hpp"

#include <TMath.h>

int AuAu1_23() {
  using namespace AnalysisTree;

  {
    const char *branch = "event_header";
    const char *name = "default";

    std::vector<SimpleCut> cuts;
    auto vtx_x_cut = RangeCut("event_header.vtx_x", -3.0, 3.0);
    auto vtx_y_cut = RangeCut("event_header.vtx_y", -3.0, 3.0);
    auto vtx_z_cut = RangeCut("event_header.vtx_z", -60.0, 0.0);
    auto vtx_chi2_cut = RangeCut("event_header.vtx_chi2", 0.5, 40);
    auto good_vertex_cut = EqualsCut("event_header.good_vertex_cluster", 1);
    auto good_vertex_candidate_cut = EqualsCut("event_header.good_vertex_candidate", 1);
    auto good_start_cut = EqualsCut("event_header.good_start", 1);
    auto no_pile_up_start_cut = EqualsCut("event_header.no_pile_up_start", 1);
    auto no_veto_cut = EqualsCut("event_header.no_veto", 1);
    auto good_start_veto_cut = EqualsCut("event_header.good_start_veto", 1);
    auto good_start_meta_cut = EqualsCut("event_header.good_start_meta", 1);

    auto min_bias_cut = EqualsCut("event_header.physical_trigger_2", 1);
    auto central_cut = EqualsCut("event_header.physical_trigger_3", 1);
    auto szymon_cut = EqualsCut("event_header.has_passed_szymon_cut", 1);

    const char *min_bias_cuts_name = "hades/auau/1.23/event_cuts/standard/pt2";
    std::string branch_name = "event_header";
    RegisterCuts(min_bias_cuts_name, Cuts(branch_name, {
        vtx_x_cut,
        vtx_y_cut,
        vtx_z_cut,
        vtx_chi2_cut,
        good_vertex_cut,
        good_vertex_candidate_cut,
        good_start_cut,
        no_pile_up_start_cut,
        no_veto_cut,
        good_start_veto_cut,
        good_start_meta_cut,
        min_bias_cut}));

    const char *central_cuts_name = "hades/auau/1.23/event_cuts/standard/pt3";
    RegisterCuts(central_cuts_name, Cuts(branch_name, {
        vtx_x_cut,
        vtx_y_cut,
        vtx_z_cut,
        vtx_chi2_cut,
        good_vertex_cut,
        good_vertex_candidate_cut,
        good_start_cut,
        no_pile_up_start_cut,
        no_veto_cut,
        good_start_veto_cut,
        good_start_meta_cut,
        central_cut}));

    const char *szymon_cuts_name = "hades/auau/1.23/event_cuts/standard/szymon";
    RegisterCuts(szymon_cuts_name, Cuts(branch_name, {
        vtx_x_cut,
        vtx_y_cut,
        vtx_z_cut,
        vtx_chi2_cut,
        good_vertex_cut,
        good_vertex_candidate_cut,
        good_start_cut,
        no_pile_up_start_cut,
        no_veto_cut,
        good_start_veto_cut,
        good_start_meta_cut,
        szymon_cut}));
  }

  return 0;
}


