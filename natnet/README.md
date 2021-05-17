# NatNet samples

## Remote Triggering: TriggerClient
This small program allows you to send "rec" or "stop" commands to the server where Motive is installed through the UDP communication protocol using [NatNet commands ](https://v22.wiki.optitrack.com/index.php?title=NatNet:_Remote_Requests/Commands).

### Instructions for use
triggerClient [ServerIP] [ Instruction ]

[ServerIP]           IP address of the server (e.g. 192.168.0.107) 
[Instruction]        "rec" / "stop"

If you want to execute these commands from your python code, see launchTriggerExample.py

### Library installation
- Copy the file located in `/include` (headers) in `/usr/local/include/natnet`
- Copy the file `libNatNetLibShared.so` in `/usr/local/lib`
- Include in `.bashrc`:

```bash
	# dinamic libraries
	export LD_LIBRARY_PATH=/usr/local/lib
```

### Compilation:

```bash
cd natnet/samples/TriggerClient/
mkdir build 
make
```

### More info:
https://v22.wiki.optitrack.com/index.php?title=Data_Streaming
