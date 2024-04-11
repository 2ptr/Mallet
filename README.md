# Mallet
Mallet is a payload generation tool to convert shellcode into PE droppers. It features evasion options with multiple encryption and obfuscation methods for payloads. Mallet also includes templates for common C2 framework payloads like Metasploit and Havoc.

Payload execution methods include simple process execution, process injection, and remote thread hijacking.

## Usage
Payloads can be placed in whichever section the user desires (.data, .rsrc, .rdata): 

Mallet includes a few default obfuscation chains but custom chains can be specified as well:

## To-Do
- AES/RC4/XOR methods
- Execution methods
- Key obfuscation
- DLL format support
- IAT manipulation
- Msfvenom templates
- Havoc C2 templates
