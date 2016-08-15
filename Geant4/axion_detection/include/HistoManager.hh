#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

class TFile;
class TTree;
class TH1D;


class HistoManager
{
public:
	HistoManager();
	~HistoManager();

	void FillHisto(G4double energy);
	void Save();

private:
	TFile *fRootFile;
	TH1D *fHisto;

};



#endif
