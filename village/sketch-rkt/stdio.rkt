#!/usr/bin/env racket

#lang racket

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (main argc argv)
  (printf "Could you please tell me your name: ")
  (define name (read))
  (printf "Hello, ~a. So how many years have you been learning coding? " name)
  (define coding-age (read))
  (printf "Greate, it's already ~a years. Please keep endeavouring for a better you!~n" coding-age)
  
  0)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(module+ main
  (exit (main (vector-length (current-command-line-arguments))
              (current-command-line-arguments))))

