import time
import wx
import ConfigParser
import socket
import struct
import sys

from urllib import urlopen

from threading import Thread
from pydispatch import dispatcher

config = ConfigParser.RawConfigParser()
config.read('laundry.cfg')

ADDRESS = (config.get('Config', 'address'))
MULTICAST = (config.get('Config', 'multicast'))
PORT = (config.get('Config', 'port'))

FLASH_TIMER = (config.getint('Config', 'flash_timer'))
FLASH_TIMER_ID = wx.NewId()

SIGNAL = 'update'

RESET_ADDRESS = "http://%s/reset.py" % ADDRESS
TEST_ADDRESS = "http://%s/test_both.py" % ADDRESS
STATUS_ADDRESS = "http://%s/status.txt" % ADDRESS
MULTICAST_GROUP = "%s" % MULTICAST
SERVER_ADDRESS = ('', int(PORT) )

#################################################################################################
class MonitorThread(Thread):

    #----------------------------------------------------------------------
    def __init__(self):
        """Init Worker Thread Class."""
        Thread.__init__(self)
        self.start()    # start the thread
 
    #----------------------------------------------------------------------
    def run(self):
        """Run Worker Thread."""
        #multicast_group = '238.0.0.1'
        #server_address = ('', 10001)

        # Create the socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # Bind to the server address
        sock.bind(SERVER_ADDRESS)
        # Tell the operating system to add the socket to the multicast group
        # on all interfaces.
        group = socket.inet_aton(MULTICAST_GROUP)
        mreq = struct.pack('4sL', group, socket.INADDR_ANY)
        sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
        # Receive/respond loop
        while True:
            data, address = sock.recvfrom(1024) 
            wx.CallAfter(self.updateStatus, data)

 
    #----------------------------------------------------------------------
    def updateStatus(self, data):
        """
        Send status to GUI
        """
        #print "sending pub.sendMessage with data"
        #print data
        dispatcher.send( signal=SIGNAL, sender=data )

#################################################################################################


def create_menu_item(menu, label, func):
    item = wx.MenuItem(menu, -1, label)
    menu.Bind(wx.EVT_MENU, func, id=item.GetId())
    menu.AppendItem(item)
    return item

class TaskBarIcon(wx.TaskBarIcon):
    def __init__(self):
        super(TaskBarIcon, self).__init__()
        self.set_icon('icons/off.ico', 'Off')
        status = urlopen(STATUS_ADDRESS).read()
        self.data = status
        self.icon_state = False
        self.icon_blink = False
        MonitorThread()
        self.flash_timer = wx.Timer(self, id=FLASH_TIMER_ID)
        self.flash_timer.Start(FLASH_TIMER)
        self.Bind(wx.EVT_TIMER, self.FlashIcon, id=FLASH_TIMER_ID) 
    # create a pubsub receiver
        dispatcher.connect(self.CheckStatus, signal=SIGNAL, sender=dispatcher.Any  )
    
    
    def CheckStatus(self, sender ):
        """
        Receives data from thread and updates the display
        """
        
        #print sender
        self.data = sender
        #print self.data
        if self.data == 'off':
            self.StopBlinkIcon()    
        else:
            if not self.icon_state == True:
                self.icon_blink = True
                self.FlashIcon(self.data)
            else:
                pass
    
    def FlashIcon(self, msg):
        states = { 'off'   : 'icons/off.ico',
                   'washer': 'icons/washer.ico', 
                   'dryer' : 'icons/dryer.ico', 
                   'both'  : 'icons/both.ico'} 
        if self.icon_blink:
            self.set_icon(states[self.data], self.data)
            self.icon_blink = False
        else:
            self.set_icon(states['off'], self.data)
            self.icon_blink = True
    
    def CreatePopupMenu(self):
        menu = wx.Menu()
        create_menu_item(menu, 'Test blinking both', self.on_test)
        menu.AppendSeparator()
        create_menu_item(menu, 'Reset', self.on_reset)
        menu.AppendSeparator()
        create_menu_item(menu, 'Exit', self.on_exit)
        
        return menu
    
    def set_icon(self, path, caption):
        icon = wx.IconFromBitmap(wx.Bitmap(path))
        self.SetIcon(icon, caption)
    
    def Reset(self, event):
        junk = urlopen(RESET_ADDRESS).read()
        
    def StopBlinkIcon(self):
        self.set_icon('icons/off.ico', 'Off')
        self.icon_state = False
        self.icon_blink = False    
    
#    def on_left_down(self, event):
        #self.CheckStatus(event)
        
        
    def on_exit(self, event):
        self.RemoveIcon()
        wx.CallAfter(self.Destroy)
        
        
        
    def on_reset(self, event):
        self.Reset(event)
        
    def on_test(self, event):
        junk = urlopen(TEST_ADDRESS).read()

def main():
    app = wx.PySimpleApp()
    TaskBarIcon()
    app.MainLoop()

if __name__ == '__main__':
    main()
