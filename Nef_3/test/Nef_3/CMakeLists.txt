# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Nef_3_Tests )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET)

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

    include_directories (BEFORE "include")

  # create a target per cppfile
  file(GLOB cppfiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
  foreach(cppfile ${cppfiles})
    create_single_source_cgal_program( "${cppfile}" )
  endforeach()

  if(BUILD_TESTING)
    set_tests_properties(
        execution___of__Nef_3_problematic_construction
        execution___of__test_nef_3_io_Cartesian
        execution___of__test_nef_3_io_Cartesian_Lazy
        execution___of__test_nef_3_io_EPEC
        execution___of__test_nef_3_io_Homogeneous
        execution___of__test_nef_3_io_Homogenoeus_Lazy
        execution___of__test_with_extended_homogeneous
        execution___of__test_with_homogeneous
        execution___of__test_with_lazy
      PROPERTIES RESOURCE_LOCK Nef_3_Tests_IO)
  endif()
else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

