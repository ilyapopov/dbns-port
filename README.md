# dbns-port

A port of `dbnsFoam` (density-based Navier-Stokes) compressible solver from `foam-extend-3.2` to `OpenFOAM-3.0`

## Install

First, setup your OpenFOAM environment, for example:

```bash
. ~/OpenFOAM/OpenFOAM-3.0.x/etc/bashrc
```

    
Then, get the sources and compile:

```bash
cd $WM_PROJECT_USER_DIR
git clone https://github.com/ilyapopov/dbns-port
cd dbns-port
wmake all
```

## Run

dbnsFoam - an inviscid solver

dbnsTurbFoam - a viscous (laminar or turbulent) solver
    
## License

This code is licensed under the terms of GPLv3 license. See COPYING file.