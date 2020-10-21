//
// Created by eugene on 21/10/2020.
//

#include "CutsRegistry.hpp"
#include "AnalysisTreeCutsGen.hpp"

#include <filesystem>
#include <TROOT.h>

namespace fs = std::filesystem;

AnalysisTree::CutsRegistry &AnalysisTree::CutsRegistry::Instance() {
  static CutsRegistry instance;
  return instance;
}


void AnalysisTree::RegisterCuts(const char *name, const Cuts &cuts) {
  CutsRegistry::Instance().RegisterCuts(name, cuts);
}

std::vector<fs::path> GetLookupPaths() {
  std::vector<fs::path> result;
  result.push_back(fs::current_path());
  result.emplace_back(AnalysisTree::CutsDefaultLibraryPaths());
  return result;
}

void AnalysisTree::LoadCutsFromFile(const char *path) {
  const std::vector<fs::path> lookup_paths(GetLookupPaths());

  fs::path p(path);

  if (p.is_relative()) {
    for (auto &lookup_path : lookup_paths) {
      auto full_path = lookup_path / p;

      int err_code;
      gROOT->Macro(full_path.c_str(), &err_code, false);
      if (err_code == 0) {
        std::cout << "Loaded cuts from " << full_path << std::endl;
        break;
      }
    }
  } else {
    int err_code;
    gROOT->Macro(p.c_str(), &err_code, false);
    if (err_code == 0) {
      std::cout << "Loaded cuts from " << p << std::endl;
    }
  }
}

void AnalysisTree::LoadCutsLibrary(const char *path) {
  fs::path library_path = std::string(path).empty()? AnalysisTree::CutsDefaultLibraryPaths() : fs::path(path);
  fs::recursive_directory_iterator library_path_iterator(library_path);

  for (auto &p : library_path_iterator) {
    if (p.is_regular_file() && p.path().extension() == ".C") {
      LoadCutsFromFile(p.path().c_str());
    }
  }

}

