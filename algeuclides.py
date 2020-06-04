def hcfnaive(a,b): 
    if(b==0): 
        return a 
    else: 
        return hcfnaive(b,a%b) 

print(hcfnaive(9307179288208,65537))#retorna o MDC


#retorna o resultado do algoritmo extendido de euclides:
#ax + by = mdc(a,b)         x,y sao unicos!
#se a=e é o expoente público, x será o meu expoente privado!
def gcdExtended(a, b):
    # Base Case
    if a == 0 :
        return b,0,1

    gcd,x1,y1 = gcdExtended(b%a, a)

    # Update x and y using results of recursive
    # call
    x = y1 - (b//a) * x1
    y = x1

    return gcd,x,y


# Driver code
e, fi = 65537,9307179288208
g, x, y = gcdExtended(e, fi)
print(x)
print(y)
print(g)
