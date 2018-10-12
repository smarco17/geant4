# Fluka インストールマニュアル

※Geant4とは直接関係ないが、他のモンテカルロシミュレーションツールであるFlukaを紹介する。

***
Flukaとは、Geant4と同じモンテカルロシミュレーションを行うことができるソフトウェアである。
Geant4とは違い、ツールキットではないため、パラメータを記述していくだけでシミュレーションを行うことができる。(Phitsと同じような感じ)またFlairというIDEのようなものもあり、かなり便利。ジオメトリもFlair上で編集、保存、エクスポート等できるため、Geant4にもIDEのようなものが欲しい。
***

また以下の手順はFlukaのオフィシャルサイトの[Instruction](http://www.fluka.org/content/manuals/online/INDEX-fluka2011.html)、またはソースファイルのREADMEファイルをまとめたものである。

1. Flukaソースファイルの準備  
   FlukaをDLするには、ユーザー登録が必須である。そのための[オフィシャルサイト](https://www.fluka.org/fluka.php?id=secured_intro)から会員登録を済ませる。するとfuid-xxxxxとpasswordが手に入る。(fuidはメールアドレスに会員登録完了メールが来て、そこに載っている。)

   次に[source](https://www.fluka.org/fluka.php?id=download&sub=packages)から適切なソースファイルを選択し、DLする。ダウンロードする際は、事前に取得したfuidとそのパスワードが必須である。  
   今回選択したソースファイルは、  

   * fluka2011.2x-linux-gfor64bit-7.3-AA.tar.gz  

   である。これはLinux系のOS上でgfortranのversion7.3-64bitを用いるということを意味している。

2. 事前に必要なパッケージを導入する。
   Flukaのみを使用するならば、一部の操作は必要ないかもしれないが、後述するFlukaのIDEのようなものFlairとgeometry viewerを使用するならば、これらの操作は必須である。わざわざ使わないということはあまり考えられないし、これらが組み合わさると劇的に便利になるため、ほぼ必須と言ってもよいだろう。

   ```shell
   > sudo apt update
   > sudo apt upgrade
   > sudo apt install python python-dev python-tk gfortran-7
   > sudo apt install tk-dev gcc-c++ gnuplot-x11
   ```

   pythonのバージョンは3.x系は対応していないので注意する。対応しているバージョンは3.xを除く、>=2.6である。Linuxのディストリビューションやそのバージョンによっては `sudo apt install python` とすると3.x系がダウンロードされてしまうかもしれないので注意。またgfortran-7も環境によっては、`sudo apt install gfortran` としても導入できる場合がある。

3. インストール  
   まず、ダウンロードしたfluka2011.x-linux-gfor64bit-7.3-AA.tar.gzを解凍する。またそれは `/home/user/Downloads` にあるとする。  
   はじめに、環境変数を設定する。設定する環境変数は、FLUPRO, FLUFORの二つであるが、環境にgfortranが複数インストールされている場合、明示的にそのバージョンを指定する必要がある。(GFORFLU)

   ```shell
   > nano ~/.bashrc
   --- 以下 nanoエディタによる .bashrcの設定 ---
   ...
   export FLUPRO=/home/user/Downloads/fluka
   export FLUFOR=gfortran
   (export GFORFLU=gfortran-7)
   --- 終了 ---
   ```

   FLUPRO --- flukaがインストールされている場所  
   FLUPRO --- gfortranかg77、どちらを使ってコンパイルするか  
   GFORFLU --- gfortranのバージョンを明示的に指定  

   ```shell
   > mkdir fluka
   > cd fluka
   > pwd
   /home/user/Downloads/fluka
   > tar -xvf ../fluka2011.x-linux-gfor64bit-7.3-AA.tar.gz .
   > source ~/.bashrc
   > make
   ```

   これでとりあえず終了。

4. Flairとgeometry viewerのDL  
   未定