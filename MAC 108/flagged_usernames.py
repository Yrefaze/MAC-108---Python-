bad_fruits =  " bAnana , PEAR  ,   orange ,  GRAPE fruit  , PINEapple  ,  KIWI ,   StrawBerry , WATERMELON ,   peach"
fruits = bad_fruits.split(",")
clean_list = []
for fruits in fruits :
 clean_fruits = fruits.strip().lower()
 clean_list.append(clean_fruits)
#for clean_list in clean_list :
print (clean_list) 