cmake_minimum_required(VERSION 3.16.3)
project(RATSQL)
project(RATSQL_SHUNTING_YARD)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(QT_BUILD Qt${QT_VERSION})
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(RATSQL
        src/main.cpp
        src/utilities/Token.h
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/algorithms/LevenshteinDistance.cpp
        src/algorithms/LevenshteinDistance.h
        src/datastructures/ParseTree.cpp
        src/datastructures/ParseTree.h
        src/datastructures/Node.cpp
        src/datastructures/Node.h
        src/utilities/Utils.h
        src/parsers/ShuntingYardParser.cpp
        src/parsers/ShuntingYardParser.h)

add_executable(RATSQL_SHUNTING_YARD
        src/main_shunting_yard.cpp
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/parsers/ShuntingYardParser.cpp
        src/parsers/ShuntingYardParser.h)

# Alles hieronder was eigenlijk onnodig?
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(RATSQL ${REQUIRED_LIBS_QUALIFIED})


