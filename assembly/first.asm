; listing 39
bits 16

; register to register
mov si, bx
mov dh, al

; 8-bit immediate-to-register
mov cx, 12
mov cx, -12

; 16-bit immediate-to-register
mov dx, 3948
mov dx, -3948

; source address calculation
mov al, [bx + si]
mov bx, [bp + di]
mov dx, [bp]

; source address calculation plus 8-bit displacement
mov ah, [bx + si + 4]

; source address calculation plus 16-bit displacement
mov al, [bx+si+4999]

; dest address calculation
mov [ bx + di ], cx
mov [ bp + si ], cl
mov [ bp ], ch



; listing 40

; signed displacements
mov ax, [bx + di - 37]
mov [si - 300], cx
mov dx, [bx - 32]

; explicit sizes
mov [bp + di], byte 7
mov [di + 901], word 347

; direct address
mov bp, [5]
mov bx, [3458]

; memory-to-accumulator test
mov ax, [2555]
mov ax, [16]

; accumulator-to-memory test
mov [2554], ax
mov [15], ax



