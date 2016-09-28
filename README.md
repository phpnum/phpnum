# phpnum

[![Build Status](https://travis-ci.org/phpnum/phpnum.svg?branch=master)](https://travis-ci.org/phpnum/phpnum)

A PHP extension for scientific computing. Inspired by [NumPy](https://github.com/numpy/numpy) & [NumPHP](https://github.com/NumPHP/NumPHP).

[查看中文文档](https://github.com/phpnum/phpnum/blob/master/README.zh.md)

# Table of contents
-----
1. [Installing/Configuring](#installingconfiguring)
   * [Requirement](#requirement)
   * [Installation](#installation)
2. [Classes and methods](#classes-and-methods)
   * [Usage](#usage)
   * [Characteristics](#characteristics)
   * [Statistics](#statistics)
   * [Arithmetic Operations](#arithmetic-operations)
   * [Maths](#maths)

-----

# Installing/Configuring
-----

Everything you should need to install phpnum on your system.

## requirement
- PHP 7 +

## Installation

~~~
phpize
./configure
make && make install
~~~

`make install` copies `num.so` to an appropriate location, but you still need to enable the module in the PHP config file. To do so, either edit your php.ini or add a num.ini file in `/path/to/php.d` with the following contents: `extension=num.so`.

# Classes and methods

-----

## Usage

1. [Class Num](#class-num) - Creates a Num object
2. [Class NumNdarray](#class-numndarray) - Creates a N-dimensional array (ndarray) object
3. [Printing](#printing) - Prints a ndarray object

### Class Num
-----
_**Description**_: Creates a Num object

##### *Example*

~~~
$num = new Num();
~~~

### Class NumNdarray
-----
_**Description**_: Creates a N-dimensional array (ndarray) object

##### *Parameters*
array: *Array*

##### *Return value*

ndarray: *Object*

##### *Example*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
~~~
### Printing
-----
_**Description**_: Prints a ndarray object

##### *Example*

~~~
$num = new Num();
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
echo $ndarray;
/* output: 
array([
  [1,2,3],
  [2,3,4]
])
*/
~~~



## Characteristics

1. [getData](#getdata) - Data of the ndarray
2. [getShape](#getshape) - Shape of ndarray dimensions
3. [getNdim](#getndim) - Number of ndarray dimensions
4. [getSize](#getsize) - Number of elements in the ndarray

### getData
-----
_**Description**_: Data of the ndarray

##### *Parameters*
None

##### *Return value*
data: *Array*

##### *Example*

~~~
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getData(); // returns array([1.0, 2, 3], [2, 3, 4])
~~~

### getShape
-----
_**Description**_: Shape of ndarray dimensions

##### *Parameters*
None

##### *Return value*
shape: *Array*

##### *Example*

~~~
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getShape(); // returns array(2, 3)
~~~

### getNdim
-----
_**Description**_: Number of ndarray dimensions

##### *Parameters*
None

##### *Return value*
ndim: *LONG*

##### *Example*

~~~
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getNdim(); // returns 2
~~~

### getSize
-----
_**Description**_: Number of elements in the ndarray

##### *Parameters*
None

##### *Return value*
size: *LONG*

##### *Example*

~~~
$ndarray = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$ndarray->getSize(); // returns 6
~~~



## Statistics

1. [amin](#amin) - Return the minimum of an array
2. [amax](#amin) - Return the maximum of an array

### amin
-----
_**Description**_: Return the minimum of an array

##### *Parameters*
ndarray: *Object*

##### *Return value*
amin: *Double*

##### *Example*

~~~
$ndarray = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
$num->min($ndarray); // returns 1
~~~

### amax
-----
_**Description**_: Return the maximum of an array

##### *Parameters*
ndarray: *Object*

##### *Return value*
amax: *Double*

##### *Example*

~~~
$ndarray = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
$num->sqrt($ndarray);
echo $ndarray;
~~~



## Arithmetic Operations

1. [add](#add) - Add an array to an other ndarray
2. [sub](#sub) - Subtract an array from an other ndarray
3. [mult](#mult) - Multiply an array by an other ndarray
4. [div](#div) - an array divided by an other ndarray

### add

------

_**Description**_: Add an array to an other ndarray

##### *Parameters*

ndarray: *Object*

##### *Return value*

ndarray: *Object*

##### *Example*

```
$a = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$b = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
echo $a->add($b);
/* output:
array([
  [4.2,3.5,4],
  [4.5,7,6]
])
*/
```

### sub

------

_**Description**_: Subtract an array from an other ndarray

##### *Parameters*

ndarray: *Object*

##### *Return value*

ndarray: *Object*

##### *Example*

```
$a = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$b = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
echo $a->sub($b);
/* output:
array([
  [-2.2,0.5,2],
  [-0.5,-1,2]
])
*/
```

### mult

------

_**Description**_: Multiply an array by an other ndarray

##### *Parameters*

ndarray: *Object*

##### *Return value*

ndarray: *Object*

##### *Example*

```
$a = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$b = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
echo $a->mult($b);
/* output:
array([
  [3.2,3,3],
  [5,12,8]
])
*/
```

### div

------

_**Description**_: an array divided by an other ndarray

##### *Parameters*

ndarray: *Object*

##### *Return value*

ndarray: *Object*

##### *Example*

```
$a = $num->array([[1.0, 2, 3], [2, 3, 4]]);
$b = $num->array([[3.2, 1.5, 1], [2.5, 4, 2]]);
echo $a->div($b);
/* output:
array([
  [0.3125,1.3333333333333,3],
  [0.8,0.75,2]
])
*/
```




## Maths

1. [power](#power) - First array elements raised to powers from second array, element-wise
2. [square](#square) - Return the element-wise square of the input
3. [sqrt](#sqrt) - Return the positive square-root of an array, element-wise
4. [exp](#exp) - Calculate the exponential of all elements in the input array
5. [log](#log) - Natural logarithm, element-wise
6. [sin](#sin) - Trigonometric sine, element-wise
7. [cos](#cos) - Cosine element-wise
8. [tan](#tan) - Compute tangent element-wise
9. [ceil](#ceil) - Return the ceiling of the input, element-wise
10. [floor](#floor) - Return the floor of the input, element-wise

### power

------

_**Description**_: First array elements raised to powers from second array, element-wise

##### *Parameters*

base: *Object*

exponent: *Object* or *Double*

##### *Return value*

array: *Array*

##### *Example*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->power($ndarray, 3);
// returns array([[0.125, 1.0], [0.0, 8.0]])
```

### square

------

_**Description**_: Return the element-wise square of the input

##### *Parameters*

ndarray: *Object*

##### *Return value*

array: *Array*

##### *Example*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->square($ndarray);
// returns array([[0.5, 1.0], [0.0, 4.0]])
```

### sqrt

------

_**Description**_: Return the positive square-root of an array, element-wise

##### *Parameters*

ndarray: *Object*

##### *Return value*

array: *Array*

##### *Example*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->sqrt($ndarray);
// returns array([[0.70710678118654757, 1.0], [0.0, 1.4142135623730951]])
```

### exp

------

_**Description**_: Calculate the exponential of all elements in the input array

##### *Parameters*

ndarray: *Object*

##### *Return value*

array: *Array*

##### *Example*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->exp($ndarray);
// returns array([[1.6487212707001282, 2.7182818284590451], [1.0, 7.3890560989306504]])
```

### log

------

_**Description**_: Natural logarithm, element-wise

##### *Parameters*

ndarray: *Object*

##### *Return value*

array: *Array*

##### *Example*

```
$ndarray = $num->array([[0.5, 1], [10, 2]]);
$num->log($ndarray);
// returns array([[-0.69314718055994529, 0.0], [2.3025850929940459, 0.69314718055994529]])
```

### sin

------

_**Description**_: Trigonometric sine, element-wise

##### *Parameters*

ndarray: *Object*

##### *Return value*

array: *Array*

##### *Example*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->sin($ndarray);
// returns array([[0.47942553860420301, 0.8414709848078965], [0.0, 0.90929742682568171]])
```

### cos

------

_**Description**_: Cosine element-wise

##### *Parameters*

ndarray: *Object*

##### *Return value*

array: *Array*

##### *Example*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->cos($ndarray);
// returns array([[0.87758256189037276, 0.54030230586813977], [1.0, -0.41614683654714241]])
```

### tan

------

_**Description**_: Compute tangent element-wise

##### *Parameters*

ndarray: *Object*

##### *Return value*

array: *Array*

##### *Example*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->tan($ndarray);
// returns array([[0.54630248984379048, 1.5574077246549023], [0.0, -2.1850398632615189]])
```

### ceil

------

_**Description**_: Return the ceiling of the input, element-wise

##### *Parameters*

ndarray: *Object*

##### *Return value*

array: *Array*

##### *Example*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->ceil($ndarray);
// returns array([[1.0, 1.0], [0.0, 2.0]])
```

### floor

------

_**Description**_: Return the floor of the input, element-wise

##### *Parameters*

ndarray: *Object*

##### *Return value*

array: *Array*

##### *Example*

```
$ndarray = $num->array([[0.5, 1], [0, 2]]);
$num->floor($ndarray);
// returns array([[0.0, 1.0], [0.0, 2.0]])
```

