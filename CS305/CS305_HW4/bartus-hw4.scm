
;1
;- Procedure: main-procedure
;- Input : Takes only one parameter named tripleList
;- Output : Returns list of triples according to the scenario
; described in section 3.
; Returns an error if the given parameter is not a tripleList.

(define main-procedure
  (lambda (tripleList)
    (if ( or (null? tripleList) (not (list? tripleList)) )
      (error "ERROR305: the input should be a list full of triples")
      (if (check-triple? tripleList)
        (sort-area (filter-pythagorean (filter-triangle (sort-all-triples tripleList)))) 

        ;first sort the triples 
        ;then filter the ones that are triangles 
        ;then filter the right triangles 
        ;then calculate the are of them and sort them in ascendign order

        (error "ERROR305: the input should be a list full of triples")
      )
    )
  )
)

;2
;- Procedure: check-triple?
;- Input : Takes only one parameter named tripleList
;- Output : Returns true if the given parameter consists of triples,
; returns false if otherwise.

(define check-triple?
  (lambda (tripleList)
    (if (null? tripleList)
      #t
      (if ( and (check-length? (car tripleList) 3 ) (check-sides? (car tripleList)) ) 
            (check-triple? (cdr tripleList))
            #f
      )
    )
  )
)

;3
;- Procedure: check-length?
;- Input : Takes two parameters as inTriple and count
;- Output : Returns true if the length of the given list
; equals to count, returns false if otherwise.

(define len
  (lambda (lst)
    (if (null? lst)
        0
        ( + 1 (len (cdr lst)) )
    )
  )
)

(define (check-length? inTriple count)
  ( = (len inTriple) count )
)

;4
;- Procedure: check-sides?
;- Input : Takes only one parameter named inTriple
;- Output : It returns true if all of the elements in the given
; list are numbers and each of the numbers is greater than zero.
; It returns false if otherwise.


(define check-sides? 
  (lambda (triples)
    (if (null? triples)
      #t       
      (if ( and (integer? (car triples)) (> (car triples) 0 ) )
          (check-sides? (cdr triples))
          #f
      )
    )
  )
)

;5
;- Procedure: sort-all-triples
;- Input : Takes only one parameter named tripleList
;- Output : Returns the list of triples given as the parameter in which
; all triples are sorted internally in ascending order.

(define (sort-all-triples tripleList)
  (if (null? tripleList)
      '()
      ( cons (sort-triple (car tripleList)) (sort-all-triples (cdr tripleList)) )
  )
)


;6
;- Procedure: sort-triple
;- Input : Takes only one parameter named inTriple
;- Output : It returns the sorted inTriple in ascending order.

(define sort-triple
  (lambda (inTriple)
    (let (
          (a (car inTriple))
          (b (cadr inTriple))
          (c (caddr inTriple))
         )
      (cond ((and (<= a b) (<= b c)) (list a b c))
            ((and (<= a c) (<= c b)) (list a c b))
            ((and (<= b a) (<= a c)) (list b a c))
            ((and (<= b c) (<= c a)) (list b c a))
            ((and (<= c a) (<= a b)) (list c a b))
            (else (list c b a))
      )
    )
  )
)


;7
;- Procedure: filter-triangle
;- Input : Takes only one parameter named tripleList
;- Output : It returns tripleList consists of triples that each triple represents
; a triangle. So, it filters triangles in intripleList and discards other triples.

(define filter-triangle
  (lambda (tripleList)
    (if (null? tripleList)
      `()
      (if (triangle? (car tripleList))
        ( cons (car tripleList) (filter-triangle (cdr tripleList)) )
        (filter-triangle (cdr tripleList))
      )
    )
  )
)

;8
;- Procedure: triangle?
;- Input : Takes only one parameter named triple
;- Output : It returns true if the given triple satisfies the triangle rule,
; returns false if otherwise.

(define triangle?
  (lambda (triple)
    (if (> (+ (cadr triple) (car triple)) (caddr triple)) 
      #t
      #f
    )
  )
)

;9
;- Procedure: filter-pythagorean
;- Input : Takes only one parameter named tripleList
;- Output : It returns tripleList consists of triples that each triple represents
; a pythagorean triangle. So, it filters pythagorean triangles in intripleList
; and discards other triples.

(define filter-pythagorean
  (lambda (tripleList)
    (if (null? tripleList)
      `()
      (if (pythagorean-triangle? (car tripleList))
        ( cons (car tripleList) (filter-pythagorean (cdr tripleList)) )
        (filter-pythagorean (cdr tripleList))
      )
    )
  )
)

;10
;- Procedure: pythagorean-triangle?
;- Input : Takes only one parameter named triple
;- Output : It returns true if the given triple satisfies the Pythagorean theorem,
; returns false if otherwise.


(define pythagorean-triangle?
  (lambda (triple)
    (let (
            (a (* (car triple) (car triple)))
            (b (* (cadr triple) (cadr triple)))
            (c (* (caddr triple) (caddr triple)))
          )
        (if (= (+ a b) c)
          #t
          #f
        ) 
    )
  )
)

;11
;- Procedure: sort-area
;- Input : Takes only one parameter named tripleList
;- Output : Returns the list of triples given as the parameter in which
; all triples are sorted according to the areas of the pythagorean triangles
; in ascending order.

(define sort-area
  (lambda (tripleList)
    ( sort tripleList (lambda (triple1 triple2) (< (get-area triple1) (get-area triple2))) )
  )
)


;12
;- Procedure: get-area
;- Input : Takes only one parameter named triple
;- Output : It returns the area of the given pythagorean triangle.

(define get-area
  (lambda (triple)
    (/ (* (car triple) (cadr triple)) 2)
  )
)


