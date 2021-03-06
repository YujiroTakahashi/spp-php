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
    public string decode ( array ids )
    public sampleEncode ( string word [, int size, float alpha] )
    public getPieceSize ()
    public pieceToId ( string word )
    public idToPiece ( int id )
    public isUnknown ( int id )
    public isControl ( int id )
    public setEncodeExtraOptions ( string option )
}
```

## Table of Contents


[Spp::__construct](#__construct)  
[Spp::load](#int-spploadstring-filename)  
[Spp::encode](#int-sppencode)  
[Spp::wakati](#string-sppwakati)  
[Spp::decode](#string-sppdecode)  
[Spp::sampleEncode](#int-sppsampleencode)  
[Spp::getPieceSize](#int-sppgetpiecesize)  
[Spp::pieceToId](#int-spppiecetoid)  
[Spp::idToPiece](#string-sppidtopiece)  
[Spp::isUnknown](#bool-sppisunknown)  
[Spp::isControl](#bool-sppiscontrol)  
[Spp::setEncodeExtraOptions](#bool-sppsetencodeextraoptions)  

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

$model = 'model/wiki8k.model';
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
    [0] => Array
        (
            [begin] => 0
            [end] => 3
            [id] => 582
            [piece] => ▁本
            [surface] => 本
        )

    [1] => Array
        (
            [begin] => 3
            [end] => 6
            [id] => 4001
            [piece] => 山
            [surface] => 山
        )

    [2] => Array
        (
            [begin] => 6
            [end] => 9
            [id] => 3784
            [piece] => は
            [surface] => は
        )

    [3] => Array
        (
            [begin] => 9
            [end] => 12
            [id] => 3775
            [piece] => 、
            [surface] => 、
        )

    [4] => Array
        (
            [begin] => 12
            [end] => 18
            [id] => 2962
            [piece] => 足利
            [surface] => 足利
        )

    [5] => Array
        (
            [begin] => 18
            [end] => 21
            [id] => 4221
            [piece] => 義
            [surface] => 義
        )

    [6] => Array
        (
            [begin] => 21
            [end] => 24
            [id] => 4575
            [piece] => 満
            [surface] => 満
        )

    [7] => Array
        (
            [begin] => 24
            [end] => 33
            [id] => 89
            [piece] => により
            [surface] => により
        )

    [8] => Array
        (
            [begin] => 33
            [end] => 36
            [id] => 4237
            [piece] => 建
            [surface] => 建
        )

    [9] => Array
        (
            [begin] => 36
            [end] => 39
            [id] => 3957
            [piece] => 立
            [surface] => 立
        )

    [10] => Array
        (
            [begin] => 39
            [end] => 48
            [id] => 24
            [piece] => された
            [surface] => された
        )

    [11] => Array
        (
            [begin] => 48
            [end] => 54
            [id] => 1517
            [piece] => 京都
            [surface] => 京都
        )

    [12] => Array
        (
            [begin] => 54
            [end] => 57
            [id] => 3774
            [piece] => の
            [surface] => の
        )

    [13] => Array
        (
            [begin] => 57
            [end] => 60
            [id] => 4182
            [piece] => 相
            [surface] => 相
        )

    [14] => Array
        (
            [begin] => 60
            [end] => 63
            [id] => 3877
            [piece] => 国
            [surface] => 国
        )

    [15] => Array
        (
            [begin] => 63
            [end] => 66
            [id] => 4443
            [piece] => 寺
            [surface] => 寺
        )

    [16] => Array
        (
            [begin] => 66
            [end] => 69
            [id] => 3780
            [piece] => 。
            [surface] => 。
        )

)
```

-----

### <a name="wakati">string Spp::wakati()

get the wakati.

```php
$encoded = $spp->wakati('本山は、足利義満により建立された京都の相国寺。');
print_r($encoded);
```

```php
"本 山 は 、 足利 義 満 により 建 立 された 京都 の 相 国 寺 。"
```

-----

### <a name="decode">string Spp::decode()

```php
$ids = [
    582,
    4001,
    3784,
    3775,
    2962,
    4221,
    4575,
    89,
    4237,
    3957,
    24,
    1517,
    3774,
    4182,
    3877,
    4443,
    3780
];
$decoded = $spp->decode($ids);
print_r($decoded);
```

```php
本山は、足利義満により建立された京都の相国寺。
```

-----

### <a name="sampleEncode">int Spp::sampleEncode()

-----

### <a name="getPieceSize">int Spp::getPieceSize()

```php
echo $spp->getPieceSize();
```

```php
8000
```

-----

### <a name="pieceToId">int Spp::pieceToId()

```php
echo $spp->pieceToId("森");
```

```php
4735
```

-----

### <a name="idToPiece">string Spp::idToPiece()

```php
echo $spp->idToPiece(4042);
```

```php
海
```

-----

### <a name="isUnknown">bool Spp::isUnknown()

```php
$spp->isUnknown(0);  // <unk>
```

```php
true
```

```php
$spp->isUnknown(582);
```

```php
false
```

-----

### <a name="isControl">bool Spp::isControl()

```php
$spp->isControl(7000);  // <s>, </s>
```

```php
false
```

-----

### <a name="setEncodeExtraOptions">bool Spp::setEncodeExtraOptions()

```php
$spp->setEncodeExtraOptions("bos:eos");
```

