cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# add_compile_options("/permissive-")
# add_compile_options("/Zc:__cplusplus")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
project(EasySchedule LANGUAGES C CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets PATHS G:/Qt6/6.8.2/mingw_64/lib/cmake)
# find_package(GTest REQUIRED PATHS G:/googletest-1.16.0/googletest/cmake)
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# find_package(SQLite3 REQUIRED)
qt_standard_project_setup()
file(GLOB_RECURSE FILES CONFIGURE_DEPENDS *.cpp *.h *.hpp)
set(SQLITE_SOURCES ${PROJECT_SOURCE_DIR}/sqlite3.c)
set_source_files_properties(${SQLITE_SOURCES} PROPERTIES LANGUAGE C)
set(FILES ${FILES} ${SQLITE_SOURCES})
# message(${FILES})
qt_add_executable(EasySchedule
    WIN32 MACOSX_BUNDLE
    ${FILES}
)
include_directories(${PROJECT_SOURCE_DIR})
target_link_libraries(EasySchedule
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)
include(GNUInstallDirs)

install(TARGETS EasySchedule
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET EasySchedule
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})