import os
from multiprocessing import Process
from threading import Thread
from multiprocessing import Lock
from time import sleep
import datetime
import urllib.request


def say_hello(name):
    print(os.getpid())
    print("hello", name)

	
class say_hello_class(Process):
    def __init__(self, name):
        super().__init__()
        self.name = name
        
    def run(self):
        print(os.getpid())
        print("hello", self.name)	
		
class say_hello_class_T(Thread):
    def __init__(self, name):
        super().__init__()
        self.name = name
        
    def run(self):
        print(os.getpid())
        print("hello", self.name)	
		
		
def count(n):
    while n > 0:
        n -= 1


def printer(item, lock):
    proc = os.getpid()
    print('Вызов {} в {} процесс {}'.format(item, datetime.datetime.now(),proc))
    lock.acquire()
    try:
        print(item)
        sleep(1)
    finally:
        lock.release()
    print('Конец {} в {} процесс {}'.format(item, datetime.datetime.now(), proc))     		
		
		
def slow_print(s):
    print('Вызов {} в {}'.format(s, datetime.datetime.now()))
    sleep(1)
    print('Конец {} в {}'.format(s, datetime.datetime.now()))
	
def run(url):
    handle = urllib.request.urlopen(url)
    fname = os.path.basename(url)
    
    with open(fname, "wb") as f_handler:
        while True:
            chunk = handle.read(1024)
            if not chunk:
                break
            f_handler.write(chunk)
    msg = "%s has finished downloading %s" % (url)			
		