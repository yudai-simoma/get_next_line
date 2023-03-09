# get_next_line

#### 概要
  * ファイル読み込みもしくは標準入力で読み込んだ文字を出力するプログラム
  
    1回でBUFFER_SIZE分文字を読み、改行もしくはEOFが読み込まれたら出力する（1行ずつ出力）

#### 使用言語
  * C
  
#### 提出ディレクトリ
  * /get_next_line

#### 作成ファイル
  * 必須課題：3
    * ```
      get_next_line.c, get_next_line_utils.c, get_next_line.h
      ```

  * ボーナス課題：3
    * ```
      get_next_line_bonus.c, get_next_line_utils_bonus.c, get_next_line_bonus.h
      ```

#### プログラム実行方法
  * ```
    コンパイル方法
      main.c 及び test.txtを/get_next_lineに格納し以下のコマンドを実行
        cc main.c get_next_line.c get_next_line_utils.c
      以下コマンドで実行
        ./a.out
      実行結果
        test.txtの中身が一行ずつ全て出力される
    ```

#### プログラム実行結果
