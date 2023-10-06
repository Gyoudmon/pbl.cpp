#lang racket

; 场景：邹忌讽齐王纳谏

; 定义类和方法
(define person%
  (class object% (super-new)
    ; 人有名字和颜值两个属性
    (init-field name)
    (init-field [颜值 (add1 (random 10))])

    (printf "~a已就绪~n" name)

    ; 人会臭美，喜欢问别人谁颜值比较高
    (define/public (问 回答者 比较者)
      (printf "~a: 吾孰与~a美?~n" name (get-field name 比较者))
      (send 回答者 曰 this 比较者))
    
    ; 人会奉承，见人说人话 见鬼说鬼话
    (define/public (曰 提问者 比较者)
      (printf "~a: 君美甚，~a何能及君也!~n" name (get-field name 比较者)))

    ; 人会自省，但多少有点偏心，颜值相同也觉得自己更美
    (define/public (自省 比较者)
      (if (< (get-field 颜值 this)
             (get-field 颜值 比较者))
          (printf "[~a窥镜而自视: 吾诚知不如~a美!]~n" name (get-field name 比较者))
          (printf "[~a窥镜而自视: 吾诚知~a何能及吾也!]~n" name (get-field name 比较者))))))

; 角色就绪
(define 邹忌 (new person% [name "邹忌"] [颜值 8]))
(define 徐公 (new person% [name "徐公"] [颜值 10]))

(define 妻 (new person% [name "妻"]))
(define 妾 (new person% [name "妾"]))
(define 客 (new person% [name "客"]))

; 完整还原情景
(send 邹忌 问 妻 徐公)
(send 邹忌 问 妾 徐公)
(send 邹忌 问 客 徐公)
(send 邹忌 自省 徐公)
