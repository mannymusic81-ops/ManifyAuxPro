cmake_minimum_required(VERSION 3.15)
project(MaNiFyAuxPro VERSION 0.1.0)

# Use in-repo JUCE
set(JUCE_DIR "${CMAKE_SOURCE_DIR}/JUCE")
add_subdirectory("${JUCE_DIR}" JUCE)

# 🎵 Binary data (embed your samples)
juce_add_binary_data(ManiFyBinary
    SOURCES
        Resources/Samples/Pads.wav
        Resources/Samples/Bells.wav
        Resources/Samples/Ambient.wav
        Resources/Samples/Hits.wav
        Resources/Samples/Pluck.wav
)

# 🎹 Define plugin
juce_add_plugin(MaNiFyAuxPro
    COMPANY_NAME "MaNiFy"
    BUNDLE_ID "com.manify.auxpro"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    FORMATS VST3 AU Standalone
    PRODUCT_NAME "MaNiFy Aux Pro"
)

# Disable VST3<->VST2 replacement to avoid JUCE error in VST3 client
target_compile_definitions(MaNiFyAuxPro PRIVATE JUCE_VST3_CAN_REPLACE_VST2=0)

target_include_directories(MaNiFyAuxPro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

# Source files
target_sources(MaNiFyAuxPro PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
    Source/SamplerEngine.cpp
)

# ✅ Use C++17
target_compile_features(MaNiFyAuxPro PRIVATE cxx_std_17)

# Link against JUCE and BinaryData
target_link_libraries(MaNiFyAuxPro PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_basics
    juce::juce_gui_extra
    juce::juce_gui_basics
    juce::juce_graphics
    juce::juce_core
    juce::juce_dsp
    ManiFyBinary
)

# macOS bundle properties
if (APPLE)
    set_target_properties(MaNiFyAuxPro PROPERTIES
        MACOSX_BUNDLE TRUE
    )
endif()
