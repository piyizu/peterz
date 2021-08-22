; mergesort in Scheme
; comp is the argument for something like comparison operator
; merge function is like that in C language
(define (merge list1 list2 comp)
    (cond 
        ((null? list1) list2)
        ((null? list2) list1)
        (else
            (if (comp (car list1) (car list2))
                (cons (car list1) (merge (cdr list1) list2 comp))
                (cons (car list2) (merge list1 (cdr list2) comp))
            ) 
        )
    )
)

; lift-n function is evaluated to a list of the first n-of-left
; elements of list with the same order
(define (left-n list n-of-left)
    (if (zero? n-of-left)
        '()
        (cons (car list) (left-n (cdr list) (- n-of-left 1)))
    )
)

; right-n function is evaluated to a list rid of the first
; n-of-left elements of list without changing the order
(define (right-n list n-of-left)
    (if (zero? n-of-left)
        list
        (right-n (cdr list) (- n-of-left 1))
    )
)

; mergesort function is like that in C language
; comp means the same as in merge function
(define (mergesort list comp)
    (let 
        ( (n-of-left (quotient (length list) 2)) )
        (if (not (zero? n-of-left))
            (let
                ( (leftlist (mergesort (left-n list n-of-left) comp))
                  (rightlist (mergesort (right-n list n-of-left) comp))
                )
                (merge leftlist rightlist comp)
            )
            list
        )
    )
)

(display (mergesort '(3.4 5 89 -9 1.7 1000 -3 4 5 8 9) <= ) )
(exit)