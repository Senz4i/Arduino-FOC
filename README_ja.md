# SimpleFOClibrary - **シンプル**なフィールド指向制御（FOC）**ライブラリ**
### Arduino IDEおよびPlatformIOをベースにした、BLDCおよびステッピングモーター用クロスプラットフォームFOC実装

私たちはとてもエキサイティングな時代に生きています😃！BLDCモーターはホビーコミュニティにも広がりつつあり、その優れたダイナミクスとパワーを活かした多くの素晴らしいプロジェクトが生まれています。BLDCモーターには従来のDCモーターに比べて多くの利点がありますが、唯一の大きな欠点は制御の複雑さです。PCBの設計や独自のハードウェアソリューションの作成が比較的容易になった今でも、適切な低コストソリューションはまだ普及していません。その理由の一つは、BLDC駆動アルゴリズム（FOCなど）の実装が複雑であることです。

本ライブラリは以下を目指しています：
- 🎯 FOCアルゴリズムを分かりやすくし、堅牢かつシンプルなArduinoライブラリを提供する：[Arduino SimpleFOClibrary](https://docs.simplefoc.com/arduino_simplefoc_library_showcase)
  - できるだけ多くの<b>モーター＋センサー＋ドライバー＋MCU</b>の組み合わせをサポート
- 🎯 モジュール式で使いやすいFOC対応BLDCドライバーボードの開発
   - 公式ドライバーボードは[SimpleFOCBoards](https://docs.simplefoc.com/boards)を参照
   - コミュニティによる多くのボードも[SimpleFOCCommunity](https://community.simplefoc.com/)で紹介

> 次回リリース 📢 : SimpleFOClibrary v2.3.4
> - ESP32 MCUの拡張サポート
> - ステッピングモーターの電流検出サポート
> - 新しい電流検出アライメント手順
> - 割り込みなしのホールセンサーサポート
> - ドキュメントの充実
> - 詳細は[リリースノート](https://github.com/simplefoc/Arduino-FOC/milestone/11)を参照

## Arduino SimpleFOClibrary v2.3.4

このビデオでは、SimpleFOClibraryの基本的な使い方、電子接続、機能を紹介しています。

### 特徴
- **簡単インストール**：
   - Arduino IDE：ライブラリマネージャ対応
   - PlatformIO
- **オープンソース**：全コードとドキュメントをGitHubで公開
- **目標**：
   - できるだけ多くの[センサー](https://docs.simplefoc.com/position_sensors)＋[モーター](https://docs.simplefoc.com/motors)＋[ドライバー](https://docs.simplefoc.com/drivers)＋[電流検出](https://docs.simplefoc.com/current_sense)の組み合わせをサポート
   - 最新かつ詳細なドキュメントとAPIリファレンス、サンプルを提供
- **簡単セットアップ・設定**：
   - ハードウェア設定が簡単
   - 各ハードウェア部品はC++オブジェクトとして扱える
   - [制御ループのチューニング](https://docs.simplefoc.com/motion_control)が容易
   - [SimpleFOC Studio](https://docs.simplefoc.com/studio)によるGUI設定ツール
   - 通信・モニタリング機能内蔵
- **クロスプラットフォーム**：
   - 異なるマイコン間でコード移植が容易
   - 複数の[MCUアーキテクチャ](https://docs.simplefoc.com/microcontrollers)をサポート
      - Arduino: UNO R4, UNO, MEGA, DUE, Leonardo, Nano, Nano33 ...
      - STM32
      - ESP32
      - Teensy
      - その他多数

## ドキュメント
APIリファレンス、サンプルプロジェクト、ステップバイステップガイドは[公式ドキュメントサイト](https://docs.simplefoc.com/)で公開しています。

## はじめに
このライブラリを「そのままArduinoライブラリとして使う」場合と、「アルゴリズムを理解しカスタマイズしたい」場合でインストール方法が異なります。

- フルライブラリインストール：[ドキュメント](https://docs.simplefoc.com/library_download)
- PlatformIO：[ドキュメント](https://docs.simplefoc.com/library_platformio)

### Arduino IDEへのインストール
#### ライブラリマネージャ
- Arduino IDEの「ツール > ライブラリを管理...」から「Simple FOC」で検索し、最新版をインストール
- IDEを再起動し、「ファイル > スケッチ例 > Simple FOC」にサンプルが追加されます

#### Githubからのインストール
- [GitHubリポジトリ](https://github.com/simplefoc/Arduino-FOC)にアクセス
- 「Clone or Download > Download ZIP」でダウンロード
- 解凍し「Arduino Libraries」フォルダ（Windows: ドキュメント > Arduino > libraries）に配置
- IDEを再起動し、サンプルが利用可能に

#### ターミナルからのインストール
```sh
cd #Arduino librariesフォルダ
git clone https://github.com/simplefoc/Arduino-FOC.git
```
- IDEを再起動し、サンプルが利用可能に

## コミュニティと貢献
実装・応用・対応ハードウェア等の質問は[コミュニティフォーラム](https://community.simplefoc.com)や[Discord](https://discord.gg/kWBwuzY32n)へどうぞ。

### Github Issues & プルリクエスト
バグ報告・提案・質問はIssueでどうぞ。プルリクエストも歓迎ですが、まずは[フォーラム](https://community.simplefoc.com)で相談してください。

## Arduinoコード例
BLDCモーター＋エンコーダによる速度制御のシンプルな例です。

```cpp
#include <SimpleFOC.h>

//  BLDCMotor( 極対数 )
BLDCMotor motor = BLDCMotor(11);
//  BLDCDriver( pin_pwmA, pin_pwmB, pin_pwmC, enable (省略可) )
BLDCDriver3PWM driver = BLDCDriver3PWM(9, 10, 11, 8);
//  Encoder(pin_A, pin_B, CPR)
Encoder encoder = Encoder(2, 3, 2048);
// チャンネルA/Bのコールバック
void doA(){encoder.handleA();}
void doB(){encoder.handleB();}

void setup() {
  encoder.init();
  encoder.enableInterrupts(doA, doB);
  motor.linkSensor(&encoder);
  driver.voltage_power_supply = 12;
  driver.init();
  motor.linkDriver(&driver);
  motor.controller = MotionControlType::velocity;
  motor.init();
  motor.initFOC();
}

void loop() {
  motor.loopFOC();
  // 目標速度2rad/sで制御
  motor.move(2);
}
```
詳細は[SimpleFOCドキュメント](https://docs.simplefoc.com/)を参照してください。

## サンプルプロジェクト
SimpleFOClibraryやSimpleFOCShieldの応用例は以下の動画で紹介しています。

## SimpleFOCの引用について
本ライブラリは複数の研究プロジェクトや論文で利用されています。引用の際は下記論文を参考にしてください：

```
@article{simplefoc2022,
  doi = {10.21105/joss.04232},
  url = {https://doi.org/10.21105/joss.04232},
  year = {2022},
  publisher = {The Open Journal},
  volume = {7},
  number = {74},
  pages = {4232},
  author = {Antun Skuric and Hasan Sinan Bank and Richard Unger and Owen Williams and David González-Reyes},
  title = {SimpleFOC: A Field Oriented Control (FOC) Library for Controlling Brushless Direct Current (BLDC) and Stepper Motors},
  journal = {Journal of Open Source Software}
}
```
