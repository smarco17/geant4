#ifndef TrackerHit_h
#define TrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class TrackerHit : public G4VHit{
  public:
    TrackerHit();
    TrackerHit(const TrackerHit&);
    virtual ~TrackerHit();

    const TrackerHit& operator=(const TrackerHit&);
    G4int operator==(const TrackerHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    virtual void Draw();
    virtual void Print();

    void SetTrackID(G4int track){ fTrackID = track; };
    void SetParentID(G4int parent){ fParentID = parent; };
    void SetParticleName(G4String name){ fParticleName = name; };
    void SetCopyNo(G4int copy){ fCopyNo = copy; };
    void SetEdep(G4double edep){ fEdep = edep; };
    void SetEkinPre(G4double ekinPre){ fEkinPre = ekinPre; };
    void SetEkinPost(G4double ekinPost){ fEkinPost = ekinPost; };
    void SetPosPre(G4ThreeVector xyz) { fPosPre = xyz; };
    void SetPosPost(G4ThreeVector xyz){ fPosPost = xyz; };
    void SetProcessName(G4String process){ fProcessName = process; };

    G4int GetTrackID() const { return fTrackID; };
    G4int GetParentID() const { return fParentID; };
    G4String GetParticleName() const { return fParticleName; };
    G4int GetCopyNo() const { return fCopyNo; };
    G4double GetEdep() const { return fEdep; };
    G4double GetEkinPre() const { return fEkinPre; };
    G4double GetEkinPost() const { return fEkinPost; };
    G4ThreeVector GetPosPre() const { return fPosPre; };
    G4ThreeVector GetPosPost() const { return fPosPost; };
    G4String GetProcessName() const { return fProcessName; };

  private:
      G4int fTrackID;
      G4int fParentID;
      G4String fParticleName;
      G4int fCopyNo;
      G4double fEdep;
      G4double fEkinPre;
      G4double fEkinPost;
      G4ThreeVector fPosPre;
      G4ThreeVector fPosPost;
      G4String fProcessName;
};

typedef G4THitsCollection<TrackerHit> TrackerHitsCollection;

extern G4ThreadLocal G4Allocator<TrackerHit>* TrackerHitAllocator;

inline void* TrackerHit::operator new(size_t){
  if(!TrackerHitAllocator)
      TrackerHitAllocator = new G4Allocator<TrackerHit>;
  return (void *) TrackerHitAllocator->MallocSingle();
}

inline void TrackerHit::operator delete(void *hit){
  TrackerHitAllocator->FreeSingle((TrackerHit*) hit);
}

#endif
