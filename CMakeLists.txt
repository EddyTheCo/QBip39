cmake_minimum_required(VERSION 3.24)

include(${CMAKE_CURRENT_BINARY_DIR}/local_conf.cmake OPTIONAL)

include(FetchContent)
FetchContent_Declare(
	ccommon
	GIT_REPOSITORY https://github.com/EddyTheCo/Common.git
	GIT_TAG use_IFW
	)
FetchContent_MakeAvailable(ccommon)
version_from_git(
	LOG       OFF
	TIMESTAMP "%Y%m%d%H%M%S"
	)
project(QtBip39 VERSION ${VERSION} DESCRIPTION "Mnemonic sentences - Bip-39" LANGUAGES CXX)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(GNUInstallDirs)


find_package(Qt6 COMPONENTS Core Network )

if (Qt6_FOUND)
	qt_standard_project_setup()


	add_library(qbip39  src/dictionaries.cpp include/crypto/qbip39.hpp
		include/crypto/dictionaries.hpp)

	add_library(${PROJECT_NAME}::qbip39 ALIAS qbip39)
	set_target_properties(qbip39 PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_MAJOR})

	target_compile_definitions(qbip39 PRIVATE WINDOWS_QBIP39)

	target_link_libraries(qbip39 PUBLIC  Qt6::Core Qt6::Network)


	target_include_directories(qbip39 PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Esterv/>")


	install(TARGETS qbip39
		EXPORT ${PROJECT_NAME}-config
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT bip39
		)

	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Esterv/
		COMPONENT ${PROJECT_NAME}
		)
	build_exports()
	if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
		build_cpack()
		if(BUILD_TESTING)
			include(CTest)
			add_subdirectory(tests)
		endif(BUILD_TESTING)
	endif(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
endif(Qt6_FOUND)

if(BUILD_DOCS)
	build_docs()
endif()
