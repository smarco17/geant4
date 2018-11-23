#include "TrackerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<TrackerHit>* TrackerHitAllocator=0;

TrackerHit::TrackerHit() : G4VHit(),
fTrackID(-1), fParentID(-1), fParticleName(""), fCopyNo(-1), fEdep(0.), fEkinPost(0.),
fPosPre(G4ThreeVector()), fPosPost(G4ThreeVector()), fProcessName(""){}

TrackerHit::~TrackerHit(){}

TrackerHit::TrackerHit(const TrackerHit& right) : G4VHit(){
  fTrackID = right.fTrackID;
  fParentID = right.fParentID;
  fParticleName = right.fParticleName;
  fCopyNo = right.fCopyNo;
  fEdep = right.fEdep;
  fEkinPost = right.fEkinPost;
  fPosPre = right.fPosPre;
  fPosPost = right.fPosPost;
  fProcessName = right.fProcessName;
}

const TrackerHit& TrackerHit::operator=(const TrackerHit& right){
  fTrackID = right.fTrackID;
  fParentID = right.fParentID;
  fParticleName = right.fParticleName;
  fCopyNo = right.fCopyNo;
  fEdep = right.fEdep;
  fEkinPost = right.fEkinPost;
  fPosPre = right.fPosPre;
  fPosPost = right.fPosPost;
  fProcessName = right.fProcessName;

  return *this;
}

G4int TrackerHit::operator==(const TrackerHit& right) const{
  return ( this == &right ) ? 1 : 0;
}

void TrackerHit::Draw(){
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager){
    G4Circle circle(fPosPost);
    circle.SetScreenSize(4.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void TrackerHit::Print(){
  G4cout
     << " ParentID:" << fParentID
     << " TrackID:" << fTrackID << " Particle:" << fParticleName << " CopyNo:" << fCopyNo
     << " EkinPre:"
     << std::setw(8) << G4BestUnit(fEkinPre, "Energy")
     << " Edep:"
     << std::setw(7) << G4BestUnit(fEdep, "Energy")
     << " EkinPost:"
     << std::setw(8) << G4BestUnit(fEkinPost, "Energy") << G4endl
     << " PosPre:"
     << std::setw(7) << G4BestUnit(fPosPre, "Length")
     << " PosPost:"
     << std::setw(7) << G4BestUnit(fPosPost, "Length")
     << " Process:"
     << std:: setw(5) << fProcessName << G4endl
     << " --- "
     << G4endl;
}
