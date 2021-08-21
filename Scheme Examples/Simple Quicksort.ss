; quicksort in scheme

;Example: function partition evaluate (3 0 1) with pivot 1 to ((0 1) (3))
;Such results can be seen when you de-comment the "begin" line
(define (partition pivot num-list) ; we assume pivot is not part of num-list
    (if (null? num-list)
        '(() ())
        (let
            ( (rest-partitioned (partition pivot (cdr num-list))) )
            (if (<= (car num-list) pivot)
                (list (cons (car num-list) (car rest-partitioned)) (cadr rest-partitioned) )
                (list (car rest-partitioned) (cons (car num-list) (cadr rest-partitioned)) )
            )
        )
    )
)
(define (sort num-list)
    (if (< (length num-list) 1)
        num-list
        (let 
            ( (partitioned (partition (car num-list) (cdr num-list))) ) ;cdr here is necessary
            ;(begin (display (car num-list)) (display #\space) (display partitioned) (display #\newline) )
            (append
                (sort (car partitioned) )
                (list (car num-list))
                (sort (cadr partitioned))
            )
        )
    )
)
(display (sort '(-1 -10 2 100 8 7 5 3 4 5 6)) )
(exit)