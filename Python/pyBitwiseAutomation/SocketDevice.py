# SocketDevice.py
# ================================================================================
# BOOST SOFTWARE LICENSE
#
# Copyright 2020 BitWise Laboratories Inc.
# Original Author.......Jim Waschura
# Contact...............info@bitwiselabs.com
#
# Permission is hereby granted, free of charge, to any person or organization
# obtaining a copy of the software and accompanying documentation covered by
# this license (the "Software") to use, reproduce, display, distribute,
# execute, and transmit the Software, and to prepare derivative works of the
# Software, and to permit third-parties to whom the Software is furnished to
# do so, all subject to the following:
#
# The copyright notices in the Software and this entire statement, including
# the above license grant, this restriction and the following disclaimer,
# must be included in all copies of the Software, in whole or in part, and
# all derivative works of the Software, unless such copies or derivative
# works are solely in the form of machine-executable object code generated by
# a source language processor.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
# SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
# FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
# ================================================================================

import socket
import time
from pyBitwiseAutomation.AutomationInterface import *
from enum import Enum;


class SocketDevice(AutomationInterface):
    """Socket device class."""

    Start = float(0.0)
    # Sock = None
    # IsConnected = False

    def __init__(self):
        self.Sock = None
        self.IsConnected = False
        self.Debugging = False
        return None

    def __del__(self):
        if self.IsConnected:
            self.Disconnect()
        return None

    @staticmethod
    def timestamp():
        now = time.time()
        if SocketDevice.Start == 0.0:
            SocketDevice.Start = now
        return now-SocketDevice.Start

    def getDebugging(self) -> bool:
        return self.Debugging

    def setDebugging(self, newValue: bool):
        self.Debugging = newValue

    def getIsConnected(self) -> bool:
        return self.IsConnected

    def Connect( self, ipaddress:str, dflt_port:int = 923 ) :
        """Connect to socket device."""
        if self.IsConnected:
            self.Disconnect()
        tempBuffer = ipaddress
        tempPort = dflt_port
        tokens = ipaddress.split(":")
        if len(tokens)>1:
            tempBuffer = tokens[0]
            tempPort = int(tokens[1])

        try:
            self.Sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

        except Exception as e:
            print("socket.socket() exception:",e)
            raise Exception("[Create_Socket_Failed")

        try:
            self.Sock.connect((tempBuffer,tempPort))
            self.IsConnected=True
        except Exception as e:
            print("self.Sock.connect() exception is: ", e)
            self.Sock=None
            raise Exception("[Unable_To_Connect]")

        return None

    def Disconnect( self ):
        """Disconnect from socket device."""
        if self.IsConnected:
            self.Sock.shutdown(socket.SHUT_RDWR)
            self.Sock.close()
            self.IsConnected = False
        self.Sock=None
        return None

    def Receive( self, buflen:int ) -> bytes:
        """Receive up to maximum number of bytes from socket device."""
        if not self.IsConnected:
            raise Exception("[Not_Connected]")
        return self.Sock.recv(buflen)

    def Send( self, buffer:bytes ):
        """Send specified number of bytes to socket device."""
        if not isinstance(buffer,bytes) :
            raise Exception("[Invalid_Type]")

        if not self.IsConnected:
            raise Exception("[Not_Connected]")

        self.Sock.send(buffer)
        return None

    def SendCommand(self, command:str ):
        """Send command (ending with '\n') to socket device."""
        if not isinstance(command,str) :
            raise Exception("[Invalid_Command_Type]")

        if not self.IsConnected:
            raise Exception("[Not_Connected]")

        self.Sock.send(bytes(command,'utf-8'))
        return None

    def QueryResponse( self, command:str, maxLength:int = 4096 ) -> str:
        """Query response from command (ending with '\n') from socket device."""

        if not isinstance(command, str) :
            raise Exception("[Invalid_Command_Type]")

        if not self.IsConnected:
            raise Exception("[Not_Connected]")

        if self.Debugging:
            print( "QueryResponse() query: " + command )

        self.Sock.send( bytes(command, 'utf-8'))

        tempBytes = self.Sock.recv(maxLength)
        tempString = str(tempBytes, encoding='utf-8')

        if len(tempString)>0 and tempString[-1]=="\n" :
            tempString = tempString[0:-1]

        if len(tempString)>1 and tempString[0] == '"' and tempString[-1] == '"' :
            tempString = tempString[1:-1]

        if self.Debugging:
            print( "QueryResponse() response: " + tempString )

        return tempString

    def QueryResponse_int(self, command: str ) -> int:
        """Query integer response from command (ending with '\n') from socket device."""
        return int(self.QueryResponse(command))

    def QueryResponse_bool(self, command: str ) -> bool:
        """Query boolean response from command (ending with '\n') from socket device."""
        response = self.QueryResponse(command)
        return bool(  len(response) > 0 and (response[0] == 'T' or response[0] == 't' or response[0] == '1') )

    def QueryResponse_float(self, command: str ) -> float:
        """Query float response from command (ending with '\n') from socket device."""
        return float(self.QueryResponse( command))

    def QueryResponse_enum(self, enumeration:Enum, command: str) -> Enum:
        """Query integer index of enum response from command (ending with '\n') from socket device."""

        if not isinstance(command, str):
            raise Exception("[Command_Must_Be_String]")

        return enumeration(self.QueryResponse(command))

    def SendBinaryCommand(self, command: str, buffer: bytes):
        """Send command (ending with '\n') followed by 4-byte count and array of bytes to socket device."""

        if not isinstance(command, str):
            raise Exception("[Invalid_Command_Type]")

        if not isinstance(buffer, bytes):
            raise Exception("[Invalid_Buffer_Type]")

        if not self.IsConnected:
            raise Exception("[Not_Connected]")

        count = len(buffer)

        self.Sock.send(bytes(command,'utf-8'))
        self.Sock.send(count.to_bytes(4, byteorder='little'))
        self.Sock.send(buffer)

        return None

    def QueryBinaryResponse( self, command:str ) -> bytes :
        """Query array of bytes response from command (ending with '\n') from socket device."""

        if not isinstance(command, str) :
            raise Exception("[Invalid_Command_Type]")

        if not self.IsConnected:
            raise Exception("[Not_Connected]")

        self.Sock.send( bytes(command,'utf-8') )

        countBytes = self.Sock.recv(4)
        if len(countBytes) != 4:
            raise Exception("[Missing_Count_Response]")

        count = int.from_bytes(countBytes, byteorder="little")
        return_value = bytes(0)

        if count>0 :
            total = 0
            while total<count :
                portion = self.Sock.recv(count-total)
                amount = len(portion)

                if amount == 0:
                    raise Exception("[Error_Receiving_Buffer]")

                return_value += portion
                total += amount
            pass

        return return_value

# EOF