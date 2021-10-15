//
// Created by eugene on 21/10/2020.
//

#ifndef CUTS_ANALYSISTREECUTSREGISTRY_CUTSREGISTRY_HPP
#define CUTS_ANALYSISTREECUTSREGISTRY_CUTSREGISTRY_HPP

#include <iostream>
#include <map>
#include <vector>

#include <AnalysisTree/Cuts.hpp>

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

  void RegisterCuts(const std::string &name, const Cuts &cuts) {
    auto emplace_result = cuts_.emplace(name, cuts);
    if (!emplace_result.second) {
      throw cuts_exist_exception();
    }
    std::cout << "Registered cut '" << name << "'" << std::endl;
  }

  Cuts operator[](const std::string &name) {
    return cuts_[name];
  }

  Cuts at(const std::string &name) {
    return cuts_.at(name);
  }

private:
  std::map<std::string, Cuts> cuts_;
};


/**
 * @brief Registers cuts under the name into the registry
 * @param name
 * @param cuts
 */
void RegisterCuts(const std::string& name, const Cuts &cuts);

void LoadCutsLibrary(const char *path = "");

void LoadCutsFromFile(const char *path);

} // namespace AnalysisTree

#define gCutsRegistry (::AnalysisTree::CutsRegistry::Instance())

#endif //CUTS_ANALYSISTREECUTSREGISTRY_CUTSREGISTRY_HPP
