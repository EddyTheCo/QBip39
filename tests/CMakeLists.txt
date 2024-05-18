file(
        DOWNLOAD
        "https://raw.githubusercontent.com/trezor/python-mnemonic/master/vectors.json"
        "${CMAKE_CURRENT_BINARY_DIR}/vectors.json")
foreach(app test1)
        add_executable(${app} ${app}.cpp)
        target_link_libraries(${app} PRIVATE qbip39)
        add_test(NAME ${app} COMMAND ${app})

        if(WIN32 AND BUILD_SHARED_LIBS)
                add_custom_command(
                        TARGET ${app}
                        POST_BUILD
                        COMMAND
                                ${CMAKE_COMMAND} -E copy_if_different
                                $<TARGET_RUNTIME_DLLS:${app}>
                                $<TARGET_FILE_DIR:${app}>
                        COMMAND_EXPAND_LISTS)
        endif()
endforeach()
