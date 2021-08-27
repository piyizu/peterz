def isNarcissistic(origin):
    '''This function check if a number "origin" is narcissistic.
        A k-digit number is narcissistic when the sum of the number
        at each digit position to the power of k is the number itself.
        For example, 153 is narcissistic, for 1^3 + 5^3 + 3^3 = 153

        This function could be better implemented using mutable 
        data structures of Python
    ''' 
    sum = 0
    digit = 0
    num = origin
    while(num):
        num //= 10 # num/10 gives a float number while num//10 ignores its fractions
        digit += 1 # no digit++
    num = origin
    while(num):
        sum += (num % 10) ** digit # a**b means a to the power of b
        num //= 10
    if(sum == origin):
        return True
    else:
        return False

def getNarcissisticNumbers(numOfNumbers):
    '''This function returns a list of the first numOfNumbers narcissistic numbers'''
    numlist = []
    x = 1
    while (numOfNumbers):
        if(isNarcissistic(x)):
            numlist.append(x)
            numOfNumbers -= 1
        x += 1
    return numlist

print(getNarcissisticNumbers(16))