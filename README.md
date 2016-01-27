C-Lisp
======

Basic lisp interpreter (Racket dialect) written in C.

Features
--------

* It supports lists, numbers, strings and lambdas
* Basic STL to manipulate basic types
* Simple I/O library.
* Unit testing library.

How can I compile?
------------------

```
cmake .
```

If you want to compile using basic stl, so compile it using WITH_PRELUDE flag.

```
cmake . -DWITH_PRELUDE=ON
```

In the same way you can remove the support for filesystem operations.

```
cmake . -DWITH_FILESYSTEM=OFF
```

How can I write a program?
--------------------------

There are two basic ways to write programs using C-Lisp.

* Using REPL

```
./clisp


> (+ 1 1)
2

> (+ 1 2)
3
```

* Using a clisp file that contains a script

```
./clisp myprogram.clisp
```
