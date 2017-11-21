# Geant4 build&install ガイド

#### 概要：CERNのGeant4インストールガイドの手順の抜粋
[link](http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/InstallationGuide/html/index.html)  
***
これから説明する方法でwindowsにgeant4をインストールした場合、描写ソフトであるOPENGLの挙動に不安定な部分が
みられるため、ほかの描写ソフト(Qtなど)を使うことも視野に入れたほうが良いかもしれない。
***

geant4をwindowsにインストールする場合、動作確認がされているOSとvisual studioのversionの組み合わせは
・Windows 7, 10 with Visual Studio 2015, 32/64bit.
となっている。しかしwindows 10とvisual studio 2017 64bitの組み合わせでも動作確認ができた。

* まずvisual studioをインストールし、コンパイラが正しくインストール・設定されているかを確認する。
確認方法は、
Start → All Programs → Visual Studio xxxx → Visual Studio Tools → Developer Command Prompt for VSxxxx. (xxxxはversionを示す。例2015)
visual studioのcmd(コマンドプロンプト)が開いたら、clコマンドを打つ。インストール・設定が上手くいっていれば次のようになる。

> cl
> Microsoft (R) C/C++ Optimizing Compiler Version > 19.00.23026 for x86
> Copyright (C) Microsoft Corporation.  All rights > reserved.
>
> usage: cl [ option... ] filename... [ /link > > >linkoption... ]

かつコンパイラのversionが最低19以上でないと動作保証はされない。
そしてcmakeをDLする。以前はビルドにmakeやgmakeを使っていたようだが、今はcmake。
https://cmake.org/download/
  Latest Release(3.9.0) → Platform → Windows Source → cmake-3.9.0.zip
適宜DLしたファイルを展開し、インストールする。

* 次にソースファイルをCERNのホームページからDLする。
http://geant4.web.cern.ch/geant4/support/download.shtml
  Source files → Download(Zip format)

以前のversionのgeant4ではデータファイルもDLする必要があったが、今は必要ない。現時点でのgeant4のversionは4 10.3である。
DLしたファイルを適当な解凍ソフトで展開し、次のディレクトリに配置する。(\はwindowsでは¥)
C:\Users\YourUsername\Geant4\geant4_10_03
どこに配置してもよいが、ここではこのディレクトリに配置したこと前提に進めるので、以降の内容は適宜読み替えてほしい。
以降はcmdによる操作となる。まずはGeant4フォルダに移動し、geant4_10_03-buildフォルダ、geant4_10_03-installフォルダを作成する。
そしてgeant4_10_03-buildフォルダへ移動する。
> cd %HOMEPATH%\Geant4
> mkdir geant4_10_03-build
> mkdir geant4_10_03-install
> cd %HOMEPATH%\Geant4\geant4_10_03-build

%HOMEPATH% はここでは C:\Users\YourUsername を示している。

* 次にビルドを行う。cmakeの引数に渡すオプションは以下に示されている。
http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/InstallationGuide/html/ch02s03.html#sect.StandardOptions

ここでは最低限のオプションのみ設定する。設定するのは、

* CMAKE_INSTALL_PREFIX ----- インストール先(絶対パス)
GEANT4_INSTALL_DATA ------ データファイルのDL
  ・GEANT4_USE_OPENGL_WIN32 -- 標準の描写ソフトとしてOPENGLを設定  
の3つである。
コマンドは、

> cmake -DCMAKE_INSTALL_PREFIX=C:%HOMEPATH%\Geant4\geant4_10_03-install -DGEANT4_INSTALL_DATA=ON -DEGANT4_USE_OPENGL_WIN32=ON %HOMEPATH%\Geant4\geant4_10_03

とする。cmd上で最後の三行に
>-- Configuring done
>-- Generating done
>-- Build files have been written to: >C:/Users/YourUsername/Geant4/geant4_10_03-bu>ild

とでれば恐らく成功している。続けて、
> cmake --build . --config Release --target >install

としインストールを行う。

* 次に環境変数の設定を行う。
次の設定を行わないとデータセットが見つからずにコンパイルに失敗する。
パスを通すデータセットは、
 %HOMEPATH%\Geant4\geant4_10_03-install\share\Geant4-10.3.1\data
にある。geant4のversion等により違う場所にあるかもしれないが、その際は適宜読み替えてほしい。
ユーザー変数に上記のディレクトリにあるデータセットをそれぞれ以下のように設定する。

>・G4LEDATA  
>Set to the path to the G4EMLOW6.50 dataset.  
>・G4LEVELGAMMADATA  
>Set to the path to the PhotonEvaporation4.3.2 dataset.  
>・G4NEUTRONHPDATA  
>Set to the path to the G4NDL4.5 dataset.  
>・G4NEUTRONXSDATA  
>Set to the path to the G4NEUTRONXS1.4 dataset.  
>・G4PIIDATA  
>Set to the path to the G4PII1.3 dataset.  
>・G4RADIOACTIVEDATA  
>Set to the path to the RadioactiveDecay5.1.1 dataset.  
>・G4REALSURFACEDATA  
>Set to the path to the RealSurface1.0 dataset.  
>・G4SAIDXSDATA  
>Set to the path to the G4SAIDDATA1.1 dataset.  
>・G4ABLADATA  
>Set to the path to the G4ABLA3.0 dataset.  
>・G4ENSDFSTATEDATA  
>Set to the path to the G4ENSDFSTATE2.1 dataset.  

例えばG4LEDATAという変数名でG4EMLOW6.50フォルダを登録するという具合にすべてのデータセットについてパスを通す。
またユーザー変数PATHに
  %HOMEPATH%\Geant4\geant4_10_03-install\bin
を追加しておく。

* シミュレーションの実行
上記の通りに進めていくと、
  %HOMEPATH%\Geant4\geant4_10_03-install\share\Geant4-10.3.1\examples\basic
にサンプルプログラムがあるはずなので、それらをコンパイルしgeant4が正しくインストールされているかどうか確認する。
これら通常のcmdではなく、1.で用いたvisual studioのcmdで行う。

> cd %HOMEPATH%\Geant4
> mkdir B1-build
> cd %HOMEPATH%\Geant4\B1-build
> cmake -DGeant4_DIR=%HOMEPATH%\geant4_10_03-install\lib\Geant4-10.3.0 %HOMEPATH%\Geant4\geant4_10_03-install\share\Geant4-10.3.1\examples\basic\B1
  > cmake --build . --config Release
  >.\Release\exampleB1.exe

でOPENGLが起動しcmdがIdle状態になればインストールが正しくできている。/run/beamOn 等のコマンドを打ち正しく動作されているかを確認する。
