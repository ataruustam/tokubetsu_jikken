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
// $Id: axionDetectorConstruction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file axionDetectorConstruction.cc
/// \brief Implementation of the axionDetectorConstruction class

#include "axionDetectorConstruction.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

axionDetectorConstruction::axionDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

axionDetectorConstruction::~axionDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* axionDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  //G4double env_sizeXY = 2*cm, env_sizeZ = 2*cm;
  //G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  G4double a1,a2,z1,z2,density1,density2;  //a is mass per mol, z is atomic number
  //G4double a3,a4,density3;
  G4State state=kStateUndefined;
  G4double temp=193.*kelvin;
  G4String name, symbol;  //for the purpose of elements' name and symbol


  //
  // World
  //
  //G4double world_sizeXY = 1.2*env_sizeXY;
  //G4double world_sizeZ  = 1.2*env_sizeZ;
  G4double world_sizeXY = 0.8*cm;
  G4double world_sizeZ = 0.8*cm;
  //G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* world_mat = nist->ConstructNewGasMaterial("ColdAirWorld","G4_AIR",temp,1*atmosphere);



  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Envelope
  //
  /*G4Box* solidEnv =
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size

  G4LogicalVolume* logicEnv =
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking */


    //size of detector and Fe
    G4double detector_sizeXY = 4.6*mm;
    G4double detector_sizeZ = 0.50*mm;
    G4double Fe_sizeXY = 10.0*mm;
    G4double Fe_sizeZ = 0.04*mm;
    G4double distance = 0.2*mm;

  //
  // Shape 1 Fe
  //
  //G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");

  a1= 57*g/mole;
  density1=7.874*g/cm3;
  G4Material* elFe = new G4Material(name="Iron"  , z1=26., a1, density1, state, temp);
  G4ThreeVector pos1 = G4ThreeVector(0, 0, 0 );


  // Conical section shape
  //G4double shape1_rmina =  0.*cm, shape1_rmaxa = 2.*cm;
  //G4double shape1_rminb =  0.*cm, shape1_rmaxb = 4.*cm;
  //G4double shape1_hz = 3.*cm;
  //G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  //G4Cons* solidShape1 =
  G4Box* solidShape1 =
    new G4Box("Shape1",
    //shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb, shape1_hz,
    //shape1_phimin, shape1_phimax);
    //
    0.5*Fe_sizeXY, 0.5*Fe_sizeXY , 0.5*Fe_sizeZ);


  G4LogicalVolume* logicShape1 =
    new G4LogicalVolume(solidShape1,         //its solid
                        elFe,          //its material
                        "Shape1");           //its name


  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //
  // Shape 2  XRPIX
  //
  a2=28.1*g/mole;
  z2=14;
  density2=2.33*g/cm3;
  G4Material* XRPIX = new G4Material(name = "XRPIX",z2,a2, density2, state, temp);
  G4ThreeVector pos2 = G4ThreeVector(0, 0,  distance + 0.5*(detector_sizeZ + Fe_sizeZ));

  // Trapezoid shape
  /*G4double shape2_dxa = 12*cm, shape2_dxb = 12*cm;
  G4double shape2_dya = 10*cm, shape2_dyb = 16*cm;
  G4double shape2_dz  = 6*cm;
  G4Trd* solidShape2 =
    new G4Trd("Shape2",                      //its name
              0.5*shape2_dxa, 0.5*shape2_dxb,
              0.5*shape2_dya, 0.5*shape2_dyb, 0.5*shape2_dz); //its size */
  G4Box* solidShape2 =
    new G4Box("Shape2",
              0.5*detector_sizeXY, 0.5*detector_sizeXY, 0.5*detector_sizeZ);

  G4LogicalVolume* logicShape2 =
    new G4LogicalVolume(solidShape2,         //its solid
                        XRPIX,          //its material
                        "Shape2");           //its name
  //G4cout << XRPIX ;
  //G4cout << *(G4Material::GetMaterialTable());

  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicShape2;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
