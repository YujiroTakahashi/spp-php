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
Spp {
    public __construct ( void )
    public int load ( string filename )
    public array encode ( string word )
    public string wakati ( string word )
}
```

## Table of Contents

[Spp::__construct](#__construct)  
[Spp::load](#load)  
[Spp::encode](#encode)  
[Spp::wakati](#wakati)  

-----

### <a name="__construct">Spp::__construct()

Instantiates a Spp object.

```php
$spp = new Spp();
```

-----

### <a name="load">int Spp::load(string filename)

load a model.

```php
$model = 'result/model.bin';
$spp->load($model);
```

-----

### <a name="encode">int Spp::encode()

get the encoded.

```php
$encoded = $spp->encode('本山は、足利義満により建立された京都の相国寺。');
print_r($encoded);
```

```php
Array
(
    [0] => ▁本
    [1] => 山
    [2] => は
    [3] => 、
    [4] => 足利
    [5] => 義
    [6] => 満
    [7] => により
    [8] => 建
    [9] => 立
    [10] => された
    [11] => 京都
    [12] => の
    [13] => 相
    [14] => 国
    [15] => 寺
    [16] => 。
)
```

-----

### <a name="wakati">int Spp::wakati()

get the wakati.

```php
$encoded = $spp->wakati('本山は、足利義満により建立された京都の相国寺。');
print_r($encoded);
```

```php
"本 山 は 、 足利 義 満 により 建 立 された 京都 の 相 国 寺 。"
```
