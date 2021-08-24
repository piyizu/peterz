; This program is going to compute the depth of a list, 
; where the depth of the list is equal to the largest number of open left parentheses.
; It mainly only uses car, cdr and some recursions. 
(define (depth list)
    (if (or (not (list? list) ) (null? list) )
        0
        (if (list? (car list))
            (max (+ 1 (depth (car list))) (depth (cdr list)))
            (max 1 (depth (cdr list)) )
        )
    )
)

(display (depth '(this (list (has (substance))))) )
(display #\newline)
(display (depth 2) )
(exit)