alert_queue = []
exit = True
while exit :                                                       
   print("\n1. Log New Alert")                                        
   print('2. View Active Queue')
   print('3. Resolve Oldest Alert')
   print('4. Exit system')
   choice = input("\nChoose an option:\n")                             

   if choice ==  '1' :                                                
      exit = True
      while exit : 
       new_alert = input('\nPlease enter new security thread description:\n ')    
       if new_alert in alert_queue :
         loop = True
         while loop :
          choice_1 = input('\nAlert is already in the system, do you want to go back to the main menu? (y = yes, n = no)\n')
          if choice_1 == 'y' :
            exit = False
            break
          elif choice_1 == 'n' :
            break
          else : 
            while True :
             choice_1 = input('\nType in a valid answer!\n')
             if choice_1 == 'y' :
                         exit = False
                         loop = False
                         break
             elif choice_1 == 'n' :
                         loop = False
                         break
             else :
                 print()
       else :
           alert_queue.append(new_alert) 
           print('\nAlert logged successfully!\n')
           break
   if choice == '2' :
       if len(alert_queue) < 1 : 
           print('\nNo alert has been logged in yet.\n ')
       else :
           for i, alert in enumerate(alert_queue) :
               print(f'{i+1}.{alert}')   
           break    
   if choice == '3' :
       if len(alert_queue) < 0 :
           print('\nNo alert to resolve!\n') 
       else: 
           resolved_threat = alert_queue.pop(0)
           print(f'Resolved and cleared: {resolved_threat} \n')
   if choice == '4' :
        print('Exiting system...\n')
        exit = False
        break
   else: 
       print('Enter a valid option!')
        
       
       
       
             

           
                         