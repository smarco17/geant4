#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4Material;

class DetectorConstruction : public G4VUserDetectorConstruction{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  private:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
    
    G4Material* fAir;
    G4Material* fAu;
    G4Material* fSi;
    G4bool  fCheckOverlaps = true;
};

#endif
