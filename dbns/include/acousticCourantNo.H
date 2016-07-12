scalar CoNum = 0.0;
scalar meanCoNum = 0.0;

if (mesh.nInternalFaces())
{

    volScalarField speed_of_sound = sqrt(thermo->Cp() / thermo->Cv() * (thermo->Cp() - thermo->Cv()) * T);
    surfaceScalarField acCo =
            (mag(phi) / (fvc::interpolate(rho) * mesh.magSf()) + fvc::interpolate(speed_of_sound))
            * mesh.surfaceInterpolation::deltaCoeffs() * runTime.deltaT();

    CoNum = gMax(acCo.internalField());

    meanCoNum = gSum(acCo.internalField()) / mesh.nInternalFaces();
}

Info<< "Acoustic Courant Number mean: " << meanCoNum
    << " max: " << CoNum << endl;
