from __future__ import print_function
import sys
import os
import subprocess
import numpy as np
import itertools
from datetime import datetime

if len(sys.argv) != 3:
    print(sys.argv)
    sys.exit()

FNULL = open(os.devnull, 'w')
startTime = datetime.now()
print("Start time: " + str(startTime), file=sys.stderr)

n_str = sys.argv[1]
m_str = sys.argv[2]
n = int(n_str)
m = int(m_str)
sep = "=" * (m+n)
intervals = int(2**(n*m-3))

progress = [None] * 9
for i in range(9):
    progress[i] = str(100.0*i/8) + "%"

# create binary n x m matrix
cnt = 0
com = 0
mat = np.zeros((n, m))
# set values here if needed
'''
mat[0][2] = mat[0][3] = 1
mat[1][2] = 1
mat[2][1] = mat[2][3] = 1
mat[3][0] = mat[3][1] = mat[3][3] = 1
mat[4][0] = mat[4][1] = mat[4][3] = 1
'''
for i in range(n):
    for j in range(m):
        cnt *= 2
        cnt += mat[i][j]
cnt = int(cnt)

while True:
    good = True
    for i in range(n-1):
        for j in range(m):
            if mat[i][j] > mat[i+1][j]:
                good = False
                break
            elif mat[i][j] < mat[i+1][j]:
                break
        if not good:
            break
    if good:
        mat_str = '\n'.join(' '.join('%d' %x for x in y) for y in mat)
        print(mat_str)
        print("")
        sm = n_str + "\n" + m_str + "\n" + mat_str
        try:
            ps = subprocess.Popen(['echo', sm], stdout=subprocess.PIPE)
            output = subprocess.check_output(['./a.out'], stdin=ps.stdout, stderr=FNULL)
            ps.wait()
            print(output.decode("utf-8"))
        except subprocess.CalledProcessError as e:
            print("return error code {}".format(e.returncode))
        print(sep)
        com += 1
    cnt += 1
    if cnt % intervals == 0:
        print("Progress: " + progress[int(cnt/intervals)] + " Time elapsed:" + str(datetime.now() - startTime) + " Now:" + str(datetime.now()), file=sys.stderr)
    nn = n-1
    mm = m-1
    while nn != -1:
        if mat[nn][mm] == 0:
            mat[nn][mm] = 1
            break
        else:
            mat[nn][mm] = 0
            if mm == 0:
                mm = m-1
                nn -= 1
            else:
                mm -= 1
    if nn == -1:
        break
print("Computed " + str(com) + " values out of " + str(cnt) + " total", file=sys.stderr)
