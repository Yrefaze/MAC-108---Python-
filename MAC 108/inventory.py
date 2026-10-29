inventory = []
while True:
    choice = input('1: Add, 2. Remove, 3. Show Inventory 4: Exit -->\n')
    if choice == '1':
        item = input("Enter device: ")
        inventory.append(item)
    elif choice == '2':
        item = input('Enter device to remove: ')
        if item in inventory:
            inventory.remove(item)
        else:
            print('Device not found.')
    elif choice == '3':
        print(inventory)       
    elif choice == '4':
        break
    else:
        print('Choose a valid option')