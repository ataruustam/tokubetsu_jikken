#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include <CLHEP/Units/SystemOfUnits.h>

#include "HistoManager.hh"
#include "G4UnitsTable.hh"


HistoManager::HistoManager()
:fRootFile(0)
{
	//prepare the histogram
	fHisto = new TH1D("Energy_Deposit","Energy_Deposit",20,0,20);

	//root file name
	G4String fileName = "XRPIX_fake.root";
  fRootFile = new TFile(fileName,"RECREATE");
  if (! fRootFile) {
    G4cout << " problem creating the ROOT TFile "
           << G4endl;
				 }
}

HistoManager::~HistoManager()
{
  if (fRootFile) delete fRootFile;
}


void HistoManager::FillHisto(G4double energy)
{
	//put data into the histogram
	fHisto->Fill(energy/CLHEP::keV);
}

void HistoManager::Save()
{
	if (! fRootFile) return;

  fRootFile->cd();
	fHisto->Write();      // Writing the histograms to the file
  fRootFile->Close();       // and closing the tree (and the file)

}
