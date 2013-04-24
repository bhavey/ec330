def main():
	inarray = [-6, 12, -7, 0, 14, -7, 1, -3]
	outsum = min_subarray(inarray)
	print outsum

def min_subarray(A):
    min_ending_here = min_so_far = 0
    for i in A:
        min_ending_here = min(0, min_ending_here + i)
        min_so_far = min(min_so_far, min_ending_here)
    return min_so_far

main()
