<<<<<<< HEAD
add_library(btor2parser
  btor2parser/btor2parser.c
)
target_include_directories(btor2parser PRIVATE .)
set_target_properties(btor2parser PROPERTIES PUBLIC_HEADER btor2parser/btor2parser.h)
install(
  TARGETS btor2parser
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
target_link_libraries(btorsim btor2parser)
target_compile_options(btorsim PRIVATE -Wall -Wfatal-errors)
install(TARGETS btorsim DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(catbtor catbtor.c)
target_link_libraries(catbtor btor2parser)
install(TARGETS catbtor DESTINATION ${CMAKE_INSTALL_BINDIR})

if(BUILD_BTOR2AIGER)
  add_library(btor2aiger
    btor2aiger.cpp
    ${CMAKE_SOURCE_DIR}/deps/aiger/aiger.c
  )
  add_executable(btor2aiger-bin
    btor2aiger_main.cpp
  )
  target_include_directories(btor2aiger PRIVATE . ${CMAKE_SOURCE_DIR}/deps/aiger)
  target_compile_options(btor2aiger PRIVATE -std=c++11 -Wall -g -g3 -ggdb)
  target_link_libraries(btor2aiger btor2parser Boolector::boolector)
  install(
    TARGETS btor2aiger
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )
  target_include_directories(btor2aiger-bin PRIVATE . ${CMAKE_SOURCE_DIR}/deps/aiger)
  target_compile_options(btor2aiger-bin PRIVATE -std=c++11 -Wall -g -g3 -ggdb)
  target_link_libraries(btor2aiger-bin btor2aiger)
  set_target_properties(btor2aiger-bin PROPERTIES OUTPUT_NAME btor2aiger)
  install(TARGETS btor2aiger-bin DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

add_executable(btorsplit btorsplit.cpp)
install(TARGETS btorsplit DESTINATION ${CMAKE_INSTALL_BINDIR})
||||||| 1df768d
=======
add_library(btor2parser
  btor2parser/btor2parser.c
)
target_include_directories(btor2parser PRIVATE .)
set_target_properties(btor2parser PROPERTIES PUBLIC_HEADER btor2parser/btor2parser.h)
install(
  TARGETS btor2parser
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
target_link_libraries(btorsim btor2parser)
target_compile_options(btorsim PRIVATE -Wall -Wfatal-errors)
install(TARGETS btorsim DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(catbtor catbtor.c)
target_link_libraries(catbtor btor2parser)
install(TARGETS catbtor DESTINATION ${CMAKE_INSTALL_BINDIR})

if(BUILD_BTOR2AIGER)
  add_executable(btor2aiger
    btor2aiger.cpp
    ${CMAKE_SOURCE_DIR}/deps/aiger/aiger.c
  )
  target_include_directories(btor2aiger PRIVATE . ${CMAKE_SOURCE_DIR}/deps/aiger)
  target_compile_options(btor2aiger PRIVATE -std=c++11 -Wall -g -g3 -ggdb)
  target_link_libraries(btor2aiger btor2parser Boolector::boolector)
  install(TARGETS btor2aiger DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

add_executable(btorsplit btorsplit.cpp)
install(TARGETS btorsplit DESTINATION ${CMAKE_INSTALL_BINDIR})
>>>>>>> master
