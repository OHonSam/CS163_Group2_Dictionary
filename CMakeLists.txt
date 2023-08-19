cmake_minimum_required(VERSION 3.5)

project(Qt_UI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Qt_UI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc

		myscreen.h myscreen.cpp

		html_creator.h html_creator.cpp

		historyscreen.h historyscreen.cpp historyscreen.ui

		homescreen.h homescreen.cpp homescreen.ui

		searchscreen.h searchscreen.cpp searchscreen.ui

		favlistscreen.h favlistscreen.cpp favlistscreen.ui

		editscreen.h editscreen.cpp editscreen.ui

		addnewword.h addnewword.cpp addnewword.ui

		quiz.h quiz.cpp quiz.ui
    )
# Define target properties for Andro
#    set_property(TARGET Qt_UI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Qt_UI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Qt_UI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Qt_UI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Qt_UI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Qt_UI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Qt_UI)
endif()

## Self

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

include(CTest)
enable_testing()

add_subdirectory(source)
add_subdirectory(tests)

target_link_libraries(${PROJECT_NAME} PUBLIC Dict)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
