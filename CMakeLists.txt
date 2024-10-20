cmake_minimum_required(VERSION 3.16)

project(TANK_ATTACK VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)  # Mantener AUTOCOMOC activado, pero lo desactivaremos para ventana2.cpp
#set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar paquetes de Qt necesarios
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(PROJECT_SOURCES
        Graph.cpp
        Graph.h
        ventana3.cpp
        ventana3.h
        main.cpp
)

# Desactivar AUTOMOC solo para ventana2.cpp
set_source_files_properties(ventana3.cpp PROPERTIES SKIP_AUTOMOC ON)

# Generar archivos moc manualmente para ventana2.h
qt5_wrap_cpp(MOC_FILES ventana3.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TANK_ATTACK
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            ${MOC_FILES}  # Incluir los archivos moc generados
    )
else()
    if(ANDROID)
        add_library(TANK_ATTACK SHARED
                ${PROJECT_SOURCES}
                ${MOC_FILES}  # Incluir los archivos moc generados
        )
    else()
        add_executable(TANK_ATTACK
                ${PROJECT_SOURCES}
                ${MOC_FILES}  # Incluir los archivos moc generados
        )
    endif()
endif()

# Enlazar las bibliotecas de Qt necesarias
target_link_libraries(TANK_ATTACK PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TANK_ATTACK)
endif()
set_target_properties(TANK_ATTACK PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TANK_ATTACK
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TANK_ATTACK)
endif()

