
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

PROJECT(Paint3D)

find_package(VTK COMPONENTS 
  vtkCommonColor
  vtkCommonCore
  vtkFiltersSources
  vtkInteractionStyle
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  vtkGUISupportQt
  vtkRenderingQt
  QUIET
)

if(NOT VTK_FOUND)
  message(FATAL_ERROR "Paint3D: ${VTK_NOT_FOUND_MESSAGE}")
endif()

if(NOT(vtkGUISupportQt_LOADED OR TARGET VTK::GUISupportQt))
  message(FATAL_ERROR "Paint3D: VTK not built with Qt support.")
endif()

if(NOT DEFINED VTK_QT_VERSION)
  set(VTK_QT_VERSION 5)
endif()

set(qt_components Core Gui Widgets)
if(${VTK_QT_VERSION} VERSION_GREATER_EQUAL 6)
  list(APPEND qt_components OpenGLWidgets)
endif()
list(SORT qt_components)
# We have ui files, so this will also bring in the macro:
#   qt5_wrap_ui or qt_wrap_ui from Widgets.
find_package(Qt${VTK_QT_VERSION} QUIET
  REQUIRED COMPONENTS ${qt_components}
)

foreach(_qt_comp IN LISTS qt_components)
  list(APPEND qt_modules "Qt${VTK_QT_VERSION}::${_qt_comp}")
endforeach()

message (STATUS "VTK_VERSION: ${VTK_VERSION}, Qt Version: ${Qt${VTK_QT_VERSION}Widgets_VERSION}")

if (VTK_VERSION VERSION_LESS "8.90.0")
# Instruct CMake to run moc automatically when needed.
  set(CMAKE_AUTOMOC ON)
else()
# Instruct CMake to run moc and uic automatically when needed.
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
endif()

set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})
include_directories(${FORMS_DIR})

file(GLOB UI_FILES "${FORMS_DIR}/*.ui")
file(GLOB QT_WRAP "${INCLUDE_DIR}/*.h")
file(GLOB CXX_FILES "${SOURCE_DIR}/*.cxx")

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})


if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  # CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
  add_executable(Paint3D WIN32 MACOSX_BUNDLE
    ${CXX_FILES} ${QT_WRAP})
  if (Qt${VTK_QT_VERSION}Widgets_VERSION VERSION_LESS "5.11.0")
    qt5_use_modules(Paint3D ${qt_components})
  else()
    target_link_libraries(Paint3D ${qt_modules})
  endif()
  target_link_libraries(Paint3D ${VTK_LIBRARIES})
else()
  # Prevent a "command line is too long" failure in Windows.
  set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
  # CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
  add_executable(Paint3D WIN32 MACOSX_BUNDLE
    ${CXX_FILES} ${QT_WRAP})
  if (Qt${VTK_QT_VERSION}Widgets_VERSION VERSION_LESS "5.11.0")
    qt5_use_modules(Paint3D ${qt_components})
  else()
    target_link_libraries(Paint3D ${qt_modules})
  endif()
  target_link_libraries(Paint3D ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS Paint3D
    MODULES ${VTK_LIBRARIES}
  )
endif()
