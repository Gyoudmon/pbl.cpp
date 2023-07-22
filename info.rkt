#lang info

(define collection 'use-pkg-name)
(define pkg-desc "Youth Language")

(define version "1.0")
(define pkg-authors '(wargrey))
(define test-omit-paths 'all)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define sdl2-config
  '((config SDL2)
    (lib gydm.stem pltmos)
    (include [windows "C:\\opt\\GYDMstem\\include"]
             [macosx "/opt/GYDMstem/include"])
    (libpath [windows "C:\\opt\\GYDMstem\\lib"]
             [macosx "/opt/GYDMstem/lib"])))

(define native-compiled-subpath '())

(define native-launcher-names
  `(["BigBang.cpp" console ,sdl2-config]
    ["FontBrowser.cpp" console ,sdl2-config]
    ["village/procedural/shape.cpp" console ,sdl2-config]
    ["village/procedural/paddleball.cpp" console ,sdl2-config]))
