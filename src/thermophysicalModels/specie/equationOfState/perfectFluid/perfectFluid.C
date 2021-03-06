/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "perfectFluid.H"
#include "IOstreams.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
Foam::perfectFluid<Specie>::perfectFluid(Istream& is)
:
    Specie(is),
    R_(readScalar(is)),
    rho0_(readScalar(is))
{
    is.check("perfectFluid<Specie>::perfectFluid(Istream& is)");
}


template<class Specie>
Foam::perfectFluid<Specie>::perfectFluid(const dictionary& dict)
:
    Specie(dict),
    R_(readScalar(dict.subDict("equationOfState").lookup("R"))),
    rho0_(readScalar(dict.subDict("equationOfState").lookup("rho0")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
void Foam::perfectFluid<Specie>::write(Ostream& os) const
{
    Specie::write(os);

    dictionary dict("equationOfState");
    dict.add("R", R_);
    dict.add("rho0", rho0_);

    os  << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
Foam::Ostream& Foam::operator<<(Ostream& os, const perfectFluid<Specie>& pf)
{
    os  << static_cast<const Specie&>(pf)
        << token::SPACE << pf.R_
        << token::SPACE << pf.rho0_;

    os.check("Ostream& operator<<(Ostream&, const perfectFluid<Specie>&)");
    return os;
}


// ************************************************************************* //
