#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

//マルチスレッド対応の場合、マルチスレッドでランの結果をマージする。
//
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

// 可視化マネージャー(OPENGL)
//
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  //
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // マルチスレッド対応か非対応か
  //
  #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
  #else
    G4RunManager* runManager = new G4RunManager;
  #endif

  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());

  // 可視化マネージャ―を登録(OPENGL)
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // インタラクティブな命令を可能にするマネージャー
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) {
    // batch mode
    //
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }
  else {
    // interactive mode
    // インタラクティブモード(コマンドラインから操作可能)に移行
    // マクロファイルinit_vis.macを読み込み。
    //
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  delete visManager;
  delete runManager;
}
