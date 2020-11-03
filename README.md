## AnalysisTreeCuts - library of Cuts for AnalysisTree-base projects

### The library Concept

* There is a common library under `${projectRoot}/CutsLibrary`.
* Cuts are defined in macro. Each set of cuts has string name.
* Cuts are loaded by their name.
* There is a registry which loads macro with cuts and builds index.

### How to define your own Cuts

* Find the best place for cuts in the structure `${projectRoot}/CutsLibrary`
* Create ROOT macros with adequate name and corresponding function inside
* Define there your `Cuts` objects and register them with function `RegisterCuts(const char* name, Cuts*)`

### How to get cuts from the registry

__Load entire library:__

```
// load cuts library. Path points to the directory with cuts
LoadCutsFromLibrary(path);
// request Cuts
Cuts c = gCutsRegistry.at("my-fancy-cuts")
// ...or using op-r
Cuts c = gCutsRegistry["my-fancy-cuts"];
```

__Load specific macro__
```
LoadCutsFromFile(path);
// request Cuts
Cuts c = gCutsRegistry.at("my-fancy-cuts")
```

#### What happens behind the scenes

When you call `LoadCutsFromLibrary`, the registry recursively iterates `path` and evaluates __every__ ROOT macro it sees.
Function `RegisterCuts` adds given `Cuts` in the singleton `gCutsRegistry`.

#### Lookup paths

If user provides relative path (e.g. `Hades/AuAu1.23.C`), algorithm will search it
* in `${PWD}` - current directory, or (if no such macro)
* in `${projectRoot}/CutsLibrary`

If user provides absolute path, registry will lookup there.






