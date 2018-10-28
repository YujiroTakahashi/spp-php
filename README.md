# Spp-php

Spp-php is a PHP bindings for SentencePieceProcessor.

[SentencePieceProcessor](https://github.com/google/sentencepiece) a Unsupervised text tokenizer for Neural Network-based text generation.

## Requirements

pkg-config  
protobuf-compiler  
libprotobuf10  
libprotobuf-dev  
libgoogle-perftools-dev  
libsentencepiece  

```
$ git clone https://github.com/google/sentencepiece.git
$ cd sentencepiece
$ mkdir build
$ cd build
$ cmake ..
$ make -j $(nproc)
$ sudo make install
```

## Building SentencePieceProcessor for PHP

```
$ cd spp-php
$ phpize
$ ./configure
$ make
$ sudo make install
```

edit your php.ini and add:

```
extension=spp.so
```

## Class synopsis

```php
Jumanpp {
    public __construct ( void )
    public int load ( string filename )
    public array encode ( string word )
}
```

## Table of Contents

[Jumanpp::__construct](#__construct)  
[Jumanpp::load](#load)  
[Jumanpp::encode](#encode)  

-----

### <a name="__construct">Jumanpp::__construct()

Instantiates a Jumanpp object.

```php
$jpp = new Jumanpp();
```

-----

### <a name="load">int Jumanpp::load(string filename)

load a model.

```php
$model = 'result/model.bin';
$jpp->load($model);
```

-----

### <a name="encode">int Jumanpp::encode()

get the encoded.

```php
$encoded = $jpp->encode('魅力がたっぷりと詰まっている');
print_r($encoded);
```

```php
Array
(
    [0] => Array
        (
            [baseform] => 魅
            [canonicForm] => 魅せ/魅せv
            [conjForm] => *
            [conjType] => *
            [pos] => 名詞
            [reading] => 魅せ
            [subpos] => 普通名詞
            [subtext] => Array
                (
                    [0] => テキスト
                    [1] => 魅せる/魅せる
                )

            [surface] => 魅
        )

    [1] => Array
        (
            [baseform] => 力
            [canonicForm] => 力/ちから
            [conjForm] => *
            [conjType] => *
            [pos] => 名詞
            [reading] => ちから
            [subpos] => 普通名詞
            [subtext] => Array
                (
                    [0] => 抽象物
                    [1] => 訓
                )

            [surface] => 力
        )

    [2] => Array
        (
            [baseform] => が
            [canonicForm] =>
            [conjForm] => *
            [conjType] => *
            [pos] => 助詞
            [reading] => が
            [subpos] => 格助詞
            [surface] => が
        )

    [3] => Array
        (
            [baseform] => たい
            [canonicForm] => たい/たい
            [conjForm] => 語幹
            [conjType] => イ形容詞アウオ段
            [pos] => 接尾辞
            [reading] => た
            [subpos] => 形容詞性述語接尾辞
            [surface] => た
        )

    [4] => Array
        (
            [baseform] => っぷり
            [canonicForm] => 振り/ぶり
            [conjForm] => *
            [conjType] => *
            [pos] => 接尾辞
            [reading] => っぷり
            [subpos] => 名詞性名詞接尾辞
            [surface] => っぷり
        )

    [5] => Array
        (
            [baseform] => と
            [canonicForm] =>
            [conjForm] => *
            [conjType] => *
            [pos] => 助詞
            [reading] => と
            [subpos] => 接続助詞
            [surface] => と
        )

    [6] => Array
        (
            [baseform] => 詰る
            [canonicForm] => 詰る/なじる
            [conjForm] => 語幹
            [conjType] => 子音動詞ラ行
            [pos] => 動詞
            [reading] => なじ
            [subpos] => *
            [surface] => 詰
        )

    [7] => Array
        (
            [baseform] => ます
            [canonicForm] => 増す/ます
            [conjForm] => 語幹
            [conjType] => 子音動詞サ行
            [pos] => 動詞
            [reading] => ま
            [subpos] => *
            [subtext] => Array
                (
                    [0] => 動詞:減らす/へらす;動詞:減る/へる
                )

            [surface] => ま
        )

    [8] => Array
        (
            [baseform] => って
            [canonicForm] =>
            [conjForm] => *
            [conjType] => *
            [pos] => 助詞
            [reading] => って
            [subpos] => 副助詞
            [surface] => って
        )

    [9] => Array
        (
            [baseform] => いる
            [canonicForm] => いる/いる
            [conjForm] => 基本形
            [conjType] => 母音動詞
            [pos] => 接尾辞
            [reading] => いる
            [subpos] => 動詞性接尾辞
            [surface] => いる
        )

)
```
