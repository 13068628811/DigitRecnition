cmake_minimum_required(VERSION 3.16)

project(number3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(OpenCV_DIR "D:/OpenCV-MinGW-Build-OpenCV-4.5.5-x64" CACHE PATH
    "Directory containing the MinGW OpenCVConfig.cmake")
find_package(OpenCV REQUIRED COMPONENTS core imgproc)

set(PROJECT_SOURCES
        main.cpp

        widget.h
        widget.ui
        widget.cpp
        writelabel.h writelabel.cpp
        penwide.h penwide.cpp penwide.ui
        chosecolor.h chosecolor.cpp chosecolor.ui
        predict.py
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(number3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET number3 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(number3 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(number3
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(number3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(number3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})
if(MSVC)
    target_compile_options(number3 PRIVATE /utf-8)
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.number3)
endif()
set_target_properties(number3 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Put recognition resources beside the executable, including shadow builds.
foreach(resource predict.py mnist.pt runtime.ini)
    configure_file(${resource} ${CMAKE_CURRENT_BINARY_DIR}/${resource} COPYONLY)
    add_custom_command(TARGET number3 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/${resource}"
            "$<TARGET_FILE_DIR:number3>/${resource}"
        VERBATIM
    )
endforeach()
if(WIN32 AND OpenCV_SHARED)
    foreach(component opencv_core opencv_imgproc)
        add_custom_command(TARGET number3 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:${component}>" "$<TARGET_FILE_DIR:number3>"
            VERBATIM
        )
    endforeach()
endif()

include(GNUInstallDirs)
install(TARGETS number3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES predict.py mnist.pt runtime.ini DESTINATION ${CMAKE_INSTALL_BINDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(number3)
endif()
