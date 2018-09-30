# Geant4  

*** 
Geant4のUbuntuへのインストール方法の解説です。  
(Unix系ならおおよそ同じ操作でインストール可能)  
あくまで最低限使用できるような設定となっているので、詳しくはCernの提供する[サイト](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/html/gettingstarted.html)を参考にしてください。  
（GDML, qt等々他にも様々なツールが使えます。）
*** 

### 環境  
- ubuntu 16.04 LTS  
- geant4.10.03.p03

### **最低限**必要なパッケージ  
- cmake (ver3.3 or higher)　　
- expat (ver2.0.1 or higher)  
- opengl  
- x11  

### 事前準備

```
>sudo apt-get update
...
>sudo apt-get upgrade
...
>sudo apt-get install cmake expat libexpat1-dev xorg-dev freeglut3-dev
```

1. ソースファイルを[DL](http://geant4.web.cern.ch/support/download) Linuxの場合は拡張子が.tar.gzで終わるもの。  
今回はgeant4.10.03.p03.tar.gzを使用する。  


2. ソースファイルの解凍  
ついでにビルド用とインストール用のフォルダを作成しておく。（ここではDownloadsフォルダで作業を行うとする。）

```
>pwd # 今どこの階層にいるかを確認（userはユーザー名なので適宜読みかえてください）
/home/user/Downloads
>tar -xvf geant4.10.03.p03.tar.gz
...
>mkdir geant4.10.03.p03-build
>mkdir geant4.10.03.p03-install
```

3. ソースファイルのビルド・インストール  
cmakeの引数については[こちら](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/html/installguide.html#geant4-build-options)を参考にしてください。  
ちなみにネットに繋がっていないとデータセットがDLできません。

```
>cd geant4.10.03.p03-build
>cmake -DCMAKE_INSTALL_PREFIX=/home/user/Downloads/geant4.10.03.p03-install -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_OPENGL_X11=ON /home/user/Downloads/geant4.10.03.p03
...
-- Configuring done
-- Generating done
-- Build files have been written to: /home/user/Downloads/geant4.10.03.p03-build
>make -jN （Nはスレッド数、4とか8とか環境に合わせて）
...
>make install
```

4. 環境変数の設定
今まで手順通りに進めていれば恐らく、  
 /home/user/Downloads/geant4.10.03.p03-install/bin/geant4.sh  
/home/user/Downloads/geant4.10.03.p03-install/share/Geant4-10.3.03/geant4make/geant4make.sh  
に環境変数を設定してくれるスクリプトがあるので、  
ホームディレクトリの.bashrcへこれらのスクリプトを実行するように記述する。  
（.bashrcはterminalの起動ごとに実行されるスクリプト、恐らく/home/user/.bashrcにあるはずだが、なければ作成）

```sh:.bashrc
source /home/user/Downloads/geant4.10.03.p03-install/bin/geant4.sh 
source /home/user/Downloads/geant4.10.03.p03-install/share/Geant4-10.3.3/geant4make/geant4make.sh 
```

5. サンプルプログラムの実行  
/home/user/Downloads/geant4.10.03.p03-install/share/Geant4-10.3.3/examples/basic  
にサンプルプログラムがあるので実行してみる。  
OPENGLのウィンドウが出て、ビームが打たれている様子が見られればきちんと設定ができている！

```
>pwd
/home/user/Downloads
>mkdir sample
>cd sample
>cp -r /home/user/Downloads/geant4.10.03.p03-install/share/Geant4-10.3.3/examples/basic/B1 .
>mkdir B1-build
>cd B1-build
>cmake
-DGeant4_DIR=/home/user/Downloads/geant4.10.03.p03-install/lib/Geant4-10.3.3 ../B1
...
>make -jN
>./exampleB1
Idle>/run/beamON 100
...
```

## 追記

- cmakeでインストール時に指定しておきたいおすすめオプション
  - GEANT4_BUILD_MULTITHREADED=ON  
    本格的にシミュレーションを行うならば、ほぼ必須のオプション。Unix系限定。CPUのスレッド数だけRunを並列して動作させることができる。
  - GEANT4_USE_QT=ON  
    描写ソフトをQTに指定する。QTの場合、GUIでマクロコマンドを指定できたり、マウスでジオメトリを回転、移動させたりして確認することができる。
  - GEANT4_USE_GDML=ON
    Geometry Description Markup Language(GDML)をGeant4内で使用するためのオプション。XERCES-Cパッケージが必要。GDMLはHTMLやXMLのようなに構造を記述していく言語であり、複雑なジオメトリを記述する際に使われる。またSTL, STEP等のCADファイルをGeant4へインポートする際にも使用される。その際は[CADMESH]()というものを使うやり方が一番簡単である。
  - GEANT4_INSTALL_DATA_TIMEOUT=xxx
    xxxは時間(単位は[s])。デフォルトでは1500[s]。回線が遅いときはよくビルドに失敗するため、長くしておくと無駄な時間を取られなくて済む。

