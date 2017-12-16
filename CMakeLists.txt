cmake_minimum_required(VERSION 3.4)
project(ME570_FinalProject)


FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE( OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osgText )
FIND_PACKAGE(Bullet)

INCLUDE_DIRECTORIES( ${OPENSCENEGRAPH_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES(${BULLET_INCLUDE_DIR})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)


SET(MYSOURCE
    osgwidget.h
    osgwidget.cpp
	main.cpp
	mainwindow.h
	mainwindow.cpp
	mainwindow.ui
        Maze.h
        Maze.cpp
        settingswindow.h
        settingswindow.cpp
        settingswindow.ui
        ground.h
        ground.cpp
        BouncyBall.h
        BouncyBall.cpp
        player.h
        player.cpp
        bulletWall.h
        bulletWall.cpp
        instructionsdialog.ui
        instructionsdialog.h
        instructionsdialog.cpp

    )
add_executable(${PROJECT_NAME}
    ${MYSOURCE}
    )


target_link_libraries(${PROJECT_NAME}
    ${OPENSCENEGRAPH_LIBRARIES}	
    Qt5::Widgets
    Qt5::Gui
    ${BULLET_LIBRARIES}
)
