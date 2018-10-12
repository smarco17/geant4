# Geant4 インストールマニュアル

***
Windows Subsystem for Linux(WSL)とは、Windows10上でネイティブにLinuxを実行できる環境であり、version 1607以降のWindows10で実行可能である。ディストリビューションとしては、Ubuntu, Debian, Kali Linux等が利用できる。もちろんWSL上のUbuntuにおいてもGeant4が実行できることは検証済みであるし、Xming等のサーバーを導入すれば、実機にUbuntuをインストールよりも簡単に、仮想環境にUbuntuをインストールするよりも効率よくシミュレーションを行うことができる。
***

1. WSL(Ubuntu)のインストール  
   詳述はしないが、WSLのインストール方法を概説する。  
   コントロールパネル > プログラム > プログラムと機能 > Windowsの機能の有効化または無効化  
   からWindows Subsystem for Linux にチェックを入れる。(セットアップ終了後、再起動)  

   その後、Microsoft Storeのアプリケーションを開き、Ubuntuと検索し、インストールを行う。(16.04, 18.04どちらでも動作確認済み)  

   スタートメニューからUbuntuを起動する。初回のみセットアップに少し時間がかかる。  
   ユーザー名とパスワードの設定画面に入る。

2. Xmingのインストール
   このままではグラフィックの出力先がないため、GUI等を使用できない。よって[Xming](https://ja.osdn.net/projects/sfnet_xming/releases/)を導入する。  

   Xmingをインストールした後、起動、全てデフォルトの設定のままでOK。  

   次にUbuntu側の設定。

   ```shell
   > sudo apt install x11-apps
   > echo 'export DISPLAY=localhost:0.0' >> ~/.bashrc
   > source ~/.bashrc
   > xeyes
   ```

   `xeyes` コマンドで目が表示されれば、設定完了。

3. Geant4のインストール  
   [こちら](./geant4_build_and_install_guide_for_ubuntu.md)