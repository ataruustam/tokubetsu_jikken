 #include "axionPhysicsList.hh"
 #include "globals.hh"
 #include "G4PhysicalConstants.hh"
 #include "G4SystemOfUnits.hh"
 #include "G4ParticleDefinition.hh"
 #include "G4EmLivermorePhysics.hh"
 #include "G4DecayPhysics.hh"
 #include "G4EmStandardPhysics.hh"
 #include "G4EmStandardPhysics_option2.hh"
 #include "G4EmExtraPhysics.hh"
 #include "G4EmLowEPPhysics.hh"
 #include "G4StoppingPhysics.hh"
 #include "G4PhotonEvaporation.hh"
 #include "G4DataQuestionaire.hh"
 #include "G4HadronInelasticQBBC.hh"
 #include "G4HadronElasticPhysics.hh"
 #include "G4HadronElasticPhysicsXS.hh"
 #include "G4HadronElasticPhysicsHP.hh"
 #include "G4ChargeExchangePhysics.hh"
 #include "G4IonPhysics.hh"
 #include "G4NeutronTrackingCut.hh"

 axionPhysicsList::axionPhysicsList( G4int ver, const G4String&)
 {
   G4DataQuestionaire it(photon, neutronxs);
   G4cout << "<<< Reference Physics List axionPhysicsList "
          <<G4endl;

   defaultCutValue = 0.01*mm;
   SetVerboseLevel(ver);

   // EM Physics
   //RegisterPhysics( new G4EmStandardPhysics(ver) );

	 //Low energy EM Physics
	 RegisterPhysics( new G4EmLivermorePhysics(ver) );
	 RegisterPhysics( new G4EmLowEPPhysics(ver) );

   // Synchroton Radiation & GN Physics
   RegisterPhysics( new G4EmExtraPhysics(ver) );

   // Decays
   RegisterPhysics( new G4DecayPhysics(ver) );

    // Hadron Physics
   RegisterPhysics( new G4HadronElasticPhysicsXS(ver) );

   RegisterPhysics( new G4StoppingPhysics(ver) );

   RegisterPhysics( new G4IonPhysics(ver) );

   RegisterPhysics( new G4HadronInelasticQBBC(ver));

   // Neutron tracking cut
   RegisterPhysics( new G4NeutronTrackingCut(ver) );
 }

 axionPhysicsList::~axionPhysicsList()
 {}

 void axionPhysicsList::SetCuts()
 {
   SetCutsWithDefault();
 }
