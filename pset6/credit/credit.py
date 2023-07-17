from cs50 import get_int
from math import floor

# Card number input
card_num = get_int("Number: ")

# Parameter
count = 0
digits = 0
adding = 0
checksum = 0
tmp = card_num
count_num = str(card_num)

# Digit count from input
count = int(len(count_num))

#Luhn's algorithm DEBUGGING IS WAITING
for i in range(1, count + 1):
    digits = floor(tmp % 10)

    if i % 2 == 0:
        digits *= 2

        if digits > 9:
            digits -= 9
        adding = digits
    else:
        adding = digits

    checksum += floor(digits)
    tmp /= 10

# Create company's ID
temp_id = card_num
while temp_id > 100:
    temp_id /= 10

company_id = floor(temp_id)

# Checking: AMEX, MASTERCARD, VISA
if checksum % 10 == 0 and count == 13 and company_id in [40, 41, 42, 43, 44, 45, 46, 47, 48, 49]:
    print("VISA")

elif checksum % 10 == 0 and count == 15 and company_id in [34, 37]:
    print("AMEX")

elif checksum % 10 == 0 and count == 16:

    if company_id in [51, 52, 53, 54, 55]:
        print("MASTERCARD")

    if company_id in [40, 41, 42, 43, 44, 45, 46, 47, 48, 49]:
        print("VISA")

else:
    print("INVALID")
