project(Cuts CXX)

HEADERS={
    CbmCuts.h
    ShineCuts.h
}

install(
        FILES
        ${HEADERS}
        DESTINATION
        include
        COMPONENT
        Devel
)