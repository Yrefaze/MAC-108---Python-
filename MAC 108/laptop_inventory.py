console = ('Playstation','Xbox','Nintendo')

device_inventory = []
while True :
    choice = input('1. Add\n2. Remove\n3. View Inventory \n. Exit')
    if choice == '1':
     device = input('Enter the device name:\n')
     if device in console:
       device_inventory.append(device)
     else: 
       print('Please enter a valid entry.')
    elif choice == '2':
      device = input('Enter the device name:\n')
      if device in console:
        device_inventory.remove(device)
      else: 
             print('Please enter a valid entry.')
       



