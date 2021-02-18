//
// Created by eugene on 21/10/2020.
//

#include "CutsRegistry.hpp"
#include "AnalysisTreeCutsGen.hpp"

#include <TROOT.h>
#include <TInterpreter.h>

#if __has_include(<filesystem>)
#   include <filesystem>
#   ifdef __cpp_lib_filesystem
#   define USE_STD_FILESYSTEM
namespace fs = std::filesystem;
#   endif
#endif

#if defined(BOOST_FILESYSTEM_FOUND) && !defined(USE_STD_FILESYSTEM)
#   define BOOST_FILESYSTEM_NO_DEPRECATED
#   include <boost/filesystem.hpp>
#   define USE_BOOST_FILESYSTEM
namespace fs = boost::filesystem;
#endif

AnalysisTree::CutsRegistry &AnalysisTree::CutsRegistry::Instance() {
  static CutsRegistry instance;
  return instance;
}

void AnalysisTree::RegisterCuts(const std::string &name, const Cuts &cuts) {
  CutsRegistry::Instance().RegisterCuts(name, cuts);
}

std::vector<fs::path> GetLookupPaths() {
  std::vector<fs::path> result;
  result.emplace_back(fs::current_path());
//  if (std::string env_path_str{std::getenv(AnalysisTree::CutsEnvironNameForLibraryPath())};
//      !env_path_str.empty()) {
//    try {
//      result.emplace_back(fs::path(env_path_str));
//    } catch (std::exception&e) {}
//  }
  result.emplace_back(AnalysisTree::CutsDefaultLibraryPaths());
  return result;
}

void AnalysisTree::LoadCutsFromFile(const char *path) {
  fs::path p(path);

  if (p.is_relative()) {
    for (auto &lookup_path : GetLookupPaths()) {
      auto full_path = lookup_path / p;

      int err_code;
      auto interpreter = gROOT->GetInterpreter();
      interpreter->AddIncludePath(CurrentSourceDir());
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

namespace Details {

bool IsRegularFile(const fs::directory_entry& e) {
#ifdef USE_BOOST_FILESYSTEM
  return boost::filesystem::is_regular_file(e.path());
#else // USE_STD_FILESYSTEM
  return e.is_regular_file();
#endif
}

}

void AnalysisTree::LoadCutsLibrary(const char *path) {
  fs::path library_path = std::string(path).empty() ? AnalysisTree::CutsDefaultLibraryPaths() : fs::path(path);
  fs::recursive_directory_iterator library_path_iterator(library_path);

  for (auto &p : library_path_iterator) {
    if (Details::IsRegularFile(p) && p.path().extension() == ".C") {
      LoadCutsFromFile(p.path().c_str());
    }
  }

}

