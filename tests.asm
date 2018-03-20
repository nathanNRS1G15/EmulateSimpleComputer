si, 0, 10
li, 2
spdl, 0
sm, 1
lm, 0
addi, 1
sm, 0
lm, 1
addi, 1
spdl, 0
sm, 1
bnei, 1000, -7
si, 0, 1000
si, 1, 2
lm, 1
mul, 1
sm, 2
lm, 0
slt, 2
bnei, 1, 24
si, 3, 10
lpdl, 3
slti, 1
bnei, 1, -9
lm, 1
muli, 2
sm, 4
lm, 0
slt, 4
beqi, 1, 5
lm, 1
addi, 1
sm, 1
j, -19
lm, 4
addi, 8
sm, 5
li, 0
spdl, 5
lm, 4
add, 1
sm, 4
j, -15
si, 6, 0
lm, 6
addi, 10
sm, 7
lm, 0
slt, 6
bnei, 1, 10
lpdl, 7
beqi, 0, 3
lpdl, 7
sm, 3000
lm, 6
addi, 1
sm, 6
j, -13
