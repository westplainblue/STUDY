# 概要
このコードはポテンショメーターの入力に基づいてLEDの明るさを制御する組み込みシステムです。

# Potentiometer.h
このヘッダーファイルではPotentiometerクラスを定義しておりクラス内には
・potAd:ポテンショメーターのアドレスを格納する変数
・Potentiometer():クラスのインスタンスを初期化する
・getPotAd():ポテンショメーターのアドレスを返す関数
が含まれています。

# LED.h
このヘッダーファイルにはLEDクラスを定義しています。
・ledLevel:LEDの明るさを表すレベル
・LED():クラスのインスタンスを初期化
・setLedLevel:LEDの明るさレベルを設定する関数
・getLedLevel():現在のLEDの明るさレベルを返す関数
