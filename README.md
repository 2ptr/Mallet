![Mallet](./mallet.png)
# Mallet
Mallet is a tool to quickly generate shellcode droppers that will evade basic AV solutions like Windows Defender. Mallet supports custom shellcode as well as templates for popular C2 frameworks like Metasploit and Havoc.

MALLET IS A WIP. MANY FEATURES ARE NOT YET IMPLEMENTED.

## Usage
Clone the repo and start `Mallet.bat`. Use the menu to select your settings and generate a payload. The output dropper and keychain will be stored in the Output folder.

### Quick Mode
Quick mode can be used to generate a runner payload with default options - a `.text` payload with a single round of AES encryption and local thread execution. Windows Defender is pretty bad so this is likely all you will need.

## Results

Using quick mode alone yields a somewhat concerning result of only 18 detections out of the 70 top AV solutions according to VirusTotal:

![Quickmode](./virustotal.png)



## Disclaimer
Mallet is just a way for me to make quick-and-dirty droppers and learn more about C and the Win32 API. This tool isn't going to save you from an EDR or any competent AV solution, and is currently held together by Elmer's glue and small strips of construction paper.

This tool is only to be used for authorized testing or educational purposes. I do not condone the use of this tool in any criminal or malicious activities.

## To-Do
- Execution methods will be getting an overhaul eventually (NT API and indirect calls).
- DLL format support
- Msfvenom templates
- Havoc C2 templates
- Error handling
- Cleanup menu and control flow

Eventually, I would like to expand Mallet to include auto-compilation as well, but this is a rather large item. We will see...
