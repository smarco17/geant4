# 5. Python Interface
Pythonはインタープリター方式の有名なスクリプト言語である。Geant4とPythonを紐づけるGeant4PyはGeant4クラスへの架け橋を提供する。これによりPythonから直接Geant4のクラスへアクセスすることができる。ユーザーのアプリケーションはPythonのソフトフェアのバス上にPyROOTのようなたくさんのサードパーティなモジュールを簡単に使用することができる。

Geant4PyはGeant4のソースパッケージのディレクトリ`environments/g4py/`において提供されている。

## 5.1. Installation
### 5.1.1. Software Requirements
Geant4PyはPythonとC++のコードを紐づける外部のライブラリの[Boost-C++](http://www.boost.org/)が必要である。

### 5.1.2. Building Geant4Py module
ビルディングシステムは完全にCMakeのシステムへ移行した。ライブラリをビルドする前に、Geant4をビルドする際に記した`CMAKE_INSTALL_PREFIX`のパスを環境変数`GEANT4_INSTALL`に設定しなければならない。
```bash
export GEANT4_INSTALL="Geant4 install path" (zsh, bash)
setenv GEANT4_INSTALL "Geant4 install path" (csh)
```
そして
```bash
mkdir build
cd build
cmake ..   
make
make install
```
もしテストのためのコンポーネントを走らせたければ、
```bash
cd build/tests
make; make install
```
デフォルトではGeant4Pyは`g4py/lib(64)`ディレクトリにインストールされる。

## 5.2. Using Geant4Py
環境変数`PYTHONPATH`が実行時に必要となる。環境変数`PYTHONPATH`はPYTHONのモジュールが探しに行くディレクトリを示していて、ディレクトリのリストをコロンで分割することで与えられる。実際には、`(your g4py directory)/lib:(your g4py directory)/lib/examples:(your g4py directory)/lib/tests`が変数である。

### 5.2.1. Import Geant4
Geant4Pyを使用するため、`Geant4`という名のモジュールをインポートすることから始める。
```bash
# python
Python 2.7.5 (default, Mar  9 2014, 22:15:05) 
[GCC 4.2.1 Compatible Apple LLVM 5.0 (clang-500.0.68)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> from Geant4 import *

*************************************************************
 Geant4 version Name: geant4-10-01         (5-December-2014)
                      Copyright : Geant4 Collaboration
                      Reference : NIM A 506 (2003), 250-303
                            WWW : http://cern.ch/geant4
*************************************************************

Visualization Manager instantiating...
>>>
```

### 5.2.2. Access to Geant4 Globals
