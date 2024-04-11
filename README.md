# Mallet
Mallet is a tool to convert raw shellcode payloads into PE droppers. It features evasion options with multiple encryption and obfuscation methods and templates for common C2 frameworks.

## Usage
Raw shellcode is read in from a specified file:

If none is provided, you may use a C2 template:

### Quick Mode
Quick mode can be used to generate a PE payload with default options - a .rsrc payload wth triple AES encryption and local thread execution:

### Custom Mode
Custom mode allows much more control over payload generation parameters.
Payloads can be placed in whichever section desired (.data, .rsrc, .rdata): 

Mallet includes a few default obfuscation chains but custom chains can be specified as well:

Finally, file format and execution options can be specified:

## Disclaimer
This tool is only to be used for authorized testing or educational purposes. I do not condone the use of this tool in any criminal or malicious activities.

## To-Do
- AES/RC4/XOR methods
- Execution methods
- Key obfuscation
- Self-signing
- DLL format support
- IAT manipulation
- Msfvenom templates
- Havoc C2 templates
