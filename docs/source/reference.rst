Reference
=========

Basic reference manual of functions supported.

Boolean
-------

.. py:function:: (bool? v)

    Check if value is boolean

    .. code-block:: racket

        > (bool? #t)
        #t
        > (bool? 1)
        #f

.. py:function:: (eq v1 v2)

    Compare equality between two values

    .. code-block:: racket

        > (eq 1 2)
        #f
        > (eq 1 1)
        #t
        > (eq 1 #t)
        #f

.. py:function:: (ne v1 v2)

    Compare inequality between two values

    .. code-block:: racket

        > (ne 1 2)
        #t
        > (ne 1 1)
        #f
        > (ne 1 #t)
        #t

.. py:function:: (not v)

    Inverse of boolean value

    .. code-block:: racket

        > (not #t)
        #f
        > (not #f)
        #t
        > (not 1)
        Error: Wrong argument type. Got: Number, Expected: Boolean

.. py:function:: (and v1 v2)

    Logical and operation

    .. code-block:: racket

        > (and #t #t)
        #t
        > (and #f #t)
        #f
        > (and #t 1)
        Error: Wrong argument type. Got: Number, Expected: Boolean

.. py:function:: (or v1 v2)

    Logical or operation

    .. code-block:: racket

        > (or #t #t)
        #t
        > (or #f #f)
        #f
        > (or #t 1)
        Error: Wrong argument type. Got: Number, Expected: Boolean

.. py:function:: (xor v1 v2)

    Logical xor operation

    .. code-block:: racket

        > (xor #t #t)
        #f
        > (xor #t #f)
        #t
        > (xor #t 1)
        Error: Wrong argument type. Got: Number, Expected: Boolean

.. py:function:: (nand v1 v2)

    Logical nand operation

    .. code-block:: racket

        > (nand #t #t)
        #f
        > (nand #f #f)
        #t
        > (nand #t 1)
        Error: Wrong argument type. Got: Number, Expected: Boolean

.. py:function:: (nor v1 v2)

    Logical nor operation

    .. code-block:: racket

        > (nor #t #t)
        #f
        > (nor #f #f)
        #t
        > (nor #t 1)
        Error: Wrong argument type. Got: Number, Expected: Boolean

Error
-----

.. py:function:: (error? v)

    Check if the value is an error

    .. code-block:: racket

        > (error? (error "Some error"))
        #t
        > (error? #t)
        #f

.. py:function:: (error message)

    Create error object

    .. code-block:: racket

        > (error "Some error")
        Error: Some error
        > (error 1)
        Error: Wrong argument type. Got: Number, Expected: String

Input/Output
------------

.. py:function:: (display t)

    Display info about type

    .. code-block:: racket

        > (display 1)
        Number -> 1
        > (display [1 2 3 4])
        List -> [1 2 3 4]

.. py:function:: (print t)

    Print type value

    .. code-block:: racket

        > (print 1)
        1
        > (print [1 2 3 4])
        [1 2 3 4]
        > (print +)
        <builtin>

.. py:function:: (load file)

    Load clisp script

    .. code-block:: racket

        > (load "stl/prelude.clisp")
        > (pi)
        3.1415

List
----

.. py:function:: (list? v)

    Check if value is a list

    .. code-block:: racket

        > (list? [1 2 3 4])
        #t
        > (list? 1)
        #f

.. py:function:: (list e1 ...)

    Create a list of elements

    .. code-block:: racket

        > (list 1 2 3 4 5)
        [1 2 3 4 5]

.. py:function:: (head xs)

    Get the first element of a list

    .. code-block:: racket

        > (head [1 2 3 4 5])
        1
        > (head 1)
        Error: Wrong argument type. Got: Number, Expected: List

.. py:function:: (tail xs)

    Discard the first element of a list

    .. code-block:: racket

        > (tail [1 2 3 4])
        [2 3 4]
        > (tail 1)
        Error: Wrong argument type. Got: Number, Expected: List

.. py:function:: (append xs el)

    Append an element in the list

    .. code-block:: racket

        > (append [1 2 3 4] 5)
        [1 2 3 4 5]
        > (append 1 1)
        Error: Wrong argument type. Got: Number, Expected: List


.. py:function:: (length xs)

    Get the number of elements in the list

    .. code-block:: racket

        > (length [1 3 4])
        3
        > (length 1)
        Error: Wrong argument type. Got: Number, Expected: List

.. py:function:: (empty? xs)

    Check if the list is empty

    .. code-block:: racket

        > (empty? [])
        #t
        > (empty? [1])
        #f
        > (empty? 1)
        Error: Wrong argument type. Got: Number, Expected: List

.. py:function:: (cons el xs)

    Get two elements and create one list

    .. code-block:: racket

        > (cons 1 2)
        [1 2]
        > (cons 1 [2 3])
        [1 2 3]

Number
------

.. py:function:: (number? v)

    Check if value is number

    .. code-block:: racket

        > (number? 1)
        #t
        > (number? #t)
        #f

.. py:function:: (zero? v)

    Check if value is equal to zero

    .. code-block:: racket

        > (zero? 0)
        #t
        > (zero? 1)
        #f
        > (zero? #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (positive? v)

    Check if value is positive

    .. code-block:: racket

        > (positive? -1)
        #f
        > (positive? 1)
        #t
        > (positive? #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (negative? v)

    Check if value is negative

    .. code-block:: racket

        > (negative? 1)
        #f
        > (negative? -1)
        #t
        > (negative? #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (even? v)

    Check if value is even

    .. code-block:: racket

        > (even? 1)
        #f
        > (even? 2)
        #t
        > (even? #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (odd? v)

    Check if value is odd

    .. code-block:: racket

        > (odd? 1)
        #t
        > (odd? 2)
        #f
        > (odd? #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (> v1 v2)

    Check if v1 is greater than v2

    .. code-block:: racket

        > (> 1 2)
        #f
        > (> 2 1)
        #t
        > (> 1 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (>= v1 v2)

    Check if v1 is greater or equal v2

    .. code-block:: racket

        > (>= 1 2)
        #f
        > (>= 2 2)
        #t
        > (>= 1 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (< v1 v2)

    Check if v1 is lesser than v2

    .. code-block:: racket

        > (< 1 2)
        #t
        > (< 2 2)
        #f
        > (< 1 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (<= v1 v2)

    Check if v1 is lesser or equal v2

    .. code-block:: racket

        > (<= 1 2)
        #t
        > (<= 2 2)
        #t
        > (<= 1 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

Math
----

.. py:function:: (+ v1 v2)

    Sum two numbers

    .. code-block:: racket

        > (+ 1 2)
        3
        > (+ 1 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (- v1 v2)

    Subtract two numbers

    .. code-block:: racket

        > (- 2 1)
        1
        > (- 1 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (* v1 v2)

    Multiply two numbers

    .. code-block:: racket

        > (* 2 1)
        2
        > (* 1 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (/ v1 v2)

    Divide two numbers

    .. code-block:: racket

        > (/ 2 1)
        2
        > (/ 1 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (% v1 v2)

   Rest of division

    .. code-block:: racket

        > (% 10 3)
        1
        > (% 1 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (^ v1 v2)

    Power of a number

    .. code-block:: racket

        > (^ 10 3)
        1000
        > (^ 1 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (ceil v)

    Round number to ceiling

    .. code-block:: racket

        > (ceil 2.1)
        3
        > (ceil #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (floor v)

    Round number to floor

    .. code-block:: racket

        > (floor 2.9)
        2
        > (floor #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (round v)

    Round number

    .. code-block:: racket

        > (round 2.3)
        2
        > (round 2.7)
        3
        > (round #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (sqrt v)

    Square root

    .. code-block:: racket

        > (sqrt 4)
        2
        > (sqrt #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (log10 v)

    Logarithm base 10

    .. code-block:: racket

        > (log10 1000)
        3
        > (log10 #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (log v)

    Natural logarithm

    .. code-block:: racket

        > (log 1)
        0
        > (log #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (sin v)

    Sine of a radian

    .. code-block:: racket

        > (sin 3.1415)
        0
        > (sin #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (cos v)

    Cosine of a radian

    .. code-block:: racket

        > (cos 3.1415)
        1
        > (cos #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (tan v)

    Tangent of a radian

    .. code-block:: racket

        > (tan 0.7854)
        1
        > (tan #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

.. py:function:: (abs v)

    Absolute value of a number

    .. code-block:: racket

        > (abs -1)
        1
        > (abs 1)
        1
        > (abs #t)
        Error: Wrong argument type. Got: Boolean, Expected: Number

