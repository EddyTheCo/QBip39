cmake_minimum_required(VERSION 3.24 FATAL_ERROR)
include(${CMAKE_CURRENT_BINARY_DIR}/local_conf.cmake OPTIONAL)

include(FetchContent)
FetchContent_Declare(
    ccommon
    GIT_REPOSITORY https://github.com/EddyTheCo/Common.git
    GIT_TAG v0.1.1
)
FetchContent_MakeAvailable(ccommon)
version_from_git(
    LOG       OFF
    TIMESTAMP "%Y%m%d%H%M%S"
)
project(QBip39 VERSION ${VERSION} DESCRIPTION "Mnemonic sentences - Bip-39" LANGUAGES CXX)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(GNUInstallDirs)

find_package(Qt6 COMPONENTS Core Network )

if (Qt6_FOUND)
    qt_standard_project_setup()
endif(Qt6_FOUND)

add_library(qbip39 qbip39.cpp src/dictionaries.cpp include/crypto/qbip39.hpp
    include/crypto/dictionaries.hpp)

add_library(${PROJECT_NAME}::qbip39 ALIAS qbip39)

target_compile_definitions(qbip39 PRIVATE WINDOWS_QBIP39)
if (Qt6_FOUND)
    target_link_libraries(qbip39 PUBLIC  Qt6::Core Qt6::Network)
endif(Qt6_FOUND)


target_include_directories(qbip39 PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Esterv>")

install(TARGETS qbip39
    EXPORT ${PROJECT_NAME}-config
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT Qbip39
)
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Esterv/
    COMPONENT Qbip39
)

install(EXPORT ${PROJECT_NAME}-config
    FILE ${PROJECT_NAME}-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Esterv
    NAMESPACE ${PROJECT_NAME}::
    COMPONENT ${PROJECT_NAME}
)
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Esterv
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Esterv
)
export(EXPORT ${PROJECT_NAME}-config
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CPACK_PACKAGE_CONTACT "estervtech")
    include(CTest)
    set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-v${SEMVER}-${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_VERSION}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_CXX_COMPILER_ID}")
    if(NOT BUILD_SHARED_LIBS)
        set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-static")
    endif(NOT BUILD_SHARED_LIBS)
    include(CPack)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif(BUILD_TESTING)
endif()
if(BUILD_DOCS)
    get_target_property(build_docs cmake_build_docs SOURCES)
    include(${build_docs})
endif()
