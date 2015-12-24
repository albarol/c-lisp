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
