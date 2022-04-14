# https://stackoverflow.com/questions/2267362/how-to-convert-an-integer-to-a-string-in-any-base

import string
digs = string.digits + string.ascii_letters


def int2base(x, base):
    if x < 0:
        sign = -1
    elif x == 0:
        return digs[0]
    else:
        sign = 1

    x *= sign
    digits = []

    while x:
        digits.append(digs[int(x % base)])
        x = int(x / base)

    if sign < 0:
        digits.append('-')

    digits.reverse()

    return ''.join(digits)

if __name__ == "__main__":
    for i in range(0, 34):
        print("    * - " + int2base(i, 2));
        print("      - " + int2base(i, 8));
        print("      - " + int2base(i, 10));
        print("      - " + int2base(i, 16));
