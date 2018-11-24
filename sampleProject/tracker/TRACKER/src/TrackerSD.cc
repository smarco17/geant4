#include "TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"


TrackerSD::TrackerSD(const G4String& name, const G4String& hitsCollectionName) : G4VSensitiveDetector(name),
fHitsCollection(NULL), fEdepEvent(0){
  collectionName.insert(hitsCollectionName);
}

TrackerSD::~TrackerSD(){}

void TrackerSD::Initialize(G4HCofThisEvent* hce){
  fHitsCollection = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 

  G4int hcID  = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection); 
}

G4bool TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory*){  
  G4double edep = aStep->GetTotalEnergyDeposit();

  if (edep == 0.) return false;

  TrackerHit* newHit = new TrackerHit();

  newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  newHit->SetParentID(aStep->GetTrack()->GetParentID());
  // newHit->SetParticleName(aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName());
  // newHit->SetCopyNo(aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
  newHit->SetEdep(edep);
  // newHit->SetEkinPre(aStep->GetPreStepPoint()->GetKineticEnergy());
  newHit->SetEkinPost(aStep->GetTrack()->GetKineticEnergy());
  // newHit->SetPosPre(aStep->GetPreStepPoint()->GetPosition());
  newHit->SetPosPost(aStep->GetPostStepPoint()->GetPosition());
  // newHit->SetProcessName(aStep->GetTrack()->GetCreatorProcess()->GetProcessName());
  newHit->Print();

  delete newHit;
  // fHitsCollection->insert(newHit);

  fEdepEvent += edep;

  return true;
}

void TrackerSD::EndOfEvent(G4HCofThisEvent*){
  if(fEdepEvent != 0.){
    /*
    G4int nofHits = fHitsCollection->entries();
    G4cout << G4endl
           << "--------> Hits Collection: " << nofHits 
           << " hits in the tracker: " << G4endl;
    for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
    */
    G4cout << "--------> Total Energy Deposition: " << G4BestUnit(fEdepEvent, "Energy") << G4endl;
    fEdepEvent = 0.;
  }
}