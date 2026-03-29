cmake_minimum_required(VERSION 3.15)
project(DigitalSynth VERSION 1.0.0)

# 1. Encontrar o PkgConfig
find_package(PkgConfig REQUIRED)

# 2. Mapear as bibliotecas necessárias para o módulo juce_gui_extra
pkg_check_modules(DEPS REQUIRED 
    gtk+-3.0 
    webkit2gtk-4.1 
    libsoup-3.0 
    javascriptcoregtk-4.1
    libcurl
)

# 3. Adicionar o JUCE
add_subdirectory(JUCE)

# 4. Criar o App
juce_add_console_app(DigitalSynth PRODUCT_NAME "DigitalSynth")

# Inclui automaticamente novos arquivos de implementação em src/
file(GLOB_RECURSE DIGITAL_SYNTH_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

target_sources(DigitalSynth PRIVATE ${DIGITAL_SYNTH_SOURCES})

# 5. Vincular as bibliotecas encontradas pelo PkgConfig e os módulos JUCE
target_link_libraries(DigitalSynth PRIVATE
    ${DEPS_LIBRARIES}
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_processors
    juce::juce_core
    juce::juce_events
)

# 6. Incluir os diretórios de cabeçalho (.h) das dependências
target_include_directories(DigitalSynth PRIVATE
    ${DEPS_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Opcional: Macros para ajudar o JUCE no Linux
target_compile_definitions(DigitalSynth PRIVATE 
    JUCE_WEB_BROWSER=0 
    JUCE_USE_CURL=1
    JUCE_ALSA=1
    JUCE_PULSEAUDIO=1
)

# Se você ainda estiver usando o JuceHeader, mantenha esta linha:
# juce_generate_juce_header(DigitalSynth)