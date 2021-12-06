cmake_minimum_required(VERSION 3.16.3)
project(RATSQL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(QT_BUILD Qt${QT_VERSION})
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/utilities/Token.h
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/algorithms/LevenshteinDistance.cpp
        src/algorithms/LevenshteinDistance.h
        src/datastructures/ParseTree.cpp
        src/datastructures/ParseTree.h
        src/datastructures/Node.cpp
        src/datastructures/Node.h src/utilities/Utils.h src/parsers/ShuntingYardParser.cpp src/parsers/ShuntingYardParser.h)

# Alles hieronder was eigenlijk onnodig?
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

#if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#message("Mac is obv. the best")
#set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/clang_64/lib/cmake/Qt5")
#set(Core_DIR "~/Qt/5.15.2/clang_64/lib/cmake/Qt5Core")
#set(Widgets_DIR "~/Qt/5.15.2/clang_64/lib/cmake/Qt5Widgets")
#set(Gui_DIR "~/Qt/5.15.2/clang_64/lib/cmake/Qt5Gui")
#if (NOT CMAKE_PREFIX_PATH)
#    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
#            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
#endif()

#elseif (WIN32)
# This one is needed for windows
#find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
#target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
#endif ()


# Onnodig?
#if (FALSE)
#    set(DEBUG_SUFFIX)
#    if (CMAKE_BUILD_TYPE MATCHES "Debug")
#        set(DEBUG_SUFFIX "d")
#    endif ()
#    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
#    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
#        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
#            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#        endif ()
#    endif ()
#    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E make_directory
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
#    endif ()
#    foreach (QT_LIB ${REQUIRED_LIBS})
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
#    endforeach (QT_LIB)
#endif ()