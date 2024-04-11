# Mallet
Mallet is a payload generation tool to convert shellcode into PE droppers. It has options for evading static analysis techniques with multiple encryption and obfuscation methods.

## Usage
Payloads can be placed in whichever section the user desires (.data, .rsrc, .rdata): 

Mallet includes a few default obfuscation chains but custom chains can be specified as well:

## To-Do
- AES/RC4/XOR methods
- Key obfuscation
- IAT manipulation
- DLL format support
- Msfvenom templates
- Havoc C2 templates
