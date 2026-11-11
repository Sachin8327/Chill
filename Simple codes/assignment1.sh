
#!/bin/bash

file="addressbook.txt"

while true
do
    echo ""
    echo "----- ADDRESS BOOK -----"
    echo "1. Create"
    echo "2. View"
    echo "3. Insert"
    echo "4. Delete"
    echo "5. Modify"
    echo "6. Exit"
    read -p "Enter choice: " ch

    case $ch in
        1)
            > "$file"
            echo "Address book created."
            ;;

        2)
            if [ -f "$file" ]; then
                echo "ID | Name | Phone | Address"
                cat "$file"
            else
                echo "Address book not found."
            fi
            ;;

        3)
            read -p "Enter ID: " id
            read -p "Enter name: " name
            read -p "Enter phone: " phone
            read -p "Enter address: " address
            echo "$id|$name|$phone|$address" >> "$file"
            echo "Contact inserted."
            ;;

        4)
            read -p "Enter ID to delete: " id
            if [ -f "$file" ]; then
                grep -v "^$id|" "$file" > temp.txt
                mv temp.txt "$file"
                echo "Contact deleted if it existed."
            else
                echo "Address book not found."
            fi
            ;;

        5)
            read -p "Enter ID to modify: " id
            if [ -f "$file" ]; then
                grep -v "^$id|" "$file" > temp.txt

                read -p "Enter new name: " name
                read -p "Enter new phone: " phone
                read -p "Enter new address: " address

                echo "$id|$name|$phone|$address" >> temp.txt
                mv temp.txt "$file"

                echo "Contact modified."
            else
                echo "Address book not found."
            fi
            ;;

        6)
            echo "Exiting..."
            break
            ;;

        *)
            echo "Invalid choice."
            ;;
    esac
done


# // A. Shebang
# // 1. #!/bin/bash – Script ko Bash shell interpreter se execute karta hai.

# // B. Variable Declaration
# // 1. file="addressbook.txt" – Address book ki file ka naam store karta hai.

# // C. Infinite While Loop
# // 1. while true – Menu ko repeatedly display karta hai jab tak user Exit select nahi karta.
# // 2. do – While loop ka body start karta hai.
# // 3. echo "" – Output mein blank line print karta hai.
# // 4. echo – Address Book ka menu display karta hai.
# // 5. read -p "Enter choice: " ch – User se choice lekar ch variable mein store karta hai.

# // D. Case Statement
# // 1. case $ch in – User ki choice ke according corresponding operation execute karta hai.

# // E. Create Operation (1)
# // 1. > "$file" – Address book file create karta hai. Agar file pehle se exist karti hai toh uska content empty kar deta hai.
# // 2. echo – Address book created ka message display karta hai.
# // 3. ;; – Current case option terminate karta hai.

# // F. View Operation (2)
# // 1. if [ -f "$file" ] – Check karta hai ki address book file exist karti hai ya nahi.
# // 2. echo – ID, Name, Phone aur Address ka heading display karta hai.
# // 3. cat "$file" – File ke saare contacts display karta hai.
# // 4. else – Agar file exist nahi karti toh error message display karta hai.
# // 5. fi – If-else condition terminate karta hai.

# // G. Insert Operation (3)
# // 1. read -p "Enter ID: " id – User se contact ki unique ID leta hai.
# // 2. read -p "Enter name: " name – User se contact ka name leta hai.
# // 3. read -p "Enter phone: " phone – User se phone number leta hai.
# // 4. read -p "Enter address: " address – User se address leta hai.
# // 5. echo "$id|$name|$phone|$address" – Contact ki saari details ko | separator ke saath combine karta hai.
# // 6. >> "$file" – New contact ko address book file ke end mein append karta hai.
# // 7. echo – Contact inserted ka message display karta hai.

# // H. Delete Operation (4)
# // 1. read -p "Enter ID to delete: " id – User se delete karne wale contact ki ID leta hai.
# // 2. if [ -f "$file" ] – Check karta hai ki address book file exist karti hai ya nahi.
# // 3. grep -v "^$id|" "$file" > temp.txt – Given ID se start hone wali matching line ko exclude karke remaining contacts temp.txt mein store karta hai.
# // 4. grep – File mein given pattern search karta hai.
# // 5. -v – Matching lines ko exclude karta hai.
# // 6. ^ – Line ki starting position represent karta hai.
# // 7. | – ID aur Name ke beech separator represent karta hai.
# // 8. > temp.txt – Remaining contacts ko temporary file mein write karta hai.
# // 9. mv temp.txt "$file" – Temporary file ko original address book file se replace karta hai.
# // 10. echo – Contact deleted ka message display karta hai.
# // 11. else – Agar file exist nahi karti toh error message display karta hai.
# // 12. fi – If-else condition terminate karta hai.

# // I. Modify Operation (5)
# // 1. read -p "Enter ID to modify: " id – User se modify karne wale contact ki ID leta hai.
# // 2. if [ -f "$file" ] – Check karta hai ki address book file exist karti hai ya nahi.
# // 3. grep -v "^$id|" "$file" > temp.txt – Old ID wale contact ko exclude karke remaining contacts temp.txt mein store karta hai.
# // 4. read -p "Enter new name: " name – User se updated name leta hai.
# // 5. read -p "Enter new phone: " phone – User se updated phone number leta hai.
# // 6. read -p "Enter new address: " address – User se updated address leta hai.
# // 7. echo "$id|$name|$phone|$address" >> temp.txt – Updated contact ki details temporary file ke end mein add karta hai.
# // 8. mv temp.txt "$file" – Temporary file ko original address book file se replace karta hai.
# // 9. echo – Contact modified ka message display karta hai.
# // 10. else – Agar address book file exist nahi karti toh error message display karta hai.
# // 11. fi – If-else condition terminate karta hai.

# // J. Exit Operation (6)
# // 1. echo "Exiting..." – Exit message display karta hai.
# // 2. break – Infinite while loop ko terminate karta hai.

# // K. Default Case
# // 1. *) – Agar user 1 se 6 ke alawa koi choice enter karta hai toh execute hota hai.
# // 2. echo "Invalid choice." – Invalid choice ka message display karta hai.
# // 3. ;; – Current case option terminate karta hai.

# // L. Loop and Case Termination
# // 1. esac – Case statement terminate karta hai.
# // 2. done – While loop terminate karta hai.