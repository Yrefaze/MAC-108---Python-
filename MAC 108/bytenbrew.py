total_bill = 0.00
black_coffee = 2.5
order1 = 1
vanilla_latte = 4.50
order2 = 2
blueberry_muffin = 3.00
order3 = 3
order4 = 4
still_ordering = 1



print('          WELCOME TO BYTE AND BREW\n                   Menu:\n     Enter a number to order or to check out\n        (at least 3 items)\n')
print('1. Black Coffee - $2.50\n2. Vanilla Latte - $4.50\n3. Blueberry Muffin - $3.00\n4. Check out\n')

while still_ordering < 2: 
 order = int(input('Enter an item number: '))
 if order == order1:
  total_bill = total_bill + black_coffee
  print('Subtotal: $', total_bill) 
 elif order == order2:
    total_bill = total_bill + vanilla_latte
    print('Subtotal: $', total_bill)
 elif order == order3:
    total_bill = total_bill + blueberry_muffin
    print('Subtotal: $', total_bill)
 elif order == order4:
   
   still_ordering = still_ordering + still_ordering
   print('\nThank you for coming! Your total is: $', total_bill)
 else:
  print('\nPlease enter a valid answer!')
 

         
     