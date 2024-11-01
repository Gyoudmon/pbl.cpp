#lang info

(define collection 'use-pkg-name)
(define pkg-desc "Youth Language")

(define version "1.0")
(define pkg-authors '(wargrey))
(define test-omit-paths 'all)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define sdl2-config
  '((config SDL2)
    (lib plteen pltmos stemos)
    (include "C:\\opt\\JrPLT\\include")
    (libpath "C:\\opt\\JrPLT\\lib")))

(define native-compiled-subpath '())
(define native-compiled-bindir '("bin"))
(define native-compiled-libdir '())
(define native-compiled-release '())
(define native-compiled-debug '("debug"))

(define native-launcher-names
  `(["BigBang.cpp" console ,@sdl2-config]
    ["FontBrowser.cpp" console ,@sdl2-config]
    ["village/procedural/shape.cpp" console ,@sdl2-config]
    ["village/procedural/paddleball.cpp" console ,@sdl2-config]))
