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
// $Id: axionEventAction.cc 93886 2015-11-03 08:28:26Z gcosmo $
//
/// \file axionEventAction.cc
/// \brief Implementation of the axionEventAction class

#include "axionEventAction.hh"
#include "axionRunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
//#include "HistoManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

axionEventAction::axionEventAction(axionRunAction* runAction,HistoManager* fhisto)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.)
{
  histo=fhisto;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

axionEventAction::~axionEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void axionEventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
  //axionRunAction::n+=1;
  //G4cout << "Event start!" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void axionEventAction::EndOfEventAction(const G4Event*)
{
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);

  /*
  axionRunAction::EnergyDep[axionRunAction::n]=fEdep/CLHEP::keV;
  axionRunAction::n++;
  //axionRunAction::EnergyDep.push_back(fEdep);
  //EnergyDep.push_back(fEdep);
  //G4cout << "Event end!" << G4endl;
  */

    // fill a histogram
    histo->FillHisto(fEdep);
    //G4cout << "Fill!" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
