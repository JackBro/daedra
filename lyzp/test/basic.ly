;; Collection of misc tests for lexer/parser verification


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Comment tests
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; one semi-colon
;; two semi-colons
;;; three semi-colons
;;;; four semi-colons
;;;;; five semi-colons
;;;;;; six semi-colons
;;;;;;; seven semi-colons
;;;;;;;; eight semi-colons
;;;;;;;;; nine semi-colons
;;;;;;;;;; ten semi-colons


; one semi-colon ;
;; two semi-colons ;;
;;; three semi-colons ;;;
;;;; four semi-colons ;;;;
;;;;; five semi-colons ;;;;;
;;;;;; six semi-colons ;;;;;;
;;;;;;; seven semi-colons ;;;;;;;
;;;;;;;; eight semi-colons ;;;;;;;;
;;;;;;;;; nine semi-colons ;;;;;;;;;
;;;;;;;;;; ten semi-colons ;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; COMMENT TEST
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;; At the top of source files
;;; Comments at the beginning of the line
;; Comments indented along with code
;(do-something a)                      ; Comments indented at column 40, or the last
;  (do-something-else b))              ; column + 1 space if line exceeds 38 columns
;; ()
;;; (1)
;;;; __some-string__
;; 10 ; Atom
; Commented out line ;
  ; commenting (until end of line)
    ; another comment
      ; yet another comment
        ; comment indented with tabs
          ;
          ;
        ;                           
        



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Whitespace tests
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
()
( ) ; Space character between parens
( ) ; Tab character between parens
(
)
(  )
(   )
(        )
((       ))
( ( ) )
    (    (  )  ( )  (    )     () )
      (    (  )  ( )  (  ()  )     (     )  (  )    )     


( ( ())
  ( (() () ())
    ()
    (() ( ) (  ) (   ) (    ))))


()
(())
((()))
(() ())
(1)
(1 2)
'(1 2 3)
(+ 1 2)
(- 1 2)
(* 1 2)
(/ 1 2)
((1) (2) (3))
(this "Canonical S-expression" has 5 atoms)
