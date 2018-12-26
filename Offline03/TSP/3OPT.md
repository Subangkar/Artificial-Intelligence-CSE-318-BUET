https://en.wikipedia.org/wiki/3-opt

def reverse_segment_if_better(tour, i, j, k):
    "If reversing tour[i:j] would make the tour shorter, then do it."
    # Given tour [...A-B...C-D...E-F...]
    A, B, C, D, E, F = tour[i-1], tour[i], tour[j-1], tour[j], tour[k-1], tour[k % len(tour)]
    d0 = distance(A,B) + distance(C,D) + distance(E,F)
    d1 = distance(A,C) + distance(B,D) + distance(E,F)
    d2 = distance(A,B) + distance(C,E) + distance(D,F)
    d3 = distance(A,D) + distance(E,B) + distance(C,F)
    d4 = distance(F,B) + distance(C,D) + distance(E,A)

    if d0 > d1:
      tour[i:j] = reversed(tour[i:j])
      return -d0 + d1
    elif d0 > d2:
      tour[j:k] = reversed(tour[j:k])
      return -d0 + d2
    elif d0 > d4:
      tour[i:k] = reversed(tour[i:k])
      return -d0 + d4
    elif d0 > d3:
      tmp = tour[j:k], tour[i:j]
      tour[i:k] = tmp
      return -d0 + d3
    return 0


def three_opt(tour):
    "Iterative improvement based on 3 exchange."
    while True:
        delta = 0
        for (a,b,c) in all_segments(len(tour)):
            delta += reverse_segment_if_better(tour, a, b, c)
        if delta >= 0:
            break
    return tour

def all_segments(N):
    "Generate all segments combinations"
    return ((i, j, k)
        for i in range(N)
        for j in range(i+2, N)
        for k in range(j+2, N+(i>0)))    