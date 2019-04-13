# echonet

Welcome to echonet

-------------------START_OF_USAGE-------------------
Usage: echonet [<params>=<values>]
<params> :
         /? | -help | -HELP | "anything not starting with -" will display this help.
         -p=port_value (eg. 20001)
         -h=hostname (eg. localhost | 127.0.0.1)
         -m=operating_mode (eg. server | client)

Default port    : 30001
Default host    : 127.0.0.1
Default mode    : client

Examples:
echonet -p=30001 -h=127.0.0.1 -m=server
echonet -p=30001 -h=127.0.0.1 -m=client
-------------------END_OF_USAGE-------------------