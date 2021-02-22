#myssn_client.py
# Based on the client from https://pymotw.com/3/socket/tcp.html

import myssn
import sys

SERVER_ADDRESS = '169.254.83.130'
Msgs = ["123123123", "Tlaxcala", "001122", "0123456789", "Denisse", "Luna", "ITESO", "11"]


try:
    i = 0
    client = myssn.client_connect(SERVER_ADDRESS)
    while True:
        try:
            while i < 8:
                # Send data
                string_msg = Msgs[i]
                i = i+1
                if ':q' in string_msg:
                    break

                bytes_msg = string_msg.encode()
                myssn.send(client, bytes_msg)
                # Look for the response
                dat = myssn.recv(client)
                if dat:
                    print('DATA: {!r}'.format(dat))
                else:
                    print('INFO: closing socket')
                    myssn.close(sock)
                    break
        except: 
            print('INFO: Client Exception') 
            break       

except ConnectionRefusedError:
    print('INFO: The server is not available')
finally:
    print('INFO: Bye!')