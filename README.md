# Measurements records

This project was developed according to the next criteria:
All measurements are read from datalager_V2.txt file. Each measurement are separated from others by a special combination of symbols *$$$*.
After the program was started, you need to run a function, by pressing a key on the keyboard corresponding to the command name. [(all the functions listed below)](#functionality)

## <a id="functionality">Functionality</a>
- n:
  * Load records stored in the file "dataloger_V2.txt" into a linked list of structures. 
  * If the list existed before, the memory will be freed.
  * If it's not possible to open the file, the program will print the message "Zaznamy neboli nacitane!".
  * If the records were successfully loaded, it will print the message "Nacitalo sa <n> zaznamov".

- v: Print entire records

- p:
  * Add new record to the linked list.
  * The command is followed by a new line containing a positive integer c1 > 0, indicating the position (counted from 1) where the record should be added (the record at position c1 will be moved to position c1+1). Then, the next 6 lines follow, each terminated by a newline character and containing the items of the record in the order as they appear in the file "dataloger_V2.txt."
  * If position c1 does not exist in the list, the record is added to the end of the list. In this case, the program does not generate any output.
  
  Example:
    ```
    p 2
    B151a
    +48.1255+19.4514
    RD
    145.25
    1015
    20231010
    ```

- z:
  * Delete all records with the coresponding id.
  * Upon executing this command, the program will print the message "Zaznam pre ID: <id_measurement_module> bol vymazany." 

  Example:
    ```
    z A111b
    ```

- u
  * Sort the linked list based on the "Datum merania" (measurment's date) and "Cas_merania" (measurment's time).
  * Upon successful sorting, the program will print the message "Spajany zoznam bol usporiadany."
  * In case of an error (i.e., if the number of items in the linked list after sorting is not the same as before sorting), the program will print the message "Chyba usporiadania."

- r
  * Swap two records in the linked list.
  * The command is followed by two positive integers, c1 > 0 and c2 > 0, indicating the positions (counted from 1) of the records to be swapped (the record at position c1 will be moved to position c2, and the record at position c2 will be moved to position c1).
  * If positions c1 or c2 do not exist in the list, the swapping will not be performed. 
  * The program does not generate any output.

- k: 
  * End of program.
  * If the linked list existd, it will be freed.
  * The program does not generate any output.
