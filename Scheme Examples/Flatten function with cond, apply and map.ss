; use apply and map to implement flatten function
(define (flatten ls)
    (cond 
        ( (not (list? ls)) (list ls) ) ;first check if ls is a list
        ( (null? ls) ls)               ;then check if list ls is an empty list
        (else (apply append (map flatten ls)) )
    )
)

(display (flatten '(1 2 (3 ((((8))))) 4)) )
(exit)

; 'ls' in the definition of flatten used to be 'list'.
; But we know that 'list' is the name of a bulit-in function.
; An error occurs when we use 'list' instead of 'ls'.
; This may be caused by the implementation of map or append.