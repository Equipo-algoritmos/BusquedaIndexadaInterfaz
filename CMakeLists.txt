cmake_minimum_required(VERSION 3.19)
project(Registro LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Concurrent)

qt_standard_project_setup()

qt_add_executable(Registro
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_sources(Registro PRIVATE
    Persona.h
    Persona.cpp
    RegistroPersonas.h
    RegistroPersonas.cpp
)

target_link_libraries(Registro
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Concurrent
)

install(TARGETS Registro
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Registro
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
