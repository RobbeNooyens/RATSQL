cmake_minimum_required(VERSION 3.16.3)
project(RATSQL_CMD)
project(RATSQL_GUI)
project(RATSQL_TESTS)
project(RATSQL_SHUNTING_YARD)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#set (QT_COMPILER_FLAGS -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64")
if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm64" AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_PREFIX_PATH "~/Qt/6.2.2/macos/lib/cmake")
endif()
set(QT_VERSION 6)
set(QT_BUILD Qt${QT_VERSION})
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)

add_executable(RATSQL_CMD
        src/main_cmd.cpp
        src/utilities/Token.h
        src/utilities/Utils.h
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/algorithms/LevenshteinDistance.cpp
        src/algorithms/LevenshteinDistance.h
        src/datastructures/ParseTree.cpp
        src/datastructures/ParseTree.h
        src/datastructures/Node.cpp
        src/datastructures/Node.h
        src/datastructures/RAExpression.cpp
        src/datastructures/RAExpression.h
        src/datastructures/SQLStatement.cpp
        src/datastructures/SQLStatement.h
        src/datastructures/ParseSettings.h
        src/datastructures/ReplaceSuggestion.h
        src/parsers/ShuntingYardParser.cpp
        src/parsers/ShuntingYardParser.h
        src/parsers/Parsers.h
        src/parsers/Parsers.cpp
        src/io/CommandHandler.h
        src/io/CommandHandler.cpp
        )

add_executable(RATSQL_GUI
        src/main_gui.cpp
        src/utilities/Token.h
        src/utilities/Utils.h
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/algorithms/LevenshteinDistance.cpp
        src/algorithms/LevenshteinDistance.h
        src/datastructures/ParseTree.cpp
        src/datastructures/ParseTree.h
        src/datastructures/Node.cpp
        src/datastructures/Node.h
        src/datastructures/RAExpression.cpp
        src/datastructures/RAExpression.h
        src/datastructures/SQLStatement.cpp
        src/datastructures/SQLStatement.h
        src/datastructures/ParseSettings.h
        src/datastructures/ReplaceSuggestion.h
        src/parsers/ShuntingYardParser.cpp
        src/parsers/ShuntingYardParser.h
        src/parsers/Parsers.h
        src/parsers/Parsers.cpp
        src/io/GUIHandler.cpp
        src/io/GUIHandler.h
        src/gui/MainWindow.cpp
        src/gui/MainWindow.h
        src/gui/InputBox.cpp
        src/gui/InputBox.h
        src/gui/OutputBox.cpp
        src/gui/OutputBox.h
        src/gui/Buttons.cpp
        src/gui/Buttons.h)

add_executable(RATSQL_TESTS
        src/main_tests.cpp
        src/utilities/Token.h
        src/utilities/Utils.h
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/algorithms/LevenshteinDistance.cpp
        src/algorithms/LevenshteinDistance.h
        src/datastructures/ParseTree.cpp
        src/datastructures/ParseTree.h
        src/datastructures/Node.cpp
        src/datastructures/Node.h
        src/datastructures/RAExpression.cpp
        src/datastructures/RAExpression.h
        src/datastructures/SQLStatement.cpp
        src/datastructures/SQLStatement.h
        src/datastructures/ParseSettings.h
        src/datastructures/ReplaceSuggestion.h
        src/parsers/ShuntingYardParser.cpp
        src/parsers/ShuntingYardParser.h
        src/parsers/Parsers.h
        src/parsers/Parsers.cpp
        src/tests/TestManager.cpp
        src/tests/TestManager.h
        src/tests/Test.h
        src/tests/LevenshteinTest.cpp
        src/tests/LevenshteinTest.h
        src/tests/ShuntingYardTest.cpp src/tests/ShuntingYardTest.h src/tests/Test.cpp)

add_executable(RATSQL_SHUNTING_YARD
        src/main_shunting_yard.cpp
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/parsers/ShuntingYardParser.cpp
        src/parsers/ShuntingYardParser.h)

# Alles hieronder was eigenlijk onnodig?
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

target_link_libraries(RATSQL_GUI ${REQUIRED_LIBS_QUALIFIED})

