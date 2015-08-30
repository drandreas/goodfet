#!/usr/bin/env python
# GoodFET Atmel Flash access library
# 

import sys, time, string, cStringIO, struct, glob, serial, os, binascii;

from GoodFET import GoodFET;

class GoodFETowe(GoodFET):
    
    def setup(self):
        """Move the FET into the flash application."""
        self.writecmd(0x81, 0x01, 0, [])      # SETUP
        if self.verb != 0:
            print "Setup Failed"
            sys.exit(-1);

    def eraseFlash(self, address):
        self.writecmd(0x81, 0x21, 2, [address & 0xff, (address & 0xff00)>>8])

    def writeFlash(self, address, value):
        self.writecmd(0x81, 0x22, 3, [address & 0xff, (address & 0xff00)>>8, value])
        
    def readFlash(self, address):
        self.writecmd(0x81, 0x23, 2, [address & 0xff, (address & 0xff00)>>8])
        return self.data
    