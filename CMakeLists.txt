cmake_minimum_required(VERSION 3.16)
project(Physics)

set(CMAKE_CXX_STANDARD 14)

set(OpenGlLinkers -lglut -lGLU -lGL -lalut)

add_executable(Physics src/main.cpp src/Entity.h src/Entity.cpp src/util/Vec2D.cpp src/util/Vec2D.h src/CollisionManager/CollisionManager.h src/CollisionManager/Simple/SimpleCollisionManager.cpp src/CollisionManager/Simple/SimpleCollisionManager.h src/CollisionManager/QuadTree/QuadTreeCollisionManager.cpp src/CollisionManager/QuadTree/QuadTreeCollisionManager.h src/CollisionManager/QuadTree/Box.cpp src/CollisionManager/QuadTree/Box.h src/Scene.cpp src/Scene.h src/Components/Component.h src/Components/PhysicsComponent/PhysicsComponent.cpp src/Components/PhysicsComponent/PhysicsComponent.h src/Components/GraphicsComponent/GraphicsComponent.cpp src/Components/GraphicsComponent/GraphicsComponent.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include(FindOpenGL.cmake)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(Physics ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
