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
    SimpleCut vtx_x_cut({branch, "vtx_x"}, -3.0, 3.0);
    SimpleCut vtx_y_cut({branch, "vtx_y"}, -3.0, 3.0);
    SimpleCut vtx_z_cut({branch, "vtx_z"}, -60.0, 0.0);
    SimpleCut vtx_chi2_cut({branch, "vtx_chi2"}, 0.5, 40);
    SimpleCut good_vertex_cut({branch, "good_vertex_cluster"}, 0.5, 1.5);
    SimpleCut good_vertex_candidate_cut({branch, "good_vertex_candidate"}, 0.5, 1.5);
    SimpleCut good_start_cut({branch, "good_start"}, 0.5, 1.5);
    SimpleCut no_pile_up_start_cut({branch, "no_pile_up_start"}, 0.5, 1.5);
    SimpleCut no_veto_cut({branch, "no_veto"}, 0.5, 1.5);
    SimpleCut good_start_veto_cut({branch, "good_start_veto"}, 0.5, 1.5);
    SimpleCut good_start_meta_cut({branch, "good_start_meta"}, 0.5, 1.5);

    SimpleCut min_bias_cut({branch, "physical_trigger_2"}, 0.5, 1.5);
    SimpleCut central_cut({branch, "physical_trigger_3"}, 0.5, 1.5);
    SimpleCut szymon_cut({branch, "has_passed_szymon_cut"}, 0.5, 1.5);

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


