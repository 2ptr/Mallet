# Mallet
Mallet is a tool to quickly generate shellcode droppers that will evade basic AV solutions like Windows Defender, using either custom shellcode or templates for popular C2 frameworks.

## Usage
The tool itself consists of two basic parts - the generator and runner files. 

The generator will take a raw shellcode file and encrypt or obfuscate it using either a preset chain or a custom chain. Afterwards, the keychain used will be written to a saved document and a decryption protocol will be inserted into the runner template.

The encrypted shellcode will then be included in whichever location of the runner the user wishes - `.text`, `.data`, `.rsrc`. The execution method may also be specified by the user.

Afterwards, you just need to open the `runner.sln` Visual Studio project and compile it to binary.

### Quick Mode
Quick mode can be used to generate a runner payload with default options - a `.text` payload with AES encryption and local thread execution:

### Custom Mode
Custom mode allows much more control over payload generation parameters. The user may specify a custom encryption chain:

Custom payload location:

As well as custom execution methods, including `.dll`:

Finally, you may choose to obfuscate the runner template's strings. This will replace variable names with random strings:

## Opsec
Mallet is just to be used for some quick-and-dirty droppers. This tool isn't going to save you from an EDR or any competent AV solution. 

## Disclaimer
This tool is only to be used for authorized testing or educational purposes. I do not condone the use of this tool in any criminal or malicious activities.

## To-Do
- Execution methods
- Key obfuscation
- DLL format support
- Msfvenom templates
- Havoc C2 templates
