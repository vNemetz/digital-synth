{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  name = "digital-synth";

  nativeBuildInputs = with pkgs; [
    cmake
    git
    gnumake
    pkg-config
    clang
  ];

  buildInputs = with pkgs; [
    gtk3
    webkitgtk_4_1
    libsoup_3
    curl
    alsa-lib
    pulseaudio
  ];

  shellHook = ''
    export CC=clang
    export CXX=clang++

    if [ ! -f JUCE/CMakeLists.txt ]; then
      echo "Bootstrapping JUCE submodule..."
      git submodule update --init --recursive
    fi
  '';
}
