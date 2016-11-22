scalar CoNum = 0.0;
scalar meanCoNum = 0.0;

if (mesh.nInternalFaces())
{

    volScalarField speed_of_sound = sqrt(thermo->Cp() / thermo->Cv() * (thermo->Cp() - thermo->Cv()) * T);

    scalarField sumPhi
    (
        fvc::surfaceSum(mag(phi))().internalField() / rho.internalField()
        + speed_of_sound.internalField() * fvc::surfaceSum(mesh.magSf())().internalField()
    );

    CoNum = 0.5*gMax(sumPhi/mesh.V().field())*runTime.deltaTValue();

    meanCoNum =
        0.5*(gSum(sumPhi)/gSum(mesh.V().field()))*runTime.deltaTValue();
}

Info<< "Acoustic Courant Number mean: " << meanCoNum
    << " max: " << CoNum << endl;
