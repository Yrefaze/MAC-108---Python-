total_bill = 0.00
black_coffee = 2.50
vanilla_latte = 4.50
blueberry_muffin = 3.00
item = ["Black Coffee","Vanilla Latte","Blueberry Muffin"]

while True:
 order = input('1. Black Coffee\n2. Vanilla Latte\n3. Blueberry Muffin\n4.Check Out\n') 
 if order == '1':
  total_bill = total_bill + black_coffee
  print(item[0])
  print('            Subtotal: $',total_bill)
 elif order == '2':
  total_bill = total_bill + vanilla_latte
  print(item[1] )
  print('            Subtotal: $',total_bill)
 elif order == '3':
  total_bill = total_bill + blueberry_muffin
  print(item[2])
  print('            Subtotal: $',total_bill)
 elif order == '4':
  print('Your total bill is: $', total_bill,' Thank you for coming!')
  break
 else:
  print('Please enter a valid item number or press 4 to check out.')
  


