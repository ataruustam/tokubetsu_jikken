//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: axionRunAction.hh 93886 2015-11-03 08:28:26Z gcosmo $
//
/// \file axionRunAction.hh
/// \brief Definition of the axionRunAction class

#ifndef axionRunAction_h
#define axionRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Parameter.hh"
#include "globals.hh"
#include "vector"
#include "HistoManager.hh"
#define maxdata 100000
class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class axionRunAction : public G4UserRunAction
{
  public:
    axionRunAction(HistoManager* fhisto);
    virtual ~axionRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep);
    /*
    void AddCount(){count += 1;}
    static G4double EnergyDep[maxdata];
    //static std::vector<G4double> EnergyDep;
    static G4int n;
    */
  private:
    G4Parameter<G4double> fEdep;
    G4Parameter<G4double> fEdep2;
    HistoManager* histo;
    //G4int count;
};

#endif
