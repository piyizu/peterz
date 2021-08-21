; Use scheme ./filename.ss to execute the program
; This program expand a potentially nested list to a non-nested list
; without changing the sequence of the elements.

(define (flatten oplist)
    (if (null? oplist) ;if it is an empty list, just evaluate it.
        oplist
        (if (list? (car oplist) )
            ;if it is not empty and the 'car oplist' is a list,
            ;expand 'car oplist' and 'cdr oplist', then connect them.
            (append (flatten (car oplist)) (flatten (cdr oplist)) )
            ;if it is not empty and the 'car oplist' is not a list,
            ;construct a list with 'car oplist' and expanded 'cdr oplist'.
            (cons (car oplist) (flatten (cdr oplist)) )
        )
    )
)
(display (flatten '(1 "s" (3 4) (2 (3)) ((4)) () ) ) )
(exit)
