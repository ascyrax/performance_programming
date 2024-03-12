;bits 16

; ax, bx, cx, dx
; si, di, bp, sp
; zf, sf, cf, of
; ip
; ss, cs, ds, es
start:

mov bx, 0     ;bx points to the current data pointer location, where I should be adding new data 

mov cx, 8

iterate_x:
    cmp cx, 0
        mov dx, 8
        iterate_y:
            cmp dx, 0
            mov byte [bx], 255
            add bx, 1
            sub dx, 1
            jz iterate_x
            jnz iterate_y
    sub cx, 1