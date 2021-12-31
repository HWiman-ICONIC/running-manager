# CMakeList.txt : CMake project for RunningManager, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

project ("RunningManager")

# --------------------------------------------------------------------------
# On Visual Studio 8 MS deprecated C. This removes all 1.276E1265 security
# warnings
if(WIN32)
    if(NOT BORLAND)
        if(NOT CYGWIN)
            if(NOT MINGW)
                if(NOT ITK_ENABLE_VISUAL_STUDIO_DEPRECATED_C_WARNINGS)
                    add_definitions(
                    -D_CRT_FAR_MAPPINGS_NO_DEPRECATE
                    -D_CRT_IS_WCTYPE_NO_DEPRECATE
                    -D_CRT_MANAGED_FP_NO_DEPRECATE
                    -D_CRT_NONSTDC_NO_DEPRECATE
                    -D_CRT_SECURE_NO_DEPRECATE
                    -D_CRT_SECURE_NO_DEPRECATE_GLOBALS
                    -D_CRT_SETERRORMODE_BEEP_SLEEP_NO_DEPRECATE
                    -D_CRT_TIME_FUNCTIONS_NO_DEPRECATE
                    -D_CRT_VCCLRIT_NO_DEPRECATE
                    -D_SCL_SECURE_NO_DEPRECATE
                    )
                endif()
                add_definitions(-DNOMINMAX)
            endif()
        endif()
    endif()
add_definitions(-D_WIN32_WINNT=0x0A00)
endif()

find_path(BOOST_SHARED_PTR_INCLUDE_DIRS "boost/shared_ptr.hpp") # Make sure we have boost::shared_ptr for smart pointer handling
# If find_path above does not work, install the entire boost package (takes time...)

# wxWidgets is used for cross platform GUI compilation (Win, MacOS, Linux)
find_package(wxWidgets REQUIRED COMPONENTS aui html net core base xml webview)
include(${wxWidgets_USE_FILE})
add_compile_definitions(WXUSINGDLL)

# Add source to this project's executable.
set(SOURCES
"RunningManager.cpp" 
"Calculator.cpp"
"Converter.cpp" 
"Event.cpp" 
"FastFinishRun.cpp" 
"Intensity.cpp" 
"LongRun.cpp" 
"Mainframe.cpp" 
"Plan.cpp" 
"Section.cpp" 
"SettingsPanel.cpp" 
"TodayControl.cpp" 
"Training.cpp" 
"TrainingProgramGrid.cpp" 
"TrainingType.cpp" 
"User.cpp" 
"WebView.cpp" 
"Week.cpp" 
"WeekDay.cpp" 
"Zone.cpp" 
"ZoneGrid.cpp"
)

if (WIN32)
    list(APPEND SOURCES 
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/sample.rc" # Resource file with reference to RunningManager icon
    )
    set_source_files_properties(sample.rc PROPERTIES LANGUAGE RC) # define resource compiler
    add_executable(RunningManager WIN32 ${SOURCES} ) # add executable with WIN32 prefix
else ()
    add_executable(RunningManager ${SOURCES} ) # Non-windows platforms
endif ()

target_include_directories(RunningManager
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    PRIVATE 
        ${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(RunningManager 
    PRIVATE
        ${wxWidgets_LIBRARIES}
)

# TODO: Add tests and install targets if needed.
