#lang typed/racket

(require plot)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 粗糙的函数
(define make-rough-hookes-law : (-> (Vector Real Real) (Values Real (-> Real Real)))
  (lambda [xy]
    (define k (/ (vector-ref xy 1) (vector-ref xy 0)))

    (values k
            (λ [[x : Real]] : Real
              (* k x)))))

; 函数拟合/最小二乘法
(define hookes-fit/least-square-method : (-> (Listof (Vector Real Real)) (Values Real Real (-> Real Real)))
  (lambda [data]
    (define N : Real (add1 (length data)))
  
    (define-values (Σx Σy Σxy Σx²)
      (for/fold ([Σx : Real 0.0]
                 [Σy : Real 0.0]
                 [Σxy : Real 0.0]
                 [Σx² : Real 0.0])
                ([datum (in-list data)])
        (define x : Real (vector-ref datum 0))
        (define y : Real (vector-ref datum 1))
        
        (values (+ Σx x)
                (+ Σy y)
                (+ Σxy (* x y))
                (+ Σx² (* x x)))))
    
    (define xbar : Real (/ Σx N))
    (define ybar : Real (/ Σy N))
    (define k : Real (/ (- Σxy (* N xbar ybar))
                        (- Σx² (* N xbar xbar))))
    (define b : Real (- ybar (* k xbar)))
    
    (values k b
            (λ [[x : Real]] : Real
              (+ (* k x) b)))))

(module+ main
  (define data : (Listof (Vector Real Real))
    (list #(100 16)
          #(80 13)
          #(60 10)
          #(40 7)
          #(20 3)))
  
  (define-values (k b fx) (hookes-fit/least-square-method data))

  (parameterize ([plot-pen-color-map 'pastel2])
    (plot #:title "胡克定律探究实验"
          #:x-label "砝码质量(m)" #:y-label "弹簧伸长长度(ΔL)"
          #:x-min 0 #:x-max 100 #:y-min 0 #:y-max 20
          #:width 600 #:height 600
          
          (list* (points #:sym 'fullcircle1 #:color 'black
                         data)
                 (function #:label (format "最小二乘法线性拟合(k = ~a)" (~r k #:precision 4))
                           #:color 'ForestGreen
                           fx)
                 (for/list : (Listof renderer2d) ([xy (in-list data)]
                                                  [c (in-naturals 4)])
                   (define-values (k f) (make-rough-hookes-law xy))
                   (function #:label (format "ΔL = ~am" (~r k #:precision 4))
                             #:color c #:alpha 0.5
                             f))))))
