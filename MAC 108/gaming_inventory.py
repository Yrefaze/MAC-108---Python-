console = ("play station 5", "play station 5 slim", "play station 5 pro", "xbox series x", "xbox series s", "xbox series x pro")
handheld = ("nintendo switch", "nintendo switch oled", "nintendo switch 2", "steam deck")
inventory = []
while True:
    print ("Welcome to The Gaming Vault!")
    print ("Please select an option:")
    print ("Add a console to inventory (1)")
    print ("Remove a console from inventory (2)")
    print ("Add a handheld to inventory (3)")
    print ("Remove a handheld from inventory (4)")
    print ("View inventory (5)")
    print ("Exit program (6)")

    choice = input("Please select an option (1-6): ")
    if choice == "1":
        print("\nAvailable consoles:")
        for i, item in enumerate(console):
            print(f"{i + 1}. {item}")
        console_choice = int(input("Select a console to add (1-6): ")) - 1
        if 0 <= console_choice < len(console):
            inventory.append(console[console_choice])       #console[console_choice] est un object de l'array console[] (ex console[1])
            print(f"Added {console[console_choice]} to inventory.")
            print('')
            answer = input('Return to main menu (1)\nExit program (2)')
            if answer == '1':
             print('')
            elif answer == '2':
                break
        else:
            print("Invalid selection.")
    elif choice == "2":
        if inventory:
            print("Inventory:")
            for i, item in enumerate(inventory):
                print(f"{i + 1}. {item}")
            remove_choice = int(input("Select an item to remove (1-6): ")) - 1
            if 0 <= remove_choice < len(inventory):
                removed_item = inventory.pop(remove_choice)
                print(f"Removed {removed_item} from inventory.")
                print('')
                answer = input('Return to main menu (1)\nExit program (2)')
                if answer == '1':
                 print('')
                elif answer == '2':
                    break
            else:
                print("Invalid selection.")
        else:
            print("Inventory is empty.")
    elif choice == "3":
        print("Available handhelds:")
        for i, item in enumerate(handheld):
            print(f"{i + 1}. {item}")
        handheld_choice = int(input("Select a handheld to add (1-4): ")) - 1
        if 0 <= handheld_choice < len(handheld):
            inventory.append(handheld[handheld_choice])
            print(f"Added {handheld[handheld_choice]} to inventory.")
            print('')
            answer = input('Return to main menu (1)\nExit program (2)')
            if answer == '1':
             print('')
            elif answer == '2':
                break
        else:
            print("Invalid selection.")
    elif choice == "4":
        if inventory:
            print("Inventory:")
            for i, item in enumerate(inventory):
                print(f"{i + 1}. {item}")
            remove_choice = int(input("Select an item to remove (1-6): ")) - 1
            if 0 <= remove_choice < len(inventory):
                removed_item = inventory.pop(remove_choice)
                print(f"Removed {removed_item} from inventory.")
            else:
                print("Invalid selection.")
        else:
            print("Inventory is empty.")
    elif choice == "5":
        if inventory:
            print("Inventory:")
            for i, item in enumerate(inventory):
                print(f"{i + 1}. {item}")
        else:
            print("Inventory is empty.")
    elif choice == "6":
        print("Exiting program. Goodbye!")
        break
    else:
        print("Invalid selection. Please choose a valid option.")