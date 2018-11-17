#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction: public G4VUserDetectorConstruction{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetDetector() const { return fDetector; }
  
  protected:
    G4LogicalVolume* fDetector;
};

#endif

