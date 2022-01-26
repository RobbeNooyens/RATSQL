cmake_minimum_required(VERSION 3.16.3)
project(RATSQL_CMD)
project(RATSQL_GUI)
project(RATSQL_TESTS)
project(RATSQL_SHUNTING_YARD)
project(RATSQL_PARSING)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

SET(CMAKE_CXX_FLAGS -O3)
SET(CMAKE_CXX_FLAGS -pthread)

set(QT_VERSION 5)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)
#set (QT_COMPILER_FLAGS -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64")
if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm64" AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_PREFIX_PATH "~/Qt/6.2.2/macos/lib/cmake")
    set(QT_VERSION 6)
    set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)
endif()
set(QT_BUILD Qt${QT_VERSION})
set(REQUIRED_LIBS Core Gui Widgets)

# Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # input and output files
    set(DOXYYGEN_IN ${PROJECT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${PROJECT_SOURCE_DIR}/docs/Doxyfile)

    # configure doxygen file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Generating Doxygen documentation...")

    # add custom target
    ADD_CUSTOM_TARGET(RATSQL_DOCS
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen package was not found")
endif (DOXYGEN_FOUND)

add_executable(RATSQL_CMD
        src/main_cmd.cpp
        src/utilities/Utils.h
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/algorithms/LevenshteinDistance.cpp
        src/algorithms/LevenshteinDistance.h
        src/datastructures/RAExpression.cpp
        src/datastructures/RAExpression.h
        src/datastructures/SQLStatement.cpp
        src/datastructures/SQLStatement.h
        src/datastructures/ParseSettings.h
        src/datastructures/ReplaceSuggestion.h
        src/utilities/Parsers.h
        src/utilities/Parsers.cpp
        src/parser/Lexer.h
        src/parser/Lexer.cpp
        src/parser/UndefinedTokenException.h
        src/parser/EarleyParser.h
        src/parser/EarleyParser.cpp
        src/io/CommandHandler.h
        src/io/CommandHandler.cpp
        src/datastructures/CFG.cpp
        src/datastructures/CFG.h
        libs/json.hpp
        src/exceptions/ExceptionHandler.cpp
        src/exceptions/ExceptionHandler.h src/parser/ParseState.cpp src/parser/ParseState.h src/parser/Tokens.h)

add_executable(RATSQL_GUI
        src/main_gui.cpp
        src/utilities/Utils.h
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/algorithms/LevenshteinDistance.cpp
        src/algorithms/LevenshteinDistance.h
        src/datastructures/RAExpression.cpp
        src/datastructures/RAExpression.h
        src/datastructures/SQLStatement.cpp
        src/datastructures/SQLStatement.h
        src/datastructures/ParseSettings.h
        src/datastructures/ReplaceSuggestion.h
        src/exceptions/ExceptionHandler.h
        src/exceptions/ExceptionHandler.cpp
        src/utilities/Parsers.h
        src/utilities/Parsers.cpp
        src/gui/MainWindow.cpp
        src/gui/MainWindow.h
        src/gui/MainWindow.ui
        src/gui/CharButton.h
        src/gui/CharButton.cpp
        src/gui/SettingButton.h
        src/gui/Highlighter.cpp
        src/gui/Highlighter.h
        src/gui/SettingButton.cpp
        src/gui/TextEdit.h
        src/gui/TextEdit.cpp
        )

add_executable(RATSQL_TESTS
        src/main_tests.cpp
        src/utilities/Utils.h
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/algorithms/LevenshteinDistance.cpp
        src/algorithms/LevenshteinDistance.h
        src/datastructures/RAExpression.cpp
        src/datastructures/RAExpression.h
        src/datastructures/SQLStatement.cpp
        src/datastructures/SQLStatement.h
        src/datastructures/ParseSettings.h
        src/datastructures/ReplaceSuggestion.h
        src/exceptions/ExceptionHandler.h
        src/exceptions/ExceptionHandler.cpp
        src/utilities/Parsers.h
        src/utilities/Parsers.cpp
        src/tests/TestManager.cpp
        src/tests/TestManager.h
        src/tests/Test.h
        src/tests/LevenshteinTest.cpp
        src/tests/LevenshteinTest.h
        src/tests/ShuntingYardTest.cpp
        src/tests/ShuntingYardTest.h
        src/tests/Test.cpp)

add_executable(RATSQL_SHUNTING_YARD
        src/main_shunting_yard.cpp
        src/algorithms/ShuntingAlgorithm.cpp
        src/algorithms/ShuntingAlgorithm.h
        src/exceptions/ExceptionHandler.h
        src/exceptions/ExceptionHandler.cpp
        src/datastructures/RAExpression.h
        src/datastructures/RAExpression.cpp
        src/parser/Tokens.h
        src/datastructures/CFG.h
        src/datastructures/CFG.cpp
        src/parser/Lexer.h
        src/parser/Lexer.cpp
        )

add_executable(RATSQL_PARSING
        src/main_parsing.cpp
        src/parser/EarleyParser.h
        src/parser/EarleyParser.cpp
        src/datastructures/CFG.cpp
        src/datastructures/CFG.h
        src/parser/ParseState.h
        src/parser/ParseState.cpp
        libs/json.hpp)

# Alles hieronder was eigenlijk onnodig?
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(RATSQL_GUI ${REQUIRED_LIBS_QUALIFIED})