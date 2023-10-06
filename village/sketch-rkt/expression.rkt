#!/usr/bin/env racket

#lang racket

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (main argc argv)
  (define coding-age 2) ; define a variable with the integer value 2

  ;;; The assignment operation is discouraged in the functional programming
  #;(set! coding-age (+ coding-age 3))
  
  (printf "Given that you have already been learning coding for ~a years.~n" coding-age)
  (printf "Thus, your coding age would be ~a after another ~a years.~n" (+ coding-age 3) 3)
  
  0)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(module+ main
  (exit (main (vector-length (current-command-line-arguments))
              (current-command-line-arguments))))
