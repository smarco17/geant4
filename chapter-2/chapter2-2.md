## 2.2.  How to Define a Detector Geometry
### 2.2.1.  Basic Concepts
geant4の検出器のジオメトリはいくつかのボリュームでできている。
最も大きなボリュームはワールドボリュームと呼ばれる。
それはある程度余裕を持って、他のすべての検出器のジオメトリを含む必要がある。
他のボリュームは先のボリュームの中に作られ、配置される。ワールドを記述する最も簡単で（効率的な）形状はボックスである。

それぞれのボリュームは形状、物理的特性を記述し、含まれるボリュームの中に配置することで生成される。

他のボリュームの中にボリュームが配置されたとき、前者を娘ボリューム、後者を親ボリュームと呼ぶ。
親ボリュームと娘ボリュームの座標系は同じでなければならない。

ボリュームの形状を記述するためには、ソリッドの概念を使用する。
ソリッドはそれぞれに形状と値を持つ幾何学的なオブジェクトである。

ボリュームのすべてのプロパティを記述するためには、ロジカルボリュームを使用する。
それはソリッドの幾何学的なプロパティを含み、そして物理的なプロパティ、ボリュームの物質・敏感な検出器の要素を含んでいるかどうか・磁場等を与える。

またボリュームの配置方法を記述されなければならない。

### 2.2.2 Create a aSimple Volume
ボリュームを作るにはどうすればよいか？
  ソリッドを作る。
  ロジカルボリュームを生成し、このソリッドを使って他の特性を与える。
それぞれのボリュームの種類（ソリッド、ロジカル、物理）は起因するレジストリ（VolumeStore）
ー構築したすべてのオブジェクトのリストを含んでいるーを持つ。
このレジストリはリクエストされたときにそれらのオブジェクトを消去する。
ユーザーは手動で削除してはならない。

### 2.2.3 Choose a Solid
簡単な箱を作るとき、名前を決めてデカルト座標で各辺の長さを指定する。
```C++
Example 2.4.  Creating a box.
  G4double world_hx = 3.0*m;
  G4double world_hy = 1.0*m;
  G4double world_hz = 1.0*m;

  G4Box* worldBox
     = new G4Box("World", world_hx, world_hy, world_hz);
```
x座標:-3.0~3.0cm、y座標:-1.0~1.0cm、z座標:-1.0~1.0cm
引数の値は各辺の半分の値であることに注意。

円筒を作るたいときには、G4Tubsクラスを使用する。
```C++
Example 2.5.  Creating a cylinder.
  G4double innerRadius = 0.*cm;
  G4double outerRadius = 60.*cm;
  G4double hz = 25.*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;

  G4Tubs* trackerTube
    = new G4Tubs("Tracker",
                 innerRadius,
                 outerRadius,
                 hz,
                 startAngle,
                 spanningAngle);
```
半径60cm、高さ25cmの円柱"Tracker"

### 2.2.4 Create a Logical Volume
ロジカルボリュームを作るために、まずソリッドと物質から始めなければならない。
そのため上で作成したボックスを使用して、アルゴンガスで満たされた簡単なロジカルボリュームを作成しよう。
```C++
G4LogicalVolume* worldLog
    = new G4LogicalVolume(worldBox, Ar, "World");
```
このロジカルボリュームは"World"と名付けられた。
同様にアルミニウムの円筒を使ってロジカルボリュームを作成しよう。
```C++
G4LogicalVolume* trackerLog
    = new G4LogicalVolume(trackerTube, Al, "Tracker");
```
### 2.2.5 Place a Volume
どのようにボリュームを配置するか？
まずロジカルボリュームから始め、既に存在するボリュームの中のどこに配置するのか決める。
そして、そのボリュームの中心のどこに配置するか、どのように回転させるかを決める。
これらを決定すれば、物理ボリュームを作成でき、ボリュームのインスタンスとして配置され、
属性を具体化する。

### 2.2.6 Create a Physical Volume
ロジカルボリュームから物理ボリュームを作成する。
物理ボリュームはロジカルボリュームのインスタンスとして配置される。
このインスタンスは親ボリュームの中に配置されなければならない。
```C++
Example 2.6.  A simple physical volume.

  G4double pos_x = -1.0*meter;
  G4double pos_y =  0.0*meter;
  G4double pos_z =  0.0*meter;

  G4VPhysicalVolume* trackerPhys
    = new G4PVPlacement(0,                       // no rotation
                        G4ThreeVector(pos_x, pos_y, pos_z),
                                                 // translation position
                        trackerLog,              // its logical volume
                        "Tracker",               // its name
                        worldLog,                // its mother (logical) volume
                        false,                   // no boolean operations
                        0);                      // its copy number
```
これは親ボリュームのworldlogに娘ボリュームのtrackerlogを配置し、
x軸に沿って-1.0m移動し、回転はさせていない。
生成された物理ボリュームは"Tracker"と名付けられ、コピーナンバーは0である。

物理ボリュームは親ボリュームの中に配置しなければならないというルールの例外がある。
その例外はワールドボリュームー最も大きいボリューム、
他のすべてのボリュームを含むボリュームーに対してである。
このボリュームは明らかに他のボリュームに含ませることはできない。
その代わり、それは親のヌルポインタとともにG4PVPlacementとして生成されなければならない。
それは回転させてはならず、グローバルな座標系の原点に配置されなければならい。

通常、ワールドボリュームとして選ぶのに最も良い種類は、
すべての基礎的な例ではG4Boxソリッドタイプである。

### 2.2.7 Coodinate Systems and Rotations
geant4では、配置されたフィジカルボリュームに関連した回転行列はその親のボリュームに関しての参照システムをの回転を表す。

通常個々の行列をインスタンス化し、回転をボリュームに対して適用することで、構築される。これも例B3において実施されている。
