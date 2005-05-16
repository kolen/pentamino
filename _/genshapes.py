#!/usr/bin/python
import sys

chars=['', '', '', '', '']
chars[0] = "     |     |     |     |     |     |     |     |  x  |  x  |     |     |"
chars[1] = " xxx | x x | x   | x   |  x  |  x  | xx  |  xx |  x  |  x  | xx  | x   |"
chars[2] = "  x  | xxx | x   | xx  | xxx | xx  |  x  | xx  |  x  |  x  | xx  | xx  |"
chars[3] = "  x  |     | xxx |  xx |  x  |  x  |  xx |  x  |  x  |  xx | x   |  x  |"
chars[4] = "     |     |     |     |     |  x  |     |     |  x  |     |     |  x  |"

def getChar(n, x, y):
    global chars;
    return chars[y][(n*6)+x] == 'x'

shapes=[]

for i in range(0, 12):
    shapes.append([])
    for n in range(0, 8):
        shapes[i].append([])
        for x in range(0, 5):
            shapes[i][n].append([])
            for y in range(0, 5):
                shapes[i][n][x].append(0)
                

#generate initial
for shapenum in range (0, 12):
    for x in range (0, 5):
        for y in range(0, 5):
            shapes[shapenum][0][x][y]     = getChar(shapenum, x, y)
            shapes[shapenum][1][4-y][x]   = getChar(shapenum, x, y)
            shapes[shapenum][2][4-x][4-y] = getChar(shapenum, x, y)            
            shapes[shapenum][3][y][4-x]   = getChar(shapenum, x, y)
                 
            shapes[shapenum][4][x][4-y]   = getChar(shapenum, x, y)
            shapes[shapenum][5][4-y][4-x]     = getChar(shapenum, x, y)
            shapes[shapenum][6][4-x][y]   = getChar(shapenum, x, y)            
            shapes[shapenum][7][y][x] = getChar(shapenum, x, y)



for i in shapes:
    for n in i:
        for x in range(0, 5):
            for y in range(0, 5):
                if n[x][y]:                    
                    bn = 0x10
                    if y==0 or not n[x][y-1]: bn |= 1
                    if x==4 or not n[x+1][y]: bn |= 2
                    if y==4 or not n[x][y+1]: bn |= 4
                    if x==0 or not n[x-1][y]: bn |= 8
                    n[x][y] = bn
                        
shn = 0

print "char pShapes[12][8][5][5] = "
print "{"
for shape in shapes:
    print "/// ------- Shape %2d ------------- ///" % shn
    print("  {");
    rotn = 0
    for rot in shape:
        print("    //Shape %2d, rotation %2d" % (shn, rotn))
        print("    {")
        for y in range(0, 5):
            print "      {",
            for x in range(0, 5):
                sys.stdout.write("%2d," % rot[x][y])
            print " },"    
        print("    },")
        rotn+=1
    print("  },")       
    shn+=1
print "};"
