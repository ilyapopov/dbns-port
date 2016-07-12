    Info<< "Reading thermophysical properties\n" << endl;

    autoPtr<psiThermo> thermo
    (
        psiThermo::New(mesh)
    );
    thermo->validate(args.executable(), "h", "e");

    // Primitive variables

    volScalarField& h = thermo->he();
    volScalarField& p = thermo->p();
    const volScalarField& T = thermo->T();

    Info<< "Reading field rho\n" << endl;
    volScalarField rho
    (
        IOobject
        (
            "rho",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        thermo->rho()
    );

    Info<< "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );


    // Conservative variables

    volVectorField rhoU
    (
        IOobject
        (
            "rhoU",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        rho*U
    );

    volScalarField rhoE
    (
        IOobject
        (
            "rhoE",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        rho*(h + 0.5*magSqr(U)) - p
    );


    // Create numeric flux
    autoPtr<basicNumericFlux> dbnsFluxPtr = basicNumericFlux::New
    (
        p,
        U,
        T,
        thermo()
    );
    basicNumericFlux& dbnsFlux = dbnsFluxPtr();

    // Create mass flux alias for easier coupling with other code components
    const surfaceScalarField& phi = dbnsFlux.rhoFlux();
