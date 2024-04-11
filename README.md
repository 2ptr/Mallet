# Mallet
Mallet is a payload generation tool to convert shellcode into PE droppers. It features evasion options with multiple encryption and obfuscation methods for payloads. Mallet also includes templates for common C2 framework payloads like Metasploit and Havoc.

Payload execution methods include simple thread execution, remote process injection, and remote thread hijacking.

## Usage
Raw shellcode is read in from a specified file:

If none is provided, you may use a C2 template:

### Quick Mode
Quick mode can be used to generate a PE payload with default options - triple AES encryption with local thread execution:

### Custom Mode
Custom mode allows much more control over payload generation parameters.
Payloads can be placed in whichever section desired (.data, .rsrc, .rdata): 

Mallet includes a few default obfuscation chains but custom chains can be specified as well:

Finally, file format and execution options can be specified:

## To-Do
- AES/RC4/XOR methods
- Execution methods
- Key obfuscation
- DLL format support
- IAT manipulation
- Msfvenom templates
- Havoc C2 templates
