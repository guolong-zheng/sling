import random
import pprint

class node:
	def __init__(self, key = 0, color = 0, left = None, right = None):
		self.key = key
		self.color = color
		self.left = left
		self.right = right

def rbt_insert_rec(x, k):
	if x is None:
		nr = node(k, 1, None, None)
        return nr
	 elif k < x.key:
		p = rbt_insert_rec(x.left, k);
		if p is not None and p.color == 0:
            x.left = p
            return x
        else:
            xr = x.right
            if xr is not None and xr.color != 0:
                x.left = p
                p.color = 0
                xr.color = 0
                x.color = 1
                return x
            else: 
                pl = p.left
                pr = p.right
                if pr is not None and pr.color != 0:
                    prl = pr.left
                    prr = pr.right
                    p.right = prl
                    x.left = prr
                    pr.left = p
                    pr.right = x
                    pr.color = 0
                    x.color = 1
                    return pr
                 elif pl is not None and pl.color != 0:
                    p.right = x
                    x.left = pr
                    p.color = 0
                    x.color = 1
                    return p
                 else:
                    x.left = p
                    return x    
	else:
        p = rbt_insert_rec(x.right, k)
		if p is not None and p.color == 0: 
            x.right = p
            return x
        else:
            xl = x.left
            if xl is not None and xl.color != 0: 
                x.right = p
                p.color = 0
                xl.color = 0
                x.color = 1
                return x
            else:
                pl = p.left
                pr = p.right
                if pl is not None and pl.color != 0:
                    pll = pl.left
                    plr = pl.right
                    p.left = plr
                    x.right = pll
                    pl.right = p
                    pl.left = x
                    pl.color = 0
                    x.color = 1
                    return pl
                 elif pr is not None and pr.color != 0:
                    p.left = x
                    x.right = pl
                    p.color = 0
                    x.color = 1
                    return p
                 else:
                    x.right = p
                    return x


def main():
	root = None
	for i in range(0, 5):
		root = rbt_insert_rec(root, random.randint(0, 20))

if __name__=="__main__":
	main()
