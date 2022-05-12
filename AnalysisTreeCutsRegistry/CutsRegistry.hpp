//
// Created by eugene on 21/10/2020.
//

#ifndef CUTS_ANALYSISTREECUTSREGISTRY_CUTSREGISTRY_HPP
#define CUTS_ANALYSISTREECUTSREGISTRY_CUTSREGISTRY_HPP

#include <iostream>
#include <map>
#include <vector>

#include <AnalysisTree/AnalysisTreeVersion.hpp>
#if ANALYSISTREE_VERSION_MAJOR == 1
# include <AnalysisTree/Cuts.hpp>
# define ANALYSISTREE_CUTS ::AnalysisTree::Cuts
#elif ANALYSISTREE_VERSION_MAJOR == 2
# include <AnalysisTree/infra-1.0/Cuts.hpp>
# define ANALYSISTREE_CUTS ::AnalysisTree::Version1::Cuts
#endif

namespace AnalysisTree {

class CutsRegistry {

public:
  static CutsRegistry &Instance();

  struct cuts_exist_exception : public std::exception {};

  [[nodiscard]] std::vector<std::string> GetCutNames() const {
    std::vector<std::string> names;
    names.reserve(cuts_.size());
    for (auto &elem : cuts_) {
      names.emplace_back(elem.first);
    }
    return names;
  }

  void RegisterCuts(const std::string &name, const ANALYSISTREE_CUTS &cuts) {
    auto emplace_result = cuts_.emplace(name, cuts);
    if (!emplace_result.second) {
      throw cuts_exist_exception();
    }
    std::cout << "Registered cut '" << name << "'" << std::endl;
  }

  ANALYSISTREE_CUTS operator[](const std::string &name) {
    return cuts_[name];
  }

  ANALYSISTREE_CUTS at(const std::string &name) {
    return cuts_.at(name);
  }

private:
  std::map<std::string, ANALYSISTREE_CUTS> cuts_;
};


/**
 * @brief Registers cuts under the name into the registry
 * @param name
 * @param cuts
 */
void RegisterCuts(const std::string& name, const ANALYSISTREE_CUTS &cuts);

void LoadCutsLibrary(const char *path = "");

void LoadCutsFromFile(const char *path);

} // namespace AnalysisTree

#define gCutsRegistry (::AnalysisTree::CutsRegistry::Instance())

#endif //CUTS_ANALYSISTREECUTSREGISTRY_CUTSREGISTRY_HPP
