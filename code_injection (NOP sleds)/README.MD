## Code Injection
# How to
- create the shellcode (virous)
- inject the code to writable memory address
- manipulate the return address to the memeory address that contains the shellcode

# Injection vector:
- NOP sled:
     - a long set of instruction precedding shellcode
     - do nothing (add, sub)
     - point is to skip and move to next instruction until we hit the shellcode address  
     - used to increste the likelihood of attack being succesfull 
- Shellcode - actual virous, machine instruction to be executred ("/bin/sh")
- Shellcode address - the address that contains the shellcode 