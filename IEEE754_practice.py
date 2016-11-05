# IEEE-754 single-precision floating-point format (binary32)
# <--> decimal conversion practice
# Created by Jason Li (´･ω･`) on May 21, 2016
# Uploaded to https://repl.it/CTdM/9

from random import randint
import sys


def ranSP(significandDigits):
    b = []
    # Generate random IEEE-754 SP,
    # with significand of 5 digits

    # the sign bit
    b.append(str(randint(0, 1)))

    # the 8 exponent bits
    e = bin(randint(-6 + 127, 10 + 127))
    # 0b1111001 to 0b10000101, 7 or 8 digits

    # read 7 digits from the end
    b.extend(e[-7:])
    # then the 8th from the end, '1' or 'b'
    if e[-8] == '1':
        b.insert(1, '1')
    else:
        b.insert(1, '0')

    # the mantissa
    for i in range(significandDigits):
        b.append(str(randint(0, 1)))
    b.extend('0' * (23 - significandDigits))

    return ''.join(b)


def spTOdec(b):
    exponent = int(b[1:9], 2) - 127
    significand = 0
    for i in range(23):
        significand += (0.5 ** (i + 1)) * (0 if b[9 + i] == '0' else 1)
    return ((-1) ** int(b[0])) * (significand + 1) * 2 ** exponent


def choose():
    while True:
        try:
            print('Enter 1: IEEE-754 SP -> DEC')
            print('Enter 2: DEC -> IEEE-754 SP')
            print('Enter 0: exit')
            choice = int(input('>>> '))
            if choice != 1 and choice != 2 and choice != 0:
                raise ValueError
            return choice
        except ValueError:
            print('Invalid input. Please retry.\n')

print('This is the IEEE-754 single-precision floating-point format conversion practice.')
print("(╯ＴДＴ）╯︵ ┻━┻It will appear in ENGG1203 final exam. You bet.\n")
win = 0
while True:
    choice = choose()
    if choice == 0:
        sys.exit()

    b = ranSP(5)
    s, e, mantissa = b[0], b[1:9], b[9:]
    # Calculate the decimal representation
    d = spTOdec(b)

    # print(s, e, mantissa)
    # print(d)

    if choice == 1:
        print('The IEEE-754 SP format of the number is')
        print(s, e, mantissa)

        while True:
            print('Please convert it to decimal format:')
            d_ans = str(d)[:-2] if str(d)[-2:] == '.0' else str(d)
            if d_ans == input('>>> '):
                print('Correct! Congratulations!\n')
                if win < 0:
                    win = 0
                win += 1
                break
            else:
                print('Oops, please press Enter to retry. Enter 0 to show answer.')
                response = input('>>> ')
                if response == '0':
                    print('Ans:', d_ans, '\n')
                    if win > 0:
                        win = 0
                    win -= 1
                    break
    elif choice == 2:
        print('The decimal format of the number is')
        print(d)
        print('Please enter the IEEE-754 SP format.')
        while True:
            sAns = input('The sign bit = ')
            eAns = input('The exponent = ')
            mAns = input('The mantissa (first 5 digit) = ')
            if s == sAns and\
                    e == eAns and\
                    mantissa[:5] == mAns:
                print('Correct! Congratulations!\n')
                if win < 0:
                    win = 0
                win += 1
                break
            else:
                print('Oops, press Enter to retry. Enter 0 to show answer.')
                response = input('>>> ')
                if response == '0':
                    print('Ans:', s, e, mantissa, '\n')
                    if win > 0:
                        win = 0
                    win -= 1
                    break
    if win > 4:
        print(':) %s WIN COMBO!' % win)
    if win < -4:
        print('눈_눈 %s LOSE COMBO!' % (-win))
