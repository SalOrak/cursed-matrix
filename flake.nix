{
  description = "Matrix TUI effect written in nCurses";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      forAllSystems = f:
        nixpkgs.lib.genAttrs [ "x86_64-linux" "aarch64-linux" ] (system: f system);
    in
    {
      packages = forAllSystems (system:
        let
          pkgs = import nixpkgs { inherit system; };
        in
        {
          cmatrix = pkgs.stdenv.mkDerivation {
            pname = "cmatrix";
            version = "0.1.0";

            src = self;

            buildInputs = [
              pkgs.gcc
              pkgs.gnumake
              pkgs.ncurses5
            ];

            buildPhase = ''
              make all
            '';

            installPhase = ''
              mkdir -p "$out/bin"
              mv main "$out/bin/cmatrix"
            '';
          };
        });
      defaultPackage = forAllSystems (system: self.packages.${system}.cmatrix);
    };
}

