cmake_minimum_required(VERSION 3.15)
project(DigitalSynth VERSION 1.0.0)

add_subdirectory(JUCE)

juce_add_console_app(DigitalSynth PRODUCT_NAME "DigitalSynth")

file(GLOB_RECURSE DIGITAL_SYNTH_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

target_sources(DigitalSynth PRIVATE ${DIGITAL_SYNTH_SOURCES})

target_link_libraries(DigitalSynth PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_processors
    juce::juce_core
    juce::juce_events
)

target_include_directories(DigitalSynth PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(DigitalSynth PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_ALSA=1
    JUCE_PULSEAUDIO=0
)

# Se você ainda estiver usando o JuceHeader, mantenha esta linha:
# juce_generate_juce_header(DigitalSynth)