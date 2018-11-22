#include "TrackerSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"


TrackerSD::TrackerSD(const G4String& name, const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name), fHitsCollection(NULL){
  collectionName.insert(hitsCollectionName);
}

TrackerSD::~TrackerSD(){}

void TrackerSD::Initialize(G4HCofThisEvent* hce){
  fHitsCollection = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 
  // Add this collection in hce
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection); 
}

G4bool TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory* history){
  G4String particleName = aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
  G4double edep = aStep->GetTotalEnergyDeposit();

  if(edep == 0.) return false;

  TrackerHit* newHit = new TrackerHit();
  newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
  newHit->SetEdep(edep);
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  // newHit->Print();

  // fHitsCollection->insert(newHit);

  return true;
}

void TrackerSD::EndOfEvent(G4HCofThisEvent* hitCollection){
  G4int nofHits = fHitsCollection->entries();
  G4cout << G4endl 
         << "-------->Hits Collection: in this event they are " << nofHits 
         << " hits in the tracker chambers: " << G4endl;
  for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
}
