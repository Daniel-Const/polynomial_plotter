cmake_minimum_required (VERSION 2.6)
project (polyonmial)

# GLUT Package
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)


# OpenGL Package
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

# Source files
set(SOURCE_FILES
    src/main.cpp
    src/polynomial.cpp
    src/point.cpp
)

add_executable(polynomial ${SOURCE_FILES})

target_link_libraries(polynomial ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
