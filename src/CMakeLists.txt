cmake_minimum_required(VERSION 3.7)

project(bss-viewer)

set(APP_SRC 
    "main.cpp" 
    "parse_exception.h"
    "parse_exception.cpp"
    "file_parser.h"
    "file_parser.cpp"
    "bank_transaction_marker.h"
    "bank_transaction.h"
    "bank_transaction.cpp"
    "bank_transaction_list.h"
    "bank_transaction_list.cpp"
    "currency_utils.h"
    "currency_utils.cpp"
    "string_utils.h"
    "string_utils.cpp"
    "table_model.h"
    "table_model.cpp"
    "main_window.h"
    "main_window.cpp")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(bssViewer ${APP_SRC} ${UI_HEADERS})

target_link_libraries(bssViewer Qt5::Widgets)
