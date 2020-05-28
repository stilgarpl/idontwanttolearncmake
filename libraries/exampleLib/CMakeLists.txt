if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${IDWTLC_LIB})
    file(GLOB_RECURSE IDWTLC_LIBRARY_SOURCES_LIST LIST_DIRECTORIES false CONFIGURE_DEPENDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.cpp *.cxx *.hpp)
    add_library(${IDWTLC_LIB} ${IDWTLC_LIBRARY_SOURCES_LIST})
    target_include_directories(${IDWTLC_LIB} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:${IDWTLC_DESTINATION_INCLUDE}>)
    install(DIRECTORY ${IDWTLC_LIB} DESTINATION ${IDWTLC_DESTINATION_INCLUDE}
            FILES_MATCHING PATTERN "*.h")
    install(DIRECTORY ${IDWTLC_LIB} DESTINATION ${IDWTLC_DESTINATION_INCLUDE}
            FILES_MATCHING PATTERN "*.hpp")
    target_link_libraries(${IDWTLC_LIB} PUBLIC)
    install(TARGETS ${IDWTLC_LIB} COMPONENT ${IDWTLC_LIB} DESTINATION ${IDWTLC_DESTINATION_LIB} EXPORT ${PROJECT_NAME}Targets)

    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/depends)
        file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/depends IDWTLC_DEPENDENCIES)


        foreach (IDWTLC_DEP_STR IN LISTS IDWTLC_DEPENDENCIES)
            string(REGEX MATCHALL "[^ ]+" IDWTLC_DEP_LIST ${IDWTLC_DEP_STR})
            list(POP_FRONT IDWTLC_DEP_LIST IDWTLC_DEP)

            list(LENGTH IDWTLC_DEP_LIST IDWTLC_COMPONENTS_NUM)
            if (${IDWTLC_COMPONENTS_NUM} GREATER 0)
                set(IDWTLC_COMPONENTS_STR "")
                set(IDWTLC_LINKCOMPONENTS_STR "")

                foreach (IDWTLC_COMPONENT IN LISTS IDWTLC_DEP_LIST)
                    set(IDWTLC_COMPONENTS_STR "${IDWTLC_COMPONENT} ${IDWTLC_COMPONENTS_STR}")
                    set(IDWTLC_LINKCOMPONENTS_STR "${IDWTLC_DEP}::${IDWTLC_COMPONENT} ${IDWTLC_LINKCOMPONENTS_STR}")
                    string(STRIP ${IDWTLC_COMPONENTS_STR} IDWTLC_COMPONENTS_STR)
                    string(STRIP ${IDWTLC_LINKCOMPONENTS_STR} IDWTLC_LINKCOMPONENTS_STR)
                endforeach ()
                hunter_add_package(${IDWTLC_DEP} COMPONENTS ${IDWTLC_COMPONENTS_STR})

                find_package(${IDWTLC_DEP} REQUIRED ${IDWTLC_COMPONENTS_STR})
                target_link_libraries(${IDWTLC_LIB} PUBLIC ${IDWTLC_LINKCOMPONENTS_STR})
            else ()
                hunter_add_package(${IDWTLC_DEP})
                find_package(${IDWTLC_DEP} REQUIRED)
                target_link_libraries(${IDWTLC_LIB} PUBLIC ${IDWTLC_DEP}::${IDWTLC_DEP})
            endif ()
        endforeach ()
    endif ()
else ()
    message(FATAL_ERROR "${IDWTLC_LIB} directory not found for ${IDWTLC_LIB} library." )
endif ()