add_library(btor2parser.LIB STATIC
  btor2parser/btor2parser.c
)
target_include_directories(btor2parser.LIB PRIVATE .)
set_target_properties(btor2parser.LIB PROPERTIES PUBLIC_HEADER btor2parser/btor2parser.h)
set_target_properties(btor2parser.LIB
        PROPERTIES OUTPUT_NAME "btor2parser")
install(
  TARGETS btor2parser.LIB
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

add_executable(btorsim
  btorsim/btorsimam.cpp
  btorsim/btorsimstate.cpp
  btorsim/btorsimvcd.cpp
  btorsim/btorsimhelpers.cpp
  btorsim/btorsim.cpp
  btorsim/btorsimbv.c
  btorsim/btorsimrng.c
)
target_include_directories(btorsim PRIVATE .)
target_link_libraries(btorsim btor2parser.LIB)
target_compile_options(btorsim PRIVATE -Wall -Wfatal-errors)
install(TARGETS btorsim DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(catbtor catbtor.c)
target_link_libraries(catbtor btor2parser.LIB)
install(TARGETS catbtor DESTINATION ${CMAKE_INSTALL_BINDIR})

if(BUILD_BTOR2AIGER)
  add_library (aiger.LIB STATIC
    ${BTOR_DEPS_DIR}/aiger/aiger.c
  )
  add_library(btor2aiger.LIB STATIC
    btor2aiger.cpp
  )
  add_executable(btor2aiger-bin
    btor2aiger_main.cpp
  )
  target_include_directories(aiger.LIB PRIVATE . ${BTOR_DEPS_DIR}/aiger)
  target_compile_options(aiger.LIB PRIVATE  -Wall -g -g3 -ggdb)
  target_include_directories(btor2aiger.LIB PRIVATE . ${BTOR_DEPS_DIR}/aiger)
  target_compile_options(btor2aiger.LIB PRIVATE -std=c++17 -Wall -g -g3 -ggdb)
  target_link_libraries(btor2aiger.LIB btor2parser.LIB aiger.LIB Boolector::boolector)
  install(
    TARGETS btor2aiger.LIB
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )
  target_include_directories(btor2aiger-bin PRIVATE . ${BTOR_DEPS_DIR}/aiger)
  target_compile_options(btor2aiger-bin PRIVATE -std=c++17 -Wall -g -g3 -ggdb)
  target_link_libraries(btor2aiger-bin btor2aiger.LIB aiger.LIB)
  set_target_properties(btor2aiger-bin PROPERTIES OUTPUT_NAME btor2aiger-bin)
  install(TARGETS btor2aiger-bin DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

add_executable(btorsplit btorsplit.cpp)
install(TARGETS btorsplit DESTINATION ${CMAKE_INSTALL_BINDIR})
