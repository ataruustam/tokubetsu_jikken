#ifndef axionPhysicsList_h
#define axionPhysicsList_h 1

#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class axionPhysicsList : public G4VModularPhysicsList
{
 public:

   axionPhysicsList(G4int ver = 1, const G4String& type = "axionPhysicsList");

   virtual ~axionPhysicsList();

   virtual void SetCuts();

 private:

   // copy constructor and hide assignment operator
   axionPhysicsList(axionPhysicsList &);
   axionPhysicsList & operator=(const axionPhysicsList &right);

 };

 #endif
