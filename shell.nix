{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  name = "qmk";

  buildInputs = with pkgs; [
    qmk
    python312
    python312Packages.pip
    python312Packages.virtualenv
    python312.pkgs.venvShellHook
  ];

  venvDir = ".venv";
  postVenvCreation = ''
    # Install QMK dependencies in the virtual environment
    pip install --upgrade pip
  '';
}
