{ pkgs ? import <nixpkgs> { } }:

with pkgs;
mkShell {
  name = "rl_custom_rime";
  buildInputs = [
    stdenv.cc
    pkg-config
    xmake
    librime
    readline.dev
    glib.dev
  ];
}
