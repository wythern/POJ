/*
Using python to avoid big number multiply.

def pow(k, n) :
	if n == 0 :
		return 1;
	if n == 1 :
		return k;
	if n % 2 == 0:
		return pow(k*k, n/2)
	else:
	return pow(k*k, n/2)*k


def getK(n, p):
	l = 2
	r = p
	while l < r :
		m = (l + r)/2
		mpn = pow(m, n)
		if mpn == p:
			return m
		if mpn < p:
			l = m + 1
		if mpn > p:
			r = m - 1
	return l
*/